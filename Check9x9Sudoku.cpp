#include<iostream.h>
#include<conio.h>

//declaring functions to be used
int check (int[9][3][3]);
int count(int[100],int,int);
void printArr(int[9], char);
void printSudoku(int s[9][9]);

void main()
{
   clrscr();
	
//sample sudoku matrix
 int s[9][3][3]={{{7,3,5},{8,4,2},{9,6,1}},{{6,1,4},{9,7,3},{2,8,5}},
		 {{8,9,2},{5,6,1},{3,7,4}},
		 {{2,8,6},{4,1,3},{5,7,9}},{{3,4,9},{8,5,7},{1,2,6}},
		 {{1,5,7},{9,2,6},{4,3,8}},
		 {{1,5,7},{6,9,4},{3,2,8}},{{4,9,2},{7,3,8},{5,6,1}},
		 {{6,8,3},{2,1,5},{7,4,9}}};

 //calling the function for checking sudoku
 (check(s)==0)?cout<<"\nSudoku is correctly solved.":cout<<"\nIncorrect number.";
 getch();
}

//this func. counts number of occurences of an element in an array.
int count(int arr[100], int val, int len)
  {
    int c=0;
    for (int i=0; i<len; i++)
    {
	if(arr[i]==val)
		c++;
    }
    return c;
  }

//Func. to check sudoku
int check(int sudoku[9][3][3])
{
 int s[9][9];
 int inc=0,mul=0;//variables to get the required index.
  for (int i=0; i<9; i++)
  {
    //defining arrays to check for blocks(3x3), rows(1x9),columns(9x1)
    int block[9],rows[9],cols[9],ind=0;

    /*Also to take input from the user( block-wise,column-wise or
    row wise), same nested for loop can be used. We just have to remove
    remaining 2 arrays from innermost and that 'checking'for loop.*/

     for (int j=0; j<3; j++)
     {
       for (int k=0; k<3; k++)
       {
	 block[ind]=sudoku[i][j][k];    	//storing numbers in one block.
	 rows[ind]=sudoku[j+inc][i-3*mul][k];   //storing numbs in one row.
	 cols[ind]=sudoku[j*3+mul][k][i-3*mul];	//storing numbs in one colomn.
	 s[i][ind]=sudoku[j+inc][i-3*mul][k];;
	 ind++;
       }
     }
      /*jumbing condition for indices.required for rows and columns.
      a mathematical function can also be used instead of using these
      two variables and this condition.*/

     if((i+1)%3==0)
     {
	inc+=3;
	mul+=1;
     }

     for (int m=0; m<9; m++)
     {
	int cntInBlock=count(block,block[m],9);
	int cntInRow=count(rows,rows[m],9);
	int cntInColm=count(cols,cols[m],9);

	 //checking if a number occurs more than than once
	 //in a block, row and a column.

	if (cntInBlock>1)
	{
		cout<<"err in block:"<< endl;
		printArr(block,'b');
		return -1;
	}
	if(cntInRow>1)
	{
		cout<<"err in rows"<<endl;
		printArr(rows,'r');
		return -1;
	}
	if(cntInColm>1)
	{
		cout<<"err in column"<<endl;
		printArr(cols,'c');
		return -1;
	}

     }
  }

  //if sudoku is correct then it will return 0, else -1.
  printSudoku(s);
  return 0;

}

void printArr(int arr[9],char flag='N')
{
      switch(flag)     //flag to check if passed array is block,row or column
			//and print array accordingly.
      {
	case 'b':
	for (int i=0;i<9;i++)
	{
	    if ((i+1)%3==0)
		cout<<arr[i]<<" "<<endl;
	    else
		cout<<arr[i]<<" ";
	}
	break;

	case 'r':

	for (int j=0;j<9;j++)
	{
		cout<<arr[j]<<" ";
	}
	break;

	case 'c':
	for (int k=0;k<9;k++)
	{
		cout<<arr[k]<<" "<<endl;
	}
	break;
      }
}

void printSudoku( int s[9][9])
{
  for (int i=0; i<9; i++)
  {
	for (int j=0; j<9; j++)
	  ((j+1)%3==0)?cout<<s[i][j]<<" | ":cout<<s[i][j]<<" ";
	((i+1)%3==0)?cout<<endl<<"------ ------- -------"<<endl:cout<<endl;
  }
}
