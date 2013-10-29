#include "IntroView.h"
#include "IntroController.h"

using namespace sf;
using namespace std;

///
/// Constructeur avec paramètres de IntroView
/// @param w Longueur de l'écran
/// @param h Hauteur de l'écran
/// @param *window Pointeur sur une fenêtre de rendu
///
IntroView::IntroView(int w, int h, sf::RenderWindow *window)
{
    _window = window;

    if (!_img_background.LoadFromFile("images/Sonic_Wallpaper.png")|| !img_bouton.LoadFromFile("images/boutton.png") || !img_bouton_enfonce.LoadFromFile("images/boutton_enfonce.png") || !textFont.LoadFromFile("fonts/shanghai.ttf") || !_img_cursor.LoadFromFile("images/cursor.png") || !intro_sound.LoadFromFile("sounds/intro.wav"))
    {
        std::cerr << "ERROR when loading files" << std::endl;
        _spr_background = Sprite ();
        spr_bouton = Sprite();
        spr_bouton_enfonce = Sprite();
        _spr_cursor = Sprite();
        sound_intro = Sound();
    }

    else
    {
        //Mise en place des sprites à partir des images si elles existent
        _spr_background = Sprite (_img_background);
        _spr_background.Resize(w,h);

        _spr_a = new Sprite();
        _spr_a->Resize(800,600);

        _spr_cursor = Sprite(_img_cursor);

        spr_bouton = Sprite(img_bouton);
        spr_bouton_enfonce = Sprite(img_bouton_enfonce);

        sound_intro = Sound(intro_sound);

        //Initialisation des boutons
        bouton_play = new Bouton(SCREEN_WIDTH/2-200, 80, text_play, "Jouer", spr_bouton, spr_bouton_enfonce, textFont);

        bouton_charger = new Bouton(SCREEN_WIDTH/2+200, 80, text_charger, "Charger", spr_bouton, spr_bouton_enfonce, textFont);

        bouton_options = new Bouton(150, 295, text_options, "Options", spr_bouton, spr_bouton_enfonce, textFont);

        bouton_score = new Bouton(650, 295, text_score, "Scores", spr_bouton, spr_bouton_enfonce, textFont);

        bouton_quitter = new Bouton(400, 540, text_quitter, "Quitter", spr_bouton, spr_bouton_enfonce, textFont);
    }
    status = sound_intro.GetStatus();
}
///
/// Destructeur de IntroView
///
IntroView::~IntroView()
{
    delete _window;
    delete bouton_play;
    delete bouton_charger;
    delete bouton_options;
    delete bouton_score;
    delete bouton_quitter;
}

///
/// Action permettant d'initialiser le controller
/// @param *controller Pointeur sur un Controller
///
void IntroView::setController(Controller * controller)
{
    _controller = dynamic_cast<IntroController *> (controller);

    _filtre = 255;
}

///
/// Action permettant d'afficher à l'écran les differents éléments
///
void IntroView::draw()
{
    _window->SetFramerateLimit(150);
    //Affichage du fond
    _window->Draw(_spr_background);

    //Affichage des boutons
    _window->Draw(*bouton_play);
    _window->Draw(*bouton_charger);
    _window->Draw(*bouton_options);
    _window->Draw(*bouton_score);
    _window->Draw(*bouton_quitter);

    if (_filtre > 0)
    {
        _filtre -= 1;
        _spr_a->SetColor(sf::Color(0,0,0,_filtre));
        _window->Draw(*_spr_a);
    }

    _spr_cursor.SetPosition(_cursorX, _cursorY);
    _window->Draw(_spr_cursor);

    _window->Display();

}

