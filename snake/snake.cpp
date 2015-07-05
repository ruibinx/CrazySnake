#include "snake.h"
inline void Coordinate::moveUp(int step)
{
	y -= step;
}

inline void Coordinate::moveDown(int step)
{
	y += step;
}

inline void Coordinate::moveRight(int step)
{
	x += step;
}

inline void Coordinate::moveLeft(int step)
{
	x -= step;
}

inline void Coordinate::setX(int newX)
{
	x = newX;
}
inline void Coordinate::setY(int newY)
{
	y = newY;
}

inline void SnakeBody::replace(const SnakeBody& last)
{
	location.setX(last.getCoordinate().getX());
	location.setY(last.getCoordinate().getY());
}


inline void SnakeBody::moveUp()
{
	location.moveUp(step);
}

inline void SnakeBody::moveDown()
{
	location.moveDown(step);
}

inline void SnakeBody::moveRight()
{
	location.moveRight(step);
}

inline void SnakeBody::moveLeft()
{
	location.moveLeft(step);
}

inline void SnakeBody::draw()
{
	if (isHead()){
		fillellipse(location.getX(), location.getY(), 15, 15);
	}
	else{
		circle(location.getX(), location.getY(), 10);
	}
}

inline void SnakeBody::move(int d)
{
	switch (d){
	case 0:moveUp(); break;
	case 1: moveDown(); break;
	case 2:moveLeft(); break;
	case 3:moveRight(); break;
	}
}

Snake::Snake():
	direction(), bodys()
{
	setDirection(static_cast<Direction>(random(4)));
}

void Snake::addBody(int x,int y)
{ 
	if (!bodys.empty()){
		bodys[0]->setHead(false);
	}
	SnakeBody *body = new SnakeBody(x, y, true);
	bodys.push_front(body);
}

void Snake::move()
{
	if (!bodys.empty())
	{
		for (int i = bodys.size() - 1; i + 1 != 0; i--)
		{
			if (bodys[i]->isHead())
			{
				bodys[i]->move(getDirection());
			}
			else
			{
				bodys[i]->replace(*bodys[i - 1]);
			}
		}
	}

}


void Snake::draw()
{
	for (SnakeBody*  body: bodys){
		body->draw();
	}
}


void Snake::reset()
{
	bodys.clear();
	addBody((random(39) + 1) * 20, (random(29) + 1) * 20);
}
Snake::~Snake()
{
	for (int i = 0; i != bodys.size(); i++){
		delete bodys[i];
	}
}

bool Snake::hasAteFood(const Apple& aApple)
{
	if (!bodys.empty() && bodys[0]->isHead())
	{
		if (bodys[0]->getCoordinate().getX() == aApple.getX()
			&& bodys[0]->getCoordinate().getY() == aApple.getY())
		{
			return true;
		}
	}
	return false;
}

bool Snake::hasBitSelf()
{
	if (!bodys.empty() && bodys[0]->isHead())
	{
		for (SnakeBody* body : bodys)
		{
			if (!body->isHead())
			{
				if (bodys[0]->getCoordinate().getX() == body->getCoordinate().getX()
					&& bodys[0]->getCoordinate().getY() == body->getCoordinate().getY())
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Snake::hasCrashedIntoWall()
{
	if (!bodys.empty() && bodys[0]->isHead())
	{
		bool xInWall = bodys[0]->getCoordinate().getX() <= 0 ||
			bodys[0]->getCoordinate().getX() >= 800;
		bool yInWall = bodys[0]->getCoordinate().getY() <= 0 ||
			bodys[0]->getCoordinate().getY() >= 600;
		return xInWall || yInWall;
	}
	return false;
}

void Apple::draw()
{
	setcolor(BLACK);
	fillellipse(location.getX(), location.getY(), 5, 5);
}

void Apple::newApple(const Snake &snake)
{
	int newX, newY;
	bool hasExisted = false;
	while (true)
	{
		newX = (random(39) + 1) * 20;
		newY = (random(29) + 1) * 20;
	
		for (SnakeBody *body : snake.bodys){
			if (newX == body->getCoordinate().getX()
				&& newY == body->getCoordinate().getY())
			{
				hasExisted = true;
				break;
			}
		}
		if (hasExisted)
		{
			continue;
		}
		else
		{ 
			break;
		}

	}
	location.setX(newX);
	location.setY(newY);
}