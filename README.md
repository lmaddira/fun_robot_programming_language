## Mujin coading Interview

# Improvements in the code as discussed yesterday
1. I did review the libraries and made sure to add limited libraries. Made sure that I include the libraries only once.
2. Used Memozition for identifying previously executed task and used that information to run the program faster
3. Used recursion depth to detect infinity. 
    * we have r = 40, c= 40 and h = 4 so total states availible <= 6400
    * p<= 26 and can have <=100 length so <=2600
    * On multiplying both of them if a robot revisits a state more than 2*10^7 times then call it as infinity
4. Use 1d vector for grid instead of 2d vector
5. Made instance of grid availible in robot and also cahnged the code that seemed to be repeating in both Robot::isbarrier() and Robot::robot_command_execution()( previously refered as Robot::move())
6. Used better names for directions in enum as north,south,east, west instead of n,s,e,w
7. Defined constant for barrier and used that over the symbol '#' so that the symbol is changed easily later
8. Defined name for barrier rather than using 'b'
9. structured code in a better way
10. Now code can detect infinities based on the logic in #3

# Things to improve
1. As there are 2 kinds of infinities, one due to robot moving in grid infinitly and unable to get out side of the loop or finish the given program, and the second one recursion by construction example: A = AAA is a recursion. Current program can detect some basic such cases but can't completley detect all such cases. This leads to segmentation faults.
Example of cases currently code can detect: A = AAAA, A = mAlmA, A = ub(mAm), A = ib(mAm)(lmAl) etc
Cases that lead to segmentation fault: A = ib(mAm)() etc which are not a definite cases. These cases can be recursive or not recursive depending on the heading they start, if conditions. Current program fail to detect such cases and lead to Segmentation fault. 




# Instructions to compile and run
```
Go to PATH_to_mujin/
mkdir build
cd build
cmake ../src
make
./mujin
```
then enter the information of the test

# Example test input
```
4 8 4 6
.......#
..#....#
.###...#
.....###
G=ub(B)
B=ub(m)lib(l)(m)
H=ib()(mmHllmll)
I=III
1 1 w
G
1 1 e
G
2 2 n
G
4 1 s
ib(lib()(mmm))(mmmm)
1 1 e
H
2 2 s
I
```
#  output
```
1 1 w
inf
1 1 w
4 4 e
1 4 e
inf
```




