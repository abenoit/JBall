#include "util.h"
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <ostream>
#include <fstream>
#include <time.h>
using namespace std;

///
/// Fonction permettant de génerer un entier aléatoire compris entre 0 et l'entier passé en paramètre
/// @param max Borne supérieure
/// @return L'entier généré
///
int aleatoire(int max)
{
    int a;
    a = (int) (max*1.0 * rand() / RAND_MAX);
    return a;
}

///
/// Action permettant de génerer deux entiers aléatoires compris entre une borne inférieure et une borne supérieure qui leurs sont propres
/// @param a Premier entier (passé en entrée/sortie)
/// @param borne_inf_a Borne inférieure du premier entier
/// @param borne_sup_a Borne supérieure du premier entier
/// @param b Second entier (passé en entrée/sortie)
/// @param borne_inf_b Borne inférieure du second entier
/// @param borne_sup_b Borne supérieure du second entier
///
void genererAleaBorne(int &a, int borne_inf_a, int borne_sup_a, int &b, int borne_inf_b, int borne_sup_b)
{
    do
    {
        a=aleatoire(borne_sup_a);
    } while (a <borne_inf_a || a > borne_sup_a);

    do
    {
        b=aleatoire(borne_sup_b);
    } while (b < borne_inf_b || b > borne_sup_b);
}

///
/// Fonction générant un entier aléatoire qui est soit 1 soit -1
/// @return Le résultat
///
int aleaDir()
{
    int r = aleatoire(2);

    if (r == 1)
        return -1;
    else
        return 1;
}

///
/// Fonction permattant de convertir un entier en chaîne de caractères
/// @param n Entier à convertir
/// @return La chaîne de caractères correspondante
///
string int_to_string(int n)
{
    ostringstream s;
    s << n;
    return s.str();
}

///
/// Fonction permattant de convertir un réel(float) en chaîne de caractères
/// @param n Réel(float) à convertir
/// @return La chaîne de caractères correspondante
///
string float_to_string(float n)
{
    ostringstream s;
    s << n;
    return s.str();
}

///
/// Action permettant la sauvergarde d'une partie
/// @param score Entier correspondant au score du joueur
/// @param life Entier correspondant aux nombre de vies restantes du joueur
/// @param niveau Entier correspondant au niveau atteint
/// @param timeleft Entier correspondant au temps restant dans la partie en cours
/// @param vitball Entier correspondant à la vitesse des balles dans le jeu
/// @param surface_tot Entier correspondant à la surface à recouvrir
/// @param perso Chaîne de caractère pour le personnage choisi
///
void sauvegarde(int score, int life, int niveau, int timeleft, int vitball, int surface_tot, string perso)
{
    //Ouverture d'un fichier pour ecrire
    ofstream save( "data/sauvegarde.data" );
    if (!save)
        cerr << "Erreur d'ouverture du fichier de sauvegarde : sauvegarde échouée" << endl;
    else
    {
        //Ecriture des scores dans le fichier
        save << score;
        save << " ";
        save << life;
        save << " ";
        save << niveau;
        save << " ";
        save << timeleft;
        save << " ";
        save << vitball;
        save << " ";
        save << surface_tot;
        save << " ";
        save << perso;
        save << endl << endl << "score" << endl << "vie " << endl << "niveau " << endl << "temps restant " << endl << "vitesse balle " << endl << "surface à recouvrir " << endl << "perso";
        //Fermeture du fichier
        save.close();
    }
}

///
/// Fonction permettant de charger une partie (sauvegardée) antérieure
/// @param score Entier correspondant au score du joueur
/// @param life Entier correspondant aux nombre de vies restantes du joueur
/// @param niveau Entier correspondant au niveau atteint
/// @param timeleft Entier correspondant au temps restant dans la partie en cours
/// @param vitball Entier correspondant à la vitesse des balles dans le jeu
/// @param surface_tot Entier correspondant à la surface à recouvrir
/// @param perso Chaîne de caractère pour le personnage choisi
/// @return Le succès du chargement de la partie
///
bool chargement( int &score, int &life, int &niveau , int &timeleft, int &vitball, int &surface_tot, string &perso)
{
    //Ouverture d'un fichier à lire
    ifstream load( "data/sauvegarde.data");

    //Si le fichier est chargé
    if ( load != NULL )
    {
        //Recuperation des scores
        load >> score;
        load >> life;
        load >> niveau;
        load >> timeleft;
        load >> vitball;
        load >> surface_tot;
        load >> perso;
        //Fermeture du fichier
        load.close();
    }

    //Si tout s'est bien passé
    return true;
}

