/*
 * Author: Christophe Dumez <dchris@gmail.com>
 * License: Public domain (No attribution required)
 * Website: http://cdumez.blogspot.com/
 * Version: 1.0
 */

#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QVariant>
#include "appitem.h"

/*
class ListItem: public QObject {
  Q_OBJECT

public:
  ListItem(QObject* parent = 0) : QObject(parent) {}
  virtual ~ListItem() {}
  virtual QString id() const = 0;
  virtual QVariant data(int role) const = 0;
  virtual QHash<int, QByteArray> roleNames() const = 0;

signals:
  void dataChanged();
};
*/

class ListModel : public QAbstractListModel
{
  Q_OBJECT

public:
  explicit ListModel(AppItem* prototype, QObject* parent = 0);
  ~ListModel();
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  void appendRow(AppItem* item);
  void appendRows(const QList<AppItem*> &items);
  void insertRow(int row, AppItem* item);
  bool removeRow(int row, const QModelIndex &parent = QModelIndex());
  bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
  AppItem* takeRow(int row);
  AppItem* find(const QString &id) const;
  QModelIndex indexFromItem( const AppItem* item) const;
  void clear();

  static bool ItemLessThan(const AppItem& a, const AppItem& b);
  void sort();

private slots:
  void handleItemChange();

private:
  AppItem* m_prototype;
  QList<AppItem*> m_list;
};

#endif // LISTMODEL_H
