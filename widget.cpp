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


    QVBoxLayout *rightLayout = new QVBoxLayout(parent);
    {
        QHBoxLayout *layout = new QHBoxLayout(parent);
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

    scene = new Scene(this);
    scene->setSceneRect(-250, -250, 500, 500);
    view = new QGraphicsView(scene, this);
    view->setRenderHints(QPainter::Antialiasing);
    rightLayout->addWidget(view);
    connect(btnCreateNode, &QAbstractButton::clicked, this, &Widget::onBtnCreateNodeClicked);
    connect(btnConnectNode, &QAbstractButton::clicked, this, &Widget::onBtnConnectNodeClicked);
    connect(btnDeleteNode, &QAbstractButton::clicked, this, &Widget::onBtnDeleteNodeClicked);
    connect(scene, &QGraphicsScene::selectionChanged, this, &Widget::sceneSelectionChanged);
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
        // добавляем стрелку на сцену
        ArrowItemGroup *arrow  = new ArrowItemGroup(lineBetweenItems, this);
        scene->addItem(arrow);
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
    node->setPos(randomBetween(-50, 50),    // Устанавливаем случайную позицию элемента
                 randomBetween(-50, 50));
    scene->addItem(node);   // Добавляем элемент на графическую сцену

    connect(node, &Node::selectNodeChanged, this, &Widget::onSceneNodeChanged);

}

void Widget::onBtnConnectNodeClicked()
{
    _source = Node::selectedNode();
    _connectNode = true;
}

void Widget::onBtnDeleteNodeClicked()
{
    _connectNode = false;
    _source = nullptr;
    scene->removeItem(Node::selectedNode());
    Node::deleteSelectedNode();
}

void Widget::sceneSelectionChanged()
{
    QList<QGraphicsItem *> l = scene->selectedItems();
    if (l.size() > 0) {
        Node *n = dynamic_cast<Node *>(l.at(0));
        if(n) {
            n->setNodeSelected(true);
            return;
        }
        // иначе выделена стрелка
        Node::selectedNode()->setNodeSelected(false);
    }
    else
        Node::selectedNode()->setNodeSelected(false);
}

