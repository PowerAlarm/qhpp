#ifndef FOABLAK_H
#define FOABLAK_H

#include <QMainWindow>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui {
class FoAblak;
}
QT_END_NAMESPACE

class FoAblak : public QMainWindow
{
    Q_OBJECT

public:
    FoAblak(QWidget *parent = nullptr);
    ~FoAblak();

private slots:
    void on_token_get_clicked();
    void token_received(QNetworkReply *reply);

    void on_accessTokenLineEdit_textChanged(const QString &arg1);

    void on_expireTimeDateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_site_search_clicked();

private:
    Ui::FoAblak *ui;
    QNetworkAccessManager *manager;
};
#endif // FOABLAK_H
