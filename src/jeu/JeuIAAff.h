#ifndef JEUIAAFF_H
#define JEUIAAFF_H

#include <jeu/JeuIA.h>
#include <jeu/JeuAff.h>

class JeuIAAff : public JeuIA, public JeuAff
{
    public:
    JeuIAAff();
    virtual bool actualiser(Direction commande);
    virtual void reinitialiser();

    protected:
    virtual void ajouterPomme();
};

#endif // JEUIAAFF_H
