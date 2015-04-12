#ifndef UNDOACTIONS_H
#define UNDOACTIONS_H

#include <stack>
#include "Entry.h"

using namespace std;

//@author A0115656A
//UndoActions can only undo the effect of Add, Edit and Delete because only these 3 commands
//modify the content of _scheduledList and _floatingList in ScheduledEntry
class UndoActions {
public:
	enum Command {
		Add, Delete, Edit
	};
	enum SuppCommand {
		BackToFloating, BackToScheduled, NoChange
	};

private:
	struct _ACTION_TO_UNDO {
		bool _isScheduled;
		//counterCommand refers to a command that can reverse the effect of the most recent command 
		//Here are the list of pairs of command and its counterCommand:
		//1. Add - Delete
		//2. Delete - Add
		//3. Edit - Edit
		Command _counterCommand;
		int _indexNumber;
		Entry _modifiedEntry;

		//only for edit
		SuppCommand _changeListCommand;
		int _newIndexNumber;
	};
	stack<_ACTION_TO_UNDO> _undoStack;

	HANDLE hConsole;

	static const string NO_MORE_ACTION;
	static const string ADDITION_UNDONE;
	static const string DELETION_UNDONE;
	static const string EDITING_UNDONE;

public:
	UndoActions();
	void emptyUndoStack();
	void counterAdd(bool, int);
	void counterDelete(bool, int, Entry);
	void counterEdit(bool, int, SuppCommand, int, Entry);
	void removeCounter();

	void execute(vector<Entry>&, vector<Entry>&);
	void executeCounter(_ACTION_TO_UNDO, vector<Entry>&, vector<Entry>&);
	
	void undoAdd(_ACTION_TO_UNDO, vector<Entry>&, vector<Entry>&);
	void undoDelete(_ACTION_TO_UNDO, vector<Entry>&, vector<Entry>&);
	void undoEdit(_ACTION_TO_UNDO, vector<Entry>&, vector<Entry>&);
};

#endif