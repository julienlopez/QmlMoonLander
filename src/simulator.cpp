#include "simulator.hpp"

#include <boost/units/quantity.hpp>
#include <boost/units/unit.hpp>

#include <boost/units/physical_dimensions/length.hpp>
#include <boost/units/physical_dimensions/mass.hpp>
#include <boost/units/base_units/si/meter.hpp>
#include <boost/units/base_units/si/kilogram.hpp>
#include <boost/units/base_units/si/second.hpp>

#include <boost/units/systems/si/acceleration.hpp>
#include <boost/units/systems/si/force.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/mass.hpp>
#include <boost/units/systems/si/momentum.hpp>
#include <boost/units/systems/si/time.hpp>
#include <boost/units/systems/si/velocity.hpp>

#include <boost/numeric/odeint.hpp>

#include <QTimer>

#include <QDebug>

namespace Impl
{

namespace bu = boost::units;
namespace si = bu::si;

class Simulator
{
public:
    explicit Simulator() = default;
    ~Simulator() = default;

    using Length_t = bu::quantity<si::length>;
    using Mass_t = bu::quantity<si::mass>;
    using Time_t = bu::quantity<si::time>;
    using Acceleration_t = bu::quantity<si::acceleration>;
    using Speed_t = bu::quantity<si::velocity>;
    using Momentum_t = bu::quantity<si::momentum>;
    using Force_t  = bu::quantity<si::force>;

    void reset(Length_t new_state)
    {
        m_height = new_state;
        m_momentum = 0 * si::kilograms * si::meters / si::seconds;
    }

    Length_t update(const Time_t dt)
    {
        using namespace boost::numeric::odeint;
        using stepper_type = symplectic_rkn_sb3a_mclachlan<Length_t, Momentum_t, double, Speed_t, Force_t, Time_t, vector_space_algebra >;

        // integrate_const(
        //         stepper_type() ,
        //         std::make_pair(
        //                 [this](const Momentum_t& p, Speed_t& dqdt){ dqdt =  p / currentMass(); },
        //                 [this](const Length_t& q, Force_t& dpdt) { dpdt = currentThrust() - gravity(q); }),
        //         std::make_pair(boost::ref(m_height), boost::ref(m_momentum)),
        //         0.0 * si::seconds , dt , dt);

        integrate_n_steps(stepper_type(),
                          std::make_pair(
                                  [this](const Momentum_t& p, Speed_t& dqdt){ dqdt =  p / currentMass(); },
                                  [this](const Length_t& q, Force_t& dpdt) { dpdt = currentThrust() - gravity(q); }),
                          std::make_pair(boost::ref(m_height), boost::ref(m_momentum)),
                          0.0 * si::seconds , dt , 1);

        return m_height;
    }

    Mass_t currentMass() const
    {
        // TODO actual mass computation
        // const auto fuel_mass = total_mass - dry_mass;
        // return dry_mass + m_fuel * fuel_mass;
        return total_mass;
    }

    Force_t currentThrust() const
    {
        return 0. * si::meter * si::kilogram / si::second / si::second;
    }

    Force_t gravity(const Length_t& height) const
    {
        const auto gravitational_constant = 6.67430e-11 * si::meter *si::meter *si::meter  / si::kilogram / si::second / si::second;
        const Mass_t moon_mass = 7.342e22 * si::kilograms;
        return gravitational_constant * currentMass() * moon_mass / (height * height);
    }

private:
    static const inline Mass_t dry_mass = 2792 * si::kilograms;
    static const inline Mass_t total_mass = 16437  * si::kilograms;

    Length_t m_height;
    Momentum_t m_momentum;
};
}

Simulator::Simulator(QObject* parent)
    : QObject(parent)
    , m_pimpl(std::make_unique<Impl::Simulator>())
    , m_starting_height(10000)
    , m_starting_fuel(2000)
{
    m_throttle = 0;
    m_fuel = 1;
    m_height = 0.;

    m_update_timer = new QTimer(this);
    m_update_timer->setInterval(time_step_ms);
    connect(m_update_timer, &QTimer::timeout, this, &Simulator::updateState);
}

Simulator::~Simulator() = default;

double Simulator::startingHeight() const
{
    return m_starting_height;
}

double Simulator::startingFuel() const
{
    return m_starting_fuel;
}

bool Simulator::isRunning() const
{
    return m_height > 0. && m_update_timer->isActive();
}

double Simulator::height() const
{
    return m_height;
}

double Simulator::fuel() const
{
    return m_fuel;
}

double Simulator::throttle() const
{
    return m_throttle;
}

void Simulator::setThrottle(const double t)
{
    if(std::abs(t - m_throttle) < 1E-6)
    {
        m_throttle = t;
        emit throttleChanged(m_throttle);
    }
}

void Simulator::start()
{
    setHeight(m_starting_height);
    setFuel(m_starting_fuel);
    setThrottle(0);
    m_pimpl->reset(m_starting_height * Impl::si::meters);
    m_update_timer->start();
    emit isRunningChanged(true);
}

void Simulator::setHeight(const double h)
{
    if(std::abs(h - m_height) > 1E-6)
    {
        m_height = h;
        emit heightChanged(m_height);
    }
}

void Simulator::setFuel(const double f)
{
    if(std::abs(f - m_fuel) > 1E-6)
    {
        m_fuel = f;
        emit fuelChanged(m_fuel);
    }
}

void Simulator::updateState()
{
    qDebug() << "Simulator::updateState()";
    qDebug() << m_height;
    const auto new_state = m_pimpl->update(time_step_ms * Impl::si::seconds);
    setHeight(new_state.value());
    qDebug() << m_height;
}
