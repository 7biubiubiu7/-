#include "play.h"
#include <stdbool.h>

void init_map(void)
{
	for(int i = 0;i < 30;i++){
		for(int j = 0;j < 30;j++){
			map[i][j] = ' ';
			if(i == 0 || i == 29)map[i][j] = '*';
			if(j == 0 || j == 29)map[i][j] = '*';
		}
	}
}

Psnake init_snake(void)
{
	Psnake snake = (Psnake)malloc(sizeof(Snake));
	Pbody head = (Pbody)malloc(sizeof(Body));
	Pbody tail = (Pbody)malloc(sizeof(Body));
	head->next = tail;
	head->x = 14;
	head->y = 15;
	tail->x = 15;
	tail->y = 15;
	snake->head = head;
	snake->tail = tail;
	snake->size = 2;
	return snake;
}

Pbody init_body(void)
{
	srand(time(NULL));
	Pbody body = (Pbody)malloc(sizeof(Body));
	body->next = NULL;
	body->x = rand()%28+1;
	body->y = rand()%28+1;
	return body;
}

void set_snake(Psnake snake)
{
	for(Pbody n = snake->head;n != NULL;n = n->next){
		map[n->x][n->y] = '&';
	}
}

void set_body(Pbody body)
{
	map[body->x][body->y] = 'O';
}

static void eat_body(void)
{
	body->next = snake->head;
	snake->head = body;
	snake->size++;
}

static bool snake_die(Pbody body)
{
	if(map[body->x][body->y] == '&')
		return true;
	else if(body->x == 0 || body->x == 29)
		return true;
	else if(body->y == 0 || body->y == 29)
		return true;
	return false;
}
static void swap_way(char* way)
{
	if(*way == 'w'){*way = 's';return ;}
	if(*way == 's'){*way = 'w';return ;}
	if(*way == 'a'){*way = 'd';return ;}
	if(*way == 'd'){*way = 'a';return ;}
}

void move_snake(void)
{
	int head_x = 0;
	int head_y = 0;
	switch(way){
		case 'w':head_x = -1;break;
		case 'a':head_y = -1;break;
		case 'd':head_y = 1;break;
		case 's':head_x = 1;break;
	}
	Pbody body2 = (Pbody)malloc(sizeof(Body));//给蛇头前面的格子初始化
	body2->x = snake->head->x + head_x;       
	body2->y = snake->head->y + head_y;
	if(body2->x == snake->head->next->x && body2->y == snake->head->next->y){//不能回头
		swap_way(&way);
		return ;
	}
	body2->next = snake->head;
	if(body2->x == body->x && body2->y == body->y){//如果刚好是随机产生的食物，那就吃掉它
		eat_body();
		body = init_body();
		return ;
	}
	if(snake_die(body2)){//死亡
		if_die = 1;
		return ;
	}
	//头部往前移动
	snake->head = body2;
	//丢掉尾巴
	Pbody n1;
	for(n1 = snake->head;n1->next != snake->tail ;n1 = n1->next){}//找到尾巴
	map[snake->tail->x][snake->tail->y] = ' ';
	Pbody n2 = snake->tail;
	snake->tail = n1;//前移尾巴
	snake->tail->next = NULL;
	free(n2);//释放尾巴空间
}


