#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindowwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addGLWidget();
}

void MainWindow::addGLWidget()
{
     MainWindowWidget* mw_widget = new MainWindowWidget();
     setCentralWidget(mw_widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
