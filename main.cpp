/*#include <raylib.h>
#include <string>

#define window_dimension_reduction_factor 0.7
#define acceleration_due_to_gravity 9.8


void logic();
void draw_2d_grid(int, int, int);
void generate_ball_at_position(float, float, float, Color);


class Ball{
    private:

    bool active;
    Color color;
    float radius;
    float velocity_x;
    float velocity_y;
    float coordinate_x;
    float coordinate_y;

    public:

    Ball(Color color, float radius, float coordinate_x, float coordinate_y, float velocity_x, float velocity_y){
        this->color = color;
        this->radius = radius;
        this->coordinate_x = coordinate_x;
        this->coordinate_y = coordinate_y;
        this->velocity_x = velocity_x;
        this->velocity_y = velocity_y;
    }
    Ball(Color color, float radius, float coordinate_x, float coordinate_y){
        this->color = color;
        this->radius = radius;
        this->coordinate_x = coordinate_x;
        this->coordinate_y = coordinate_y;
        this->velocity_x = 0.0f;
        this->velocity_y = 0.0f;
    }

    bool is_active() const{
        return active;
    }

    void destroy(){
        active = false;
    }

    void set_velocity_x(float velocity_x){
        this->velocity_x = velocity_x;
    }

    void set_velocity_y(float velocity_y){
        this->velocity_y = velocity_y;
    }

    void set_coordinate_x(float coordinate_x){
        this->coordinate_x = coordinate_x;
    }

    void set_coordinate_y(float coordinate_y){
        this->coordinate_y = coordinate_y;
    }

    float get_radius() const{
        return radius;
    }
    float get_coordinate_x() const{
        return coordinate_x;
    }
    float get_coordinate_y() const{
        return coordinate_y;
    }
    float get_velocity_x() const{
        return velocity_x;
    }
    float get_velocity_y() const{
        return velocity_y;
    }
    Color get_color() const{
        return color;
    }

};

class Window{
    private:
    int width;
    int height;
    std::string title;

    public:

    Window(int width, int height, std::string_view title){
        this->width = width;
        this->height = height;
        this->title = title;
    }
    Window(std::string title){
        InitWindow(0, 0, title.c_str());
        this->width = GetScreenWidth() * window_dimension_reduction_factor ;
        this->height = GetScreenHeight() * window_dimension_reduction_factor;
        CloseWindow();
        this->title = title;
    }

    int get_width() const{
        return width;
    }
    int get_height() const{
        return height;
    }
    std::string get_title() const{
        return title;
    }
};

std::string title = "Ball on a window";
Window window(title); //Initialized width and title already in this constructor call
Ball ball(DARKBLUE, 30.0f, 630.0f, 300.0f);
const float velocity_x = 1.0f;
const float velocity_y = 1.0f;


int main() {
    std::string title = "Ball on a Window";
    Window window(title); // Move object creation inside main

    InitWindow(window.get_width(), window.get_height(), window.get_title().c_str());
    SetTargetFPS(60);

    bool game_started = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        if (!game_started) {
            DrawText("Press space to start", window.get_width() * 0.1, window.get_height() * 0.4, 100, DARKGREEN);
            DrawText("the simulation", window.get_width() * 0.2, window.get_height() * 0.5, 100, DARKGREEN);

            if (IsKeyPressed(KEY_SPACE)) game_started = true;
        } else {
            logic();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}


void logic() {
    draw_2d_grid(29, window.get_width(), window.get_height());

    // Update velocity due to gravity
    ball.set_velocity_y(ball.get_velocity_y() + acceleration_due_to_gravity * GetFrameTime());

    // Update position
    ball.set_coordinate_x(ball.get_coordinate_x() + ball.get_velocity_x());
    ball.set_coordinate_y(ball.get_coordinate_y() + ball.get_velocity_y());

    // Collision with window boundaries
    if (ball.get_coordinate_x() + ball.get_radius() >= window.get_width() || ball.get_coordinate_x() - ball.get_radius() <= 0) {
        ball.set_velocity_x(-ball.get_velocity_x());
    }
    if (ball.get_coordinate_y() + ball.get_radius() >= window.get_height() || ball.get_coordinate_y() - ball.get_radius() <= 0) {
        ball.set_velocity_y(-ball.get_velocity_y());
    }

    // Draw the ball after updating
    generate_ball_at_position(ball.get_coordinate_x(), ball.get_coordinate_y(), ball.get_radius(), ball.get_color());
}


void draw_2d_grid(int cellSize, int screenWidth, int screenHeight) {
    for (int x = 0; x <= screenWidth; x += cellSize)
    
        DrawLine(x, 0, x, screenHeight, BLACK); // Vertical lines

    for (int y = 0; y <= screenHeight; y += cellSize)
        DrawLine(0, y, screenWidth, y, BLACK); // Horizontal lines
}

void generate_ball_at_position(float coordinate_x, float coordinate_y, float radius, Color color){
    DrawCircle(coordinate_x, coordinate_y, radius, color);

}*/

