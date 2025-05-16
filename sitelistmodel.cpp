#include "sitelistmodel.h"

SiteListModel::SiteListModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_headers << tr("id")
    << tr("siteName");
}

QVariant SiteListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ((role == Qt::DisplayRole) && (orientation == Qt::Horizontal)) {
        return m_headers.at(section);
    }
    return QVariant();
}

int SiteListModel::rowCount(const QModelIndex &parent) const
{
    return m_sites.count();
}

int SiteListModel::columnCount(const QModelIndex &parent) const
{
    return m_headers.count();
}

QVariant SiteListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(index.column() == 0 && role == Qt::DisplayRole)
        return m_sites.at(index.row()).id;
    if(index.column() == 1 && role == Qt::DisplayRole)
        return m_sites.at(index.row()).siteName;

    return QVariant();
}

void SiteListModel::addrow(QJsonObject site)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    Site s;
    s.id = site["id"].toString();
    s.siteName = site["siteName"].toString();
    m_sites.append(s);
    endInsertRows();
}

void SiteListModel::clear()
{
    beginResetModel();
    m_sites.clear();
    endResetModel();
}
