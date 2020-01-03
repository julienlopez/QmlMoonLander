#include "simulator.hpp"
#include "iengine.hpp"

#include "boostengine.hpp"
#include "basiceulerengine.hpp"

#include <QTimer>

#include <QDebug>

Simulator::Simulator(QObject* parent)
    : QObject(parent)
    , m_engine(std::make_unique<BasicEulerEngine>())
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
    m_engine->reset(m_starting_height * si::meters);
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
    const auto new_state = m_engine->update(time_step_ms * si::seconds);
    setHeight(new_state.value());
    qDebug() << m_height;
}
