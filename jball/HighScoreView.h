#ifndef _HIGHSCORE_VIEW_
#define _HIGHSCORE_VIEW_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "HighScoreModel.h"
#include <string>
#include <iostream>
#include <sstream>
#include "Bouton.h"
#include "HighScoreView.h"
#include "Vue.h"
class HighScoreController;

///
/// @class HighScoreView
///
class HighScoreView : public Vue
{
    friend class HighScoreController;

private:
    /// Déclaration d'un pointeur sur une fenpetre de rendu
    sf::RenderWindow *_window;

    /// Image pour le fond d'écran
    sf::Image _img_background;
    /// Image pour le bouton non enfoncé
    sf::Image _img_bouton;
    /// Image pour le bouton enfoncé
    sf::Image _img_bouton_enfonce;

    sf::Image _img_cursor;

    /// Sprite pour l'image du fond d'écran
    sf::Sprite _spr_background;
    /// Sprite pour l'image de la bordure
    sf::Sprite _spr_bordure;
    /// Sprite pour l'image du bouton non enfoncé
    sf::Sprite _spr_bouton;
    /// Sprite pour l'image du bouton enfoncé
    sf::Sprite _spr_bouton_enfonce;
    /// Sprite pour le curseur de la souris
    sf::Sprite _spr_cursor;

    sf::Sprite *_spr_assombri;

    int _cursorX;
    int _cursorY;

    /// Vecteur de chaîne de caractères pour récupérer les noms
    std::vector<sf::String> _name;
    /// Vecteur de chaîne de caractères pour récupérer les scores
    std::vector<sf::String> _score;
    /// Vecteur de chaîne de caractères pour récupérer le niveau
    std::vector<sf::String> _niveau;

    /// Chaine de caractère pour le bouton retour
    sf::String _text_retour;
    /// Déclaration d'une police d'écriture
    sf::Font _police;

    /// Déclaration d'un bouton pour retourner à l'intro
    Bouton *bouton_retour;
    /// Déclaration d'un controller lié à ce view
    HighScoreController * _controller;
    /// Action permettant d'attacher le controller à ce view
    void setController(Controller * controller);


public:
    HighScoreView(int w, int h, sf::RenderWindow *window);
    ~HighScoreView();
    void draw();
    void manageEvent(std::string &etat, bool &stop);

};

#endif

