#include "GameView.h"
using namespace sf;
using namespace std;

///
/// Constructeur avec paramètres de la classe GameView
/// @param w Largeur de la fenêtre
/// @param h Hauteur de la fenêtre
/// @param *window Pointeur sur un RenderWindow (fenêtre de rendu)
///
GameView::GameView(int w, int h, sf::RenderWindow *window)
{
    _window = window;

    if (!_img_background.LoadFromFile("images/sonic.png") || !_img_balle.LoadFromFile("images/ball.png") || !_police.LoadFromFile("fonts/shanghai.ttf") || !img_bouton.LoadFromFile("images/boutton.png") || !img_bouton_enfonce.LoadFromFile("images/boutton_enfonce.png")|| !_img_sonic.LoadFromFile("images/sonic.png") || !_img_amy.LoadFromFile("images/amy.png") || !_img_knuckles.LoadFromFile("images/knuckles.png") || !_img_tails.LoadFromFile("images/tails.png") || !_img_shadow.LoadFromFile("images/shadow.png") || !_img_cursor_hori.LoadFromFile("images/cursor_hori.png") || !_img_cursor_verti.LoadFromFile("images/cursor_verti.png") || !_img_cursor.LoadFromFile("images/cursor.png"))
    {
        std::cerr << "ERROR when loading files" << std::endl;
        _spr_background = Sprite ();
        _spr_ball = Sprite ();
        _spr_bouton = Sprite();
        _spr_bouton_enfonce = Sprite();
    }
    else
    {
        // Chargement des sprites
        _spr_background.Resize(w,h);

        _spr_ball = Sprite(_img_balle);

        _spr_bordure = Sprite();
        _spr_bordure.Resize(800,3);

        _spr_mur_plein = new Sprite();
        _spr_mur_plein->Resize(10,10);
        _spr_mur_plein->SetColor(sf::Color(100,0,255,100));

        _spr_mur_construction = new Sprite();
        _spr_mur_construction->Resize(10,10);
        _spr_mur_construction->SetColor(sf::Color(255,255,0,100));

        _spr_bouton = Sprite(img_bouton);
        _spr_bouton_enfonce = Sprite(img_bouton_enfonce);
        _spr_bouton_enfonce.Resize(LONG_BUTTON, HAUT_BUTTON);

        bouton_intro = new Bouton(SCREEN_WIDTH/2-150, 200, _text_intro, "Acceuil", _spr_bouton, _spr_bouton_enfonce, _police);

        bouton_options = new Bouton(SCREEN_WIDTH/2-150, 300,_text_options, "Options", _spr_bouton, _spr_bouton_enfonce, _police);

        bouton_pause = new Bouton(SCREEN_WIDTH/2-150, 400, _text_pause, "Pause", _spr_bouton, _spr_bouton_enfonce, _police);

        bouton_sauvegarder = new Bouton(SCREEN_WIDTH/2+150, 200, _text_sauvegarder, "Sauvegarder", _spr_bouton, _spr_bouton_enfonce, _police);

        bouton_quitter = new Bouton(SCREEN_WIDTH/2+150, 400, _text_quitter, "Quitter", _spr_bouton, _spr_bouton_enfonce, _police);

        bouton_perso = new Bouton(SCREEN_WIDTH/2+150, 300, _text_perso, "Personnages", _spr_bouton, _spr_bouton_enfonce, _police);
    }

    _tmp_temps_barre1=_tmp_temps_barre2 =0;

    _barreHorizGauche = _barreHorizDroit = _barreVertiBas = _barreVertiHaut = false;
    _fini_gauche = _fini_droit = _fini_bas = _fini_haut = false;

    _tmp_xd = _tmp_xg =_tmp_yb = _tmp_yh=0;
    _nb_gauche = _nb_droit = _nb_haut = _nb_bas = 0;


    //Initialisation du texte de pause
    textPause.SetFont(_police);
    textPause.SetText("Pause !");
    textPause.SetPosition(w/2-textPause.GetRect().GetWidth()/2,80);
    textPause.SetSize(40);

    _txtPause.SetFont(_police);
    _txtPause.SetText("P : pause");
    _txtPause.SetPosition(w-150,565);
    _txtPause.SetSize(25);

    //Initialisation du texte score, vie, ...

    //Niveau :
    textNiveau.SetFont(_police);
    textNiveau.SetText("Niveau :");
    textNiveau.SetPosition(10, 5);
    textNiveau.SetSize(25);
    //Vie :
    textVie.SetFont(_police);
    textVie.SetText("Vie :");
    textVie.SetPosition(310, 5);
    textVie.SetSize(25);
    //Temps :
    textTemps.SetFont(_police);
    textTemps.SetText("Temps :");
    textTemps.SetPosition(565, 5);
    textTemps.SetSize(25);
    //Score :
    textScore.SetFont(_police);
    textScore.SetText("Score :");
    textScore.SetPosition(10, 565);
    textScore.SetSize(25);
    //Surface :
    textSurface.SetFont(_police);
    textSurface.SetText("Surface :      /");
    textSurface.SetPosition(310, 565);
    textSurface.SetSize(25);

    //Initialisation des variables score, vie ...
    //_txt_time
    _txt_time.SetFont(_police);
    _txt_time.SetPosition(700,5);
    _txt_time.SetColor(sf::Color(255,150,0));
    _txt_time.SetSize(25);
    //score
    _txt_score.SetFont(_police);
    _txt_score.SetPosition(190,565);
    _txt_score.SetColor(sf::Color(255,150,0));
    _txt_score.SetSize(25);
    //level
    _txt_level.SetFont(_police);
    _txt_level.SetPosition(150,5);
    _txt_level.SetColor(sf::Color(255,150,0));
    _txt_level.SetSize(25);
    //life
    _txt_life.SetFont(_police);
    _txt_life.SetPosition(410,5);
    _txt_life.SetColor(sf::Color(255,150,0));
    _txt_life.SetSize(25);
    //area
    _txt_area.SetFont(_police);
    _txt_area.SetPosition(470,565);
    _txt_area.SetColor(sf::Color(255,150,0));
    _txt_area.SetSize(25);
    //area total à recouvrir
    _txt_area_tot.SetFont(_police);
    _txt_area_tot.SetPosition(540,565);
    _txt_area_tot.SetColor(sf::Color(255,150,0));
    _txt_area_tot.SetSize(25);

    _etat_cursor = "horizontal";
}

