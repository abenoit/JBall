#ifndef NEWSCORE_H
#define NEWSCORE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <cstdlib>
#include <iostream>

void newScore(sf::RenderWindow * _window, std::string &name, int score, int niveau, bool quit, bool &stop);

#endif
