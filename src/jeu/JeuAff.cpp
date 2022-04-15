#include "JeuAff.h"

JeuAff::JeuAff()
{
    std::srand(std::time(0));
    reinitialiser();
}

void JeuAff::ajouterPomme()
{
    int aleat=rand()%(HAUTEUR*LARGEUR-m_score-3);
    int numcase=0;
    int i=0;
    for(i=0; numcase<=aleat;i++)
    {
        if(m_sprite[i]==Vide)
        {
            numcase++;
        }
    }
    m_position_pomme=i-1;
    m_sprite[i-1]=Pomme;
}

void JeuAff::reinitialiser()
{
    for(int i=0;i<HAUTEUR*LARGEUR;i++)
    {
        m_sprite[i]=Vide;
    }
    m_position_tete = (HAUTEUR/2)*LARGEUR + LARGEUR/2 -1;
    m_position_queue = (HAUTEUR/2)*LARGEUR + LARGEUR/2 +1;
    m_sprite[m_position_tete]=TO;
    m_sprite[m_position_tete+1]=EO;
    m_sprite[m_position_queue]=QO;
    m_score = 0;
    ajouterPomme();
}

bool JeuAff::actualiser(Direction commande)
{
    unsigned int pos_tete=m_position_tete;
    unsigned int score=m_score;
    if(Jeu::actualiser(commande))
    {
        if (m_sprite[m_position_tete]!=Vide && m_sprite[m_position_tete]!=Pomme)
        {
            return false;
        }
        switch(commande)
        {
        case Nord :
            switch(m_sprite[pos_tete])
            {
            case TN:
                m_sprite[pos_tete]=NS;
                break;
            case TE:
                m_sprite[pos_tete]=ON;
                break;
            case TO:
                m_sprite[pos_tete]=EN;
                break;
            }
            m_sprite[m_position_tete]=TN;
            break;
        case Est :
            switch(m_sprite[pos_tete])
            {
            case TN:
                m_sprite[pos_tete]=SE;
                break;
            case TE:
                m_sprite[pos_tete]=OE;
                break;
            case TS:
                m_sprite[pos_tete]=EN;
                break;
            }
            m_sprite[m_position_tete]=TE;
            break;
        case Sud :
            switch(m_sprite[pos_tete])
            {
            case TS:
                m_sprite[pos_tete]=NS;
                break;
            case TE:
                m_sprite[pos_tete]=OS;
                break;
            case TO:
                m_sprite[pos_tete]=ES;
                break;
            }
            m_sprite[m_position_tete]=TS;
            break;
        case Ouest :
            switch(m_sprite[pos_tete])
            {
            case TN:
                m_sprite[pos_tete]=SO;
                break;
            case TO:
                m_sprite[pos_tete]=OE;
                break;
            case TS:
                m_sprite[pos_tete]=ON;
                break;
            }
            m_sprite[m_position_tete]=TO;
            break;
        }
        if(score!=m_score)
        {
            return true;
        }
        switch(m_sprite[m_position_queue])
        {
        case QN:
            m_sprite[m_position_queue]=Vide;
            m_position_queue-=LARGEUR;
            switch(m_sprite[m_position_queue])
            {
            case SN:
                m_sprite[m_position_queue]=QN;
                break;
            case SE:
                m_sprite[m_position_queue]=QE;
                break;
            case SO:
                m_sprite[m_position_queue]=QO;
                break;
            }
            break;
        case QS:
            m_sprite[m_position_queue]=Vide;
            m_position_queue+=LARGEUR;
            switch(m_sprite[m_position_queue])
            {
            case SN:
                m_sprite[m_position_queue]=QS;
                break;
            case NE:
                m_sprite[m_position_queue]=QE;
                break;
            case NO:
                m_sprite[m_position_queue]=QO;
                break;
            }
            break;
        case QE:
            m_sprite[m_position_queue]=Vide;
            m_position_queue++;
            switch(m_sprite[m_position_queue])
            {
            case ON:
                m_sprite[m_position_queue]=QN;
                break;
            case OE:
                m_sprite[m_position_queue]=QE;
                break;
            case SO:
                m_sprite[m_position_queue]=QS;
                break;
            }
            break;
        case QO:
            m_sprite[m_position_queue]=Vide;
            m_position_queue--;
            switch(m_sprite[m_position_queue])
            {
            case EN:
                m_sprite[m_position_queue]=QN;
                break;
            case ES:
                m_sprite[m_position_queue]=QS;
                break;
            case EO:
                m_sprite[m_position_queue]=QO;
                break;
            }
            break;
        }
        return true;
    }
    return false;
}
