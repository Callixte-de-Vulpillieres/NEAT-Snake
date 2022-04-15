#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <random>
#include "CarteDeTuile.h"
#include "jeu/JeuAff.h"
#include "IA/IASimple.h"
#include "IA/IACplx.h"

void jouer(std::mt19937& generateur);
void IA(std::mt19937& generateur);

int main()
{
    std::random_device rd;
    std::mt19937 generateur(rd());
    while(true)
    {
        int argument;
        std::cout<<"Bienvenue dans ce jeu et simulateur d'evolution d'IA de Snake, par Callixte de Vulpillieres, realise avec l'aide de la SFML pour les graphismes, et de l'implementation de NEAT de Eric Launkien pour l'IA."<<std::endl;
        std::cout<<std::endl<<"Pour jouer a snake, entrez 1. Pour Commencer une simulation d'IA, entrez 2. Pour quitter le programme, entrez 3"<<std::endl;
        while ( ! ( std::cin >> argument ) || argument < 1 || argument > 3 )
        {
            std::cout << "Saisie incorrecte, recommencez : ";
            if ( std::cin.fail() )
            {
                std::cin.clear();
                std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
            }
        }
        switch (argument)
        {
        case 1:
            jouer(generateur);
            break;
        case 2:
            IA(generateur);
            break;
        default:
            return 0;
            break;
        }
    }
}

void jouer(std::mt19937 &generateur)
{
    // on crée la fenêtre
    sf::RenderWindow window(sf::VideoMode(LARGEUR*64, HAUTEUR*64),"Snake par Callixte de Vulpillieres. Score : 0");
    window.setFramerateLimit(3);
    window.requestFocus();
    //On crée le jeu
    JeuAff jeu;

    try
    {
        CarteDeTuile map("tileset.bmp", sf::Vector2u(64, 64), &jeu);     // on crée la tilemap
        map.actualiser();
        Direction temp=Ouest;
        // on fait tourner la boucle principale
        while (window.isOpen())
        {
            if(window.hasFocus())
            {

                // on gère les évènements
                bool ordre_recu = false ;
                bool vie =true ;
                sf::Event event;
                while (window.pollEvent(event) && !ordre_recu)
                {
                    switch(event.type)
                    {
                    case sf::Event::Closed :
                        window.close();
                        break;
                    case sf::Event::KeyPressed :
                        switch(event.key.code)
                        {
                        case sf::Keyboard::Up :
                            vie = jeu.actualiser(Nord);
                            temp=Nord;
                            ordre_recu = true;
                            break;
                        case sf::Keyboard::Down :
                            vie = jeu.actualiser(Sud);
                            temp=Sud;
                            ordre_recu = true;
                            break;
                        case sf::Keyboard::Right :
                            vie = jeu.actualiser(Est);
                            temp=Est;
                            ordre_recu = true;
                            break;
                        case sf::Keyboard::Left :
                            vie = jeu.actualiser(Ouest);
                            temp=Ouest;
                            ordre_recu = true;
                            break;
                        }
                        break;
                    }
                }
                if (ordre_recu)
                {
                    while(window.pollEvent(event))
                    {
                        switch(event.type)
                        {
                        case sf::Event::Closed :
                            window.close();
                            break;
                        case sf::Event::KeyPressed :
                            switch(event.key.code)
                            {
                            case sf::Keyboard::Up :
                                temp=Nord;
                                break;
                            case sf::Keyboard::Down :
                                temp=Sud;
                                break;
                            case sf::Keyboard::Right :
                                temp=Est;
                                break;
                            case sf::Keyboard::Left :
                                temp=Ouest;
                                break;
                            }
                            break;
                        }
                    }
                }
                else
                {
                    vie=jeu.actualiser(temp);
                }
                if (!vie)
                {
                    jeu.reinitialiser();
                    temp=Ouest;
                }


                // on dessine le niveau
                window.clear();
                map.actualiser();
                window.draw(map);
                window.setTitle("Snake par Callixte de Vulpillieres. Score : " + std::to_string(jeu.getScore()));
                window.display();
            }
        }
    }
    catch(std::exception const& e)
    {
        std::cerr << "ERREUR : " << e.what() << std::endl;
    }
}

