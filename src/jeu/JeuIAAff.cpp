#include "JeuIAAff.h"

JeuIAAff::JeuIAAff()
{
    std::srand(std::time(0));
    reinitialiser();
}

void JeuIAAff::ajouterPomme()
{
    JeuAff::ajouterPomme();
    m_ordre[m_position_pomme]=-1;
}

void JeuIAAff::reinitialiser()
{
    JeuAff::reinitialiser();
    for(int i=0;i<HAUTEUR*LARGEUR;i++)
    {
        m_ordre[i]=0;
    }
    m_ordre[m_position_tete]=3;
    m_ordre[m_position_tete+1]=2;
    m_ordre[m_position_tete+2]=1;
    m_ordre[m_position_pomme]=-1;
}

bool JeuIAAff::actualiser(Direction commande)
{
    unsigned int score=m_score;
    if(JeuAff::actualiser(commande))
    {
        if (m_score==score)
        {
            for (int i=0;i<HAUTEUR*LARGEUR;i++)
            {
                if (m_ordre[i]>0)
                {
                    m_ordre[i]--;
                }
            }
        }
        m_ordre[m_position_tete]=m_score+3;
        return true;
    }
    return false;
}
