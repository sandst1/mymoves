#ifndef APPITEM_H
#define APPITEM_H

#include <QByteArray>
#include <QHash>
#include <QObject>
#include <QString>
#include <QVariant>

//#include "app.h"

class AppItem : public QObject //: public ListItem
{
    Q_OBJECT
public:
    enum Roles {
        NameRole = Qt::UserRole+1
        ,CommandRole
        //,IconRole
    };

    AppItem(QObject* parent = 0): QObject(parent) {}
    explicit AppItem(const QString& name, const QString& command, QObject *parent = 0);
    QVariant data(int role) const;
    QHash<int, QByteArray> roleNames() const;

    inline QString id() const { return m_name; }

    inline QString name() const { return m_name; }
    inline QString command() const { return m_command; }
signals:
    void dataChanged();
public slots:

private:
    QString m_name;
    QString m_command;
};

#endif // APPITEM_H
