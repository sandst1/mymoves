#include "appitem.h"

AppItem::AppItem(const QString& name, const QString& command, const QString& icon, QObject *parent) :
    ListItem(parent),
    m_name(name),
    m_command(command),
    m_icon(icon)
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

        case IconRole:
            return icon();
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
    names[IconRole] = "icon";
    return names;
}
