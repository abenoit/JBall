#include "GameModel.h"


using namespace std;
using namespace sf;

///
/// Constructeur avec paramètres de GameModel
/// @param w Longueur de la fenêtre
/// @param h Hauteur de la fenêtre
///
GameModel::GameModel(int w, int h) : _w(w), _h(h)
{
    _vie_model = 5;
    _score_model = 0;
    _surface_model = 0;
    _temps_model = 10;
    _niveau_model = 1;
    _surface_a_recouvrir = 50;
    _temps_par_niveau = 10;
    _vitesse_ball = 1;
    _vitesse_barre = 0.08;
    _taille_ball = 20;

    int a, b;
    genererAleaBorne(a, 0, _w-_taille_ball, b, 40, _h-40-_taille_ball );

    Ball *B = new Ball(a, b, _taille_ball, _vitesse_ball);
    _tabBall.push_back(B);

    touchBarre = false;

    //Initisialisation du timer
    _clock_temps.Reset();

    //Initialisation du son
    if (!touchBall.LoadFromFile("sounds/touch.wav"))
      {
        std::cerr << "ERROR when loading sound files" << std::endl;
	touchSoundBall = Sound();
      }
    else
      touchSoundBall = Sound(touchBall);

    // constructeur avec paramÃ¨tres de la matrice
    int xMat, yMat;
    xMat = yMat = 0;
    Matrice.resize(60,vector<Wall* >(80));
    for (unsigned int i=0; i< Matrice.size(); i++)
    {
        for (unsigned int j=0; j<Matrice[i].size(); j++)
        {
            Wall *tmp = new Wall(xMat, yMat);
            Matrice[i][j]=tmp;
            xMat += 10;
        }
        xMat = 0;
        yMat += 10;
    }
}

///
/// Destructeur de GameModel
///
GameModel::~GameModel()
{}

///
/// Action permettant de générer l'étape suivante dans le jeu
///
void GameModel::nextStep()
{
    bool perdu = false;
    int x, y;

    for (unsigned int i = 0; i < _tabBall.size(); i++)
    {
        int bSize = _tabBall[i]->getSize();

        //On simule l'avancée de la balle en x
        _tabBall[i]->setX(_tabBall[i]->getX()+_tabBall[i]->getDx()*_tabBall[i]->getVit());
        x = _tabBall[i]->getX();

        //Si une collision d'est produite
        if ( x >= (_w-bSize) || x<0 || _tabBall[i]->collisionBalles(_tabBall) || _tabBall[i]->collisionMur(Matrice, perdu))
        {
            if (!perdu)
            {
                _tabBall[i]->setX(_tabBall[i]->getX()-_tabBall[i]->getDx()*_tabBall[i]->getVit());
                _tabBall[i]->reverseDX();
            }
            else
            {
                //La balle a touchée un mur en construction
                touchSoundBall.Play();

                touchBarre = true;

            }
        }

        //On simule l'avancée de la balle en y
        _tabBall[i]->setY(_tabBall[i]->getY()+_tabBall[i]->getDy()*_tabBall[i]->getVit());
        y = _tabBall[i]->getY();

        //Si une collision d'est produite
        if ( y>= (_h-bSize-40)  || y<=40 || _tabBall[i]->collisionBalles(_tabBall) || _tabBall[i]->collisionMur(Matrice, perdu))
        {
            if (!perdu)
            {
                _tabBall[i]->setY(_tabBall[i]->getY()-_tabBall[i]->getDy()*_tabBall[i]->getVit());
                _tabBall[i]->reverseDY();
            }
            else
            {
                //La balle a touchée un mur en construction
                touchBarre = true;

                touchSoundBall.Play();
            }
        }
    }

    //pour afficher le temps restant
    float Time = _clock_temps.GetElapsedTime();
    _temps_model -= Time;
    _clock_temps.Reset();


}

