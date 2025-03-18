//Bilge Kaan Yildirim 30607 CS204 HW1

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unistd.h>
#include <climits>

#ifdef _WIN32
#include <windows.h>
#else
#include <mach-o/dyld.h>
#endif

using namespace std;

// Function to get the directory where the executable is running
string getExecutableDirectory()
{
    char path[PATH_MAX];

#ifdef _WIN32
    GetModuleFileNameA(NULL, path, PATH_MAX);
#else
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) != 0)
    {
        cerr << "Error: Buffer too small!" << endl;
        return "";
    }
#endif

    string fullPath(path);
    size_t lastSlash = fullPath.find_last_of("/\\");
    return fullPath.substr(0, lastSlash); // Extract directory path
}

bool IsMatrixEmpty(const vector<vector<char> > &matrix)
{
    bool checker = true;

    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[i].size(); ++j)
        {
            if (matrix[i][j] != '-')
            {
                return false;
            }
        }
    }
    return checker;
}

// check chosen cell can move outside the table
bool IsCellAtTheEnd(const vector<vector<char> > &matrix, const int &rowPos, const int &columnPos)
{
    bool checker = false;

    if (matrix[rowPos][columnPos] == 'r')
    {
        if (columnPos == matrix[rowPos].size() - 1)
        {
            return true;
        }
    }
    else if (matrix[rowPos][columnPos] == 'l')
    {
        if (columnPos == 0)
        {
            return true;
        }
    }
    else if (matrix[rowPos][columnPos] == 'u')
    {
        if (rowPos == 0)
        {
            return true;
        }
    }
    else if (matrix[rowPos][columnPos] == 'd')
    {
        if (rowPos == matrix.size() - 1)
        {
            return true;
        }
    }

    return checker;
}

bool IsCellAtTheEnd(const vector<vector<char> > &matrix, const int &rowPos, const int &columnPos, const char &direction)
{
    bool checker = false;

    if (direction == 'r')
    {
        if (columnPos == matrix[rowPos].size() - 1)
        {
            return true;
        }
    }
    else if (direction == 'l')
    {
        if (columnPos == 0)
        {
            return true;
        }
    }
    else if (direction == 'u')
    {
        if (rowPos == 0)
        {
            return true;
        }
    }
    else if (direction == 'd')
    {
        if (rowPos == matrix.size() - 1)
        {
            return true;
        }
    }

    return checker;
}

// check chosen cell can move to its way
bool CanCellMove(const vector<vector<char> > &matrix, const int &rowPos, const int &columnPos)
{
    if (!IsCellAtTheEnd(matrix, rowPos, columnPos))
    {
        if (matrix[rowPos][columnPos] == 'r')
        {
            if (matrix[rowPos][columnPos + 1] == '-')
            {
                return true;
            }
        }
        if (matrix[rowPos][columnPos] == 'l')
        {
            if (matrix[rowPos][columnPos - 1] == '-')
            {
                return true;
            }
        }
        if (matrix[rowPos][columnPos] == 'u')
        {
            if (matrix[rowPos - 1][columnPos] == '-')
            {
                return true;
            }
        }
        if (matrix[rowPos][columnPos] == 'd')
        {
            if (matrix[rowPos + 1][columnPos] == '-')
            {
                return true;
            }
        }
        return false;
    }
    else
    {
        return true;
    }
}

// check all cells can move to its way
bool AreMovesPossible(const vector<vector<char> > &matrix)
{
    bool checker = false;

    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[i].size(); ++j)
        {
            checker = CanCellMove(matrix, i, j);

            if (checker)
            {
                return checker;
            }
        }
    }

    return checker;
}

void PrintMatrix(const vector<vector<char> > &matrix)
{
    for (int i = 0; i < matrix.size(); ++i)
    {
        for (int j = 0; j < matrix[i].size(); ++j)
        {
            cout << matrix[i][j];
        }
        cout << endl;
    }
}

// drop the cell
void DropCell(vector<vector<char> > &matrix, const int &row, const int &column)
{
    matrix[row][column] = '-';
}

