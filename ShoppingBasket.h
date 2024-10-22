#pragma once
#include "TrenchCoat.h"
#include "Repository.h"
#include <string>
#include <vector>

class ShoppingBasketException : public std::exception
{
private:
	std::string message;

public:
	ShoppingBasketException(const std::string& message);
	std::string getMessage() const;
};

// ----------------------------------------------------------------------------------

class ShoppingBasket
{
private:
	std::vector<Coat> shoppingBasket;
	Repository& repo;

public:
	ShoppingBasket(Repository& repo);
	void add(const Coat& coat);
	std::vector<Coat> getAll() const;
	Repository& getRepo() const{
		return repo;
	}
};