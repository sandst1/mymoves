#include <QDebug>
#include <QStringList>
#include <QTextStream>
#include <QFile>

#include "constants.h"
#include "gestureitem.h"
#include "gesturelistmodel.h"

GestureListModel::GestureListModel(ListItem* prototype, QObject *parent)
    : ListModel(prototype, parent),
      m_selectedGests(NULL)
{
}


void GestureListModel::saveItem(int index, const QString& app, const QString& command)
{
    qDebug("GestureListModel::saveItem %d %s %s", index, app.toLatin1().data(), command.toLatin1().data());
    GestureItem* item = static_cast<GestureItem*>(m_list[index]);
    item->setReserved(true);
    item->setApp(app);
    item->setCommand(command);
    saveToDisk();
    updateSelectedGestures();
    qDebug("GestureListModel::saveItem done");
}

void GestureListModel::loadFromDisk()
{
    qDebug() << __PRETTY_FUNCTION__;
    QFile gfile(GESTURES_CONF_FILE);
    gfile.open(QIODevice::ReadOnly);
    QTextStream stream(&gfile);

    // Read the gesture file version
    QString version = stream.readLine();

    QString line = stream.readLine();
    do
    {
        QStringList data = line.split("###");
        QString id;
        QString app;
        QString command;
        bool reserved = false;
        qDebug("### Gesture ###");
        for (int i = 0; i < data.size(); i++)
        {
            qDebug("data %d %s", i, data.at(i).toLatin1().data());
        }

        id = data.at(0);
        app = data.at(1);
        command = data.at(2);
        if (app.size() > 0)
        {
            reserved = true;
        }
        QString image = QString(GESTURE_IMG_PATH) + id + GESTURE_IMG_EXT;
        qDebug("### Gesture END ###");

        GestureItem* item = new GestureItem(id, image, this);
        item->setApp(app);
        item->setCommand(command);
        item->setReserved(reserved);
        this->appendRow(item);

        line = stream.readLine();
    } while (!line.isEmpty());
    updateSelectedGestures();
    qDebug() << __PRETTY_FUNCTION__ << "end";
}

void GestureListModel::saveToDisk()
{
    qDebug() << __PRETTY_FUNCTION__;
    QFile gfile(GESTURES_CONF_FILE);
    gfile.open(QIODevice::WriteOnly);
    QTextStream stream(&gfile);

    // Insert version
    stream << "0" << endl;

    for (int i = 0; i < m_list.size(); i++)
    {
        GestureItem* item = static_cast<GestureItem*>(m_list[i]);
        stream << item->id() << "###" << item->app().trimmed() << "###" << item->command().trimmed() << endl;
    }

    gfile.close();
    qDebug() << __PRETTY_FUNCTION__ << "end";
}

void GestureListModel::setContextProperties(QDeclarativeContext* ctx)
{
    qDebug() << __PRETTY_FUNCTION__;
    ctx->setContextProperty("GestureListModel", this);
    ctx->setContextProperty("SelectedGesturesList", m_selectedGests);
    qDebug() << __PRETTY_FUNCTION__ << "end";
}

void GestureListModel::updateSelectedGestures()
{
    qDebug() << __PRETTY_FUNCTION__;
    if (m_selectedGests)
    {
        m_selectedGests->clear();
        for (int i = 0; i < m_list.size(); i++)
        {
            GestureItem* itemtocopy = static_cast<GestureItem*>(m_list[i]);
            GestureItem* item = new GestureItem(*itemtocopy, m_selectedGests);
            if (item->reserved())
            {
                m_selectedGests->appendRow(item);                
            }
        }
    }
    qDebug() << __PRETTY_FUNCTION__ << "end";
}

void GestureListModel::setSelectedList(GestureListModel* list)
{
    m_selectedGests = list;
}
