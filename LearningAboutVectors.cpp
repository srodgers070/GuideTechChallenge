#include <iostream>
#include <vector>
using namespace std;
 
int main()
{
    /*
    Below we initialize a 2D vector 
    named "vect" on line 12 and then
    we declare the values on 
    line 14, 15 and 16 respectively.
    */
     
    vector<vector<int>> vect
    {
        {1, 2},
        {4, 5},
        {7, 8}
    };
     
    /*
    Now we print the values that 
    we just declared on lines
    14, 15 and 16 using a simple 
    nested for loop.
    */
     
    for (int i = 0; i < vect.size(); i++)
    {
        for (int j = 0; j < vect[i].size(); j++)
        {
            cout << vect[i][j] << " ";
            // cout <<  <<" ";
            // cout << vect.front() << "Vector";
        } 
        cout << endl;
    }
    // cout << "\nVector value at front is" << vect.front()
    // for (int i = 0; i < vect.size(); i++)
    // {
    //     cout << "Vector value at i is" << vect.at(i);
    //     cout << endl;
    // }

    return 0;
}
