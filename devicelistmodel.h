#ifndef DEVICELISTMODEL_H
#define DEVICELISTMODEL_H

#include <QAbstractTableModel>
#include <QJsonObject>

class Device
{
/*
        "id": "4513768bd74d4961a38192d680e01a42",
        "deviceName": "IPC05",
        "deviceOnlineStatus": 1,
        "deviceSerial": "FK3276061",
        "deviceVersion": "V5.7.23 build 241008",
        "deviceCategory": 1,
        "deviceType": "DS-2CD1021-I",
        "deviceSubCategory": 0,
        "isSubscribed": false,
        "deviceAddTime": "1736500414869",
        "timeZone": "27",
        "siteID": "8a7484e88f603e0f018f77589ff81f34",
        "siteName": "[E] Dombóvár",
        "deviceShareFlag": false
 */
public:
    QString id;
    QString deviceName;
    bool deviceOnlineStatus;
    QString deviceSerial;
    QString deviceVersion;
    QString deviceType;
};

class DeviceListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit DeviceListModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    bool setHeaderData(int section,
                       Qt::Orientation orientation,
                       const QVariant &value,
                       int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    // Fetch data dynamically:
    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;

    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    void clear();
    void addDevice(QJsonObject);
private:
    QList<Device> m_devices; // List of devices
    QStringList m_headers; // Column headers
};

#endif // DEVICELISTMODEL_H
