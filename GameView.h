#ifndef _GAMEVIEW_
#define _GAMEVIEW_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameModel.h"
#include "Vue.h"
#include "Bouton.h"
#include "GameController.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include "vieMoins.h"
#include "newScore.h"
#include "gameOver.h"
#include "niveauSuivant.h"
#include "menuChoix.h"


class GameController;
class Options;
///
/// @class GameView
///
class GameView : public Vue
{
    friend class GameController;

private:
    /// Fenêtre de rendu
    sf::RenderWindow * _window;

    //----------------------------------------------------------------
    // Les Images
    //----------------------------------------------------------------

    /// Image de type sf  pour le fond d'écran principal
    sf::Image _img_background;
    /// Image de type sf pour la balle
    sf::Image  _img_balle;


    sf::Image _img_sonic;
    sf::Image _img_amy;
    sf::Image _img_knuckles;
    sf::Image _img_shadow;
    sf::Image _img_tails;

    sf::Image _img_cursor_hori;
    sf::Image _img_cursor_verti;
    sf::Image _img_cursor;

    sf::Sprite _spr_cursor;

    std::string _etat_cursor;
    bool _cursor_in_game;

    //------------------------------------------------------------------
    //----------------------------------------------------------------
    //Déclaration des boutons

    //Déclaration des images des boutons

    /// Image de type sf pour le bouton non enfoncé
    sf::Image img_bouton;
    /// Image de type sf pour le bouton enfoncé
    sf::Image img_bouton_enfonce;

    /// Creation d'un pointeur sur un bouton pour l'introduction du jeu
    Bouton *bouton_intro;
    /// Creation d'un pointeur sur un bouton pour les options du jeu
    Bouton *bouton_options;
    /// Creation d'un pointeur sur un bouton pour quitter le jeu
    Bouton *bouton_quitter;
    /// Creation d'un pointeur sur un bouton pour la pause du jeu
    Bouton *bouton_pause;
    /// Creation d'un pointeur sur un bouton pour la sauvegarde du jeu
    Bouton *bouton_sauvegarder;

    Bouton *bouton_perso;

    //Déclaration des sprites des boutons

    /// Sprite correspondant à l'image du bouton non enfoncé
    sf::Sprite _spr_bouton;
    /// Sprite correspondant à l'image du bouton enfoncé
    sf::Sprite _spr_bouton_enfonce;

    //Déclaration des texte des boutons

    /// Chaîne de caractères de type sf utilisé pour le texte du bouton d'introduction
    sf::String _text_intro;
    /// Chaîne de caractères de type sf utilisé pour le texte du bouton d'options
    sf::String _text_options;
    /// Chaîne de caractères de type sf utilisé pour le texte du bouton quitter
    sf::String _text_quitter;
    /// Chaîne de caractères de type sf utilisé pour le texte du bouton pause
    sf::String _text_pause;
    /// Chaîne de caractères de type sf utilisé pour le texte du bouton sauvegarder
    sf::String _text_sauvegarder;

    sf::String _text_perso;
    //-----------------------------------------------------------------
    //------------------------------------------------------------------

    //----------------------------------------------------------
    // Les sprites
    //----------------------------------------------------------

    /// Sprite correspondant à l'image du fond d'écran principal
    sf::Sprite _spr_background;
/// Sprite correspondant à l'image de la balle
    sf::Sprite _spr_ball;
    /// Sprite correspondant à l'image de la bordure
    sf::Sprite _spr_bordure;


    sf::Sprite *_spr_mur_plein;
    sf::Sprite *_spr_mur_construction;

    //----------------------------------------------------------------
    // Les "Clock"
    //----------------------------------------------------------------

    /// Permet de manipuler le temps lors de l'extension des barres
    sf::Clock _clock_temps_barre;
    /// Permet de gérer de temps de jeu du joueur
    sf::Clock _clock_temps;

    //---------------------------------------------------------------
    // Les strings
    //---------------------------------------------------------------

