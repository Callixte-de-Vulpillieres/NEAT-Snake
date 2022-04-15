#ifndef JEUIA_H
#define JEUIA_H

#include <jeu/Jeu.h>
#include <ctime>

class JeuIA : public virtual Jeu
{
    public:
    JeuIA();
    virtual bool actualiser(Direction commande);
    virtual void reinitialiser();
    int getOrdre(unsigned int i) const;

    protected:
    virtual void ajouterPomme();
    int m_ordre[HAUTEUR*LARGEUR];
};

#endif // JEUIA_H
