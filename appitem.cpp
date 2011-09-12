#include "appitem.h"

AppItem::AppItem(const QString& name, const QString& command, QObject *parent) :
    ListItem(parent),
    m_name(name),
    m_command(command)
{
}

QVariant AppItem::data(int role) const
{
    switch (role)
    {
        case NameRole:
            return name();
        break;

        case CommandRole:
            return command();
        break;

        default:
            return QVariant();
        break;
    }

}

QHash<int, QByteArray> AppItem::roleNames() const
{
    QHash<int, QByteArray> names;
    names[NameRole] = "name";
    names[CommandRole] = "command";
    return names;
}
