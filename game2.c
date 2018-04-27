#include<locale.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>

//SOURCE @ https://github.com/huseyincangunduz/XOReversiProject

static char playground[8][8];
int avaible_moves[24][2];
char x_ = 'x', o_ = 'o', player1 = 'x', player2 = 'o';
int x_point = 0, o_point = 0;
int testAll(char [][8], char , int , int , int );

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
			return 1;
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
void setInPlayground(char c,int row, int col)
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

int vertical_down_test(char ply[][8], char side, int row, int col,int change)
{
	char *ptr_ply 
		,target = getFromPlayground(row,col);
	ptr_ply = &ply[0][0];

	int avaible = 0;
	char under = getFromPlayground(row + 1, col);

	if (under == reversedChar(side))
	{
		int testrow = row  + 1;
	
		while (change && testrow < 8)
		{
			char cx = (getFromPlayground(testrow, col));
			if (empty(cx) || (testrow == 7 && cx != side))
				return 0;
			if (cx == side) break;
			testrow++;
		}
		
		while (testrow < 8)
		{
			
			char test = getFromPlayground(testrow, col);
			if (test == reversedChar(side))
			{

				avaible += 1;
				avaible += testAll(ply, side, testrow, col, change);
			}
			else if (empty(test))
			{
				avaible = 0;
				//setInPlayground('_', row, col);
				break;
			}
			else if (test == side)
			{
				
				break;
			}
			
			testrow++;
		}
	}

	return avaible;
}
int vertical_up_test(char ply[][8], char side, int row, int col, int change)
{


	char *ptr_ply
		, target = getFromPlayground(row, col);
	ptr_ply = &ply[0][0];

	int avaible = 0;
	char up = getFromPlayground(row - 1, col);

	/*if (row == 5 && col == 3 && side == o_)
	{
		printf("XO Reversi Oyunu...\n");
	}*/
	if (side == x_ && up == o_)
		printf("\a");
	if (up == reversedChar(side))
	{
		
		int testrow = row - 1;

	
		while (change && testrow >= 0)
		{
			char m = getFromPlayground(testrow, col);
			if (empty(m) || (testrow == 0 && m != side))
				return 0;
			else if (m == side) 
				break;
			testrow--;
		}
		

		 testrow = row - 1;

		while (testrow >= 0)
		{
			char test = getFromPlayground(testrow, col);
			if (test == reversedChar(side))
			{
				avaible += 1;
				/*if (change == 0 || testAll(ply, side, testrow, col, 0)>0)*/
				if(change == 1) avaible += testAll(ply, side, testrow, col, change);
			}
			else if (empty(test))
			{
				avaible = 0;
				
				
				break;
			}
			else if (test == side)
			{
				
				
				break;
			}

			testrow--;
		}
	}
	/*printf("%d x %d\n", row, col);
	}*/
	//printf("s");
	//printf(ply);
	return avaible;
}

int horizontal_right_test(char ply[][8], char side, int row, int col, int change)
{


	char *ptr_ply
		, target = getFromPlayground(row, col);
	ptr_ply = &ply[0][0];

	int avaible = 0;
	char RightSide = getFromPlayground(row, col + 1);
	/*/if (side == o_ && under == x_)
		printf("\a");*/
	if (RightSide == reversedChar(side))
	{
		int testcol = col + 1;
		
		
		while (change && testcol < 8)
		{
			char k = getFromPlayground(row, testcol);
			if (empty(k) && (testcol == 8 & k != side)) return 0;
			if (getFromPlayground(row, testcol) == side) break;
			testcol++;
		}
		testcol = col + 1;
		while (testcol < 8)
		{
			char test = getFromPlayground(row,testcol);
			if (test == reversedChar(side))
			{
				avaible += 1;
				if (change == 1) avaible += testAll(ply, side, row, testcol, change);
			}
			else if (empty(test))
			{
				avaible = 0;
				//setInPlayground('_', row, col);
				
				break;
			}
			else if (test == side)
			{
				//setInPlayground('-', row, col);
				break;
			}

			testcol++;
		}
	}

	return avaible;
}
int horizontal_left_test(char ply[][8], char side, int row, int col, int change)
{


	char *ptr_ply
		, target = getFromPlayground(row, col);
	ptr_ply = &ply[0][0];

	int avaible = 0;
	char LeftSide = getFromPlayground(row , col - 1);

	if (LeftSide == reversedChar(side))
	{
		int testcol = col - 1;

		while (change && testcol >= 0)
		{
			char tst = getFromPlayground(row, testcol);
			if (empty(tst) || (tst != side && testcol == 0)) return 0;
			if (reversedChar(getFromPlayground(row, testcol))) break;
			testcol--;
		}
		testcol = col - 1;
		while (testcol >= 0)
		{
			char test = getFromPlayground(row, testcol);
			if (test == reversedChar(side))
			{
				avaible += 1;
				avaible += testAll(ply, side, row, testcol, change);
			}
			else if (empty(test))
			{
				avaible = 0;
				/*setInPlayground('_', row, col);
				setInPlayground('_', row, testcol);*/
				break;
			}
			else if (test == side)
			{
				//setInPlayground('-', row, col);
				break;
			}

			testcol--;
		}
	}

	return avaible;
}

