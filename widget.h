#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGraphicsView>
#include <QPushButton>
#include <QVector>
#include <QMap>
#include <QLabel>
#include <QLineEdit>

#include "node.h"

class Widget : public QWidget
{
    Q_OBJECT
private:
    QPushButton *btnCreateNode;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QMap<uint, Node *> nodes;

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private slots:
    void onBtnCreateNodeClicked();
};

#endif // WIDGET_H
