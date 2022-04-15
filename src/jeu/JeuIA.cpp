#include "JeuIA.h"

JeuIA::JeuIA()
{
    std::srand(std::time(0));
    reinitialiser();
}

void JeuIA::ajouterPomme()
{
    int aleat=rand()%(HAUTEUR*LARGEUR-m_score-3);
    int numcase=0;
    int i=0;
    for(i=0; numcase<=aleat;i++)
    {
        if(m_ordre[i]==0)
        {
            numcase++;
        }
    }
    m_position_pomme=i-1;
    m_ordre[i-1]=-1;
}

void JeuIA::reinitialiser()
{
    for(int i=0;i<HAUTEUR*LARGEUR;i++)
    {
        m_ordre[i]=0;
    }
    m_position_tete = (HAUTEUR/2)*LARGEUR + LARGEUR/2 -1;
    m_ordre[m_position_tete]=3;
    m_ordre[m_position_tete+1]=2;
    m_ordre[m_position_tete+2]=1;
    m_score = 0;
    ajouterPomme();
}

int JeuIA::getOrdre(unsigned int i) const
{
    return m_ordre[i];
}

bool JeuIA::actualiser(Direction commande)
{
    unsigned int score=m_score;
    if(Jeu::actualiser(commande))
    {
        if(m_ordre[m_position_tete]>0)
        {
            return false;
        }
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
