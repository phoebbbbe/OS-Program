#include "func.h"

int results[11]; // results[0] 為rows, results[1] 為columns, results[2~11]為3*3的區域，共有9個

void *checkRows(void*);
void *checkCols(void*);
void *checkSubgrid(void*);

int main()
{
    int i, j, ch;

    printf("Input 0 is default sudoku or 1 to enter your own sudoku:");
    scanf("%d", &ch);
    if (ch == 1)
    {

        for (i = 0; i < 9; i++)
	{
            for (j = 0; j < 9; j++)
                scanf("%d", &grid[i][j]);
        }
    }

    printf("\nThe sudoku is:\n");
    show();//顯示輸入或default sudoku
    printf("\n");

    pthread_t rowT;
    pthread_t colT;
    pthread_t gridT[9];

    // 檢查row
    pthread_create(&rowT, NULL, checkRows, &rowT);
    pthread_join(rowT, NULL);

    // 檢查column
    pthread_create(&colT, NULL, checkCols, &colT);
    pthread_join(colT, NULL);

    //把9個3*3區域的數字存入sub1~sub9中
    setsubs();
    
    // 檢查3*3區域
    for (i = 0; i < 9; i++)
    {
        pthread_create(&gridT[i], NULL, checkSubgrid, &i);
        pthread_join(gridT[i], NULL);
    }

    // 檢查解是否是valid的解
    printf("\n");
    if (in_array(results, 0, 11))
            printf("The solution is invalid\n");
    else
        printf("The solution is valid\n");
    return 0;
}

void* checkRows(void *arg)
{
    /*檢查每個row是否都含有數字1~9*/

    int i,j;
    int lval, uval;

    lval = 0; uval = 8; // row的第一和最後一個

    for (i = 0; i < 9; i++) // i = row , j = 檢查的數字
    {
        for (j = 1; j <= 9; j++) 
        {
	    //檢查第i個row，是否有數字j，沒有的話results[0]=0
            if (!in_row (lval, uval, j, i)) 
            {
                printf("Row check failed！ %d does not exist in row %d\n", j, i+1);
                results[0] = 0;
                pthread_exit(NULL);
            }
        }
    }

    printf("Rows are ok\n");
    results[0] = 1;
    pthread_exit(NULL);

}

void *checkCols (void *arg)
{
    /*檢查每個column是否都含有數字1~9*/

    int i,j;
    int lval, uval;

    lval = 0; uval = 8; // column的第一和最後一個

    for (i = 0; i < 9; i++) // i = column , j = 檢查的數字
    {
        for (j = 1; j <= 9; j++)
        {
	    /*檢查第i個column，是否有數字j，沒有的話results[1]=0*/
            if (!in_col (lval, uval, j, i))
            {
                printf("Column check failed since %d does not exist in column %d\n", j, i+1);
                results[1] = 0;
                pthread_exit(NULL);
            }
        }
    }

    printf("Columns are ok\n");
    results[1] = 1;
    pthread_exit(NULL);
}

void *checkSubgrid (void *arg)
{
    int i, j;
    int gridNumber = *((int *)arg);
    int subgrid[9];
    /*透過gridNumber取得0~8(3*3區域)*/
    switch (gridNumber) 
    {
        case 0: 
            for (i = 0; i < 9; i++) subgrid[i] = sub1[i]; 
            break;
        case 1: 
            for (i = 0; i < 9; i++) subgrid[i] = sub2[i];
            break;
        case 2: 
            for (i = 0; i < 9; i++) subgrid[i] = sub3[i];
            break;
        case 3: 
            for (i = 0; i < 9; i++) subgrid[i] = sub4[i];
            break;
        case 4: 
            for (i = 0; i < 9; i++) subgrid[i] = sub5[i];
            break;
        case 5: 
            for (i = 0; i < 9; i++) subgrid[i] = sub6[i];
            break;
        case 6: 
            for (i = 0; i < 9; i++) subgrid[i] = sub7[i];
            break;
        case 7: 
            for (i = 0; i < 9; i++) subgrid[i] = sub8[i];
            break;
        case 8: 
            for (i = 0; i < 9; i++) subgrid[i] = sub9[i];
            break;
        default: 
            printf("Error\n");
            pthread_exit(NULL);
    }
    //檢查subgrid(3*3)是否都有1~9
    for (i = 1; i <=9; i++)
    {
        if (! in_array(subgrid, i, 9))
        {
            printf("subgrid %d because %d is not in it\n", gridNumber+1, i);
            results[gridNumber + 2] = 0;
            pthread_exit(NULL);
        }
    }
    printf("subgrid %d ok\n", gridNumber+1);
    results[gridNumber + 2] = 1;
    pthread_exit(NULL);
}

