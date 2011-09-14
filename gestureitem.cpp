#include "gestureitem.h"

GestureItem::GestureItem(const QString& id, const QString& image, QObject *parent)
    : ListItem(parent),
      m_id(id),
      m_image(image),
      m_reserved(false),
      m_app(),
      m_command()
{}

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


