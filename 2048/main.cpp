#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

using namespace std;

vector<vector<int>> makeMove(vector<vector<int>>& board, string direction);
void displayBoard(vector<vector<int>>& board);
void addRandomTile(vector<vector<int>>& board);

vector<vector<int>> createBoard(int N) {
    vector<vector<int>> board(4, vector<int> (N));
    addRandomTile(board);
    addRandomTile(board);
    return board;
}

int main() {    
    const int N = 4;
    const int TILE_SIZE = 200;
    const int PADDING = 20;

    vector<vector<int>> board = createBoard(N);

    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "2048");

    sf::Font font;
    if (!font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        return -1; // Make sure you have a valid font path
    }
    bool focused = true;
    while (window.isOpen()) {
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()){
                window.close();
                window.clear(sf::Color(50,50,50));
            }
            else if (event->is<sf::Event::FocusLost>()) {
                focused = false;
            }
            else if (event->is<sf::Event::FocusGained>()) {
                focused = true;
            }
            else if (focused) {
                if (const auto *e = event->getIf<sf::Event::KeyReleased>()) {
                
                        switch (e->scancode) {
                        case sf::Keyboard::Scancode::Left:
                            makeMove(board, "a");
                            break;
                        case sf::Keyboard::Scancode::Right:
                            makeMove(board, "d");
                            break;
                        case sf::Keyboard::Scancode::Up:
                            makeMove(board, "w");
                            break;
                        case sf::Keyboard::Scancode::Down:
                            makeMove(board, "s");
                            break;           
                        case sf::Keyboard::Scancode::R:
                            createBoard(N);
                            break;
                        case sf::Keyboard::Scancode::Q:
                            window.close();
                            window.clear(sf::Color(50,50,50));
                        default:
                            break;
                    }
                }
            }
        }

        for (int i=0; i<N; i++) {
            for (int j=0; j<N; j++) {
                sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                tile.setPosition(sf::Vector2f(
                    PADDING+j*(TILE_SIZE+PADDING),
                    PADDING+i*(TILE_SIZE+PADDING))
                );
                if (board[i][j] == 0)
                    tile.setFillColor(sf::Color(200,200,200));
                else
                    tile.setFillColor(sf::Color(255,200-min(board[i][j]*10, 200), 100));
                window.draw(tile);
                
                sf::Text number(font, to_string(board[i][j]), 50);

                sf::FloatRect textRect = number.getLocalBounds();
                float top = textRect.position.y;
                float left = textRect.position.x;

                number.setOrigin(sf::Vector2f(
                    left + TILE_SIZE/2.0f,
                    top  + TILE_SIZE/2.0f
                    // TILE_SIZE/2.0f,
                    // TILE_SIZE/2.0f
                ));
                number.setPosition(sf::Vector2f(
                    PADDING + j * (TILE_SIZE + PADDING) + TILE_SIZE/2,
                    PADDING + i * (TILE_SIZE + PADDING) + TILE_SIZE/2
                ));
                window.draw(number);
            
            }
        }
        window.display();
    }
        // static_cast<unsigned int>(N*(TILE_SIZE+PADDING)+PADDING),
        // static_cast<unsigned int>(N*(TILE_SIZE+PADDING)+PADDING)),
        // "2048");
    // while (window.isOpen()) {
    //     sf::Event event;
    //     while (window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed) window.close();
    //     }
    //     window.display();
    // }
    // string x;
    // while (true) {
    //     cout << "BOARD\n";
    //     displayBoard(board);
    //     cout << "Move Direction: ";
    //     cin >> x;
    //     if (x=="q") break;
    //     board = makeMove(board, x);
    // };
}