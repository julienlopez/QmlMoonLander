#include "basiceulerengine.hpp"

void BasicEulerEngine::reset(Length_t new_state)
{
    m_height = new_state;
    m_speed = 0 * si::meters / si::seconds;
}

auto BasicEulerEngine::update(const Time_t dt) -> std::pair<Length_t, Speed_t>
{
    m_speed += dt * (totalForce(m_height) / currentMass());
    m_height += dt * m_speed;
    return {m_height, m_speed};
}
