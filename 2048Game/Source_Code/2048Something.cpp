#include "Board.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <conio.h>

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    Board playTable;

    // Init two random tiles
    int firstX = rand() % 4, firstY = rand() % 4;
    playTable.setTile(firstX,firstY,new Tile(2));

    int secondX = rand() % 4, secondY = rand() % 4;
    while (secondX == firstX && secondY == firstY)
        secondX = rand() % 4, secondY = rand() % 4;
    playTable.setTile(secondX, secondY, new Tile(2));
    sf::Music music;
    if (!music.openFromFile("amanojaku.wav"))
        cout << "Loi roi em nhe!" << endl;
    music.play();
    // SFML Window
    sf::RenderWindow window(sf::VideoMode({ 400, 400 }), "2048 - SFML");

    sf::Font font;
    if (!font.openFromFile("OpenSans_Condensed-Bold.ttf")) cout << "Loi roi em nhe!" << endl;
    while (window.isOpen())
    {
        sf::Event event();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            char dir = 0;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) dir = 'a';
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) dir = 'd';
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) dir = 'w';
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) dir = 's';

            if (dir && playTable.move(dir))
            {
                playTable.spamTile();
                playTable.resetMergeFlag();
                sf::sleep(sf::seconds(0.2f));
            }
        }


        // Draw the board
        window.clear(sf::Color::White);
        float cellSize = 100.f;

        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                sf::RectangleShape cell({ cellSize - 4, cellSize - 4 });
                cell.setPosition({ j * cellSize + 2, i * cellSize + 2 });
                cell.setFillColor(sf::Color(200, 200, 200));

                if (playTable.getTile(i,j)) {
                    int val = playTable.getTile(i,j)->getValue();

                    cell.setFillColor(sf::Color(240, 220 - val * 2, 180));
                    sf::Text text(font);
                    text.setFont(font);
                    text.setString(std::to_string(val));
                    text.setCharacterSize(28);
                    text.setFillColor(sf::Color::Black);
                    sf::FloatRect textBounds = text.getLocalBounds();
                    float textWidth = textBounds.size.x;
                    float textHeight = textBounds.size.y;
                    float textLeft = textBounds.position.x;
                    float textTop = textBounds.position.y;
                    float x = j * cellSize + (cellSize - textWidth) / 2.0f - textLeft;
                    float y = i * cellSize + (cellSize - textHeight) / 2.0f - textTop;
                    text.setPosition({ x,y });
                    window.draw(cell);
                    window.draw(text);
                }
                else
                {
                    window.draw(cell);
                }
            }
        }

        window.display();

        if (playTable.checkWin())
        {
            window.setTitle("YOU WIN!");
            sf::sleep(sf::seconds(5));
            return 0;
        }
        else if (playTable.checkLose())
        {
            window.setTitle("YOU LOSE!");
            sf::sleep(sf::seconds(5));
            return 0;
        }

    }

    return 0;
}
