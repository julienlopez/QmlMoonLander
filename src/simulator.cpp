#include "simulator.hpp"

Simulator::Simulator(QObject* parent)
    : QObject(parent)
    , m_starting_height(1000)
    , m_starting_fuel(2000)
{
    m_throttle = 0;
    m_fuel = 1;
    m_height = 0.;
}

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
    return m_height > 0.;
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
