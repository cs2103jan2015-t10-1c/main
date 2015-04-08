#include "UndoActions.h"

const string UndoActions::NO_MORE_ACTION = "There is no more action left to undo.";
const string UndoActions::ADDITION_UNDONE = "Addition undone";
const string UndoActions::DELETION_UNDONE = "Deletion undone";
const string UndoActions::EDITING_UNDONE = "Editing undone";

UndoActions::UndoActions(){
}

void UndoActions::emptyUndoStack(){
	while (!_undoStack.empty()){
		_undoStack.pop();
	}
}

//to counter addition, push delete command and index number into _undoStack
void UndoActions::counterAdd(bool isScheduled, int latestEntryIndex){
	_ACTION_TO_UNDO latestAction;
	latestAction._isScheduled = isScheduled;
	latestAction._counterCommand = Delete;
	latestAction._indexNumber = latestEntryIndex;

	_undoStack.push(latestAction);
}

//to counter deletion, push add command, index number and the entry into _undoStack
void UndoActions::counterDelete(bool isScheduled, int latestEntryIndex, Entry latestEntry){
	_ACTION_TO_UNDO latestAction;
	latestAction._isScheduled = isScheduled;
	latestAction._counterCommand = Add;
	latestAction._indexNumber = latestEntryIndex;
	latestAction._modifiedEntry = latestEntry;

	_undoStack.push(latestAction);
}

//to counter editing, push edit command, index number and the entry into _undoStack
void UndoActions::counterEdit(bool isScheduled, int latestEntryIndex, Entry latestEntry){
	_ACTION_TO_UNDO latestAction;
	latestAction._isScheduled = isScheduled;
	latestAction._counterCommand = Edit;
	latestAction._indexNumber = latestEntryIndex;
	latestAction._modifiedEntry = latestEntry;

	_undoStack.push(latestAction);
}

void UndoActions::execute(vector<Entry>& _scheduledList, vector<Entry>& _floatingList){
	//no more action to undo
	if(_undoStack.empty()){
		cout << NO_MORE_ACTION << endl;
	}

	//there is action to undo
	else {
		executeCounter(_undoStack.top(), _scheduledList, _floatingList);
		//remove the counter action that was just executed from the stack
		_undoStack.pop();
	}
}

void UndoActions::executeCounter(_ACTION_TO_UNDO latestAction, vector<Entry>& _scheduledList, vector<Entry>& _floatingList){
	Command latestCounter = latestAction._counterCommand;
	//undo addition of entry
	if (latestCounter == Delete){
		undoAdd(latestAction, _scheduledList, _floatingList);
	}

	//undo deletion of entry
	else if (latestCounter == Add){
		undoDelete(latestAction, _scheduledList, _floatingList);
	}

	//undo editing of entry
	else if (latestCounter == Edit){
		undoEdit(latestAction);
	}
}

//undo addition of entry. Counter command = delete
void UndoActions::undoAdd(_ACTION_TO_UNDO latestAction, vector<Entry>& _scheduledList, vector<Entry>& _floatingList){
	//scheduled entries
	if (latestAction._isScheduled){
		_scheduledList.erase(_scheduledList.begin() + latestAction._indexNumber - 1);
	}

	//floating entries
	else {
		_floatingList.erase(_floatingList.begin() + latestAction._indexNumber - 1);
	}

	cout << ADDITION_UNDONE << endl;
}

//undo deletion of entry. Counter command = add
void UndoActions::undoDelete(_ACTION_TO_UNDO latestAction, vector<Entry>& _scheduledList, vector<Entry>& _floatingList){
	vector<Entry>::iterator iter;
	//scheduled entries
	if (latestAction._isScheduled){
		iter = _scheduledList.begin() + latestAction._indexNumber - 1;
		_scheduledList.insert(iter, latestAction._modifiedEntry);
	}

	//floating entries
	else {
		iter = _floatingList.begin() + latestAction._indexNumber - 1;
		_floatingList.insert(iter, latestAction._modifiedEntry);
	}

	cout << DELETION_UNDONE << endl;
}

//undo editing of entry. Counter command = edit
void UndoActions::undoEdit(_ACTION_TO_UNDO latestAction){
	//scheduled entries
	if (latestAction._isScheduled){

	}

	//floating entries
	else {

	}

	cout << EDITING_UNDONE << endl;
}