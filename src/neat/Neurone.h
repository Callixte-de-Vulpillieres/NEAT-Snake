#ifndef NEURONE_H
#define NEURONE_H

#include <vector>
#include <random>
#include <unordered_set>
#include "neat/Liaison.h"

enum Nature {Entrant,Sortant,Cache,Mort};

class Neurone
{
    public:
    Neurone(Nature nat,std::mt19937* generateur);
    Neurone(const Neurone &original);
    float getVal() const;
    Nature getNature() const;
    void setNature(Nature nat);
    void ajouterPere(unsigned int pere, float factevol);
    void setVal(float val);
    bool muter(float factevol);
    std::vector<unsigned int> getParents() const;
    std::vector<float> getPoids() const;
    float getDecalage() const;
    void ajouterEntrees(unsigned int entree_av, unsigned int entreessup);
    void suppparents(std::unordered_set<unsigned int> &parents);

    private:
    std::mt19937* m_generateur;
    std::vector<Liaison> m_liaison;
    std::vector<unsigned int> m_morts;
    float m_valeur;
    float m_decalage=0;
    Nature m_nat;

};

#endif // NEURONE_H
