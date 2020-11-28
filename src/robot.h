#include <iostream>
#include <vector>
#include <assert.h>
#include <stack>

using namespace std;
#define blocked '#' 
#define barrier 'b'

/* enum of direction of the robot */
enum Heading{north = 'n' ,west = 'w',south = 's',east = 'e'};

/* robot class contains information of robot location  and basic commands 
    like move and checks */
class Robot{    
    int x;  
    int y; 
    char h; 
    vector<char> grid;
    int rows;
    int cols;
    /* x, y, h - stores current robots grid position x - row, y - col, h - heading*/
    /* grid, rows and cols are pointing to environment grid, rows and cols */
public:
    /* constructor */
    Robot(); 
    /* constructor with grid this grid points to the env grid*/
    void initiate_grid(vector<char> & grid, int &rows, int &cols);
    /* adds or changes the current robot location */
    void add_robot_location(int &x,int &y,char &h); 
    /* return robot location as a string "x y h"*/
    string get_robot_location();
    /* returns the current heading */
    char get_current_heading(); 
    /* returns true if the next state is blocked else false */
    bool isbarrier(); 
    /* executes basic robot commands like m and l only */  
    void robot_command_execution(char &c); 
};
