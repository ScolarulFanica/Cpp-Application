#include "CoatsValidator.h"

ValidationException::ValidationException(std::string message) : message{ message }
{
}
std::string ValidationException::getMessage() const
{
    return this->message;
}

ValidationExceptionInherited::ValidationExceptionInherited(std::string message) : message{ message }
{
}

const char* ValidationExceptionInherited::what() const noexcept
{
    return this->message.c_str();
}

void CoatsValidator::validateCoat(const Coat& c)
{
    std::string errors;
    if (c.getSize() < 0)
        errors += "The size of the coat must be a positive integer!\n";
    if (c.getColour().size() == 0)
        errors += "The colour of the coat must be a non-empty string!\n";
    if (c.getPrice() < 0)
        errors += "The price of the coat must be a positive real number!\n";
    if (c.getQuantity() < 0)
        errors += "The quantity of the coat must be a positive integer!\n";
    if (c.getPhotograph().size() == 0)
        errors += "The photograph of the coat must be a non-empty string!\n";
    if (errors.size() > 0)
        throw ValidationException(errors);
}