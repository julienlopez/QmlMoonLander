#include "boostengine.hpp"

#include <boost/numeric/odeint.hpp>

void BoostEngine::reset(Length_t new_state)
{
    m_height = new_state;
    m_momentum = 0 * si::kilograms * si::meters / si::seconds;
}

auto BoostEngine::update(const Time_t dt) -> std::pair<Length_t, Speed_t>
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
                                     [this](const Length_t& q, Force_t& dpdt) { dpdt = totalForce(q); }),
                      std::make_pair(boost::ref(m_height), boost::ref(m_momentum)), 0.0 * si::seconds, dt, 1);

    return {m_height, m_momentum / currentMass()};
}
