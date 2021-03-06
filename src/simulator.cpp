#include "simulator.hpp"
#include "iengine.hpp"

#include "basiceulerengine.hpp"
#include "boostengine.hpp"

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
    m_speed = 0.;

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

double Simulator::speed() const
{
    return m_speed;
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
    if(std::abs(t - m_throttle) > 1E-6)
    {
        m_throttle = t;
        m_engine->setThrottle(m_throttle);
        emit throttleChanged(m_throttle);
    }
}

void Simulator::start()
{
    setHeight(m_starting_height);
    setFuel(m_starting_fuel);
    setThrottle(0.);
    setSpeed(0.);
    m_engine->reset(m_starting_height * si::meters);
    m_update_timer->start();
    emit isRunningChanged(true);
}

void Simulator::setHeight(double h)
{
    if(std::abs(h - m_height) > 1E-6)
    {
        if(h < 0)
        {
            h = 0;
            m_update_timer->stop();
        }
        m_height = h;
        emit heightChanged(m_height);
    }
}

void Simulator::setSpeed(double s)
{
    m_speed = s;
    emit speedChanged(m_speed);
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
    const auto[height, speed] = m_engine->update(time_step_ms / 1000 * si::seconds);
    setHeight(height.value());
    setSpeed(speed.value());
    qDebug() << m_height;
    qDebug() << m_speed;
}
