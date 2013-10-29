#include "OptionsView.h"

using namespace sf;
using namespace std;

///
/// Constructeur avec paramètres de OptionsView
/// @param w Longueur de la fenêtre
/// @param h Hauteur de la fenêtre
/// @param *window Pointeur sur une fenêtre de rendu
///
OptionsView::OptionsView(int w, int h, sf::RenderWindow * window)
{
    _window = window;

    if (!_background_image.LoadFromFile("images/options.png") || !_img_bouton.LoadFromFile("images/boutton.png") || !_img_bouton_enfonce.LoadFromFile("images/boutton_enfonce.png") || !img_barre.LoadFromFile("images/barre.png") || !img_fleche_gauche.LoadFromFile("images/fleche_gauche.png") || !img_fleche_droite.LoadFromFile("images/fleche_droite.png") || !img_repere.LoadFromFile("images/repere.png") || !police.LoadFromFile("fonts/shanghai.ttf") || !_img_cursor.LoadFromFile("images/cursor.png"))
    {
        std::cerr << "ERROR when loading files" << std::endl;
        _background = Sprite ();
        sprite_bouton = Sprite();
        sprite_bouton_enfonce = Sprite();
        sprite_repere = Sprite ();
        sprite_barre = Sprite ();
        sprite_fleche_gauche = Sprite ();
        sprite_fleche_droite = Sprite ();
        _spr_cursor = Sprite();
    }
    else
    {
        _background = Sprite (_background_image);
        _background.Resize(800,600);

        sprite_bouton = Sprite(_img_bouton);
        sprite_bouton_enfonce = Sprite(_img_bouton_enfonce);

        sprite_repere = Sprite (img_repere);
        sprite_barre = Sprite (img_barre);
        sprite_fleche_gauche = Sprite (img_fleche_gauche);
        sprite_fleche_droite = Sprite (img_fleche_droite);

        _spr_cursor = Sprite(_img_cursor);
    }

    bouton_intro = new Bouton(800/2-200,500,text_intro, "Accueil", sprite_bouton, sprite_bouton_enfonce, police);

    bouton_play = new Bouton(800/2+200,500,text_play, "Jouer", sprite_bouton, sprite_bouton_enfonce, police);

    //Slider nombre de balle
    slider_nb_balle = new Slider(200,50,1,30,1,sprite_barre, sprite_repere, sprite_fleche_gauche, sprite_fleche_droite, text_nb_balle, "Nombre de balle(s) :", _nb_balle, police);

    //Slider vitesse des balle
    slider_vitesse_balle = new Slider(200, 120,1,5,1,sprite_barre, sprite_repere, sprite_fleche_gauche, sprite_fleche_droite, text_vitesse_balle, "Vitesse balle :", _vitesse_balle, police);

    //Slider nombre de vie
    slider_nb_vie = new Slider(200, 190,1,30,1, sprite_barre, sprite_repere, sprite_fleche_gauche, sprite_fleche_droite, text_nb_vie, "Nombre de vie(s) :", _nb_vie, police);

    //Slider surface a recouvrir
    slider_surface = new Slider(200, 260,50,90,5, sprite_barre, sprite_repere, sprite_fleche_gauche, sprite_fleche_droite, text_surface, "Surface :", _surface, police);

    //Slider temps pour le niveau
    slider_temps = new Slider(200, 330,10,60,5, sprite_barre, sprite_repere, sprite_fleche_gauche, sprite_fleche_droite, text_temps, "Temps :", _temps, police);

    //Slider vitesse des barres
    slider_vitesse_barre = new Slider(200, 400,4,12,2,sprite_barre, sprite_repere, sprite_fleche_gauche, sprite_fleche_droite, text_vitesse_barre, "Vitesse barre :", _vitesse_barre, police);
}

///
/// Destructeur de OptionView
///
OptionsView::~OptionsView()
{}

///
/// Action permettant d'instancier le controller à OptionsView
/// @param *controller Pointeur sur un Controller
///
void OptionsView::setController(Controller * controller)
{
    _controller = dynamic_cast<OptionsController *> (controller);


    slider_nb_balle->setValLocal(_controller->getNbBall());
    slider_nb_balle->actualiseRepere();

    slider_vitesse_balle->setValLocal(_controller->getVitBall());
    slider_vitesse_balle->actualiseRepere();

    slider_nb_vie->setValLocal(_controller->getVie());
    slider_nb_vie->actualiseRepere();

    slider_surface->setValLocal(_controller->getSurfaceARecouvrir());
    slider_surface->actualiseRepere();

    slider_temps->setValLocal(_controller->getTempsParNiveau());
    slider_temps->actualiseRepere();

    slider_vitesse_barre->setValLocal(ceil(_controller->getVitesseBarre()*100));
    slider_vitesse_barre->actualiseRepere();
}

