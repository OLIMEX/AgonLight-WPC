#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <conio.h> // for win用

#include <graphics.h>

#define OUTER_BOX_SIZE 12
#define INNER_BOX_SIZE 8

#define OFFSET_X 15
#define OFFSET_Y 6

#define FIELD_HEIGHT 21 //枠を含む
#define FIELD_WIDTH 12  //枠を含む

#define MINO_HEIGHT 4
#define MINO_WIDTH 4

#define DEFAULT_POS_X 5
#define DEFAULT_POS_Y (-MINO_HEIGHT + 1)

// #define bool _Bool
// #define true 1
// #define false 0

enum {
	MINO_ANGLE_0, MINO_ANGLE_90, MINO_ANGLE_180, MINO_ANGLE_270, MINO_ANGLE_MAX
};

enum {
	MINO_TYPE_I,
	MINO_TYPE_O,
	MINO_TYPE_S,
	MINO_TYPE_Z,
	MINO_TYPE_J,
	MINO_TYPE_L,
	MINO_TYPE_T,
	MINO_TYPE_MAX
};

int minoX = DEFAULT_POS_X;
int minoY = DEFAULT_POS_Y;
int minoAngle = 0;
int minoType = 0;
int score = 0;

int getRandom(int min, int max);
void resetMino();
void initField();
void copyField();
bool check(int _minoX, int _minoY, int minoType, int _minoAngle);
void moveMino(int *minoX, int *minoY, int *minoAngle, int _dx, int _dy, int _da);
void writeMino(int target[FIELD_WIDTH][FIELD_HEIGHT], int _nextX, int _nextY,
		int minoType, int minoAngle);
void draw_screen();
bool isGameOver(int flag);

