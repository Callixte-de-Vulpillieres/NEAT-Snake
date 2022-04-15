#ifndef INDIVIDU_H
#define INDIVIDU_H

#include <vector>
#include <cstdlib>
#include <math.h>
#include <unordered_set>
#include <random>
#include "neat/Neurone.h"

class Individu
{
    public:
    Individu() {}
    void init(unsigned int entrees,unsigned int sorties,std::mt19937* generateur);
    void setEntree(unsigned int entree, float valeur);
    float getSortie(unsigned int sortie) const;
    void muter();
    void calcul();
    void augmenterEntrees(unsigned int entreessup);
    Individu(const Individu &original);
    void setNote(float note);
    float getNote() const;
    unsigned int getNeuroneCaches() const;


    private:
    std::mt19937* m_generateur;
    void calculNeurone(unsigned int indice, std::vector<bool> teste);
    bool parcoursNeurone(unsigned int indice,std::unordered_set<unsigned int>& desc,std::unordered_set<unsigned int>& visite);
    float m_note;
    float m_factevol=1;
    std::vector<Neurone> m_neurone;
    std::vector<size_t> m_morts;
    unsigned int m_entree;
    unsigned int m_sortie;
};

bool operator<(const Individu &a,const Individu &b);
#endif // INDIVIDU_H
