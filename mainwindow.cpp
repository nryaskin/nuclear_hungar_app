#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hangarview.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addGLWidget();
}

void MainWindow::addGLWidget()
{
    HangarView *hg_view = new HangarView();
    setCentralWidget(hg_view);
}

MainWindow::~MainWindow()
{
    delete ui;
}
