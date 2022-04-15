#ifndef IAABSTRAITE_H
#define IAABSTRAITE_H

#include <ctime>
#include <iostream>
#include <random>
#include <neat/Evolutor.h>
#include <CarteDeTuile.h>
#include <jeu/Jeu.h>
#include <jeu/JeuAffBasique.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class IAAbstraite
{
    public:
    IAAbstraite();
    ~IAAbstraite();
    unsigned int gener();
    void setParamAff(unsigned int framerate, bool aff, bool affmax);
    void setParamAff(unsigned int framerate);
    Evolutor *getEvolutor();

    protected:
    void note(unsigned int creature);
    unsigned int afficherpartie(unsigned int creature);
    virtual Direction recupCommande(unsigned int creature, bool affichage)=0;
    std::mt19937* m_generateur;

    CarteDeTuile* m_carte=nullptr;
    Jeu* m_jeu=nullptr;
    JeuAffBasique* m_jeu_aff=nullptr;
    sf::RenderWindow* m_fenetre;
    unsigned int m_framerate = 4;
    unsigned int m_imax;
    float m_scoremax=0;
    bool m_affichage=true;
    bool m_affmax=true;
    unsigned int m_generation=0;
    float m_scoretot;
    float m_neuronetot;
    Evolutor* m_evolutor;
    std::string m_titre;

};

#endif // IAABSTRAITE_H
