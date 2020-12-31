#include <vector>
#include <math.h>
#include <fstream>
#include <iterator>
#include <string>
using namespace std; // so you don't have to type "std::" before every vector

struct Point {
    double x = 0; // Sane defaults in case you forget to initialize your Point
    double y = 0;
    //generic Point structure

};
struct VelocityVector {
    double missile = 0; 
    double target = 0;
    //generic Velocity structure
};

struct Angles{
    double phi=0;
    double distance=0;
    double alpha_T=0;
    double theta_T=0;
    double alpha_M=0;
    double theta_M=0;
    double k=1;
};
struct Derivatives{
    double r_dot=0;
    double phi_dot=0;
    double alpha_M_dot=0;
    double theta_T_dot=0;
    double theta_M_dot=0;
};
// define the world state 
struct WorldState{
    Angles angles;
    Point missile_location;
    VelocityVector velocities;
    Point target_location;
};
Derivatives calculate_dddt(const WorldState & previous_state)
{
    double phi_dot=(-1*previous_state.velocities.target*cos(previous_state.angles.alpha_T) + previous_state.velocities.missile*cos(previous_state.angles.alpha_M))/previous_state.angles.distance;
    return Derivatives{
        previous_state.velocities.target*cos(previous_state.angles.alpha_T) - previous_state.velocities.missile*cos(previous_state.angles.alpha_M),
        phi_dot,
        -phi_dot*(previous_state.angles.k - 1),
        0.0,
        phi_dot*previous_state.angles.k,
    };
}
Point UpdateMisPos(const Point & previous_loc, const Angles prev_angles, const VelocityVector & velocity)
{
    const double time_step=0.1; // s
    return Point{
        previous_loc.x+velocity.missile*cos(prev_angles.theta_M)*time_step, // calculates new x position
        previous_loc.y+velocity.missile*sin(prev_angles.theta_M)*time_step, // calculates new y position
    };
}
Point UpdateTargPos(const Point & previous_loc, const Angles prev_angles, const VelocityVector & velocity)
{
    const double time_step=0.1; // s
    return Point{
        previous_loc.x+velocity.target*cos(prev_angles.theta_M)*time_step, // calculates new x position
        previous_loc.y+velocity.target*sin(prev_angles.theta_M)*time_step, // calculates new y position
    };
}
Angles Update_Angles(const Angles & prev_angles, const VelocityVector & velocity, const Derivatives & drvs)
{
    const double time_step=0.1; // s
    return Angles{
        prev_angles.phi+drvs.phi_dot*time_step,
        prev_angles.distance+drvs.r_dot*time_step,
        prev_angles.alpha_T,
        prev_angles.theta_T+drvs.theta_T_dot*time_step,
        prev_angles.alpha_M+drvs.alpha_M_dot*time_step,
        prev_angles.theta_M+drvs.theta_M_dot*time_step,
        prev_angles.k
    };
};
WorldState EulerStep(const WorldState & previous_state)
{
    const double time_step=0.1; // s
    WorldState out = previous_state;
    out.missile_location=UpdateMisPos(previous_state.missile_location, previous_state.angles, previous_state.velocities);
    out.target_location=UpdateTargPos(previous_state.target_location, previous_state.angles,previous_state.velocities);
    Derivatives derivs=calculate_dddt(previous_state);
    out.angles=Update_Angles(previous_state.angles, previous_state.velocities, derivs);
}
int main()
{
    const int iterations = 1000; // s
    vector<WorldState> worldstates;
    worldstates.reserve(iterations+1);
    const WorldState initial_state{
        Angles {1.107,2000,1.107,0.0,1.107,0,1}, // {Phi, distance, a_T, o_T, a_M, a_T, k}
        Point{0,0},
        VelocityVector{2.0*343, 0.9*343}, // initial velocity {missile, target} m/s
        Point{1000, 2000}             // initial target loc {X, Y}
    };
    worldstates.push_back(initial_state);
    for(int iter = 0; iter < iterations; ++iter)
    {
        const WorldState & prev_state = worldstates.back();
        const WorldState & new_state = EulerStep(prev_state);
        worldstates.push_back(new_state);
    }
    // we have now initialized our initial conditions
    ofstream output_file("./Testing.txt");
    ostream_iterator<string> output_iterator(output_file, "\n");
    copy(worldstates.begin(), worldstates.end(), output_iterator);
    //TODO: outputvalues to a csv file, import into python and plot
}