#ifndef EVOLUTOR_H
#define EVOLUTOR_H

#define POPULATION 500

#include "neat/Individu.h"
#include <algorithm>
#include <random>

class Evolutor
{
    public:
    Evolutor(const Evolutor &original);
    Evolutor(unsigned int sortie, unsigned int entree,std::mt19937* generateur);
    void evolution();
    void setNote(unsigned int creature,float note);
    float getNote(unsigned int creature) const;
    void setEntree(unsigned int creature,unsigned int entree, float valeur);
    void calcul(unsigned int creature);
    float getSortie(unsigned int creature, unsigned int sortie) const;
    void augmenterEntrees(unsigned int entreessup);
    unsigned int getNeuroneCaches(unsigned int i) const;

    private:
    Individu m_pop[POPULATION];

};

#endif // EVOLUTOR_H
