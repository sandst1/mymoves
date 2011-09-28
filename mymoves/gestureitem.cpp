#include "gestureitem.h"

GestureItem::GestureItem(const QString& id, const QString& image, QObject *parent)
    : ListItem(parent),
      m_id(id),
      m_image(image),
      m_reserved(false),
      m_app(),
      m_command()
{}

GestureItem::GestureItem(const GestureItem& item, QObject* parent)
    : ListItem(parent)
{
    m_id = item.m_id;
    m_image = item.m_image;
    m_reserved = item.m_reserved;
    m_app = item.m_app;
    m_command = item.m_command;
}

QVariant GestureItem::data(int role) const
{
    switch (role)
    {
        case ImageRole:
            return m_image;
        break;

        case ReservedRole:
            return m_reserved;
        break;

        case AppRole:
            return m_app;
        break;

        case CommandRole:
            return m_command;
        break;

        default:
            return QVariant();
        break;
    }
}

QHash<int, QByteArray> GestureItem::roleNames() const
{
    QHash<int, QByteArray> names;
    names[ImageRole] = "image";
    names[ReservedRole] = "reserved";
    names[AppRole] = "app";
    names[CommandRole] = "command";
    return names;
}

void GestureItem::setReserved(bool res)
{
    m_reserved = res;
}

void GestureItem::setApp(const QString& app)
{
    m_app = app;
}

void GestureItem::setCommand(const QString& cmd)
{
    m_command = cmd;
}

