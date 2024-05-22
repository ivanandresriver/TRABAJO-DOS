#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

enum GameState {
    RUNNING,
    GAME_OVER
};

class GameObject {
public:
    int x, y;

    GameObject(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

void drawObject(char c, int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << c;
}

void clearObject(int x, int y) {
    drawObject(' ', x, y);
}

void drawBorder() {
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        drawObject('-', i, 0);
        drawObject('-', i, SCREEN_HEIGHT - 1);
    }

    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        drawObject('|', 0, i);
        drawObject('|', SCREEN_WIDTH - 1, i);
    }
}

void updateObjects(GameObject& player, GameObject& obstacle, int& score) {
    if (player.y == 0) {
        player.y = SCREEN_HEIGHT - 3;
    }

    if (player.y > 0) {
        player.y--;
    }

    if (obstacle.x == -1) {
        obstacle.x = SCREEN_WIDTH;
        obstacle.y = rand() % (SCREEN_HEIGHT - 3) + 1;
        score++;
    }

    obstacle.x--;
}

bool checkCollision(GameObject& player, GameObject& obstacle) {
    if (player.x == obstacle.x && player.y == obstacle.y) {
        return true;
    }

    return false;
}

int main() {
    srand(time(NULL));

    GameState gameState = RUNNING;
    GameObject player(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 3);
    GameObject obstacle(SCREEN_WIDTH, rand() % (SCREEN_HEIGHT - 3) + 1);
    int score = 0;

    drawBorder();
    drawObject('R', player.x, player.y);
    drawObject('x', obstacle.x, obstacle.y);

    while (gameState == RUNNING) {
        if (_kbhit()) {
            char key = _getch();

            if (key == ' ') {
                player.y = 0;
            }
        }

        updateObjects(player, obstacle, score);

        if (checkCollision(player, obstacle)) {
            gameState = GAME_OVER;
        }

        clearObject(player.x, player.y);
        drawObject('R', player.x, player.y);
        clearObject(obstacle.x, obstacle.y);
        drawObject('x', obstacle.x, obstacle.y);

        cout << "Puntaje: " << score << endl;
        Sleep(50);
    }

    cout << "Game Over! Tu puntaje fue: " << score << endl;

    return 0;
}