///
/// Action permettant de récupérer la position d'une balle
/// @param x Position en x de la balle (entier passé en entrée/sortie)
/// @param y Position en y de la balle (entier passé en entrée/sortie)
/// @param i Indice de la balle dans le vecteur de balle(s)
///
void GameModel::getBallPos(int &x, int &y, int i)
{
    x = _tabBall[i]->getX();
    y = _tabBall[i]->getY();
}

///
/// Accesseur permettant de récupérer l'état d'une case
/// @param i Indice de la case en abscisse
/// @param j Indice de la case en ordonnée
/// @return L'état de la case par une chaîne de caractères : vide, construction ou plein
///
string GameModel::getEtat(int i,int j)
{
    return Matrice[i][j]->getEtat(); //accesseur de la classe Wall pour rÃ©cupÃ©rer l'état de la casse d'indice i j
}

///
/// Accesseur permettant de récupérer le nombre de vie(s) restante(s) du joueur
/// @return Le nombre de vie
///
int GameModel::getVie()
{
    return _vie_model;
}


///
/// Accesseur permettant de récupérer le score du joueur
/// @return Le score
///
int GameModel::getScore()
{
    return _score_model;
}

///
/// Accesseur permettant de récupérer le temps restant du joueur
/// @return Le temps restant
///
float GameModel::getTemps()
{
    return _temps_model;
}

///
/// Accesseur permettant de récupérer le niveau de la partie
/// @return Le niveau
///
int GameModel::getNiveau()
{
    return _niveau_model;
}

///
/// Accesseur permettant de récupérer le nombre de balle(s) dans la partie
/// @return Le nombre de balle(s)
///
int GameModel::getNbBall()
{
    return _tabBall.size();
}

///
/// Accesseur permettant de récupérer la vitesse des balles dans la partie
/// @return La vitesse des balles
///
int GameModel::getVitBall()
{
    return _vitesse_ball;
}

///
/// Accesseur permettant de récupérer la vitesse des barres
/// @return La vitesse des barres
///
float GameModel::getVitBarre()
{
    return _vitesse_barre;
}

///
/// Accesseur permettant de récupérer la surface à recouvrir dans la partie
/// @return La surface à recouvrir
///
int GameModel::getSurfaceARecouvrir()
{
    return _surface_a_recouvrir;
}

///
/// Accesseur permettant de récupérer le temps maximum autorisé pour finir la partie
/// @return Le temps maximum par niveau
///
int GameModel::getTempsParNiveau()
{
    return _temps_par_niveau;
}

///
/// Accesseur permettant de savoir si on a touché une barre
/// @return Retourne un booléen correspondant à la situation
///
bool GameModel::getTouchBarre()
{
    return touchBarre;
}

///
/// Action permettant de changer la vitesse des balles
/// @param vit Nouvelle vitesse des balles
///
void GameModel::setVitesseBall(int vit)
{
    for (unsigned int i = 0; i < _tabBall.size(); i++)
    {
        _tabBall[i]->setVit(vit);
    }
    _vitesse_ball = vit;
}

///
/// Action permettant de changer le nombre de vie(s) restante(s)
/// @param vie Nouveau nombre de vie(s) à mettre à jour
///
void GameModel::setVie(int vie)
{
    _vie_model = vie;
}

///
/// Action permettant de changer le temps maximum autorisé par niveau
/// @param temps Nouveau temps maximum par niveau
///
void GameModel::setTempsParNiveau(int temps)
{
    _temps_par_niveau = temps;
}

///
/// Action permettant de changer le temps restant
/// @param new_temps Nouveau temps restant
///
void GameModel::setTemps(int new_temps)
{
    _clock_temps.Reset();
    _temps_model = new_temps;
}

///
/// Action permettant de changer l'état d'une case
/// @param x Coordonnée en x de la case
/// @param y Coordonnée en y de la case
/// @param e Chaîne de caractère contenant le nouvel état de la case
///
void GameModel::setEtat(int x, int y, std::string e)
{
    Matrice[x][y]->setEtat(e);
}

