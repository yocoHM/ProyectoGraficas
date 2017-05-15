#include "Grid.hpp"

Grid::Grid(int _X, int _Y)
{
	X = _X;
	Y = _Y;

	for(int i = 0; i < X; i++)
	{
		std::vector<Platform*> row;			
		for(int j = 0; j < Y; j++)
		{
			float color = rand() % 3 + 1;
			Platform * p = new Platform();			
			if(color == 1)
				p->setColor(Platform::Color::RED);
			if(color == 2)
				p->setColor(Platform::Color::GREEN);
			if(color == 3)
				p->setColor(Platform::Color::BLUE);
			p->setTranslation(i, 0, j);
			row.push_back(p);
		}
		platforms.push_back(row);
	}
}

void Grid::changeColor(Platform::Color newColor)
{
	activeColor = newColor;
	for(int i = 0; i < X; i++)
	{
		for(int j = 0; j < Y; j++)
		{
			platforms[i][j]->changeActiveColor(newColor);
		}		
	}
}

void Grid::Draw()
{
	for(int i = 0; i < X; i++)
	{
		for(int j = 0; j < Y; j++)
		{
			platforms[i][j]->Draw();
		}
	}
}

bool Grid::tikiLives(Object * object)
{
	for(int i = 0; i < X; i++)
	{
		for(int j = 0; j < Y; j++)
		{
			if(object->intersects(platforms[i][j]))
			{
				if(!platforms[i][j]->getActive())
				{
					return false;
				}
				else 
				{
					return true;
				}
			}
		}
	}
	return false;
}
