#include "boostengine.hpp"

#include <boost/numeric/odeint.hpp>

void BoostEngine::reset(Length_t new_state)
{
    m_height = new_state;
    m_momentum = 0 * si::kilograms * si::meters / si::seconds;
}

BoostEngine::Length_t BoostEngine::update(const Time_t dt)
{
    using namespace boost::numeric::odeint;
    using stepper_type
        = symplectic_rkn_sb3a_mclachlan<Length_t, Momentum_t, double, Speed_t, Force_t, Time_t, vector_space_algebra>;

    // integrate_const(
    //         stepper_type() ,
    //         std::make_pair(
    //                 [this](const Momentum_t& p, Speed_t& dqdt){ dqdt =  p / currentMass(); },
    //                 [this](const Length_t& q, Force_t& dpdt) { dpdt = currentThrust() - gravity(q); }),
    //         std::make_pair(boost::ref(m_height), boost::ref(m_momentum)),
    //         0.0 * si::seconds , dt , dt);

    integrate_n_steps(stepper_type(),
                      std::make_pair([this](const Momentum_t& p, Speed_t& dqdt) { dqdt = p / currentMass(); },
                                     [this](const Length_t& q, Force_t& dpdt) { dpdt = currentThrust() - gravity(q); }),
                      std::make_pair(boost::ref(m_height), boost::ref(m_momentum)), 0.0 * si::seconds, dt, 1);

    return m_height;
}

BoostEngine::Mass_t BoostEngine::currentMass() const
{
    // TODO actual mass computation
    // const auto fuel_mass = total_mass - dry_mass;
    // return dry_mass + m_fuel * fuel_mass;
    return total_mass;
}

BoostEngine::Force_t BoostEngine::currentThrust() const
{
    return 0. * si::meter * si::kilogram / si::second / si::second;
}

BoostEngine::Force_t BoostEngine::gravity(const Length_t& height) const
{
    const auto gravitational_constant
        = 6.67430e-11 * si::meter * si::meter * si::meter / si::kilogram / si::second / si::second;
    const Mass_t moon_mass = 7.342e22 * si::kilograms;
    return gravitational_constant * currentMass() * moon_mass / (height * height);
}
