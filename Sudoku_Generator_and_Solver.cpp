#include <bits/stdc++.h>
using namespace std;
const int N=9;
int mat[N][N];
//k is number of empty spaces 
const int K=40;
 int RANDOM(int num)
    { //return random numbers from 1 to num
        return (rand() %num+ 1);
    }
     // check in the row for existence
     bool unUsedInRow(int i, int num)
    {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] == num) {
                return false;
            }
        }
        return true;
    }
    // check in the colum for existence
    bool unUsedInCol(int j, int num)
    {
        for (int i = 0; i < N; i++) {
            if (mat[i][j] == num) {
                return false;
            }
        }
        return true;
    }
   
    
   
    // Returns false if given 3 x 3 block contains num.
    bool unUsedInBox(int rowStart, int colStart, int num)
    {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (mat[rowStart + i][colStart + j]
                    == num) {
                    return false;
                }
            }
        }
        return true;
    }
    // Fill a 3 x 3 matrix.
    void fillBox(int row, int col)
    {
        int num;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                /*do {
                    num = RANDOM(N);
                } while (!unUsedInBox(row, col, num));
                mat[row + i][col + j] = num;*/
                   num=RANDOM(N);
    /*
    unless the num is present ..generate random numbers ..till a 
    unique value is found
    */
                while(unUsedInBox(row, col, num)==false)
                {  
                   
                    num=RANDOM(N);


                }
                  
                  mat[row+i][col+j]=num;



            }
        }
    }

    // fill the diagonal (3*3)matrix ..which are independent on each other
     void fillDiagonal()
    {
        for (int i = 0; i < N; i = i + 3)
        {
           
           
            fillBox(i, i);
        }
    }
   
   
    // Check if safe to put in cell
    bool CheckIfSafe(int i, int j, int num)
    {
        return (
            unUsedInRow(i, num) && unUsedInCol(j, num)
            && unUsedInBox(i - i % 3, j - j % 3, num));
    }

   
    // A recursive function to fill remaining
    // matrix
    bool fillRemaining(int i, int j)
    {
         // check the end of traversing a row .. so go to next row and start from zero column
        if (j>=9 && i<=7) {
            i = i + 1;
            j = 0;
        }
        // check whether the cell is in the first quadrant(1,1) or not out of 9 (3*3) box
        if (i < 3 && j<3) {
           j=3;
        }
        //check for  (2*2) for 9 by 9 matrix
        else if (i >2 && i<=5 && j>=3 &&j<=5) {
          j+=3;
        }
        else {
            // check for (3*3)   for 9 by 9 matrix
            if (i>5 && i<=8&&j>=6 && j<=8) {
                i++;
                j=0;
                if (i >= 9) {
                    return true;
                }
            }
        }

        // sudoku solve logic .. 
        /*
        if the number is valid ..fill the cell with it ///
        then run a recursive loop // if at any point there is no valid number for a particular cell we bacttrack 

        */
        for (int num = 1; num <= N; num++) {
            if (CheckIfSafe(i, j, num)) {
                mat[i][j] = num;
       

                if (fillRemaining(i, j + 1)) {
                    return true;
                }
                mat[i][j] = 0;
            }
        }
        return false;
    }
    // Remove the K no. of digits to
    // complete game
    void removeKDigits()
    {
        int count = K;
        while (count != 0) {
            // generate number from 0 to 80
            int cellId = RANDOM(N * N) - 1;
         
            // extract coordinates i and j
            int i = (cellId / N);
            int j = cellId % 9;
            
            // if mat[i][j] is non empty
            if (mat[i][j] != 0) {
                count--;
                mat[i][j] = 0;
            }
        }
    }
     void fillValues()
    {
       
        // Fill the diagonal of 3 x 3 matrices
        fillDiagonal();
       
        // Fill remaining blocks
        fillRemaining(0, 3);
       
        // Remove Randomly K digits to make game
        removeKDigits();
    }
    bool isvalid(int grid[N][N],int r,int c,int val)
    {
        for(int i=0;i<9;i++)
         {
             if(grid[r][i]==val)
             return false;
             if(grid[i][c]==val)
              return false;
              if(grid[3*(r/3)+i%3][3*(c/3)+i/3]==val)
                return false;
         }
         return true;
         
    }
    bool SolveSudoku(int grid[N][N])  
    { 
        // Your code here
        
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
              {
                  if(grid[i][j]==0)
                  {
                      for(int op=1;op<=9;op++)
                       {
                           if(isvalid(grid,i,j,op))
                           {
                               grid[i][j]=op;
                                 if(SolveSudoku(grid))
                                  return true;
                                 else grid[i][j]=0;
                           }
                              
                       }
                       return false;
                  }
              }
        }
        return true;
    }
    
int main() {
    srand(time(0));
    fillValues();
    cout<<"THE SUDOKU PUZZLE TO BE SOLVED -->\n";
     for(int i=0;i<N;i++)
     {
         for(int j=0;j<N;j++)
           cout<<mat[i][j]<<" ";
           cout<<endl;
     }
SolveSudoku(mat);
   cout<<endl;
   cout<<endl;
   cout<<"THE SOLVED SUDOKU -->\n";
    for(int i=0;i<N;i++)
     {
         for(int j=0;j<N;j++)
           cout<<mat[i][j]<<" ";
           cout<<endl;
     }
   
}
