#ifndef LOCAL_EXCEPTIONS_H_
#define LOCAL_EXCEPTIONS_H_

#include <string>

/**
 * @brief This class provides an exception that can be thrown if an element is tried to be accessed but does not exist
 */
class elementDoesNotExistException : public std::exception
{
public:
    /**
     * @{
     * @brief Constructor for the exception class
     * 
     * @param element A string that should hold the name of the element that was requested [optional]
     * @param id The id of the element, if it has one, like the bitId of a net [optional]
     */
    elementDoesNotExistException(std::string element, unsigned int id) :
                                 message("Tried to get a non-existing " + element + " with id " + std::to_string(id)){};
    elementDoesNotExistException(std::string element) : message("Tried to get a non-existing " + element){};
    elementDoesNotExistException(unsigned int id) : message("Tried to get a non-existing element with id " + id){};
    elementDoesNotExistException() : message("Tried to get a non-existing unknown element"){};
    /**
     * @}
     */
    virtual ~elementDoesNotExistException(){};
    virtual const char *what() const throw()
    {
        return message.c_str();
    }
private:
    std::string message;    //<! The error message that will be returned
};

#endif // LOCAL_EXCEPTIONS_H_