#ifndef CARTEDETUILE_H
#define CARTEDETUILE_H

#include <exception>
#include <SFML/Graphics.hpp>
#include "jeu/JeuAffBasique.h"

class CarteDeTuile : public sf::Drawable, public sf::Transformable
{
    public:
    CarteDeTuile(const std::string& tileset, sf::Vector2u tailletuile, JeuAffBasique *jeu);
    void actualiser();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const ;

    private:
    sf::VertexArray m_vertices ;
    sf::Texture m_tileset ;
    sf::Vector2u m_tailletuile ;
    JeuAffBasique* m_jeu ;


};

#endif // CARTEDETUILE_H
