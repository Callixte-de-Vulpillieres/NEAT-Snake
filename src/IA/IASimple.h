#ifndef IASIMPLE_H
#define IASIMPLE_H

#include <IA/IAAbstraite.h>
#include <jeu/JeuAffBasique.h>
#include <jeu/Jeu.h>

class IASimple : public IAAbstraite
{
    public:
    IASimple(std::mt19937* generateur);

    protected:
    virtual Direction recupCommande(unsigned int creature, bool affichage);
};

#endif // IASIMPLE_H
