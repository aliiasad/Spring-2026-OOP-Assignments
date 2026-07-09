//Asad Ali
//25L-0519

# include <iostream>
# include <ctime>
# include <cstdlib>
# include <climits>

using namespace std;

void inputSize(int &size);
int** generateMaze(int size);
void printMaze(int **maze, int size, int pRow, int pCol);
bool findShortestPath(int **maze, int size, bool silent);

bool moveExists(int ** matrix, int pRow, int pCol, int size);
bool handleMove(int **matrix, int &pRow, int &pCol, int size);
bool checkResult(int pRow, int pCol, int size);

void shortestPath(int** maze, int currentRow, int currentCol,
                  int** visited, char** parent, char** bestParent,
                  int rows, int cols, int steps, int &minMoves);

bool isSafe(int currentRow, int currentCol, int rows, int cols, int** visited, int** maze);

int main()  {
    srand(time(0));

    int size = 0;   
    inputSize(size);

    int pRow = 0, pCol = 0;
    int **maze = generateMaze(size);

    if (!findShortestPath(maze, size, true)) {
        printMaze(maze, size, pRow, pCol);
        cout << "No possible path exists in this maze!" << endl;
    } else {
        int **originalMaze = new int*[size];
        for (int i = 0; i < size; i++) {
            *(originalMaze + i) = new int[size];
            for (int j = 0; j < size; j++)
                *(*(originalMaze + i) + j) = *(*(maze + i) + j);
        }

        int movesTaken = 0;

        while ((pRow != size - 1 || pCol != size - 1) && moveExists(maze, pRow, pCol, size)) {
            printMaze(maze, size, pRow, pCol);
            
            cout << "Current Position: " << pRow << ", " << pCol << endl;
            cout << "Enter W/A/S/D to move!" << endl;

            bool success = handleMove(maze, pRow, pCol, size);

            if (success) movesTaken++;
            else cout << "Invalid Move! Try Again." << endl;
        }

        if (checkResult(pRow, pCol, size)) {
            printMaze(maze, size, pRow, pCol);
            cout << "CONGRATULATIONS! You found the exit!" << endl;
            cout << "Total Moves: " << movesTaken << endl;
        } else {
            cout << "GAME OVER! You are trapped with no moves left." << endl;
        }

        cout << "\nNow showing shortest possible path:\n";

        findShortestPath(originalMaze, size, false);

        for (int i = 0; i < size; i++)
            delete[] *(originalMaze + i);
        delete[] originalMaze;
        originalMaze = nullptr;
    }

    for (int i = 0; i < size; i++)
        delete[] *(maze + i);
    delete[] maze;
    maze = nullptr;

    return 0;
}

void inputSize(int &size) {
    const int MAX_SIZE = 20;
    while (size < 2 || size > MAX_SIZE) {
        cout << "Enter maze size (2-" << MAX_SIZE << "): ";
        if (!(cin >> size)) {
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
    cin.ignore(1000, '\n');
}

int** generateMaze(int size) {
    int **maze = new int*[size];
    for (int i = 0; i < size; i++)
        *(maze + i) = new int[size];

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            *(*(maze + i) + j) = (rand() % 4 == 0) ? 0 : 1;

    *(*(maze + 0) + 0) = 1;
    *(*(maze + size - 1) + size - 1) = 1;

    return maze;
}

void printMaze(int **maze, int size, int pRow, int pCol) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == pRow && j == pCol)
                cout << "P ";
            else if (*(*(maze + i) + j) == 0)
                cout << "0 ";
            else if (*(*(maze + i) + j) == '.')
                cout << ". ";
            else if (i == size - 1 && j == size - 1)
                cout << "E ";
            else
                cout << "1 ";
        }
        cout << endl;
    }
    cout << endl;
}

bool moveExists(int ** matrix, int pRow, int pCol, int size)  {
    if (pRow > 0 && (*(*(matrix + (pRow - 1)) + pCol) == 1 || *(*(matrix + (pRow - 1)) + pCol) == '.')) return true;
    if (pCol > 0 && (*(*(matrix + pRow) + (pCol - 1)) == 1 || *(*(matrix + pRow) + (pCol - 1)) == '.')) return true;
    if (pRow < size - 1 && (*(*(matrix + (pRow + 1)) + pCol) == 1 || *(*(matrix + (pRow + 1)) + pCol) == '.')) return true;
    if (pCol < size - 1 && (*(*(matrix + pRow) + (pCol + 1)) == 1 || *(*(matrix + pRow) + (pCol + 1)) == '.')) return true;
    return false;
}

