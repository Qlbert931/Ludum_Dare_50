#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Node.hpp"
#include "Button.hpp"
#include "TextButton.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(840, 600), "GAME", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);

    sf::Font font;

    sf::Text text("przycisk", font);
    text.setFillColor(sf::Color::Red);
    text.setCharacterSize(50);
    
    if (!font.loadFromFile("res/Comic_Book.otf"))
    {
        std::cerr << "font errore!\n";
        return 0;
    }


    Node root;
    std::shared_ptr<Node> player = std::make_shared<Node>(Node()); 
    std::shared_ptr<TextButton> button = std::make_shared<TextButton>(TextButton({ 0,0 }, { 300,200 }, text));
    root.addChild(player);
    player->addChild(button);
    
 
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                break;

                case sf::Event::Resized:
                {
                    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    window.setView(sf::View(visibleArea));
                }
                break;

                case sf::Event::KeyPressed:
                {
                    if (event.key.code == sf::Keyboard::Right)
                    {
                        //player->move({0.0,10.0});
                        player->move({10.0,0.0});
                    }

                    if (event.key.code == sf::Keyboard::Up)
                    {
                        player->rotate(30.0);
                    }

                    if (event.key.code == sf::Keyboard::Down)
                    {
                        player->scale({2.0,0.5});
                    }
                }
            }
        }

        button->isPressed(window);

        window.clear();

        root.draw(window);
        
        window.display();
    }
}
