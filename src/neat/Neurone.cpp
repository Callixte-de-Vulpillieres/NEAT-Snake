#include "Neurone.h"

Neurone::Neurone(Nature nat, std::mt19937 *generateur)
{
    m_nat=nat;
    m_generateur=generateur;
}

Neurone::Neurone(const Neurone &original)
{
    for (unsigned int i=0; i<original.m_liaison.size();i++)
    {
        m_liaison.push_back(original.m_liaison[i]);
    }
    for (unsigned int i=0; i<original.m_morts.size();i++)
    {
        m_morts.push_back(original.m_morts[i]);
    }
    m_valeur=original.m_valeur;
    m_decalage=original.m_decalage;
    m_nat=original.m_nat;
    m_generateur=original.m_generateur;
}

void Neurone::ajouterEntrees(unsigned int entree_av, unsigned int entreessup)
{
    for (unsigned int i=0;i<m_liaison.size();i++)
    {
        if (m_liaison[i].getPere()>=entree_av)
        {
            m_liaison[i].decalPere(entreessup);
        }
    }
}

void Neurone::setNature(Nature nat)
{
    m_nat = nat;
    if(m_nat==Mort)
    {
        for (unsigned int i=0;i<m_liaison.size();i++)
        {
            if(m_liaison[i].getPoids()!=0)
            {
                m_morts.push_back(i);
                m_liaison[i].setMort();
            }
        }
    }
}

Nature Neurone::getNature() const
{
    return m_nat;
}

void Neurone::ajouterPere(unsigned int pere, float factevol)
{
    if (m_morts.size()==0)
    {
        m_liaison.push_back(Liaison(pere,factevol,m_generateur));
    }
    else
    {
        m_liaison[m_morts[m_morts.size()-1]].reinit(pere,factevol,m_generateur);
        m_morts.pop_back();
    }
}

void Neurone::setVal(float val)
{
    m_valeur=val;
}

bool Neurone::muter(float factevol)
{
    for (unsigned int i=0;i<m_liaison.size();i++)
    {
        if (m_liaison[i].getPoids()!=0 && !m_liaison[i].muter(factevol))
        {
            m_morts.push_back(i);
        }
    }
    if (m_morts.size()==m_liaison.size() && m_nat==Cache)
    {
        m_nat=Mort;
        return false;
    }
    std::normal_distribution<float> d(m_decalage, VARIANCE*factevol);
    m_decalage=d(*m_generateur);
    return true;
}

float Neurone::getDecalage() const
{
    return m_decalage;
}

std::vector<unsigned int> Neurone::getParents() const
{
    std::vector<unsigned int> ret;
    for (unsigned int i=0;i<m_liaison.size();i++)
    {
        if(m_liaison[i].getPoids()!=0)
        {
            ret.push_back(m_liaison[i].getPere());
        }
    }
    return ret;
}

std::vector<float> Neurone::getPoids() const
{
    std::vector<float> ret;
    for (unsigned int i=0;i<m_liaison.size();i++)
    {
        if(m_liaison[i].getPoids()!=0)
        {
            ret.push_back(m_liaison[i].getPoids());
        }
    }
    return ret;
}
float Neurone::getVal() const
{
    return m_valeur;
}

void Neurone::suppparents(std::unordered_set<unsigned int> &parents)
{
    for (unsigned int i=0;i<m_liaison.size();i++)
    {
        if(m_liaison[i].getPoids()!=0 && parents.find(m_liaison[i].getPere())!=parents.end())
        {
            m_liaison[i].setMort();
            m_morts.push_back(i);
        }
    }
}
