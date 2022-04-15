#include "Evolutor.h"

Evolutor::Evolutor(unsigned int sortie, unsigned int entree, std::mt19937 *generateur)
{
    for (int i=0;i<POPULATION;i++)
    {
        m_pop[i].init(entree,sortie,generateur);
    }
}

void Evolutor::augmenterEntrees(unsigned int entreessup)
{
    for (int i=0;i<POPULATION;i++)
    {
        m_pop[i].augmenterEntrees(entreessup);
    }
}

void Evolutor::evolution()
{
    std::sort(std::begin(m_pop),std::end(m_pop));
    for (int i=0;i<POPULATION/2;i++)
    {
        m_pop[i+POPULATION/2]= Individu(m_pop[i]);
        m_pop[i+POPULATION/2].muter();
    }
}

void Evolutor::setNote(unsigned int creature,float note)
{
    m_pop[creature].setNote(note);
}

void Evolutor::setEntree(unsigned int creature,unsigned int entree, float valeur)
{
    m_pop[creature].setEntree(entree,valeur);
}

void Evolutor::calcul(unsigned int creature)
{
    m_pop[creature].calcul();
}

float Evolutor::getSortie(unsigned int creature, unsigned int sortie) const
{
    return m_pop[creature].getSortie(sortie);
}

unsigned int Evolutor::getNeuroneCaches(unsigned int i) const
{
    return m_pop[i].getNeuroneCaches();
}

float Evolutor::getNote(unsigned int creature) const
{
    return m_pop[creature].getNote();
}

Evolutor::Evolutor (const Evolutor &original)
{
    for (int i=0;i<POPULATION;i++)
    {
        m_pop[i]=Individu(original.m_pop[i]);
    }
}
