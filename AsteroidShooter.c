#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define MAX_BULLETS 100
#define MAX_ASTEROIDS 100

// Utility function for getting current time in milliseconds
long long getTimeMillis() {
    SYSTEMTIME time;
    GetSystemTime(&time);
    return (time.wSecond * 1000) + time.wMilliseconds;
}

// Player Structure
typedef struct {
    int x, y;
    int health;
    int bulletCount;
    int bulletX[MAX_BULLETS];
    int bulletY[MAX_BULLETS];
} Player;

// Asteroid Structure
typedef struct {
    int x, y;
    int health;
    char shape[6]; // Shape format is like "(n)", max 5 chars, one extra for null terminator
} Asteroid;

// Global variables
Asteroid asteroids[MAX_ASTEROIDS];
int asteroidCount = 0;
int score = 0; // Score counter

// Function to initialize player
void initPlayer(Player* player, int width, int height) {
    player->x = width / 2;
    player->y = height - 2;
    player->health = 3;
    player->bulletCount = 0;
}

// Function to shoot bullet
void shootBullet(Player* player) {
    if (player->bulletCount < MAX_BULLETS) {
        player->bulletX[player->bulletCount] = player->x;
        player->bulletY[player->bulletCount] = player->y - 1;
        player->bulletCount++;
    }
}

// Function to initialize an asteroid
void spawnAsteroid(int width) {
    if (asteroidCount < MAX_ASTEROIDS) {
        int health = rand() % 9 + 1; // Random health between 1 and 9
        // Ensure the asteroid spawns within the borders
        asteroids[asteroidCount].x = rand() % (width - 5) + 1; // Range from 2 to (width - 3)
        asteroids[asteroidCount].y = 0; // Start at top of screen
        asteroids[asteroidCount].health = health;
        sprintf(asteroids[asteroidCount].shape, "{%d}", health); // Format asteroid shape
        asteroidCount++;
    }
}

// Function to move asteroids
void moveAsteroids(Player* player, int height) {
    for (int i = 0; i < asteroidCount; i++) {
        asteroids[i].y += 1; // Move asteroid down

        // Check if asteroid reached the player
        if (asteroids[i].y == player->y && 
            (asteroids[i].x == player->x || asteroids[i].x == player->x - 1 || asteroids[i].x == player->x + 1)) {
            player->health -= 1;
            asteroids[i] = asteroids[asteroidCount - 1]; // Remove asteroid
            asteroidCount--;
            i--;
        } else if (asteroids[i].y >= height) { // Asteroid reaches bottom of the screen
            asteroids[i] = asteroids[asteroidCount - 1]; // Remove asteroid without reducing player health again
            asteroidCount--;
            i--;
        }
    }
}

// Function to move bullets
void moveBullets(Player* player) {
    for (int i = 0; i < player->bulletCount; i++) {
        player->bulletY[i]--;
        if (player->bulletY[i] < 0) { // Remove bullets off screen
            player->bulletX[i] = player->bulletX[player->bulletCount - 1];
            player->bulletY[i] = player->bulletY[player->bulletCount - 1];
            player->bulletCount--;
            i--;
        }
    }
}

// Function to handle bullet-asteroid collisions
void checkCollisions(Player* player) {
    for (int i = 0; i < player->bulletCount; i++) {
        for (int j = 0; j < asteroidCount; j++) {
            // Check if the bullet hits the asteroid's position
            if ((player->bulletX[i] == asteroids[j].x && player->bulletY[i] == asteroids[j].y) || 
                (player->bulletX[i] == asteroids[j].x + 1 && player->bulletY[i] == asteroids[j].y) || 
                (player->bulletX[i] == asteroids[j].x + 2 && player->bulletY[i] == asteroids[j].y)) {
                
                asteroids[j].health--; // Decrease asteroid health

                // Remove the bullet
                player->bulletX[i] = player->bulletX[player->bulletCount - 1];
                player->bulletY[i] = player->bulletY[player->bulletCount - 1];
                player->bulletCount--;
                i--; // Adjust bullet loop to ensure no bullet is skipped

                // Check for health and update the asteroid shape
                if (asteroids[j].health <= 0) {
                    asteroids[j] = asteroids[asteroidCount - 1]; // Replace with last asteroid
                    asteroidCount--;
                    j--; // Adjust the loop to ensure correct iteration
                    score++; // Increment score when an asteroid is destroyed
                } else {
                    sprintf(asteroids[j].shape, "(%d)", asteroids[j].health); // Update the shape
                }

                break; // Exit the inner loop if a bullet has hit an asteroid
            }

            // Check if the bullet hits the numeric part of the asteroid
            if (player->bulletX[i] == asteroids[j].x + 1 && player->bulletY[i] == asteroids[j].y) {
                asteroids[j].health--; // Decrease asteroid health
                player->bulletX[i] = player->bulletX[player->bulletCount - 1];
                player->bulletY[i] = player->bulletY[player->bulletCount - 1];
                player->bulletCount--;
                i--; // Adjust bullet loop to ensure no bullet is skipped

                // Check for health and update the asteroid shape
                if (asteroids[j].health <= 0) {
                    asteroids[j] = asteroids[asteroidCount - 1]; // Replace with last asteroid
                    asteroidCount--;
                    j--; // Adjust the loop to ensure correct iteration
                    score++; // Increment score when an asteroid is destroyed
                } else {
                    sprintf(asteroids[j].shape, "(%d)", asteroids[j].health); // Update the shape
                }

                break; // Exit the inner loop if a bullet has hit an asteroid
            }
        }
    }
}

