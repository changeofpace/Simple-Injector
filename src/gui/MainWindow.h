#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class InjectWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void closeEvent (QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    InjectWidget* injectWidget;
};

#endif // MAINWINDOW_H
