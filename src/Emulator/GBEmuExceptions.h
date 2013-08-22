#ifndef GBEMUEXCEPTIONS_H
#define GBEMUEXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace GBEmu{

class GBEmuException : public std::runtime_error{

public:
    GBEmuException(const std::string &msg)
        :std::runtime_error(msg)
    {}




};


class FileNotFoundException : public GBEmuException{

public:
    FileNotFoundException(const std::string fileName)
        :GBEmuException("File not found: " + fileName)
    {}
};


class ROMNotLoadedException : public GBEmuException{

public:
    ROMNotLoadedException()
        :GBEmuException("ROM Not Loaded!")
    {}

};
}
#endif
