#pragma once
#include "Shashka.h"
#include <array>
#include <ctime>
#include <cstdlib>

using namespace System::Windows::Forms;
using namespace System::Drawing;

using std::pair;

ref class Board
{
public:
	Board(PictureBox^, bool);
	~Board();

	void Paint(MouseEventArgs^);
	bool getRestart();
	
private:
	void PaintFirstStep(MouseEventArgs^, bool);
	void PaintSecondStep(MouseEventArgs^);
	void Makefield(int**);
	Shashka^ getCoord(int, int);
	pair<int, int>* getMove(Shashka^,int);
	void PaintShashka(bool,int,int,bool);
	int** getA();
	void setSelected(int, int, bool);
	Shashka^ getSelected();
	int CheckEnd(bool);
	void ArtificialIntelligence();

	PictureBox^ pb;
	array<Shashka^>^ white;
	array<Shashka^>^ black;
	bool colorPlayer;
	const int N = 8;
	const int SIZE = 50;
	bool FLAG;
	Shashka^ lastdied;
	bool restart;
	bool required;
};

Board::Board(PictureBox^ p, bool whie)
{
	required = 0;
	lastdied = nullptr;
	pb = p;
	FLAG = 0;
	white = gcnew array<Shashka^>(12);
	black = gcnew array<Shashka^>(12);
	colorPlayer = whie;
	restart = 0;

	for (int i = 0; i < 12; i++)
	{
		white[i] = gcnew Shashka();
		black[i] = gcnew Shashka();
	}

	int k = 0;
	if (colorPlayer)
	{
		for (int j = N - 3; j < N; j++)
		{
			for (int i = 0; i < N; i++)
			{
				if ((i + j) % 2 == 1)
				{
					white[k]->setData(i, j, 1);
					k++;
				}
			}
		}
		k = 0;
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < N; i++)
			{
				if ((i + j) % 2 == 1)
				{
					black[k]->setData(i, j, 0);
					k++;
				}
			}
		}
	}
	else
	{
		for (int j = N - 3; j < N; j++)
		{
			for (int i = 0; i < N; i++)
			{
				if ((i + j) % 2 == 1)
				{
					black[k]->setData(i, j, 0);
					k++;
				}
			}
		}
		k = 0;
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < N; i++)
			{
				if ((i + j) % 2 == 1)
				{
					white[k]->setData(i, j, 1);
					k++;
				}
			}
		}
	}
	Makefield(this->getA());
	if (!colorPlayer)
		ArtificialIntelligence();
}

Board::~Board()
{
	pb->Enabled = false;
	pb->Visible = false;
}

int** Board::getA()
{
	int** c = new int*[N];
	for (int i = 0; i < N; i++)
	{
		c[i] = new int[N];
		for (int j = 0; j < N; j++)
		{
			c[i][j] = 0;
		}
	}

	for (int i = 0; i < 12; i++)
	{
		if (white[i]->getCheck())
			c[white[i]->getX()][white[i]->getY()] = 1;
		if (black[i]->getCheck())
			c[black[i]->getX()][black[i]->getY()] = 2;
	}
	return c;
}

Shashka^ Board::getCoord(int x, int y)
{
	for (int i = 0; i < 12; i++)
	{
		if (white[i]->getX() == x && white[i]->getY() == y && white[i]->getCheck())
			return white[i];
	}

	for (int i = 0; i < 12; i++)
	{
		if (black[i]->getX() == x && black[i]->getY() == y && black[i]->getCheck())
			return black[i];
	}

	return nullptr;
}

Shashka^ Board::getSelected()
{
	if (colorPlayer)
		for (int i = 0; i < 12; i++)
		{
			if (white[i]->getSelected())
				return white[i];
		}
	else
		for (int i = 0; i < 12; i++)
		{
			if (black[i]->getSelected())
				return black[i];
		}

	return nullptr;
}

void Board::setSelected(int X, int Y, bool f)
{
	if (colorPlayer)
	{
		for (int i = 0; i < 12; i++)
		{
			if (white[i]->getX() == X && white[i]->getY() == Y && white[i]->getCheck())
				white[i]->setSelected(f);
		}
	}
	else
	{
		for (int i = 0; i < 12; i++)
		{
			if (black[i]->getX() == X && black[i]->getY() == Y && black[i]->getCheck())
				black[i]->setSelected(f);
		}
	}
}

