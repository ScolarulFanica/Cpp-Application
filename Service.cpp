#include "Service.h"

Service::Service(Repository& repo) : repo{repo} 
{
	this->repo = repo;
}

void Service::undo()
{
	if (this->undoStack.empty())
		throw std::exception("No more undos!");

	auto action = std::move(this->undoStack.back());
	this->undoStack.pop_back();
	action->executeUndo();
	this->redoStack.push_back(std::move(action));
}

void Service::redo()
{
	if (this->redoStack.empty())
		throw std::exception("No more redos!");

	auto action = std::move(this->redoStack.back());
	this->redoStack.pop_back();
	action->executeRedo();
	this->undoStack.push_back(std::move(action));
}

void Service::addUndo(std::unique_ptr<UndoAction> action)
{
	this->undoStack.push_back(std::move(action));
	this->redoStack.clear();
}

void Service::clearRedo()
{
	this->redoStack.clear();
}

void Service::add(const int& size, const string& colour, const double& price, const int& quantity, const string& photograph)
{
	Coat c{ size, colour, price, quantity, photograph };
	this->addUndo(std::make_unique<UndoAdd>(this->repo, c));
	this->repo.add(c);
}

void Service::remove(int pos)
{
	this->addUndo(std::make_unique<UndoRemove>(this->repo, this->repo.getAll()[pos]));
	this->repo.remove(pos);
}

void Service::update(const int& size, const string& colour, const double& price, const int& quantity, const string& photograph, const int& pos)
{
	Coat c{ size, colour, price, quantity, photograph };
	this->addUndo(std::make_unique<UndoUpdate>(this->repo, this->repo.getAll()[pos], c));
	this->repo.update(c, pos);
}

std::vector<Coat> Service::getAll() const
{
	return this->repo.getAll();
}

/*
Add multiple undo and redo functionality for the add, remove, and update operations.
Implement this functionality using inheritance and polymorphism.
You will have Undo and Redo buttons on the GUI, as well as a key combination to undo and redo the operations (e.g. Ctrl+Z, Ctrl+Y).
*/

