#include "mainwindowwidget.h"

MainWindowWidget::MainWindowWidget(QWidget *parent) : QWidget(parent)
{
    HangarView *hg_view = new HangarView();
    QGridLayout *layout = new QGridLayout;
    QWidgetItem* hangar_item = new QWidgetItem(hg_view);
    layout->addItem(hangar_item, 0, 0, 2, 3);

    QPushButton *button1 = new QPushButton("One");
    QPushButton *button2 = new QPushButton("Two");
    QPushButton *button3 = new QPushButton("Three");

    QVBoxLayout *ux_layout = new QVBoxLayout;
    ux_layout->addWidget(button1);
    ux_layout->addWidget(button2);
    ux_layout->addWidget(button3);
    layout->addItem(ux_layout,0, 3, 2, 1);
    setLayout(layout);
}
