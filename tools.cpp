#include "tools.h"

Tools::Tools(QWidget *parent, Display *disp)
    : QWidget(parent)
{
    this->disp = disp;

    penWslider = new QSlider(this);
    penWslider->setMaximum(50);
    penWslider->setOrientation(Qt::Horizontal);
    connect(penWslider, &QSlider::sliderMoved, this, &Tools::penWsliderMoved);

    penHslider = new QSlider(this);
    penHslider->setMaximum(50);
    penHslider->setOrientation(Qt::Horizontal);
    connect(penHslider, &QSlider::sliderMoved, this, &Tools::penHsliderMoved);

    penWlabel = new QLabel(this);
    penWlabel->setText("Ширина кисти: " + QString::number(disp->getPenW()));

    penHlabel = new QLabel(this);
    penHlabel->setText("Высота кисти: " + QString::number(disp->getPenH()));

    clear = new QPushButton("clear", this);
    connect(clear, &QPushButton::released, this, &Tools::clearReleased);
}

void Tools::resize()
{
    penWslider->setGeometry(width() / 8, height() * 0.8, width() * 0.75, height() * 0.1);
    penHslider->setGeometry(width() / 8, height() * 0.6, width() * 0.75, height() * 0.1);
    penWlabel->setGeometry(width() / 8, height() * 0.77, width() * 0.75, height() * 0.03);
    penHlabel->setGeometry(width() / 8, height() * 0.57, width() * 0.75, height() * 0.03);
    clear->setGeometry(width() / 8, height() * 0.95, width() * 0.325, height() * 0.05);
}

void Tools::update()
{
    penWlabel->setText("Ширина кисти: " + QString::number(disp->getPenW()));
    penHlabel->setText("Высота кисти: " + QString::number(disp->getPenH()));
}

void Tools::penWsliderMoved()
{
    disp->setPenW(penWslider->value());
    update();
    qDebug() << penWslider->value();
}

void Tools::penHsliderMoved()
{
    disp->setPenH(penHslider->value());
    update();
    qDebug() << penHslider->value();
}

void Tools::clearReleased()
{
    disp->clear();

}