void IA(std::mt19937 &generateur)
{
    int argument;
    std::cout<<"Pour creer une population simple, entrez 1. Pour creer une population complexe, entrez 2 : ";
    while ( ! ( std::cin >> argument ) || argument < 1 || argument > 2 )
    {
        std::cout << "Saisie incorrecte, recommencez : ";
        if ( std::cin.fail() )
        {
            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
        }
    }
    switch (argument)
    {
    case 1:
    {
        IASimple IAs(&generateur);
        IAs.setParamAff(4,false,false);
        while(true)
        {
            std::cout<<"Pour lancer un nombre defini de generations, entrez 1. Pour lancer jusqu'a atteindre un objectif donne, entrez 2. Pour changer les parametres, 3. Pour convertir en population complexe, 4 : ";
            while ( ! ( std::cin >> argument ) || argument < 1 || argument > 4 )
            {
                std::cout << "Saisie incorrecte, recommencez : ";
                if ( std::cin.fail() )
                {
                    std::cin.clear();
                    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                }
            }
            switch (argument)
            {
            case 1:
            {
                std::cout<<"Combien de generations ? ";
                while ( ! ( std::cin >> argument ) || argument < 1)
                {
                    std::cout << "Saisie incorrecte, recommencez : ";
                    if ( std::cin.fail() )
                    {
                        std::cin.clear();
                        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                    }
                }
                for (int i=0;i<argument;i++)
                {
                    IAs.gener();
                }
                break;
            }
            case 2:
            {
                std::cout<<"Quel objectif ? ";
                unsigned int truc;
                while ( ! ( std::cin >> truc ) || truc < 1)
                {
                    std::cout << "Saisie incorrecte, recommencez : ";
                    if ( std::cin.fail() )
                    {
                        std::cin.clear();
                        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                    }
                }
                while (IAs.gener()<truc) {}
                break;
            }
            case 3 :
            {
                std::cout<<"Afficher chaque individu ? [0: Non ; 1:Oui] :";
                bool aff=false;
                while ( ! ( std::cin >> argument ) || argument < 0 || argument>1)
                {
                    std::cout << "Saisie incorrecte, recommencez : ";
                    if ( std::cin.fail() )
                    {
                        std::cin.clear();
                        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                    }
                }
                if(argument==1)
                    aff=true;
                std::cout<<"Afficher le maximum ? [0: Non ; 1:Oui] :";
                while ( ! ( std::cin >> argument ) || argument < 0 || argument>1)
                {
                    std::cout << "Saisie incorrecte, recommencez : ";
                    if ( std::cin.fail() )
                    {
                        std::cin.clear();
                        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                    }
                }
                IAs.setParamAff(4,aff,argument==1);
                break;
            }
            case 4 :
                IACplx IAc(IAs.getEvolutor(),&generateur);
                IAc.setParamAff(4,false,false);
                while(true)
                {
                    std::cout<<"Pour lancer un nombre defini de generations, entrez 1. Pour lancer jusqu'a atteindre un objectif donne, entrez 2. Pour changer les parametres, 3 : ";
                    while ( ! ( std::cin >> argument ) || argument < 1 || argument > 4 )
                    {
                        std::cout << "Saisie incorrecte, recommencez : ";
                        if ( std::cin.fail() )
                        {
                            std::cin.clear();
                            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                        }
                    }
                    switch (argument)
                    {
                    case 1:
                        std::cout<<"Combien de generations ? ";
                        while ( ! ( std::cin >> argument ) || argument < 1)
                        {
                            std::cout << "Saisie incorrecte, recommencez : ";
                            if ( std::cin.fail() )
                            {
                                std::cin.clear();
                                std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                            }
                        }
                        for (int i=0;i<argument;i++)
                        {
                            IAc.gener();
                        }
                        break;
                    case 2:
                        std::cout<<"Quel objectif ? ";
                        unsigned int truc;
                        while ( ! ( std::cin >> truc ) || truc < 1)
                        {
                            std::cout << "Saisie incorrecte, recommencez : ";
                            if ( std::cin.fail() )
                            {
                                std::cin.clear();
                                std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                            }
                        }
                        while (IAc.gener()<truc) {}
                        break;
                    case 3 :
                        std::cout<<"Afficher chaque individu ? [0: Non ; 1:Oui] :";
                        bool aff=false;
                        while ( ! ( std::cin >> argument ) || argument < 0 || argument>1)
                        {
                            std::cout << "Saisie incorrecte, recommencez : ";
                            if ( std::cin.fail() )
                            {
                                std::cin.clear();
                                std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                            }
                        }
                        if(argument==1)
                            aff=true;
                        std::cout<<"Afficher le maximum ? [0: Non ; 1:Oui] :";
                        while ( ! ( std::cin >> argument ) || argument < 0 || argument>1)
                        {
                            std::cout << "Saisie incorrecte, recommencez : ";
                            if ( std::cin.fail() )
                            {
                                std::cin.clear();
                                std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                            }
                        }
                        IAc.setParamAff(4,aff,argument==1);
                        break;
                    }
                }
                break;
            }
        }
        break;
    }
    case 2:

        IACplx IAc(&generateur);
        IAc.setParamAff(4,false,false);
        while(true)
        {
            std::cout<<"Pour lancer un nombre defini de generations, entrez 1. Pour lancer jusqu'a atteindre un objectif donne, entrez 2. Pour changer les parametres, 3 : ";
            while ( ! ( std::cin >> argument ) || argument < 1 || argument > 4 )
            {
                std::cout << "Saisie incorrecte, recommencez : ";
                if ( std::cin.fail() )
                {
                    std::cin.clear();
                    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                }
            }
            switch (argument)
            {
            case 1:
                std::cout<<"Combien de generations ? ";
                while ( ! ( std::cin >> argument ) || argument < 1)
                {
                    std::cout << "Saisie incorrecte, recommencez : ";
                    if ( std::cin.fail() )
                    {
                        std::cin.clear();
                        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                    }
                }
                for (int i=0;i<argument;i++)
                {
                    IAc.gener();
                }
                break;
            case 2:
                std::cout<<"Quel objectif ? ";
                unsigned int obj;
                while ( ! ( std::cin >> obj ) || obj < 1)
                {
                    std::cout << "Saisie incorrecte, recommencez : ";
                    if ( std::cin.fail() )
                    {
                        std::cin.clear();
                        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                    }
                }
                while (IAc.gener()<obj) {}
                break;
            case 3 :
                std::cout<<"Afficher chaque individu ? [0: Non ; 1:Oui] :";
                bool aff=false;
                while ( ! ( std::cin >> argument ) || argument < 0 || argument>1)
                {
                    std::cout << "Saisie incorrecte, recommencez : ";
                    if ( std::cin.fail() )
                    {
                        std::cin.clear();
                        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                    }
                }
                if(argument==1)
                    aff=true;
                std::cout<<"Afficher le maximum ? [0: Non ; 1:Oui] :";
                while ( ! ( std::cin >> argument ) || argument < 0 || argument>1)
                {
                    std::cout << "Saisie incorrecte, recommencez : ";
                    if ( std::cin.fail() )
                    {
                        std::cin.clear();
                        std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                    }
                }
                IAc.setParamAff(4,aff,argument==1);
                break;
            }
        }
        break;
    }
}
