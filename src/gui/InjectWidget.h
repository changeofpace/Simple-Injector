#ifndef INJECTWIDGET_H
#define INJECTWIDGET_H

#include <QWidget>
#include <QString>

#include "core.h"

#define CSTR(qstr)  (QString(qstr).toStdString().c_str())

// Inject core uses DWORD, qt uses unsigned int (QVariant::UInt).
static_assert(sizeof(DWORD) == sizeof(unsigned int),
              "DWORD type is incompatible with the assumed conversion type (unsigned int).");

namespace Ui {
class InjectWidget;
}

class InjectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InjectWidget(QWidget *parent = 0);
    ~InjectWidget();

    void saveSettings();
    void loadSettings();

private slots:
    void on_dllBrowseButton_clicked();
    void on_injectButton_clicked();

    void populateActiveProcesses();

private:
    Ui::InjectWidget *ui;

    QVector<core::ActiveProcess> activeProcesses;
    QString payloadPath;
};

#endif // INJECTWIDGET_H
