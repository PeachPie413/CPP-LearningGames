#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<string>
#include <vector>
using namespace std;

enum class Direction {
    north, east, south, west
};

struct vec2 {
    int x, y;

    vec2(int x, int y) {
        this->x = x;
        this->y = y;
    }
};


const sf::Color snakeColor = sf::Color(230, 230, 0);
//how many pixels each square should be
const int squarePixSize = 20;
//shapes for saying how to draw tiles
sf::RectangleShape snakeSegmentShape;

//length of one side of the map
int mapSize = 20;

//snake stuff
int snakeLength = 1;
vector<sf::Vector2i> snakeSegments = vector<sf::Vector2i>();
sf::Vector2i foodPos;
sf::Clock moveSnakeClock;
float timeBetweenSnakeMovements = .2f;
Direction curSnakeDirection = Direction::south;

//graphics
sf::RenderWindow window;



//draw the map
void DrawMap() {

    window.clear();

    for (sf::Vector2i snakePos : snakeSegments) {

        //draw each segment of the snake
        snakeSegmentShape.setPosition((sf::Vector2f)(snakePos * squarePixSize));
        window.draw(snakeSegmentShape);
    }
    
    window.display();
}

void ResetGame() {

}

void AdvanceSnake() {

    //if it's too soon, then dont do anything
    if (moveSnakeClock.getElapsedTime().asSeconds() < timeBetweenSnakeMovements) return;

    //reset clock
    moveSnakeClock.restart();

    //get new snake segment
    sf::Vector2i addMoveDir;
    switch (curSnakeDirection)
    {
    case Direction::north:
        addMoveDir = sf::Vector2i(0, -1);
        break;
    case Direction::east:
        addMoveDir = sf::Vector2i(1, 0);
        break;
    case Direction::south:
        addMoveDir = sf::Vector2i(0, 1);
        break;
    case Direction::west:
        addMoveDir = sf::Vector2i(-1, 0);
        break;
    default:
        break;
    }

    sf::Vector2i newHeadPos = addMoveDir + snakeSegments.back();

    //if new snake tile is off the map, move it to the other side
    if (newHeadPos.x >= mapSize) newHeadPos.x = 0;
    if (newHeadPos.x < 0) newHeadPos.x = mapSize;
    if (newHeadPos.y >= mapSize) newHeadPos.y = 0;
    if (newHeadPos.y < 0) newHeadPos.y = mapSize;

    //append it to the snake
    snakeSegments.push_back(newHeadPos);

    //remove last snake segment
    snakeSegments.erase(snakeSegments.begin());
}

void GetInput() {

    //get event type and respond accordingly
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) curSnakeDirection = Direction::north;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) curSnakeDirection = Direction::south;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) curSnakeDirection = Direction::west;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) curSnakeDirection = Direction::east;
    }
}

//init game
void Init() {

    snakeSegments.push_back(sf::Vector2i(1, 1));
    snakeSegments.push_back(sf::Vector2i(1, 1));
    snakeSegments.push_back(sf::Vector2i(1, 1));
    snakeSegments.push_back(sf::Vector2i(1, 1));

    //create shapes to draw tiles
    sf::Vector2f tileVecSize(squarePixSize, squarePixSize);
    snakeSegmentShape = sf::RectangleShape(tileVecSize);
    snakeSegmentShape.setFillColor(snakeColor);
    

    //create window
    //set window to be map size
    window.create(sf::VideoMode(mapSize * squarePixSize, mapSize * squarePixSize), "Snake!", sf::Style::Close);
}

//main
int main()
{
    Init();

    while (window.isOpen())
    {
        GetInput();

        AdvanceSnake();

        DrawMap();
    }

    return 0;
}