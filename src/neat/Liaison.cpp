#include "Liaison.h"

Liaison::Liaison(unsigned int pere, float factEvol, std::mt19937 *generateur)
{
    reinit(pere,factEvol,generateur);
}

void Liaison::reinit(unsigned int pere, float factEvol, std::mt19937 *generateur)
{
    m_pere = pere;
    m_generateur=generateur;
    std::normal_distribution<float> d(0, VARIANCE*factEvol);
    float p;
    do
    {
        p=d(*m_generateur);
        if(p<0)
        {
            m_poids=p-EPSILON;
        }
        else
        {
            m_poids=p+EPSILON;
        }
    }while(p==0);
}

void Liaison::setMort()
{
    m_poids=0;
}

bool Liaison::muter(float factEvol)
{
    std::normal_distribution<float> d(m_poids, VARIANCE*factEvol);
    float p=d(*m_generateur);
    if(-EPSILON<=p && p<=EPSILON)
    {
        m_poids=0;
        return false;
    }
    m_poids=p;
    return true;
}

float Liaison::getPoids() const
{
    return m_poids;
}

unsigned int Liaison::getPere() const
{
    return m_pere;
}

void Liaison::decalPere(unsigned int decal)
{
    m_pere += decal;
}
