// NiveauSuivant.cc

#include "niveauSuivant.h"

using namespace sf;

///
/// Action qui permet d'afficher une fenêtre de niveau suivant et de gérer les évenements qui y sont liés
/// @param *_window Pointeur sur une fenête de rendu
/// @param quit Booléen permettant de quitter la fenetre
/// @param stop Booléen permettant de quitter l'application
///
void niveauSuivant( sf::RenderWindow *  _window, bool quit, bool &stop)
{
    sf::Image _background_image;
    sf::Sprite _background;
    sf::String text,text2;
    sf::Font Police;
    sf::Event event;
    sf::SoundBuffer next_sound;
    sf::Sound sound_next;

    int filtre_text1 = 0, filtre_text2 = 0;

    if (!next_sound.LoadFromFile("sounds/next.wav"))
    {
        std::cerr << "ERROR when loading files" << std::endl;
        sound_next = Sound();
    }
    else
        sound_next = Sound(next_sound);

    sound_next.Play();

    if (!_background_image.LoadFromFile("images/niveau_suivant.jpg") || !Police.LoadFromFile("fonts/shanghai.ttf"))
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
    text.SetText("Niveau Suivant !");
    text.SetPosition(100,80);
    text.SetSize(60);
    text.SetColor(sf::Color(0,0,255,0));

    text2.SetFont(Police);
    text2.SetText("Appuyez sur espace pour continuer");
    text2.SetPosition(30,550);
    text2.SetColor(sf::Color(0,0,255,0));

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

        while (_window->GetEvent(event) && !quit)
        {

            if ((event.Type == sf::Event::Closed) || ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape)))
            {
                stop = true;
                quit = true;
                sound_next.Stop();
                _window->Close();

            }
            if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Space))
            {
                sound_next.Stop();
                quit = true;
            }
        }
    }
}
