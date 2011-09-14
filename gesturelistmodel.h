#ifndef GESTURELISTMODEL_H
#define GESTURELISTMODEL_H

#include "listmodel.h"

class GestureItem;
class GestureListModel : public ListModel
{
    Q_OBJECT
public:
    explicit GestureListModel(ListItem* prototype, QObject *parent = 0)
        : ListModel(prototype, parent)
    {}

    Q_INVOKABLE void saveItem(int index, const QString& app, const QString& command);

    void loadFromDisk();
    void saveToDisk();
signals:

public slots:

private:

};

#endif // GESTURELISTMODEL_H
