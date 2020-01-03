#pragma once

#include "iengine.hpp"

class BoostEngine : public IEngine
{
public:
    explicit BoostEngine() = default;

    virtual ~BoostEngine() = default;

    virtual void reset(Length_t new_state) override;

    virtual std::pair<Length_t, Speed_t> update(const Time_t dt) override;

private:
    Length_t m_height;
    Momentum_t m_momentum;
};
