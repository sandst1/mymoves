#ifndef GESTURELISTMODEL_H
#define GESTURELISTMODEL_H

#include <QDeclarativeContext>
#include "listmodel.h"

class GestureItem;
class GestureListModel : public ListModel
{
    Q_OBJECT
public:
    explicit GestureListModel(ListItem* prototype, QObject *parent = 0);
    Q_INVOKABLE void saveItem(int index, const QString& app, const QString& command);
    void loadFromDisk();
    void saveToDisk();

    void setContextProperties(QDeclarativeContext* ctx);
signals:

public slots:

private:
    GestureListModel* m_selectedGests;

};

#endif // GESTURELISTMODEL_H
