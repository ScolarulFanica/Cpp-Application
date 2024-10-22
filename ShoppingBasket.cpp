#include "ShoppingBasket.h"
#include <fstream>

using namespace std;

ShoppingBasketException::ShoppingBasketException(const std::string& message) : message{ message }
{
}

std::string ShoppingBasketException::getMessage() const
{
	return this->message;
}

// ----------------------------------------------------------------------------------

ShoppingBasket::ShoppingBasket(Repository& repo) : repo{ repo }
{
	this->repo = repo;
}

void ShoppingBasket::add(const Coat& coat)
{
	if (this->repo.find(coat) == -1)
		throw ShoppingBasketException("The coat doesn't exist!\n");
	this->shoppingBasket.push_back(coat);
}

std::vector<Coat> ShoppingBasket::getAll() const
{
	return this->shoppingBasket;
}