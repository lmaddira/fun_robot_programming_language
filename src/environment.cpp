#include "environment.h"

using namespace std;

Environment::Environment(int &rows, int &cols){
        this->rows = rows;
        this->cols = cols;
    }

void Environment::read_grid(){ // intitate env with information of number of rows and columns in the grid
    grid.resize(rows*cols);
    for(int i = 0;i< rows*cols; ++i)
    {
        cin>>grid[i];
    }
    r.initiate_grid(grid,rows,cols); // initiate grid in robot class as well
}

void Environment::initiate_robot(int &x,int &y,char &heading){ // assigns robot pose
    r.add_robot_location(x,y,heading); 
}

string Environment::get_robot_location() // returns robot pose
{
    return r.get_robot_location();
}

void Environment::add_procedure(string s){
    assert(s[0] >='A' && s[0]<='Z' && s[1]=='=');// asserting that procedure is capital letter 
    procedure[s[0]] = s.substr(2,s.length()-2);
}

bool Environment::ifrecursion(char &c)
{
    string description = procedure[c];
    size_t found = description.find(c); // gives position of the 
    if(found == string::npos)return false; // if same character is not found
    // if found check if there is a if clause in the def
    size_t found2 = description.find('i');
    if(found2 == string::npos)return true; // if "if" clause is not found then true
    int i = 0;
    while (i<description.length())
    {
        while(i<description.length() && description[i] !='i' && description[i]!= c)++i;
        if(description[i] == c )return true;
        if(description[i] == 'i')
        {
            vector<string> conditions;
            i +=2;
            get_if_clause(description,conditions, i); // get if conditions 
            size_t f1 = conditions[0].find(c);
            size_t f2 = conditions[1].find(c);
            if(f1 != string::npos && f2 != string::npos)return true; // if both conditions has value "X" then return true;

        }
    }
    return false;
     
}

void Environment::get_if_clause(string &s,vector<string> &conditions, int &i)
{
    stack<char> p_check; //paranthesis check
    int rep = 2;
    string cond;
    while(rep--) // repeat 2 times as we need 2 conditions
    {
        assert(s[i] == '(');
        cond = ""; // not pushing the paranthesis '(' or ')'
        ++i;
        p_check.push(s[i]);
        while(!p_check.empty()) // if stack is empty  then the condition is complete
        {
            // balanced paranthesis method to get conditions
            if(s[i] =='(')p_check.push(s[i]);
            else if (s[i] ==')')p_check.pop();
            cond +=s[i];
            ++i;
        }
        cond.pop_back(); // poping back the last appended ')'
        conditions.push_back(cond);
    }             
    --i;
}
void Environment::get_until_clause(string &s, string &cond, int &i) // s should start with ( and can contain anything else
// return 1 strings ==>{condition 1} return the position of next index
{
    stack<char> p_check; //paranthesis check
    assert(s[i] == '(');
    i++;
    p_check.push(s[i]);
    while(!p_check.empty()) // if stack is empty  then the condition is complete
    {
        // balanced paranthesis method to get conditions
        if(s[i] =='(')p_check.push(s[i]);
        else if (s[i] ==')')p_check.pop();
        cond +=s[i];
        ++i;
    }
    cond.pop_back(); // poping back the last appended ')'
    --i;
}

void Environment::execute_if_clause(int &n,string &s, int &i) // this function is to execute the if clause
{
    if(n <= 0) return ;
    vector<string> conditions;
    char c = s[++i]; // condition for the if statement
    get_if_clause(s,conditions, ++i); // get if conditions 
    // check the case
    switch(c) // if barrier,n,e,s,w
    {
        case barrier:
            if(r.isbarrier()) execute_procedure(--n,conditions[0]);
            else execute_procedure(--n, conditions[1]);
            break;
        case north:
            if(r.get_current_heading() == 0) execute_procedure(--n, conditions[0]); //if true execute 1st condition else 2nd condition
            else execute_procedure(--n, conditions[1]);
            break;
        case east:
            if(r.get_current_heading() == 3) execute_procedure(--n, conditions[0]);
            else execute_procedure(--n, conditions[1]);
            break;
        case west:
            if(r.get_current_heading() == 1) execute_procedure(--n, conditions[0]);
            else execute_procedure(--n, conditions[1]);
            break;
        case south:
            if(r.get_current_heading() == 2) execute_procedure(--n, conditions[0]);
            else execute_procedure(--n, conditions[1]);
            break;
        default:
            std::cout<<"error in if clause\n";
            break;
    }

}

