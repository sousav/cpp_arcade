/*
** Music.hpp for Shared in /Users/gmblucas/Desktop/Shared/cpp_arcade/includes/utils/data
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Tue Mar 14 02:26:28 2017 Lucas Gambini
** Last update	Fri Mar 17 02:30:38 2017 Full Name
*/

#ifndef AUDIO_HPP_
#define AUDIO_HPP_

#include "AData.hpp"

class Audio: public AData {

public:
    explicit Audio (std::string const & audio, unsigned int intensity = 100, bool repeat = false);
    ~Audio ();
    Audio(const Audio &obj);
    Audio    &operator=(const Audio &obj);

    std::string const &getAudio() const;
    void setAudio(std::string const &audio);

    bool getRepeat() const;
    void setRepeat(bool repeat);

    unsigned int getIntensity() const;
    void setIntensity(unsigned int intensity);

    void reset(void);

private:
    std::string _audio;
    unsigned int _intensity;
    bool _repeat;

};

#else

class Audio;

#endif /* !AUDIO_HPP_ */
