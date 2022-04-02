#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<string>
#include <vector>
using namespace std;

enum class TileType {
    empty, snake, food
};

struct vec2 {
    int x, y;

    vec2(int x, int y) {
        this->x = x;
        this->y = y;
    }
};


const sf::Color backgroundColor = sf::Color(0, 0, 0);
//how many pixels each square should be
const int squarePixSize = 20;
//shapes for saying how to draw tiles
sf::RectangleShape emptyTileShape;
const sf::Color emptyTileColor = sf::Color(255, 255, 255);

//length of one side of the map
int mapSize = 10;
TileType mapData[100] = {TileType::empty};

int snakeLength = 1;
vector<int> snakeSegments;
sf::RenderWindow window;


//get linear pos from xy pos
int CartesianToLinear(vec2 input) {

    return input.x * mapSize + input.y;
}

//draw the map
void DrawMap() {

    window.clear();

    for (int x = 0; x < mapSize; x++)
    {
        for (int y = 0; y < mapSize; y++)
        {
            vec2 tilePos = vec2(x,y);
            sf::Vector2f tileDrawPos = sf::Vector2f(x * squarePixSize, y * squarePixSize);

            //get map data
            TileType type = mapData[CartesianToLinear(tilePos)];

            //draw tile
            switch (type)
            {
            case TileType::empty:
                emptyTileShape.setPosition(tileDrawPos);
                window.draw(emptyTileShape);
                break;
            case TileType::snake:
                break;
            case TileType::food:
                break;
            default:
                break;
            }
        }
    }
}

//init game
void Init() {

    //create shapes to draw tiles
    sf::Vector2f tileVecSize(squarePixSize, squarePixSize);
    emptyTileShape.setFillColor(emptyTileColor);
    emptyTileShape.setSize(tileVecSize);
    emptyTileShape.setOutlineThickness(10);
    emptyTileShape.setOutlineColor(backgroundColor);
    

    window.create(sf::VideoMode(mapSize * squarePixSize, mapSize * squarePixSize), "Snake!");
}

//main
int main()
{
    Init();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        DrawMap();

        window.display();
    }

    return 0;
}