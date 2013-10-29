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
    /// D�claration d'une fen�tre de rendu
    sf::RenderWindow * _window;
    /// Image correspondant au fond d'�cran de l'intro
    sf::Image _img_background;
    /// Sprite correspondant � l'image du fond d'�cran
    sf::Sprite _spr_background;

    sf::Image _img_cursor;

    sf::Sprite _spr_cursor;

    int _filtre;
    sf::Sprite *_spr_a;

    int _cursorX;
    int _cursorY;

    /// D�claration d'un controller de type intro
    IntroController * _controller;
    /// Initialisation du controller
    void setController(Controller * controller);

    /// D�claration d'une police d'�criture
    sf::Font textFont;

    /// D�claration d'une images pour le bouton non enfonc�
    sf::Image img_bouton;
    /// D�claration d'une images pour le bouton enfonc�
    sf::Image img_bouton_enfonce;
    /// D�claration du sprite correspondant � l'image du bouton non enfonc�
    sf::Sprite spr_bouton;
    /// D�claration du sprite correspondant � l'image du bouton enfonc�
    sf::Sprite spr_bouton_enfonce;
    /// D�claration d'un bouton pour jouer
    Bouton *bouton_play;
    /// D�claration d'un bouton pour atteindre les options
    Bouton *bouton_options;
    /// D�claration d'un bouton pour quitter
    Bouton *bouton_quitter;
    /// D�claration d'un bouton pour afficher les scores
    Bouton *bouton_score;
    /// D�claration d'un bouton pour charger une partie
    Bouton *bouton_charger;

    /// D�claration du texte associ� au bouton play
    sf::String text_play;
    /// D�claration du texte associ� au bouton options
    sf::String text_options;
    /// D�claration du texte associ� au bouton quitter
    sf::String text_quitter;
    /// D�claration du texte associ� au bouton scores
    sf::String text_score;
    /// D�claration du texte associ� au bouton charger
    sf::String text_charger;

    /// D�claration du son d'introduction
    sf::SoundBuffer intro_sound;
    /// Le son qui sera jou�
    sf::Sound sound_intro;

    /// D�fini le status du son (playing, paused, stopped)
    sf::Sound::Status status;

public:
    IntroView(int w, int h, sf::RenderWindow *window);
    ~IntroView();
    void draw();
    void manageEvent_perso(std::string &etat, bool &stop, std::string &perso);



};

#endif
