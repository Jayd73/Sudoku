//this algorithm may take several minutes (or hours) to solve some of the //sudoku puzzle

#include<iostream.h>
#include<conio.h>


//declaring functions to be used
int check (int[9][3][3]);
int count(int[100],int,int);
void printSudoku(int[9][3][3]);
int* getNumsIn(int[9][3][3],int,int);
int solveSudoku (int[9][3][3]);


int main()
{
   clrscr();
//sample sudoku matrix
//unsolved. More unsolved in the unsolvedSudoku.txt file
 int t1[9][3][3]={{{1,0,0},{7,3,0},{4,6,0}},{{4,8,9},{0,5,0},{0,0,1}},
		 {{0,0,6},{0,4,0},{2,9,5}},
		 {{3,8,7},{5,0,1},{0,4,6}},{{1,2,0},{7,0,3},{0,9,5}},
		 {{6,0,0},{0,0,8},{7,1,0}},
		 {{9,1,4},{0,2,0},{8,0,3}},{{6,0,0},{0,4,0},{5,1,2}},
		 {{0,8,0},{0,3,7},{0,0,4}}};


 //cout<<"Before:\n";
 //printSudoku(t);
cout<<"After Solving:\n";
solveSudoku(t1);

 getch();
 return 0;
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

//this function returns possible numbers for an empty cell satisfying the 3 conditions.
int* getNumsIn (int sudoku[9][3][3], int rowInd, int colmInd)
{
  int* posb= new int[9];
  int block[9],rows[9],cols[9];
  for (int i=0; i<9; i++)
  {
    int ind=0;
     for (int j=0; j<3; j++)
     {
       for (int k=0; k<3; k++)
       {
	 if (i<=colmInd/3 + rowInd - rowInd%3)
		block[ind]=sudoku[i][j][k];
	 if (i<=rowInd)
		rows[ind]=sudoku[j+(i/3)*3][i-(i/3)*3][k];
	 if (i<=colmInd)
		cols[ind]=sudoku[j*3+(i/3)][k][i-(i/3)*3];
	 ind++;
       }
     }
    }

    int index=0;
    for (int m=1; m<=9; m++)
    {
      if (count(block, m, 9)==0 && count(rows,m,9)==0 && count(cols,m,9)==0)
      {
	posb[index+1]=m;
	index++;
      }
    }
    posb[0]=index; //storing len of posb at index 0, hence elem. starts from index 1
	
       return posb;
}

//solving function which will be called recursively
int solveSudoku (int sudoku[9][3][3])
{
  int returnVal=0, repeat=1; 
  int incP=1; 				// for moving to the next possibility.
  for (int i=0; i<9; i++)
  {
    int numInCell,ind=0;

     for (int j=0; j<3; j++)
     {
       for (int k=0; k<3; k++)
       {
	 numInCell=sudoku[j+(i/3)*3][i-3*(i/3)][k];	//getting one number at a time from a cell. 
	 repeat=1;
	 while(repeat==1)				
	 {   repeat=0;					//hence the code inside this loop will be repeated once.
	 if(numInCell==0)				//checking if the cell is empty .i.e if the number in it is 0.
	   {
	    int* posb = getNumsIn(sudoku,i,ind);	// getting all possibilities for the empty cell in the form of an array.
	    if(posb[0]==0)				//checking whether there are 0 possibilities by checking the length of the array.
		{return 0;}
	    else
	    {
	      sudoku[j+(i/3)*3][i-3*(i/3)][k]=posb[incP];   // if there are possibilities, fill the empty cell with the next possibility.
		    					    //based on the incP counter which starts from 1.
		    
	      returnVal=solveSudoku(sudoku);		    //call the function with the modified sudoku matrix and store the return value.
	    }


       if(returnVal !=1)	  	//if value returned by the function called by this function is not 1, then proceed.
       {
	   if(incP<posb[0])		//if there are possibilities remaining which are not entered in the empty cell.
	      {
		 incP++;
		 sudoku[j+(i/3)*3][i-3*(i/3)][k]=0;	//empty the again from it's previous entered possibility.
		 numInCell=0;
		 repeat=1;				//repeat the while loop again for the new possibility.
	      }
	 else
	    {
		       sudoku[j+(i/3)*3][i-3*(i/3)][k]=0;	//if all possibilities are over empty the cell again and return 0.
		       return 0;
		    }
	}	//the numInCell if condition
       }  	//the if condition checking for empty sq.
      }   	//while looop
      ind++;				//incrementing the coloumn counter.
     } 		 //k for loop
   }   		//j for loop
  }		//i for loop
	
  if(returnVal!=1)		//This condition will be checked after all cells are traversed.	
  {
   if (check(sudoku)==0)	//After traversing, checking if the sudoku is solved correctly.
   {
	printSudoku(sudoku);	//if the ans is correct, then print the solved sudoku and return 1. 
	   
	return 1;		//Returning 1 specifies that puzzle is successfully solved.
   }
  }

  if (returnVal==1)		//if the returned value is 1, puzzle is solved and the current function should return 1 while going back
	  			//to the first function that started the recursion
	return 1;

  return 0;			//if sudoku is not solved .i.e returnVal=0, then this function will return 0 too.
}

//Func. to check sudoku
int check (int sudoku[9][3][3])
{
  for (int i=0; i<9; i++)
  {
    //defining arrays to check for blocks(3x3), rows(1x9),columns(9x1)
    int block[9],rows[9],cols[9],ind=0;

     for (int j=0; j<3; j++)
     {
       for (int k=0; k<3; k++)
       {
	 block[ind]=sudoku[i][j][k];    	//storing numbers in one block.
	 rows[ind]=sudoku[j+3*(i/3)][i-3*(i/3)][k];   //storing numbs in one row.
	 cols[ind]=sudoku[j*3+(i/3)][k][i-3*(i/3)];	//storing numbs in one colomn.
	 ind++;
       }
     }

     for (int m=0; m<9; m++)
     {
	int cntInBlock=count(block,block[m],9);
	int cntInRow=count(rows,rows[m],9);
	int cntInColm=count(cols,cols[m],9);

	 //checking if a number occurs more than than once
	 //in a block, row and a column.

	if (cntInBlock>1 || cntInRow >1 || cntInColm>1)
	{
		//cout<<"err in block "<<i+1<<" : "<< endl;
		//printArr(block,'b');
		return -1;
	}

     }
  }
  //if sudoku is correct then it will return 0, else -1.
  return 0;

}


void printSudoku( int sudoku[9][3][3])
{
  int s[9][9];

for(int i=0; i<9; i++)
{
 int ind=0;
  for (int j=0; j<3; j++)
     {
       for (int k=0; k<3; k++)
       {
	 s[i][ind]=sudoku[j+3*(i/3)][i-3*(i/3)][k];  //storing rows for printing.
	 ind++;
       }
     }
  }

  for (int x=0; x<9; x++)
  {
	for (int y=0; y<9; y++)
	  ((y+1)%3==0)?cout<<s[x][y]<<" | ":cout<<s[x][y]<<" ";
	((x+1)%3==0)?cout<<endl<<"------ ------- -------"<<endl:cout<<endl;
  }
}