bool handleMove(int **matrix, int &pRow, int &pCol, int size)  {
    char move;
    cin >> move;

    int nextRow = pRow, nextCol = pCol;

    if (move == 'W' || move == 'w') nextRow--;
    else if(move == 'A' || move == 'a') nextCol--;
    else if(move == 'S' || move == 's') nextRow++;
    else if(move == 'D' || move == 'd') nextCol++;
    else return false;

    if (nextRow >= 0 && nextRow < size &&
        nextCol >= 0 && nextCol < size &&
        (*(*(matrix + nextRow) + nextCol) == 1 || *(*(matrix + nextRow) + nextCol) == '.')) {

        *(*(matrix + pRow) + pCol) = '.';
        pRow = nextRow;
        pCol = nextCol;
        return true;
    }
    return false;
}

bool checkResult(int pRow, int pCol, int size) {
    return (pRow == size - 1 && pCol == size - 1);
}

bool isSafe(int currentRow, int currentCol, int rows, int cols, int** visited, int** maze) {
    return (currentRow >= 0 && currentCol >= 0 &&
            currentRow < rows && currentCol < cols &&
            *(*(visited + currentRow) + currentCol) == 0 &&
            *(*(maze + currentRow) + currentCol) != 0);
}

void shortestPath(int** maze, int currentRow, int currentCol,
                  int** visited, char** parent, char** bestParent,
                  int rows, int cols, int steps, int &minMoves) {

    if (currentRow == rows - 1 && currentCol == cols - 1) {
        if (steps < minMoves) {
            minMoves = steps;
            for(int i=0; i<rows; i++)   {
                for(int j=0; j<cols; j++)   {
                    *(*(bestParent + i) + j) = *(*(parent + i) + j);
                }
            }
        }
        return;
    }

    if (steps >= minMoves) return;

    *(*(visited + currentRow) + currentCol) = 1;

    int rowDirection[4] = {0, 1, 0, -1};
    int colDirection[4] = {1, 0, -1, 0};
    char directionLabels[4] = {'R','D','L','U'};

    for (int i = 0; i < 4; i++) {
        int neighbourRow = currentRow + *(rowDirection + i);
        int neighbourCol = currentCol + *(colDirection + i);

        if (isSafe(neighbourRow, neighbourCol, rows, cols, visited, maze)) {
            *(*(parent + neighbourRow) + neighbourCol) = *(directionLabels + i);
            shortestPath(maze, neighbourRow, neighbourCol,
                         visited, parent, bestParent,
                         rows, cols, steps + 1, minMoves);
        }
    }
    *(*(visited + currentRow) + currentCol) = 0;
}

bool findShortestPath(int **maze, int size, bool silent) {
    int max = size * size;
    int **visited = new int*[size];
    char **parent = new char*[size];
    char **bestParent = new char*[size];

    for (int i = 0; i < size; i++) {
        *(visited + i) = new int[size]();
        *(parent + i) = new char[size]();
        *(bestParent + i) = new char[size]();
    }

    int minMoves = size * size + 1;
    shortestPath(maze, 0, 0, visited, parent, bestParent, size, size, 0, minMoves);

    if (minMoves == size * size + 1) {
        for (int i = 0; i < size; i++) {
            delete[] visited[i]; delete[] parent[i]; delete[] bestParent[i];
        }
        delete[] visited; 
        delete[] parent; 
        delete[] bestParent;
        return false;
    }

    if (!silent) {
        int row = size - 1, col = size - 1;
        char *path = new char[max];
        int length = 0;

        while (!(row == 0 && col == 0)) {
            char d = *(*(bestParent + row) + col);
            *(path + (length++)) = d;
            if (d == 'R') col--;
            else if (d == 'L') col++;
            else if (d == 'U') row++;
            else if (d == 'D') row--;
            else break;
        }

        cout << "Shortest Path => ";
        for (int i = length - 1; i >= 0; i--) {
            if (*(path + i) == 'U') cout << "up";
            if (*(path + i) == 'D') cout << "down";
            if (*(path + i) == 'L') cout << "left";
            if (*(path + i) == 'R') cout << "right";
            if (i != 0) cout << ", ";
        }
        cout << endl;
        delete[] path;
    }

    for (int i = 0; i < size; i++) {
        delete[] *(visited + i);
        delete[] *(parent + i);
        delete[] *(bestParent + i);
    }
    delete[] visited; 
    delete[] parent; 
    delete[] bestParent;
    //no need to null them as they are local
    return true;
}