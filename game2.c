#include<locale.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>
//#include<W,n>
static char playground[8][8];
int avaible_moves[24][3];

void colofrullPrint(char* str)
{
	printf("%c[1;31m%s\n",str, 27); // red
}

int MoveRotations[8][2] = {
	{ 1,0 },
	{ -1,0 },
	{ 0,1 },
	{ 0,-1 },
	{ 1,1 },
	{ 1,-1 },
	{ -1,1 },
	{ -1,-1 }, 
};
const char x_ = 'x', o_ = 'o', player1 = 'x', player2 = 'o';
int x_point = 0, o_point = 0;
int testAll(char[][8], char, int, int, int);

char reversedChar(char cx)
{
	if (cx == x_) return o_;
	else if (cx == o_) return x_;
	else return 0;
}
int getRowInt(char row)
{
	row = toupper(row);
	switch (row)
	{
	case 'A':
		return 1;
	case 'B':
		return 2;
	case 'C':
		return 3;
	case 'D':
		return 4;
	case 'E':
		return 5;
	case 'F':
		return 6;
	case 'G':
		return 7;
	case 'H':
		return 8;
	}
	return 0;
}



void printgame()
{
	int i = 0;
	char *ply_ptr;
	ply_ptr = &playground[0][0];
	printf("\n   1 2 3 4 5 6 7 8");
	for (; i<64; i++)
	{

		char row = 'A';
		char amblem = '_';
		if (i % 8 == 0) {
			printf("\n%c ", row + i / 8);
		}
		amblem = *(ply_ptr + i);
		if (empty(amblem))
		{
			int willBeReverse = MoveablePoint(i / 8, i % 8);

			if (willBeReverse>9)
			{

				amblem = '+';
			}
			else if (0 < willBeReverse && willBeReverse<9)
			{

				amblem = 48 + willBeReverse;

			}
		}

		
			
		printf(":%c", amblem);
		
		if (i % 8 == 7) printf(":");

	}

}
void printscors()
{
	printf("\n");
	int i = 0;
	char *ply_ptr; ply_ptr = &playground[0][0];
	x_point = 0;
	o_point = 0;
	for (; i < 64; i++)
	{
		if ((*(ply_ptr + i)) == 'x')
		{
			x_point++;
		}
		if ((*(ply_ptr + i)) == 'o')
		{
			o_point++;
		}

	}
	printf("x: %d puan, o: %d puan", x_point, o_point);
}

int MoveablePoint(int row, int col)
{
	int i = 0;
	for (; i < 24; i++)
	{
		if (avaible_moves[i][0] == row && avaible_moves[i][1] == col)
		{
			return avaible_moves[i][2];
		}
	}
	return 0;
}

void FillForNewGame(char ply[][8])
{
	int i = 0, row = 0;
	char *ply_ptr; ply_ptr = &ply[0][0];
	for (i = 0; i<64; i++)
	{

		int val = '_';

		//*(ply_ptr + i) = i + 1; 
		//m.twoplayergames.org/play/reversi.html
		//
		if (i == 27 || i == 36)
		{
			val = 'x';
		}
		else if (i == 28 || i == 35)
		{
			val = 'o';
		}
		*(ply_ptr + i) = val;
	}

}
char getFromPlayground(int row, int col)
{
	char *ptr_pygr; ptr_pygr = &playground[0][0];
	return *(ptr_pygr + 8 * row + col);
}
void setInPlayground(char c, int row, int col)
{

	char *ptr_pygr; ptr_pygr = &playground[0][0];
	*(ptr_pygr + 8 * row + col) = c;
}
int empty(char c)
{
	if (c == x_ || c == o_)

		return 0;

	else
		return 1;
}

int BorderCrossing(int row, int col)
{
	
	if ((row == 7 || col == 0) || (row == 7 || col == 0)) return 1;
	return 0;

}
int BorderCrossingCorner(int row, int col)
{
	if ((row == 7 || col == 0) && (row == 7 || col == 0)) return 1;
	return 0;
}




