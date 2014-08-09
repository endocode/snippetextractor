#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>

#include <QString>

class Exception : public std::runtime_error
{
public:
    explicit Exception(const QString& message);
    ~Exception() throw();
    QString message() const;

private:
    QString m_message;
};

#endif // EXCEPTION_H
