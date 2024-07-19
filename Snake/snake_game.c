#include "snake_game.h"
#include "ui.h"
#include "play.h"
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
void init(void)
{
	char button;
	while(1){
		init_show();
		button = getch();
		if(button != '1' && button != '2' && button != '3')
			continue;
		switch(button){
			case '1':
				return ;
			case '2':
				history_show();
				break;
			case '3':
				exit(0);
		}
	}
}

struct itimerval value;
static void snake_action(int sig_num)
{
	if(if_die){
		value.it_value.tv_sec = 0;
		value.it_value.tv_usec = 0;
		value.it_interval = value.it_value;
		setitimer(ITIMER_REAL,&value,NULL);
		printf("\n  游戏结束,按任意键盘继续\n");
		return ;
	}
	set_body(body);
	set_snake(snake);
	game_show();
	move_snake();
}

void run(void)
{
	init_map();
	snake = init_snake();
	body = init_body();
	way = 'w';
	if_die = 0;
	//设置定时器
	signal(SIGALRM,snake_action);
	value.it_value.tv_sec = 0;
	value.it_value.tv_usec = 120000;
	value.it_interval = value.it_value;
	setitimer(ITIMER_REAL,&value,NULL);
	printf("\n  等待游戏开始.......\n");
	while(!if_die){
		way = getch();
	}
	printf("\n  socre : %d\n",snake->size);
	printf("\n  等待上传数据.....\n");
	sleep(5);
}

void end(void)
{
	int fd = open("gameHistoryScore.txt",O_CREAT |O_WRONLY | O_APPEND , 0644);
	char buf[100] = {};
	time_t rawtime;
	struct tm *info;
	time( &rawtime );
	info = localtime( &rawtime );
	sprintf(buf," %d  创建时间：%s", snake->size,asctime(info));
	size_t size = write(fd,buf,strlen(buf));
	if(size <= 0){
		printf("记录失败!\n");
	}
}
