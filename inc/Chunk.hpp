#pragma once
#include "Node.hpp"
#include "TileMap.hpp"
#include "NPC.hpp"
#include "NPCCreator.hpp"

#include <fstream>
#include <random>

const int amountOfChunkTemplates = 3;

// SETTINGS
const sf::Vector2i TileSize = {16,16};
const sf::Vector2f TileMapScale = {0.5f, 0.5f};

class Chunk : public Node
{
private:
    sf::Vector2i size;
    TileMap tileMap;

    sf::Vector2i WorldChunkSize =
    {TileSize.x * TileMapScale.x * 32,
    TileSize.y * TileMapScale.y * 32};

public:
    sf::Vector2i getWorldChunkSize();

    std::shared_ptr<std::ifstream> loadChunk(std::shared_ptr<sf::Texture> _tileSet);

    Chunk();
    Chunk(std::shared_ptr<sf::Texture> _tileSet);
    ~Chunk();

protected:
};