    /// Chaîne de caractères de type sf pour indiquer que le jeu est en pause
    sf::String textPause;
    /// Chaîne de caractères de type sf pour l'écriture de "Niveau :" dans le jeu
    sf::String textNiveau;
    /// Chaîne de caractères de type sf pour l'écriture de "Score : " dans le jeu
    sf::String textScore;
    /// Chaîne de caractères de type sf pour l'écriture de "Vie : " dans le jeu
    sf::String textVie;
    /// Chaîne de caractères de type sf pour l'écriture de "Temps : " dans le jeu
    sf::String textTemps;
    /// Chaîne de caractères de type sf pour l'écriture de "Surface : " dans le jeu
    sf::String textSurface;
    /// Chaîne de caractères de type sf pour indiquer le temps restant en temps réel
    sf::String _txt_time;
    /// Chaîne de caractères de type sf pour indiquer le score en temps réel
    sf::String _txt_score;
/// Chaîne de caractères de type sf pour indiquer le niveau actuel
    sf::String _txt_level;
/// Chaîne de caractères de type sf pour indiquer le nombre de vie(s) en temps réel
    sf::String _txt_life;
/// Chaîne de caractères de type sf pour indiquer la surface recouverte en temps réel
    sf::String _txt_area;
    /// Chaîne de caractères de type sf pour indiquer la surface à recouvrir
    sf::String _txt_area_tot;
    /// Chaîne de caractères de type sf pour indiquer la pause dans le jeu et la toucher à utiliser pour l'activer
    sf::String _txtPause;


    //----------------------------------------------------------------
    // Les entiers et les réels
    //----------------------------------------------------------------

    /// Entier permettant la progression de la barre horizontale droite
    int _tmp_xd;
    /// Entier permettant la progression de la barre horizontale gauche
    int _tmp_xg;
    /// Entier permettant la progression de la barre verticale haut
    int _tmp_yh;
    /// Entier permettant la progression de la barre verticale bas
    int _tmp_yb;
    /// Entier correspondant aux coordonnées de la souris en x lors du clic
    int _coordX;
    /// Entier correspondant aux coordonnées de la souris en y lors du clic
    int _coordY;

    /// Entier permettant de stocker le nombre de cases à l'état "vide" de la matrice compris entre le clic et le bord gauche ou la prochaine case à l'état "plein" sur la gauche
    int _nb_gauche;
    /// Entier permettant de stocker le nombre de cases à l'état "vide" de la matrice compris entre le clic et le bord droit ou la prochaine case à l'état "plein" sur la droite
    int _nb_droit;
    /// Entier permettant de stocker le nombre de cases à l'état "vide" de la matrice compris entre le clic et le bord haut ou la prochaine case à l'état "plein" sur le haut
    int _nb_haut;
    /// Entier permettant de stocker le nombre de cases à l'état "vide" de la matrice compris entre le clic et le bord bas ou la prochaine case à l'état "plein" sur le bas
    int _nb_bas;
    /// Réel de type float utilisé pour la vitesse de l'extension des barres
    float _time_barre;
    /// Réel temporaire de type float permettant la bonne pregression d'une partie de la barre
    float _tmp_temps_barre1;
    /// Réel temporaire de type float permettant la bonne pregression d'une partie de la barre
    float _tmp_temps_barre2;

    int _cursorX;
    int _cursorY;


    //----------------------------------------------------------------
    // Les booléens
    //----------------------------------------------------------------

    /// Booléen permattant de savoir si une barre horizontale vers la droite est en cours
    bool _barreHorizDroit;
/// Booléen permattant de savoir si une barre horizontale vers la gauche est en cours
    bool _barreHorizGauche;
/// Booléen permattant de savoir si une barre verticale vers le bas est en cours
    bool _barreVertiBas;
/// Booléen permattant de savoir si une barre verticale vers le haut est en cours
    bool _barreVertiHaut;
    /// Booléen permettant de savoir si la construction du mur gauche est terminée
    bool _fini_gauche;
    /// Booléen permettant de savoir si la construction du mur droit est terminée
    bool _fini_droit;
    /// Booléen permettant de savoir si la construction du mur bas est terminée
    bool _fini_bas;
    /// Booléen permettant de savoir si la construction du mur haut est terminée
    bool _fini_haut;



    /// Déclaration d'un pointeur sur un GameController
    GameController * _controller;
    /// Action qui instancie le controller
    void setController(Controller * controller);
    /// Déclaration d'une police utilisée pour les chaînes de caractères
    sf::Font _police;

public:
    GameView(int w, int h, sf::RenderWindow *window);
    ~GameView();
    void draw();
    void update(std::string perso);
    void manageEvent_perso(std::string &etat, bool &stop, std::string &perso);



};

#endif