void Reverse(char playground[][8], char side, int row, int col,int  CheckThePoint)
{
	

	int i = 0;
	

	for (i; i < 8; i++)
	{
		int deltarow = MoveRotations[i][0];
		int deltacol = MoveRotations[i][1];
		if(CheckThePoint == 0 || test_move(playground, side, row, col, deltarow, deltacol, 0))
			reverse_move(playground, side, row, col, deltarow, deltacol);

	}
	
}

int test_move(char ply[][8], char side, int row, int col, int deltarow, int deltacol, int deeptest)
{

	char c = getFromPlayground(row, col);
	int testrow = row + deltarow, 
		testcol = col + deltacol, 
		avaibleRock = 0;

	
	while (0 <= testcol < 8 && 0 <= testrow < 8 && empty(c))
	{
		char current = getFromPlayground(testrow,testcol);
		int invalidrun = 
			(empty(current)) 
			|| 
			(BorderCrossing(testrow,testcol) && current != side);
			
		if (invalidrun)
		{
			avaibleRock == 0;
			return 0;
		}
		else if (current == side)
		{
			break;
		}
		avaibleRock += 1;
		if (deeptest) avaibleRock += TestPoint(side, testrow, testcol,1);
		
		testcol += deltacol;
		testrow += deltarow;
	}


	return avaibleRock;
	
}
int reverse_move(char ply[][8], char side, int row, int col, int deltarow, int deltacol)
{
	int testrow = row+deltarow, testcol = col + deltacol, avaibleRock = 0;
	setInPlayground(side, row, col);

	while (0 <= testcol < 8 && 0 <= testrow < 8)
	{
		char current = getFromPlayground(testrow, testcol);
		

		if (empty(current))
		{
			break;
		}
		setInPlayground(side, testrow, testcol);
		Reverse(playground, side, testrow, testcol, 1);



		testcol += deltacol;
		testrow += deltarow;
	}
	return avaibleRock;

}
int TestPoint(char side, int row, int col, int deepTest)
{
	int a = 0, i = 0;
	for (i; i < 8; i++)
	{
		int deltarow = MoveRotations[i][0];
		int deltacol = MoveRotations[i][1];

		a += test_move(playground, side, row, col, deltarow, deltacol, deepTest);
		if (a > 0) return a;
	}
	return a;
}

int findValidMoves(char ply[][8], char side)
{
	int i = 0;
	//for (i < )
	//printf("\n%c",side);
	int row = 0, col = 0, avaible = 0;
	int a = 0;
	for (row = 0; row < 8; row++)
	{
		for (col = 0; col < 8; col++)
		{
			/*if (ply[row][col] == 'x')
			{
			printf("x bulundu");
			}*/
			if (empty(getFromPlayground(row, col)))
			{
				avaible = TestPoint(side, row, col, 1);
			
			//avaible = testAll(side, row, col);

				if (avaible > 0)
				{
				//printf("avaible > 0");
					avaible_moves[i][0] = row;
					avaible_moves[i][1] = col;
					avaible_moves[i][2] = avaible;
					i++;
					a = 1;
				}
			}
		}
	}
	for (; i < 24; i++)
	{
		avaible_moves[i][0] = -1;
		avaible_moves[i][1] = -1;
	}
	return a;
}


