#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "InjectWidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    injectWidget = new InjectWidget(this);

    setCentralWidget(injectWidget);

    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    injectWidget->saveSettings();

    QMainWindow::closeEvent(event);
}
