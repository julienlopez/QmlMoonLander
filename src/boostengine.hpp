#pragma once

#include "iengine.hpp"

namespace bu = boost::units;
namespace si = bu::si;

class BoostEngine : public IEngine
{
public:
    explicit BoostEngine() = default;

    virtual ~BoostEngine() = default;

    virtual void reset(Length_t new_state) override;

    virtual Length_t update(const Time_t dt) override;

private:
    virtual Mass_t currentMass() const override;

    virtual Force_t currentThrust() const override;

    virtual Force_t gravity(const Length_t& height) const override;

    Length_t m_height;
    Momentum_t m_momentum;
};
