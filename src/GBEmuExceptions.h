#ifndef GBEMUEXCEPTIONS_H
#define GBEMUEXCEPTIONS_H

#include <exception>
#include <string>

namespace GBEmu{

    class GBEmuException : public std::exception{

        public:
            GBEmuException(const std::string &msg)
                :msg(msg)
            {}


            virtual const char *what() noexcept{
                return msg.c_str();
            }

        protected:
            std::string msg;
    };


    class FileNotFoundException : public GBEmuException{

        public:
            FileNotFoundException(const std::string fileName)
                :GBEmuException(fileName)
            {
                this->msg = "File not found: " + fileName;
            }
    };
}
#endif
