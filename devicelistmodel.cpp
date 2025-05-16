#include "devicelistmodel.h"

DeviceListModel::DeviceListModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant DeviceListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ((role == Qt::DisplayRole) && (orientation == Qt::Horizontal)) {
        return m_headers.at(section);
    }
    return QVariant();
}

bool DeviceListModel::setHeaderData(int section,
                                    Qt::Orientation orientation,
                                    const QVariant &value,
                                    int role)
{
    if (value != headerData(section, orientation, role)) {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            if (section >= m_headers.count())
                m_headers.resize(section + 1);
            //m_headers[section] = value.toString();
            m_headers.replace(section, value.toString());
        }
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}

int DeviceListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_devices.count();
}

int DeviceListModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_headers.count();
}

bool DeviceListModel::hasChildren(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return false;
}

bool DeviceListModel::canFetchMore(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return false;
}

void DeviceListModel::fetchMore(const QModelIndex &parent)
{
    // FIXME: Implement me!
}

QVariant DeviceListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    if(index.column() == 0 && role == Qt::DisplayRole)
        return m_devices.at(index.row()).id;
    if(index.column() == 1 && role == Qt::DisplayRole)
        return m_devices.at(index.row()).deviceName;

    return QVariant();
}

bool DeviceListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags DeviceListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

bool DeviceListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool DeviceListModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endInsertColumns();
    return true;
}

bool DeviceListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();
    return true;
}

bool DeviceListModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endRemoveColumns();
    return true;
}

void DeviceListModel::clear()
{
    beginResetModel();
    m_devices.clear();
    endResetModel();
}
