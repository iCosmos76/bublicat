#include "pch.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

POINT me, old, trend;				// текущая позиция, старая позиция, позиция обнаружена
int size = 0;						// размер карты

//	Карта представляет собой двумерный массив N * N, допустимое значение 0, 1, 2, 3, 4

//	0 - комната - ' '
//	1 - стена   - '#'
//	2 - цель - '+'
//	3 - коробка - '?'
//	4 - игрок  - 1

// тектовая карта 1
/*
int map[6][6]={
				0,1,1,1,1,0,
				1,1,0,0,1,1,
				1,0,4,3,0,1,
				1,0,0,2,0,1,
				1,1,0,0,1,1,
				0,1,1,1,1,0,
			};
int map_goal[6][6]={
				0,1,1,1,1,0,
				1,1,0,0,1,1,
				1,0,4,3,0,1,
				1,0,0,2,0,1,
				1,1,0,0,1,1,
				0,1,1,1,1,0,
			};
*/

// тектовая карта 2
/*
int map[7][7]={
				1,1,1,1,1,1,1,
				1,0,0,0,0,0,1,
				1,0,4,3,0,0,1,
				1,0,0,2,0,0,1,
				1,0,3,2,0,0,1,
				1,0,3,0,2,0,1,
				1,1,1,1,1,1,1,
			};
int map_goal[7][7]={
				1,1,1,1,1,1,1,
				1,0,0,0,0,0,1,
				1,0,4,3,0,0,1,
				1,0,0,2,0,0,1,
				1,0,3,2,0,0,1,
				1,0,3,0,2,0,1,
				1,1,1,1,1,1,1,
			};

			*/

// карта 3
int map[20][20] = {
				0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
				0,0,0,0,1,2,0,0,3,0,0,1,1,1,1,1,1,1,0,0,
				0,0,0,0,1,2,2,3,0,3,0,0,0,0,0,0,0,1,0,0,
				1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,2,1,0,0,
				1,2,0,0,1,2,0,0,0,0,0,0,0,0,0,0,3,1,0,0,
				1,3,0,0,1,3,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
				1,2,0,0,1,0,0,1,1,1,1,1,1,0,1,0,0,1,0,0,
				1,3,0,0,1,0,0,1,0,3,2,2,1,0,1,0,0,1,0,0,
				1,2,0,0,1,0,0,1,0,3,3,2,1,0,1,0,0,1,0,0,
				1,3,0,0,1,0,0,1,0,0,1,1,1,0,1,0,0,1,0,0,
				1,2,0,0,1,0,0,1,0,0,0,2,3,0,1,0,0,1,0,0,
				1,3,0,0,1,0,0,1,0,0,0,0,3,2,1,0,0,1,0,0,
				1,0,0,0,1,0,0,1,1,1,1,1,1,1,1,0,0,1,0,0,
				1,2,2,0,3,0,0,3,0,0,4,0,0,0,3,0,2,1,0,0,
				1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,0,
				1,2,3,0,0,3,0,0,0,0,0,0,0,0,3,2,2,1,0,0,
				1,0,0,0,0,3,3,1,1,1,1,1,1,1,0,3,2,1,0,0,
				1,1,1,1,1,3,2,1,0,0,0,0,0,1,1,1,1,1,0,0,
				0,0,0,0,1,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,
				0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
};

int map_goal[20][20] = {
				0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
				0,0,0,0,1,2,0,0,3,0,0,1,1,1,1,1,1,1,0,0,
				0,0,0,0,1,2,2,3,0,3,0,0,0,0,0,0,0,1,0,0,
				1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,2,1,0,0,
				1,2,0,0,1,2,0,0,0,0,0,0,0,0,0,0,3,1,0,0,
				1,3,0,0,1,3,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
				1,2,0,0,1,0,0,1,1,1,1,1,1,0,1,0,0,1,0,0,
				1,3,0,0,1,0,0,1,0,3,2,2,1,0,1,0,0,1,0,0,
				1,2,0,0,1,0,0,1,0,3,3,2,1,0,1,0,0,1,0,0,
				1,3,0,0,1,0,0,1,0,0,1,1,1,0,1,0,0,1,0,0,
				1,2,0,0,1,0,0,1,0,0,0,2,3,0,1,0,0,1,0,0,
				1,3,0,0,1,0,0,1,0,0,0,0,3,2,1,0,0,1,0,0,
				1,0,0,0,1,0,0,1,1,1,1,1,1,1,1,0,0,1,0,0,
				1,2,2,0,3,0,0,3,0,0,4,0,0,0,3,0,2,1,0,0,
				1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,0,
				1,2,3,0,0,3,0,0,0,0,0,0,0,0,3,2,2,1,0,0,
				1,0,0,0,0,3,3,1,1,1,1,1,1,1,0,3,2,1,0,0,
				1,1,1,1,1,3,2,1,0,0,0,0,0,1,1,1,1,1,0,0,
				0,0,0,0,1,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,
				0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
};

