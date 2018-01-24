//
// ScoreManager.cpp for score manager in /Users/leandr_g/Documents/Shared folder/cpp_arcade/sources/
//
// Made by Gaëtan Léandre
// Login   <leandr_g@epitech.eu>
//
// Started on  Thu Mar 23 22:57:06 2017 Gaëtan Léandre
// Last update Thu Apr  6 01:52:14 2017 Gaëtan Léandre
//

#include "ScoreManager.hpp"

ScoreManager::ScoreManager (std::string const & gameName, std::string name)
{
    this->_name = name;
    this->_file.open(gameName + std::string(".teur"), std::fstream::in | std::fstream::out | std::fstream::app);
    this->loadScores();
}

ScoreManager::~ScoreManager ()
{
    if (this->_file.is_open())
        this->_file.close();
}

void ScoreManager::pushNewScore(int nsco)
{
    Score score;

    if (this->_file.is_open())
    {
        this->_file.clear();
        this->_file.seekp(0, std::fstream::end);
        this->_file << nsco << " " << this->_name << std::endl;
    }
    score.score = nsco;
    score.name = this->_name;
    this->_scoreBoard.push_back(score);
}

int ScoreManager::getBestScore() const
{
    int score;

    if (this->_scoreBoard.size() > 0)
        score = this->_scoreBoard[0].score;
    else
        score = 0;
    for (std::vector<Score>::const_iterator it = this->_scoreBoard.begin() ; it != this->_scoreBoard.end(); ++it)
    {
        if ((*it).score > score)
            score = (*it).score;
    }
    return (score);
}

std::string ScoreManager::getBestName() const
{
    std::string name("");
    int score;

    if (this->_scoreBoard.size() > 0)
        score = this->_scoreBoard[0].score - 1;
    else
        score = 0;
    for (std::vector<Score>::const_iterator it = this->_scoreBoard.begin() ; it != this->_scoreBoard.end(); ++it)
    {
        if ((*it).score > score)
        {
            name = (*it).name;
            score = (*it).score;
        }
    }
    return (name);
}

std::string const &ScoreManager::getName() const
{
    return (this->_name);
}
void ScoreManager::setName(std::string const &name)
{
    this->_name = name;
}

std::vector<Score> const &ScoreManager::getScoreBoard() const
{
    return (this->_scoreBoard);
}

bool ScoreManager::getLineInfo(std::string line, Score &score)
{
    std::stringstream ss(line);
    int sco;
    std::string name;

    if (ss >> sco >> name)
    {
        score.name = name;
        score.score = sco;
        return (true);
    }
    return (false);
}

void ScoreManager::loadScores()
{
    std::string line;
    Score score;

    if (this->_file.is_open())
    {
        this->_file.seekp(0, std::fstream::beg);
        while (getline(this->_file, line))
        {
            if (getLineInfo(line, score))
                this->_scoreBoard.push_back(score);
        }
    }
}
