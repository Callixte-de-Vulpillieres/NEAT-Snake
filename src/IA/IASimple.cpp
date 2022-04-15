#include "IASimple.h"

IASimple::IASimple(std::mt19937 *generateur) : IAAbstraite()
{
    m_generateur=generateur;
    m_jeu = new Jeu();
    m_jeu_aff = new JeuAffBasique();
    m_evolutor = new Evolutor(4,4,m_generateur);
    m_carte = new CarteDeTuile("tileset.bmp", sf::Vector2u(64, 64), m_jeu_aff);
}

Direction IASimple::recupCommande(unsigned int creature,bool affichage)
{
    Jeu* jeu;
    if(affichage)
        jeu=m_jeu_aff;
    else
        jeu=m_jeu;
    m_evolutor->setEntree(creature,0,jeu->getPositionTete()%LARGEUR);
    m_evolutor->setEntree(creature,1,jeu->getPositionPomme()%LARGEUR);
    m_evolutor->setEntree(creature,2,jeu->getPositionTete()/LARGEUR);
    m_evolutor->setEntree(creature,3,jeu->getPositionPomme()/LARGEUR);
    m_evolutor->calcul(creature);
    Direction maxd=Nord;
    float maxv=m_evolutor->getSortie(creature,0);
    if (m_evolutor->getSortie(creature,1)>maxv)
    {
        maxd=Sud;
        maxv=m_evolutor->getSortie(creature,1);
    }
    if (m_evolutor->getSortie(creature,2)>maxv)
    {
        maxd=Est;
        maxv=m_evolutor->getSortie(creature,2);
    }
    if (m_evolutor->getSortie(creature,3)>maxv)
    {
        return Ouest;
    }
    return maxd;
}
