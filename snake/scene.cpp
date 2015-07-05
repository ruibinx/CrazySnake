#include "Scene.h"

Scene::Scene():
hasFailed(false), speed(1), score(0), snake(), aApple(snake)
{
}

void Scene::init()
{
	initgraph(800, 600);
	setcaption("CrAzy SnaKE!");
	randomize();
	maxscore = 0;
	setbkcolor(0xffffff);
	setcolor(BLACK);
	reset();
}

void Scene::reset()
{
	snake.reset();
	speed = 5;
	score = 0;
	hasFailed = false;
	hasHitKey = false;

}

void Scene::setDirectionByKeyMsg()
{
	key_msg key;

	if (kbmsg())
	{
		key = getkey();

		if (key.msg == key_msg_down && !hasHitKey)
		{
			switch (snake.getDirection())
			{
			case Snake::up:
			case Snake::down:
			{
				switch (key.key)
				{
				case VK_LEFT:snake.setDirection(Snake::left); hasHitKey = true; break;
				case VK_RIGHT:snake.setDirection(Snake::right); hasHitKey = true; break;
				}
				break;
			}
			case Snake::left:
			case Snake::right:
			{
				switch (key.key)
				{
				case VK_UP:snake.setDirection(Snake::up); hasHitKey = true; break;
				case VK_DOWN:snake.setDirection(Snake::down); hasHitKey = true; break;
				}
			}
			}

		}
	}
}

void Scene::start()
{
	int originalSpeed = speed;
	for (int counter = 0; is_run() && !hasFailed; delay_ms(10), counter++)
	{
		setDirectionByKeyMsg();
		if (counter % speed == 0)
		{
			cleardevice();
			snake.move();
			if (snake.hasAteFood(aApple)){
				snake.addBody(aApple.getX(), aApple.getY());
				aApple.newApple(snake);
				score++;
				if (score > maxscore){
					maxscore = score;
				}
				speed = originalSpeed / ( 1.0 + score / 100.0);
				if (speed == 0){
					speed = 1;
				}
			}
			else
			if (snake.hasBitSelf() | snake.hasCrashedIntoWall())
			{
				hasFailed = true;
			}
			snake.draw();
			aApple.draw();
			hasHitKey = false;
			std::string scorestr = std::string("Score: ") + std::to_string(score) + std::string(" Speed: ") + std::to_string(speed)
				+ std::string(" MaxScore:") + std::to_string(maxscore);
			outtext(scorestr.c_str());

		}
	}
	failed();
}
void Scene::failed()
{

	outtextxy(380, 200, "YOU LOSE!");
	getch();
	reset();
	start();
}

Scene::~Scene(){
	closegraph();
}