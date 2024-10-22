#pragma once
#include "Repository.h"
#include "TrenchCoat.h"

class UndoAction
{
public:
    virtual void executeUndo() = 0;
    virtual void executeRedo() = 0;
    virtual ~UndoAction() = default;
};

class UndoAdd : public UndoAction
{
private:
    Repository& repo;
    Coat addedCoat;
public:
    UndoAdd(Repository& repo, const Coat& addedCoat) : repo{ repo }, addedCoat{ addedCoat } {}
    void executeUndo() override
    {
        repo.remove(this->repo.find(addedCoat));
    }
    void executeRedo() override
    {
        repo.add(addedCoat);
    }
};

class UndoRemove : public UndoAction
{
private:
    Repository& repo;
    Coat removedCoat;
public:
    UndoRemove(Repository& repo, const Coat& removedCoat) : repo{ repo }, removedCoat{ removedCoat } {}
    void executeUndo() override
    {
        repo.add(removedCoat);
    }
    void executeRedo() override
    {
        repo.remove(this->repo.find(removedCoat));
    }
};

class UndoUpdate : public UndoAction
{
private:
    Repository& repo;
    Coat oldCoat;
    Coat newCoat;
public:
    UndoUpdate(Repository& repo, const Coat& oldCoat, const Coat& newCoat) : repo{ repo }, oldCoat{ oldCoat }, newCoat{ newCoat } {}
    void executeUndo() override
    {
        repo.update(oldCoat, this->repo.find(newCoat));
    }
    void executeRedo() override
    {
        repo.update(newCoat, this->repo.find(oldCoat));
    }
};
