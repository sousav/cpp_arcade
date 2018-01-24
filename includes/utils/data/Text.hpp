//
// Text.hpp for text in /Users/leandr_g/Documents/Shared folder/cpp_arcade/includes/utils/data/
//
// Made by Gaëtan Léandre
// Login   <leandr_g@epitech.eu>
//
// Started on  Thu Mar 16 23:56:39 2017 Gaëtan Léandre
// Last update Wed Mar 22 01:48:04 2017 Gaëtan Léandre
//

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "AVisual.hpp"

class Text : public AVisual {
public:
    enum Align
    {
        CENTER,
        LEFT,
        RIGHT
    };

    explicit Text (std::string const &text, unsigned int size, Position const &pos = Position(), unsigned int zIndex = 0);
    ~Text ();
    Text(const Text &obj);
    Text    &operator=(const Text &obj);
    std::string const &getText() const;
    void setText(std::string const &text);
    Align const &getAlign() const;
    void setAlign(Align const &align);
    unsigned int getSize() const;
    void setSize(unsigned int size);
    void reset(void);

protected:
    std::string _text;
    Align _align;
    unsigned int _size;

};

#else

class Test;

#endif
