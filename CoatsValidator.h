#pragma once
#include <string>
#include "TrenchCoat.h"

class ValidationException
{
private:
    std::string message;
public:
    ValidationException(std::string message);
    std::string getMessage() const;
};

class ValidationExceptionInherited : public std::exception {
private:
    std::string message;
public:
    ValidationExceptionInherited(std::string message);
    const char* what() const noexcept override;
};

class CoatsValidator
{
public:
    static void validateCoat(const Coat& c);
};
