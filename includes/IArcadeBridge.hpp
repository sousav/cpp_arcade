/*
** IArcadeBridge.hpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/includes
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Mon Mar 20 22:23:14 2017 Lucas Gambini
** Last update	Sat Apr 08 12:21:08 2017 Full Name
*/

#ifndef IARCADEBRIDGE_HPP_
#define IARCADEBRIDGE_HPP_

class IArcadeBridge {

public:
    IArcadeBridge    &operator=(const IArcadeBridge &obj);

    virtual void prevGraph() = 0;
    virtual void nextGraph() = 0;

    virtual void prevGame() = 0;
    virtual void nextGame() = 0;

    virtual void toggleRunning() = 0;
    virtual void goUp() const = 0;
    virtual void goDown() const = 0;
    virtual void goLeft() const = 0;
    virtual void goRight() const = 0;
    virtual void goForward() const = 0;
    virtual void shoot() const = 0;
    virtual void pressEchap() = 0;
    virtual void pressEight() = 0;
    virtual void pressNine() = 0;
};

#endif /* !IARCADEBRIDGE_HPP_ */
