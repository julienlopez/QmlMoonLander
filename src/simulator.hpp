#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <QObject>

class Simulator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double height READ height NOTIFY heightChanged MEMBER m_height)
    Q_PROPERTY(double starting_height READ startingHeight NOTIFY startingHeightChanged)
    Q_PROPERTY(double fuel READ fuel NOTIFY fuelChanged MEMBER m_fuel)
    Q_PROPERTY(double throttle READ throttle WRITE setThrottle NOTIFY throttleChanged MEMBER m_throttle)

public:
    explicit Simulator(QObject* parent = nullptr);

    virtual ~Simulator() = default;

    double height() const;
    double startingHeight() const;
    double fuel() const;
    double throttle() const;

    void setThrottle(const double t);

signals:
    void heightChanged(double);
    void startingHeightChanged(double);
    void fuelChanged(double);
    void throttleChanged(double);

private:
    double m_height;
    double m_starting_height;
    double m_fuel;
    double m_throttle;

    void setHeight(const double h);
    void setFuel(const double f);
};

#endif // SIMULATOR_HPP
