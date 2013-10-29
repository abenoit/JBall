#ifndef _GAME_MODEL_
#define _GAME_MODEL_
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "Ball.h"
#include "Wall.h"
#include "Model.h"
#include "util.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class Wall;
class Ball;

///
/// @class GameModel
///
class GameModel : public Model
{
private:
    /// Longueur de la fenêtre
    int _w;
    /// Hauteur de la fenêtre
    int _h;
    ///vecteur qui contiend tous les pointeurs sur les balles
    std::vector<Ball*> _tabBall;
    ///vecteur de vecteur qui contiend tous les pointeurs sur les murs de la matrice
    std::vector < std::vector < Wall* > > Matrice;


    /// Entier représentant le nombre de vie
    int _vie_model;
    /// Score du joueur
    int _score_model;
    /// Surface recouverte
    int _surface_model;
    /// Temps restant
    float _temps_model;
    /// Niveau du jeu
    int _niveau_model;
    /// Surface à recouvrir
    int _surface_a_recouvrir;
    /// Temps maximum par niveau
    int _temps_par_niveau;
    /// Vitesse des balles
    int _vitesse_ball;
    /// Vitesse de la progression des barres
    float _vitesse_barre;
    /// Taille de la balle
    int _taille_ball;

    /// Temporisateur permettant de mettre à jour le temps du jeu
    sf::Clock _clock_temps;
    /// Son actif lorsque l'on touche une barre en construction
    sf::SoundBuffer touchBall;
    sf::Sound touchSoundBall;

    bool touchBarre ;

public:

    GameModel(int w, int h);
    ~GameModel();

    //Méthode
    void nextStep();

    //Accesseur pour obtenir des données
    void getBallPos(int &x, int &y, int i);          //la position en x,y de la balle d'indice i dans le vecteur tabBall
    //void getWallPos(int &x, int &y, int i, int j);   //la position en x,y du mur d'indice i,j dans le vecteur de vecteur Matrice
    std::string getEtat(int i,int j);                     //l'état du mur d'indice i,j
    int getVie();                                    //le nombre de vie restantes
    int getScore();                                  //le score
    float getTemps();                                  //le temps
    int getNiveau();                                 //le niveau
    int getNbBall();                                 //le nombre de balle présente dans la vecteur tabBall
    int getVitBall();                                //la vitesse de la (des) balle(s)
    float getVitBarre();                             //la vitesse des barres
    int getSurfaceARecouvrir();                      //la surface totale à recouvrir
    int getTempsParNiveau();                         //le temps par niveau
    bool getTouchBarre();

    //Accesseur pour mettre à jour les données
    void setVitesseBall(int vit);                    //la vitesse de toutes les balles
    void setVie(int vie);                            //le nombre de vie
    void setTempsParNiveau(int temps);               //le temps par niveau
    void setTemps(int new_temps);                    //le temps restant
    void setEtat(int x, int y, std::string e);       //l'état du mur d'indice x,y
    void setSurfaceARecouvrir(int surf);             //la surface à recouvrir
    void setNiveau(int niv);                         //le niveau
    void setTouchBarre(bool touch);
    void setVitesseBarre(float vit);
    void setNbBall(int nb);
    void setScore(int score);

    void resetTemps();

    void ajoutBall();
    void suppBall();
    void clearBall();



    bool BarreHorizDroit(int x, int y, int &nb_d, bool &fini);
    bool BarreHorizGauche(int x, int y, int &nb_g, bool &fini);
    bool BarreVertiHaut(int x, int y, int &nb_h, bool &fini);
    bool BarreVertiBas(int x, int y, int &nb_b, bool &fini);
    int calculSurface();
    void remplissageHori(int x, int y, int nb_g, int nb_d);
    void remplissageVerti(int x, int y, int nb_b, int nb_h);
    void initGrille();
    void initAll();

    bool verifPositionBallOk(int a, int b);
};
#endif
