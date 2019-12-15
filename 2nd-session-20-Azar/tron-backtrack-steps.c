#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXX 30
#define MAXY 20

int grid[MAXX][MAXY];

int isBad(int x, int y) {
	if(x >= MAXX || x < 0)
		return 1;
	if(y >= MAXY || y < 0)
		return 1;
	if(grid[x][y] != 0)
		return 1;
	return 0;
}

#define MAXP 2000

int btState[2000];
int bestState[2000];
int xmove[4] = {0, -1, 0, 1}; // UP, LEFT, DOWN, RIGHT
int ymove[4] = {-1, 0, 1, 0}; 


int backtrack(int step, int maxStep, int curX, int curY) {
	if(isBad(curX, curY) == 1)
		return 0;
    
	if(step == maxStep) {
		return 1;
	}
  	grid[curX][curY] = 1;
	int found = 0;
	for(int move = 0; move < 4; move++) {
		int nextX = curX + xmove[move];
		int nextY = curY + ymove[move];
		btState[step] = move;
		if(backtrack(step + 1, maxStep, nextX, nextY) == 1) {
			found = 1;
			break;
		}
	}
	grid[curX][curY] = 0;
	return found;
}

int main()
{
	// game loop
	while (1) {
		int N; // total number of players (2 to 4).
		int P; // your player number (0 to 3).
		int myX = -1, myY = -1;
		scanf("%d%d", &N, &P);
		
		for (int i = 0; i < N; i++) {
			int X0; // starting X coordinate of lightcycle (or -1)
			int Y0; // starting Y coordinate of lightcycle (or -1)
			int X1; // starting X coordinate of lightcycle (can be the same as X0 if you play before this player)
			int Y1; // starting Y coordinate of lightcycle (can be the same as Y0 if you play before this player)
			scanf("%d%d%d%d", &X0, &Y0, &X1, &Y1);
			if(i == P)
				myX = X1, myY = Y1;
			grid[X0][Y0] = grid[X1][Y1] = i + 1;
		}

        int target = 40;
        
        grid[myX][myY] = 0;
        
        while(target > 0 && backtrack(0, target, myX, myY) == 0) {
            target -= 5;
        }
        
        fprintf(stderr, "myX = %d, myY = %d, target = %d\n", myX, myY, target);
        
        if(target > 0) {
			int move = btState[0];
			if(move == 0)
				printf("UP\n");
			else if(move == 1)
				printf("LEFT\n");
			else if(move == 2)
				printf("DOWN\n");
			else
				printf("RIGHT\n");
		}
		else {
    		if(myY > 0 && grid[myX][myY - 1] == 0)
    			printf("UP\n");
    		else if(myX > 0 && grid[myX - 1][myY] == 0)
    			printf("LEFT\n");
    		else if(myY < 19 && grid[myX][myY + 1] == 0)
    			printf("DOWN\n");
    		else
    			printf("RIGHT\n");
		}
        grid[myX][myY] = 1;
	}

	return 0;
} 