#pragma once
#include "Node.hpp"
#include "TileMap.hpp"

#include <fstream>
#include <random>

const int amountOfChunkTemplates = 2;

// SETTINGS
const sf::Vector2i TileSize = {16,16};
const sf::Vector2f TileMapScale = {5.f, 5.f};

class Chunk : public Node
{
private:
    sf::Vector2i size;
    TileMap tileMap;

    sf::Vector2i WorldChunkSize;

public:
    sf::Vector2i getWorldChunkSize();

    Chunk(std::shared_ptr<sf::Texture> _tileSet);
    ~Chunk();

protected:
};