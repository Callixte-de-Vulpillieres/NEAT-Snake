#include "CarteDeTuile.h"

CarteDeTuile::CarteDeTuile(const std::string &tileset, sf::Vector2u tailletuile, JeuAffBasique *jeu)
{
    // on charge la texture du tileset
    if (!m_tileset.loadFromFile(tileset))
        throw std::runtime_error("Impossiblede charger le tilset");

    m_jeu=jeu;
    m_tailletuile=tailletuile;

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(LARGEUR * HAUTEUR * 4);
}

void CarteDeTuile::actualiser()
{
    for (unsigned int i = 0; i < LARGEUR; ++i)
    {
        for (unsigned int j = 0; j < HAUTEUR; ++j)
        {
            // on récupère le numéro de tuile courant
            unsigned int tileNumber = m_jeu->getSprite(i + j *LARGEUR);
            // on en déduit sa position dans la texture du tileset
            int tu = tileNumber % (m_tileset.getSize().x / m_tailletuile.x);
            int tv = tileNumber / (m_tileset.getSize().x / m_tailletuile.x);

            // on récupère un pointeur vers le quad à définir dans le tableau de vertex
            sf::Vertex* quad = &m_vertices[(i + j * LARGEUR) * 4];

            // on définit ses quatre coins
            quad[0].position = sf::Vector2f(i * m_tailletuile.x, j * m_tailletuile.y);
            quad[1].position = sf::Vector2f((i + 1) * m_tailletuile.x, j * m_tailletuile.y);
            quad[2].position = sf::Vector2f((i + 1) * m_tailletuile.x, (j + 1) * m_tailletuile.y);
            quad[3].position = sf::Vector2f(i * m_tailletuile.x, (j + 1) * m_tailletuile.y);

            // on définit ses quatre coordonnées de texture
            quad[0].texCoords = sf::Vector2f(tu * m_tailletuile.x, tv * m_tailletuile.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * m_tailletuile.x, tv * m_tailletuile.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * m_tailletuile.x, (tv + 1) * m_tailletuile.y);
            quad[3].texCoords = sf::Vector2f(tu * m_tailletuile.x, (tv + 1) * m_tailletuile.y);
        }
    }
}

void CarteDeTuile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // on applique la transformation
    states.transform *= getTransform();

    // on applique la texture du tileset
    states.texture = &m_tileset;

    // et on dessine enfin le tableau de vertex
    target.draw(m_vertices, states);
}
