#include "ui.h"
#include "play.h"

void init_show(void)
{
	system("clear");
	printf("  贪吃蛇\n");
	printf("1. 开始游戏\n");
	printf("2. 历史战绩\n");
	printf("3.   退出\n");
	printf("请选择：");
}

void history_show(void)
{
	system("clear");
	 FILE* fptr = fopen("gameHistoryScore.txt", "r");
	 if(fptr == NULL){
		printf("还没有历史记录哦~\n");
		printf("按任意键继续\n");
		getch();
		return ;
	 }
	char buf[100] = {};
	while(fgets(buf,100,fptr)){
		printf("%s",buf);
	}
	printf("按任意键继续\n");
	getch();
}

void game_show(void)
{
	system("clear");
	printf("\n");
	for(int i = 0;i < 30;i++){
		for(int j = 0;j < 30;j++){
			printf(" %c",map[i][j]);
		}
		printf("\n");
	}
}
