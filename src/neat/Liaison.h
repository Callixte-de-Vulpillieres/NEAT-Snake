#ifndef LIAISON_H
#define LIAISON_H

#include <random>

#define EPSILON 0.05
#define VARIANCE 0.3
#define PROBNEUR 0.1
#define PROBLIAIS 0.1

class Liaison
{
    public:
    Liaison(unsigned int pere,float factEvol,std::mt19937* generateur);
    void reinit(unsigned int pere,float factEvol, std::mt19937* generateur);
    void setMort();
    bool muter(float factEvol);
    float getPoids() const;
    unsigned int getPere() const;
    void decalPere(unsigned int decal);

    private:
    std::mt19937* m_generateur;
    float m_poids;
    unsigned int m_pere;
};

#endif // LIAISON_H
