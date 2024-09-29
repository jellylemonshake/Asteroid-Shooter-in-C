# **Asteroid Shooter Game in C**

## Introduction:
This is a simple Asteroid Shooter Game implemented in C. The player controls a spaceship and tries to shoot down incoming asteroids while avoiding collisions. Each asteroid has a health value that determines how many bullets it can withstand before being destroyed. The game tracks the player's score based on the number of asteroids destroyed. The game ends if the spaceship collides with an asteroid.

![Screenshot 2024-09-29 123644](https://github.com/user-attachments/assets/da9960c7-6c1c-4462-9cfd-45a675bd96a6)


## Features:
* Player movement using keyboard controls.
* Random asteroid spawning on the screen, each with its own health.
* Bullet shooting mechanics to destroy asteroids.
* Health tracking for the player's spaceship.
* Score tracking based on the number of asteroids destroyed.

## Controls:
* **a:** Move Left
* **d:** Move Right
* **w:** Shoot
* **q:** Quit Game

## How to Compile and Run
### Requirements:
* A C compiler (e.g., GCC).
* A Windows terminal or command prompt to run the game.
   
### Steps to Compile:
* Save the code in a file named **asteroid_shooter.c**.
* Open a terminal and navigate to the directory where the file is saved.

**Compile the code using this command:**
   
      gcc asteroid_shooter.c -o asteroid_shooter.exe
  
**Run the game with the following command:**

      ./asteroid_shooter.exe
  
## Important Notes:
* The code is written specifically for Windows using **conio.h** and **windows.h** for input handling and screen clearing.
* **system("cls")** is used to clear the console screen, which may not work on non-Windows platforms.
* **Sleep()** is used to control the frame rate of the game.

## Game Rules
1. **Goal:** 
   * Control the spaceship and shoot down as many asteroids as possible to increase your score.
2. **Game Over Conditions:**
   * The spaceship collides with an asteroid.
   * The player's health reaches zero.

## Game Mechanics
* **Asteroid Health:** 
  Each asteroid has a health value that ranges from 1 to 9. Players must shoot an asteroid multiple times to destroy it, depending on its health. When an asteroid's health reaches zero, it is removed from the game, and the player scores a point.

## Game Loop
* **Input Handling:**
  The player can move the spaceship left or right and shoot bullets at the asteroids using the corresponding keys.
* **Asteroid Movement:**
  Asteroids continuously move downwards towards the player's position, and their spawning is randomized.
* **Collision Detection:**
  The game checks for collisions between the bullets and asteroids, as well as the spaceship and asteroids, after each movement.
* **Bullet Management:**
  The player can shoot bullets to destroy asteroids, which also updates the score accordingly.
* **Drawing the Game:**
  The game window is redrawn after each movement, displaying the current state of the player, bullets, asteroids, health, and score.

## Future Improvements
* Adding different types of asteroids with varying properties.
* Implementing power-ups to enhance player abilities.
* Introducing a high score system for tracking player performance.