int getRandom(int min, int max) {

	static int flag;

	if (flag == 0) {
		srand((unsigned int) time(NULL));
		flag = 1;
	}

	return min + (int) (rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

void resetMino() {
	minoX = 5;
	minoY = 0;
	//minoType = rand() % MINO_TYPE_MAX;
	minoType = getRandom(0, MINO_TYPE_MAX - 1);
	//minoAngle = rand() % MINO_ANGLE_MAX;
	minoAngle = getRandom(0, MINO_ANGLE_MAX - 1);
}

int field[FIELD_WIDTH][FIELD_HEIGHT];
int displayBuffer[FIELD_WIDTH][FIELD_HEIGHT] = { };
int prevDisplayBuffer[FIELD_WIDTH][FIELD_HEIGHT] = { };

char minoShapes[MINO_TYPE_MAX][MINO_ANGLE_MAX][MINO_HEIGHT][MINO_WIDTH] =
		{
		//MINO_TYPE_I
				{
				//MINO_ANGLE_0
						{ { 0, 1, 0, 0 }, { 0, 1, 0, 0 }, { 0, 1, 0, 0 }, { 0,
								1, 0, 0 } },
						//MINO_ANGLE_90
						{ { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 1, 1, 1, 1 }, { 0,
								0, 0, 0 } },
						//MINO_ANGLE_180
						{ { 0, 0, 1, 0 }, { 0, 0, 1, 0 }, { 0, 0, 1, 0 }, { 0,
								0, 1, 0 } },
						//MINO_ANGLE_270
						{ { 0, 0, 0, 0 }, { 1, 1, 1, 1 }, { 0, 0, 0, 0 }, { 0,
								0, 0, 0 } } },
				//MINO_TYPE_O
				{
				//MINO_ANGLE_0
						{ { 0, 0, 0, 0 }, { 0, 1, 1, 0 }, { 0, 1, 1, 0 }, { 0,
								0, 0, 0 } },
						//MINO_ANGLE_90
						{ { 0, 0, 0, 0 }, { 0, 1, 1, 0 }, { 0, 1, 1, 0 }, { 0,
								0, 0, 0 } },
						//MINO_ANGLE_180
						{ { 0, 0, 0, 0 }, { 0, 1, 1, 0 }, { 0, 1, 1, 0 }, { 0,
								0, 0, 0 } },
						//MINO_ANGLE_270
						{ { 0, 0, 0, 0 }, { 0, 1, 1, 0 }, { 0, 1, 1, 0 }, { 0,
								0, 0, 0 } } },
				//MINO_TYPE_S
				{
				//MINO_ANGLE_0
						{ { 0, 0, 0, 0 }, { 0, 0, 1, 1 }, { 0, 1, 1, 0 }, { 0,
								0, 0, 0 } },
						//MINO_ANGLE_90
						{ { 0, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 1, 1, 0 }, { 0,
								0, 1, 0 } },
						//MINO_ANGLE_180
						{ { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 1, 1 }, { 0,
								1, 1, 0 } },
						//MINO_ANGLE_270
						{ { 0, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 1, 1, 0 }, { 0,
								0, 1, 0 } } },
				//MINO_TYPE_Z
				{
				//MINO_ANGLE_0
						{ { 0, 0, 0, 0 }, { 1, 1, 0, 0 }, { 0, 1, 1, 0 }, { 0,
								0, 0, 0 } },
						//MINO_ANGLE_90
						{ { 0, 0, 1, 0 }, { 0, 1, 1, 0 }, { 0, 1, 0, 0 }, { 0,
								0, 0, 0 } },
						//MINO_ANGLE_180
						{ { 0, 0, 0, 0 }, { 1, 1, 0, 0 }, { 0, 1, 1, 0 }, { 0,
								0, 0, 0 } },
						//MINO_ANGLE_270
						{ { 0, 0, 1, 0 }, { 0, 1, 1, 0 }, { 0, 1, 0, 0 }, { 0,
								0, 0, 0 } } },
				//MINO_TYPE_J
				{
				//MINO_ANGLE_0
						{ { 0, 1, 0, 0 }, { 0, 1, 0, 0 }, { 1, 1, 0, 0 }, { 0,
								0, 0, 0 } },
						//MINO_ANGLE_90
						{ { 1, 0, 0, 0 }, { 1, 1, 1, 0 }, { 0, 0, 0, 0 }, { 0,
								0, 0, 0 } },
						//MINO_ANGLE_180
						{ { 0, 1, 1, 0 }, { 0, 1, 0, 0 }, { 0, 1, 0, 0 }, { 0,
								0, 0, 0 } },
						//MINO_ANGLE_270
						{ { 0, 0, 0, 0 }, { 1, 1, 1, 0 }, { 0, 0, 1, 0 }, { 0,
								0, 0, 0 } } },
				//MINO_TYPE_L
				{
				//MINO_ANGLE_0
						{ { 0, 1, 0, 0 }, { 0, 1, 0, 0 }, { 0, 1, 1, 0 }, { 0,
								0, 0, 0 } },
						//MINO_ANGLE_90
						{ { 0, 0, 0, 0 }, { 1, 1, 1, 0 }, { 1, 0, 0, 0 }, { 0,
								0, 0, 0 } },
						//MINO_ANGLE_180
						{ { 1, 1, 0, 0 }, { 0, 1, 0, 0 }, { 0, 1, 0, 0 }, { 0,
								0, 0, 0 } },
						//MINO_ANGLE_270
						{ { 0, 0, 0, 0 }, { 0, 0, 1, 0 }, { 1, 1, 1, 0 }, { 0,
								0, 0, 0 } }, },
				//MINO_TYPE_T
				{
				//MINO_ANGLE_0
						{ { 0, 0, 0, 0 }, { 1, 1, 1, 0 }, { 0, 1, 0, 0 }, { 0,
								0, 0, 0 } },
						//MINO_ANGLE_90
						{ { 0, 1, 0, 0 }, { 1, 1, 0, 0 }, { 0, 1, 0, 0 }, { 0,
								0, 0, 0 }, },
						//MINO_ANGLE_180
						{ { 0, 0, 0, 0 }, { 0, 1, 0, 0 }, { 1, 1, 1, 0 }, { 0,
								0, 0, 0 } },
						//MINO_ANGLE_270
						{ { 0, 1, 0, 0 }, { 0, 1, 1, 0 }, { 0, 1, 0, 0 }, { 0,
								0, 0, 0 } } } };

//Initialize field 
void initField() {
	memset(field, 0, sizeof(field));

	for (int y = 0; y < FIELD_HEIGHT; y++) {
		field[0][y] = field[FIELD_WIDTH - 1][y] = 1;
	}
	for (int x = 0; x < FIELD_WIDTH; x++) {
		field[x][FIELD_HEIGHT - 1] = 1;
	}
}

//copy field to displayBuffer
void copyField() {
	memset(displayBuffer, 0, sizeof(displayBuffer));

	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			displayBuffer[x][y] |= field[x][y];
		}
	}
}

//Check of movement
bool check(int _minoX, int _minoY, int minoType, int _minoAngle) {
	int _nextX;
	int _nextY;
	int _nextA = _minoAngle % MINO_ANGLE_MAX;

	for (int h = 0; h < MINO_HEIGHT; h++) {
		for (int w = 0; w < MINO_WIDTH; w++) {
			_nextX = _minoX + w;
			_nextY = _minoY + h;

			if (_nextY < 0 || minoShapes[minoType][_nextA][h][w] == 0) {
				continue;
			}

			if (minoShapes[minoType][_nextA][h][w]
					&& field[_nextX][_nextY] == 1) {
				return false;
			}
		}
	}
	return true;

}

//Move piece
void moveMino(int *minoX, int *minoY, int *minoAngle, int _dx, int _dy, int _da) {
	*minoX += _dx;
	*minoY += _dy;
	*minoAngle = (*minoAngle + _da) % MINO_ANGLE_MAX;
}

