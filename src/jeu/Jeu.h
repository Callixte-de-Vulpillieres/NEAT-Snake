#ifndef JEU_H
#define JEU_H

#define HAUTEUR 7
#define LARGEUR 15

#include <ctime>
#include <cstdlib>

enum Direction {Nord,Sud,Est,Ouest};

class Jeu
{
    public:
    Jeu();
    virtual bool actualiser(Direction commande);
    virtual void reinitialiser();
    unsigned int getScore() const;
    unsigned int getPositionPomme() const;
    unsigned int getPositionTete() const;

    protected:
    virtual void ajouterPomme();
    unsigned int m_position_pomme;
    unsigned int m_position_tete;
    unsigned int m_score;
};

#endif // JEU_H
