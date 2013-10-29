// vieMoins.cc
#include "vieMoins.h"

using namespace sf;

///
/// Action qui permet d'afficher une nouvelle fenêtre lorsque le joueur perd une vie; cette action gère aussi les évenements qui y sont liés.
/// @param *_window Pointeur sur une fenête de rendu
/// @param quit Booléen permettant de quitter la fenetre
/// @param stop Booléen permettant de quitter l'application
///
void vieMoins( sf::RenderWindow *_window, bool quit, bool & stop)
{
    sf::Image _background_image;
    sf::Sprite _background;
    sf::String text,text2;
    sf::Font Police;
    sf::Event event;

    int filtre_text1 = 0, filtre_text2 = 0;

    if (!_background_image.LoadFromFile("images/autre.png") || !Police.LoadFromFile("fonts/shanghai.ttf"))
    {
        std::cerr << "ERROR when loading files" << std::endl;
        _background = Sprite ();
    }
    else
    {
        _background = Sprite (_background_image);
        _background.Resize(800,600);
    }

    text.SetFont(Police);
    text.SetText("Une vie en moins !");
    text.SetPosition(100,5);
    text.SetSize(60);
    text.SetColor(sf::Color(255,255,255, filtre_text1));

    text2.SetFont(Police);
    text2.SetText("Appuyez sur espace pour continuer");
    text2.SetPosition(100,550);
    text2.SetColor(sf::Color(255,255,255, filtre_text2));

    while (!quit)
    {
        _window->SetFramerateLimit(200);

        _window->Draw(_background);

        if (filtre_text1 < 255)
        {
            filtre_text1 += 1;

            text.SetColor(sf::Color(255,255,255, filtre_text1));
        }
        else if (filtre_text2 < 255)
        {
            filtre_text2 += 1;

            text2.SetColor(sf::Color(255,255,255, filtre_text2));
        }

        _window->Draw(text);
        _window->Draw(text2);

        _window->Display();

        while (_window->GetEvent(event))
        {

            if ((event.Type == sf::Event::Closed) || ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape)))
            {
                quit=true;
                stop=true;
                _window->Close();
            }
            if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Space))
            {
                quit = true;
            }
        }
    }
}