pair<int, int>* Board::getMove(Shashka^ sh, int f)
{
	pair<int, int>* pr = new pair<int, int>[150];

	pr[0].first = 0;
	pr[0].second = 0;
	int x = sh->getX();
	int y = sh->getY();

	int x1 = sh->getX();
	int y1 = sh->getY();

	int**w = getA();
	if (sh->getColor() == colorPlayer)
	{
		if (sh->getDamka() == 0)
		{
			y1--;
			x1--;
			if (f == 0)
			{
				if (x1 >= 0 && y1 >= 0)
				{
					if (w[x1][y1] == 0)
					{
						pr[0].first++;
						pr[pr[0].first].first = x1;
						pr[pr[0].first].second = y1;
					}
					else if (w[x1][y1] == 1 && colorPlayer == 0 || w[x1][y1] == 2 && colorPlayer)
					{
						if (x1 > 0 && y1 > 0)
						{
							x1--;
							y1--;
							if (w[x1][y1] == 0) {
								pr[0].first++;
								pr[pr[0].first].first = x1;
								pr[pr[0].first].second = y1;
							}
						}
					}
				}
				x1 = x + 1;
				y1 = y - 1;
				if (x1 <= 7 && y1 >= 0)
				{
					if (w[x1][y1] == 0)
					{
						pr[0].first++;
						pr[pr[0].first].first = x1;
						pr[pr[0].first].second = y1;
					}
					else if (w[x1][y1] == 1 && colorPlayer == 0 || w[x1][y1] == 2 && colorPlayer)
					{
						if (x1 < 7 && y1 > 0)
						{
							x1++;
							y1--;
							if (w[x1][y1] == 0) {
								pr[0].first++;
								pr[pr[0].first].first = x1;
								pr[pr[0].first].second = y1;
							}
						}
					}
				}

				x1 = x - 1;
				y1 = y + 1;
				if (x1 >= 0 && y1 <= 7 && (w[x1][y1] == 1 && colorPlayer == 0 || w[x1][y1] == 2 && colorPlayer))
				{
					if (x1 > 0 && y1 < 7)
					{
						x1--;
						y1++;
						if (w[x1][y1] == 0) {
							pr[0].first++;
							pr[pr[0].first].first = x1;
							pr[pr[0].first].second = y1;
						}
					}
				}

				x1 = x + 1;
				y1 = y + 1;
				if (x1 <= 7 && y1 <= 7 && (w[x1][y1] == 1 && colorPlayer == 0 || w[x1][y1] == 2 && colorPlayer))
				{
					if (x1 < 7 && y1 < 7)
					{
						x1++;
						y1++;
						if (w[x1][y1] == 0) {
							pr[0].first++;
							pr[pr[0].first].first = x1;
							pr[pr[0].first].second = y1;
						}
					}
				}

			}
			else if (f != 0)
			{
				if (x1 >= 0 && y1 >= 0)
				{
					if (w[x1][y1] == 1 && colorPlayer == 0 || w[x1][y1] == 2 && colorPlayer)
					{
						if (x1 > 0 && y1 > 0)
						{
							x1--;
							y1--;
							if (w[x1][y1] == 0) {
								pr[0].first++;
								pr[pr[0].first].first = x1;
								pr[pr[0].first].second = y1;
							}
						}
					}
				}
				x1 = x + 1;
				y1 = y - 1;
				if (x1 <= 7 && y1 >= 0)
				{
					if (w[x1][y1] == 1 && colorPlayer == 0 || w[x1][y1] == 2 && colorPlayer)
					{
						if (x1 < 7 && y1 > 0)
						{
							x1++;
							y1--;
							if (w[x1][y1] == 0) {
								pr[0].first++;
								pr[pr[0].first].first = x1;
								pr[pr[0].first].second = y1;
							}
						}
					}
				}

				x1 = x - 1;
				y1 = y + 1;
				if (x1 >= 0 && y1 <= 7 && (w[x1][y1] == 1 && colorPlayer == 0 || w[x1][y1] == 2 && colorPlayer))
				{
					if (x1 > 0 && y1 < 7)
					{
						x1--;
						y1++;
						if (w[x1][y1] == 0) {
							pr[0].first++;
							pr[pr[0].first].first = x1;
							pr[pr[0].first].second = y1;
						}
					}
				}

				x1 = x + 1;
				y1 = y + 1;
				if (x1 <= 7 && y1 <= 7 && (w[x1][y1] == 1 && colorPlayer == 0 || w[x1][y1] == 2 && colorPlayer))
				{
					if (x1 < 7 && y1 < 7)
					{
						x1++;
						y1++;
						if (w[x1][y1] == 0) {
							pr[0].first++;
							pr[pr[0].first].first = x1;
							pr[pr[0].first].second = y1;
						}
					}
				}
			}
		}
		else if (sh->getDamka() == 1)
		{
			y1--;
			x1--;
			if (f == 0)
			{
				while (x1 >= 0 && y1 >= 0)
				{
					if (w[x1][y1] == 0)
					{
						pr[0].first++;
						pr[pr[0].first].first = x1;
						pr[pr[0].first].second = y1;
					}
					else if (w[x1][y1] == 1 && colorPlayer == 0 || w[x1][y1] == 2 && colorPlayer)
					{
						if (x1 > 0 && y1 > 0)
						{
							x1--;
							y1--;
							if (w[x1][y1] == 0) {
								pr[0].first++;
								pr[pr[0].first].first = x1;
								pr[pr[0].first].second = y1;
							}
						}
						break;
					}
					else
					{
						break;
					}
					x1--;
					y1--;
				}

				x1 = x + 1;
				y1 = y - 1;

				while (x1 <= 7 && y1 >= 0)
				{
					if (w[x1][y1] == 0)
					{
						pr[0].first++;
						pr[pr[0].first].first = x1;
						pr[pr[0].first].second = y1;
					}
					else if (w[x1][y1] == 1 && colorPlayer == 0 || w[x1][y1] == 2 && colorPlayer)
					{
						if (x1 < 7 && y1 > 0)
						{
							x1++;
							y1--;
							if (w[x1][y1] == 0) {
								pr[0].first++;
								pr[pr[0].first].first = x1;
								pr[pr[0].first].second = y1;
							}
						}
						break;
					}
					else
					{
						break;
					}
					x1++;
					y1--;
				}

				x1 = x - 1;
				y1 = y + 1;

				while (x1 >= 0 && y1 <= 7)
				{
					if (w[x1][y1] == 0)
					{
						pr[0].first++;
						pr[pr[0].first].first = x1;
						pr[pr[0].first].second = y1;
					}
					else if (w[x1][y1] == 1 && colorPlayer == 0 || w[x1][y1] == 2 && colorPlayer)
					{
						if (x1 > 0 && y1 < 7)
						{
							x1--;
							y1++;
							if (w[x1][y1] == 0) {
								pr[0].first++;
								pr[pr[0].first].first = x1;
								pr[pr[0].first].second = y1;
							}
						}
						break;
					}
					else
					{
						break;
					}
					x1--;
					y1++;
				}

				x1 = x + 1;
				y1 = y + 1;

				while (x1 <= 7 && y1 <= 7)
				{
					if (w[x1][y1] == 0)
					{
						pr[0].first++;
						pr[pr[0].first].first = x1;
						pr[pr[0].first].second = y1;
					}
					else if (w[x1][y1] == 1 && colorPlayer == 0 || w[x1][y1] == 2 && colorPlayer)
					{
						if (x1 < 7 && y1 < 7)
						{
							x1++;
							y1++;
							if (w[x1][y1] == 0) {
								pr[0].first++;
								pr[pr[0].first].first = x1;
								pr[pr[0].first].second = y1;
							}
						}
						break;
					}
					else
					{
						break;
					}
					x1++;
					y1++;
				}

			}
			else if (f != 0)
			{
				if (lastdied == nullptr || lastdied->getX() != x1 || lastdied->getY() != y1)
					while (x1 >= 0 && y1 >= 0)
					{
						if (w[x1][y1] == 1 && colorPlayer == 0 || w[x1][y1] == 2 && colorPlayer)
						{
							if (x1 > 0 && y1 > 0)
							{
								x1--;
								y1--;
								if (w[x1][y1] == 0) {
									pr[0].first++;
									pr[pr[0].first].first = x1;
									pr[pr[0].first].second = y1;
								}
							}
							break;
						}
						else if (w[x1][y1] == 0)
						{
							x1--;
							y1--;
						}
						else break;
					}

				x1 = x + 1;
				y1 = y - 1;
				if (lastdied == nullptr || lastdied->getX() != x1 || lastdied->getY() != y1)
					while (x1 <= 7 && y1 >= 0)
					{
						if (w[x1][y1] == 1 && colorPlayer == 0 || w[x1][y1] == 2 && colorPlayer)
						{
							if (x1 < 7 && y1 > 0)
							{
								x1++;
								y1--;
								if (w[x1][y1] == 0) {
									pr[0].first++;
									pr[pr[0].first].first = x1;
									pr[pr[0].first].second = y1;
								}
							}
							break;
						}
						else if (w[x1][y1] == 0)
						{
							x1++;
							y1--;
						}
						else break;
					}

				x1 = x - 1;
				y1 = y + 1;
				if (lastdied == nullptr || lastdied->getX() != x1 || lastdied->getY() != y1)
					while (x1 >= 0 && y1 <= 7)
					{
						if (w[x1][y1] == 1 && colorPlayer == 0 || w[x1][y1] == 2 && colorPlayer)
						{
							if (x1 > 0 && y1 < 7)
							{
								x1--;
								y1++;
								if (w[x1][y1] == 0) {
									pr[0].first++;
									pr[pr[0].first].first = x1;
									pr[pr[0].first].second = y1;
								}
							}
							break;
						}
						else if (w[x1][y1] == 0)
						{
							x1--;
							y1++;
						}
						else break;
					}

				x1 = x + 1;
				y1 = y + 1;
				if (lastdied == nullptr || lastdied->getX() != x1 || lastdied->getY() != y1)
					while (x1 <= 7 && y1 <= 7)
					{
						if (w[x1][y1] == 1 && colorPlayer == 0 || w[x1][y1] == 2 && colorPlayer)
						{
							if (x1 < 7 && y1 < 7)
							{
								x1++;
								y1++;
								if (w[x1][y1] == 0) {
									pr[0].first++;
									pr[pr[0].first].first = x1;
									pr[pr[0].first].second = y1;
								}
							}
							break;
						}
						else if (w[x1][y1] == 0)
						{
							x1++;
							y1++;
						}
						else break;
					}

			}
		}
	}
	else if (sh->getColor() != colorPlayer)
	{
		if (sh->getDamka() == 0)
		{
			y1++;
			x1--;
			if (f == 0)
			{
				if (x1 >= 0 && y1 <= 7)
				{
					if (w[x1][y1] == 0)
					{
						pr[0].first++;
						pr[pr[0].first].first = x1;
						pr[pr[0].first].second = y1;
					}
					else if (w[x1][y1] == 1 && colorPlayer == 1 || w[x1][y1] == 2 && colorPlayer == 0)
					{
						if (x1 > 0 && y1 < 7)
						{
							x1--;
							y1++;
							if (w[x1][y1] == 0) {
								pr[0].first++;
								pr[pr[0].first].first = x1;
								pr[pr[0].first].second = y1;
							}
						}
					}
				}
				x1 = x + 1;
				y1 = y + 1;
				if (x1 <= 7 && y1 <= 7)
				{
					if (w[x1][y1] == 0)
					{
						pr[0].first++;
						pr[pr[0].first].first = x1;
						pr[pr[0].first].second = y1;
					}
					else if (w[x1][y1] == 1 && colorPlayer == 1 || w[x1][y1] == 2 && colorPlayer == 0)
					{
						if (x1 < 7 && y1 < 7)
						{
							x1++;
							y1++;
							if (w[x1][y1] == 0) {
								pr[0].first++;
								pr[pr[0].first].first = x1;
								pr[pr[0].first].second = y1;
							}
						}
					}
				}

				x1 = x - 1;
				y1 = y - 1;
				if (x1 >= 0 && y1 >= 0 && ((w[x1][y1] == 1 && colorPlayer == 1) || (w[x1][y1] == 2 && colorPlayer == 0)))
				{
					if (x1 > 0 && y1 > 0)
					{
						x1--;
						y1--;
						if (w[x1][y1] == 0) {
							pr[0].first++;
							pr[pr[0].first].first = x1;
							pr[pr[0].first].second = y1;
						}
					}
				}

				x1 = x + 1;
				y1 = y - 1;
				if (x1 <= 7 && y1 >= 0 && ((w[x1][y1] == 1 && colorPlayer == 1) || (w[x1][y1] == 2 && colorPlayer == 0)))
				{
					if (x1 < 7 && y1 > 0)
					{
						x1++;
						y1--;
						if (w[x1][y1] == 0) {
							pr[0].first++;
							pr[pr[0].first].first = x1;
							pr[pr[0].first].second = y1;
						}
					}
				}
			}
			else if (f != 0)
			{
				if (x1 >= 0 && y1 <= 7)
				{
					if (w[x1][y1] == 1 && colorPlayer == 1 || w[x1][y1] == 2 && colorPlayer == 0)
					{
						if (x1 > 0 && y1 < 7)
						{
							x1--;
							y1++;
							if (w[x1][y1] == 0) {
								pr[0].first++;
								pr[pr[0].first].first = x1;
								pr[pr[0].first].second = y1;
							}
						}
					}
				}
				x1 = x + 1;
				y1 = y + 1;
				if (x1 <= 7 && y1 <= 7)
				{
					if (w[x1][y1] == 1 && colorPlayer == 1 || w[x1][y1] == 2 && colorPlayer == 0)
					{
						if (x1 < 7 && y1 < 7)
						{
							x1++;
							y1++;
							if (w[x1][y1] == 0) {
								pr[0].first++;
								pr[pr[0].first].first = x1;
								pr[pr[0].first].second = y1;
							}
						}
					}
				}

				x1 = x - 1;
				y1 = y - 1;
				if (x1 >= 0 && y1 >= 0 && (w[x1][y1] == 1 && colorPlayer == 1 || w[x1][y1] == 2 && colorPlayer == 0))
				{
					if (x1 > 0 && y1 > 0)
					{
						x1--;
						y1--;
						if (w[x1][y1] == 0) {
							pr[0].first++;
							pr[pr[0].first].first = x1;
							pr[pr[0].first].second = y1;
						}
					}
				}

				x1 = x + 1;
				y1 = y - 1;
				if (x1 <= 7 && y1 >= 0 && (w[x1][y1] == 1 && colorPlayer == 1 || w[x1][y1] == 2 && colorPlayer == 0))
				{
					if (x1 < 7 && y1 > 0)
					{
						x1++;
						y1--;
						if (w[x1][y1] == 0) {
							pr[0].first++;
							pr[pr[0].first].first = x1;
							pr[pr[0].first].second = y1;
						}
					}
				}
			}
		}
		else if (sh->getDamka() == 1)
		{
			y1--;
			x1--;
			if (f == 0)
			{
				while (x1 >= 0 && y1 >= 0)
				{
					if (w[x1][y1] == 0)
					{
						pr[0].first++;
						pr[pr[0].first].first = x1;
						pr[pr[0].first].second = y1;
					}
					else if (w[x1][y1] == 1 && colorPlayer == 1 || w[x1][y1] == 2 && colorPlayer == 0)
					{
						if (x1 > 0 && y1 > 0)
						{
							x1--;
							y1--;
							if (w[x1][y1] == 0) {
								pr[0].first++;
								pr[pr[0].first].first = x1;
								pr[pr[0].first].second = y1;
							}
						}
						break;
					}
					else
					{
						break;
					}
					x1--;
					y1--;
				}

				x1 = x + 1;
				y1 = y - 1;

				while (x1 <= 7 && y1 >= 0)
				{
					if (w[x1][y1] == 0)
					{
						pr[0].first++;
						pr[pr[0].first].first = x1;
						pr[pr[0].first].second = y1;
					}
					else if (w[x1][y1] == 1 && colorPlayer == 1 || w[x1][y1] == 2 && colorPlayer == 0)
					{
						if (x1 < 7 && y1 > 0)
						{
							x1++;
							y1--;
							if (w[x1][y1] == 0) {
								pr[0].first++;
								pr[pr[0].first].first = x1;
								pr[pr[0].first].second = y1;
							}
						}
						break;
					}
					else
					{
						break;
					}
					x1++;
					y1--;
				}

				x1 = x - 1;
				y1 = y + 1;

				while (x1 >= 0 && y1 <= 7)
				{
					if (w[x1][y1] == 0)
					{
						pr[0].first++;
						pr[pr[0].first].first = x1;
						pr[pr[0].first].second = y1;
					}
					else if (w[x1][y1] == 1 && colorPlayer == 1 || w[x1][y1] == 2 && colorPlayer == 0)
					{
						if (x1 > 0 && y1 < 7)
						{
							x1--;
							y1++;
							if (w[x1][y1] == 0) {
								pr[0].first++;
								pr[pr[0].first].first = x1;
								pr[pr[0].first].second = y1;
							}
						}
						break;
					}
					else
					{
						break;
					}
					x1--;
					y1++;
				}

				x1 = x + 1;
				y1 = y + 1;

				while (x1 <= 7 && y1 <= 7)
				{
					if (w[x1][y1] == 0)
					{
						pr[0].first++;
						pr[pr[0].first].first = x1;
						pr[pr[0].first].second = y1;
					}
					else if (w[x1][y1] == 1 && colorPlayer == 1 || w[x1][y1] == 2 && colorPlayer == 0)
					{
						if (x1 < 7 && y1 < 7)
						{
							x1++;
							y1++;
							if (w[x1][y1] == 0) {
								pr[0].first++;
								pr[pr[0].first].first = x1;
								pr[pr[0].first].second = y1;
							}
						}
						break;
					}
					else
					{
						break;
					}
					x1++;
					y1++;
				}

			}
			else if (f != 0)
			{
				if (lastdied == nullptr || lastdied->getX() != x1 || lastdied->getY() != y1)
					while (x1 >= 0 && y1 >= 0)
					{
						if (w[x1][y1] == 1 && colorPlayer == 1 || w[x1][y1] == 2 && colorPlayer == 0)
						{
							if (x1 > 0 && y1 > 0)
							{
								x1--;
								y1--;
								if (w[x1][y1] == 0) {
									pr[0].first++;
									pr[pr[0].first].first = x1;
									pr[pr[0].first].second = y1;
								}
							}
							break;
						}
						else if (w[x1][y1] == 0)
						{
							x1--;
							y1--;
						}
						else break;
					}

				x1 = x + 1;
				y1 = y - 1;
				if (lastdied == nullptr || lastdied->getX() != x1 || lastdied->getY() != y1)
					while (x1 <= 7 && y1 >= 0)
					{
						if (w[x1][y1] == 1 && colorPlayer == 1 || w[x1][y1] == 2 && colorPlayer == 0)
						{
							if (x1 < 7 && y1 > 0)
							{
								x1++;
								y1--;
								if (w[x1][y1] == 0) {
									pr[0].first++;
									pr[pr[0].first].first = x1;
									pr[pr[0].first].second = y1;
								}
							}
							break;
						}
						else if (w[x1][y1] == 0)
						{
							x1++;
							y1--;
						}
						else break;
					}

				x1 = x - 1;
				y1 = y + 1;
				if (lastdied == nullptr || lastdied->getX() != x1 || lastdied->getY() != y1)
					while (x1 >= 0 && y1 <= 7)
					{
						if (w[x1][y1] == 1 && colorPlayer == 1 || w[x1][y1] == 2 && colorPlayer == 0)
						{
							if (x1 > 0 && y1 < 7)
							{
								x1--;
								y1++;
								if (w[x1][y1] == 0) {
									pr[0].first++;
									pr[pr[0].first].first = x1;
									pr[pr[0].first].second = y1;
								}
							}
							break;
						}
						else if (w[x1][y1] == 0)
						{
							x1--;
							y1++;
						}
						else break;
					}

				x1 = x + 1;
				y1 = y + 1;
				if (lastdied == nullptr || lastdied->getX() != x1 || lastdied->getY() != y1)
					while (x1 <= 7 && y1 <= 7)
					{
						if (w[x1][y1] == 1 && colorPlayer == 1 || w[x1][y1] == 2 && colorPlayer == 0)
						{
							if (x1 < 7 && y1 < 7)
							{
								x1++;
								y1++;
								if (w[x1][y1] == 0) {
									pr[0].first++;
									pr[pr[0].first].first = x1;
									pr[pr[0].first].second = y1;
								}
							}
							break;
						}
						else if (w[x1][y1] == 0)
						{
							x1++;
							y1++;
						}
						else break;
					}
			}
		}
	}

	for (int i = 0; i < N; i++)
		delete[] w[i];
	delete[] w;
	return pr;
}

