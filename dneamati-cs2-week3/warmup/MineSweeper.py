# Daniel Neamati
# Bonus Problem - MineSweeper

import random

class MineSweeper:
    '''This class contains the grid and member functions of Minesweeper.'''
    def __init__(self, numRows, numCols, difficulty):
        self.numRows = numRows
        self.numCols = numCols
        self.grid = [['E' for i in range(numCols)] for j in range(numRows)]
        for i in range(difficulty):
            self.grid[random.randint(0, numRows - 1)]\
            [random.randint(0, numCols - 1)] = 'M'
    
    def gamePrint(self):
        '''Prints the board'''
        top = '     '
        for i in range(self.numCols):
            top += str(i)
            top += '    '
        print(top)
        for i in range(self.numRows):
            if i < 10:
                print(i, '', self.grid[i])
            else:
                print(i, self.grid[i])
    
    def checkDirection(self, direction, row, col):
        '''Returns the value at the cell North (N), South (S), East (E), or
        West (W) (Or in between the cardinal directions) of a cell.
        If input is invalid, it returns dummy value (' ', -1, -1).'''
        assert(direction in ['N', 'NE', 'E', 'SE', 'S', 'SW', 'W', 'NW'])
        if direction == 'N':
            if row <= 0:
                return (' ', -1, -1)
            return (self.grid[row - 1][col], row - 1, col)
        
        elif direction == 'NE':
            if row <= 0 or col >= self.numCols - 1:
                return (' ', -1, -1)
            return (self.grid[row - 1][col + 1], row - 1, col + 1)
        
        elif direction == 'E':
            if col >= self.numCols - 1:
                return (' ', -1, -1)
            return (self.grid[row][col + 1], row, col + 1)
        
        elif direction == 'SE':
            if col >= self.numCols - 1 or row >= self.numRows - 1:
                return (' ', -1, -1)
            return (self.grid[row + 1][col + 1], row + 1, col + 1)
        
        elif direction == 'S':
            if row >= self.numRows - 1:
                return (' ', -1, -1)
            return (self.grid[row + 1][col], row + 1, col)
        
        elif direction == 'SW':
            if row >= self.numRows - 1 or col <= 0:
                return (' ', -1, -1)
            return (self.grid[row + 1][col - 1], row + 1, col - 1)
        
        elif direction == 'W':
            if col <= 0:
                return (' ', -1, -1)
            return (self.grid[row][col - 1], row, col - 1)
        
        elif direction == 'NW':
            if col <= 0 or row <= 0:
                return (' ', -1, -1)
            return (self.grid[row - 1][col - 1], row - 1, col - 1)
    
    def numAdjacentMines(self, row, col):
        '''Returns the number of mines adjacent to a given location.'''
        numAdj = 0
        for direction in ['N', 'NE', 'E', 'SE', 'S', 'SW', 'W', 'NW']:
            if self.checkDirection(direction, row, col)[0] == 'M':
                numAdj += 1
            #elif self.checkDirection(direction, row, col)[0] == ' ':
                #print("Hit the Border", direction)
        return numAdj
    
    def clear(self, row, col):
        '''Clears out empty squares at a location or shows mine is hit'''
        if self.grid[row][col] == 'M':
            self.grid[row][col] = 'X'
        
        elif self.grid[row][col] == 'E':
            numAdj = self.numAdjacentMines(row, col)
            if (numAdj > 0):
                self.grid[row][col] = str(numAdj)
            else:
                self.grid[row][col] = 'B'
            
            for direction in ['N', 'NE', 'E', 'SE', 'S', 'SW', 'W', 'NW']:
                # Check if we can clear out an adjacent cell
                dirNext = self.checkDirection(direction, row, col)
                nextAdj = self.numAdjacentMines(dirNext[1], dirNext[2])
                
                # If the adjacent cell is empty and blank, we can clear it
                if dirNext[0] == 'E' and nextAdj == 0:
                    self.clear(dirNext[1], dirNext[2])
                
                # If the adjacent cell is empty and next to mine, update its
                # cell
                elif dirNext[0] == 'E' and nextAdj > 0:
                    self.grid[dirNext[1]][dirNext[2]] = str(nextAdj)
            
    
    def gameEnd(self):
        '''Returns 0 if game is active.
        Returns 1 if game is won.
        Returns 2 if game is lost.'''
        end = 1
        for row in range(self.numRows):
            for col in range(self.numCols):
                if self.grid[row][col] == 'X':
                    # Player has hit a mine
                    return 2
                elif self.grid[row][col] == 'E':
                    # There is an unrevealed empty cell
                    end = 0
        # Otherwise all non-mine cells are cleared
        return end






def minesweeper():
    ''' This function runs the minesweeper game and player interaction. '''
    print()
    print("Difficulty: 1 - 5 is easy, 6 - 10 is medium,")
    print("increment up for harder.")
    difficulty = int(input("Enter difficulty: "))
    rows = random.randint(difficulty, 2 * difficulty)
    cols = random.randint(difficulty, 2 * difficulty)
    
    sweeper = MineSweeper(rows, cols, difficulty)
    
    print("Type moves in format: [row, column]")
    while sweeper.gameEnd() == 0: # Game is active
        sweeper.gamePrint()
        move = input("Enter Move: ")
        if move == 'q':
            break
        try:
            (row, col) = move.split(',')
            row = int(row[1:len(row)])
            col = int(col[:len(col) - 1])
            sweeper.clear(row, col)
        except ValueError:
            print("Invalid Input, try again.")
            
    if sweeper.gameEnd() == 1: # Game is won
        sweeper.gamePrint()
        print()
        print("CONGRATULATIONS!!!")
    elif sweeper.gameEnd() == 2: # Game is lost
        sweeper.gamePrint()
        print()
        print("MINE HIT! GAME LOST!")


minesweeper()