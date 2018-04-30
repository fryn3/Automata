#include "widget.h"

static int randomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

Widget::Widget(QWidget *parent)
    : QWidget(parent), _connectNode(false)
{
    resize(540, 560);
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

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 500, 500);
    view = new QGraphicsView(scene);
    view->setRenderHints(QPainter::Antialiasing);
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
    if (_connectNode) {
        // Возможно будет равен nullptr,
        // это значит направлен в себя
        _destination = Node::selectedNode();
        QLineF lineBetweenItems;
        lineBetweenItems.setP1(_source->scenePos());
        lineBetweenItems.setP2(_destination->scenePos());
        // добавляем линию на сцену
        QGraphicsLineItem * l = scene->addLine(lineBetweenItems);
        l->setPen(QPen(Qt::black, 3, Qt::SolidLine));
//        l->setFlags(QGraphicsItem::ItemIsSelectable);


        _connectNode = false;
        Node::selectedNode()->setNodeSelected(false);
    }
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
    node->setPos(randomBetween(150, 350),    // Устанавливаем случайную позицию элемента
                 randomBetween(150, 350));
    scene->addItem(node);   // Добавляем элемент на графическую сцену

    connect(node, SIGNAL(selectNodeChanged()), SLOT(onSceneNodeChanged()));

}

void Widget::onBtnConnectNodeClicked()
{
    _source = Node::selectedNode();
    _connectNode = true;
}

void Widget::onBtnDeleteNodeClicked()
{
    scene->removeItem(Node::selectedNode());
    Node::deleteSelectedNode();
}

