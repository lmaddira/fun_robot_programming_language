#include <chrono> // to check time taken for a procedure
#include "environment.h"
using namespace std;


int main()
{
    int r,c,p,q;
    cin>>r>>c>>p>>q; // reading rows, cols, no of programs and queries
    assert(r >= 1 && r <= 40 && c >= 1 && c <= 40 && p >=0 && p <= 26 && q >= 1 && q <= 10); //asserting their values

    Environment env(r,c); // create env object
    env.read_grid(); // reading env
    // env.print_grid(); // printing env

    string s;
    getline(cin, s);// read blank line

    // read program definations
    while(p--)
    {
        getline(cin, s);
        env.add_procedure(s); // storing program commands
    }
    // using array to store information of x,y,h and procedure for each query
    int x[q], y[q];
    char h[q];
    string programs[q];

    // read commands
    for(int i=0;i<q;++i)
    {
        cin>>x[i]>>y[i]>>h[i]; // read x,y,h
        getline(cin, s);// read blank line check a better way of doing this
        getline(cin, programs[i]);// read program
    }
    /* for each query intitiate robot position for the task 
        execute the procedure and returns the final position of the robot after the procedure */

    for(int i=0;i<q;++i)
    {
        auto start = std::chrono::high_resolution_clock::now();
        env.initiate_robot(x[i],y[i],h[i]);
        int recursion_depth = 200000;
        string result = env.execute_procedure(recursion_depth,programs[i]);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 
        // cout<<"duration took "<<duration.count()*0.000001<<" seconds ";
        cout<<result<<endl;
    }
    // env.print_procedure_map();

    return 0;
}
