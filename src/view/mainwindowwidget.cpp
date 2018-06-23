#include "mainwindowwidget.h"
#include <QTableWidgetItem>
MainWindowWidget::MainWindowWidget(QWidget *parent) : QWidget(parent)
{
    HangarView *hg_view = new HangarView();
    QGridLayout *layout = new QGridLayout;
    QWidgetItem* hangar_item = new QWidgetItem(hg_view);
    layout->addItem(hangar_item, 0, 0, 4, 35);

    QPushButton *button1 = new QPushButton("Добавить ящик");
    QObject::connect(button1, SIGNAL(clicked()),hg_view, SLOT(addContainerClicked()));
    QPushButton *button2 = new QPushButton("Убрать ящик");
    QPushButton *button3 = new QPushButton("Построить маршрут");

    QVBoxLayout *ux_layout = new QVBoxLayout;
    QTableWidget* tableWidget = new QTableWidget(4, 14);
    ux_layout->addWidget(button1);
    ux_layout->addWidget(tableWidget);
    ux_layout->addWidget(button2);
    ux_layout->addWidget(button3);
    layout->addItem(ux_layout,0, 35, 4, 14);
    setLayout(layout);
}
