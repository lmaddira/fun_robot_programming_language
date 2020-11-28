#include "robot.h"

using namespace std;

Robot::Robot()  
{
    this->x = 0;
    this->y = 0;
    this->h = north;
}
void Robot::add_robot_location(int x,int y,char h)
{
    this->x = x-1;  //converting one indexing to zero indexing
    this->y = y-1;
    this->h = h;
}
string Robot::get_robot_location()
{
    return to_string(x+1)+" "+to_string(y+1)+" "+h; //converting zero indexing to one indexing 
}
char Robot::get_current_heading()
{
    return this->h; 
}
/* true if next state is blocked else false */
bool Robot::isbarrier(const vector<vector<char>> &grid) 
{
    switch(h) // as output of m is dependent on h heading
    {
        case north:// if north check if grid has barrier
            if(x-1>=0 && grid[x-1][y] !=blocked) return false; 
            break;
        case west:// if west
            if(y-1>= 0 && grid[x][y-1] !=blocked) return false; 
            break;
        case south:// if south
            if(x+1 < grid.size() && grid[x+1][y] !=blocked) return false; 
            break;
        case east:// if east
            if(y+1 < grid[0].size() && grid[x][y+1] !=blocked)return false; 
            break;
        default:
            std::cout<<"error in h heading \n";
            break;
    }
    return true;
} 


void Robot::robot_command_execution(char c, const vector<vector<char>> &grid) // expecting commands like m,l 
{
    switch(c)// switch cases for m and l
    {
        case 'm': //if move
            
            switch(h) // as output of m is dependent on h heading
            {
                case north:// if north check if grid has barrier
                    if(x-1>=0 && grid[x-1][y] !=blocked)--x; // if the grid cell is free and in bounds then move if not then do nothing
                    break;
                case west:// if west
                    if(y-1>= 0 && grid[x][y-1] !=blocked)--y; 
                    break;
                case south:// if south
                    if(x+1 <grid.size() && grid[x+1][y] !=blocked)++x; 
                    break;
                case east:// if east
                    if(y+1 < grid[0].size() && grid[x][y+1] !=blocked)++y; 
                    break;
                default:
                    std::cout<<"error in h heading in executing move \n";
                    // std::cout<<"x "<<x<<" y "<<y<<" heading "<<h<<" can't move "<<"\n";
                    break;
            }
            break;
        case 'l': // if turn left
            switch(h) // as output of l is dependent on h heading
            {
                case north:// if north
                    this->h = west; // result after turning left would be west
                    break;
                case west:// if west
                    this->h = south; // result after turning left would be south
                    break;
                case south:// if south
                    this->h = east; // result after turning left would be east
                    break;
                case east:// if east
                    this->h = north; // result after turning left would be north
                    break;
                default:
                    std::cout<<"error in h heading in executing left turn\n";
                    break;
            }
            break;
        default:
            std::cout<<"unidentified move commands check the input \n";
            // std::cout<<"x "<<x<<" y "<<y<<" heading "<<h<<" motion "<<c<<"\n";
            break;

    }
}