void HideCursor(){
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void Gotoxy(int x, int y){
	COORD pos;
	pos.X = x - 1;
	pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Init(){
	int i = 0, j = 0;
	me.x = 0;
	me.y = 0;
	trend.x = 0;
	trend.y = 0;
	old.x = 0;
	old.y = 0;
	size = sqrt(sizeof(map) / sizeof(int));		
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			if (map[i][j] == 4){
				me.x = i;
				me.y = j;
			}
		
	if (me.x == 0 || me.y == 0){
		MessageBox(NULL, L"Ошибка данных! \n \nInit ",L" Загрузка не удалась！", MB_ICONEXCLAMATION);
		system("pause");
		exit(0);
	}
}

void Appearance(){

	char screen_size[26] = "mode con cols=17 lines=09";
	screen_size[14] = ((size - 7) * 2 + 23) / 10 + 48;
	screen_size[15] = ((size - 7) * 2 + 23) % 10 + 48;
	screen_size[23] = (size - 7 + 12) / 10 + 48;
	screen_size[24] = (size - 7 + 12) % 10 + 48;
	system(screen_size);					
	system("color f0");						
	system("title Sokoban");				
	HideCursor();							
}

void Showscreen(){

	int i = 0, j = 0, temp = 0;
	Gotoxy(1, 1);				
	for (i = 0; i < size; i++){
		printf("\n  ");
		for (j = 0; j < size; j++){
			switch (map[i][j]){
			case 0:
				temp = 0;
				break;
			case 1:
				temp = 35;
				break;
			case 2:
				temp = 43;
				break;
			case 3:
				temp = 1;
				break;
			case 4:
				temp = 49;
				break;
			default:			
				MessageBox(NULL,L"Ошибка данных на карте! \n \nShowscreen ",L" Загрузка не удалась!", MB_ICONEXCLAMATION);
				system("pause");
				exit(0);
				break;
			}
			printf("%c ", temp);
		}
	}
}

int Is_not_win(){
	int i = 0, j = 0;
	for (i = 0; i < size; ++i)
		for (j = 0; j < size; ++j)
			if (map_goal[i][j] == 2 && map[i][j] != 3)
				return 1;

	return 0;
}

void Rollback()
{
	int i = 0, j = 0;
	for (i = 0; i < size; ++i)
		for (j = 0; j < size; ++j)
			if (map_goal[i][j] == 2 && map[i][j] == 0)
				map[i][j] = 2;

}

void Move(int direct)
{
	POINT temp;
	trend = me;
	switch (direct){
	case 'w':
		--trend.x;
		break;
	case 's':
		++trend.x;
		break;
	case 'a':
		--trend.y;
		break;
	case 'd':
		++trend.y;
		break;
	default:
		break;
	}
	temp = trend;

	if (map[trend.x][trend.y] == 0 || map[trend.x][trend.y] == 2){
		old = me;
		me = trend;
	}
	else if (map[trend.x][trend.y] == 3){
		switch (direct){
		case 'w':
			--temp.x;
			break;
		case 's':
			++temp.x;
			break;
		case 'a':
			--temp.y;
			break;
		case 'd':
			++temp.y;
			break;
		default:
			break;
		}
		if (map[temp.x][temp.y] == 0 || map[temp.x][temp.y] == 2){
			map[temp.x][temp.y] = 3;
			map[trend.x][trend.y] = 0;
			old = me;
			me = trend;
		}
	}
	if (map[me.x][me.y] != 4){
		map[old.x][old.y] = 0;
		map[me.x][me.y] = 4;
		old = me;
	}
	Rollback();				
}

void Run(){
	Showscreen();				
	while (Is_not_win()){		
		Move(_getch());			
		Showscreen();			
	}
	system("title Вы выиграли! ");
	printf("\n\n  Ты выиграл!\n\n  ");
	system("pause");	
}

int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Init();
	Appearance();
	Run();
}