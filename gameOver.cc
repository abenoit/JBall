#include "gameOver.h"

using namespace sf;

///
/// Action qui permet d'afficher l'écran de game over
/// @param *_window Pointeur sur une fenêtre de rendu
/// @param quit Booléen permettant de quitter la fenêtre de game over
/// @param stop Booléen passé en entrée/sortie permettant de quitter l'application quand le joueur est dans la fenêtre game over
///
void gameOver( sf::RenderWindow *  _window, bool quit, bool &stop)
{
    sf::Image _background_image;
    sf::Sprite _background;
    sf::String _text_game_over,text2;
    sf::Font Police;
    sf::Event event;
    sf::SoundBuffer end_sound;
    sf::Sound sound_end;

    int filtre_text1 = 0, filtre_text2 = 0;

    if (!end_sound.LoadFromFile("sounds/end.wav"))
    {
        std::cerr << "ERROR when loading files" << std::endl;
        sound_end = Sound();
    }
    else
        sound_end = Sound(end_sound);

    if (!_background_image.LoadFromFile("images/Dr.Eggman.png") || !Police.LoadFromFile("fonts/shanghai.ttf"))
    {
        std::cerr << "ERROR when loading files" << std::endl;
        _background = Sprite ();

    }
    else
    {
        _background = Sprite (_background_image);
        _background.Resize(800,600);
    }

    _text_game_over.SetFont(Police);
    _text_game_over.SetText("GAME OVER !");
    _text_game_over.SetPosition(400,150);
    _text_game_over.SetColor(sf::Color(255,255,255,0));
    _text_game_over.SetSize(50);

    text2.SetFont(Police);
    text2.SetText("Appuyez sur espace pour continuer");
    text2.SetPosition(40,550);
    text2.SetColor(sf::Color(255,255,255,0));

    sound_end.Play();

    while (!quit)
    {
        _window->SetFramerateLimit(200);

        _window->Draw(_background);

        if (filtre_text1 < 255)
        {
            filtre_text1 += 1;

            _text_game_over.SetColor(sf::Color(255,255,255, filtre_text1));
        }
        else if (filtre_text2 < 255)
        {
            filtre_text2 += 1;

            text2.SetColor(sf::Color(255,255,255, filtre_text2));
        }

        _window->Draw(_text_game_over);
        _window->Draw(text2);

        _window->Display();

        while (_window->GetEvent(event))
        {

            if ((event.Type == sf::Event::Closed) || ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape)))
            {
                stop = true;
                quit = true;
                sound_end.Stop();
                _window->Close();
            }
            if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Space))
            {
                sound_end.Stop();
                quit = true;
            }
        }
    }
}