// Function to draw the game window
void drawGame(Player* player, int width, int height) {
    system("cls");

    // Draw top border
    printf("+");
    for (int i = 0; i < width - 2; i++) printf("-");
    printf("+\n");

    // Draw game area
    for (int i = 0; i < height; i++) {
        printf("|"); // Left border
        for (int j = 0; j < width - 2; j++) {
            if (i == player->y && j == player->x) {
                printf("^"); // Player spaceship
            } else {
                int drawn = 0;

                // Draw bullets
                for (int k = 0; k < player->bulletCount; k++) {
                    if (i == player->bulletY[k] && j == player->bulletX[k]) {
                        printf("|");
                        drawn = 1;
                        break;
                    }
                }

                // Draw asteroids
                for (int k = 0; k < asteroidCount; k++) {
                    if (i == asteroids[k].y && j == asteroids[k].x) {
                        printf("%s", asteroids[k].shape); // Print asteroid shape
                        j += 2; // Skip next two spaces as asteroid occupies 3 chars
                        drawn = 1;
                        break;
                    }
                }

                if (!drawn) printf(" ");
            }
        }
        printf("|\n"); // Right border
    }

    // Draw bottom border
    printf("+");
    for (int i = 0; i < width - 2; i++) printf("-");
    printf("+\n");

    printf("Health: %d\n", player->health);
    printf("Score: %d\n", score); // Display score
}

// Input function to control the player
char getInput() {
    if (_kbhit()) {
        return _getch();
    }
    return ' ';
}

// Function to display the welcome screen
void displayWelcomeScreen() {
    system("cls");
    printf("Welcome to the Asteroid Shooter Game!\n");
    printf("Instructions:\n");
    printf(" - Move left: 'a'\n");
    printf(" - Move right: 'd'\n");
    printf(" - Shoot: 'w'\n");
    printf(" - Quit: 'q'\n");
    printf("Press any key to start...\n");
    _getch(); // Wait for a key press
}

int main() {
    srand(time(NULL));

    displayWelcomeScreen(); // Display the welcome screen

    int width = 30, height = 15;
    int frameRate = 60;
    Player player;
    initPlayer(&player, width, height);

    long long asteroidSpawnTime = getTimeMillis();
    long long asteroidMoveTime = getTimeMillis();
    long long bulletMoveTime = getTimeMillis();

    int gameRunning = 1;

    while (gameRunning) {
        char input = getInput();

        if (input == 'q') gameRunning = 0;
        if (input == 'a' && player.x > 1) player.x--;
        if (input == 'd' && player.x < width - 3) player.x++; // Adjust for border space
        if (input == 'w') shootBullet(&player);

        // Spawn asteroids every 1 seconds
        if (getTimeMillis() - asteroidSpawnTime > 1000) {
            spawnAsteroid(width);
            asteroidSpawnTime = getTimeMillis();
        }

        // Move asteroids every 1.5 seconds
        if (getTimeMillis() - asteroidMoveTime > 1500) {
            moveAsteroids(&player, height);
            asteroidMoveTime = getTimeMillis();
        }

        // Move bullets every 0.1 second
        if (getTimeMillis() - bulletMoveTime > 100) {
            moveBullets(&player);
            bulletMoveTime = getTimeMillis();
        }

        // Check for bullet and asteroid collisions
        checkCollisions(&player);

        // Draw the game window
        drawGame(&player, width, height);

        // End game if player health reaches 0
        if (player.health <= 0) {
            gameRunning = 0;
            printf("Game Over! Your Score: %d\n", score);
        }

        Sleep(1000 / frameRate);
    }

    return 0;
}
