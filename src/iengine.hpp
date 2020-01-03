#pragma once

#include <boost/units/quantity.hpp>
#include <boost/units/unit.hpp>

#include <boost/units/base_units/si/kilogram.hpp>
#include <boost/units/base_units/si/meter.hpp>
#include <boost/units/base_units/si/second.hpp>
#include <boost/units/physical_dimensions/length.hpp>
#include <boost/units/physical_dimensions/mass.hpp>

#include <boost/units/systems/si/acceleration.hpp>
#include <boost/units/systems/si/force.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/mass.hpp>
#include <boost/units/systems/si/momentum.hpp>
#include <boost/units/systems/si/time.hpp>
#include <boost/units/systems/si/velocity.hpp>

namespace bu = boost::units;
namespace si = bu::si;

class IEngine
{
protected:
    explicit IEngine() = default;

public:
    virtual ~IEngine() = default;

    using Length_t = bu::quantity<si::length>;
    using Mass_t = bu::quantity<si::mass>;
    using Time_t = bu::quantity<si::time>;
    using Acceleration_t = bu::quantity<si::acceleration>;
    using Speed_t = bu::quantity<si::velocity>;
    using Momentum_t = bu::quantity<si::momentum>;
    using Force_t = bu::quantity<si::force>;

    virtual void reset(Length_t new_state) = 0;

    virtual Length_t update(const Time_t dt) = 0;

protected:
    Mass_t currentMass() const;

    Force_t currentThrust() const;

    Force_t gravity(const Length_t& height) const;

    Force_t totalForce(const Length_t& height) const;

    static const inline Mass_t dry_mass = 2792 * si::kilograms;
    static const inline Mass_t total_mass = 16437 * si::kilograms;
};