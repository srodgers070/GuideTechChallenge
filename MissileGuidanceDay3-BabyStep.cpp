//MissileGuidance in Cpp
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator

using namespace std;
//First thing I will do is aim for a target moving in a straight line at constant altitude
//I believe using float values is acceptable since I don't need this to be incredibly precise. 
float target_vel = 0.9*343; //vel in mach * m/s/mach -> vel in m/s
float missile_vel = 2.0*343; //vel in mach * m/s/mach -> vel in m/s
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



void velocity_verlet(vector TargetPositions, vector MissilePositions)
{
    //First assign values
    float TargetX=TargetPositions[i][0];
    float TargetY=TargetPositions[0][i];
    float MissileX=MissilePositions[i][0];
    float MissileY=MissilePositions[0][i];
    //Now that we have x and y we can calculate direction vector
    float xdif= TargetX-MissileX; // x value of vector
    float ydif= TargetY-MissileY;// y value of vector 
    float magnitude=sqrt(pow(xdif, 2) + pow(ydif, 2)); //magnitude of our vector

    //initialize direction vector and normalize it;
    vector<vector<float>> DirectionVec{
        {xdif/magnitude*missile_vel, ydif/magnitude*missile_vel}
    };
    
    //we now have a unit vector pointing in the direction of the target from the missile
    // so now we can make a step in that direction
    vector<vector<float>> NewPositionVec{
        {MissileX+DirectionVec[0][0]*delta_t, MissileY+DirectionVec[0][1]*delta_t}
    };
    float NewX= NewPositionVec[0][0];
    cout << "\nX coord is: " << NewX;
    float NewY=NewPositionVec[0][1];
    cout << "\nY Coord is:" << NewY;

}



int main()
{
    // just testing some stuff here, this is working correctly
    float distance = get_distance(target_x, target_y, missile_x, missile_y);
    cout << distance; 
    float phi=get_phi(target_x, target_y, missile_x, missile_y);
    cout << "\nPhi is: " << phi;
    cout << "\n";
    
    float initialxvel=missile_vel*cos(phi);
    float initialyvel=missile_vel*sin(phi);

    // Create 2D vectors for our Missile and Target Positions
    //These are written <X,Y>
    vector< vector< float> > MissilePositions{
        {0.0,0.0}
    };
    vector< vector< float> > TargetPositions{
        {1000,2000},
    };

    TargetPositions.push_back({1001,2001});
    TargetPositions.push_back({1002,2002});
    int i=1
    void velocity_verlet(TargetPositions, MissilePositions);
}
