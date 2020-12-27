//MissileGuidance in Cpp
#include <iostream>
#include <vector>
#include <math.h>


using namespace std;
//First thing I will do is aim for a target moving in a straight line at constant altitude
// double target_vel = 0.9*343; //vel in mach * m/s/mach -> vel in m/s
// double missile_vel = 2.0*343; //vel in mach * m/s/mach -> vel in m/s
int target_x = 1000 ;//m
int target_y= 2000 ;//m
int missile_x=0;//m
int missile_y=0;//m
//calculating the miss distance should be super easy so let me do that now
float get_distance(float TargX, float TargY, float MissileX, float MissileY)
{
   // tells us how long the MissilePos is
    return sqrt(pow(TargX - MissileX, 2) + pow(TargY - MissileY, 2));//pythag

}
float get_phi(float TargX, float TargY, float MissileX, float MissileY)
{
    return atan((TargY-MissileY)/(TargX-MissileX));
}


int main()
{

    distance=get_distance(target_x, target_y, missile_x, missile_y);
    cout<<distance;

    // make a vector for missile pos to append data to
    //vector format is: vector<DataType> nameofvector
    // vector <vector <float> > MissilePos
    // {
    //     {0.0,0.0}
    // }
    // vector <vector <float> > TargetPos
    // {
    //     {1000,2000}
    // }
    // // MissilePos.assign(1, vector <int> (2, 0)); //creates matrix with 1 row and 2 columns filled with 0s 
    // // MissilePos.push_back(3,4);
    // // MissilePos.push_back(3,4);
    // // MissilePos.push_back(3,4);
    // // MissilePos.push_back(3,4);
    // cout << "Vector: ";
    // for (unsigned int i=0; i< MissilePos.size(); i++){
    //     cout<<MissilePos[i] << " ";
    // }
    // cout << endl;
    // return 0;
}
