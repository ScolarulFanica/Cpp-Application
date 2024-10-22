#pragma once
#include "TrenchCoat.h"
#include <string>
#include <vector>

class RepositoryException : public std::exception
{
private:
	std::string message;

public:
	RepositoryException(const std::string& message);
	std::string getMessage() const;
};

// ----------------------------------------------------------------------------------

class Repository
{
private:
	std::string filename;
	std::vector<Coat> coats;

public:
	Repository();
	void add(const Coat& coat);
	void remove(int pos);
	int find(const Coat& coat);
	void update(const Coat& newCoat, int pos);
	std::vector<Coat> getAll() const;

private:
	void readFromFile();
	void writeToFile();
};