void Environment::execute_until_clause(int &n,string &s, int &i) // this function is to execute the until clause
{
    if(n <= 0) return ;
    string condition = "";
    char c = s[++i]; // condition for the if statement
    get_until_clause(s,condition, ++i); 
    switch(c) // if barrier,n,e,s,w
    {
        case barrier:
            while(n > 0 && !r.isbarrier()) execute_procedure(--n, condition); // until this condition is true execute the procedure 
            break;
        case north:
            while(n > 0 && r.get_current_heading() != north) execute_procedure(--n, condition);
            break;
        case east:
            while(n >0 && r.get_current_heading() != east) execute_procedure(--n, condition);
            break;
        case west:
            while(n > 0 && r.get_current_heading() != west) execute_procedure(--n, condition);
            break;
        case south:
            while(n > 0 && r.get_current_heading() != south) execute_procedure(--n, condition);
            break;
        default:
            std::cout<<"error in until clause \n";
            break;
    }
}


string Environment::execute_procedure(int &n, string &s) // execute the procedure and return the final location of the robot as a string x y h
{
    if(n <= 0 ) return "inf";
    // give robot specific commands like m and l only, process the rest of the conditions here
    string robot_state_nd_procedure =  convert_to_string(s);
    if(procedure_map.find(robot_state_nd_procedure) == procedure_map.end())
    {
        for(int i=0;i<s.length();++i)
        {
            if(procedure.find(s[i]) != procedure.end()) // if it's a defined procedure
            {
                if(ifrecursion(s[i])) return"inf";
                execute_procedure(--n,procedure[s[i]]);
            }
            else if(s[i]=='m'|| s[i]=='l')
            {
                --n;
                r.robot_command_execution(s[i]); // if m or l just execute the action
            }
            else if(s[i]=='i')
            {
                execute_if_clause(--n, s, i);
            }
            else if(s[i]=='u') // if until clause
            {
                execute_until_clause(--n, s, i); 
            }
            else
            {
                std::cout<<"unidentified execution asked "<<s[i]<<"\n";
            }    
        }
    }else
    {
        reset_robot_from_string(procedure_map[robot_state_nd_procedure]); // reset the robot to the output of this procedure
        return procedure_map[robot_state_nd_procedure]; // return robot state
    }
    if(n <=0 )return "inf";
    procedure_map[robot_state_nd_procedure] = get_robot_location();
    return get_robot_location();
}
string Environment::convert_to_string(string &procedure)
{
    return get_robot_location()+" "+procedure;
}
void Environment::reset_robot_from_string(string &s)
{
    // here we know the format would be "x y h" so formulating accordingly
    int x = atoi(&s[0]);
    int y = atoi(&s[2]);
    char h = s[4];
    initiate_robot(x,y,h); // taking care of indexing difference
}

void Environment::print_grid()
{
    for( int i= 0;i<rows;++i)
    {
        for(int j =0;j<cols;++j)
        {
            std::cout<<grid[(i*cols) + j];
            
        }
        std::cout<< "\n";
    }
}
void Environment::print_procedure(char &c)
{
    std::cout<<c<<" = "<<procedure[c]<<std::endl;
}

void Environment::print_procedure_map()
{
    for(auto i: procedure_map)
        std::cout<<i.first<<" results to "<<i.second<<"\n";
}
