#include "HighScoreView.h"
#include "HighScoreController.h"

using namespace sf;

///
/// Constructeur de HighScoreView avec paramètres
/// @param w Longueur de la fenêtre
/// @param h Hauteur de la fenêtre
/// @param *window Pointeur vers une fenêtre de rendu
///
HighScoreView::HighScoreView(int w, int h, sf::RenderWindow *window)
{
    _window = window;

    if (!_img_background.LoadFromFile("images/high_score.png") || !_police.LoadFromFile("fonts/shanghai.ttf") || !_img_bouton.LoadFromFile("images/boutton.png") || !_img_bouton_enfonce.LoadFromFile("images/boutton_enfonce.png") || !_img_cursor.LoadFromFile("images/cursor.png"))
    {
        std::cerr << "ERROR when loading files" << std::endl;

        _spr_background = Sprite ();

        _spr_bordure = Sprite();
        _spr_bouton = Sprite();
        _spr_bouton_enfonce = Sprite();
        _spr_cursor = Sprite();

        _spr_assombri = new Sprite();
        _spr_assombri->Resize(800,600);
        _spr_assombri->SetColor(sf::Color(0,0,0,100));
    }
    else
    {
        _spr_background = Sprite (_img_background);
        _spr_background.Resize(w,h);

        _spr_cursor = Sprite(_img_cursor);

        _spr_bordure = Sprite();
        _spr_bordure.Resize(w,3);
        _spr_bordure.SetPosition(0,65);
        _spr_bordure.SetColor(sf::Color(255,0,0));

        _spr_bouton = Sprite(_img_bouton);
        _spr_bouton_enfonce = Sprite(_img_bouton_enfonce);

        _spr_assombri = new Sprite();
        _spr_assombri->Resize(800,600);
        _spr_assombri->SetColor(sf::Color(0,0,0,150));

        bouton_retour = new Bouton(400, 550, _text_retour, "Retour", _spr_bouton, _spr_bouton_enfonce, _police);
    }
}

///
/// Destructeur de HighScoreView
///
HighScoreView::~HighScoreView()
{
    delete _window;
    delete bouton_retour;
    delete _spr_assombri;
}

///
/// Action permettant d'attacher un controller à HighScoreView
/// @param *controller Pointeur vers un Controller
///
void HighScoreView::setController(Controller * controller)
{
    _controller = dynamic_cast<HighScoreController *> (controller);

    //Mise à jour des vecteur name, score, niveau
    //seul endroit possible, car on doit le faire qu'une seule fois
    //Et on doit le faire après avoir initialisé le controller
    sf::String tmp_name, tmp_score, tmp_niveau;

    _controller->chargeScore();

    _name.clear();
    _score.clear();
    _niveau.clear();

    tmp_name.SetText("Nom");
    tmp_name.SetFont(_police);
    tmp_name.SetColor(sf::Color(255,255,255));
    _name.push_back(tmp_name);

    tmp_score.SetText("Score");
    tmp_score.SetFont(_police);
    tmp_score.SetColor(sf::Color(255,255,255));
    _score.push_back(tmp_score);

    tmp_niveau.SetText("Niveau");
    tmp_niveau.SetFont(_police);
    tmp_niveau.SetColor(sf::Color(255,255,255));
    _niveau.push_back(tmp_niveau);

    for (int i = 0; i < _controller->getTaille(); i++)
    {
        tmp_name.SetText(_controller->getName(i));
        tmp_name.SetFont(_police);
        _name.push_back(tmp_name);

        tmp_score.SetText(int_to_string(_controller->getScore(i)));
        tmp_score.SetFont(_police);
        _score.push_back(tmp_score);

        tmp_niveau.SetText(int_to_string(_controller->getNiveau(i)));
        tmp_niveau.SetFont(_police);
        _niveau.push_back(tmp_niveau);
    }

    int y = 20;
    for (unsigned int i = 0; i < _name.size() ; i++)
    {
        _name[i].SetPosition(100,y);
        _score[i].SetPosition(400,y);
        _niveau[i].SetPosition(600,y);
        y += 50;
    }
}

///
/// Action permettant d'afficher la fenêtre et son contenu
///
void HighScoreView::draw()
{
    _window->Draw(_spr_background);

    //Pour assombrir l'écran afin de mieux voir les scores
    _window->Draw(*_spr_assombri);

    _window->Draw(_spr_bordure);

    _window->Draw(*bouton_retour);

    _window->Draw(_name[0]);
    _window->Draw(_score[0]);
    _window->Draw(_niveau[0]);

    for (unsigned int i = 1; i < _name.size() ; i += 2)
    {
        _name[i].SetColor(sf::Color(230,0,0));
        _window->Draw(_name[i]);

        _score[i].SetColor(sf::Color(230,0,0));
        _window->Draw(_score[i]);

        _niveau[i].SetColor(sf::Color(230,0,0));
        _window->Draw(_niveau[i]);
    }
    for (unsigned int i = 2; i < _name.size() ; i += 2)
    {
        _name[i].SetColor(sf::Color(255,130,0));
        _window->Draw(_name[i]);

        _score[i].SetColor(sf::Color(255,130,0));
        _window->Draw(_score[i]);

        _niveau[i].SetColor(sf::Color(255,130,0));
        _window->Draw(_niveau[i]);
    }

    _spr_cursor.SetPosition(_cursorX, _cursorY);
    _window->Draw(_spr_cursor);

    _window->Display();
}

///
/// Action qui permet de récupérer et gérer les évenements liés à HighScoreView
/// @param etat Chaîne de caractère permettant de savoir dans quel view l'on se place
/// @param stop Booléen permettant de quitter la fenêtre
///
void HighScoreView::manageEvent(std::string &etat, bool &stop)
{
    if (_window->IsOpened())
    {
        sf::Event event;
        const sf::Input& input = _window->GetInput();

        int MouseX = input.GetMouseX();
        int MouseY = input.GetMouseY();

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

            if (bouton_retour->estDedans( MouseX, MouseY ))
                bouton_retour->changeColor(sf::Color(100,0,255));
            else
                bouton_retour->changeColor(sf::Color(255,255,255));

            //Si on clique
            if (event.Type == sf::Event::MouseButtonPressed && event.MouseButton.Button == sf::Mouse::Left)
            {
                MouseX = input.GetMouseX();
                MouseY = input.GetMouseY();

                if (bouton_retour->estDedans( MouseX, MouseY ))
                {
                    bouton_retour->setEnfonce(true);
                }
            }
            else if (event.Type == sf::Event::MouseButtonReleased && event.MouseButton.Button == sf::Mouse::Left)
            {
                MouseX = input.GetMouseX();
                MouseY = input.GetMouseY();

                if (bouton_retour->estDedans( MouseX, MouseY ) && bouton_retour->getEnfonce())
                {
                    bouton_retour->setEnfonce(false);
                    etat = "menu_intro";
                    _controller->detachView(this);
                }
                else
                    bouton_retour->setEnfonce(false);
            }
        }
    }
}