void Board::PaintShashka(bool colors, int x, int y, bool damka)
{
	Brush ^MyBrushB = Brushes::Black;
	Pen ^MyPenB = Pens::Black;
	Brush ^MyBrushL = Brushes::LightYellow;
	Graphics^ g = pb->CreateGraphics();
	if (!damka)
	{
		if (colors)
		{
			g->FillEllipse(MyBrushL, x * SIZE + 5, y * SIZE + 5, SIZE - 10, SIZE - 10);
		}
		else
		{
			g->FillEllipse(MyBrushB, x * SIZE + 5, y * SIZE + 5, SIZE - 10, SIZE - 10);
		}
	}
	else
	{
		if (colors)
		{
			g->FillEllipse(MyBrushL, x * SIZE + 5, y * SIZE + 5, SIZE - 10, SIZE - 10);
			g->FillEllipse(MyBrushB, x * SIZE + 14, y * SIZE + 14, SIZE - 28, SIZE - 28);
		}
		else
		{
			g->FillEllipse(MyBrushB, x * SIZE + 5, y * SIZE + 5, SIZE - 10, SIZE - 10);
			g->FillEllipse(MyBrushL, x * SIZE + 14, y * SIZE + 14, SIZE - 28, SIZE - 28);
		}
	}
	g->DrawRectangle(MyPenB, 0, 0, 400, 400);
}

