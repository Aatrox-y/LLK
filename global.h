#pragma once
typedef struct tagVertex
{
	int row;     
	int col;   
	int info;  
}Vertex;

#define BLANK -1
const int  MRow = 10;
const int  MCol = 16;
const int  Mpic = 20;
#define game_lose -1;
#define game_win 0;
#define game_play 1;