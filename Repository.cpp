#include "Repository.h"
#include <fstream>

using namespace std;

RepositoryException::RepositoryException(const std::string& message) : message{ message }
{
}

std::string RepositoryException::getMessage() const
{
	return this->message;
}

// ----------------------------------------------------------------------------------

Repository::Repository()
{
	this->readFromFile();
}

void Repository::add(const Coat& coat)
{
	this->coats.push_back(coat);
	this->writeToFile();
}

int Repository::find(const Coat& coat)
{
	for (int i = 0; i < this->coats.size(); i++)
		if (this->coats[i] == coat)
			return i;
	return -1;
}

void Repository::remove(int pos)
{
	this->coats.erase(this->coats.begin()+pos);
	this->writeToFile();
}

void Repository::update(const Coat& newCoat, int pos)
{
	this->coats[pos] = newCoat;
	this->writeToFile();
}


std::vector<Coat> Repository::getAll() const
{
	return this->coats;
}

void Repository::readFromFile()
{
	ifstream f{ "Coats.csv" };
	if (!f.is_open())
		throw RepositoryException{ "File could not be opened for reading!" };

	Coat c{};
	while (f >> c)
	{
		this->coats.push_back(c);
	}

	f.close();
}

void Repository::writeToFile()
{
	ofstream f("Coats.csv");
	if (!f.is_open())
		throw RepositoryException{ "File could not be opened for writing!" };

	for (auto c : coats)
	{
		f << c;
	}

	f.close();
}
