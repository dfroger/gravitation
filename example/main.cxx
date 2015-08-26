#include "gravitation/force.hxx"

#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    double sun_mass = 1.98855e+30;
    double earth_mass = 5.97219e+24;
    double sun_earth_distance = 149597870700;
    double force = Gravitation::compute_force(sun_mass, earth_mass,
                                              sun_earth_distance);
    cout << "Gravitional force between sun and earth is "
         << force << " N." << endl;
    return 0;
}
