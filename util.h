#ifndef _UTIL_H_
#define _UTIL_H_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


std::string int_to_string(int n);
std::string float_to_string(float n);
int aleatoire(int max);
void genererAleaBorne(int &a, int borne_inf_a, int borne_sup_a, int &b, int borne_inf_b, int borne_sup_b);
int aleaDir();
void sauvegarde(int score, int life, int niveau, int timeleft, int vitball, int surface_tot, std::string perso);
bool chargement( int &score, int &life, int &niveau , int &timeleft, int &vitball, int &surface_tot, std::string &perso);
bool chargerHighScore(std::vector<std::string> &name, std::vector<int> &score, std::vector<int> &niveau);
bool MaJHighScore(std::string name, int score, int niveau);

#endif
