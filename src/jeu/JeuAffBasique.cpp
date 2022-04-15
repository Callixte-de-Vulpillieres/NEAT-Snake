#include "JeuAffBasique.h"

JeuAffBasique::JeuAffBasique()
{
    std::srand(std::time(0));
    reinitialiser();
}

void JeuAffBasique::ajouterPomme()
{
    Jeu::ajouterPomme();
    m_sprite[m_position_pomme]=Pomme;
}

void JeuAffBasique::reinitialiser()
{
    for(int i=0;i<HAUTEUR*LARGEUR;i++)
    {
        m_sprite[i]=Vide;
    }
    m_position_tete = (HAUTEUR/2)*LARGEUR + LARGEUR/2 -1;
    m_sprite[m_position_tete]=TO;
    m_sprite[m_position_tete+1]=QO;
    m_position_queue=m_position_tete+1;
    m_score = 0;
    ajouterPomme();
}

Sprite JeuAffBasique::getSprite(unsigned int i) const
{
    return m_sprite[i];
}

bool JeuAffBasique::actualiser(Direction commande)
{
    m_sprite[m_position_queue]=Vide;
    m_position_queue = m_position_tete;
    if(Jeu::actualiser(commande))
    {
        switch(commande)
        {
        case Nord :
            m_sprite[m_position_tete]=TN;
            m_sprite[m_position_queue]=QN;
            break;
        case Sud :
            m_sprite[m_position_tete]=TS;
            m_sprite[m_position_queue]=QS;
            break;
        case Ouest :
            m_sprite[m_position_tete]=TO;
            m_sprite[m_position_queue]=QO;
            break;
        case Est :
            m_sprite[m_position_tete]=TE;
            m_sprite[m_position_queue]=QE;
            break;
        }
        return true;
    }
    return false;
}
