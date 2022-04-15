#include "IACplx.h"

IACplx::IACplx(std::mt19937 *generateur)
{
    m_generateur=generateur;
    m_jeu_IA = new JeuIA();
    m_jeu = m_jeu_IA;
    m_jeu_IA_aff = new JeuIAAff();
    m_jeu_aff=m_jeu_IA_aff;
    m_evolutor = new Evolutor(4,HAUTEUR*LARGEUR+4,m_generateur);
    m_carte = new CarteDeTuile("tileset.bmp", sf::Vector2u(64, 64), m_jeu_aff);
}

IACplx::IACplx(Evolutor* evolutor,std::mt19937* generateur)
{
    m_generateur=generateur;
    m_evolutor=evolutor;
    m_jeu_IA = new JeuIA();
    m_jeu = m_jeu_IA;
    m_jeu_IA_aff = new JeuIAAff();
    m_jeu_aff=m_jeu_IA_aff;
    m_carte = new CarteDeTuile("tileset.bmp", sf::Vector2u(64, 64), m_jeu_aff);
    m_evolutor->augmenterEntrees(HAUTEUR*LARGEUR);
}

Direction IACplx::recupCommande(unsigned int creature,bool affichage)
{
    JeuIA* jeu;
    if(affichage)
        jeu=m_jeu_IA_aff;
    else
        jeu=m_jeu_IA;
    unsigned int x_tete = jeu->getPositionTete()%LARGEUR;
    unsigned int y_tete = jeu->getPositionTete()/LARGEUR;
    m_evolutor->setEntree(creature,0,x_tete);
    m_evolutor->setEntree(creature,1,jeu->getPositionPomme()%LARGEUR);
    m_evolutor->setEntree(creature,2,y_tete);
    m_evolutor->setEntree(creature,3,jeu->getPositionPomme()/LARGEUR);
    for(int i=0;i<HAUTEUR*LARGEUR;i++)
    {
        m_evolutor->setEntree(creature,4+i,jeu->getOrdre( (((i/LARGEUR)+y_tete)%HAUTEUR)*LARGEUR + (x_tete+(i%LARGEUR))%LARGEUR ));
    }
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
