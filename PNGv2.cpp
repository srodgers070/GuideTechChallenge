#include <vector>
#include <math.h>
#include <fstream>
#include <iterator>
#include <string>
#include <iostream>
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

struct Values{
    double theta_t=0;
    double phi=0;
    double alpha_t=0;
    double Rt=0; //initial distance from missile to target
    double Rm=0; // missile initial radius from origin shoudl be 0
    double alpha_m=0;
    double theta_m=0; //actually should be 0
};
struct Accels{
    double target=0;
    double missile=0;
};
struct Derivatives{
    double theta_t_dot=0;
    double phi_dot=0;
    double alpha_t_dot=0;
    double r_t_dot=0;
    double r_m_dot=0;
    double alpha_m_dot=0;
    double theta_m_dot=0;
};
// define the world state 
struct WorldState{
    Values values;
    Accels accels;
    Point missile_location;
    VelocityVector velocities;
    Point target_location;
};
Derivatives calculate_dddt(const WorldState & previous_state)
{
    double theta_t_dot=previous_state.accels.target/previous_state.velocities.target;

    double phi_dot = previous_state.velocities.target*sin(previous_state.values.alpha_t)/previous_state.values.Rt;

    double alpha_t_dot=theta_t_dot - phi_dot;

    double r_t_dot = previous_state.velocities.target*cos(previous_state.values.alpha_t);

    double r_m_dot= previous_state.velocities.missile*cos(previous_state.values.alpha_m);

    double alpha_m_dot = (1/(previous_state.values.Rt*r_m_dot))*(r_m_dot*previous_state.velocities.target*sin(previous_state.values.alpha_t)+ previous_state.values.Rm*r_t_dot*alpha_t_dot - r_t_dot*previous_state.velocities.missile*sin(previous_state.values.alpha_m));

    double theta_m_dot = alpha_m_dot + phi_dot;

    return Derivatives{
        theta_t_dot, //r_dot
        phi_dot,
        alpha_t_dot,
        r_t_dot,
        r_m_dot,
        alpha_m_dot,
        theta_m_dot 
    };
}
Point UpdateMisPos(const WorldState & previous_state)
{
    const double time_step=0.1; // s
    return Point{
        previous_state.missile_location.x+time_step*previous_state.velocities.missile*cos(previous_state.values.theta_m), // calculates new x position
        previous_state.missile_location.y+time_step*previous_state.velocities.missile*sin(previous_state.values.theta_m), // calculates new y position
    };
}
// Accels UpdateAccles(const WorldState & previous_state)
// {
//     return
// }
Point UpdateTargPos(const WorldState & previous_state)
{
    const double time_step=0.1; // s
    return Point{
        previous_state.target_location.x+time_step*previous_state.velocities.target*cos(previous_state.values.theta_t), // calculates new x position
        previous_state.target_location.y+time_step*previous_state.velocities.target*sin(previous_state.values.theta_t), // calculates new y position
    };
}

Values Update_Values(const Values & prev_values, const Derivatives & drvs)
{
    const double time_step=0.1; // s


    double new_theta_t= prev_values.theta_t+ time_step*drvs.theta_t_dot;

    double new_phi=prev_values.phi + time_step*drvs.phi_dot;

    double new_alpha_t = prev_values.alpha_t+ time_step*drvs.alpha_t_dot;

    double new_r_t= prev_values.Rt+ time_step*drvs.r_t_dot;

    double new_r_m=prev_values.Rm+time_step*drvs.r_m_dot;

    double new_alpha_m=prev_values.alpha_m+time_step*drvs.alpha_m_dot;

    double new_theta_m=prev_values.theta_m+time_step*drvs.theta_m_dot;

    return Values{
        new_theta_t,
        new_phi,
        new_alpha_t,
        new_r_t,
        new_r_m,
        new_alpha_m,
        new_theta_m
    };
};
WorldState EulerStep(const WorldState & previous_state)
{
    const double time_step=0.1; // s
    WorldState out=previous_state;
    Derivatives derivs=calculate_dddt(previous_state);// calculate first order time derivatives
    out.accels.missile=previous_state.velocities.missile*derivs.theta_m_dot; //update accerations
    out.accels.target=previous_state.velocities.target*derivs.theta_t_dot;
    out.values=Update_Values(previous_state.values, derivs); // update our values
    out.missile_location=UpdateMisPos(previous_state); // update missile pos
    out.target_location=UpdateTargPos(previous_state); // update target pos
    return out;
}

int main()
{
    vector<WorldState> worldstates;
    const WorldState initial_state{
        Values {.3067, // theta_t
                1.9124,//phi
                -1.5882, //alpha_t
                359,//Rt,
                0,//Rm default should be 0 duh
                0,//alpha_m set to 0 if you want theta_m to be directly to target
                1.9124},//theta_m
        Accels{0,0},
        Point{0,0},
        VelocityVector{373, 221}, // initial velocity {missile, target} m/s
        Point{initial_state.values.Rt*cos(initial_state.values.phi), initial_state.values.Rt*sin(initial_state.values.phi)}// initial target loc {X, Y}
    };
    worldstates.push_back(initial_state);
    //lets change the for loop to a while loop
    const WorldState & prev_state = worldstates.back();
    int i=0;
    do{
        const WorldState & prev_state = worldstates.back();
        const WorldState & new_state = EulerStep(prev_state);
        worldstates.push_back(new_state);
        i+=1;
    }
    while(i < 30);
  
    
    ofstream OutFile;
    OutFile.open("NMT-PNG.csv");
    int j=0;
    OutFile << "Author: Spencer Rodgers, Date 1/5/2021\n";
    // OutFile<< "Initial Conditions:" << initial_state.values << '';
    OutFile << "Missile X, Missile Y, Target X, Target Y, Phi, Alpha_M, Time \n";
    for (vector<WorldState> :: iterator it = worldstates.begin(); it!=worldstates.end(); it++)
    {

        WorldState value=worldstates.at(j);
        double timeis=j*0.01; //s
        OutFile << value.missile_location.x << ',' << value.missile_location.y << ',' << value.target_location.x << ',' << value.target_location.y << ',' << value.values.phi << ',' << value.values.alpha_m << ',' << timeis << '\n';
        j+=1;

    };
    OutFile.close();
    cout << "Task completed";
    cout<< endl;
    return 0;

}