void Board::Makefield(int** e)
{
	Graphics^ g = pb->CreateGraphics();
	Brush ^MyBrushB = Brushes::Black;
	Brush ^MyBrushL = Brushes::LightYellow;
	Brush ^MyBrushS = Brushes::SandyBrown;
	Brush ^MyBrushN = Brushes::NavajoWhite;
	Pen ^MyPenB = System::Drawing::Pens::Black;
	//Pen ^MyPenR = System::Drawing::Pens::Red;
	//Pen ^MyPenW = System::Drawing::Pens::White;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((i + j) % 2 == 0)
			{
				g->FillRectangle(MyBrushN, i * SIZE, j * SIZE, SIZE, SIZE);
			}
			else
			{
				g->FillRectangle(MyBrushS, i * SIZE, j * SIZE, SIZE, SIZE);
			}

			if (e[i][j] == 1)
			{
				g->FillEllipse(MyBrushL, i * SIZE + 5, j * SIZE + 5, SIZE - 10, SIZE - 10);
			}
			else if (e[i][j] == 2)
			{
				g->FillEllipse(MyBrushB, i * SIZE + 5, j * SIZE + 5, SIZE - 10, SIZE - 10);
			}
		}
	}
	g->DrawRectangle(MyPenB, 0, 0, 400, 400);
}

