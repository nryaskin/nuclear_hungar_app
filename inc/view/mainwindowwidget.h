#ifndef MAINWINDOWWIDGET_H
#define MAINWINDOWWIDGET_H

#include <QWidget>
#include "hangarview.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidgetItem>

class MainWindowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindowWidget(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MAINWINDOWWIDGET_H
