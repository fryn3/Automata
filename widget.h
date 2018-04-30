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
    QPushButton *btnConnectNode;
    QPushButton *btnDeleteNode;
    QGraphicsView *view;
    QGraphicsScene *scene;
    bool _connectNode;
    Node *_source, *_destination;
public:
    Widget(QWidget *parent = 0);
    ~Widget();
private slots:
    void onSceneNodeChanged();
    void onBtnCreateNodeClicked();
    void onBtnConnectNodeClicked();
    void onBtnDeleteNodeClicked();
};

#endif // WIDGET_H