///
/// Destructeur de la classe GameView
///
GameView::~GameView()
{
    delete _window;
}

///
/// Action qui permet d'initialiser le controller
/// @param *controller Pointeur sur un Controller
///
void GameView::setController(Controller * controller)
{
    // Connaître le type du controller et eventuellement le convertir
    _controller = dynamic_cast<GameController *> (controller);
}

///
/// Action qui permet de mettre à jour le fond, la couleur des murs et des écritures en fonction du personnage
/// @param perso Chaîne de caractère qui correspond au personnage
///
void GameView::update(std::string perso)
{
    if (perso == "sonic")
    {
        _spr_background = Sprite(_img_sonic);

        _spr_bordure.SetColor(sf::Color(255,0,0));

        textNiveau.SetColor(sf::Color(255,0,0));
        textVie.SetColor(sf::Color(255,0,0));
        textTemps.SetColor(sf::Color(255,0,0));
        textScore.SetColor(sf::Color(255,0,0));
        textSurface.SetColor(sf::Color(255,0,0));
        _txtPause.SetColor(sf::Color(0,0,255));
        textPause.SetColor(sf::Color(0,0,255));

        _txt_time.SetColor(sf::Color(255,0,0));
        _txt_score.SetColor(sf::Color(255,0,0));
        _txt_level.SetColor(sf::Color(255,0,0));
        _txt_life.SetColor(sf::Color(255,0,0));
        _txt_area.SetColor(sf::Color(255,0,0));
        _txt_area_tot.SetColor(sf::Color(255,0,0));

        _spr_mur_plein->SetColor(sf::Color(255,0,0,100));
        _spr_mur_construction->SetColor(sf::Color(255,255,0,100));
    }
    else if (perso == "knuckles")
    {
        _spr_background = Sprite(_img_knuckles);

        _spr_bordure.SetColor(sf::Color(255,190,20));

        textNiveau.SetColor(sf::Color(255,190,20));
        textVie.SetColor(sf::Color(255,190,20));
        textTemps.SetColor(sf::Color(255,190,20));
        textScore.SetColor(sf::Color(255,190,20));
        textSurface.SetColor(sf::Color(255,190,20));
        _txtPause.SetColor(sf::Color(0,125,0));
        textPause.SetColor(sf::Color(0,125,0));

        _txt_time.SetColor(sf::Color(255,190,20));
        _txt_score.SetColor(sf::Color(255,190,20));
        _txt_level.SetColor(sf::Color(255,190,20));
        _txt_life.SetColor(sf::Color(255,190,20));
        _txt_area.SetColor(sf::Color(255,190,20));
        _txt_area_tot.SetColor(sf::Color(255,190,20));

        _spr_mur_plein->SetColor(sf::Color(0,125,0,100));
        _spr_mur_construction->SetColor(sf::Color(255,255,0,100));
    }
    else if (perso == "tails")
    {
        _spr_background = Sprite(_img_tails);

        _spr_bordure.SetColor(sf::Color(255,0,0));

        textNiveau.SetColor(sf::Color(160,0,0));
        textVie.SetColor(sf::Color(160,0,0));
        textTemps.SetColor(sf::Color(160,0,0));
        textScore.SetColor(sf::Color(160,0,0));
        textSurface.SetColor(sf::Color(160,0,0));
        _txtPause.SetColor(sf::Color(255,0,0));
        textPause.SetColor(sf::Color(255,0,0));

        _txt_time.SetColor(sf::Color(160,0,0));
        _txt_score.SetColor(sf::Color(160,0,0));
        _txt_level.SetColor(sf::Color(160,0,0));
        _txt_life.SetColor(sf::Color(160,0,0));
        _txt_area.SetColor(sf::Color(160,0,0));
        _txt_area_tot.SetColor(sf::Color(160,0,0));

        _spr_mur_plein->SetColor(sf::Color(100,60,30,100));
        _spr_mur_construction->SetColor(sf::Color(0,0,0,100));
    }
    else if (perso == "amy")
    {
        _spr_background = Sprite(_img_amy);

        _spr_bordure.SetColor(sf::Color(255,0,0));

        textNiveau.SetColor(sf::Color(85,20,100));
        textVie.SetColor(sf::Color(85,20,100));
        textTemps.SetColor(sf::Color(85,20,100));
        textScore.SetColor(sf::Color(85,20,100));
        textSurface.SetColor(sf::Color(85,20,100));
        _txtPause.SetColor(sf::Color(0,0,255));
        textPause.SetColor(sf::Color(0,0,255));

        _txt_time.SetColor(sf::Color(85,20,100));
        _txt_score.SetColor(sf::Color(85,20,100));
        _txt_level.SetColor(sf::Color(85,20,100));
        _txt_life.SetColor(sf::Color(85,20,100));
        _txt_area.SetColor(sf::Color(85,20,100));
        _txt_area_tot.SetColor(sf::Color(85,20,100));

        _spr_mur_plein->SetColor(sf::Color(100,0,255,100));
        _spr_mur_construction->SetColor(sf::Color(255,255,0,100));
    }
    else if (perso == "shadow")
    {
        _spr_background = Sprite(_img_shadow);

        _spr_bordure.SetColor(sf::Color(255,190,20));

        textNiveau.SetColor(sf::Color(255,190,20));
        textVie.SetColor(sf::Color(255,190,20));
        textTemps.SetColor(sf::Color(255,190,20));
        textScore.SetColor(sf::Color(255,190,20));
        textSurface.SetColor(sf::Color(255,190,20));
        _txtPause.SetColor(sf::Color(255,255,255));
        textPause.SetColor(sf::Color(255,30,0));

        _txt_time.SetColor(sf::Color(255,190,20));
        _txt_score.SetColor(sf::Color(255,190,20));
        _txt_level.SetColor(sf::Color(255,190,20));
        _txt_life.SetColor(sf::Color(255,190,20));
        _txt_area.SetColor(sf::Color(255,190,20));
        _txt_area_tot.SetColor(sf::Color(255,190,20));

        _spr_mur_plein->SetColor(sf::Color(255,255,0,100));
        _spr_mur_construction->SetColor(sf::Color(255,255,255,100));
    }
}

