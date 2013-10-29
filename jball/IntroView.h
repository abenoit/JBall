#ifndef _INTROVIEW_
#define _INTROVIEW_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameModel.h"
#include <string>
#include <iostream>
#include <sstream>
#include "Bouton.h"
#include "Slider.h"
#include "OptionsView.h"
#include "util.h"
#include "Vue.h"
#include "menuChoix.h"

class IntroController;

///
/// @class IntroView
///
class IntroView : public Vue
{
    friend class IntroController;
    friend class GameController;

private:
    /// Déclaration d'une fenêtre de rendu
    sf::RenderWindow * _window;
    /// Image correspondant au fond d'écran de l'intro
    sf::Image _img_background;
    /// Sprite correspondant à l'image du fond d'écran
    sf::Sprite _spr_background;

    sf::Image _img_cursor;

    sf::Sprite _spr_cursor;

    int _filtre;
    sf::Sprite *_spr_a;

    int _cursorX;
    int _cursorY;

    /// Déclaration d'un controller de type intro
    IntroController * _controller;
    /// Initialisation du controller
    void setController(Controller * controller);

    /// Déclaration d'une police d'écriture
    sf::Font textFont;

    /// Déclaration d'une images pour le bouton non enfoncé
    sf::Image img_bouton;
    /// Déclaration d'une images pour le bouton enfoncé
    sf::Image img_bouton_enfonce;
    /// Déclaration du sprite correspondant à l'image du bouton non enfoncé
    sf::Sprite spr_bouton;
    /// Déclaration du sprite correspondant à l'image du bouton enfoncé
    sf::Sprite spr_bouton_enfonce;
    /// Déclaration d'un bouton pour jouer
    Bouton *bouton_play;
    /// Déclaration d'un bouton pour atteindre les options
    Bouton *bouton_options;
    /// Déclaration d'un bouton pour quitter
    Bouton *bouton_quitter;
    /// Déclaration d'un bouton pour afficher les scores
    Bouton *bouton_score;
    /// Déclaration d'un bouton pour charger une partie
    Bouton *bouton_charger;

    /// Déclaration du texte associé au bouton play
    sf::String text_play;
    /// Déclaration du texte associé au bouton options
    sf::String text_options;
    /// Déclaration du texte associé au bouton quitter
    sf::String text_quitter;
    /// Déclaration du texte associé au bouton scores
    sf::String text_score;
    /// Déclaration du texte associé au bouton charger
    sf::String text_charger;

    /// Déclaration du son d'introduction
    sf::SoundBuffer intro_sound;
    /// Le son qui sera joué
    sf::Sound sound_intro;

    /// Défini le status du son (playing, paused, stopped)
    sf::Sound::Status status;

public:
    IntroView(int w, int h, sf::RenderWindow *window);
    ~IntroView();
    void draw();
    void manageEvent_perso(std::string &etat, bool &stop, std::string &perso);



};

#endif
