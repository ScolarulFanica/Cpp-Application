#pragma once
#include <string.h>
#include <iostream>

using std::string;

class Coat {
private:
    int size;
    string colour;
    double price;
    int quantity;
    string photograph;
public:
    //default constructor for a Coat
    Coat() {}

    //constructor with parameters
    Coat(const int & size, const string & colour, const double & price, const int & quantity, const string & photograph);

    //copy constructor for a Coat
    Coat(const Coat& c);

    //destructor for a Coat
    ~Coat();

    //assignment operator for a Coat
    Coat& operator=(const Coat& c);

    //getters for the Coat
    int getSize() const { return size; }
    string getColour() const { return colour; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    string getPhotograph() const { return photograph; }

    //setters for the Coat
    void setSize(int size);
    void setColour(string colour);
    void setPrice(double price);
    void setQuantity(int quantity);
    void setPhotograph(string photograph);

    //overloading the == operator
    bool operator==(const Coat& c);

    //overloading the << operator
    friend std::ostream& operator<<(std::ostream& os, const Coat& c);

    //overloading the >> opertaor
    friend std::istream& operator>>(std::istream& is, Coat& c);

    //returns a string with the Coat's attributes
    string toString();

};