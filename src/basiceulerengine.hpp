#pragma once

#include "iengine.hpp"

class BasicEulerEngine : public IEngine
{
public:
    explicit BasicEulerEngine() = default;

    virtual ~BasicEulerEngine() = default;

    virtual void reset(Length_t new_state) override;

    virtual std::pair<Length_t, Speed_t> update(const Time_t dt) override;

private:
    Length_t m_height;
    Speed_t m_speed;
};
