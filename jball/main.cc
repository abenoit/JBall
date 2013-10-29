#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameController.h"
#include "GameView.h"
#include "GameModel.h"
#include "IntroView.h"
#include "OptionsController.h"
#include "IntroController.h"
#include "HighScoreController.h"
#include "HighScoreModel.h"
#include "HighScoreView.h"
#include "SegaView.h"
#include <cstdlib>
#include <iostream>
#include <string>
using namespace sf;
using namespace std;

///
/// Fonction qui lance le jeu
/// @param argc Entier qui défini le nombre de paramètre passé dans le terminal
/// @param argv[] Pointeur sur un tableau de caractère qui contient les chaîne de caractère passées dans le terminal
/// @return quitte avec succès
///
int main(int argc, char *argv[])
{
    string argument;
    RenderWindow * screen;
    string etat = "menu_intro";
    string perso;
    bool stop = false;

    if (argc == 2)
        argument = argv[1];

    if (argument == "-f")
        screen = new RenderWindow(sf::VideoMode(800, 600, 32), "Sonic in JBall", sf::Style::Fullscreen);
    else
    {
        screen = new RenderWindow(sf::VideoMode(800, 600, 32), "Sonic in JBall", sf::Style::Resize|sf::Style::Close);
        //sf::Image icone;
        //icone.LoadFromFile("images/sonic_icone.png");
        //screen->SetIcon(icone.GetWidth(), icone.GetHeight(), icone.GetPixelsPtr());
    }
    screen->ShowMouseCursor(false);

    Model *game_model = new GameModel(800,600);

    Vue *intro_view = new IntroView(800, 600, screen);
    Controller *intro_controller = new IntroController(game_model);

    Vue *game_view = new GameView(SCREEN_WIDTH, SCREEN_HEIGHT, screen);
    Controller *game_controller = new GameController(game_model);

    Vue *options_view = new OptionsView(SCREEN_WIDTH, SCREEN_HEIGHT, screen);
    Controller *options_controller = new OptionsController(game_model);

    Model *score_model = new HighScoreModel();
    Vue *score_view = new HighScoreView(SCREEN_WIDTH, SCREEN_HEIGHT, screen);
    Controller *score_controller = new HighScoreController(score_model);

    SegaView(screen, stop);

    while (!stop)
    {
        if (etat == "menu_intro")
        {
            intro_controller->attachView(intro_view);
            intro_controller->run_perso(etat, stop, perso);
        }
        else if (etat == "menu_options")
        {
            options_controller->attachView(options_view);
            options_controller->run_perso(etat, stop, perso);
        }
        else if (etat == "menu_score")
        {
            score_controller->attachView(score_view);
            score_controller->run(etat, stop);
        }
        else if (etat == "jeu")
        {
            game_controller->attachView(game_view);
            game_controller->run_perso(etat, stop, perso);
        }
    }


    delete screen;
    delete game_model;
    delete score_model;
    delete intro_controller;
    delete game_controller;
    delete options_controller;
    delete score_controller;

    return EXIT_SUCCESS;

}
