/*
** exceptions.hpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/includes/utils
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Fri Mar 17 01:36:08 2017 Lucas Gambini
** Last update Sun Apr 09 19:46:07 2017 Lucas Gambini
*/

#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_

# include <string>

class ArcError : public std::exception
{
    public:
        ArcError(std::string const &message) { _message = message; };
        virtual ~ArcError() throw() {};
        virtual const char *what(void) const throw() {
          return (this->_message.data());
        }

    private:
        std::string _message;
};

class InvalidDlOpen : public ArcError
{
    public:
        InvalidDlOpen(std::string const &message): ArcError(message) {};
        virtual ~InvalidDlOpen() throw() {};
};

class InvalidDirectory : public ArcError
{
    public:
        InvalidDirectory(std::string const &message): ArcError(message) {};
        virtual ~InvalidDirectory() throw() {};
};

class NoLibGraphFound : public ArcError
{
    public:
        NoLibGraphFound(std::string const &message): ArcError(message) {};
        virtual ~NoLibGraphFound() throw() {};
};

class NoGraphServerFound : public ArcError
{
    public:
        NoGraphServerFound(std::string const &message): ArcError(message) {};
        virtual ~NoGraphServerFound() throw() {};
};

class GraphServerFailed : public ArcError
{
    public:
        GraphServerFailed(std::string const &message): ArcError(message) {};
        virtual ~GraphServerFailed() throw() {};
};

#endif /* !EXCEPTIONS_HPP_ */
