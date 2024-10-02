#include <iostream>
#include <raylib.h>
#include <deque>
#include <raymath.h>
using namespace std;

// Samostalno definirane boje (r, g, b, alpha)
Color Green = { 173, 204, 96, 255 };
Color DarkGreen = { 43, 52, 24, 255 };

// Dimenzije ćelija
int CellSize = 30;
int CellCount = 25;
double LastUpdateTime = 0;
int OffSet = 75;//sirina bordera oko game Frame-a

bool ElementInDeque(Vector2 element, deque<Vector2> dequeSnake)
{
    for (unsigned int i = 0; i < dequeSnake.size(); i++)
    {
        if (Vector2Equals(dequeSnake[i], element))
        {
            return true;
        }
    }
    return false;
}
bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - LastUpdateTime >= interval)
    {
        LastUpdateTime = currentTime;
        return true;
    }
    return false;
}

class Food {
public:
    Vector2 position;
    Texture2D texture;

    Food(deque<Vector2> snakeBody)
    {
        Image image = LoadImage("Apple_Logo1.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos(snakeBody);//ovdje je snake body komparator argument, u odnosu n akoga cemo usporedivat poziciju hrane
    }

    ~Food() {
        UnloadTexture(texture);
    }

    void Draw() {
        DrawTexture(texture, OffSet + position.x * CellSize, OffSet + position.y * CellSize, WHITE);
    }

    Vector2 GenerateRandomCell()
    {
        float x = GetRandomValue(0, CellCount - 1);
        float y = GetRandomValue(0, CellCount - 1);
        return Vector2{ x, y };
    }

    Vector2 GenerateRandomPos(deque<Vector2> snakeBody)
    {
        Vector2 position = GenerateRandomCell();
        while (ElementInDeque(position, snakeBody))
        {
            position = GenerateRandomCell();
        }
        return position;
    }
};

class Snake
{
public:
    deque<Vector2> body = { Vector2{6,9}, Vector2{5,9}, Vector2{4,9} };
    Vector2 direction = { 1,0 };
    bool addSegment = false;

    void Draw()
    {
        for (unsigned int i = 0; i < body.size(); i++)
        {
            int x = body[i].x;
            int y = body[i].y;
            Rectangle SnakeRectangleBodySegment = Rectangle{ OffSet + (float)x * CellSize, OffSet + (float)y * CellSize, (float)CellSize, (float)CellSize };
            DrawRectangleRounded(SnakeRectangleBodySegment, 0.4, 10, DarkGreen);
        }
    }

    void Update()
    {
        // Dodajemo novi segment ako je potrebno
        if (addSegment)
        {
            body.push_front(Vector2Add(body[0], direction)); // Novi segment ide naprijed,micemo tijelo
            addSegment = false; // restartiramo flag
        }
        else
        {
            body.pop_back(); // Uklanjamo zadnji segment
            body.push_front(Vector2Add(body[0], direction)); // pomicemo tijelo zmije
        }
    }
    void Reset()
    {
        body = { Vector2{6,9}, Vector2{5,9}, Vector2{4,9} };
        direction = { 1,0 };
    }
};

class Game
{
public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = true;
    int ScoreCounter = 0;

    void Draw()
    {
        food.Draw();
        snake.Draw();
    }

    void Update()
    {
        if (running == true)
        {
            snake.Update();
            CheckCollisionWithFood();
            CheckCollisionWithEnd();
            CheckCollisionWithTail();
        }
    }

    void CheckCollisionWithFood()
    {
        if (Vector2Equals(snake.body[0], food.position))
        {
            ScoreCounter++;
            cout << "Food eaten!" << endl;
            food.position = food.GenerateRandomPos(snake.body);
            snake.addSegment = true; // Omogućavamo dodavanje novog segmenta
        }
    }


    void CheckCollisionWithEnd()
    {
        if (snake.body[0].x == CellCount || snake.body[0].x == -1)
        {
            //game is over
            GameOver();
        }
        if (snake.body[0].y == CellCount || snake.body[0].y == -1)
        {
            //game is over
            GameOver();
        }
    }

    void CheckCollisionWithTail()
    {
        deque<Vector2> HeadLessBody = snake.body;
        HeadLessBody.pop_front();
        if (ElementInDeque(snake.body[0], HeadLessBody))
        {
            GameOver();
        }
    }

    void GameOver()
    {
        snake.Reset();//metoda vraca zmiju nakon izgublje partije na pocetne pozicije
        food.position = food.GenerateRandomPos(snake.body);//metoda postavlja hranu na random poziciju
        running = false;//postavlja se flag na stop, i nece se pokrenit dok se ne takne neka od tipki
        cout << "Game Over, your score is " << ScoreCounter << endl;
        ScoreCounter = 0;
    }
};

int main() {
    InitWindow(OffSet * 2 + CellSize * CellCount, OffSet * 2 + CellSize * CellCount, "Snake Game");

    SetTargetFPS(40);

    Game game;//glavni objekt igre

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Green);

        if (EventTriggered(0.2))
        {
            game.Update();
        }

        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1)
        {
            game.snake.direction = { 0,-1 };
            game.running = true;
        }
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1)
        {
            game.snake.direction = { 0,1 };
            game.running = true;
        }
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1)
        {
            game.snake.direction = { -1,0 };
            game.running = true;
        }
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1)
        {
            game.snake.direction = { 1,0 };
            game.running = true;
        }

        ClearBackground(Green);
        DrawRectangleLinesEx(Rectangle{ (float)OffSet - 5,(float)OffSet - 5,(float)CellSize * CellCount + 10,CellSize * (float)CellCount + 10 }, 5, DarkGreen);
        DrawText("Snake Game", 15 * CellSize, 20, 50, DarkGreen);
        DrawText(TextFormat("%i", game.ScoreCounter), 180, OffSet * 2 + CellSize * CellCount - 52, 50, DarkGreen);
        DrawText("Score:", 20, OffSet * 2 + CellSize * CellCount - 50, 40, DarkGreen);

        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
