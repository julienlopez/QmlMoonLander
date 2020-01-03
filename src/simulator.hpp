#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <QObject>

class IEngine;

class QTimer;

class Simulator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double starting_height READ startingHeight)
    Q_PROPERTY(double starting_fuel READ startingFuel)
    Q_PROPERTY(bool is_running READ isRunning NOTIFY isRunningChanged)

    Q_PROPERTY(double height READ height NOTIFY heightChanged MEMBER m_height)
    Q_PROPERTY(double speed READ speed NOTIFY speedChanged MEMBER m_speed)
    Q_PROPERTY(double fuel READ fuel NOTIFY fuelChanged MEMBER m_fuel)
    Q_PROPERTY(double throttle READ throttle WRITE setThrottle NOTIFY throttleChanged MEMBER m_throttle)

public:
    explicit Simulator(QObject* parent = nullptr);

    virtual ~Simulator();

    double startingHeight() const;
    double startingFuel() const;

    bool isRunning() const;

    double height() const;
    double speed() const;
    double fuel() const;
    double throttle() const;

    void setThrottle(const double t);

signals:
    void isRunningChanged(bool);
    void heightChanged(double);
    void speedChanged(double);
    void fuelChanged(double);
    void throttleChanged(double);

public slots:
    void start();

private:
    std::unique_ptr<IEngine> m_engine;
    const double m_starting_height;
    const double m_starting_fuel;

    double m_height;
    double m_speed;
    double m_fuel;
    double m_throttle;

    QTimer* m_update_timer;

    const double time_step_ms = 100;

    void setHeight(double h);

    void setSpeed(double s);

    void setFuel(const double f);

    void updateState();
};

#endif // SIMULATOR_HPP