int PlayerMove(char PlayerSide)
{


	int col, row;
	char *pointerOf_ply; pointerOf_ply = &playground[0][0];
	char rowc;
	int rescan = 1, no_request = 0;
	while (no_request == 0)
	{
		rescan = 1;
		printf("\nHAMLE SIRASI: %c", PlayerSide);
		printf("\nTaþýnýzý yerleþtirmek istediðiniz yere koyun\n('satýr harfi''sütun numarasý' þeklinde girin\n");


		while (rescan)
		{
			scanf("%c%d", &rowc, &col);
			
			if (rowc != '\n') rescan = 0;

		}
		row = getRowInt(rowc) - 1;
		col--;
		no_request = (MoveablePoint(row, col));
		if (no_request == 0) printf("\nBuraya hamle yapmanýz mümkün deðil. Lütfen geçerli bir noktaya hamle yapýnýz");
		/*printf("\nsatýr: %d, kolon: %d\n", row_i, col - 1);*/

		//playground[col - 1][row_i] = PlayerSide;
		

	}
	//*(pointerOf_ply + row_i * 8 + col) = PlayerSide;
	Reverse(playground, PlayerSide, row, col, 1);
	//testAll(playground, PlayerSide, row_i, col, 1);
	return 0;
}
void ComputerMove(char PlayerSide)
{
	printf("\nBilgisayar hamlesi yapýlýyor... Bilgisayar tarafý: %c", PlayerSide);
	int len = 0, i = 0, row = -1, col = -1;
	for (; i < 24; i++)
	{
		int trow = avaible_moves[i][0];
		int tcol = avaible_moves[i][1];
		if (trow == -1 || tcol == -1) break;
		int c = TestPoint(PlayerSide, trow, tcol, 1);
		if (c > len)
		{
			len = c;
			row = trow;
			col = tcol;
		}
	}
	Reverse(playground, PlayerSide, row, col, 1);
}
int main()
{
	setlocale(LC_ALL, "");
	printf("XO Reversi Oyunu...\n");
	char PlayMode = ' ', currentplayer = x_;

	int exit_ = 0, gameOver = 0;

	while (!exit_)
	{
		while (PlayMode != 'c' && PlayMode != 'm' && PlayMode != 'x')
		{
			printf("Bilgisayara karþý oynamak için 'c',\n Ýki kiþiyle oynamak için 'm' yazýnýz\nYardým için ise 'h' yazabilirsiniz.");
			PlayMode = tolower(getchar());
			if (PlayMode == 'h')
			{
	
				///ShowHelp() will added
			}
		}
		FillForNewGame(playground);
		int x_hak = 0, o_hak = 0;
		while (!gameOver)
		{
			if(currentplayer == player1)
				x_hak = findValidMoves(playground, currentplayer);
			else if (currentplayer == player2)
				o_hak = findValidMoves(playground, currentplayer);

			printgame();
			printscors();
			
			if (currentplayer == player1 ) {
				if (x_hak) {
					if (PlayMode == 'x')
					{
						ComputerMove(currentplayer);
					}
					else
						PlayerMove(currentplayer);
				}
				else 
				{ 
				printf("%d: Hamle yapamazsýnýz... Ýkinci oyuncuya geçiliyor", currentplayer);
				}
			}
			else if (currentplayer == player2)
			{
				if (o_hak)
				{
					if (PlayMode == 'm')
					{
						PlayerMove(currentplayer);
					}
					else if (PlayMode == 'c')
					{
						ComputerMove(currentplayer);
					}
				}
				else
				{
					printf("%d: Hamle yapamazsýnýz... Birinci oyuncuya geçiliyor", currentplayer);
				}

			}
			
			currentplayer = reversedChar(currentplayer);

			gameOver = (x_hak == 0 && o_hak == 0);
		}
		printf("\n OYUN BÝTTÝ \n");
		printscors();
		if (x_point > o_point)
		{
			printf("\nKazanan: x");
		}
		else if(x_point < o_point)
		{
			printf("\nKazanan: o");
		}
		else if (x_point == o_point)
		{
			printf("\nKazanan: Berabere");
		}
		printf("\nÇýkmak için esc'ye, tekrar oynamak için enter'a basýn");
		char x = getch();
		if (x == '\e')
		{
			exit_ = 1;
		}
		else if (x == '\n')
		{
			gameOver = 0;
			FillForNewGame(playground);
		}
	}

	printf("\n");
	system("pause");
	return 0;
}

