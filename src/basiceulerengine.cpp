#include "basiceulerengine.hpp"

void BasicEulerEngine::reset(Length_t new_state)
{
    m_height = new_state;
    m_speed = 0 * si::meters / si::seconds;
}

BasicEulerEngine::Length_t BasicEulerEngine::update(const Time_t dt)
{
    m_speed += dt * (totalForce(m_height) / currentMass());
    m_height += dt * m_speed;
    return m_height;
}
