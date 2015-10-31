
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>
#include <iostream>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"

int getIntRandom(int min, int max)
{
    std::random_device generator;
    std::uniform_int_distribution<int> distribution(min,max);
    
    return distribution(generator);
}

sf::Image rotation(const sf::Image& image)
{
    
    sf::Image toReturn;
    toReturn.create(800, 600);
    
    for(int i = 0; i < 800; i++)
    {
        for(int j = 0; j < 600; j++)
        {
            int xToGet = i;
            int yToGet = (j+6)%600;
            toReturn.setPixel(i,j, image.getPixel(xToGet, yToGet));
        }
    }
    return toReturn;
}

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    /**
     * Bruit de base
     */
    
    sf::Image imagebruitRandom;
    sf::Texture textureBruitRandom;
    sf::Sprite spriteBruitRandom;
    imagebruitRandom.create(800, 600);
    
    for(int i = 0; i < 800; i++)
        for(int j = 0; j < 600; j++)
            if(getIntRandom(0,1) == 1)
                imagebruitRandom.setPixel(i,j, sf::Color::White);
    
    textureBruitRandom.loadFromImage(imagebruitRandom);
    spriteBruitRandom.setTexture(textureBruitRandom);

    /*-----------------------*/
 
    /**
     * Le background
     */
    
    sf::Image backgroundMouvement = imagebruitRandom;
    sf::Texture textureBackgroundMouvement;
    sf::Sprite spriteBackgroundMouvement;
    
    /*------------------------*/
    
    /**
     * Le texte
     */
    
    sf::Text texteEcrit;
    sf::Font fontTexte;
    fontTexte.loadFromFile("/Users/nicolasserf/Desktop/ProjetPersonnel/monPremierBruit/monPremierBruit/sansation.ttf");
    
    texteEcrit.setCharacterSize(100);
    texteEcrit.setColor(sf::Color::White);
    texteEcrit.setString("SALOPE");
    texteEcrit.setFont(fontTexte);
    texteEcrit.setPosition(250, 300);
    
    /*-------------------------*/
    
    /**
     * Texture texte "bruité"
     */
    
    sf::RenderTexture texteBruite;
    texteBruite.create(800, 600);
    texteBruite.draw(texteEcrit);
    texteBruite.display();
    texteBruite.draw(spriteBruitRandom, sf::BlendMultiply);
    texteBruite.display();
    
    sf::Sprite spriteTexteBruite;
    spriteTexteBruite.setTexture(texteBruite.getTexture());
    
    /*-------------------------*/
    
    /**
     * Texture background "bruité"
     */
    
    texteEcrit.setColor(sf::Color::Black); //on va écrire en noir sur fond blanc
    sf::RenderTexture backgroundBruite;
    backgroundBruite.create(800, 600);
    backgroundBruite.clear(sf::Color::White); //Fond blanc
    backgroundBruite.draw(texteEcrit);
    backgroundBruite.display();
    
    /*------------------------*/
    
    /**
     * Réunion du texte bruité et du background bruité
     */
    
    sf::Sprite regroupe;
    
    bool stop = true;

    while (window.isOpen())
    {
        if(stop)
        {
        backgroundMouvement = rotation(backgroundMouvement);
        textureBackgroundMouvement.loadFromImage(backgroundMouvement);
        spriteBackgroundMouvement.setTexture(textureBackgroundMouvement);
        
        backgroundBruite.draw(spriteBackgroundMouvement, sf::BlendMultiply);
        backgroundBruite.display();
        regroupe.setTexture(backgroundBruite.getTexture());
        
        backgroundBruite.draw(spriteTexteBruite, sf::BlendAdd);
        backgroundBruite.display();
        
        regroupe.setTexture(backgroundBruite.getTexture());
        }
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
                if(stop == false)
                    stop = true;
                else
                    stop = false;
            }
        }

        // Clear screen
        window.clear();
        //window.draw(spriteTexteBruite);
        window.draw(regroupe);
        // Update the window
        window.display();
        
        if(stop){
        backgroundBruite.clear(sf::Color::White);
        backgroundBruite.draw(texteEcrit);
        backgroundBruite.display();
        }
    }

    return EXIT_SUCCESS;
}
