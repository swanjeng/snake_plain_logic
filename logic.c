#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int x;
    int y;
} Point;

int PointEqual(Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

int hitWall(Point head, int row, int col) {
    return !(0 <= head.x && head.x < row && 0 <= head.y && head.y < col);
}

int hitBody(Point head, Point *snake, int snakeLength) {
    for (int i = 0 ; i < snakeLength ; i ++) {
        if (PointEqual(head, snake[i])) return 1;
    }
    return 0;
}

// dir: 0 = up, 1 = down, 2 = left, 3 = right
int move(Point *snake, int *snakeLength, int dir, int row, int col, Point food) {
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    Point newHead = {snake[0].x + dirs[dir][0], snake[0].y + dirs[dir][1]};
    if (hitWall(newHead, row, col) || hitBody(newHead, snake, *snakeLength)) {
        return -1;
    }

    int val = 0;
    if (PointEqual(food, newHead)) {
        *snakeLength += 1;
        val = 1;
    }

    for (int i = *snakeLength - 2 ; i >= 0 ; i --) {
        snake[i + 1] = snake[i];
    }

    snake[0] = newHead;
    return val;
}

void printGrid(Point *snake, int snakeLength, int row, int col, Point food) {
    char grid[10][10];
    for (int i = 0 ; i < row ; i ++) {
        for (int j = 0 ; j < col ; j ++) {
            grid[i][j] = ' ';
        }
    }
    grid[snake[0].x][snake[0].y] = 'S';
    for (int i = 1 ; i < snakeLength ; i ++) {
        grid[snake[i].x][snake[i].y] = 's';
    }
    grid[food.x][food.y] = 'f';
    for (int i = 0 ; i < row ; i ++) {
        for (int j = 0 ; j < col ; j ++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
}

int validFoodPos(Point food, Point *snake, int snakeLength) {
    for (int i = 0 ; i < snakeLength ; i ++) {
        if (PointEqual(food, snake[i])) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int row = 10, col = 10;
    int snakeLength = 1, maxLen = row * col;
    Point *snake = malloc((maxLen + 1) * sizeof(Point));
    if (snake == NULL) {
        printf("Initialization failed\n");
        return 0;
    }
    snake[0] = (Point) {5, 5};
    
    Point food = {8, 8};
    printGrid(snake, snakeLength, row, col, food);
    int input = 0;
    while (scanf("%d", &input) != EOF && input != -1) {
        if (move(snake, &snakeLength, input, row, col, food) == 1) {
            // printf("got food, len ++ (%d)\n", snakeLength);
            while (!validFoodPos(food, snake, snakeLength)) {
                food.x = rand() % row;
                food.y = rand() % col;
            }
        }
        printGrid(snake, snakeLength, row, col, food);
    }
    free(snake);
    snake = NULL;
    return 0;
}