void Board::ArtificialIntelligence()
{
	srand(time(0));
	required = 0;
	Brush ^MyBrushS = Brushes::SandyBrown;
	Brush ^MyBrushB = Brushes::Black;
	Brush ^MyBrushL = Brushes::LightYellow;
	Graphics^ g = pb->CreateGraphics();
	bool anticol = 1 - colorPlayer;
	int** w = getA();
	int score = 0;
	int* x = new int[1000];
	int* y = new int[1000];
	int* ind = new int[1000];
	for (int i = 0; i < 1000; i++)
	{
		x[i] = y[i] = ind[i] = 0;
	}
	pair<int, int>* pr = new pair<int, int>[5];
	for (int i = 0; i < 5; i++)
	{
		pr[i].first = 0;
		pr[i].second = 0;
	}
	pair<int, int>* ti;
	int x1, y1;

	bool flag4 = false;

	if (colorPlayer)
	{
		for (int i = 0; i < 12; i++)
		{
			if (black[i]->getCheck())
			{
				ti = getMove(black[i], 1);
				if (ti[0].first != 0)
				{
					flag4 = true;
					for (int k = 1; k <= ti[0].first; k++)
					{
						score++;
						x[score - 1] = ti[k].first;
						y[score - 1] = ti[k].second;
						ind[score - 1] = i;
					}
					delete[] ti;
				}
			}
		}

		if (flag4 == false)
		{
			for (int i = 0; i < 12; i++)
			{
				if (black[i]->getCheck())
				{
					ti = getMove(black[i], 0);
					for (int k = 1; k <= ti[0].first; k++)
					{
						score++;
						x[score - 1] = ti[k].first;
						y[score - 1] = ti[k].second;
						ind[score - 1] = i;
					}
					delete[] ti;
				}
			}
		}
	}
	else if (!colorPlayer)
	{
		for (int i = 0; i < 12; i++)
		{
			if (white[i]->getCheck())
			{
				ti = getMove(white[i], 1);
				if (ti[0].first != 0)
				{
					flag4 = true;
					for (int k = 1; k <= ti[0].first; k++)
					{
						score++;
						x[score - 1] = ti[k].first;
						y[score - 1] = ti[k].second;
						ind[score - 1] = i;
					}
					delete[] ti;
				}
			}
		}

		if (flag4 == false)
		{
			for (int i = 0; i < 12; i++)
			{
				if (white[i]->getCheck())
				{
					ti = getMove(white[i], 0);
					for (int k = 1; k <= ti[0].first; k++)
					{
						score++;
						x[score - 1] = ti[k].first;
						y[score - 1] = ti[k].second;
						ind[score - 1] = i;
					}
					delete[] ti;
				}
			}
		}
	}

	int ran = rand() % score;
	bool flag = false;
	Shashka^ sh;
	lastdied = nullptr;

	if (colorPlayer)
	{
		sh = black[ind[ran]];
		if (abs(sh->getX() - x[ran]) >= 2)
		{
			Shashka^ sh1;
			if (sh->getDamka() == 0) {
				sh1 = getCoord((black[ind[ran]]->getX() + x[ran]) / 2, (black[ind[ran]]->getY() + y[ran]) / 2);
				g->FillRectangle(MyBrushS, sh1->getX()*SIZE, sh1->getY()*SIZE, SIZE, SIZE);
				lastdied = sh1;
				sh1->setCheck(0);
				flag = true;
			}
			else
			{
				int d1 = x[ran];
				int d2 = y[ran];
				if (d1 > sh->getX()) d1--;
				else d1++;
				if (d2 > sh->getY()) d2--;
				else d2++;

				sh1 = getCoord(d1, d2);
				if (sh1 != nullptr)
				{
					g->FillRectangle(MyBrushS, sh1->getX()*SIZE, sh1->getY()*SIZE, SIZE, SIZE);
					lastdied = sh1;
					sh1->setCheck(0);
					flag = true;
				}
			}
		}
		g->FillRectangle(MyBrushS, sh->getX()*SIZE, sh->getY()*SIZE, SIZE, SIZE);
		sh->setCoord(x[ran], y[ran]);
		if (sh->getY() == 7) sh->setDamka(1);
		PaintShashka(anticol, x[ran], y[ran], sh->getDamka());

	}
	else if (!colorPlayer)
	{
		sh = white[ind[ran]];
		if (abs(white[ind[ran]]->getX() - x[ran]) >= 2)
		{
			Shashka^ sh1;
			if (sh->getDamka() == 0) {
				sh1 = getCoord((white[ind[ran]]->getX() + x[ran]) / 2, (white[ind[ran]]->getY() + y[ran]) / 2);
				g->FillRectangle(MyBrushS, sh1->getX()*SIZE, sh1->getY()*SIZE, SIZE, SIZE);
				lastdied = sh1;
				sh1->setCheck(0);
				flag = true;
			}
			else
			{
				int d1 = x[ran];
				int d2 = y[ran];
				if (d1 > sh->getX()) d1--;
				else d1++;
				if (d2 > sh->getY()) d2--;
				else d2++;

				sh1 = getCoord(d1, d2);
				if (sh1 != nullptr)
				{
					g->FillRectangle(MyBrushS, sh1->getX()*SIZE, sh1->getY()*SIZE, SIZE, SIZE);
					lastdied = sh1;
					sh1->setCheck(0);
					flag = true;
				}
			}
		}
		g->FillRectangle(MyBrushS, sh->getX()*SIZE, sh->getY()*SIZE, SIZE, SIZE);
		sh->setCoord(x[ran], y[ran]);
		if (sh->getY() == 7) sh->setDamka(1);
		PaintShashka(anticol, x[ran], y[ran], sh->getDamka());
	}

	pr[0].first = -1;
	if (flag == true)
	{
		while (true)
		{
			for (int i = 0; i < 2e8; i++)
				;

			for (int i = 0; i < 4; i++)
			{
				pr[i].first = 0;
				pr[i].second = 0;
			}

			int xx, yy;
			Shashka^ sh2;
			if (sh->getDamka() == 0)
			{
				ti = getMove(sh, 1);
				for (int k = 1; k <= ti[0].first; k++)
				{
					pr[0].first++;
					pr[pr[0].first].first = ti[k].first;
					pr[pr[0].first].second = ti[k].second;
				}
				delete[] ti;
			}
			else if (sh->getDamka() == 1)
			{
				xx = sh->getX();
				yy = sh->getY();
				xx--;
				yy--;
				if (lastdied == nullptr || lastdied->getX() != xx || lastdied->getY() != yy)
					while (xx > 0 && yy > 0)
					{
						sh2 = getCoord(xx, yy);
						if (sh2 != nullptr && sh2->getColor() != sh->getColor())
						{
							xx--;
							yy--;
							if (getCoord(xx, yy) == nullptr)
							{
								pr[0].first++;
								pr[pr[0].first].first = xx;
								pr[pr[0].first].second = yy;
							}
							break;
						}
						else if (sh2 == nullptr)
						{
							xx--;
							yy--;
						}
						else break;
					}
				xx = sh->getX();
				yy = sh->getY();
				xx++;
				yy--;
				if (lastdied == nullptr || lastdied->getX() != xx || lastdied->getY() != yy)
					while (xx < 7 && yy > 0)
					{
						sh2 = getCoord(xx, yy);
						if (sh2 != nullptr && sh2->getColor() != sh->getColor())
						{
							xx++;
							yy--;

							if (getCoord(xx, yy) == nullptr)
							{
								pr[0].first++;
								pr[pr[0].first].first = xx;
								pr[pr[0].first].second = yy;
							}
							break;
						}
						else if (sh2 == nullptr)
						{
							xx++;
							yy--;
						}
						else break;
					}

				xx = sh->getX();
				yy = sh->getY();
				xx++;
				yy++;
				if (lastdied == nullptr || lastdied->getX() != xx || lastdied->getY() != yy)
					while (xx < 7 && yy < 7)
					{
						sh2 = getCoord(xx, yy);
						if (sh2 != nullptr && sh2->getColor() != sh->getColor())
						{
							xx++;
							yy++;

							if (getCoord(xx, yy) == nullptr)
							{
								pr[0].first++;
								pr[pr[0].first].first = xx;
								pr[pr[0].first].second = yy;
							}
							break;
						}
						else if (sh2 == nullptr)
						{
							xx++;
							yy++;
						}
						else break;
					}

				xx = sh->getX();
				yy = sh->getY();
				xx--;
				yy++;
				if (lastdied == nullptr || lastdied->getX() != xx || lastdied->getY() != yy)
					while (xx > 0 && yy < 7)
					{
						sh2 = getCoord(xx, yy);
						if (sh2 != nullptr && sh2->getColor() != sh->getColor())
						{
							xx--;
							yy++;

							if (getCoord(xx, yy) == nullptr)
							{
								pr[0].first++;
								pr[pr[0].first].first = xx;
								pr[pr[0].first].second = yy;
							}
							break;
						}
						else if (sh2 == nullptr)
						{
							xx--;
							yy++;
						}
						else break;
					}
			}


			if (pr[0].first == 0)
			{
				break;
			}
			else
			{
				int ra = rand() % pr[0].first + 1;

				xx = pr[ra].first;
				if (xx > sh->getX()) xx--; else xx++;
				yy = pr[ra].second;
				if (yy > sh->getY()) yy--; else yy++;
				sh2 = getCoord(xx, yy);
				if (sh2->getColor() == sh->getColor()) break;

				g->FillRectangle(MyBrushS, sh2->getX()*SIZE, sh2->getY()*SIZE, SIZE, SIZE);
				lastdied = sh2;
				sh2->setCheck(0);

				g->FillRectangle(MyBrushS, sh->getX()*SIZE, sh->getY()*SIZE, SIZE, SIZE);
				sh->setCoord(pr[ra].first, pr[ra].second);
				if (sh->getY() == 7) sh->setDamka(1);
				PaintShashka(anticol, pr[ra].first, pr[ra].second, sh->getDamka());
			}

		}
	}

	if (CheckEnd(colorPlayer) == 2)
	{
		MessageBox::Show("Поздравляем с победой Чёрных!", "Победа",
			MessageBoxButtons::OK, MessageBoxIcon::None);
		restart = 1;
	}
	else if (CheckEnd(colorPlayer) == 1)
	{
		MessageBox::Show("Поздравляем с победой Белых!", "Победа",
			MessageBoxButtons::OK, MessageBoxIcon::None);
		restart = 1;
	}

	delete[] x;
	delete[] y;
	delete[] ind;
	for (int i = 0; i < N; i++)
		delete[] w[i];
	delete[] w;

	delete pr;

	if (restart == 1) return;

	score = 0;
	x = new int[1000];
	y = new int[1000];
	ind = new int[1000];
	for (int i = 0; i < 1000; i++)
	{
		x[i] = y[i] = ind[i] = 0;
	}

	flag4 = false;
	if (colorPlayer == 1)
	{
		for (int i = 0; i < 12; i++)
		{
			if (white[i]->getCheck())
			{
				ti = getMove(white[i], 1);
				if (ti[0].first != 0)
				{
					flag4 = true;
					for (int k = 1; k <= ti[0].first; k++)
					{
						score++;
						x[score - 1] = ti[k].first;
						y[score - 1] = ti[k].second;
						ind[score - 1] = i;
					}
					delete[] ti;
				}
			}
		}
	}
	else if (colorPlayer == 0)
	{
		for (int i = 0; i < 12; i++)
		{
			if (black[i]->getCheck())
			{
				ti = getMove(black[i], 1);
				if (ti[0].first != 0)
				{
					flag4 = true;
					for (int k = 1; k <= ti[0].first; k++)
					{
						score++;
						x[score - 1] = ti[k].first;
						y[score - 1] = ti[k].second;
						ind[score - 1] = i;
					}
					delete[] ti;
				}
			}
		}
	}

	if (score != 0)
	{
		required = 1;
		Pen^ MyPenM = Pens::Magenta;
		Pen^ MyPenD = Pens::DodgerBlue;
		Graphics^ g = pb->CreateGraphics();

		for (int i = 0; i < score; i++)
		{
			g->DrawEllipse(MyPenD, x[i] * SIZE + 5, y[i] * SIZE + 5, SIZE - 10, SIZE - 10);
			if (colorPlayer == 1)
				g->DrawEllipse(MyPenM, white[ind[i]]->getX()*SIZE + 5, white[ind[i]]->getY()*SIZE + 5, SIZE - 10, SIZE - 10);
			else
				g->DrawEllipse(MyPenM, black[ind[i]]->getX()*SIZE + 5, black[ind[i]]->getY()*SIZE + 5, SIZE - 10, SIZE - 10);
		}

	}
	delete[] x;
	delete[] y;
	delete[] ind;
}

