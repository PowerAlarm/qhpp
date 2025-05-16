#include "sitesearch.h"
#include "ui_sitesearch.h"
#include "devicelist.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>

SiteSearch::SiteSearch(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SiteSearch)
    , manager(new QNetworkAccessManager(this))
    , request(QUrl("https://api.hik-partner.com/api/hpcgw/v1/site/search"))
    , model(this)
{
    ui->setupUi(this);
    ui->tableView->setModel(&model);
    QSettings settings;
    accessToken = settings.value("accessToken").toString();
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Authorization", QString("Bearer ").append(accessToken).toUtf8());
    jsd.setObject(jso);
    jso["pageSize"] = "100";

    connect(ui->searchPushButton, &QPushButton::clicked,
            this, &SiteSearch::searchPushButton_clicked);
    connect(ui->tableView, &QTableView::doubleClicked,
            this, &SiteSearch::tableView_doubleClicked);
    connect(manager, &QNetworkAccessManager::finished,
            this, &SiteSearch::site_list_received);
}

SiteSearch::~SiteSearch()
{
    delete ui;
}

void SiteSearch::site_list_received(QNetworkReply *reply)
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
        model.addrow(site);
    }
    ui->tableView->resizeColumnsToContents();
    if( page < totalPage ) {
        jso["page"] = QString::number(page + 1);
        jsd.setObject(jso);
        manager->post(request, jsd.toJson());
    }
}

void SiteSearch::searchPushButton_clicked()
{
    jso["page"] = "1";
    jso["search"] = ui->searchLineEdit->text();
    jsd.setObject(jso);

    manager->post(request, jsd.toJson());
}

void SiteSearch::tableView_doubleClicked(const QModelIndex &index)
{
    if( index.column() == 0 ) {
        QString id = index.data().toString();
        ui->statusbar->showMessage(QString("DeviceList by siteId: %1").arg(id));
        DeviceList *dlw = new DeviceList();
        dlw->setAttribute(Qt::WA_DeleteOnClose);
        dlw->searchBySiteId(id);
        dlw->show();
    }
}

