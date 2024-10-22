#pragma once
#include "Repository.h"
#include "Undo.h"

class Service
{
private:
	Repository& repo;
	std::vector<std::unique_ptr<UndoAction>> undoStack;
	std::vector<std::unique_ptr<UndoAction>> redoStack;

public:
	Service(Repository& repo);
	void add(const int& size, const string& colour, const double& price, const int& quantity, const string& photograph);
	void remove(int pos);
	void update(const int& size, const string& colour, const double& price, const int& quantity, const string& photograph, const int& pos);
	std::vector<Coat> getAll() const;
	void undo();
	void redo();
	void addUndo(std::unique_ptr<UndoAction> action);
	void clearRedo();
};

/*
Add multiple undo and redo functionality for the add, remove, and update operations.
Implement this functionality using inheritance and polymorphism.
You will have Undo and Redo buttons on the GUI, as well as a key combination to undo and redo the operations (e.g. Ctrl+Z, Ctrl+Y).
*/

