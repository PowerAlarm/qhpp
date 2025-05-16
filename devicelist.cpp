#include "devicelist.h"
#include "ui_devicelist.h"
#include <QSettings>
#include <QNetworkReply>
#include <QJsonArray>

DeviceList::DeviceList(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DeviceList)
{
    ui->setupUi(this);
    model.setHeaderData(0, Qt::Horizontal, tr("ID"));
    model.setHeaderData(1, Qt::Horizontal, tr("Device Name"));
    model.setHeaderData(2, Qt::Horizontal, tr("Device Online Status"));
    model.setHeaderData(3, Qt::Horizontal, tr("Device Serial"));
    model.setHeaderData(4, Qt::Horizontal, tr("Device Version"));
    model.setHeaderData(5, Qt::Horizontal, tr("Device Type"));

    ui->tableView->setModel(&model);
    QSettings settings;
    accessToken = settings.value("accessToken").toString();
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Authorization", QString("Bearer ").append(accessToken).toUtf8());
    jsd.setObject(jso);
    jso["pageSize"] = "100";

    connect(ui->siteIdPushButton, &QPushButton::clicked,
            this, &DeviceList::siteIdPushButton_clicked);
    connect(ui->tableView, &QTableView::doubleClicked,
            this, &DeviceList::tableView_doubleClicked);
    connect(manager, &QNetworkAccessManager::finished,
            this, &DeviceList::deviceListReceived);
}

DeviceList::~DeviceList()
{
    delete ui;
}

void DeviceList::searchBySiteId(QString siteId)
{
    ui->siteIdLineEdit->setText(siteId);
    siteIdPushButton_clicked();
}

void DeviceList::siteIdPushButton_clicked()
{
    jso["page"] = "1";
    jso["search"] = ui->siteIdLineEdit->text();
    jsd.setObject(jso);

    manager->post(request, jsd.toJson());
}

void DeviceList::deviceListReceived(QNetworkReply *reply)
{
    QByteArray r = reply->readAll();
    reply->deleteLater();
    ui->statusbar->showMessage(QString::fromUtf8(r));
    QJsonDocument rjsd = QJsonDocument::fromJson(r);
    QJsonObject rjso = rjsd.object();
    QJsonObject data = rjso["data"].toObject();
    int totalPage = data.value("totalPage").toInt();
    ui->progressBar->setMaximum(totalPage);
    int page = data.value("page").toInt();
    ui->progressBar->setValue(page);
    const QJsonArray siteList = data["rows"].toArray();
    if( jso["page"] == "1" ) {
        model.clear();
    }
    for( const QJsonValue &siteValue : siteList ) {
        QJsonObject site = siteValue.toObject();
        //model.addrow(site);
    }
    ui->tableView->resizeColumnsToContents();
    if( page < totalPage ) {
        jso["page"] = QString::number(page + 1);
        jsd.setObject(jso);
        manager->post(request, jsd.toJson());
    }
}

void DeviceList::tableView_doubleClicked(const QModelIndex &index)
{

}
