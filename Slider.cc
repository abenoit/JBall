#include "Slider.h"

Slider::Slider(int x, int y, int val_min, int val_max, int ecart, sf::Sprite &barre, sf::Sprite &repere, sf::Sprite &fleche_gauche, sf::Sprite & fleche_droite, sf::String &name, std::string _name, sf::String &name_changed, sf::Font &font) : _val_min(val_min), _val_max(val_max),_ecart(ecart), _spr_repere(repere),_spr_barre(barre),_spr_fleche_g(fleche_gauche), _spr_fleche_d(fleche_droite), _str_name(&name), _str_name_changed(&name_changed), _str_name_(&_name), _font(&font)
{
    my_posX = x;
    my_posY = y;

    //Redimmensionnement des sprites
    _spr_fleche_g.Resize ( LONG , LONG );
    _spr_fleche_d.Resize ( LONG , LONG );
    _spr_barre.Resize ( LONG_BARRE , LONG );
    _spr_repere.Resize ( LONG/2 , CURSOR );

    //Positionnement des sprites
    _spr_fleche_g.SetPosition ( x-(LONG_BARRE/2)-(2*LONG), y ) ;
    _spr_fleche_d.SetPosition ( x+(LONG_BARRE/2)+LONG, y ) ;
    _spr_barre.SetPosition ( x-(LONG_BARRE/2), y ) ;
    _spr_repere.SetPosition ( x-(LONG_BARRE/2), y-((CURSOR-LONG)/2)) ;

    //Initialisation des écritures
    _str_name->SetText( *_str_name_ );
    _str_name->SetPosition ( x + ( LONG_BARRE/2 ) + ( 4 * LONG ) - 20 , y);
    _str_name->SetFont(*_font);
    _str_name->SetSize(17);

    _str_name_changed->SetText("");
    _str_name_changed->SetPosition ( x + ( LONG_BARRE/2 ) + ( 4 * LONG ) + 235 , y );
    _str_name_changed->SetFont(font);
    _str_name_changed->SetSize(17);

    my_pos_cursorX =  x-(LONG_BARRE/2);
    my_pos_cursorY =  y-((CURSOR-LONG)/2);

    enfonce = false;

    _Xecart = 1. * LONG_BARRE / (((_val_max-_val_min)/_ecart));
}


Slider::~Slider()
{
    // Destructeur
}

void Slider::Render(sf::RenderTarget& Target) const
{
    Target.Draw(_spr_barre);
    Target.Draw(_spr_repere);
    Target.Draw(_spr_fleche_g);
    Target.Draw(_spr_fleche_d);
    Target.Draw(*_str_name);
    Target.Draw(*_str_name_changed);
}

bool Slider::estDedansGauche(int MouseX, int MouseY )
{
    //Si les coordonnée de la souris se trouve sur les flèches
    return ( (MouseX > (my_posX-(LONG_BARRE/2)-(2*LONG)) && MouseX < (my_posX-(LONG_BARRE/2)-LONG) && MouseY > my_posY && MouseY < (my_posY+LONG) ) );
}

bool Slider::estDedansDroit(int MouseX, int MouseY )
{
    //Si les coordonnée de la souris se trouve sur les flèches
    return ( (MouseX > (my_posX+(LONG_BARRE/2)+LONG) && MouseX < (my_posX+(LONG_BARRE/2)+(2*LONG)) && MouseY > my_posY && MouseY < (my_posY+LONG)) );
}

bool Slider::estDedansBarre(int MouseX, int MouseY)
{
    return( MouseX >= my_posX-(LONG_BARRE/2) && MouseX <= my_posX+(LONG_BARRE/2) && MouseY >= my_posY && MouseY <= my_posY+LONG);
}

void Slider::setEnfonce(bool etat)
{
    enfonce = etat;
}

bool Slider::getEnfonce()
{
    return enfonce;
}

void Slider::setPositionRepere(int MouseX)
{
    my_pos_cursorX = MouseX;
    _spr_repere.SetX(my_pos_cursorX-(LONG/4));

    _val_local = ((my_pos_cursorX-(my_posX-(LONG_BARRE/2)))/_Xecart)*_ecart+_val_min;
}

void Slider::setValLocal(int val)
{
    _val_local = val;
}

void Slider::actualiseValLocal()
{
    if (_val_local%_ecart != 0) //si la valeur locale n'est pas un multiple de l'écart lorsqu'on actualise la valeur alors on la place à la valeur proportionnel inférieure
        _val_local -= _val_local%_ecart;
}

void Slider::actualiseRepere()
{
    my_pos_cursorX = my_posX-LONG_BARRE/2 + ((_val_local-_val_min)/_ecart)*_Xecart;
    _spr_repere.SetX(my_pos_cursorX-(LONG/4));
}

int Slider::getValLocal()
{
    return _val_local;
}

int Slider::getValMin()
{
    return _val_min;
}

int Slider::getValMax()
{
    return _val_max;
}

void Slider::setPlus()
{
    _val_local += _ecart;
}

void Slider::setMoins()
{
    _val_local -= _ecart;
}