// move cell to its direction
void MoveCell(vector<vector<char> > &matrix, const int &rowPos, const int &columnPos)
{
    bool isMoved = false;

    if (matrix[rowPos][columnPos] == 'r')
    {
        if (IsCellAtTheEnd(matrix, rowPos, columnPos))
        {
            DropCell(matrix, rowPos, columnPos);
        }
        else
        {
            for (int i = columnPos + 1; i < matrix[rowPos].size() && !isMoved; ++i)
            {
                if (matrix[rowPos][i] != '-')
                {
                    matrix[rowPos][columnPos] = '-';
                    matrix[rowPos][i - 1] = 'r';
                    isMoved = true;
                }
                if (IsCellAtTheEnd(matrix, rowPos, i, matrix[rowPos][columnPos]))
                {
                    DropCell(matrix, rowPos, columnPos);
                }
            }
        }
    }
    else if (matrix[rowPos][columnPos] == 'l')
    {
        if (IsCellAtTheEnd(matrix, rowPos, columnPos))
        {
            DropCell(matrix, rowPos, columnPos);
        }
        else
        {
            for (int i = columnPos - 1; i >= 0 && !isMoved; --i)
            {
                if (matrix[rowPos][i] != '-')
                {
                    matrix[rowPos][columnPos] = '-';
                    matrix[rowPos][i + 1] = 'l';
                    isMoved = true;
                }
                if (IsCellAtTheEnd(matrix, rowPos, i, matrix[rowPos][columnPos]))
                {
                    DropCell(matrix, rowPos, columnPos);
                }
            }
        }
    }
    else if (matrix[rowPos][columnPos] == 'u')
    {
        if (IsCellAtTheEnd(matrix, rowPos, columnPos))
        {
            DropCell(matrix, rowPos, columnPos);
        }
        else
        {
            for (int i = rowPos - 1; i >= 0 && !isMoved; --i)
            {
                if (matrix[i][columnPos] != '-')
                {
                    matrix[rowPos][columnPos] = '-';
                    matrix[i + 1][columnPos] = 'u';
                    isMoved = true;
                }
                if (IsCellAtTheEnd(matrix, i, columnPos, matrix[rowPos][columnPos]))
                {
                    DropCell(matrix, rowPos, columnPos);
                }
            }
        }
    }
    else if (matrix[rowPos][columnPos] == 'd')
    {
        if (IsCellAtTheEnd(matrix, rowPos, columnPos))
        {
            DropCell(matrix, rowPos, columnPos);
        }
        else
        {
            for (int i = rowPos + 1; i < matrix.size() && !isMoved; ++i)
            {
                if (matrix[i][columnPos] != '-')
                {
                    matrix[rowPos][columnPos] = '-';
                    matrix[i - 1][columnPos] = 'd';
                    isMoved = true;
                }
                if (IsCellAtTheEnd(matrix, i, columnPos, matrix[rowPos][columnPos]))
                {
                    DropCell(matrix, rowPos, columnPos);
                }
            }
        }
    }
}

string getExecutablePath() {
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    if (count != -1) {
        result[count] = '\0';  // Null-terminate the string
        string fullPath(result);
        size_t lastSlash = fullPath.find_last_of("/\\");
        return fullPath.substr(0, lastSlash); // Return directory path only
    }
    return ""; // Return empty if failed
}

int main()
{
    string filename, line;

    string execDir = getExecutableDirectory();

    if (execDir.empty())
    {
        cerr << "Error: Could not determine executable directory!" << endl;
        return 1;
    }

    // For debug
    //cout << "Executable is running from: " << execDir << endl;

    cout << "Please enter the file name:" << endl;
    cin >> filename;

    string filePath = execDir + "/Inputs/" + filename;

    ifstream input(filePath);

    while (input.fail()) // check correct filename is entered and request until it is correct
    {
        cout << "Could not open the file. Please enter a valid file name:" << endl;
        cin >> filename;
        filePath = execDir + "/Inputs/" + filename;
        input.open(filePath);
    }

    vector<vector<char> > gameTable;

    // get first line length to check all line lengths are equal in the next while loop
    getline(input, line);
    unsigned int lineLength = line.length();
    input.seekg(0);

    while (getline(input, line))
    {
        if (lineLength != line.length()) // check line length equality with first line length
        {
            cout << "Erroneous file content. Program terminates." << endl;
            return 0;
        }

        vector<char> row;

        for (unsigned int i = 0; i < line.length(); ++i) // check all characters are valid in the line then append chars to vector
        {
            char chr = line[i];
            if (chr != 'u' && chr != 'd' && chr != 'l' && chr != 'r' && chr != '-')
            {
                cout << "Erroneous file content. Program terminates." << endl;
                return 0;
            }

            row.push_back(chr);
        }
        gameTable.push_back(row);
    }

    cout << "The matrix file contains:" << endl;
    PrintMatrix(gameTable);

    if (IsMatrixEmpty(gameTable))
    {
        cout << "The matrix is empty." << endl;
        return 0;
    }
    else if (!AreMovesPossible(gameTable))
    {
        cout << "No more moves are possible." << endl;
        return 0;
    }

    bool gameOnProgress = true;
    int row, column;

    while(gameOnProgress)
    {
        cout << "Please enter the row and column of the tile that you want to move:" << endl;
        cin >> row >> column;

        while (row < 0 || row > gameTable.size() - 1 || column < 0 || column > gameTable[0].size() - 1) // check validity of inputs, if not ask again
        {
            cout << "Invalid row or column index." << endl;
            cout << "Please enter the row and column of the tile that you want to move:" << endl;
            cin >> row >> column;
        }

        if (!CanCellMove(gameTable, row, column))
        {
            cout << "No tiles have been moved." << endl;
        }
        else
        {
            MoveCell(gameTable, row, column);
            cout << "Tile at (" << row << "," << column << ") has been moved." << endl;
        }
        PrintMatrix(gameTable);

        if (IsMatrixEmpty(gameTable))
        {
            cout << "The matrix is empty." << endl;
            gameOnProgress = false;
        }
        else if (!AreMovesPossible(gameTable))
        {
            cout << "No more moves are possible." << endl;
            gameOnProgress = false;
        }
    }
}