///
/// Fonction permettant de charger le fichier des high scores
/// @param name vecteur contenant le(s) nom(s) présents dans le fichier
/// @param score vecteur contenant le(s) score(s) présents dans le fichier
/// @param niveau vecteur contenant le(s) niveau(x) présents dans le fichier
/// @return Le succès du chargement
///
bool chargerHighScore(vector<string> &name, vector<int> &score, vector<int> &niveau)
{
    //Ouverture d'un fichier à lire
    ifstream fic( "data/high_score.data");

    string s;
    unsigned int count = 0;
    while (std::getline(fic, s))
        count++;

    fic.close();

    ifstream load("data/high_score.data");

    string tmp_n;
    int tmp_s, tmp_ni;

    unsigned int i = 0;

    //Si le fichier est chargé
    if ( load != NULL )
    {
        name.clear();
        score.clear();
        niveau.clear();

        while (i < count && i < 9)
        {
            //Recuperation des scores
            load >> tmp_n;
            name.push_back(tmp_n);

            load >> tmp_s;
            score.push_back(tmp_s);

            load >> tmp_ni;
            niveau.push_back(tmp_ni);

            i++;
        }

        //Fermeture du fichier
        load.close();
    }

    //Si tout s'est bien passé
    return true;
}

///
/// Fonction permettant de mettre à jour les scores
/// @param name Nom du joueur
/// @param score Score du joueur
/// @param niveau Niveau du joueur
/// @return Vrai si tout s'est bien dérouler
///
bool MaJHighScore(string name, int score, int niveau)
{
    //Ouverture d'un fichier à lire
    ifstream fic( "data/high_score.data");

    string s;
    unsigned int count = 0;
    while (std::getline(fic, s))
        count++;

    fic.close();

    ifstream load("data/high_score.data");

    string tmp_n;
    int tmp_s, tmp_ni;

    vector<string> vect_name;
    vector<int> vect_score;
    vector<int> vect_niveau;

    unsigned int i = 0;

    //Si le fichier est chargé
    if ( load != NULL )
    {
        while (i < count && i < 9)
        {
            //Recuperation des scores
            load >> tmp_n;
            vect_name.push_back(tmp_n);

            load >> tmp_s;
            vect_score.push_back(tmp_s);

            load >> tmp_ni;
            vect_niveau.push_back(tmp_ni);

            i++;
        }

        //Fermeture du fichier
        load.close();

        vector<int> copie_score;
        copie_score = vect_score;
        vector<string> copie_name;
        copie_name = vect_name;
        vector<int> copie_niveau;
        copie_niveau = vect_niveau;

        vect_name.clear();
        vect_score.clear();
        vect_niveau.clear();

        bool place = false;
        unsigned int i = 0;

        while (i<copie_score.size())
        {
            if (score > copie_score[i] && !place)
            {
                vect_score.push_back(score);
                vect_name.push_back(name);
                vect_niveau.push_back(niveau);
                place = true;
            }
            else
            {
                vect_score.push_back(copie_score[i]);
                vect_name.push_back(copie_name[i]);
                vect_niveau.push_back(copie_niveau[i]);
                i++;
            }
        }

        //Si il y avait déjà 9 scores avant et qu'on en a rajouté un, donc 10, on va enlevé le dernier pour ne pas encombrer le fichier high_score.data
        if (place && vect_score.size() == 10)
        {
            vect_score.pop_back();
            vect_name.pop_back();
            vect_niveau.pop_back();
        }

        //Si il y a moins de 9 scores enregistrés et qu'on a pas pu le rentré précemment (score le plus faible) alors on le place à la fin
        if (!place && vect_score.size() < 8)
        {
            vect_score.push_back(score);
            vect_name.push_back(name);
            vect_niveau.push_back(niveau);
            place = true;
        }

        if (place)
        {
            ofstream load("data/high_score.data");

            for (unsigned int i = 0; i < vect_score.size() ; i++)
            {
                load << vect_name[i] << " " << vect_score[i] << " " << vect_niveau[i] << endl;
            }

            //Fermeture du fichier
            load.close();
        }

    }

    //Si tout s'est bien passé
    return true;
}
