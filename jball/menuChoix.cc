//menuChoix.cc

#include "menuChoix.h"

using namespace std;
using namespace sf;

///
/// Action qui affiche une fenêtre où l'on peut sélectionner/changer de personnage
/// @param *window Pointeur de fenêtre de rendu
/// @param stop Booléen passé en entrée/sortie permettant de quitter l'application quand le joueur est dans la fenêtre game over
/// @param perso Chaîne de caractère qui défini le personnage
///
void menuChoix(sf::RenderWindow *window,bool &stop, string &perso)
{
    sf::Image img_sonic;
    sf::Image img_amy;
    sf::Image img_tails;
    sf::Image img_shadow;
    sf::Image img_knuckles;
    sf::Image img_cursor;

    sf::Sprite spr_sonic;
    sf::Sprite spr_amy;
    sf::Sprite spr_tails;
    sf::Sprite spr_shadow;
    sf::Sprite spr_knuckles;
    sf::Sprite spr_cursor;

    int cursorX;
    int cursorY;

    Bouton * bouton_sonic;
    Bouton * bouton_amy;
    Bouton * bouton_tails;
    Bouton * bouton_shadow;
    Bouton * bouton_knuckles;

    sf::Image img_bouton_enfonce;
    sf::Image img_bouton_non_enfonce;

    sf::Sprite spr_bouton_enfonce;
    sf::Sprite spr_bouton_non_enfonce;

    sf::String text_sonic;
    sf::String text_amy;
    sf::String text_knuckles;
    sf::String text_tails;
    sf::String text_shadow;

    sf::Font police;
    sf::String text_choix;

    bool quit = false;
    if (!img_sonic.LoadFromFile("images/sonic_portrait.png") || !img_amy.LoadFromFile("images/amy_portrait.png") || !img_shadow.LoadFromFile("images/shadow_portrait.png") || !img_tails.LoadFromFile("images/tails_portrait.png") || !img_knuckles.LoadFromFile("images/knuckles_portrait.png") || !img_bouton_enfonce.LoadFromFile("images/boutton_enfonce.png") || !img_bouton_non_enfonce.LoadFromFile("images/boutton.png") || !police.LoadFromFile("fonts/shanghai.ttf") || !img_cursor.LoadFromFile("images/cursor.png"))
    {
        std::cerr << "ERROR when loading files" << std::endl;

        spr_bouton_enfonce = Sprite();
        spr_bouton_non_enfonce = Sprite();
        spr_amy = Sprite ();
        spr_sonic = Sprite ();
        spr_knuckles = Sprite ();
        spr_tails = Sprite ();
        spr_shadow = Sprite ();
        spr_cursor = Sprite();
    }
    else
    {
        spr_bouton_enfonce = Sprite(img_bouton_enfonce);
        spr_bouton_non_enfonce = Sprite(img_bouton_non_enfonce);
        spr_amy = Sprite (img_amy);
        spr_sonic = Sprite (img_sonic);
        spr_knuckles = Sprite (img_knuckles);
        spr_tails = Sprite (img_tails);
        spr_shadow = Sprite (img_shadow);
        spr_cursor = Sprite(img_cursor);

        spr_sonic.Resize(150 ,170);
        spr_sonic.SetPosition(50,90);
        spr_amy.Resize(150 ,170);
        spr_amy.SetPosition(200,350);
        spr_knuckles.Resize(150 ,170);
        spr_knuckles.SetPosition(450,350);
        spr_tails.Resize(150 ,170);
        spr_tails.SetPosition(325,90);
        spr_shadow.Resize(150 ,170);
        spr_shadow.SetPosition(600,90);


        bouton_sonic = new Bouton(125, 290, text_sonic, "Sonic", spr_bouton_non_enfonce, spr_bouton_enfonce, police);
        bouton_amy = new Bouton(275, 550, text_amy, "Amy", spr_bouton_non_enfonce, spr_bouton_enfonce, police);
        bouton_knuckles = new Bouton(525,550 , text_knuckles, "Knuckles", spr_bouton_non_enfonce, spr_bouton_enfonce, police);
        bouton_tails = new Bouton(400, 290, text_tails, "Tails", spr_bouton_non_enfonce, spr_bouton_enfonce, police);
        bouton_shadow = new Bouton(675, 290, text_shadow, "Shadow", spr_bouton_non_enfonce, spr_bouton_enfonce, police);

        text_choix.SetFont(police);
        text_choix.SetText(" Choisissez votre personnage : ");
        text_choix.SetPosition( SCREEN_WIDTH/2 - text_choix.GetRect().GetWidth()/2, 25);
        text_choix.SetColor(sf::Color(255,255,255));

    }


    while (window->IsOpened() && !quit)
    {

        sf::Event event;
        const sf::Input& input = window->GetInput();

        while (window->GetEvent(event))
        {
            int MouseX =  input.GetMouseX();
            int MouseY =  input.GetMouseY();

            cursorX =  input.GetMouseX();
            cursorY =  input.GetMouseY();

            if ((event.Type == sf::Event::Closed) || ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape)))
            {
                stop = true;
                window->Close();
            }

            if (bouton_sonic->estDedans( MouseX, MouseY ))
            {
                bouton_sonic->changeColor(sf::Color(51,102,255));
            }
            else if (bouton_amy->estDedans( MouseX, MouseY ))
            {
                bouton_amy->changeColor(sf::Color(255,51,153));
            }
            else if (bouton_knuckles->estDedans( MouseX, MouseY ))
            {
                bouton_knuckles->changeColor(sf::Color(153,0,102));
            }
            else if (bouton_tails->estDedans( MouseX, MouseY ))
            {
                bouton_tails->changeColor(sf::Color(255,102,0));
            }
            else if (bouton_shadow->estDedans( MouseX, MouseY ))
            {
                bouton_shadow->changeColor(sf::Color(0,0,0));
            }
            else
            {
                bouton_sonic->changeColor(sf::Color(255,255,255));
                bouton_amy->changeColor(sf::Color(255,255,255));
                bouton_shadow->changeColor(sf::Color(255,255,255));
                bouton_knuckles->changeColor(sf::Color(255,255,255));
                bouton_tails->changeColor(sf::Color(255,255,255));
            }

            if (event.Type == sf::Event::MouseButtonPressed && event.MouseButton.Button == sf::Mouse::Left)
            {
                MouseX = input.GetMouseX();
                MouseY = input.GetMouseY();

                if (bouton_sonic->estDedans( MouseX, MouseY ))
                {
                    bouton_sonic->setEnfonce(true);
                }
                else if (bouton_amy->estDedans( MouseX, MouseY ))
                {
                    bouton_amy->setEnfonce(true);
                }
                else if (bouton_knuckles->estDedans( MouseX, MouseY ))
                {
                    bouton_knuckles->setEnfonce(true);
                }
                else if (bouton_tails->estDedans( MouseX, MouseY ))
                {
                    bouton_tails->setEnfonce(true);
                }
                else if (bouton_shadow->estDedans( MouseX, MouseY ))
                {
                    bouton_shadow->setEnfonce(true);
                }
            }
            else if (event.Type == sf::Event::MouseButtonReleased && event.MouseButton.Button == sf::Mouse::Left)
            {
                MouseX = input.GetMouseX();
                MouseY = input.GetMouseY();

                if (bouton_sonic->estDedans( MouseX, MouseY ) && bouton_sonic->getEnfonce())
                {
                    perso = "sonic";
                    quit = true;
                    bouton_sonic->setEnfonce(false);

                }
                else if (bouton_shadow->estDedans( MouseX, MouseY ) && bouton_shadow->getEnfonce())
                {
                    perso = "shadow";
                    quit = true;
                    bouton_shadow->setEnfonce(false);
                }
                else if (bouton_amy->estDedans( MouseX, MouseY ) && bouton_amy->getEnfonce())
                {
                    perso = "amy";
                    quit = true;
                    bouton_amy->setEnfonce(false);
                }
                else if (bouton_tails->estDedans( MouseX, MouseY ) && bouton_tails->getEnfonce())
                {
                    perso = "tails";
                    quit = true;
                    bouton_tails->setEnfonce(false);
                }
                else if (bouton_knuckles->estDedans( MouseX, MouseY ) && bouton_knuckles->getEnfonce())
                {
                    perso = "knuckles";
                    quit = true;
                    bouton_knuckles->setEnfonce(false);
                }
                else
                {
                    bouton_sonic->setEnfonce(false);
                    bouton_amy->setEnfonce(false);
                    bouton_knuckles->setEnfonce(false);
                    bouton_shadow->setEnfonce(false);
                    bouton_tails->setEnfonce(false);
                }
            }

        }

        window->Clear(sf::Color(0,0,0));
        //window->SetBackgroundColor(sf::Color(0,0,0));
        window->Draw(spr_sonic);
        window->Draw(spr_amy);
        window->Draw(spr_shadow);
        window->Draw(spr_tails);
        window->Draw(spr_knuckles);
        window->Draw(text_choix);
        window->Draw(*bouton_sonic);
        window->Draw(*bouton_amy);
        window->Draw(*bouton_shadow);
        window->Draw(*bouton_tails);
        window->Draw(*bouton_knuckles);

        spr_cursor.SetPosition(cursorX, cursorY);
        window->Draw(spr_cursor);

        window->Display();


    }

}
