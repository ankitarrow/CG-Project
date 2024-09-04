#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>

// Bird properties
int birdX = 100, birdY = 200, gravity = 2, lift = -15, birdDY = 0;
int birdRadius = 10;
char ch;
char scoreStr[10];
// Pipe properties
int pipeX = 500, pipeY = 300, pipeWidth = 50, gapHeight = 150;
int pipeSpeed = 3;

// Game properties
int score = 0;
int isGameOver = 0;

// Function to draw the bird
void drawBird() {
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(birdX, birdY, birdRadius, birdRadius);
}

// Function to draw the pipes
void drawPipes() {
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    bar(pipeX, 0, pipeX + pipeWidth, pipeY - gapHeight / 2); // Upper pipe
    bar(pipeX, pipeY + gapHeight / 2, pipeX + pipeWidth, getmaxy()); // Lower pipe
}

// Function to check for collisions
void checkCollision() {
    if (birdY - birdRadius <= 0 || birdY + birdRadius >= getmaxy()) {
        isGameOver = 1;
    }
    if (birdX + birdRadius >= pipeX && birdX - birdRadius <= pipeX + pipeWidth) {
        if (birdY - birdRadius <= pipeY - gapHeight / 2 || birdY + birdRadius >= pipeY + gapHeight / 2) {
            isGameOver = 1;
        }
    }
}

void updateGame() {
    birdDY += gravity;
    birdY += birdDY;

    pipeX -= pipeSpeed;

    if (pipeX + pipeWidth < 0) {
        pipeX = getmaxx();
        pipeY = rand() % (getmaxy() - gapHeight) + gapHeight / 2;
        score++;
    }

    checkCollision();
}

// Function to display the game over screen
void gameOverScreen() {
    setcolor(RED);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(getmaxx() / 2 - 50, getmaxy() / 2 - 10, "Game Over");
    
    sprintf(scoreStr, "Score: %d", score);
    outtextxy(getmaxx() / 2 - 50, getmaxy() / 2 + 20, scoreStr);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    while (!isGameOver) {
        cleardevice();
        drawBird();
        drawPipes();
        updateGame();
        delay(50);
        if (kbhit()) {
            ch = getch();
            if (ch == ' ') {
                birdDY = lift;
            }
        }
    }
    gameOverScreen();
    getch();
    closegraph();
    return 0;
}
