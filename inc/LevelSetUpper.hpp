#pragma once
#include <SFML/Graphics.hpp>

#include "LevelLoader.hpp"
#include "Toolkit.hpp"
#include "Y-sort.hpp"
#include "ButtonsContainer.hpp"
#include "WorldView.hpp"

class LevelSetUpper
{
private:
    std::shared_ptr<LevelLoader> game;
    std::shared_ptr<LevelLoader> GUI;
    sf::Font font;
    SoundSystem *soundSystem;

public:
    LevelSetUpper(std::shared_ptr<LevelLoader> _game, std::shared_ptr<LevelLoader> _GUI, sf::Font _font, SoundSystem* _soundSystem);
    void setUp(std::shared_ptr<Node>& level, std::shared_ptr<Node>& levelGUI, std::shared_ptr<ButtonsContainer>& Buttons, LEVEL lv);
};