///
/// Action permettant de changer la surface minimum à recouvrir
/// @param surf Nouvelle surface minimum à recouvrir
///
void GameModel::setSurfaceARecouvrir(int surf)
{
    _surface_a_recouvrir = surf;
}

///
/// Action permettant de changer le niveau du jeu
/// @param niv Nouveau niveau
///
void GameModel::setNiveau(int niv)
{
    _niveau_model = niv;
}

///
/// Action mettant à jour le booléen d'une balle qui touche une barre
/// @param touch Nouveau booléen pour mettre à jour touchBarre
///
void GameModel::setTouchBarre(bool touch)
{
    touchBarre = touch;
}

///
/// Action permettant de gérer la vitesse des barres
/// @param vit Temps s'écoulant entre deux progression de barres
///
void GameModel::setVitesseBarre(float vit)
{
    _vitesse_barre = vit;
}

///
/// Action permettant de gérer la vitesse des balles
/// @param nb Entier correspondant au nouveau nombre de balles
///
void GameModel::setNbBall(int nb)
{
    unsigned int cpt = nb;

    if (_tabBall.size() < cpt)
        for (unsigned int i = _tabBall.size(); i < cpt; i++)
            ajoutBall();
    else
        for (unsigned int i = cpt; i < _tabBall.size(); i++)
            suppBall();
}

///
/// Action permettant de mettre à jour le score
/// @param score Nouveau score
///
void GameModel::setScore(int score)
{
    _score_model = score;
}

///
/// Action qui remet à zero le temps
///
void GameModel::resetTemps()
{
    _clock_temps.Reset();
}

///
/// Action permettant d'ajouter une balle
///
void GameModel::ajoutBall()
{
    int cpt = 0;
    int a, b;
    // pour que la balle soit comprise dans le jeu et non pas dans les bordures
    genererAleaBorne(a, 0, _w-_taille_ball, b, 40, _h-40-_taille_ball);

    while (!verifPositionBallOk(a,b) && cpt < 500)
    {
        // pour qu'une balle ne se superpose pas à une autre
        genererAleaBorne(a, 0, _w-_taille_ball, b, 40, _h-40-_taille_ball);
        cpt++;
    }

    if (cpt < 500)
    {
        // tant qu'il y a moins de 500 balles on peut en ajouter
        Ball *B = new Ball(a, b, _taille_ball, _vitesse_ball);
        _tabBall.push_back(B);
    }
    else
        cerr << "Plus de place pour ajouter une balle" << endl;

}

///
/// Action permettant de supprimer une balle du vecteur de balles
///
void GameModel::suppBall()
{
    _tabBall.pop_back();
}

///
/// Action permettant de supprimer toutes les balles du vecteur de balles
///
void GameModel::clearBall()
{
    _tabBall.clear();
}

///
/// Fonction  qui permet la progression de la barre horizontale droite
/// @param x Entier correspondant à la position en x de la souris
/// @param y Entier correspondant à la position en y de la souris
/// @param nb_d Entier passé en entrée/sortie stockant le nombre de case(s) comprise(s) entre le clic et le bord droit ou la prochaine case à l'état "plein"
/// @param fini Booléen passé en entrée/sortie permettant de savoir si la progression est terminée ou non
/// @return False si la prochaine case à droite est une bordure ou s'il s'agit d'une case à l'état "plein", sinon renvoie true.
bool GameModel::BarreHorizDroit(int x, int y, int &nb_d, bool &fini)
{
    if (x < 80 && getEtat(y,x) == "vide" )
    {
        nb_d++;
        setEtat( y ,x, "construction");
        return true;
    }
    else
    {
        fini = true;
        int i = x-nb_d;
        while (i< x)
        {
            setEtat( y , i , "plein");
            i++;
        }

        return false;
    }

}

