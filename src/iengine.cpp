#include "iengine.hpp"

auto IEngine::currentMass() const -> Mass_t
{
    // TODO actual mass computation
    // const auto fuel_mass = total_mass - dry_mass;
    // return dry_mass + m_fuel * fuel_mass;
    return total_mass;
}

auto IEngine::currentThrust() const -> Force_t
{
    return 0. * si::meter * si::kilogram / si::second / si::second;
}

auto IEngine::gravity(const Length_t& height) const -> Force_t
{
    const auto gravitational_constant
        = 6.67430e-11 * si::meter * si::meter * si::meter / si::kilogram / si::second / si::second;
    const Mass_t moon_mass = 7.342e22 * si::kilograms;
    return gravitational_constant * currentMass() * moon_mass / (height * height);
}

auto IEngine::totalForce(const Length_t& height) const -> Force_t
{
    return currentThrust() - gravity(height);
}