int testAll(char ply[][8], char side, int row, int col,int change)
{
	if (change == 1)
	{
		setInPlayground(side, row, col);

	//	printgame();
	}


//	if (row == 5 && col == 3)
//	{
//		printf("\a");
//	}
	int A =  
		(vertical_up_test(ply, side, row, col, change)
		+ vertical_down_test(ply, side, row, col, change)
		+ horizontal_left_test(ply, side, row, col, change)
		+ horizontal_right_test(ply, side, row, col, change));

	return A;
}
int findValidMoves(char ply[][8], char side)
{
	int i = 0;
	//for (i < )
	//printf("\n%c",side);
	int row = 0, col = 0, avaible = 0;
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
				avaible = testAll(ply, side, row, col, 0);
			}
			avaible = testAll(ply, side, row, col,0);
			
			if (avaible > 0)
			{
				//printf("avaible > 0");
				avaible_moves[i][0] = row;
				avaible_moves[i][1] = col;
				i++;
			}
		}
	}
	for (; i < 24; i++)
	{
		avaible_moves[i][0] = -1;
		avaible_moves[i][1] = -1;
	}
	return 1;
}
int PlayerMove(char PlayerSide)
{


	int col, row_i;
	char *pointerOf_ply; pointerOf_ply = &playground[0][0];
	char row;
	int rescan = 1, no_request = 0;
	while (no_request == 0)
	{
	rescan = 1;
	printf("\nHAMLE SIRASI: %c", PlayerSide);
	printf("\nTaþýnýzý yerleþtirmek istediðiniz yere koyun\n('satýr harfi''sütun numarasý' þeklinde girin\n");

	
	while (rescan)
	{
		scanf("%c%d", &row, &col);
		row_i = getRowInt(row) - 1;
		if (row != '\n') rescan = 0;
		
	}
	col--;
	no_request = (MoveablePoint(row_i, col));
	if (no_request == 0) printf("\nBuraya hamle yapmanýz mümkün deðil. Lütfen geçerli bir noktaya hamle yapýnýz");
	/*printf("\nsatýr: %d, kolon: %d\n", row_i, col - 1);*/

	//playground[col - 1][row_i] = PlayerSide;
	

	}
	//*(pointerOf_ply + row_i * 8 + col) = PlayerSide;
	testAll(playground, PlayerSide, row_i, col, 1);
	return 0;
}
int main()
{
	setlocale(LC_ALL, "");
	printf("XO Reversi Oyunu...\n");
	char PlayMode = ' ', currentplayer = x_;

	int exit_ = 0, gameOver = 0;

	while (!exit_)
	{
		while (PlayMode != 'c' && PlayMode != 'm')
		{
			printf("Bilgisayara karþý oynamak için 'c',\n Ýki kiþiyle oynamak için 'm' yazýnýz\nYardým için ise 'h' yazabilirsiniz.");
			PlayMode = tolower(getchar());
			if (PlayMode == 'h')
			{

				///ShowHelp() will added
			}
		}
		FillForNewGame(playground);
		while (!gameOver)
		{

			findValidMoves(playground, currentplayer);
			printgame();
			printscors();
			PlayerMove(currentplayer);
			/*if (currentplayer == player1)
				PlayerMove(player1);
			else if (currentplayer == player2)
			{
				PlayerMove(player2);
			}*/
			currentplayer = reversedChar(currentplayer);
			
		}
	}

	printf("\n");
	system("pause");
	return 0;
}
