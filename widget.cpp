#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setMinimumSize(400, 400);

    disp = new Display(this);
    disp->setGeometry(0, 0, width() / 1.5, height());

    tools = new Tools(this, disp);
    tools->setGeometry(width() / 1.5, 0, width() / 3, height());
    tools->setStyleSheet("border: 1px solid black;");
    tools->resize();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent *e)
{
    disp->setGeometry(0, 0, width() / 1.5, height());
    tools->setGeometry(width() / 1.5, 0, width() / 3, height());
}