#include <raylib.h>
#include <string>

#define window_dimension_reduction_factor 0.7
#define acceleration_due_to_gravity 9.8

void draw_2d_grid(int, int, int);
void generate_ball_at_position(float, float, float, Color);

class Ball {
private:
    bool active;
    Color color;
    float radius;
    float velocity_x;
    float velocity_y;
    float coordinate_x;
    float coordinate_y;

public:
    Ball(Color color, float radius, float coordinate_x, float coordinate_y, float velocity_x = 5.0f, float velocity_y = 5.0f)
        : color(color), radius(radius), coordinate_x(coordinate_x), coordinate_y(coordinate_y), velocity_x(velocity_x), velocity_y(velocity_y), active(true) {}

    bool is_active() const { return active; }

    void destroy() { active = false; }

    void update(float delta_time, int window_width, int window_height) {
        velocity_y += acceleration_due_to_gravity * delta_time;

        coordinate_x += velocity_x * delta_time;
        coordinate_y += velocity_y * delta_time;

        // Collision with window boundaries
        if (coordinate_x + radius >= window_width || coordinate_x - radius <= 0) {
            velocity_x = -velocity_x;
            coordinate_x = (coordinate_x + radius >= window_width) ? window_width - radius : radius;
        }
        if (coordinate_y + radius >= window_height || coordinate_y - radius <= 0) {
            velocity_y = -velocity_y;
            coordinate_y = (coordinate_y + radius >= window_height) ? window_height - radius : radius;
        }
    }

    void draw() const {
        DrawCircle(coordinate_x, coordinate_y, radius, color);
    }
};

class Window {
private:
    int width;
    int height;
    std::string title;

public:
    Window(std::string title) {
        InitWindow(0, 0, title.c_str());
        width = GetScreenWidth() * window_dimension_reduction_factor;
        height = GetScreenHeight() * window_dimension_reduction_factor;
        CloseWindow();
        this->title = title;
    }

    int get_width() const { return width; }
    int get_height() const { return height; }
    std::string get_title() const { return title; }
};

class Game {
private:
    Window window;
    Ball ball;
    bool game_started;

public:
    Game() : window("Ball on a Window"), ball(DARKBLUE, 30.0f, 630.0f, 300.0f, 1.0f, 1.0f), game_started(false) {
        InitWindow(window.get_width(), window.get_height(), window.get_title().c_str());
        SetTargetFPS(60);
    }

    ~Game() {
        CloseWindow();
    }

    void run() {
        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(LIGHTGRAY);

            if (!game_started) {
                DrawText("Press space to start", window.get_width() * 0.1, window.get_height() * 0.4, 100, DARKGREEN);
                DrawText("the simulation", window.get_width() * 0.2, window.get_height() * 0.5, 100, DARKGREEN);

                if (IsKeyPressed(KEY_SPACE)) game_started = true;
            } else {
                logic();
            }

            EndDrawing();
        }
    }

    void logic() {
        draw_2d_grid(29, window.get_width(), window.get_height());
        ball.update(GetFrameTime(), window.get_width(), window.get_height());
        ball.draw();
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}

void draw_2d_grid(int cell_size, int screen_width, int screen_height) {
    for (int x = 0; x <= screen_width; x += cell_size)
        DrawLine(x, 0, x, screen_height, BLACK); // Vertical lines

    for (int y = 0; y <= screen_height; y += cell_size)
        DrawLine(0, y, screen_width, y, BLACK); // Horizontal lines
}

void generate_ball_at_position(float coordinate_x, float coordinate_y, float radius, Color color) {
    DrawCircle(coordinate_x, coordinate_y, radius, color);
}