///
/// Fonction qui permet la progression de la barre horizontale gauche
/// @param x Entier correspondant à la position en x de la souris
/// @param y Entier correspondant à la position en y de la souris
/// @param nb_g Entier passé en entrée/sortie stockant le nombre de case(s) comprise(s) entre le clic et le bord gauche ou la prochaine case à l'état "plein"
/// @param fini Booléen passé en entrée/sortie permettant de savoir si la progression est terminée ou non
/// @return False si la prochaine case à gauche est à l'état "plein" ou s'il s'agit d'une bordure, true sinon
///
bool GameModel::BarreHorizGauche(int x, int y, int &nb_g, bool &fini)
{

    if (x >= 0 && getEtat(y,x) == "vide" )
    {
        nb_g++;
        setEtat( y ,x, "construction");
        return true;
    }
    else
    {
        int i = x+nb_g;
        fini = true;
        while ( i> x)
        {
            setEtat( y, i, "plein");
            i--;
        }
        return false;
    }
}

///
/// Fonction qui permet la progression de la barre verticale bas
/// @param x Entier correspondant à la position en x de la souris
/// @param y Entier correspondant à la position en y de la souris
/// @param nb_b Entier passé en entrée/sortie stockant le nombre de case(s) comprise(s) entre le clic et le bord droit ou la prochaine case à l'état "plein"
/// @param fini Booléen passé en entrée/sortie permettant de savoir si la progression est terminée ou non
/// @return False si la prochaine case en bas est à l'état "plein" ou s'il s'agit d'une bordure, sinon renvoie true
///
bool GameModel::BarreVertiBas(int x, int y, int &nb_b, bool &fini)
{
    if (y < 56 && getEtat(y,x) == "vide" )
    {
        nb_b++;
        setEtat( y ,x, "construction");
        return true;
    }
    else
    {
        int i = y-nb_b;
        fini = true;
        while ( i < y )
        {
            setEtat( i , x, "plein");
            i++;
        }
        return false;
    }
}


///
/// Fonction qui permet la progression de la barre verticale haut
/// @param x Entier correspondant à la position en x de la souris
/// @param y Entier correspondant à la position en y de la souris
/// @param nb_h Entier passé en entrée/sortie stockant le nombre de case(s) comprise(s) entre le clic et le bord haut ou la prochaine case à l'état "plein"
/// @param fini Booléen passé en entrée/sortie permettant de savoir si la progression est terminée ou non
/// @return False si la prochaine case en haut est à l'état "plein" ou s'il s'agit d'une bordure, sinon renvoie true
///
bool GameModel::BarreVertiHaut(int x, int y, int &nb_h, bool &fini)
{
    if (y >= 4 && getEtat(y,x) == "vide" )
    {
        nb_h++;
        setEtat( y ,x, "construction");
        return true;
    }
    else
    {
        int i = y+nb_h;
        fini = true;
        while ( i > y)
        {
            setEtat ( i, x, "plein");
            i--;
        }
        return false;
    }
}

///
/// Fonction qui calcule la surface recouverte au cours du jeu
/// @return le nombre de case(s) à l'état "plein"
///
int GameModel::calculSurface()
{
    int cpt = 0;
    int nb_total = (SCREEN_WIDTH / 10) * ((SCREEN_HEIGHT - 40 - 40)/10);

    for (int i =0; i<SCREEN_WIDTH/10 ; i++)
        for (int j=0; j< SCREEN_HEIGHT/10 ; j++)
            if (getEtat(j,i) == "plein")
                cpt++;

    _surface_model = (cpt *100)/nb_total ;

    return _surface_model;
}

