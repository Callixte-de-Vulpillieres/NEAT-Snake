#include "Individu.h"

void Individu::init(unsigned int entrees, unsigned int sorties, std::mt19937 *generateur)
{
    m_generateur=generateur;
    m_entree=entrees;
    m_sortie=sorties;
    for (size_t i=0;i<m_entree;i++)
    {
        m_neurone[i] = Neurone(Entrant,m_generateur);
    }
    for (size_t i=0;i<m_sortie;i++)
    {
        m_neurone[m_entree + i] = Neurone(Sortant,m_generateur);
    }
    std::uniform_int_distribution<> entr(0,m_entree-1);
    std::uniform_int_distribution<> sort(m_entree,m_entree+m_sortie-1);
    m_neurone[sort(*m_generateur)].ajouterPere(entr(*m_generateur),m_factevol);
}

float Individu::getSortie(unsigned int sortie) const
{
    return m_neurone[sortie + m_entree].getVal();
}

void Individu::setEntree(unsigned int entree, float valeur)
{
    m_neurone[entree].setVal(valeur);
}

void Individu::muter()
{
    std::bernoulli_distribution rdli (PROBLIAIS*m_factevol);
    if(rdli(*m_generateur)) //ajouter une liaison
    {
        std::uniform_int_distribution<> rdfil(m_entree,m_neurone.size()-1);
        unsigned int fils;
        bool bo=true;
        while (bo)
        {
            fils = rdfil(*m_generateur);
            if(m_neurone[fils].getNature()!=Mort)
            {
                bo=false;
                std::unordered_set<unsigned int> desc;
                std::unordered_set<unsigned int> visite;
                desc.insert(fils);
                visite.insert(fils);
                for(unsigned int i=0 ; i<m_sortie ; i++)
                {
                    parcoursNeurone(i+m_entree, desc, visite);
                    desc.insert(i+m_entree);
                }
                std::uniform_int_distribution<> rdtr(1,m_neurone.size()-desc.size()-m_morts.size());
                unsigned int aleat=rdtr(*m_generateur);
                unsigned int pere=0;
                unsigned int i=0;
                do
                {
                    if (desc.find(i)==desc.end() && m_neurone[i].getNature() != Mort)
                    {
                        pere++;
                    }
                    i++;
                }while(pere!=aleat);
                m_neurone[fils].ajouterPere(i-1,m_factevol);
            }
        }
    }
    std::bernoulli_distribution rdneur (PROBNEUR*m_factevol);
    if(rdneur(*m_generateur)) //ajouter un neurone
    {
        std::uniform_int_distribution<> rdfil(m_entree,m_neurone.size()-1);
        unsigned int fils;
        bool bo=true;
        while (bo)
        {
            fils = rdfil(*m_generateur);
            if(m_neurone[fils].getNature()!=Mort)
            {
                bo=false;
                std::unordered_set<unsigned int> desc;
                std::unordered_set<unsigned int> visite;
                desc.insert(fils);
                visite.insert(fils);
                for(unsigned int i=0 ; i<m_sortie ; i++)
                {
                    parcoursNeurone(i+m_entree, desc, visite);
                    desc.insert(i+m_entree);
                }
                std::uniform_int_distribution<> rdtr(1,m_neurone.size()-desc.size()-m_morts.size());
                unsigned int aleat=rdtr(*m_generateur);
                unsigned int pere=0;
                unsigned int i=0;
                unsigned int indice;
                do
                {
                    if (desc.find(i)==desc.end() && m_neurone[i].getNature()!=Mort)
                    {
                        pere++;
                    }
                    i++;
                }while(pere<aleat);
                if (m_morts.size()==0)
                {
                    indice=m_neurone.size();
                    m_neurone.push_back(Neurone(Cache,m_generateur));
                }
                else
                {
                    indice=m_morts[m_morts.size()-1];
                    m_morts.pop_back();
                    m_neurone[indice].setNature(Cache);
                }
                m_neurone[indice].ajouterPere(i-1,m_factevol);
                m_neurone[fils].ajouterPere(indice,m_factevol);
            }
        }
    }
    for(unsigned int i=0;i<m_neurone.size();i++)
    {
        if ((m_neurone[i].getNature() != Mort) && !m_neurone[i].muter(m_factevol))
        {
            m_morts.push_back(i);
        }
    }
    std::normal_distribution<float> d(m_factevol, VARIANCE*0.05*m_factevol);
    float al = d(*m_generateur);
    if(al<EPSILON)
    {
        m_factevol = EPSILON;
    }
}

