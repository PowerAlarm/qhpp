#include "foablak.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Power Alarm Kft.");
    QCoreApplication::setOrganizationDomain("poweralarm.hu");
    QCoreApplication::setApplicationName("Cute HPP");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "qhpp_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    FoAblak *w = new FoAblak();
    w->show();
    return a.exec();
}
