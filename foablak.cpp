#include "foablak.h"
#include "ui_foablak.h"
#include "sitesearch.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>

FoAblak::FoAblak(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FoAblak)
    , manager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    QSettings settings;
    ui->appKeyLineEdit->setText(settings.value("appKey").toString());
    ui->secretKeyLineEdit->setText(settings.value("secretKey").toString());
    ui->accessTokenLineEdit->setText(settings.value("accessToken").toString());
    ui->expireTimeDateTimeEdit->setDateTime(QDateTime::fromMSecsSinceEpoch(settings.value("expireTime").toLongLong()));
}

FoAblak::~FoAblak()
{
    delete ui;
}

void FoAblak::on_token_get_clicked()
{
    QSettings settings;
    settings.setValue("appKey", ui->appKeyLineEdit->text());
    settings.setValue("secretKey", ui->secretKeyLineEdit->text());

    QNetworkRequest request;
    request.setUrl(QUrl("https://api.hik-partner.com/api/hpcgw/v1/token/get"));
    request.setRawHeader("Content-Type", "application/json");
    QJsonDocument jsd;
    QJsonObject jso;
    jso["appKey"] = ui->appKeyLineEdit->text();
    jso["secretKey"] = ui->secretKeyLineEdit->text();
    jsd.setObject(jso);

    manager->post(request, jsd.toJson());
    connect(manager, &QNetworkAccessManager::finished,
            this, &FoAblak::token_received);
}

void FoAblak::token_received(QNetworkReply *reply)
{
    QByteArray r = reply->readAll();
    reply->deleteLater();
    ui->statusbar->showMessage(QString::fromUtf8(r));
    QJsonDocument jsd = QJsonDocument::fromJson(r);
    QJsonObject jso = jsd.object();
    QJsonObject data = jso["data"].toObject();
    QString accessToken = data.value("accessToken").toString();
    qint64 expireTime = data.value("expireTime").toInteger();
    ui->accessTokenLineEdit->setText(accessToken);
    ui->expireTimeDateTimeEdit->setDateTime(QDateTime::fromMSecsSinceEpoch(expireTime));
    QSettings settings;
    settings.setValue("accessToken", accessToken);
    settings.setValue("expireTime", expireTime);
}

void FoAblak::on_accessTokenLineEdit_textChanged(const QString &arg1)
{
    bool access = ui->accessTokenLineEdit->text().startsWith("hpc.");
    ui->site_search->setEnabled(access);
    ui->device_list->setEnabled(access);
}


void FoAblak::on_expireTimeDateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    bool access = ui->expireTimeDateTimeEdit->dateTime() > QDateTime::currentDateTime();
    ui->site_search->setEnabled(access);
    ui->device_list->setEnabled(access);
}

void FoAblak::on_site_search_clicked()
{
    SiteSearch *ssw = new SiteSearch();
    ssw->setAttribute(Qt::WA_DeleteOnClose);
    ssw->show();
}