///
/// Action qui permet d'afficher les différents composant de l'option
///
void OptionsView::draw()
{
    _window->Draw(_background);

    //Affichage des boutons
    _window->Draw(*bouton_intro);
    _window->Draw(*bouton_play);

    //Affichage des sliders
    _window->Draw(*slider_nb_balle);
    _window->Draw(*slider_vitesse_balle);
    _window->Draw(*slider_nb_vie);
    _window->Draw(*slider_surface);
    _window->Draw(*slider_temps);
    _window->Draw(*slider_vitesse_barre);

    _spr_cursor.SetPosition(_cursorX, _cursorY);
    _window->Draw(_spr_cursor);

    _window->Display();

}

///
/// Action permettant de gérer les évenements dans les options
/// @param etat Chaîne de caractère permettant de savoir dans quel view on se place
/// @param stop Booléen permettant de quitter l'écran d'options
/// @param perso Chaîne de caractère pour le personnage choisi
///
void OptionsView::manageEvent_perso(std::string &etat, bool &stop, std::string &perso)
{
    if (_window->IsOpened())
    {
        sf::Event event;
        const sf::Input& input = _window->GetInput();

        MouseX = input.GetMouseX();
        MouseY = input.GetMouseY();

        _cursorX = input.GetMouseX();
        _cursorY = input.GetMouseY();

        while (_window->GetEvent(event))
        {
            if ((event.Type == sf::Event::Closed) || ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape)))
            {
                stop = true;
                _window->Close();
                _controller->detachView(this);
            }

            if (bouton_intro->estDedans( MouseX, MouseY ))
            {
                bouton_intro->changeColor(sf::Color(100,0,255));
            }
            else if (bouton_play->estDedans( MouseX, MouseY ))
            {
                bouton_play->changeColor(sf::Color(100,0,255));
            }
            else
            {
                bouton_intro->changeColor(sf::Color(255,255,255));
                bouton_play->changeColor(sf::Color(255,255,255));
            }

            if (event.Type == sf::Event::MouseButtonPressed && event.MouseButton.Button == sf::Mouse::Left)
            {
                MouseX = input.GetMouseX();
                MouseY = input.GetMouseY();

                if (slider_nb_balle->estDedansBarre(MouseX, MouseY))
                    slider_nb_balle->setEnfonce(true);
                else if (slider_vitesse_balle->estDedansBarre(MouseX, MouseY))
                    slider_vitesse_balle->setEnfonce(true);
                else if (slider_nb_vie->estDedansBarre(MouseX, MouseY))
                    slider_nb_vie->setEnfonce(true);
                else if (slider_surface->estDedansBarre(MouseX, MouseY))
                    slider_surface->setEnfonce(true);
                else if (slider_temps->estDedansBarre(MouseX, MouseY))
                    slider_temps->setEnfonce(true);
                else if (slider_vitesse_barre->estDedansBarre(MouseX, MouseY))
                    slider_vitesse_barre->setEnfonce(true);


                if (bouton_intro->estDedans( MouseX, MouseY ))
                {
                    bouton_intro->setEnfonce(true);
                }
                else if (bouton_play->estDedans( MouseX, MouseY ))
                {
                    bouton_play->setEnfonce(true);
                }
                else if (slider_nb_balle->estDedansGauche( MouseX, MouseY) && slider_nb_balle->getValLocal() != slider_nb_balle->getValMin())
                {
                    slider_nb_balle->setMoins();
                    slider_nb_balle->actualiseRepere();
                    _controller->suppBall();
                }
                else if (slider_vitesse_balle->estDedansGauche(MouseX, MouseY) && slider_vitesse_balle->getValLocal() != slider_vitesse_balle->getValMin())
                {
                    slider_vitesse_balle->setMoins();
                    slider_vitesse_balle->actualiseRepere();
                    _controller->setVitesseBall(slider_vitesse_balle->getValLocal());
                }
                else if (slider_nb_vie->estDedansGauche(MouseX, MouseY) && slider_nb_vie->getValLocal() != slider_nb_vie->getValMin())
                {
                    slider_nb_vie->setMoins();
                    slider_nb_vie->actualiseRepere();
                    _controller->setVie(slider_nb_vie->getValLocal());
                }
                else if (slider_surface->estDedansGauche(MouseX, MouseY) && slider_surface->getValLocal() != slider_surface->getValMin())
                {
                    slider_surface->setMoins();
                    slider_surface->actualiseRepere();
                    _controller->setSurface(slider_surface->getValLocal());
                }
                else if (slider_temps->estDedansGauche(MouseX, MouseY) && slider_temps->getValLocal() != slider_temps->getValMin())
                {
                    slider_temps->setMoins();
                    slider_temps->actualiseRepere();
                    _controller->setTempsParNiveau(slider_temps->getValLocal());
                }
                else if (slider_vitesse_barre->estDedansGauche(MouseX, MouseY) && slider_vitesse_barre->getValLocal() != slider_vitesse_barre->getValMin())
                {
                    slider_vitesse_barre->setMoins();
                    slider_vitesse_barre->actualiseRepere();
                    _controller->setVitesseBarre(1.*slider_vitesse_barre->getValLocal()/100);
                }
                else if (slider_nb_balle->estDedansDroit( MouseX, MouseY) && slider_nb_balle->getValLocal() != slider_nb_balle->getValMax())
                {
                    slider_nb_balle->setPlus();
                    slider_nb_balle->actualiseRepere();
                    _controller->ajoutBall();
                }
                else if (slider_vitesse_balle->estDedansDroit(MouseX, MouseY) && slider_vitesse_balle->getValLocal() != slider_vitesse_balle->getValMax())
                {
                    slider_vitesse_balle->setPlus();
                    slider_vitesse_balle->actualiseRepere();
                    _controller->setVitesseBall(slider_vitesse_balle->getValLocal());
                }
                else if (slider_nb_vie->estDedansDroit(MouseX, MouseY) && slider_nb_vie->getValLocal() != slider_nb_vie->getValMax())
                {
                    slider_nb_vie->setPlus();
                    slider_nb_vie->actualiseRepere();
                    _controller->setVie(slider_nb_vie->getValLocal());
                }
                else if (slider_surface->estDedansDroit(MouseX, MouseY) && slider_surface->getValLocal() != slider_surface->getValMax())
                {
                    slider_surface->setPlus();
                    slider_surface->actualiseRepere();
                    _controller->setSurface(slider_surface->getValLocal());
                }
                else if (slider_temps->estDedansDroit(MouseX, MouseY) && slider_temps->getValLocal() != slider_temps->getValMax())
                {
                    slider_temps->setPlus();
                    slider_temps->actualiseRepere();
                    _controller->setTempsParNiveau(slider_temps->getValLocal());
                }
                else if (slider_vitesse_barre->estDedansDroit(MouseX, MouseY) && slider_vitesse_barre->getValLocal() != slider_vitesse_barre->getValMax())
                {
                    slider_vitesse_barre->setPlus();
                    slider_vitesse_barre->actualiseRepere();
                    _controller->setVitesseBarre(1.*slider_vitesse_barre->getValLocal()/100);

                }
            }

            else if (event.Type == sf::Event::MouseButtonReleased && event.MouseButton.Button == sf::Mouse::Left)
            {
                MouseX = input.GetMouseX();
                MouseY = input.GetMouseY();

                if (bouton_intro->estDedans( MouseX, MouseY ) && bouton_intro->getEnfonce())
                {
                    bouton_intro->setEnfonce(false);
                    etat = "menu_intro";
                    _controller->detachView(this);
                }
                else if (bouton_play->estDedans( MouseX, MouseY ) && bouton_play->getEnfonce())
                {
                    bouton_play->setEnfonce(false);

                    if (perso == "")
                        menuChoix(_window,stop, perso);

                    etat = "jeu";
                    _controller->detachView(this);
                }
                else
                {
                    bouton_intro->setEnfonce(false);
                    bouton_play->setEnfonce(false);
                }

                slider_nb_balle->setEnfonce(false);
                slider_nb_balle->actualiseValLocal();
                slider_nb_balle->actualiseRepere();

                slider_vitesse_balle->setEnfonce(false);
                slider_vitesse_balle->actualiseValLocal();
                slider_vitesse_balle->actualiseRepere();
                _controller->setVitesseBall(slider_vitesse_balle->getValLocal());

                slider_nb_vie->setEnfonce(false);
                slider_nb_vie->actualiseValLocal();
                slider_nb_vie->actualiseRepere();
                _controller->setVie(slider_nb_vie->getValLocal());

                slider_surface->setEnfonce(false);
                slider_surface->actualiseValLocal();
                slider_surface->actualiseRepere();
                _controller->setSurface(slider_surface->getValLocal());

                slider_temps->setEnfonce(false);
                slider_temps->actualiseValLocal();
                slider_temps->actualiseRepere();
                _controller->setTemps(slider_temps->getValLocal());

                slider_vitesse_barre->setEnfonce(false);
                slider_vitesse_barre->actualiseValLocal();
                slider_vitesse_barre->actualiseRepere();
                _controller->setVitesseBarre(1.*slider_vitesse_barre->getValLocal()/100);
            }
        }

        if (slider_nb_balle->getEnfonce() && slider_nb_balle->estDedansBarre(MouseX, MouseY))
        {
            slider_nb_balle->setPositionRepere(MouseX);
            _controller->setNbBall(slider_nb_balle->getValLocal());
        }
        else if (slider_vitesse_balle->getEnfonce() && slider_vitesse_balle->estDedansBarre(MouseX, MouseY))
        {
            slider_vitesse_balle->setPositionRepere(MouseX);
            _controller->setVitesseBall(slider_vitesse_balle->getValLocal());
        }
        if (slider_nb_vie->getEnfonce() && slider_nb_vie->estDedansBarre(MouseX, MouseY))
        {
            slider_nb_vie->setPositionRepere(MouseX);
            _controller->setVie(slider_nb_vie->getValLocal());
        }
        if (slider_surface->getEnfonce() && slider_surface->estDedansBarre(MouseX, MouseY))
        {
            slider_surface->setPositionRepere(MouseX);
            _controller->setSurface(slider_surface->getValLocal());
        }
        if (slider_temps->getEnfonce() && slider_temps->estDedansBarre(MouseX, MouseY))
        {
            slider_temps->setPositionRepere(MouseX);
            _controller->setTempsParNiveau(slider_temps->getValLocal());
        }
        if (slider_vitesse_barre->getEnfonce() && slider_vitesse_barre->estDedansBarre(MouseX, MouseY))
        {
            slider_vitesse_barre->setPositionRepere(MouseX);
            _controller->setVitesseBarre(slider_vitesse_barre->getValLocal()/100);
        }

        string tmp_nbBall = int_to_string(_controller->getNbBall());
        _nb_balle.SetText(tmp_nbBall);

        switch (_controller->getVitBall())
        {
        case 1:
            _vitesse_balle.SetText("Tres lente");
            break;
        case 2:
            _vitesse_balle.SetText("Lente");
            break;
        case 3:
            _vitesse_balle.SetText("Normale");
            break;
        case 4:
            _vitesse_balle.SetText("Rapide");
            break;
        case 5:
            _vitesse_balle.SetText("Tres rapide");
            break;
        }

        string tmp_nbVie = int_to_string(_controller->getVie());
        _nb_vie.SetText(tmp_nbVie);

        string tmp_surface = int_to_string(_controller->getSurfaceARecouvrir());
        _surface.SetText(tmp_surface);

        string tmp_temps = int_to_string(_controller->getTempsParNiveau());
        _temps.SetText(tmp_temps);

        if (_controller->getVitesseBarre() < 0.13 && _controller->getVitesseBarre() > 0.11 )
            _vitesse_barre.SetText("Tres lente");
        else if (_controller->getVitesseBarre() < 0.11 && _controller->getVitesseBarre() > 0.09)
            _vitesse_barre.SetText("Lente");
        else if (_controller->getVitesseBarre() < 0.09 && _controller->getVitesseBarre() > 0.07)
            _vitesse_barre.SetText("Normale");
        else if (_controller->getVitesseBarre() < 0.07 && _controller->getVitesseBarre() > 0.05)
            _vitesse_barre.SetText("Rapide");
        else if (_controller->getVitesseBarre() < 0.05 && _controller->getVitesseBarre() > 0.03)
            _vitesse_barre.SetText("Tres rapide");

    }
}