void Board::Paint(MouseEventArgs^  e)
{

	if (getSelected() == nullptr)
		PaintFirstStep(e, 0);
	else
		PaintSecondStep(e);
}

void Board::PaintFirstStep(MouseEventArgs^  e, bool fr)
{
	Graphics^ g = pb->CreateGraphics();
	Pen^ MyPen;
	if (colorPlayer)
		MyPen = Pens::Red;
	else
		MyPen = Pens::Lime;

	Pen^ MyPenS = Pens::SandyBrown;
	Pen ^MyPenB = Pens::Black;
	Pen ^MyPenL = Pens::LightYellow;
	Pen^ MyPenM = Pens::Magenta;
	Pen^ MyPenD = Pens::DodgerBlue;

	int x = e->Location.X;
	int y = e->Location.Y;
	x /= SIZE;
	y /= SIZE;

	pair<int, int>* ti;
	int score = 0;
	bool flag4 = false;
	int* x0 = new int[1000];
	int* y0 = new int[1000];
	int* ind = new int[1000];
	for (int i = 0; i < 1000; i++)
	{
		x0[i] = y0[i] = ind[i] = 0;
	}

	if (required == 1)
	{
		if (colorPlayer == 1)
		{
			for (int i = 0; i < 12; i++)
			{
				if (white[i]->getCheck())
				{
					ti = getMove(white[i], 1);
					if (ti[0].first != 0)
					{
						flag4 = true;
						for (int k = 1; k <= ti[0].first; k++)
						{
							score++;
							x0[score - 1] = ti[k].first;
							y0[score - 1] = ti[k].second;
							ind[score - 1] = i;
						}
						delete[] ti;
					}
				}
			}
		}
		else if (colorPlayer == 0)
		{
			for (int i = 0; i < 12; i++)
			{
				if (black[i]->getCheck())
				{
					ti = getMove(black[i], 1);
					if (ti[0].first != 0)
					{
						flag4 = true;
						for (int k = 1; k <= ti[0].first; k++)
						{
							score++;
							x0[score - 1] = ti[k].first;
							y0[score - 1] = ti[k].second;
							ind[score - 1] = i;
						}
						delete[] ti;
					}
				}
			}
		}
		flag4 = false;
		for (int i = 0; i < score; i++)
		{
			if (colorPlayer == 1 && white[ind[i]]->getX() == x && white[ind[i]]->getY() == y)
			{
				flag4 = true;
				break;
			}
			else if (colorPlayer == 0 && black[ind[i]]->getX() == x && black[ind[i]]->getY() == y)
			{
				flag4 = true;
				break;
			}
		}

		if (flag4)
		{
			for (int i = 0; i < score; i++)
			{
				if (colorPlayer == 1)
					g->DrawEllipse(MyPenL, white[ind[i]]->getX()*SIZE + 5, white[ind[i]]->getY()*SIZE + 5, SIZE - 10, SIZE - 10);
				else if (colorPlayer == 0)
					g->DrawEllipse(MyPenB, black[ind[i]]->getX()*SIZE + 5, black[ind[i]]->getY()*SIZE + 5, SIZE - 10, SIZE - 10);

				g->DrawEllipse(MyPenS, x0[i] * SIZE + 5, y0[i] * SIZE + 5, SIZE - 10, SIZE - 10);
			}

			setSelected(x, y, 1); // убрать требуемые хода
		}
		else
		{
			for (int i = 0; i < score; i++)
			{
				g->DrawEllipse(MyPenD, x0[i] * SIZE + 5, y0[i] * SIZE + 5, SIZE - 10, SIZE - 10);
				if (colorPlayer == 1)
					g->DrawEllipse(MyPenM, white[ind[i]]->getX()*SIZE + 5, white[ind[i]]->getY()*SIZE + 5, SIZE - 10, SIZE - 10);
				else
					g->DrawEllipse(MyPenM, black[ind[i]]->getX()*SIZE + 5, black[ind[i]]->getY()*SIZE + 5, SIZE - 10, SIZE - 10);
			}
			delete[] x0;
			delete[] y0;
			delete[] ind;
			return; // вернуть требуемые
		}
	}
	else
	{
		setSelected(x, y, 1);
	}

	Shashka^ sh = getSelected();

	if (sh != nullptr)
	{
		pair<int, int>* pr;
		if (required == 1)
			pr = getMove(sh, 1);
		else
			pr = getMove(sh, fr);

		if (sh->getColor() == colorPlayer)
		{
			sh->setSelected(1);
			g->DrawEllipse(MyPen, sh->getX()*SIZE + 5, sh->getY()*SIZE + 5, SIZE - 10, SIZE - 10);
			for (int i = 1; i <= pr[0].first; i++)
			{
				g->DrawEllipse(MyPenD, pr[i].first*SIZE + 5, pr[i].second*SIZE + 5, SIZE - 10, SIZE - 10);
			}
		}
	}
	delete[] x0;
	delete[] y0;
	delete[] ind;
}

