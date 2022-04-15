#include "IAAbstraite.h"

IAAbstraite::IAAbstraite()
{
    m_fenetre=new sf::RenderWindow(sf::VideoMode(LARGEUR*64, HAUTEUR*64),"Snake par Callixte de Vulpillieres");
    m_fenetre->setFramerateLimit(m_framerate);
    m_fenetre->setVisible(false);
    m_fenetre->setActive(false);
}

IAAbstraite::~IAAbstraite()
{
    m_fenetre->close();
    delete m_fenetre;
    delete m_jeu;
    delete m_jeu_aff;
    delete m_carte;
    delete m_evolutor;
}

unsigned int IAAbstraite::gener()
{
    m_scoremax=0;
    m_scoretot=0;
    m_neuronetot=0;
    m_fenetre->setActive(m_affichage);
    if (m_affichage)
    {
        m_titre="Generation "+std::to_string(m_generation);
        m_fenetre->requestFocus();
    }
    for (unsigned int i=0;i<POPULATION;i++)
    {
        note(i);
    }
    std::cout<<std::endl<<std::endl<<"Generation "<<m_generation<<" : "<<std::endl<<"    Score Maximum : "<<m_scoremax<<std::endl;
    std::cout<<"    Nombre de neurones caches : "<<m_evolutor->getNeuroneCaches(m_imax)<<std::endl<<std::endl;
    std::cout<<"    Score moyen : "<<m_scoretot/POPULATION<<std::endl<<"    Nombre de neurones caches moyen : "<<m_neuronetot/POPULATION<<std::endl;
    m_fenetre->setActive(m_affmax);
    if (m_affmax)
    {
        m_titre="Max de la generation "+std::to_string(m_generation);
        afficherpartie(m_imax);
    }
    m_evolutor->evolution();
    m_generation++;
    return m_scoremax;
}

void IAAbstraite::setParamAff(unsigned int framerate, bool aff, bool affmax)
{
    if (framerate==0)
        m_framerate=1;
    else
        m_framerate=framerate;
    m_affichage=aff;
    m_affmax=affmax;
    m_fenetre->setFramerateLimit(m_framerate);
}

void IAAbstraite::setParamAff(unsigned int framerate)
{
    if (framerate==0)
        m_framerate=1;
    else
        m_framerate=framerate;
    m_fenetre->setFramerateLimit(m_framerate);
}

void IAAbstraite::note(unsigned int creature)
{
    if(m_affichage)
    {
        m_evolutor->setNote(creature,afficherpartie(creature));
    }
    else
    {
        m_jeu->reinitialiser();
        Direction commande;
        bool qcq=true;
        unsigned int j=0;
        while(qcq&&j<20000)
        {
            int i=0;
            unsigned int score=m_jeu->getScore();
            for(i=0;i<50&&qcq;i++)
            {
                commande = recupCommande(creature,false);
                qcq=m_jeu->actualiser(commande);
                j++;
                if(score!=m_jeu->getScore())
                {
                    i=70;
                }
            }
            if(i==50)
            {
                qcq=false;
            }
        }
        m_evolutor->setNote(creature,m_jeu->getScore() + 1/(1+pow(((m_jeu->getPositionPomme())%LARGEUR)-((m_jeu->getPositionTete())%LARGEUR),2) + pow(((m_jeu->getPositionPomme())/LARGEUR)-((m_jeu->getPositionTete())/LARGEUR),2)));
    }
    m_scoretot+=m_evolutor->getNote(creature);
    m_neuronetot+=m_evolutor->getNeuroneCaches(creature);
    if(m_evolutor->getNote(creature)>m_scoremax)
    {
        m_scoremax=m_evolutor->getNote(creature);
        m_imax=creature;
    }
}

unsigned int IAAbstraite::afficherpartie(unsigned int creature)
{
    m_jeu_aff->reinitialiser();
    m_fenetre->setTitle(m_titre+". Score : 0");
    m_fenetre->setVisible(true);
    m_carte->actualiser();
    bool visible=true;
    unsigned int score=0;
    unsigned int j=0;
    while (visible&&j<20000)
    {
        int i=0;
        score=m_jeu_aff->getScore();
        for(i=0;visible&&i<50;i++)
        {// on gère les évènements
            sf::Event event;
            while (m_fenetre->pollEvent(event))
            {
                switch(event.type)
                {
                case sf::Event::Closed :
                    m_fenetre->setVisible(false);
                    visible=false;
                    break;
                case sf::Event::KeyPressed :
                    switch(event.key.code)
                    {
                    case sf::Keyboard::Right :
                        if (m_framerate<UINT_MAX/2)
                            setParamAff(m_framerate*2);
                        else
                            setParamAff(UINT_MAX);
                        break;
                    case sf::Keyboard::Left :
                        setParamAff(m_framerate/2);
                        break;
                    }
                    break;
                }
            }
            if (!m_jeu_aff->actualiser(this->recupCommande(creature,true)))
            {
                m_fenetre->setVisible(false);
                visible=false;
            }
            j++;
            if(score!=m_jeu_aff->getScore())
            {
                i=100;
            }


            // on dessine le niveau
            m_fenetre->clear();
            m_carte->actualiser();
            m_fenetre->draw(*m_carte);
            m_fenetre->setTitle(m_titre+". Score : "+std::to_string(m_jeu_aff->getScore()));
            m_fenetre->display();
        }
        if(i==50)
        {
            m_fenetre->setVisible(false);
            visible=false;
        }
    }
    score= m_jeu_aff->getScore();
    return score + 1/(1+pow(((m_jeu_aff->getPositionPomme())%LARGEUR)-((m_jeu_aff->getPositionTete())%LARGEUR),2) + pow(((m_jeu_aff->getPositionPomme())/LARGEUR)-((m_jeu_aff->getPositionTete())/LARGEUR),2));
}

Evolutor* IAAbstraite::getEvolutor()
{
    Evolutor* ret = new Evolutor(*m_evolutor);
    return ret;
}
