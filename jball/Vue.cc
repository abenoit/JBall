#include "Vue.h"

///
/// Destructeur de la classe vue
///
Vue::~Vue()
{}

///
/// Action qui gère les évènement (implémenter dans certaine classes fille)
/// @param etat Chaîne de caractère qui décrit ou on se situe (jeu, intro, options ou score)
/// @param stop Booléen qui permet de savoir si on a arreter le jeu
///
void Vue::manageEvent(std::string &etat, bool &stop)
{}

///
/// Action qui gère les évènement (implémenter dans certaine classes fille)
/// @param etat Chaîne de caractère qui décrit ou on se situe (jeu, intro, options ou score)
/// @param stop Booléen qui permet de savoir si on a arreter le jeu
/// @param perso Chaïne de caractère qui définit le personnage
void Vue::manageEvent_perso(std::string &etat, bool &stop, std::string &perso)
{}