void Board::PaintSecondStep(MouseEventArgs^  e)
{
	Graphics^ g = pb->CreateGraphics();
	Brush ^MyBrushB = Brushes::Black;
	Brush ^MyBrushL = Brushes::LightYellow;
	Brush ^MyBrushS = Brushes::SandyBrown;
	Brush ^MyBrushN = Brushes::NavajoWhite;
	Pen^ MyPen;
	if (colorPlayer)
		MyPen = Pens::LightYellow;
	else
		MyPen = Pens::Black;

	Pen^ MyPenS = Pens::SandyBrown;

	Shashka^ sh = getSelected();
	int x = e->Location.X;
	int y = e->Location.Y;
	x /= SIZE;
	y /= SIZE;
	int d = -1;
	bool flag2 = false;

	pair<int, int>* pr;

	pr = getMove(sh, (required || FLAG));

	for (int i = 1; i <= pr[0].first; i++)
	{
		if (pr[i].first == x && pr[i].second == y)
		{
			flag2 = true;
			pr[0].second = i;
		}
	}

	if (!flag2 && !FLAG)
	{
		for (int i = 1; i <= pr[0].first; i++)
		{
			g->DrawEllipse(MyPenS, pr[i].first*SIZE + 5, pr[i].second*SIZE + 5, SIZE - 10, SIZE - 10);
		}
		g->DrawEllipse(MyPen, sh->getX()*SIZE + 5, sh->getY()*SIZE + 5, SIZE - 10, SIZE - 10);
		sh->setSelected(0);
		PaintFirstStep(e, 0);
	}
	else if (flag2)
	{
		bool flag = false;
		for (int i = 1; i <= pr[0].first; i++)
		{
			g->DrawEllipse(MyPenS, pr[i].first*SIZE + 5, pr[i].second*SIZE + 5, SIZE - 10, SIZE - 10);
		}
		g->FillRectangle(MyBrushS, sh->getX()*SIZE, sh->getY()*SIZE, SIZE, SIZE);
		lastdied = nullptr;

		if (abs(pr[pr[0].second].first - sh->getX()) >= 2)
		{
			Shashka^ sh1;
			if (sh->getDamka() == 0)
			{
				sh1 = getCoord((pr[pr[0].second].first + sh->getX()) / 2, (pr[pr[0].second].second + sh->getY()) / 2);
				g->FillRectangle(MyBrushS, sh1->getX()*SIZE, sh1->getY()*SIZE, SIZE, SIZE);
				sh1->setCheck(0);
				lastdied = sh1;
				flag = true;
			}
			else
			{
				int d1 = pr[pr[0].second].first;
				int d2 = pr[pr[0].second].second;
				if (d1 > sh->getX()) d1--;
				else d1++;
				if (d2 > sh->getY()) d2--;
				else d2++;

				sh1 = getCoord(d1, d2);
				if (sh1 != nullptr)
				{
					g->FillRectangle(MyBrushS, sh1->getX()*SIZE, sh1->getY()*SIZE, SIZE, SIZE);
					lastdied = sh1;
					sh1->setCheck(0);
					flag = true;
				}

			}
		}
		sh->setSelected(0);
		sh->setCoord(pr[pr[0].second].first, pr[pr[0].second].second);
		if (sh->getY() == 0) sh->setDamka(1);


		PaintShashka(colorPlayer, pr[pr[0].second].first, pr[pr[0].second].second, sh->getDamka());
		FLAG = 0;
		required = 0;
		pr = getMove(sh, 1);

		if (!flag || pr[0].first == 0)
		{
			for (int i = 0; i < 2e8; i++)
				;
			if (CheckEnd(1 - colorPlayer) == 0)
			{
				ArtificialIntelligence();
			}
			else if (CheckEnd(1 - colorPlayer) == 1)
			{
				restart = 1;
				MessageBox::Show("Поздравляем с победой Белых!", "Победа",
					MessageBoxButtons::OK, MessageBoxIcon::None);

				return;
			}
			else if (CheckEnd(1 - colorPlayer) == 2)
			{
				restart = 1;
				MessageBox::Show("Поздравляем с победой Чёрных!", "Победа",
					MessageBoxButtons::OK, MessageBoxIcon::None);

				return;
			}
		}
		else
		{
			FLAG = 1;
			PaintFirstStep(e, 1);
		}
	}
}

int Board::CheckEnd(bool f)
{
	int k = 0;
	bool flag = false;
	pair<int, int>* qwer;
	if (f)
	{
		for (int i = 0; i < 12; i++)
		{
			if (white[i]->getCheck())
			{
				qwer = getMove(white[i], 0);
				if (qwer[0].first)
				{
					flag = true;
					delete[] qwer;
					break;
				}
			}
		}

		if (!flag)
		{
			return 2;
		}
	}
	else
	{
		flag = false;
		for (int i = 0; i < 12; i++)
		{
			if (black[i]->getCheck())
			{
				qwer = getMove(black[i], 0);
				if (qwer[0].first)
				{
					flag = true;
					delete[] qwer;
					break;
				}
			}
		}

		if (!flag)
		{
			return 1;
		}
	}
	return 0;
}

bool Board::getRestart()
{
	return restart;
}
