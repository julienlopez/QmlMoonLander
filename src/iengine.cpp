#include "iengine.hpp"

void IEngine::setThrottle(const double t)
{
    m_throttle = t;
    if(m_throttle > 1) m_throttle = 1.;
    if(m_throttle < 0) m_throttle = 0.;
}

auto IEngine::currentMass() const -> Mass_t
{
    // TODO actual mass computation
    // const auto fuel_mass = total_mass - dry_mass;
    // return dry_mass + m_fuel * fuel_mass;
    return total_mass;
}

auto IEngine::currentThrust() const -> Force_t
{
    const auto max_thrust = 45.04 * 1000 * si::newtons;
    return m_throttle * max_thrust;
}

auto IEngine::gravity(const Length_t& height) const -> Force_t
{
    const auto gravitational_constant
        = 6.67430e-11 * si::meter * si::meter * si::meter / si::kilogram / si::second / si::second;
    const Mass_t moon_mass = 7.342e22 * si::kilograms;
    const Length_t moon_radius = 1737.4 * 1000 * si::meter;
    const auto actual_height = height + moon_radius;
    return gravitational_constant * currentMass() * moon_mass / (actual_height * actual_height);
}

auto IEngine::totalForce(const Length_t& height) const -> Force_t
{
    return currentThrust() - gravity(height);
}
