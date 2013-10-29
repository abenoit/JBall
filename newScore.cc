#include "newScore.h"

using namespace std;
using namespace sf;
using namespace Key;

///
/// Action permettant d'afficher une fenêtre et de gérer les evenement qui y sont liés : dans cete fenêtre l'utilisateur peut rentrer son nom afin d'apparaitre dans les high score
/// @param *_window Pointeur sur une fenête de rendu
/// @param name Chaîne de caractères passée en entrée sortie correspondant au nom
/// @param score Entier correspondant au score réalisé
/// @param niveau Entier correspondant au niveau atteint
/// @param quit Booléen permettant de quitter la fenetre
/// @param stop Booléen permettant de quitter l'application
///
void newScore(sf::RenderWindow *  _window, string &name, int score, int niveau, bool quit, bool &stop)
{
    sf::Image _background_image;
    sf::Sprite _background;
    sf::String text_name;
    sf::String text_enter;
    sf::Font Police;
    sf::Event event;

    int filtre_text1 = 0, filtre_text2 = 0;

    vector<sf::String> vect_name;
    name = "";
    sf::String tmp;

    if (!_background_image.LoadFromFile("images/highScore.png") || !Police.LoadFromFile("fonts/shanghai.ttf"))
    {
        std::cerr << "ERROR when loading files" << std::endl;
        _background = Sprite ();
    }
    else
    {
        _background = Sprite (_background_image);
        _background.Resize(800,600);
    }

    text_name.SetFont(Police);
    text_name.SetText("Entrez votre nom :");
    text_name.SetPosition(10,10);
    text_name.SetColor(sf::Color(255,0,0,0));
    text_name.SetSize(40);

    text_enter.SetFont(Police);
    text_enter.SetText("Appuyez sur Entrée pour continuer");
    text_enter.SetPosition(30,550);
    text_enter.SetColor(sf::Color(255,0,0,0));


    while (!quit)
    {
        _window->SetFramerateLimit(150);

        _window->Draw(_background);

        if (filtre_text1 < 255)
        {
            filtre_text1 += 1;

            text_name.SetColor(sf::Color(255,255,255, filtre_text1));
        }
        else if (filtre_text2 < 255)
        {
            filtre_text2 += 1;

            text_enter.SetColor(sf::Color(255,255,255, filtre_text2));
        }

        _window->Draw(text_name);
        _window->Draw(text_enter);

        int x = 250;
        for (unsigned int i = 0; i < vect_name.size(); i++)
        {
            vect_name[i].SetSize(50);
            vect_name[i].SetFont(Police);
            vect_name[i].SetColor(sf::Color(255,255,255));
            vect_name[i].SetPosition(x, 330);
            _window->Draw(vect_name[i]);
            x+=40;
        }


        _window->Display();

        while (_window->GetEvent(event))
        {

            if ((event.Type == sf::Event::Closed) || ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape)))
            {
                _window->Close();
                quit = true;
                stop = true;
            }

            if (event.Type == sf::Event::KeyPressed)
            {
                if (event.Key.Code == Back && vect_name.size() > 0)
                    vect_name.pop_back();
                else if (event.Key.Code == Return && vect_name.size() > 0)
                {
                    for (unsigned int i = 0; i < vect_name.size(); i++)
                        name += vect_name[i].GetText();
                    quit = true;
                }
            }

            if (event.Type == sf::Event::KeyPressed && vect_name.size() < 9)
            {
                switch (event.Key.Code)
                {
                case Return:
                    break;
                case A:
                    tmp.SetText("a");
                    vect_name.push_back(tmp);
                    break;
                case B:
                    tmp.SetText("b");
                    vect_name.push_back(tmp);
                    break;
                case C:
                    tmp.SetText("c");
                    vect_name.push_back(tmp);
                    break;
                case D:
                    tmp.SetText("d");
                    vect_name.push_back(tmp);
                    break;
                case E:
                    tmp.SetText("e");
                    vect_name.push_back(tmp);
                    break;
                case F:
                    tmp.SetText("f");
                    vect_name.push_back(tmp);
                    break;
                case G:
                    tmp.SetText("g");
                    vect_name.push_back(tmp);
                    break;
                case H:
                    tmp.SetText("h");
                    vect_name.push_back(tmp);
                    break;
                case I:
                    tmp.SetText("i");
                    vect_name.push_back(tmp);
                    break;
                case J:
                    tmp.SetText("j");
                    vect_name.push_back(tmp);
                    break;
                case K:
                    tmp.SetText("k");
                    vect_name.push_back(tmp);
                    break;
                case L:
                    tmp.SetText("l");
                    vect_name.push_back(tmp);
                    break;
                case M:
                    tmp.SetText("m");
                    vect_name.push_back(tmp);
                    break;
                case N:
                    tmp.SetText("n");
                    vect_name.push_back(tmp);
                    break;
                case O:
                    tmp.SetText("o");
                    vect_name.push_back(tmp);
                    break;
                case P:
                    tmp.SetText("p");
                    vect_name.push_back(tmp);
                    break;
                case Q:
                    tmp.SetText("q");
                    vect_name.push_back(tmp);
                    break;
                case R:
                    tmp.SetText("r");
                    vect_name.push_back(tmp);
                    break;
                case S:
                    tmp.SetText("s");
                    vect_name.push_back(tmp);
                    break;
                case T:
                    tmp.SetText("t");
                    vect_name.push_back(tmp);
                    break;
                case U:
                    tmp.SetText("u");
                    vect_name.push_back(tmp);
                    break;
                case V:
                    tmp.SetText("v");
                    vect_name.push_back(tmp);
                    break;
                case W:
                    tmp.SetText("w");
                    vect_name.push_back(tmp);
                    break;
                case X:
                    tmp.SetText("x");
                    vect_name.push_back(tmp);
                    break;
                case Y:
                    tmp.SetText("y");
                    vect_name.push_back(tmp);
                    break;
                case Z:
                    tmp.SetText("z");
                    vect_name.push_back(tmp);
                    break;
                case Numpad0:
                    tmp.SetText("0");
                    vect_name.push_back(tmp);
                    break;
                case Numpad1:
                    tmp.SetText("1");
                    vect_name.push_back(tmp);
                    break;
                case Numpad2:
                    tmp.SetText("2");
                    vect_name.push_back(tmp);
                    break;
                case Numpad3:
                    tmp.SetText("3");
                    vect_name.push_back(tmp);
                    break;
                case Numpad4:
                    tmp.SetText("4");
                    vect_name.push_back(tmp);
                    break;
                case Numpad5:
                    tmp.SetText("5");
                    vect_name.push_back(tmp);
                    break;
                case Numpad6:
                    tmp.SetText("6");
                    vect_name.push_back(tmp);
                    break;
                case Numpad7:
                    tmp.SetText("7");
                    vect_name.push_back(tmp);
                    break;
                case Numpad8:
                    tmp.SetText("8");
                    vect_name.push_back(tmp);
                    break;
                case Numpad9:
                    tmp.SetText("9");
                    vect_name.push_back(tmp);
                    break;
                case Back:
                    break;
                case Escape:
                    break;
                default:
                    cerr << "Erreur entrée" << endl;
                    break;
                }
            }
        }
    }
}
