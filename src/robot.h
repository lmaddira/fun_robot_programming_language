#include <iostream>
#include <vector>
#include <assert.h>
#include <stack>

using namespace std;
#define blocked '#'

/* enum of direction of the robot */
enum Heading{north = 'n' ,west = 'w',south = 's',east = 'e'};

/* robot class contains information of robot location  and basic commands 
    like move and checks */
class Robot{    
    int x;  
    int y; 
    char h; 
    /* x, y, h - stores current robots grid position x - row, y - col, h - heading*/
    
public:
    /* constructor */
    Robot(); 
    /* adds or changes the current robot location */
    void add_robot_location(int x,int y,char h); 
    /* return robot location as a string "x y h"*/
    string get_robot_location();
    /* returns the current heading */
    char get_current_heading(); 
    /* returns true if the next state is blocked else false */
    bool isbarrier(const vector<vector<char>> &grid); 
    /* executes basic robot commands like m and l only */  
    void robot_command_execution(char c, const vector<vector<char>> &grid); 
};
