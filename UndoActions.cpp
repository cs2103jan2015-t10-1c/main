#include "UndoActions.h"

const string UndoActions::NO_MORE_ACTION = "There is no more action left to undo.";
const string UndoActions::ADDITION_UNDONE = "Addition undone";
const string UndoActions::DELETION_UNDONE = "Deletion undone";
const string UndoActions::EDITING_UNDONE = "Editing undone";

//@author A0115656A
UndoActions::UndoActions() {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void UndoActions::emptyUndoStack() {
	while (!_undoStack.empty()) {
		_undoStack.pop();
	}
}

//to counter addition, push delete command and index number into _undoStack
void UndoActions::counterAdd(bool isScheduled, int latestEntryIndex) {
	_ACTION_TO_UNDO latestAction;
	latestAction._isScheduled = isScheduled;
	latestAction._counterCommand = Delete;
	latestAction._indexNumber = latestEntryIndex;

	_undoStack.push(latestAction);
}

//to counter deletion, push add command, index number and the entry into _undoStack
void UndoActions::counterDelete(bool isScheduled, int latestEntryIndex, Entry latestEntry) {
	_ACTION_TO_UNDO latestAction;
	latestAction._isScheduled = isScheduled;
	latestAction._counterCommand = Add;
	latestAction._indexNumber = latestEntryIndex;
	latestAction._modifiedEntry = latestEntry;

	_undoStack.push(latestAction);
}

//to counter editing, push edit command, index number and the entry into _undoStack
void UndoActions::counterEdit(bool isScheduled, int oldEntryIndex, SuppCommand changeListCommand, int latestEntryIndex, Entry latestEntry) {
	_ACTION_TO_UNDO latestAction;
	latestAction._isScheduled = isScheduled;
	latestAction._counterCommand = Edit;
	latestAction._indexNumber = oldEntryIndex;
	latestAction._changeListCommand = changeListCommand;
	latestAction._newIndexNumber = latestEntryIndex;
	latestAction._modifiedEntry = latestEntry;

	_undoStack.push(latestAction);
}

//pop out the newest member of _undoStack
void UndoActions::removeCounter() {
	_undoStack.pop();
}

void UndoActions::execute(vector<Entry>& _scheduledList, vector<Entry>& _floatingList) {
	if(_undoStack.empty()) {
		SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_INTENSITY));
		cout << NO_MORE_ACTION << endl;
		SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
	} else {
		executeCounter(_undoStack.top(), _scheduledList, _floatingList);
		removeCounter();
	}
}

void UndoActions::executeCounter(_ACTION_TO_UNDO latestAction, vector<Entry>& _scheduledList, vector<Entry>& _floatingList) {
	Command latestCounter = latestAction._counterCommand;
	if (latestCounter == Delete) {
		undoAdd(latestAction, _scheduledList, _floatingList);
	} else if (latestCounter == Add) {
		undoDelete(latestAction, _scheduledList, _floatingList);
	} else if (latestCounter == Edit) {
		undoEdit(latestAction, _scheduledList, _floatingList);
	}
}

//undo addition of entry. Counter command = delete
void UndoActions::undoAdd(_ACTION_TO_UNDO latestAction, vector<Entry>& _scheduledList, vector<Entry>& _floatingList) {
	//scheduled entries
	if (latestAction._isScheduled) {
		_scheduledList.erase(_scheduledList.begin() + latestAction._indexNumber - 1);
	} else {
		_floatingList.erase(_floatingList.begin() + latestAction._indexNumber - 1);
	}

	SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << ADDITION_UNDONE << endl;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
}

//undo deletion of entry. Counter command = add
void UndoActions::undoDelete(_ACTION_TO_UNDO latestAction, vector<Entry>& _scheduledList, vector<Entry>& _floatingList) {
	vector<Entry>::iterator iter;
	if (latestAction._isScheduled) {
		//getIter(latestAction, _scheduledList, iter);
		if (latestAction._indexNumber > _scheduledList.size()) {
			iter = _scheduledList.end();
		} else {
			iter = _scheduledList.begin() + latestAction._indexNumber - 1;
		}
		_scheduledList.insert(iter, latestAction._modifiedEntry);
	} else {
		if (latestAction._indexNumber > _floatingList.size()) {
			iter = _floatingList.end();
		} else {
			iter = _floatingList.begin() + latestAction._indexNumber - 1;
		}
		_floatingList.insert(iter, latestAction._modifiedEntry);
	}

	SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << DELETION_UNDONE << endl;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
}

//undo editing of entry. Counter command = edit
void UndoActions::undoEdit(_ACTION_TO_UNDO latestAction, vector<Entry>& _scheduledList, vector<Entry>& _floatingList) {
	vector<Entry>::iterator addedIter;
	vector<Entry>::iterator removedIter;
	if (latestAction._isScheduled) {
		if (latestAction._indexNumber > _scheduledList.size()) {
			addedIter = _scheduledList.end();
		} else {
			addedIter = _scheduledList.begin() + latestAction._indexNumber - 1;
		}
		_scheduledList.insert(addedIter, latestAction._modifiedEntry);
		
		if (latestAction._changeListCommand == NoChange) {
			if (latestAction._indexNumber <= latestAction._newIndexNumber) {
				removedIter = _scheduledList.begin() + latestAction._newIndexNumber;
			} else {
				removedIter = _scheduledList.begin() + latestAction._newIndexNumber - 1;
			}
			_scheduledList.erase(removedIter);
		} else if (latestAction._changeListCommand == BackToScheduled) {
			removedIter = _floatingList.begin() + latestAction._newIndexNumber - 1;
			_floatingList.erase(removedIter);
		}
	} else {
		if (latestAction._indexNumber > _floatingList.size()) {
			addedIter = _floatingList.end();
		} else {
			addedIter = _floatingList.begin() + latestAction._indexNumber - 1;
		}
		_floatingList.insert(addedIter, latestAction._modifiedEntry);
		if (latestAction._changeListCommand == NoChange) {
			removedIter = _floatingList.begin() + latestAction._newIndexNumber;
			_floatingList.erase(removedIter);
		} else if (latestAction._changeListCommand == BackToFloating) {
			removedIter = _scheduledList.begin() + latestAction._newIndexNumber - 1;
			_scheduledList.erase(removedIter);
		}
	}

	SetConsoleTextAttribute(hConsole, (FOREGROUND_GREEN | FOREGROUND_INTENSITY));
	cout << EDITING_UNDONE << endl;
	SetConsoleTextAttribute(hConsole, (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN));
}