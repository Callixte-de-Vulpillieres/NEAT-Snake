#include "Jeu.h"

Jeu::Jeu()
{
    std::srand(std::time(0));
    reinitialiser();
}

void Jeu::reinitialiser()
{
    m_position_tete = (HAUTEUR/2)*LARGEUR + LARGEUR/2;
    m_score = 0;
    ajouterPomme();
}

void Jeu::ajouterPomme()
{
    int aleat=rand()%(HAUTEUR*LARGEUR-1);
    if (m_position_tete<=aleat)
        aleat++;
    m_position_pomme=aleat;
}
bool Jeu::actualiser(Direction commande)
{
    int xprec = m_position_tete%LARGEUR ;
    int yprec =  m_position_tete/LARGEUR ;
    switch(commande)
    {
    case Nord :
        if (yprec==0)
        {
            return false;
        }
        m_position_tete-=LARGEUR;
        break;
    case Est :
        if (xprec+1==LARGEUR)
        {
            return false;
        }
        m_position_tete++;
        break;
    case Sud :
        if (yprec+1==HAUTEUR)
        {
            return false;
        }
        m_position_tete+=LARGEUR;
        break;
    case Ouest :
        if (xprec==0)
        {
            return false;
        }
        m_position_tete--;
        break;
    }
    if(m_position_tete==m_position_pomme)
    {
        m_score++;
        this->ajouterPomme();
        return true;
    }
    return true;
}

unsigned int Jeu::getScore() const
{
    return m_score;
}

unsigned int Jeu::getPositionPomme() const
{
    return m_position_pomme;
}

unsigned int Jeu::getPositionTete() const
{
    return m_position_tete;
}
