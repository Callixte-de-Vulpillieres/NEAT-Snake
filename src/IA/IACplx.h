#ifndef IACPLX_H
#define IACPLX_H

#include <IA/IAAbstraite.h>
#include <jeu/JeuIA.h>
#include <jeu/JeuIAAff.h>

class IACplx : public IAAbstraite
{
    public:
    IACplx(std::mt19937* generateur);
    IACplx(Evolutor *evolutor,std::mt19937* generateur);

    protected:
    virtual Direction recupCommande(unsigned int creature, bool affichage);
    JeuIA* m_jeu_IA;
    JeuIAAff* m_jeu_IA_aff;
};

#endif // IACPLX_H
