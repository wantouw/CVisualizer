#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

void cls()
{
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

const int size = 100, vals = 25;
const int width = 51, height = 21;
int frontierAmount = 0;
int iStart, jStart, iEnd, jEnd;
int flag;

struct Vertex{
	int gScore, fScore;
	char paths[300];
};
struct Child{
	int i, j;
	Child *prev, *next;
}*headC, *tailC;
struct node
{
    int i;
    int j;
    node *prev, *next;
} *head, *tail;
struct heap
{
    int i;
    int j;
    int status;
};
struct Queue
{
    char paths[300];
    Queue *prev, *next;
} *headQ, *tailQ;

void continuee(){
	printf ("Press Enter to continue...");
	getchar();
}

void draw(int arr[], int pivot, int iter)
{
    cls();
    for (int i = -1; i < vals; i++)
    {
    	printf ("          ");
        for (int j = 0; j < size; j++)
        {
            if (vals - i <= arr[j])
            {
            	if(j==pivot){
            		printf("\x1b[31m""%c""\x1b[31m", 219);
				}
				else if(j==iter){
					printf("\x1b[34m""%c""\x1b[34m", 219);
				}
				else{
					printf("\x1b[m""%c""\x1b[0m", 219);
				}
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void drawFinish(int arr[])
{
    system("cls");
    for (int i = -1; i < vals; i++)
    {
    	printf ("          ");
        for (int j = 0; j < size; j++)
        {
            if (vals - i <= arr[j])
            {
                printf("\x1b[32m" "%c" "\x1b[32m", 219);
            }
            else
            {
                printf(" ");
            }
        }
        printf("\x1b[0m" "\n" "\x1b[0m");
    }
    
}

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int divide(int arr[], int &sorted, int start, int end)
{
    int pivot = arr[end];
    int i = (start - 1);
    for (int j = start; j < end; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
            draw(arr, i, j);
            printf("\n                                 Bar sorted: %d/%d                  Bar sorted: %.1lf%%\n", sorted, size, sorted * 100.0 / size);
        }
        
    }

    swap(arr[i + 1], arr[end]);

    return (i + 1);
}

void quickS(int arr[], int &sorted, int start, int end)
{
    if (start < end)
    {
        int part = divide(arr, sorted, start, end);
        sorted++;
        quickS(arr, sorted, start, part - 1);

        quickS(arr, sorted, part + 1, end);
    }
    if (start == end)
    {
        sorted++;
    }
}

void merge(int arr[], int start, int m, int end)
{
    int leftLen = m - start + 1;
    int rightLen = end - m;
    int left[leftLen], right[rightLen];
    for (int i = 0; i < leftLen; i++)
    {
        left[i] = arr[start + i];
    }
    for (int i = 0; i < rightLen; i++)
    {
        right[i] = arr[m + 1 + i];
    }
    int i = 0, j = 0, k = start;
    while (i < leftLen && j < rightLen)
    {
        if (left[i] < right[j])
        {
            arr[k++] = left[i++];
        }
        else
        {
            arr[k++] = right[j++];
        }
    }
    while (i < leftLen)
    {
        arr[k++] = left[i++];
    }
    while (j < rightLen)
    {
        arr[k++] = right[j++];
    }
}

void mergeS(int arr[], int start, int end)
{
    if (start < end)
    {
        int m = start + (end - start) / 2;
        mergeS(arr, start, m);
        mergeS(arr, m + 1, end);
        merge(arr, start, m, end);
        draw(arr, 90, 200);
        printf("\n                                 Bar sorted: %d/%d                  Bar sorted: %.1lf%%\n", 0, size, 0 * 100.0 / size);
    }
}

void heapify(int arr[], int size, int i)
{
    int biggest = i;
    int lc = 2 * i + 1;
    int rc = 2 * i + 2;
    if (lc < size && arr[biggest] < arr[lc])
    {
        biggest = lc;
    }
    if (rc < size && arr[biggest] < arr[rc])
    {
        biggest = rc;
    }
    if (biggest != i)
    {
        swap(arr[i], arr[biggest]);
        draw(arr, i, biggest);
        heapify(arr, size, biggest);
    }
}

void heapS(int arr[], int &sorted)
{
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        heapify(arr, size, i);
    }
    for (int i = size - 1; i >= 0; i--)
    {
        swap(arr[i], arr[0]);
        heapify(arr, i, 0);
        sorted++;
        printf("\n                                 Bar sorted: %d/%d                  Bar sorted: %.1lf%%\n", sorted, size, sorted * 100.0 / size);
    }
}

void printArr(int arr[])
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
}

void sortFinish()
{
    printf("Sorted! Press Enter to continue...");
    getchar();
}

void sorting()
{
    int arr[size + 5] = {};
    int sorted = 0;
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % vals + 1;
        draw(arr, 200, 200);
        printf ("                                               Randomizing Bars\n");
    }
    while (true)
    {
		cls();
        draw(arr, 200, 200);
        // printArr(arr);
        printf ("Choose sorting method:\n");
        printf("1. Quick Sort\n");
        printf("2. Merge Sort\n");
        printf("3. Heap Sort\n");
        printf("4. Back\n");
        int choice;
        scanf("%d", &choice);
        fflush(stdin);
        system("cls");
        switch (choice)
        {
        case 1:
            quickS(arr, sorted, 0, size - 1);
            drawFinish(arr);
            printf("\n                                 Bar sorted: %d/%d                  Bar sorted: %.1lf%%\n", sorted, size, sorted * 100.0 / size);
            printf ("                                             Sorted! ");
            return;
            break;
        case 2:
            mergeS(arr, 0, size - 1);
            sorted = size;
            drawFinish(arr);
            printf("\n                                 Bar sorted: %d/%d                  Bar sorted: %.1lf%%\n", sorted, size, sorted * 100.0 / size);
            printf ("\n                                             Sorted! ");
            return;
            break;
        case 3:
            heapS(arr, sorted);
            drawFinish(arr);
            printf("\n                                 Bar sorted: %d/%d                  Bar sorted: %.1lf%%\n", sorted, size, sorted * 100.0 / size);
            printf ("\n                                             Sorted! ");
            return;
            break;
        case 4:
            return;
        }
    }
}

void drawMaze(int maze[][width])
{
    cls();
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (maze[i][j] == 0)
            {
                printf("\x1b[0m""%c""\x1b[0m", 219);
            }
            else if(i==iStart&&j==jStart){
            	printf("\x1b[35m"
                       "%c"
                       "\x1b[35m",
                       219);
			}
			else if(i==iEnd&&j==jEnd){
            	printf("\x1b[31m"
                       "%c"
                       "\x1b[31m",
                       219);
			}
            else if (maze[i][j] == 3)
            {
                printf("\x1b[34m"
                       "%c"
                       "\x1b[34m",
                       219);
            }
            else if (maze[i][j] == 2)
            {
                printf("\x1b[32m"
                       "%c"
                       "\x1b[32m",
                       219);
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void recursiveBacktrack(int maze[][width], int i, int j)
{
    int flagRand = rand() % 4;
    drawMaze(maze);
    if (flagRand == 0)
    {
        if (maze[i][j + 2] == 0 && j + 2 < width - 1)
        {
            maze[i][j + 1] = 1;
            maze[i][j + 2] = 1;
            recursiveBacktrack(maze, i, j + 2);
        }
        if (maze[i + 2][j] == 0 && i + 2 < height - 1)
        {
            maze[i + 1][j] = 1;
            maze[i + 2][j] = 1;
            recursiveBacktrack(maze, i + 2, j);
        }
        if (maze[i][j - 2] == 0 && j - 2 > 0)
        {
            maze[i][j - 1] = 1;
            maze[i][j - 2] = 1;
            recursiveBacktrack(maze, i, j - 2);
        }
        if (maze[i - 2][j] == 0 && i - 2 > 0)
        {
            maze[i - 1][j] = 1;
            maze[i - 2][j] = 1;
            recursiveBacktrack(maze, i - 2, j);
        }
        else
        {
            return;
        }
    }
    else if(flagRand==1)
    {
        if (maze[i + 2][j] == 0 && i + 2 < height - 1)
        {
            maze[i + 1][j] = 1;
            maze[i + 2][j] = 1;
            recursiveBacktrack(maze, i + 2, j);
        }
        if (maze[i][j - 2] == 0 && j - 2 > 0)
        {
            maze[i][j - 1] = 1;
            maze[i][j - 2] = 1;
            recursiveBacktrack(maze, i, j - 2);
        }
        if (maze[i][j + 2] == 0 && j + 2 < width - 1)
        {
            maze[i][j + 1] = 1;
            maze[i][j + 2] = 1;
            recursiveBacktrack(maze, i, j + 2);
        }
        if (maze[i - 2][j] == 0 && i - 2 > 0)
        {
            maze[i - 1][j] = 1;
            maze[i - 2][j] = 1;
            recursiveBacktrack(maze, i - 2, j);
        }
        else
        {
            return;
        }
    }
    else if(flagRand==2)
    {
    	if (maze[i][j - 2] == 0 && j - 2 > 0)
        {
            maze[i][j - 1] = 1;
            maze[i][j - 2] = 1;
            recursiveBacktrack(maze, i, j - 2);
        }
    	if (maze[i - 2][j] == 0 && i - 2 > 0)
        {
            maze[i - 1][j] = 1;
            maze[i - 2][j] = 1;
            recursiveBacktrack(maze, i - 2, j);
        }
        if (maze[i + 2][j] == 0 && i + 2 < height - 1)
        {
            maze[i + 1][j] = 1;
            maze[i + 2][j] = 1;
            recursiveBacktrack(maze, i + 2, j);
        }
        if (maze[i][j + 2] == 0 && j + 2 < width - 1)
        {
            maze[i][j + 1] = 1;
            maze[i][j + 2] = 1;
            recursiveBacktrack(maze, i, j + 2);
        }
        else
        {
            return;
        }
    }
    else
    {
    	if (maze[i - 2][j] == 0 && i - 2 > 0)
        {
            maze[i - 1][j] = 1;
            maze[i - 2][j] = 1;
            recursiveBacktrack(maze, i - 2, j);
        }
        if (maze[i + 2][j] == 0 && i + 2 < height - 1)
        {
            maze[i + 1][j] = 1;
            maze[i + 2][j] = 1;
            recursiveBacktrack(maze, i + 2, j);
        }
        if (maze[i][j - 2] == 0 && j - 2 > 0)
        {
            maze[i][j - 1] = 1;
            maze[i][j - 2] = 1;
            recursiveBacktrack(maze, i, j - 2);
        }
        if (maze[i][j + 2] == 0 && j + 2 < width - 1)
        {
            maze[i][j + 1] = 1;
            maze[i][j + 2] = 1;
            recursiveBacktrack(maze, i, j + 2);
        }
        else
        {
            return;
        }
    }
}

void backtrackingGen(int maze[][width])
{
	int iRand=1, jRand=1;
    maze[iRand][jRand] = 1;
    recursiveBacktrack(maze, iRand, jRand);
}

node *createNode(int i, int j)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->i = i;
    newNode->j = j;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

int searchNode(int i, int j)
{
    node *curr = head;
    while (curr)
    {
        if (curr->i == i && curr->j == j)
        {
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

void insertNode(int i, int j)
{
    node *curr = head;
    node *newNode = createNode(i, j);
    if (head == NULL)
    {
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

node *deleteNode(node *target)
{
    if (head == target && tail == target)
    {
        head = tail = NULL;
        free(target);
    }
    else if (head == target)
    {
        head = head->next;
        head->prev = NULL;
        free(target);
    }
    else if (tail == target)
    {
        tail = tail->prev;
        tail->next = NULL;
        free(target);
    }
    else
    {
        target->next->prev = target->prev;
        target->prev->next = target->next;
        free(target);
    }
    target = NULL;
}

void genFrontier(int maze[][width], int iSource, int jSource)
{
    if ((iSource + 2 < height - 1 && maze[iSource + 2][jSource] != 1 && searchNode(iSource + 2, jSource) == 0))
    {
        insertNode(iSource + 2, jSource);
        frontierAmount++;
    }
    if ((iSource - 2 > 0 && maze[iSource - 2][jSource] != 1 && searchNode(iSource - 2, jSource) == 0))
    {
        insertNode(iSource - 2, jSource);
        frontierAmount++;
    }
    if ((jSource - 2 > 0 && maze[iSource][jSource - 2] != 1 && searchNode(iSource, jSource - 2) == 0))
    {
        insertNode(iSource, jSource - 2);
        frontierAmount++;
    }
    if ((jSource + 2 < width - 1 && maze[iSource][jSource + 2] != 1 && searchNode(iSource, jSource + 2) == 0))
    {
        insertNode(iSource, jSource + 2);
        frontierAmount++;
    }
}

void pickFrontier(int maze[][width], int iPick, int jPick)
{
    maze[iPick][jPick] = 1;
    int flagRand=rand()%2;
    if(flagRand==0){
    	if (maze[iPick + 2][jPick] == 1 && iPick + 2 < height - 1)
	    {
	        maze[iPick + 1][jPick] = 1;
	        genFrontier(maze, iPick, jPick);
	    }
	    else if (maze[iPick][jPick - 2] == 1 && jPick - 2 > 0)
	    {
	        maze[iPick][jPick - 1] = 1;
	        genFrontier(maze, iPick, jPick);
	    }
	    else if (maze[iPick - 2][jPick] == 1 && iPick - 2 > 0)
	    {
	        maze[iPick - 1][jPick] = 1;
	        genFrontier(maze, iPick, jPick);
	    }
	    else if (maze[iPick][jPick + 2] == 1 && jPick + 2 < width - 1)
	    {
	        maze[iPick][jPick + 1] = 1;
	        genFrontier(maze, iPick, jPick);
	    }
	}
	else{
		if (maze[iPick][jPick - 2] == 1 && jPick - 2 > 0)
	    {
	        maze[iPick][jPick - 1] = 1;
	        genFrontier(maze, iPick, jPick);
	    }
	    else if (maze[iPick - 2][jPick] == 1 && iPick - 2 > 0)
	    {
	        maze[iPick - 1][jPick] = 1;
	        genFrontier(maze, iPick, jPick);
	    }
		else if (maze[iPick + 2][jPick] == 1 && iPick + 2 < height - 1)
	    {
	        maze[iPick + 1][jPick] = 1;
	        genFrontier(maze, iPick, jPick);
	    }
	    else if (maze[iPick][jPick + 2] == 1 && jPick + 2 < width - 1)
	    {
	        maze[iPick][jPick + 1] = 1;
	        genFrontier(maze, iPick, jPick);
	    }
	}
}

node *pickRandom()
{
    int pick = rand() % frontierAmount;
    node *curr = head;
    for (int i = 0; i <= pick; i++)
    {
        if (i == pick)
        {
            return curr;
        }
        curr = curr->next;
    }
    return curr;
}

void primGen(int maze[][width])
{
    int iRand = rand() % (height - 2) + 1;
    if (iRand % 2 == 0)
    {
        iRand--;
    }
    int jRand = rand() % (width - 2) + 1;
    if (jRand % 2 == 0)
    {
        jRand--;
    }
    maze[iRand][jRand] = 1;
    drawMaze(maze);
    frontierAmount = 0;
    genFrontier(maze, iRand, jRand);
    while (head)
    {
        node *pick = pickRandom();
        pickFrontier(maze, pick->i, pick->j);
        deleteNode(pick);
        frontierAmount--;
        drawMaze(maze);
    }
}

void makeSet(heap parent[][width])
{
    for (int i = 1; i < height; i += 2)
    {
        for (int j = 1; j < width; j += 2)
        {
            parent[i][j].i = i;
            parent[i][j].j = j;
            parent[i][j].status = 0;
        }
    }
}

heap findParent(heap parent[height][width], int i, int j)
{
    if (parent[i][j].i == i && parent[i][j].j == j)
    {
        return parent[i][j];
    }
    parent[i][j] = findParent(parent, parent[i][j].i, parent[i][j].j);
    return parent[i][j];
}

int isSameSet(heap parent[height][width], int i1, int j1, int i2, int j2)
{
    heap parent1 = findParent(parent, i1, j1);
    heap parent2 = findParent(parent, i2, j2);
    if (parent1.i == parent2.i && parent1.j == parent2.j)
    {
        return 0;
    }
    return 1;
}

void joinSet(heap parent[height][width], int i1, int j1, int i2, int j2)
{
    heap parent1 = findParent(parent, i1, j1);
    heap parent2 = findParent(parent, i2, j2);
    parent[parent1.i][parent1.j] = parent2;
    return;
}

void kruskalPick(heap parent[height][width], int maze[][width], int iPick, int jPick)
{
    int flag = rand() % 2 + 1;
    maze[iPick][jPick] = 1;
    if (flag == 1)
    {
        if (iPick - 2 > 0 && isSameSet(parent, iPick, jPick, iPick - 2, jPick) != 0)
        {
            maze[iPick - 1][jPick] = 1;
            joinSet(parent, iPick, jPick, iPick - 2, jPick);
            return;
        }
        if (iPick + 2 < height - 1 && isSameSet(parent, iPick, jPick, iPick + 2, jPick) != 0)
        {
            maze[iPick + 1][jPick] = 1;
            joinSet(parent, iPick, jPick, iPick + 2, jPick);
            return;
        }
        if (jPick - 2 > 0 && isSameSet(parent, iPick, jPick, iPick, jPick - 2) != 0)
        {
            maze[iPick][jPick - 1] = 1;
            joinSet(parent, iPick, jPick, iPick, jPick - 2);
            return;
        }
        if (jPick + 2 < width - 1 && isSameSet(parent, iPick, jPick, iPick, jPick + 2) != 0)
        {
            maze[iPick][jPick + 1] = 1;
            joinSet(parent, iPick, jPick, iPick, jPick + 2);
            return;
        }
    }
    else if (flag == 2)
    {
        if (jPick - 2 > 0 && isSameSet(parent, iPick, jPick, iPick, jPick - 2) != 0)
        {
            maze[iPick][jPick - 1] = 1;
            joinSet(parent, iPick, jPick, iPick, jPick - 2);
            return;
        }
        if (jPick + 2 < width - 1 && isSameSet(parent, iPick, jPick, iPick, jPick + 2) != 0)
        {
            maze[iPick][jPick + 1] = 1;
            joinSet(parent, iPick, jPick, iPick, jPick + 2);
            return;
        }
        if (iPick + 2 < height - 1 && isSameSet(parent, iPick, jPick, iPick + 2, jPick) != 0)
        {
            maze[iPick + 1][jPick] = 1;
            joinSet(parent, iPick, jPick, iPick + 2, jPick);
            return;
        }
        if (iPick - 2 > 0 && isSameSet(parent, iPick, jPick, iPick - 2, jPick) != 0)
        {
            maze[iPick - 1][jPick] = 1;
            joinSet(parent, iPick, jPick, iPick - 2, jPick);
            return;
        }
    }
}

void kruskalGen(int maze[][width])
{
    heap parent[height][width];
    makeSet(parent);
    int iPick, jPick;
    for (int i = 1; i < height - 1; i += 2)
    {
        for (int j = 1; j < width - 1; j += 2)
        {
            insertNode(i, j);
            frontierAmount++;
        }
    }
    while (head)
    {
        node *pick = pickRandom();
        kruskalPick(parent, maze, pick->i, pick->j);
        deleteNode(pick);
        frontierAmount--;
        drawMaze(maze);
    }
}

Queue *createQueue(char paths[])
{
    Queue *newQueue = (Queue *)malloc(sizeof(Queue));
    strcpy(newQueue->paths, paths);
    newQueue->prev = newQueue->next = NULL;
    return newQueue;
}

void insertQueue(int maze[][width], char paths[])
{
    Queue *newQueue = createQueue(paths);
    if (headQ == NULL)
    {
        headQ = tailQ = newQueue;
    }
    else
    {
        tailQ->next = newQueue;
        newQueue->prev = tailQ;
        tailQ = newQueue;
    }
    int len = strlen(paths);
    int iCurr = iStart;
    int jCurr = jStart;
    for (int i = 0; i < len; i++)
    {
        if (paths[i] == 'L')
        {
            jCurr--;
        }
        else if (paths[i] == 'R')
        {
            jCurr++;
        }
        else if (paths[i] == 'U')
        {
            iCurr--;
        }
        else if (paths[i] == 'D')
        {
            iCurr++;
        }
        maze[iCurr][jCurr] = 3;
    }
}

void insertQueueDfs(int maze[][width], char paths[]){
	Queue *newQueue = createQueue(paths);
    if (headQ == NULL)
    {
        headQ = tailQ = newQueue;
    }
    else
    {
        headQ->prev = newQueue;
        newQueue->next = headQ;
        headQ = newQueue;
    }
    int len = strlen(paths);
    int iCurr = iStart;
    int jCurr = jStart;
    for (int i = 0; i < len; i++)
    {
        if (paths[i] == 'L')
        {
            jCurr--;
        }
        else if (paths[i] == 'R')
        {
            jCurr++;
        }
        else if (paths[i] == 'U')
        {
            iCurr--;
        }
        else if (paths[i] == 'D')
        {
            iCurr++;
        }
        maze[iCurr][jCurr] = 3;
    }
}

void backTrack(int maze[][width], char paths[])
{
    int len = strlen(paths);
    int iCurr=iStart;
    int jCurr=jStart;
    for (int i = 0; i < len; i++)
    {
        if (paths[i] == 'L')
        {
            jCurr--;
        }
        else if (paths[i] == 'R')
        {
            jCurr++;
        }
        else if (paths[i] == 'U')
        {
            iCurr--;
        }
        else if (paths[i] == 'D')
        {
            iCurr++;
        }
        maze[iCurr][jCurr] = 2;
        drawMaze(maze);
    }
}

int checkEnd(int maze[][width], char paths[])
{
    int len = strlen(paths);
    int iCurr = iStart;
    int jCurr = jStart;
    for (int i = 0; i < len; i++)
    {
        if (paths[i] == 'L')
        {
            jCurr--;
        }
        else if (paths[i] == 'R')
        {
            jCurr++;
        }
        else if (paths[i] == 'U')
        {
            iCurr--;
        }
        else if (paths[i] == 'D')
        {
            iCurr++;
        }
    }
    if (iCurr == iEnd && jCurr == jEnd)
    {
        return 0;
    }
    return 1;
}

void printNode(){
	node *curr=head;
	while(curr){
		printf ("%d %d->", curr->i, curr->j);
		curr=curr->next;
	}
	return;
}

void popAllNode(){
	while(head){
        deleteNode(head);
    }
}

int checkNode(int maze[][width], char paths[])
{
    int len = strlen(paths);
    int iCurr = iStart;
    int jCurr = jStart;
    if (iCurr <= 0 || iCurr >= height - 1 || jCurr <= 0 || jCurr >= width - 1)
        {
        	popAllNode();
            return 1;
        }
    insertNode(iCurr, jCurr);
    for (int i = 0; i < len; i++)
    {
        if (paths[i] == 'L')
        {
            jCurr--;
        }
        else if (paths[i] == 'R')
        {
            jCurr++;
        }
        else if (paths[i] == 'U')
        {
            iCurr--;
        } 
        else if (paths[i] == 'D')
        {
            iCurr++;
        }
        if (iCurr <= 0 || iCurr >= height - 1 || jCurr <= 0 || jCurr >= width - 1)
        {
        	popAllNode();
            return 1;
        }
        if (maze[iCurr][jCurr] == 0)
        {
        	popAllNode();
            return 1;
        }
        if(searchNode(iCurr, jCurr)==1){
        	popAllNode();
            return 1;
        }
        insertNode(iCurr, jCurr);
    }
    popAllNode();
    return 0;
}

void deleteQueue()
{
    if (headQ == NULL)
    {
        return;
    }
    Queue *curr = headQ;
    if (headQ == tailQ)
    {
        headQ = tailQ = NULL;
    }
    else
    {
        headQ = headQ->next;
        headQ->prev = NULL;
    }
    free(curr);
    return;
}

void printQueue(){
	Queue *curr=headQ;
	while(curr){
		printf ("%s->", curr->paths);
		curr=curr->next;
	}
	printf ("\n");
}

void bfs(int maze[][width])
{
    insertQueue(maze, "");
    char directions[5] = {"LRUD"};
    while (checkEnd(maze, headQ->paths) == 1)
    {
    		
        for (int i = 0; i < 4; i++)
        {
            char added[300] = {};
            strcpy(added, headQ->paths);
            added[strlen(added)] = directions[i];
            added[strlen(added)+1] = '\0';
            
            if (checkNode(maze, added) == 0)
            {
                insertQueue(maze, added);
                drawMaze(maze);
            }
            if(checkEnd(maze, headQ->paths) == 0){
            	break;
			}
        }
        if(checkEnd(maze, headQ->paths) == 0){
            	break;
		}
        deleteQueue();
    }
    backTrack(maze, headQ->paths);
}

void dfsRec(int maze[][width]){
	char directions[5] = {"LRUD"};
	int noPass=0;
	for (int i = 0; i < 4; i++)
        {
            char added[300] = {};
            strcpy(added, headQ->paths);
            added[strlen(added)] = directions[i];
            added[strlen(added)+1] = '\0';
            
            if (checkNode(maze, added) == 0)
            {
                insertQueueDfs(maze, added);
                drawMaze(maze);
                
                dfsRec(maze);
            }
            if(checkEnd(maze, headQ->paths)==0){
                if(flag==0){
               		backTrack(maze, headQ->paths);
               		flag=1;
				}	
                	return;
			}
            else{
            	noPass++;
			}
        }
        deleteQueue();
}

void dfs(int maze[][width])
{
	flag=0;
	insertQueueDfs(maze, "");
    while (checkEnd(maze, headQ->paths) == 1)
    {
		dfsRec(maze);
    }
}

void dijkstra()
{
}

Child *createChild(int i, int j){
	Child *newNode = (Child *)malloc(sizeof(Child));
    newNode->i = i;
    newNode->j = j;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

void insertPriorityChild(int i, int j, struct Vertex vertices[][width]){
	Child *newNode=createChild(i, j);
	if(headC==NULL){
		headC=tailC=newNode;
		return;
	}
	Child *curr=headC;
	if(vertices[i][j].fScore<vertices[headC->i][headC->j].fScore){
		headC->prev=newNode;
		newNode->next=headC;
		headC=newNode;
	}
	else if(vertices[i][j].fScore>=vertices[tailC->i][tailC->j].fScore){
		tailC->next=newNode;
		newNode->prev=tailC;
		tailC=newNode;
	}
	else{
		while(curr->next&&vertices[curr->next->i][curr->next->j].fScore<vertices[i][j].fScore){
			curr=curr->next;
		}
		newNode->next=curr->next;
		newNode->prev=curr;
		curr->next->prev=newNode;
		curr->next=newNode;
	}
}

void popChild(){
	if(headC==NULL){
		return;
	}
	if(headC==tailC){
		free(headC);
		headC=tailC=NULL;
		return;
	}
	Child *del=headC;
	headC=headC->next;
	headC->prev=NULL;
	free(del);
}

void printChilds(){
	Child *curr=headC;
	while(curr){
		printf ("%d %d->", curr->i, curr->j);
		curr=curr->next;
	}
	printf ("\n");
}

int hCount(int i, int j){
	int diff1=iEnd-i;
	if(diff1<0) diff1*=-1;
	int diff2=jEnd-j;
	if(diff2<0) diff2*=-1;
	return diff1+diff2;
}

void aStar(int maze[][width])
{
	Vertex vertices[height][width]={};
	vertices[iStart][jStart].gScore=0;
	char directions[5] = {"LRUD"};
	int iCurr=iStart;
	int jCurr=jStart;
	maze[iStart][jStart]=3;
	vertices[iStart][jStart].fScore=vertices[iStart][jStart].gScore+hCount(iStart, jStart);
	insertPriorityChild(iCurr, jCurr, vertices);
	while(checkEnd(maze, vertices[headC->i][headC->j].paths)==1){
		for(int i=0;i<4;i++){
			char added[300] = {};
			int tempg=vertices[iCurr][jCurr].gScore+1;
            strcpy(added, vertices[headC->i][headC->j].paths);
            int len=strlen(added);
            added[len] = directions[i];
            int iTemp=iCurr;
            int jTemp=jCurr;
            added[len+1] = '\0';
			if (directions[i] == 'L')
	        {
	            jTemp--;
	        }
	        else if (directions[i] == 'R')
	        {
	            jTemp++;
	        }
	        else if (directions[i] == 'U')
	        {
	            iTemp--;
	        } 
	        else if (directions[i] == 'D')
	        {
	            iTemp++;
	        }
	        if(checkNode(maze, added)!=1){
	        	vertices[iTemp][jTemp].gScore=tempg;
	        	vertices[iTemp][jTemp].fScore=tempg+hCount(iTemp, jTemp);
	        	strcpy(vertices[iTemp][jTemp].paths, added);
	        	insertPriorityChild(iTemp, jTemp, vertices);
			}
		}
		popChild();
		iCurr=headC->i;
		jCurr=headC->j;
		maze[iCurr][jCurr]=3;
		drawMaze(maze);
	}
	backTrack(maze, vertices[headC->i][headC->j].paths);
	while(headC){
		popChild();
	}
}

void path(int maze[][width])
{
	while(true){
		while(true){
			while(true){
				printf ("Enter start x-point (1-%d): ", width-2);
				scanf ("%d", &jStart); fflush(stdin);
				if(jStart>0&&jStart<width-1){
					break;
				}
			}
			while(true){
				printf ("Enter start y-point (1-%d): ", height-2);
				scanf ("%d", &iStart); fflush(stdin);
				if(iStart>0&&iStart<height-1){
					break;
				}
			}
			if(maze[iStart][jStart]!=0){
				
				system("cls"); drawMaze(maze);
				break;
			}
			printf ("Cannot be a wall\n");
		}
		while(true){
			while(true){
				printf ("Enter end x-point (1-%d): ", width-2);
				scanf ("%d", &jEnd); fflush(stdin);
				if(jEnd>0&&jEnd<width-1){
					break;
				}
			}
			while(true){
				printf ("Enter end y-point (1-%d): ", height-2);
				scanf ("%d", &iEnd); fflush(stdin);
				if(iEnd>0&&iEnd<height-1){
					break;
				}
			}
			if((iStart!=iEnd||jStart!=jEnd)&&maze[iEnd][jEnd]!=0){
				system("cls"); drawMaze(maze);
				break;
			}
			printf ("%d %d\n", iEnd, jEnd);
			printf ("Cannot be a wall or same as starting point\n");
		}
		printf("Choose maze-solving algorithm:\n");
	    printf("1. BFS\n");
	    printf("2. DFS\n");
	    printf("3. Dijkstra's\n");
	    printf("4. A*\n");
	    printf ("5. Back\n");
	    int choice;
	    scanf("%d", &choice);
	    fflush(stdin);
	    system("cls");
	    drawMaze(maze);
	    switch (choice)
	    {
	    case 1:
	        bfs(maze);
	        return;
	    case 2:
	        dfs(maze);
	        return;
	    case 3:
	        bfs(maze);
	        return;
	    case 4:
	        aStar(maze);
	        return;
	    case 5:
	    	return;
	    }
	}
    
}

void mazeSolving()
{
    while (true)
    {
        int maze[height][width] = {};
        printf("Choose Maze Generator method:\n");
        printf("1. Backtracking\n");
        printf("2. Prim\n");
        printf("3. Kruskal\n");
        printf("4. Back\n");
        frontierAmount = 0;
        iEnd=height-2;
        jEnd=width-2;
        iStart=1;
        jStart=1;
        int choice;
        scanf("%d", &choice);
        fflush(stdin);
        system("cls");
        switch (choice)
        {
        case 1:
            backtrackingGen(maze);
            path(maze);
            continuee();
            return;
        case 2:
            primGen(maze);
            path(maze);
            continuee();
            return;
        case 3:
            kruskalGen(maze);
            path(maze);
            continuee();
            return;
        case 4:
            return;
        }
    }
}



void sandbox()
{
	printf ("SandBox\n");
	while(true){
		printf ("Enter start x-point (1-%d): ", width-2);
		scanf ("%d", &jStart); fflush(stdin);
		if(jStart>0&&jStart<width-1){
			break;
		}
	}
	while(true){
		printf ("Enter start y-point (1-%d): ", height-2);
		scanf ("%d", &iStart); fflush(stdin);
		if(iStart>0&&iStart<height-1){
			break;
		}
	}
	while(true){
		while(true){
			printf ("Enter end x-point (1-%d): ", width-2);
			scanf ("%d", &jEnd); fflush(stdin);
			if(jEnd>0&&jEnd<width-1){
				break;
			}
		}
		while(true){
			printf ("Enter end y-point (1-%d): ", height-2);
			scanf ("%d", &iEnd); fflush(stdin);
			if(iEnd>0&&iEnd<height-1){
				break;
			}
		}
		if(iStart!=iEnd||jStart!=jEnd){
			break;
		}
		printf ("Cannot be same as starting point\n");
	}
	int maze[height][width] = {};
	for(int i=1;i<height-1;i++){
		for(int j=1;j<width-1;j++){
			maze[i][j]=1;
		}
	}
	drawMaze(maze);
	while (true)
    {
        printf("Choose maze-solving algorithm:\n");
	    printf("1. BFS\n");
	    printf("2. DFS\n");
	    printf("3. Dijkstra's\n");
	    printf("4. A*\n");
	    printf ("5. Back\n");
	    int choice;
	    scanf("%d", &choice);
	    fflush(stdin);
	    maze[iStart][jStart]=4;
	    system("cls");
	    drawMaze(maze);
	    switch (choice)
	    {
	    case 1:
	        bfs(maze);
	        continuee();
	        return;
	    case 2:
	        dfs(maze);
	        continuee();
	        return;
	    case 3:
	        bfs(maze);
	        continuee();
	        return;
	    case 4:
	        aStar(maze);
	        continuee();
	        return;
	    case 5:
	    	return;
	    }
    }
    continuee();
}

int main()
{
    hideCursor();
    srand(time(NULL));
    while (true)
    {
        system("cls");
        printf("CVisualizer\n");
        printf("================\n");
        printf("1. Sorting\n");
        printf("2. Maze Solving\n");
        printf("3. Sandbox\n");
        printf("4. Exit\n");
        int choice;
        scanf("%d", &choice);
        fflush(stdin);
        system("cls");
        switch (choice)
        {
        case 1:
            sorting();
            continuee();
            break;
        case 2:
            mazeSolving();
            break;
        case 3:
            sandbox();
            break;
        case 4:
        	printf ("Thank you for using the program...\n");
            return 0;
        }
    }
}