void Individu::calculNeurone(unsigned int indice, std::vector<bool> teste)
{
    float somme=m_neurone[indice].getDecalage();
    std::vector<unsigned int> parents = m_neurone[indice].getParents();
    std::vector<float> poids = m_neurone[indice].getPoids();
    std::unordered_set<unsigned int> parentsmorts;
    bool adesparents=false;
    for (unsigned int j=0 ; j<parents.size() ; j++)
    {
        if (m_neurone[parents[j]].getNature()!=Mort)
        {
            if (!teste[parents[j]])
            {
                calculNeurone(parents[j],teste);
            }
            if (m_neurone[parents[j]].getNature()!=Mort)
            {
                somme+=m_neurone[parents[j]].getVal()*poids[j];
                adesparents=true;
            }
            else
            {
                parentsmorts.insert(parents[j]);
            }
        }
        else
        {
            parentsmorts.insert(parents[j]);
        }
    }
    m_neurone[indice].setVal(1/(1+exp(-somme)));
    if (parentsmorts.size()!=0)
    {
        m_neurone[indice].suppparents(parentsmorts);
    }
    if ((!adesparents) && m_neurone[indice].getNature()==Cache)
    {
        m_neurone[indice].setNature(Mort);
        m_morts.push_back(indice);
    }
    teste[indice]=true;
}

void Individu::calcul()
{
    std::vector<bool> teste;
    for (unsigned int i=0; i<m_entree; i++)
    {
        teste.push_back(true);
    }
    for(unsigned int i=0 ; i<m_sortie ; i++)
    {
        calculNeurone(i+m_entree, teste);
    }
    for (unsigned int i=0;i<m_neurone.size();i++)
    {
        if((!teste[i]) && (m_neurone[i].getNature()==Cache))
        {
            m_morts.push_back(i);
            m_neurone[i].setNature(Mort);
        }
    }
}

void Individu::augmenterEntrees(unsigned int entreessup)
{
    for(unsigned int i=m_entree;i<m_neurone.size();i++)
    {
        m_neurone[i].ajouterEntrees(m_entree,entreessup);
    }
    for(unsigned int i=0;i<m_morts.size();i++)
    {
        m_morts[i] += entreessup;
    }
    for(unsigned int i=0;i<entreessup;i++)
    {
        m_neurone.insert(m_neurone.begin()+m_entree,Neurone(Entrant,m_generateur));
    }
    m_entree+=entreessup;
}

Individu::Individu(const Individu &original)
{
    m_generateur=original.m_generateur;
    m_note=original.m_note;
    m_factevol=original.m_factevol;
    for (unsigned int i=0; i<original.m_neurone.size();i++)
    {
        m_neurone.push_back(Neurone(original.m_neurone[i]));
    }
    for (unsigned int i=0; i<original.m_morts.size();i++)
    {
        m_morts.push_back(original.m_morts[i]);
    }
    m_entree = original.m_entree;
    m_sortie = original.m_sortie;
}

void Individu::setNote(float note)
{
    m_note=note;
}

float Individu::getNote() const
{
    return m_note;
}

bool Individu::parcoursNeurone(unsigned int indice, std::unordered_set<unsigned int> &desc, std::unordered_set<unsigned int> &visite)
{
    bool ret=false;
    auto par = m_neurone[indice].getParents();
    for (unsigned int i=0;i<par.size();i++)
    {
        if(visite.find(par[i])!=visite.end())
        {
            ret = ret || (desc.find(par[i])!=desc.end());
        }
        else
        {
            ret = parcoursNeurone(par[i],desc,visite) || ret;
        }
    }
    visite.insert(indice);
    if (ret)
    {
        desc.insert(indice);
    }
    return ret;
}

bool operator<(const Individu &a,const Individu &b)
{
    return a.getNote()>b.getNote();
}

unsigned int Individu::getNeuroneCaches() const
{
    return m_neurone.size()-m_entree-m_sortie-m_morts.size();
}