///
/// Action permettant de gérer les évenements
/// @param etat Chaîne de caractères permettant de savoir dans quel view on se place
/// @param stop Booléen permettant de quitter l'application
/// @param perso Chaîne de caractère pour le personnage choisi
///
void IntroView::manageEvent_perso(std::string &etat, bool &stop, std::string &perso)
{
    if (_window->IsOpened())
    {
        sf::Event event;
        const sf::Input& input = _window->GetInput();

        status = sound_intro.GetStatus();

        if (status == sf::Sound::Stopped)
            sound_intro.Play();

        while (_window->GetEvent(event))
        {
            int MouseX =  input.GetMouseX();
            int MouseY =  input.GetMouseY();

            _cursorX = input.GetMouseX();
            _cursorY = input.GetMouseY();

            //Si on appuie sur echap ou sur la croix, on ferme le programme
            if ((event.Type == sf::Event::Closed) || ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape)))
            {
                stop = true;
                sound_intro.Stop();

                _window->Close();
                _controller->detachView(this);
            }

            if (bouton_play->estDedans( MouseX, MouseY ))
            {
                bouton_play->changeColor(sf::Color(100,0,255));
            }
            else if (bouton_charger->estDedans( MouseX, MouseY ))
            {
                bouton_charger->changeColor(sf::Color(100,0,255));
            }
            else  if (bouton_options->estDedans( MouseX, MouseY ))
            {
                bouton_options->changeColor(sf::Color(100,0,255));
            }
            else  if (bouton_score->estDedans( MouseX, MouseY ))
            {
                bouton_score->changeColor(sf::Color(100,0,255));
            }
            else  if (bouton_quitter->estDedans( MouseX, MouseY ))
            {
                bouton_quitter->changeColor(sf::Color(100,0,255));
            }
            else
            {
                bouton_play->changeColor(sf::Color(255,255,255));
                bouton_charger->changeColor(sf::Color(255,255,255));
                bouton_options->changeColor(sf::Color(255,255,255));
                bouton_score->changeColor(sf::Color(255,255,255));
                bouton_quitter->changeColor(sf::Color(255,255,255));
            }

            //Si on clique
            if (event.Type == sf::Event::MouseButtonPressed && event.MouseButton.Button == sf::Mouse::Left)
            {
                MouseX = input.GetMouseX();
                MouseY = input.GetMouseY();

                if (bouton_play->estDedans( MouseX, MouseY ))
                {
                    bouton_play->setEnfonce(true);
                }
                else if (bouton_charger->estDedans( MouseX, MouseY ))
                {
                    bouton_charger->setEnfonce(true);
                }
                else  if (bouton_options->estDedans( MouseX, MouseY ))
                {
                    bouton_options->setEnfonce(true);
                }
                else  if (bouton_score->estDedans( MouseX, MouseY ))
                {
                    bouton_score->setEnfonce(true);
                }
                else  if (bouton_quitter->estDedans( MouseX, MouseY ))
                {
                    bouton_quitter->setEnfonce(true);
                }
            }

            //Si on relache le clic
            else if (event.Type == sf::Event::MouseButtonReleased && event.MouseButton.Button == sf::Mouse::Left)
            {
                MouseX = input.GetMouseX();
                MouseY = input.GetMouseY();

                if (bouton_play->estDedans( MouseX, MouseY ) && bouton_play->getEnfonce())
                {
                    bouton_play->setEnfonce(false);

                    sound_intro.Stop();

                    if (perso == "")
                        menuChoix(_window,stop, perso);

                    etat = "jeu";
                    _controller->detachView(this);
                }
                else if (bouton_charger->estDedans( MouseX, MouseY ) && bouton_charger->getEnfonce())
                {
                    bouton_charger->setEnfonce(false);

                    int tmp_score, tmp_vie, tmp_niveau, tmp_temps, tmp_vitBall, tmp_surface;
                    if (!chargement(tmp_score, tmp_vie, tmp_niveau, tmp_temps, tmp_vitBall, tmp_surface, perso))
                        cerr << "ERROR when loading files" << endl;
                    else
                    {
                        cout << "Votre partie a bien été chargée" << endl;

                        _controller->setScore(tmp_score);
                        _controller->setVie(tmp_vie);
                        _controller->setNiveau(tmp_niveau);
                        _controller->setNbBall(tmp_niveau);
                        _controller->setTempsParNiveau(tmp_temps);
                        _controller->setSurfaceARecouvrir(tmp_surface);
                        _controller->setVitesseBall(tmp_vitBall);

                        sound_intro.Stop();
                        etat = "jeu";
                        _controller->detachView(this);
                    }
                }
                else  if (bouton_options->estDedans( MouseX, MouseY ) && bouton_options->getEnfonce())
                {
                    bouton_options->setEnfonce(false);

                    sound_intro.Stop();
                    etat = "menu_options";
                    _controller->detachView(this);
                }
                else  if (bouton_score->estDedans( MouseX, MouseY ) && bouton_score->getEnfonce())
                {
                    bouton_score->setEnfonce(false);

                    sound_intro.Stop();
                    etat = "menu_score";
                    _controller->detachView(this);
                }
                else  if (bouton_quitter->estDedans( MouseX, MouseY ) && bouton_quitter->getEnfonce())
                {
                    bouton_quitter->setEnfonce(false);

                    sound_intro.Stop();
                    stop = true;
                    _window->Close();
                    _controller->detachView(this);
                }
                else
                {
                    bouton_play->setEnfonce(false);
                    bouton_charger->setEnfonce(false);
                    bouton_options->setEnfonce(false);
                    bouton_score->setEnfonce(false);
                    bouton_quitter->setEnfonce(false);
                }
            }
        }
    }
}