///
/// Action permettant de remplir une surface à la fin de la progression complète d'une barre horizontale
/// @param x Entier correspondant à la position en x de la souris lors du clic
/// @param y Entier correspondant à la position en y de la souris lors du clic
/// @param nb_g Entier correspondant au nombre de case(s) à l'état vide disponible sur la gauche
/// @param nb_d Entier correspondant au nombre de case(s) à l'état vide disponible sur la droite
///
void GameModel::remplissageHori(int x, int y, int nb_g, int nb_d)
{
    //Remplissage haut
    bool arrive_haut = false;
    int nb_haut = y-1;
    int cpt_haut = 0;
    //Pour connaÃ®tre la hauteur
    while (!arrive_haut && nb_haut > 4)
    {
        if ( getEtat(nb_haut,x) == "vide")
        {
            cpt_haut++;
            nb_haut--;
        }
        else
            arrive_haut = true;
    }
    bool balle_present_haut = false;
    //Parcours les balles pour voir si elles sont dans la zone du haut
    for (unsigned int b = 0; b < _tabBall.size() ; b++)
        if ( _tabBall[b]->getX()/10 > x-nb_g && _tabBall[b]->getX()/10+ _tabBall[b]->getSize()/10 < x+nb_d && _tabBall[b]->getY()/10 > y-cpt_haut-1 && _tabBall[b]->getY()/10+ _tabBall[b]->getSize()/10 < y )
            balle_present_haut = true;

    int tmp;
    if (cpt_haut == 0)
        tmp = y-cpt_haut;
    else
        tmp = y-cpt_haut-1;

    if (!balle_present_haut)
        for (int i = tmp ; i < y; i++)
        {
            for (int j = x-nb_g ; j < x+nb_d ; j++)
            {
                setEtat(i, j , "plein" );
                _score_model++;
            }
        }

    //Remplissage bas
    bool arrive_bas = false;
    int nb_bas = y+1;
    int cpt_bas = 0;
    //Pour connaÃ®tre la hauteur
    while (!arrive_bas && nb_bas < 56)
    {
        if ( getEtat(nb_bas,x) == "vide")
        {
            cpt_bas++;
            nb_bas++;
        }
        else
            arrive_bas = true;
    }
    //cout << " nb bas : " << cpt_bas << endl;
    bool balle_present_bas = false;
    //Parcours les balles pour voir si elles sont dans la zone du bas
    for (unsigned int b = 0; b < _tabBall.size() ; b++)
        if ( _tabBall[b]->getX()/10 > x-nb_g && _tabBall[b]->getX()/10+ _tabBall[b]->getSize()/10 < x+nb_d && _tabBall[b]->getY()/10 > y+1 && _tabBall[b]->getY()/10+ _tabBall[b]->getSize()/10 < y+cpt_bas+1 )
            balle_present_bas = true;

    if (!balle_present_bas)
        for (int i = y+1 ; i < y+cpt_bas+1; i++)
        {
            for (int j = x-nb_g ; j < x+nb_d ; j++)
            {
                setEtat(i, j , "plein" );
                _score_model++;
            }
        }
}

