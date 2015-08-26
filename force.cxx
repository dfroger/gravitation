#include <cmath>
#include "gravitation/force.hxx"

namespace Gravitation
{

// Compute gravitional force as describe for example here:
// https://en.wikipedia.org/wiki/Newton's_law_of_universal_gravitation#Modern_form
double
compute_force(double mass1, double mass2, double radius)
{
    double gravitational_constant = 6.673e-11;
    return gravitational_constant * mass1 * mass2 / pow(radius,2);
}

}
