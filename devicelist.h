#ifndef DEVICELIST_H
#define DEVICELIST_H

#include "devicelistmodel.h"
#include <QMainWindow>
#include <QNetworkAccessManager>

namespace Ui {
class DeviceList;
}

class DeviceList : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeviceList(QWidget *parent = nullptr);
    ~DeviceList();

    void searchBySiteId(QString siteId);

public slots:
    void siteIdPushButton_clicked();
    void deviceListReceived(QNetworkReply *reply);
    void tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::DeviceList *ui;
    QNetworkAccessManager *manager;
    QString accessToken;
    QNetworkRequest request;
    DeviceListModel model;
    QJsonDocument jsd;
    QJsonObject jso;
};

#endif // DEVICELIST_H
