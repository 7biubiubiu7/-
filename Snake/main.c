#include "snake_game.h"

int main(int argc,const char* argv[])
{
	while(1){
		init();//初始化界面，显示开始游戏、退出、历史数据
		run();//游戏过程
		end();//游戏结束，上传数据
	}
}
