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
    QVBoxLayout *leftLayout = new QVBoxLayout();
    {
        QHBoxLayout *lay = new QHBoxLayout();
        QLabel *l = new QLabel("Вариант");
        QLineEdit *e = new QLineEdit("32");
        QPushButton *b = new QPushButton("Применить");
        lay->addWidget(l);
        lay->addWidget(e);
        lay->addWidget(b);
        leftLayout->addLayout(lay);
    }
    mainLayout->addLayout(leftLayout);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    {
        QHBoxLayout *layout = new QHBoxLayout();
        {
            btnCreateNode = new QPushButton("Добавить вершину", this);
            layout->addWidget(btnCreateNode);
            QPushButton *bSt = new QPushButton("Соединить", this);
            layout->addWidget(bSt);
            QPushButton *bDel = new QPushButton("Удалить", this);
            layout->addWidget(bDel);
        }
        rightLayout->addLayout(layout);
    }

    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    view->setScene(scene);
    rightLayout->addWidget(view);
    connect(btnCreateNode, SIGNAL(clicked()), SLOT(onBtnCreateNodeClicked()));

    // только дизайн
    {
        QGridLayout *layout = new QGridLayout();
        {
            QLabel *l = new QLabel("Состояние:");
            QLineEdit *e = new QLineEdit();
            layout->addWidget(l, 0, 0);
            layout->addWidget(e, 0, 1);
        }
        {
            QLabel *l = new QLabel("X", this);
            QLineEdit *e = new QLineEdit(this);
            layout->addWidget(l, 1, 0);
            layout->addWidget(e, 1, 1);
        }
        {
            QLabel *l = new QLabel("Y", this);
            QLineEdit *e = new QLineEdit(this);
            layout->addWidget(l, 1, 2);
            layout->addWidget(e, 1, 3);
        }
        {
            QPushButton *b = new QPushButton("Применить", this);
            b->setFixedSize(100, 50);
            layout->addWidget(b, 0, 4, 2, 1);
        }
        {
            QPushButton *b = new QPushButton("Проверить!", this);
            b->setFixedSize(100,50);
            layout->addWidget(b, 0, 5, 2, 1);
        }
        rightLayout->addLayout(layout);
    }
    mainLayout->addLayout(rightLayout);
}

Widget::~Widget()
{

}

void Widget::onBtnCreateNodeClicked()
{
    Node *node = new Node();        // Создаём графический элемент
    nodes[node->id] = node;
    node->setPos(randomBetween(100, 300),    // Устанавливаем случайную позицию элемента
                 randomBetween(100, 300));
    scene->addItem(node);   // Добавляем элемент на графическую сцену
}