///
/// Action permettant d'afficher dans la fenêtre les differents éléments: textes, sprites...
///
void GameView::draw()
{
    _window->Draw(_spr_background);

    _window->SetFramerateLimit(200);

    if (!_controller->getPause())
    {
        //Affichage des balles
        for (int i =0; i < _controller->getNbBall(); i++)
        {
            int x, y;
            _controller->getBallPos(x, y, i);
            Vector2f ballPos(x, y);
            _spr_ball.SetPosition(ballPos);
            _window->Draw(_spr_ball);
        }
        //Affichage des Murs
        for (unsigned int i=4; i< (SCREEN_HEIGHT/10)-4; i++)
        {
            for (unsigned int j=0; j<SCREEN_WIDTH/10; j++)
            {
                if (_controller->getEtat(i,j) == "plein" )
                {
                    _spr_mur_plein->SetPosition(j*10,i*10);
                    _window->Draw(*_spr_mur_plein);
                }
                else if (_controller->getEtat(i,j) == "construction" )
                {
                    _spr_mur_construction->SetPosition(j*10,i*10);
                    _window->Draw(*_spr_mur_construction);
                }
            }
        }
    }
    else
    {
        _window->Draw(textPause);

        _window->Draw(*bouton_intro);
        _window->Draw(*bouton_options);
        _window->Draw(*bouton_pause);
        _window->Draw(*bouton_sauvegarder);
        _window->Draw(*bouton_quitter);
        _window->Draw(*bouton_perso);
    }

    _spr_bordure.SetPosition(0,37);
    _window->Draw(_spr_bordure);
    _spr_bordure.SetPosition(0,600-40);
    _window->Draw(_spr_bordure);



    //Affichage du texte score, vie ...
    _window->Draw(textNiveau);
    _window->Draw(textScore);
    _window->Draw(textVie);
    _window->Draw(textTemps);
    _window->Draw(textSurface);
    _window->Draw(_txtPause);
    //Affichage des variables score, vie ...
    _window->Draw(_txt_time);
    _window->Draw(_txt_score);
    _window->Draw(_txt_area);
    _window->Draw(_txt_area_tot);
    _window->Draw(_txt_level);
    _window->Draw(_txt_life);


    //Affichage du curseur
    if (_etat_cursor == "horizontal" && _cursor_in_game && !_controller->getPause())
    {
        _spr_cursor = Sprite(_img_cursor_hori);
        _spr_cursor.SetPosition(_cursorX-10, _cursorY-10);
    }
    else if (_etat_cursor == "vertical" && _cursor_in_game && !_controller->getPause())
    {
        _spr_cursor = Sprite(_img_cursor_verti);
        _spr_cursor.SetPosition(_cursorX-10, _cursorY-10);
    }
    else if (!_cursor_in_game || _controller->getPause())
    {
        _spr_cursor = Sprite(_img_cursor);
        _spr_cursor.SetPosition(_cursorX, _cursorY);
    }
    _window->Draw(_spr_cursor);


    //Rafraichi l'écran
    _window->Display();

}

