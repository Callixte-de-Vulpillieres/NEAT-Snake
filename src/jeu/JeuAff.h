#ifndef JEUAFF_H
#define JEUAFF_H

#include <jeu/JeuAffBasique.h>

class JeuAff : public virtual JeuAffBasique
{
    public:
    JeuAff();
    virtual bool actualiser(Direction commande);
    virtual void reinitialiser();

    protected:
    virtual void ajouterPomme();
};

#endif // JEUAFF_H
