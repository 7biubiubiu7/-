#ifndef PLAY_H
#define PLAY_H

#include <stdio.h>
#include <getch.h>
#include <stdlib.h>
#include <time.h>


typedef struct Body_Node{
	struct Body_Node* next;
	size_t x;
	size_t y;
}Body,*Pbody;

typedef struct Snake_List{
	Pbody head;
	Pbody tail;
	size_t node_size;
	int size;
}Snake,*Psnake;

Pbody body;
Psnake snake;
char map[30][30];
char way;
int if_die;

void init_map(void);

Psnake init_snake(void);

Pbody init_body(void);

void set_snake(Psnake snake);

void set_body(Pbody body);

void move_snake(void);

#endif// PLAY_H
