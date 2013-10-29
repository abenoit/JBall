// SegaView.cc
#include "SegaView.h"

using namespace sf;
using namespace std;

///
/// Action qui permet d'afficher nos sponsors :)
/// @param *window Pointeur sur une fenêtre de rendu
/// @param stop Booléen passé en entrée/sortie permettant de quitter l'application lorsque cette fenêtre est active
///
void SegaView(sf::RenderWindow *window, bool &stop)
{

    sf::Clock timer;
    sf::Image img_sega;
    sf::Sprite sprite_sega;
    sf::SoundBuffer Sega_sound;
    sf::Sound Ssound;
    sf::String text_presente;
    sf::Font font;

    float Time;
    bool sound_play = false;
    bool intro = true;

    timer.Reset();

    if (!Sega_sound.LoadFromFile("sounds/sega.wav") || !img_sega.LoadFromFile("images/sega.png") ||  !font.LoadFromFile("fonts/shanghai.ttf"))
    {
        std::cerr << "ERROR when loading files" << std::endl;
        sprite_sega = Sprite();
        Ssound = Sound();
    }
    else
    {
        Ssound = Sound(Sega_sound);
        sprite_sega = Sprite(img_sega);
    }


    text_presente.SetFont(font);
    text_presente.SetText("presente...");
    text_presente.SetPosition(SCREEN_WIDTH/2, 450 );
    text_presente.SetColor(sf::Color(255,0,0));

    while (window->IsOpened() && intro)
    {
        Time = timer.GetElapsedTime();

        sf::Event event;

        while (window->GetEvent(event))
        {
            if ((event.Type == sf::Event::Closed) || ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape)))
            {
                stop = true;
                window->Close();
            }
        }

        if (Time >= 2 && !sound_play)
        {
            sound_play = true;
            Ssound.Play();
        }

        //window->SetBackgroundColor(sf::Color(0, 0, 0));
        window->Clear(sf::Color(0, 0, 0));

        //Zoom progressif à partir de 3 secondes jusqu'à 4 secondes
        if (Time >= 2 && Time <3)
            sprite_sega.SetScale(Time-2, Time-2);

        //Actualisation de la position du sprite
        sprite_sega.SetPosition((SCREEN_WIDTH/2)-(sprite_sega.GetSize().x/2),(SCREEN_HEIGHT/2)-(sprite_sega.GetSize().y/2));

        //On affiche le sprite seulement entre la 3ème et 4ème seconde
        if (Time >= 2 && Time < 4)
            window->Draw(sprite_sega);


        if (Time >= 4 && Time < 5)
        {
            text_presente.Move(0.1,0);
            window->Draw(text_presente);
        }

        window->Display();

        if (Time >= 5)
        {
            intro = false;
        }
    }
}
