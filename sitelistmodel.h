#ifndef SITELISTMODEL_H
#define SITELISTMODEL_H

#include <QAbstractTableModel>
#include <QJsonObject>

class Site
{
/*
{
        "cloudEnable": true,
        "id": "8a748495967a909401967c2ae1200fac",
        "installerFirstName": "Attila",
        "installerId": "8a5c814d7673b9eb017674f8c1fa0a9f",
        "installerLastName": "Jecs",
        "location": "",
        "sharedInfo": {
          "shareType": 0
        },
        "siteCity": "",
        "siteDeliveryStatus": 0,
        "siteName": "Nyírmkettes",
        "siteState": "",
        "siteStreet": "",
        "timeSync": false,
        "timeZone": "27"
      }
 */
public:
    QString id;
    QString siteName;
};

class SiteListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit SiteListModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void addrow(QJsonObject site);
    
    void clear();
private:
    QList<Site> m_sites; // List of sites
    QStringList m_headers; // Column headers
};

#endif // SITELISTMODEL_H
