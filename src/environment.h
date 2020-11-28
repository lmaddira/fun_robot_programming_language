#include <map>       // need this for using maps
#include <iterator>  // need this for using maps
#include "robot.h"

using namespace std;


class Environment{
private:
    /* store grid */
    vector<vector<char>> grid; 
    /*robot object */
    Robot r; 
    /* stores all procedures to execute later */
    map< char, string > procedure;
    /* no of rows and columns in the grid */
    int rows; 
    int cols;
    /* maps "robot state + procedure" string(xyhProcedure) to out put of that string */
    map <string,string> procedure_map; 
public:
    /* constructor */
    Environment(int &rows, int &cols); 
    /* reads grid from console and stores it */
    void read_grid();
    /* assigns robot starting pose */
    void initiate_robot(int x,int y,char heading); 
    /* returns robot location as string "x y h" */
    string get_robot_location(); 
    /* add procedure definition to map of procedures */
    void add_procedure(string s); 
    /* takes string that start with '(' adds the if conditions ==>{condition 1, condition2} and advances pointer in the string to after if clause */
    void get_if_clause(string &s,vector<string> &conditions, int &i); 
    /* takes string that start with '(' adds the until condition and advances pointer in the string to after until clause */
    void get_until_clause(string &s, string &cond, int &i); 
    /* execute if clause takes string, pointer in the string that points to if clause and recursive depth check number */
    void execute_if_clause(int &n,string &s, int &i); 
    /* execute until clause takes string, pointer in the string that points to until clause and recursive depth check number */
    void execute_until_clause(int &n,string &s, int &i); 
    /* execute the procedure, Inputs n - checks recursion deption and s-procedure call and return the final location of the robot as a string x y h */
    string execute_procedure(int &n, string &s);
    /* visualise the grid */
    void print_grid(); 
    /* visualise the procedure definition input char c = procedure "X" */
    void print_procedure(char &c); 
    /* converts robot state and procedure at that state to string */
    string convert_to_string(string &procedure);
    /* Input s - robot location "x y h"from the map of memory of robot procedures if we get a output string then we want to reset robot to that resultant state */
    void reset_robot_from_string(string &s); 
    /* prints procedure map */
    void print_procedure_map(); 

};