#include "widget.h"

static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(500, 530);
    QHBoxLayout *mainLayout = new QHBoxLayout(this);


    QVBoxLayout *rightLayout = new QVBoxLayout();
    {
        QHBoxLayout *layout = new QHBoxLayout();
        {
            btnCreateNode = new QPushButton("Добавить вершину", this);
            layout->addWidget(btnCreateNode);
            btnConnectNode = new QPushButton("Соединить", this);
            btnConnectNode->setEnabled(false);
            layout->addWidget(btnConnectNode);
            btnDeleteNode = new QPushButton("Удалить", this);
            btnDeleteNode->setEnabled(false);
            layout->addWidget(btnDeleteNode);
        }
        rightLayout->addLayout(layout);
    }

    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    view->setScene(scene);
    rightLayout->addWidget(view);
    connect(btnCreateNode, SIGNAL(clicked()), SLOT(onBtnCreateNodeClicked()));
    connect(btnConnectNode, SIGNAL(clicked()), SLOT(onBtnConnectNodeClicked()));
    connect(btnDeleteNode, SIGNAL(clicked()), SLOT(onBtnDeleteNodeClicked()));
    mainLayout->addLayout(rightLayout);
}

Widget::~Widget()
{

}

void Widget::onSceneNodeChanged()
{
    if (Node::selectedNode() != nullptr) {
        btnConnectNode->setEnabled(true);
        btnDeleteNode->setEnabled(true);
    } else {
        btnConnectNode->setEnabled(false);
        btnDeleteNode->setEnabled(false);
    }
}

void Widget::onBtnCreateNodeClicked()
{
    Node *node = new Node();        // Создаём графический элемент
    node->setPos(randomBetween(100, 300),    // Устанавливаем случайную позицию элемента
                 randomBetween(100, 300));
    scene->addItem(node);   // Добавляем элемент на графическую сцену

    connect(node, SIGNAL(selectNodeChanged()), SLOT(onSceneNodeChanged()));

}

void Widget::onBtnConnectNodeClicked()
{

}

void Widget::onBtnDeleteNodeClicked()
{
    Node::deleteSelectedNode();
}