//Write piece
void writeMino(int target[FIELD_WIDTH][FIELD_HEIGHT], int _nextX, int _nextY,
		int minoType, int minoAngle) {
	for (int w = 0; w < MINO_WIDTH; w++) {
		for (int h = 0; h < MINO_HEIGHT; h++) {
			if (_nextY + h < 0 && minoShapes[minoType][minoAngle][h][w] == 1) {
				continue;
			}
			target[_nextX + w][_nextY + h] |=
					minoShapes[minoType][minoAngle][h][w];
		}
	}
}

//Show on screen
void draw_screen() {
	copyField();

	writeMino(displayBuffer, minoX, minoY, minoType, minoAngle);
	// clg();

	for (int y = 0; y < FIELD_HEIGHT; ++y) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			//printf("%s", displayBuffer[x][y] ? "回" : "・");

			if (prevDisplayBuffer[x][y] != displayBuffer[x][y]) {

				if (displayBuffer[x][y] == true) {
					drawb((x + OFFSET_X) * OUTER_BOX_SIZE,
							(y + OFFSET_Y) * OUTER_BOX_SIZE, OUTER_BOX_SIZE,
							OUTER_BOX_SIZE);
					drawb(((x + OFFSET_X) * OUTER_BOX_SIZE) + 2,
							((y + OFFSET_Y) * OUTER_BOX_SIZE) + 2,
							INNER_BOX_SIZE, INNER_BOX_SIZE);
				} else {
					undrawb((x + OFFSET_X) * OUTER_BOX_SIZE,
							(y + OFFSET_Y) * OUTER_BOX_SIZE, OUTER_BOX_SIZE,
							OUTER_BOX_SIZE);
					undrawb(((x + OFFSET_X) * OUTER_BOX_SIZE) + 2,
							((y + OFFSET_Y) * OUTER_BOX_SIZE) + 2,
							INNER_BOX_SIZE, INNER_BOX_SIZE);
				}

				prevDisplayBuffer[x][y] = displayBuffer[x][y];
			}
		}
		//printf("\n");
	}
}

//Is it GameOver 
bool isGameOver(int flag) {
	return flag ? true : false;
}

int main(void) {

	// system("chcp 65001");

	char in_key;

	bool runing = True;

	time_t t = time(NULL); //Time
 	printf("T E T R I S\n");
	printf("A -> Left\n"); 
	printf("D -> Right\n");
	printf("S -> Speed Up\n");
	printf("W -> Rotate\n");
 	printf("C -> Restart\n");


	initField();

	resetMino();

	while (runing) {

		int dx = 0; //横移動
		int dy = 0; //縦移動
		int da = 0; //回転

		if (kbhit()) //Use _kbhit() in conio.h for windows
		{
			in_key = getch();

			switch (in_key) {
			case 'a': {
				if (check(minoX - 1, minoY, minoType, minoAngle)) {
					dx += -1;
					moveMino(&minoX, &minoY, &minoAngle, dx, dy, da);
				}
				break;
			}
			case 'd': {
				if (check(minoX + 1, minoY, minoType, minoAngle)) {
					dx += 1;
					moveMino(&minoX, &minoY, &minoAngle, dx, dy, da);
				}
				break;
			}
			case 'w': {
				if (check(minoX, minoY, minoType, minoAngle + 1)) {
					draw_screen();
					da += 1;
					moveMino(&minoX, &minoY, &minoAngle, dx, dy, da);
				}
				break;
			}
			case 's': {
				if (check(minoX, minoY + 1, minoType, minoAngle)) {
					dy = 1;
					moveMino(&minoX, &minoY, &minoAngle, dx, dy, da);
				}
				break;
			}
			case 27: {
				clg();
				runing = False;
				break;
			}
			case 99: {
				initField();
				resetMino();
				break;
			}
			default: {
				//cprintf("%d", in_key);
				break;
			}
			}

			draw_screen();

			msleep(1000);

		}

		if (t != time(NULL)) {

			dy++;

			t = time(NULL);

			if (check(minoX + dx, minoY + dy, minoType, minoAngle + da)) {

				moveMino(&minoX, &minoY, &minoAngle, dx, dy, da);

			} else {

				// printf("fix\n");

				writeMino(field, minoX, minoY, minoType, minoAngle);

				int x, y;

				for (y = 0; y < FIELD_HEIGHT - 1; y++) {
					bool lineFill = true;

					for (x = 1; x < FIELD_WIDTH - 1; x++) {
						if (!field[x][y])
							lineFill = false;
					}

					if (lineFill) {

						// printf("fill\n");

						for (int i = y; 0 < i; i--) {

							for (int j = 0; j < FIELD_WIDTH; j++) {
								field[j][i] = field[j][i - 1];
							}

							y--;
						}

					}

					resetMino();
				}
			}
			draw_screen();
		}
	}

	return 0;
}