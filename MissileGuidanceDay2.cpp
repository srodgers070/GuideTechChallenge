//MissileGuidance in Cpp
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator

using namespace std;
//First thing I will do is aim for a target moving in a straight line at constant altitude
double target_vel = 0.9*343; //vel in mach * m/s/mach -> vel in m/s
double missile_vel = 2.0*343; //vel in mach * m/s/mach -> vel in m/s
int target_x = 1000 ;//m
int target_y= 2000 ;//m
int missile_x=0;//m
int missile_y=0;//m
float delta_t= 0.1; //seconds
//calculating the miss distance should be super easy so let me do that now
float get_distance(float TargX, float TargY, float MissileX, float MissileY)
{
   // tells us how long the MissilePos is
    return sqrt(pow(TargX - MissileX, 2) + pow(TargY - MissileY, 2));//pythag

}
float get_phi(float TargX, float TargY, float MissileX, float MissileY)
{
    return atan((TargY-MissileY)/(TargX-MissileX)); // returns phi in radians
}


int main()
{
    // just testing some stuff here, this is working correctly
    float distance = get_distance(target_x, target_y, missile_x, missile_y);
    cout << distance; 
    float phi=get_phi(target_x, target_y, missile_x, missile_y);
    cout << "\n Phi is: " << phi;
    
    float initialxvel=missile_vel*cos(phi);
    float initialyvel=missile_vel*sin(phi);

    vector< vector< float> > MissilePositions{
        {0,0}
    };
    vector< vector< float> > TargetPositions{
        {1000,2000},
    };

    // std::copy(TargetPositions.begin(), TargetPositions.end(), std::ostream_iterator<char>(std::cout, " "));

    // return 0;

}
