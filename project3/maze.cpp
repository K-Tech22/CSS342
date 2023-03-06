//
// Created by Yusuf Pisan on 4/18/18.
//

#include "maze.h"
#include <algorithm>
#include <cassert>
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// print maze object
ostream &operator<<(ostream &out, const Maze &maze)
{
    for (int row = 0; row < maze.height; ++row)
    {
        for (int col = 0; col < maze.width; ++col)
        {
            out << maze.field[row][col];
        }
        out << endl;
    }
    out << endl;
    return out;
}

// default constructor
Maze::Maze() = default;

// Load maze file from current directory
bool Maze::load(const string &fileName)
{

    ifstream inFile;
    inFile.open(fileName);
    if (!inFile.is_open())
    {
        cerr << "Unable to open file: " << fileName << endl;
        // next line is just to satisfy clang-tidy
        // otherwise it complains saying function can be const
        width = height = 0;
        return false;
    }
    inFile >> width >> height;
    inFile >> exitRow >> exitColumn;
    inFile >> startRow >> startColumn;

    // ignore leftover charcaters up to newline

    inFile.ignore(INT_MAX, '\n');
    string line;
    for (int row = 0; row < height; ++row)
    {
        getline(inFile, line);
        field.push_back(line);
    }
    return true;
}

// Moves back one coordinate and checks for a different route in tryDirections.
// Returns true if backtracked successfully
bool Maze::backtracking(int &row, int &col)
{
    if (row == startRow && col == startColumn)
    {
        markAsVisited(row, col);
        return false;
    }
    if (path.back() == 'E')
    {
        col -= 1;
        path.pop_back();
        return true;
    }
    if (path.back() == 'W')
    {
        col += 1;
        path.pop_back();
        return true;
    }
    if (path.back() == 'N')
    {
        row += 1;
        path.pop_back();
        return true;
    }
    if (path.back() == 'S')
    {
        row -= 1;
        path.pop_back();
        return true;
    }
    return false;
}

// Checks all the possible routes from a point and moves in a direction if its safe
// Otherwise calls the backtracking function
// Returns true if the maze can be solved
bool Maze::tryDirections(int &row, int &col)
{
    bool success = false;
    if (atExit(row, col))
    {
        markAsPath(row, col);
        return true;
    }
    if (isInside(row, col))
    {
        if (isInside(row, col + 1) && isClear(row, col + 1))
        {
            path += 'E';
            markAsPath(row, col);
            col += 1;
            success = tryDirections(row, col);
        }
        else if (isInside(row - 1, col) && isClear(row - 1, col))
        {
            path += 'N';
            markAsPath(row, col);
            row -= 1;
            success = tryDirections(row, col);
        }
        else if (isInside(row, col - 1) && isClear(row, col - 1))
        {
            path += 'W';
            markAsPath(row, col);
            col -= 1;
            success = tryDirections(row, col);
        }
        else if (isInside(row + 1, col) && isClear(row + 1, col))
        {
            path += 'S';
            markAsPath(row, col);
            row += 1;
            success = tryDirections(row, col);
        }
        else
        {
            markAsVisited(row, col);
            if (!backtracking(row, col))
            {
                return false;
            }
            success = tryDirections(row, col);
        }
    }
    return success;
}

bool Maze::solve()
{

    int initialRow = startRow;
    int initialCol = startColumn;
    return tryDirections(initialRow, initialCol);
}

// path to exit
string Maze::getPath() const { return path; }

// true if row, column is the exit
bool Maze::atExit(int row, int column) const
{
    return row == exitRow && column == exitColumn;
}

// true if row, column is inside the maze
bool Maze::isInside(int row, int col) const
{
    return row >= 0 && col >= 0 && row < field.size() && col < field[row].size();
}

// true if row, column is clear to move
bool Maze::isClear(int row, int col) const
{
    assert(row >= 0 && col >= 0 && row < field.size() && col < field[row].size());
    return field[row][col] == CLEAR;
}

// mark location as part of the path to exit
void Maze::markAsPath(int row, int col)
{
    assert(row >= 0 && col >= 0 && row < field.size() && col < field[row].size());
    field[row][col] = PATH;
}

// mark location as visited, not part of the path to exit
void Maze::markAsVisited(int row, int col)
{
    assert(row >= 0 && col >= 0 && row < field.size() && col < field[row].size());
    field[row][col] = VISITED;
}
