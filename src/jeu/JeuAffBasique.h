#ifndef JEUAFFBASIQUE_H
#define JEUAFFBASIQUE_H

#include <jeu/Jeu.h>
enum Sprite : unsigned int{Vide=0,QN=1,QE=2,QS=3,QO=4,NS=5,SN=5,EO=6,OE=6,NE=7,EN=7,ES=8,SE=8,OS=9,SO=9,ON=10,NO=10,TN=11,TE=12,TS=13,TO=14,Pomme=15};

class JeuAffBasique : public virtual Jeu
{
    public:
    JeuAffBasique();
    virtual bool actualiser(Direction commande);
    virtual void reinitialiser();
    Sprite getSprite(unsigned int i) const;

    protected:
    virtual void ajouterPomme();
    unsigned int m_position_queue;
    Sprite m_sprite[HAUTEUR*LARGEUR];
};

#endif // JEUAFFBASIQUE_H
