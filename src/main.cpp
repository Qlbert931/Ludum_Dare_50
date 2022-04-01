#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Progressbar.hpp"
#include "MouseChangeableProgressbar.hpp"
#include "Resolution.hpp"
#include "Node.hpp"
#include "Button.hpp"
#include "TextButton.hpp"
#include "Container.hpp"
#include "LevelLoader.hpp"

#include "MovingCircle.hpp"

int main()
{
    Resolution resolution(Resolution::resolution::_1280x720);
    sf::RenderWindow window(resolution.getDefault(), "GAME", sf::Style::Close | sf::Style::Titlebar);

    sf::Font font;

    if (!font.loadFromFile("res/Comic_Book.otf"))
    {
        std::cerr << "font errore!\n";
        return 0;
    }

    sf::Text buttonText("place holder", font);
    buttonText.setFillColor(sf::Color::Red);
    buttonText.setCharacterSize(20);

    std::shared_ptr<MovingCircle> circle = std::make_shared<MovingCircle>(MovingCircle({ 100,100 }, 100));
    circle->setVelocity({ 10.f,10.f });

    std::unique_ptr<LevelLoader> root = std::make_unique<LevelLoader>(LevelLoader());
    root->setName("root");

    std::shared_ptr<Node> mainMenu = std::make_shared<Node>(Node());
    std::shared_ptr<Node> secondaryMenu = std::make_shared<Node>(Node());
        
    root->addLevel(mainMenu);
    root->addLevel(secondaryMenu);

    secondaryMenu->addChild(circle);

    buttonText.setString("1280 x 720");
    std::shared_ptr<TextButton> _1280x720button = std::make_shared<TextButton>(TextButton({ 50,200 }, { 200,100 }, buttonText));
    _1280x720button->setName("_1280x720button");

    buttonText.setString("1336 x 768");
    std::shared_ptr<TextButton> _1336x768button = std::make_shared<TextButton>(TextButton({ 300,200 }, { 200,100 }, buttonText));
    _1336x768button->setName("_1336x768button");

    buttonText.setString("1600 x 900");
    std::shared_ptr<TextButton> _1600x900button = std::make_shared<TextButton>(TextButton({ 550,200 }, { 200,100 }, buttonText));
    _1600x900button->setName("_1600x900button");

    buttonText.setString("1900 x 1080");
    std::shared_ptr<TextButton> _1900x1080button = std::make_shared<TextButton>(TextButton({ 800,200 }, { 200,100 }, buttonText));
    _1900x1080button->setName("_1900x1080button");

    std::shared_ptr<MouseChangeableProgressbar> progressbar = std::make_shared<MouseChangeableProgressbar>(1000.0f, 50.0f, sf::Color(100, 100, 100), sf::Color(200, 200, 200));
    progressbar->setName("progressbar");

    std::shared_ptr<Container> container = std::make_shared<Container>();
    container->setName("container");

    container->addChild(_1280x720button);
    container->addChild(_1336x768button);
    container->addChild(_1600x900button);
    container->addChild(_1900x1080button);
    mainMenu->addChild(progressbar);
    mainMenu->addChild(container);

    container->translate({ 100, 100 });
    progressbar->translate({ 100, 100 });

    sf::Text text("przycisk", font);
    text.setFillColor(sf::Color::Red);
    text.setCharacterSize(50);

    mainMenu->printTree();

    if (!font.loadFromFile("res/Comic_Book.otf"))
    {
        std::cerr << "font errore!\n";
        return 0;
    }

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Num1)
                {
                    root->setLevel(0);
                }
                else if (event.key.code == sf::Keyboard::Num2)
                {
                    root->setLevel(1);
                }
                break;
            }
        }


        progressbar->update(window);

        if (_1280x720button->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1280x720, window);
            root->resize(resolution);
            _1280x720button->printDebug();
        }

        if (_1336x768button->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1336x768, window);
            root->resize(resolution);
            _1280x720button->printDebug();
        }

        if (_1600x900button->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1600x900, window);
            root->resize(resolution);
            _1280x720button->printDebug();
        }

        if (_1900x1080button->isPressed(window))
        {
            resolution.changeResolution(Resolution::resolution::_1920x1080, window);
            root->resize(resolution);
            _1280x720button->printDebug();
        }

        sf::Time delta = deltaClock.restart();
        window.clear();

        root->update(delta);
        root->draw(window);

        window.display();
    }
}