///
/// Action permettant de remplir une surface à la fin de la progression complète d'une barre verticale
/// @param x Entier correspondant à la position en x de la souris lors du clic
/// @param y Entier correspondant à la position en y de la souris lors du clic
/// @param nb_b Entier correspondant au nombre de case(s) à l'état vide disponible sur le bas
/// @param nb_h Entier correspondant au nombre de case(s) à l'état vide disponible sur le haut
///
void GameModel::remplissageVerti(int x, int y, int nb_b, int nb_h)
{
    //Remplissage gauche
    bool arrive_gauche = false;
    int nb_gauche = x-1;
    int cpt_gauche = 0;
    //Pour connaÃ®tre la largeur Ã  gauche
    while (!arrive_gauche && nb_gauche > 0)
    {
        if ( getEtat(y,nb_gauche) == "vide")
        {
            cpt_gauche++;
            nb_gauche--;
        }
        else
            arrive_gauche = true;
    }

    bool balle_present_gauche = false;
    //Parcours les balles pour voir si elles sont dans la zone de gauche
    for (unsigned int b = 0; b < _tabBall.size() ; b++)
        if ( _tabBall[b]->getX()/10 > x-cpt_gauche && _tabBall[b]->getX()/10+ _tabBall[b]->getSize()/10 < x && _tabBall[b]->getY()/10 > y-nb_h-1 && _tabBall[b]->getY()/10+ _tabBall[b]->getSize()/10 < y+nb_b )
            balle_present_gauche = true;

    int tmp;
    if (cpt_gauche == 0)
        tmp = x-cpt_gauche;
    else
        tmp =x-cpt_gauche-1;

    if (!balle_present_gauche)
        for (int i = y-nb_h ; i < y+nb_b; i++)
        {
            for (int j = tmp ; j < x ; j++)
            {
                setEtat(i, j , "plein" );
                _score_model++;
            }
        }

    //Remplissage bas
    bool arrive_droite = false;
    int nb_droite = x+1;
    int cpt_droite = 0;


    //Pour connaÃ®tre la largeur droite
    while (!arrive_droite && nb_droite < 80)
    {
        if ( getEtat(y,nb_droite) == "vide")
        {
            cpt_droite++;
            nb_droite++;
        }
        else
            arrive_droite = true;
    }

    bool balle_present_droite = false;
    //Parcours les balles pour voir si elles sont dans la zone de droite
    for (unsigned int b = 0; b < _tabBall.size() ; b++)
        if ( _tabBall[b]->getX()/10 > x && _tabBall[b]->getX()/10+ _tabBall[b]->getSize()/10 < x+cpt_droite && _tabBall[b]->getY()/10 > y-nb_h-1 && _tabBall[b]->getY()/10+ _tabBall[b]->getSize()/10 < y+nb_b )
            balle_present_droite = true;

    if (!balle_present_droite)
        for (int i = y-nb_h ; i < y+nb_b; i++)
        {
            for (int j = x ; j < x+cpt_droite+1 ; j++)
            {
                setEtat(i, j , "plein" );
                _score_model ++;
            }
        }
}

///
/// Action permettant d'initialiser la matrice du jeu
///
void GameModel::initGrille()
{
    for (unsigned int i=0; i< Matrice.size(); i++)
    {
        for (unsigned int j=0; j<Matrice[i].size(); j++)
        {
            Matrice[i][j]->setEtat("vide");
        }
    }
}

///
/// Fonction permettant de vérifier la position d'une balle
/// @param a Position en x d'une balle
/// @param b Position en y d'une balle
/// @return True si la position est correcte, False sinon.
///
bool GameModel::verifPositionBallOk(int a, int b)
{
    for (unsigned int i = 0; i < _tabBall.size(); i++)
    {
        //On regarde si deux balle ne se touchent pas
        if (a >= _tabBall[i]->getX()-_tabBall[i]->getSize() && a <= _tabBall[i]->getX()+_tabBall[i]->getSize() && b >= _tabBall[i]->getY()-_tabBall[i]->getSize() && b <= _tabBall[i]->getY()+_tabBall[i]->getSize())
            return false;
    }
    return true;
}

///
/// Action qui remet à l'état initial tous les paramètres du jeu après une partie perdue
///
void GameModel::initAll()
{
    //On réinitialise tout
    _vie_model = 5;
    _score_model = 0;
    _surface_model = 0;
    _temps_model = 10;
    _niveau_model = 1;
    _surface_a_recouvrir = 50;
    _temps_par_niveau = 10;
    _vitesse_ball = 1;
    _vitesse_barre = 0.08;
    _taille_ball = 20;

    setVitesseBall(_vitesse_ball);
    setVie(_vie_model);
    setTempsParNiveau(_temps_par_niveau);
    setTemps(_temps_model);
    setSurfaceARecouvrir(_surface_a_recouvrir);
    setNiveau(_niveau_model);
    setNbBall(_niveau_model);
    setTouchBarre(false);
    initGrille();
}