///
/// Action qui permet de gérer les differents évenements dans la fenêtre
/// @param etat Chaîne de caractères pour connaître dans quel view on se place
/// @param stop Booléen permettant de savoir si on arrête le programme
/// @param perso Chaîne de caractère pour le personnage choisi
///
void GameView::manageEvent_perso(std::string &etat, bool &stop, std::string &perso)
{

    const sf::Input& input = _window->GetInput();
    if (_window->IsOpened())
    {
        sf::Event event;
        unsigned int MouseX = input.GetMouseX();
        unsigned int MouseY = input.GetMouseY();

        _cursorX = input.GetMouseX();
        _cursorY = input.GetMouseY();

        //Vérification du temps
        if (_controller->getTemps() <= 0)
        {
            //Si le temps arrive à zero mais si on possède encore une ou des vies
            if (_controller->getVie() != 1)
            {
                vieMoins( _window, false,stop);
                if (stop)
                {
                    _window->Close();
                    _controller->detachView(this);
                }
                else
                {
                    _controller->setVie(_controller->getVie()-1);
                    _controller->setTemps(_controller->getTempsParNiveau());
                    _controller->initGrille();

                    _barreHorizDroit = false;
                    _barreHorizGauche = false;
                    _barreVertiBas = false;
                    _barreVertiHaut = false;
                    _nb_gauche = _nb_droit = _nb_haut = _nb_bas = 0;
                }
            }
            //Si on ne possède plus de vie et le temps arrive à zero
            else
            {
                gameOver(_window, false,stop);
                if (stop)
                {
                    _window->Close();
                    _controller->detachView(this);
                }
                else
                {

                    string nom;
                    newScore(_window, nom, _controller->getScore(), _controller->getNiveau(), false, stop);
                    if (stop)
                    {
                        _window->Close();
                        _controller->detachView(this);
                    }
                    else
                    {
                        if (!MaJHighScore(nom,_controller->getScore(), _controller->getNiveau()))
                            cerr << "Erreur lors de la lecture du fichier" << endl;

                        _controller->initAll();
                        _barreHorizDroit = false;
                        _barreHorizGauche = false;
                        _barreVertiBas = false;
                        _barreVertiHaut = false;
                        _nb_gauche = _nb_droit = _nb_haut = _nb_bas = 0;

                        etat = "menu_intro";
                        _controller->detachView(this);
                    }
                }
            }
        }

        if (_controller->getTouchBarre() )
        {
            if (_controller->getVie() != 1)
            {
                vieMoins( _window, false,stop);
                if (stop)
                {
                    _window->Close();
                    _controller->detachView(this);
                }
                else
                {
                    _controller->setVie(_controller->getVie()-1);
                    _controller->setTemps(_controller->getTempsParNiveau());
                    _controller->initGrille();

                    _barreHorizDroit = false;
                    _barreHorizGauche = false;
                    _barreVertiBas = false;
                    _barreVertiHaut = false;
                    _nb_gauche = _nb_droit = _nb_haut = _nb_bas = 0;
                }
            }
            else
            {
                gameOver(_window, false, stop);
                if (stop)
                {
                    _window->Close();
                    _controller->detachView(this);
                }
                else
                {
                    string nom;
                    newScore(_window, nom, _controller->getScore(), _controller->getNiveau(), false, stop);

                    if (stop)
                    {
                        _window->Close();
                        _controller->detachView(this);
                    }
                    else
                    {
                        if (!MaJHighScore(nom,_controller->getScore(), _controller->getNiveau()))
                            cerr << "Erreur lors de la lecture du fichier" << endl;

                        _controller->initAll();
                        _barreHorizDroit = false;
                        _barreHorizGauche = false;
                        _barreVertiBas = false;
                        _barreVertiHaut = false;
                        _nb_gauche = _nb_droit = _nb_haut = _nb_bas = 0;

                        etat = "menu_intro";
                        _controller->detachView(this);
                    }
                }
            }
            _controller->setTouchBarre(false);
        }

        //Vérification de la surface
        if (_controller->getSurface() >= _controller->getSurfaceARecouvrir() )
        {
            niveauSuivant(_window, false,stop);
            if (stop)
            {
                _window->Close();
                _controller->detachView(this);
            }
            _controller->setTemps(_controller->getTempsParNiveau());
            _controller->initGrille();
            _controller->ajoutBall();
            _controller->setNiveau(_controller->getNiveau()+1);

            _barreHorizDroit = false;
            _barreHorizGauche = false;
            _barreVertiBas = false;
            _barreVertiHaut = false;
            _nb_gauche = _nb_droit = _nb_haut = _nb_bas = 0;
        }


        while (_window->GetEvent(event))
        {
            if ((event.Type == sf::Event::Closed) || ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape)))
            {
                _window->Close();
                stop = true;
                _controller->detachView(this);
            }

            if (event.Type == sf::Event::MouseWheelMoved && MouseY > 40 && MouseY < SCREEN_HEIGHT-40)
            {
                if (_etat_cursor == "horizontal")
                    _etat_cursor = "vertical";
                else
                    _etat_cursor = "horizontal";
            }

            if (MouseY <= 40 || MouseY >= SCREEN_HEIGHT-40)
                _cursor_in_game = false;
            else
                _cursor_in_game = true;


            //Ajout d'une balle sur l'appui de la touche a
            if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::A))
            {
                if (_controller->getNbBall() < 30)
                    _controller->ajoutBall();
            }

            if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::S))
            {
                if (_controller->getNbBall() > 0)
                    _controller->suppBall();
            }

            if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::C))
            {
                if (_controller->getNbBall() > 0)
                    _controller->clearBall();
            }

            if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::P))
            {
                if (!_controller->getPause())
                    _controller->setPause(true);
                else
                    _controller->setPause(false);
            }
            if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::M))
            {
                string tmp_name;

                newScore(_window, tmp_name, _controller->getScore(), _controller->getNiveau(), false, stop);
                if (!MaJHighScore(tmp_name,_controller->getScore(), _controller->getNiveau()))
                    cerr << "Erreur lors de la lecture du fichier" << endl;

                etat = "menu_intro";
                _controller->detachView(this);
            }


            if (bouton_intro->estDedans( MouseX, MouseY ))
            {
                bouton_intro->changeColor(sf::Color(100,0,255));
            }
            else  if (bouton_options->estDedans( MouseX, MouseY ))
            {
                bouton_options->changeColor(sf::Color(100,0,255));
            }
            else  if (bouton_pause->estDedans( MouseX, MouseY ))
            {
                bouton_pause->changeColor(sf::Color(100,0,255));
            }
            else  if (bouton_sauvegarder->estDedans( MouseX, MouseY ))
            {
                bouton_sauvegarder->changeColor(sf::Color(100,0,255));
            }
            else  if (bouton_quitter->estDedans( MouseX, MouseY ))
            {
                bouton_quitter->changeColor(sf::Color(100,0,255));
            }
            else  if (bouton_perso->estDedans( MouseX, MouseY ))
            {
                bouton_perso->changeColor(sf::Color(100,0,255));
            }
            else
            {
                bouton_intro->changeColor(sf::Color(255,255,255));
                bouton_options->changeColor(sf::Color(255,255,255));
                bouton_pause->changeColor(sf::Color(255,255,255));
                bouton_sauvegarder->changeColor(sf::Color(255,255,255));
                bouton_quitter->changeColor(sf::Color(255,255,255));
                bouton_perso->changeColor(sf::Color(255,255,255));
            }

            //Si on clique dans la pause
            if (event.Type == sf::Event::MouseButtonPressed && event.MouseButton.Button == sf::Mouse::Left && _controller->getPause())
            {
                MouseX = input.GetMouseX();
                MouseY = input.GetMouseY();

                if (bouton_intro->estDedans( MouseX, MouseY ))
                {
                    bouton_intro->setEnfonce(true);
                }
                else  if (bouton_options->estDedans( MouseX, MouseY ))
                {
                    bouton_options->setEnfonce(true);
                }
                else  if (bouton_pause->estDedans( MouseX, MouseY ))
                {
                    bouton_pause->setEnfonce(true);
                }
                else  if (bouton_quitter->estDedans( MouseX, MouseY ))
                {
                    bouton_quitter->setEnfonce(true);
                }
                else  if (bouton_sauvegarder->estDedans( MouseX, MouseY ))
                {
                    bouton_sauvegarder->setEnfonce(true);
                }
                else  if (bouton_perso->estDedans( MouseX, MouseY ))
                {
                    bouton_perso->setEnfonce(true);
                }
            }

            //Si on relache le clic dans la pause
            else if (event.Type == sf::Event::MouseButtonReleased && event.MouseButton.Button == sf::Mouse::Left && _controller->getPause())
            {
                MouseX = input.GetMouseX();
                MouseY = input.GetMouseY();

                if (bouton_intro->estDedans( MouseX, MouseY ) && bouton_intro->getEnfonce())
                {
                    bouton_intro->setEnfonce(false);
                    etat = "menu_intro";
                    _controller->setPause(false);
                    _controller->detachView(this);
                }
                else  if (bouton_options->estDedans( MouseX, MouseY ) && bouton_options->getEnfonce())
                {
                    bouton_options->setEnfonce(false);
                    etat = "menu_options";
                    _controller->setPause(false);
                    _controller->detachView(this);
                }
                else  if (bouton_pause->estDedans( MouseX, MouseY ) && bouton_pause->getEnfonce())
                {
                    bouton_pause->setEnfonce(false);
                    _controller->setPause(false);
                }
                else  if (bouton_quitter->estDedans( MouseX, MouseY ) && bouton_quitter->getEnfonce())
                {
                    bouton_quitter->setEnfonce(false);
                    stop = true;
                    _window->Close();
                    _controller->detachView(this);
                }
                else  if (bouton_sauvegarder->estDedans( MouseX, MouseY ) && bouton_sauvegarder->getEnfonce())
                {
                    bouton_sauvegarder->setEnfonce(false);
                    cout << "Votre progression a été sauvegardée" << endl;
                    sauvegarde(_controller->getScore(), _controller->getVie(), _controller->getNiveau(), _controller->getTemps(), _controller->getVitBall(), _controller->getSurfaceARecouvrir(),perso );
                    _controller->setPause(false);
                }

                else  if (bouton_perso->estDedans( MouseX, MouseY ) && bouton_perso->getEnfonce())
                {
                    bouton_perso->setEnfonce(false);
                    menuChoix(_window, stop, perso);
                    update(perso);

                    if (stop)
                    {
                        _window->Close();
                        _controller->detachView(this);
                    }
                    else
                        _controller->setPause(false);
                }
                else
                {
                    bouton_intro->setEnfonce(false);
                    bouton_options->setEnfonce(false);
                    bouton_pause->setEnfonce(false);
                    bouton_quitter->setEnfonce(false);
                    bouton_sauvegarder->setEnfonce(false);
                }
            }

            // Quand on clique dans la zone de jeu et qu'on est pas dans la pause:
            if (event.Type == sf::Event::MouseButtonPressed && MouseY > 40 && MouseY < 560 && !_controller->getPause())
            {
                // si aucune barre n'est en cours de progression et que l'ont clique gauche, on lance le chrono temps_barre.
                if ( _etat_cursor == "horizontal" && !_barreHorizDroit && !_barreHorizGauche && !_barreVertiBas && !_barreVertiHaut)
                {
                    //-----------------------------------
                    // pour la progression à vitesse donnée des barres
                    _clock_temps_barre.Reset();
                    _time_barre = _clock_temps_barre.GetElapsedTime();
                    _tmp_temps_barre1= _tmp_temps_barre2 = _time_barre ;
                    //-----------------------------------------------
                    //pour mettre la barre à position coordX coordY et
                    //indiquer que les barre passent en construction à cet endroit

                    _coordX = _tmp_xd = _tmp_xg= (MouseX / 10);
                    _coordY = _tmp_yh = MouseY/10;
                    _barreHorizGauche = _barreHorizDroit = _controller->getHorizDroit(_tmp_xd, _tmp_yh, _nb_droit, _fini_droit);


                }
                // si on clique droit et qu'aucune barre n'est en cours de progression
                else if ( _etat_cursor == "vertical" &&  !_barreHorizDroit && !_barreHorizGauche && !_barreVertiBas && !_barreVertiHaut)
                {
                    //------------------------------
                    // on réutilise les données pour les deux types de barres que l'on réinitialise car on ne peut lancer 2 barres simultanément
                    _clock_temps_barre.Reset();
                    _time_barre = _clock_temps_barre.GetElapsedTime();
                    _tmp_temps_barre1= _tmp_temps_barre2 = _time_barre ;
                    //------------------------------------------

                    _coordX = _tmp_xd = MouseX/10;
                    _coordY = _tmp_yh = _tmp_yb = MouseY/10;
                    _barreVertiBas = _barreVertiHaut= _controller->getVertiBas(_tmp_xd, _tmp_yb, _nb_bas, _fini_bas);

                }

            }

        }

        string time_tmp = int_to_string(_controller->getTemps());
        _txt_time.SetText(time_tmp);

        string score_tmp = int_to_string(_controller->getScore());
        _txt_score.SetText(score_tmp);

        string vie_tmp = int_to_string(_controller->getVie());
        _txt_life.SetText(vie_tmp);

        string niveau_tmp = int_to_string(_controller->getNiveau());
        _txt_level.SetText(niveau_tmp);

        string surface_tmp = int_to_string(_controller->getSurface());
        _txt_area.SetText(surface_tmp);

        string surface_tot_tmp = int_to_string(_controller->getSurfaceARecouvrir());
        _txt_area_tot.SetText(surface_tot_tmp);

        if (_barreHorizDroit && _tmp_temps_barre2 < _time_barre && !_controller->getPause())
        {
            if ( _time_barre < _tmp_temps_barre2+_controller->getVitBarre())
            {

                _tmp_temps_barre2+=_controller->getVitBarre();

                _tmp_xd++;
                _barreHorizDroit = _controller->getHorizDroit(_tmp_xd,_tmp_yh,_nb_droit,_fini_droit);
            }
            else
            {
                while ( _tmp_temps_barre2 + _controller->getVitBarre() <= _time_barre)
                {
                    _tmp_temps_barre2 += _controller->getVitBarre();
                }
            }
        }
        else if (!_controller->getPause())
        {
            _time_barre = _clock_temps_barre.GetElapsedTime();

        }

        // si le _tmp_temps_barre est inférieur à time barre
        if (_barreHorizGauche && _tmp_temps_barre1 < _time_barre && !_controller->getPause())
        {
            // et que time barre est inférieur à _tmp_temps_barre auquel on ajoute la vitesse
            if ( _time_barre < _tmp_temps_barre1+_controller->getVitBarre())
            {
                _tmp_temps_barre1+=_controller->getVitBarre();

                _tmp_xg--;
                _barreHorizGauche = _controller->getHorizGauche(_tmp_xg,_tmp_yh, _nb_gauche, _fini_gauche);
            }

        }
        else if (!_controller->getPause())
        {
            _time_barre = _clock_temps_barre.GetElapsedTime();
        }

        if (_fini_droit && _fini_gauche)
        {

            _controller->remplissageHori(_coordX, _coordY, _nb_gauche, _nb_droit);

            _fini_droit = _fini_gauche = false;
            _nb_gauche = _nb_droit = 0;


        }
        else
        {
            _time_barre = _clock_temps.GetElapsedTime();
        }

        if (_barreVertiBas && _tmp_temps_barre1 < _time_barre && !_controller->getPause())
        {
            if ( _time_barre < _tmp_temps_barre1+_controller->getVitBarre())
            {
                _tmp_temps_barre1+=_controller->getVitBarre();
                _tmp_yb++;
                _barreVertiBas = _controller->getVertiBas(_tmp_xd, _tmp_yb, _nb_bas, _fini_bas);
            }
            else
            {
                while ( _tmp_temps_barre1 + _controller->getVitBarre() <= _time_barre)
                {
                    _tmp_temps_barre1 += _controller->getVitBarre();
                }
            }
        }
        else if (!_controller->getPause())
        {
            _time_barre = _clock_temps.GetElapsedTime();
        }

        if (_barreVertiHaut && _tmp_temps_barre2< _time_barre && !_controller->getPause())
        {
            if ( _time_barre < _tmp_temps_barre2+_controller->getVitBarre())
            {
                _tmp_temps_barre2+=_controller->getVitBarre();
                _tmp_yh--;
                _barreVertiHaut = _controller->getVertiHaut(_tmp_xd, _tmp_yh, _nb_haut, _fini_haut);
            }
            else
            {
                while ( _tmp_temps_barre2 + _controller->getVitBarre() <= _time_barre)
                {
                    _tmp_temps_barre2 += _controller->getVitBarre();
                }
            }
        }
        else if (!_controller->getPause())
        {
            _time_barre = _clock_temps.GetElapsedTime();
        }

        if (_fini_bas && _fini_haut)
        {

            _controller->remplissageVerti(_coordX, _coordY, _nb_bas, _nb_haut);

            _fini_bas = _fini_haut = false;
            _nb_bas = _nb_haut = 0;

        }
    }
}

