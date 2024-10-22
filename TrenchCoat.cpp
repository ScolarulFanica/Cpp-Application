#include "TrenchCoat.h"
#include "CoatsValidator.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

Coat::Coat(const int & size, const string & colour, const double & price, const int & quantity, const string & photograph): size{size},colour{colour},price{price},quantity{quantity},photograph{photograph}
{
}

Coat::Coat(const Coat& c)
{
    this->size = c.size;
    this->colour = c.colour;
    this->price = c.price;
    this->quantity = c.quantity;
    this->photograph = c.photograph;
}

Coat::~Coat()
{
}

Coat& Coat::operator=(const Coat& c)
{
    if (this == &c)
        return *this;

    this->size = c.size;
    this->colour = c.colour;
    this->price = c.price;
    this->quantity = c.quantity;
    this->photograph = c.photograph;

    return *this;
}

void Coat::setSize(int size)
{
    this->size = size;
}

void Coat::setColour(string colour)
{
    this->colour = colour;
}

void Coat::setPrice(double price)
{
    this->price = price;
}

void Coat::setQuantity(int quantity)
{
    this->quantity = quantity;
}

void Coat::setPhotograph(string photograph)
{
    this->photograph = photograph;
}

bool Coat::operator==(const Coat& c)
{
    return this->size == c.size && this->colour == c.colour && this->price == c.price && this->quantity == c.quantity && this->photograph == c.photograph;
}

/*
    Tokenizes a string.
    Input:	str - the string to be tokenized.
            delimiter - char - the delimiter used for tokenization
    Output: a vector of strings, containing the tokens
*/

vector<string> tokenize(string str, char delimiter)
{
    vector<string> result;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);
    return result;
}

/*
Store repository data in a text file. When the program
starts, entities are read from the file. Modifications
made during program execution are stored in the file.
Implement this using the iostream library. Create
insertion and extraction operators for your entities and
use these when reading/writing to files or the console.
*/

//The coat will be read from the console in the following format: size,colour,price,quantity,photograph

std::istream& operator>>(std::istream& is, Coat& c)
{
    string line;
    getline(is, line);

    vector<string> tokens = tokenize(line, ',');
    if (tokens.size() != 5)
        return is;

    c.size = stoi(tokens[0]);
    c.colour = tokens[1];
    c.price = stod(tokens[2]);
    c.quantity = stoi(tokens[3]);
    c.photograph = tokens[4];

    //Validate program input
    int err = 0;
    CoatsValidator v;
    v.validateCoat(c);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Coat& c)
{
    os << c.size << "," << c.colour << "," << c.price << "," << c.quantity << "," << c.photograph << "\n";
    return os;
}


string Coat::toString()
{
    return to_string(this->size) + "," + this->colour + "," + to_string(this->price) + "," + to_string(this->quantity) + "," + this->photograph;
}