#ifndef OPTIONSVIEW_H
#define OPTIONSVIEW_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bouton.h"
#include "OptionsController.h"
#include "GameController.h"
#include "Slider.h"
#include "Vue.h"
#include "menuChoix.h"
#include <string>
#include <iostream>
#include <sstream>

class OptionsController;

///
/// @class OptionsView
///
class OptionsView : public Vue
{
    friend class OptionsController;

private :

    /// Fenêtre de rendu
    sf::RenderWindow * _window;
    /// Déclaration d'une police d'écriture
    sf::Font police;

    /// Déclaration d'un pointeur sur un OptionsController
    OptionsController * _controller;
    /// Fonction pour initialiser le pointeur precedement déclaré
    void setController(Controller * controller);

    /// Image pour le fond d'écran des options
    sf::Image _background_image;
    /// Image correspondant au bouton (non enfoncé)
    sf::Image _img_bouton;
    /// Image correspondant au bouton (enfoncé)
    sf::Image _img_bouton_enfonce;

    sf::Image _img_cursor;

    /// Sprite correspondant à l'image du fond d'écran
    sf::Sprite _background;
    /// Sprite correspondant à l'image du bouton non enfoncé
    sf::Sprite sprite_bouton;
    /// Sprite correspondant à l'image du bouton enfoncé
    sf::Sprite sprite_bouton_enfonce;

    sf::Sprite _spr_cursor;

    int _cursorX;
    int _cursorY;

    /// Chaîne de caractères de type sf à placer sur le bouton intro
    sf::String text_intro;
    /// Chaîne de caractères de type sf à placer sur le bouton play
    sf::String text_play;

    /// Déclaration d'evenements
    sf::Event event;

    //-----------------------------------------------------------
    // SLIDERS
    //
    /// Déclaration d'un pointeur sur un slider pour le nombre de balle(s)
    Slider *slider_nb_balle;
    /// Déclaration d'un pointeur sur un slider pour la vitesse des balles
    Slider *slider_vitesse_balle;
    /// Déclaration d'un pointeur sur un slider pour le nombre de vies
    Slider *slider_nb_vie;
    /// Déclaration d'un pointeur sur un slider pour la surface à recouvrir
    Slider *slider_surface;
    /// Déclaration d'un pointeur sur un slider pour le temps maximum
    Slider *slider_temps;
    /// Déclaration d'un pointeur sur un slider pour la vitesse des barres
    Slider *slider_vitesse_barre;


    /// Déclaration d'une image pour la barre
    sf::Image img_barre;
    /// Déclaration d'une image pour la flèche gauche
    sf::Image img_fleche_gauche;
    /// Déclaration d'une image pour la flèche droite
    sf::Image img_fleche_droite;
    /// Déclaration d'une image pour le repère du slider
    sf::Image img_repere;

    /// Déclaration du sprite correspondant à l'image du repère
    sf::Sprite sprite_repere;
    /// Déclaration du sprite correspondant à l'image de la barre
    sf::Sprite sprite_barre;
    /// Déclaration du sprite correspondant à l'image de la flèche gauche
    sf::Sprite sprite_fleche_gauche;
    /// Déclaration du sprite correspondant à l'image de la flèche droite
    sf::Sprite sprite_fleche_droite;

    /// Déclaration d'une chaîne de caractères pour le nombre de balle(s)
    sf::String text_nb_balle;
    /// Déclaration d'une chaîne de caractères pour la vitesse des balles
    sf::String text_vitesse_balle;
    /// Déclaration d'une chaîne de caractères pour le nombre de vie(s)
    sf::String text_nb_vie;
    /// Déclaration d'une chaîne de caractères pour la surface à recouvrir
    sf::String text_surface;
    /// Déclaration d'une chaîne de caractères pour le temps maximum d'une partie
    sf::String text_temps;
    /// Déclaration d'une chaîne de caractères pour la vitesse des barres
    sf::String text_vitesse_barre;

    /// String : Variable contenant et indiquant le nombre de balle(s) choisi
    sf::String _nb_balle;
    /// String : Variable contenant et indiquant la vitesse des balles choisie
    sf::String _vitesse_balle;
    /// String : Variable contenant et indiquant le nombre de vie(s) choisi
    sf::String _nb_vie;
    /// String : Variable contenant et indiquant la surface minimum à recouvrir choisie
    sf::String _surface;
    /// String : Variable contenant et indiquant le temps maximum d'une partie choisi
    sf::String _temps;
    /// String : Variable contenant et indiquant la vitesse des barres choisie
    sf::String _vitesse_barre;

    /// Déclaration d'un bouton permettant de retourner à l'intro du jeu
    Bouton *bouton_intro;
    /// Déclaration d'un bouton permettant de jouer avecles paramètres choisis
    Bouton *bouton_play;

    int MouseX , MouseY;

public :

    OptionsView(int w, int h, sf::RenderWindow *window);
    ~OptionsView();
    void draw();
    void manageEvent_perso(std::string &etat, bool &stop, std::string &perso);
};

#endif
