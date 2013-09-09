#include <iostream>

using namespace std;

enum Direction { UP, DOWN, RIGHT, LEFT };

void mazeTraversal( char [][ 12 ], const int, const int, int, int, int );
void printMaze( const char[][ 12 ], const int, const int );
bool validMove( const char [][ 12 ], int, int );
bool coordsAreEdge( int, int );

int main()
{
    char maze[ 12 ][ 12 ] =
    {   {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
        {'.', '.', '#', '.', '#', '.', '#', '#', '#', '#', '.', '#'},
        {'#', '#', '#', '.', '#', '.', '.', '.', '.', '#', '.', '#'},
        {'#', '.', '.', '.', '.', '#', '#', '#', '.', '#', '.', '.'},
        {'#', '#', '#', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
        {'#', '.', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
        {'#', '#', '.', '#', '.', '#', '.', '#', '.', '#', '.', '#'},
        {'#', '.', '.', '.', '.', '.', '.', '.', '.', '#', '.', '#'},
        {'#', '#', '#', '#', '#', '#', '.', '#', '#', '#', '.', '#'},
        {'#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'} };
    
    int xStart = 2; 
    int yStart = 0;
    int x = xStart; 
    int y = yStart;
    
    mazeTraversal( maze, xStart, yStart, x, y, LEFT );
}

void mazeTraversal( char maze[][ 12 ], const int xStart, const int yStart,
                   int xCoord, int yCoord, int direction )
{
    static bool flag = false;
    
    printMaze( maze, xCoord, yCoord );
    
    if ( coordsAreEdge( xCoord, yCoord ) && xCoord != xStart && 
        yCoord != yStart ) 
    {
        cout << "\nMaze successfully exited!\n";
        return; // to end All recursions
    } 
    else if ( xCoord == xStart && yCoord == yStart && flag ) 
    {
        cout << "\nArrived back to starting location.\n";
        return; // to end All recursions
    } 
    else 
    {
        flag = true;
         
        for ( int move = direction, count = 0; count < 4; count++, 
             move++, move %= 4 )
        {
            switch( move ) 
            {
                case UP: 
                    if ( validMove( maze, xCoord - 1, yCoord ) )  
                    {
                        mazeTraversal( 
                                      maze, xStart, yStart, xCoord - 1, yCoord, RIGHT ); // direction with respect to the enum above, go through all others before the opposite direction to prevent from going backwards
                        return; // to end All recursions
                    } 
                    break;
                case RIGHT: 
                    if ( validMove( maze, xCoord, yCoord + 1 ) ) 
                    {
                        mazeTraversal( 
                                      maze, xStart, yStart, xCoord, yCoord + 1, UP ); // direction with respect to the enum above, go through all others before the opposite direction to prevent from going backwards
                        return; // to end All recursions
                    } 
                    break;
                case DOWN: 
                    if ( validMove( maze, xCoord + 1, yCoord ) ) 
                    {
                        mazeTraversal( 
                                      maze, xStart, yStart, xCoord + 1, yCoord, DOWN ); // direction with respect to the enum above, go through all others before the opposite direction to prevent from going backwards
                        return; // to end All recursions
                    } 
                    break;
                case LEFT: 
                    if ( validMove( maze, xCoord, yCoord - 1 ) )  
                    {
                        mazeTraversal( 
                                      maze, xStart, yStart, xCoord, yCoord - 1, LEFT ); // direction with respect to the enum above, go through all others before the opposite direction to prevent from going backwards
                        return;
                    } 
                    break; // to end All recursions
            } 
        } 
    } 
} 


bool validMove( const char maze[][ 12 ], int r, int c )
{
    return ( r >= 0 && r <= 11 && c >= 0 && c <= 11 && maze[ r ][ c ] != '#' );
} 

// function to check coordinates
bool coordsAreEdge( int x, int y )
{
    if ( ( x == 0 || x == 11 ) && ( y >= 0 && y <= 11 ) )
        return true;
    else if ( ( y == 0 || y == 11 ) && ( x >= 0 && x <= 11 ) )
        return true;
    else
        return false;
} 


void printMaze( const char maze[][ 12 ], const int xCoord, const int yCoord )
{
    for ( int x = 0; x < 12; x++ ) 
    {
        for ( int y = 0; y < 12; y++ )
        {
            if ( x == xCoord && y == yCoord ) 
                cout << 'x' << ' ';
            else
                cout << maze[ x ][ y ] << ' ';
        }
        
        cout << '\n';
    } 
    
    cout << "\nHit return to see next move\n";
    cin.get();
} 


