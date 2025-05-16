#ifndef SITESEARCH_H
#define SITESEARCH_H

#include "sitelistmodel.h"
#include <QMainWindow>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui {
class SiteSearch;
}
QT_END_NAMESPACE

class SiteSearch : public QMainWindow
{
    Q_OBJECT

public:
    SiteSearch(QWidget *parent = nullptr);
    ~SiteSearch();

private slots:
    void site_list_received(QNetworkReply *reply);
    void searchPushButton_clicked();

    void tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::SiteSearch *ui;
    QNetworkAccessManager *manager;
    QString accessToken;
    QNetworkRequest request;
    SiteListModel model;
    QJsonDocument jsd;
    QJsonObject jso;
};
#endif // SITESEARCH_H
