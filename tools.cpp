#include "tools.h"

Tools::Tools(QWidget *parent, Display *disp)
    : QWidget(parent)
{
    this->disp = disp;

    penSlider = new QSlider(this);
    penSlider->setMaximum(50);
    penSlider->setOrientation(Qt::Horizontal);
    connect(penSlider, &QSlider::sliderMoved, this, &Tools::penSliderMoved);

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
    penWslider->setValue(disp->getPenW());

    penHlabel = new QLabel(this);
    penHlabel->setText("Высота кисти: " + QString::number(disp->getPenH()));
    penHslider->setValue(disp->getPenH());

    clear = new QPushButton("clear", this);
    connect(clear, &QPushButton::released, this, &Tools::clearReleased);

    backDrawPB = new QPushButton("back", this);
    connect(backDrawPB, &QPushButton::released, this, &Tools::backDrawPBReleased);

    nextDrawPB = new QPushButton("next", this);
    connect(nextDrawPB, &QPushButton::released, this, &Tools::nextDrawPBReleased);

    changePenColorPB = new QPushButton("changePenColor", this);
    connect(changePenColorPB, &QPushButton::released, this, &Tools::changePenColorPBReleased);

    cpc = new ChangePenColor(disp);
    cpc->setGeometry(50, 50, 500, 500);
    cpc->show();

    cpcWidgetOpen = false;
}

Tools::~Tools()
{
    delete cpc;
}

void Tools::resize()
{
    penSlider->setGeometry(width() * 0.1, height() * 0.4, width() * 0.75, height() * 0.1);
    penWslider->setGeometry(width() * 0.1, height() * 0.8, width() * 0.75, height() * 0.1);
    penHslider->setGeometry(width() * 0.1, height() * 0.6, width() * 0.75, height() * 0.1);
    penWlabel->setGeometry(width() * 0.1, height() * 0.77, width() * 0.75, height() * 0.03);
    penHlabel->setGeometry(width() * 0.1, height() * 0.57, width() * 0.75, height() * 0.03);
    clear->setGeometry(width() * 0.1, height() * 0.95, width() * 0.325, height() * 0.05);
    backDrawPB->setGeometry(width() * 0.1, height() * 0.025, width() * 0.25, height() * 0.05);
    nextDrawPB->setGeometry(width() * 0.4, height() * 0.025, width() * 0.25, height() * 0.05);
    changePenColorPB->setGeometry(width() * 0.1, height() * 0.08, width() * 0.8, height() * 0.05);
}

void Tools::updateLabels()
{
    penWlabel->setText("Ширина кисти: " + QString::number(disp->getPenW()));
    penHlabel->setText("Высота кисти: " + QString::number(disp->getPenH()));

}

void Tools::updateSliders()
{
    penWslider->setValue(disp->getPenW());
    penHslider->setValue(disp->getPenH());
}

void Tools::penSliderMoved()
{
    disp->setPenW(penSlider->value());
    disp->setPenH(penSlider->value());
    updateSliders();
}

void Tools::penWsliderMoved()
{
    disp->setPenW(penWslider->value());
    updateLabels();
    qDebug() << penWslider->value();
}

void Tools::penHsliderMoved()
{
    disp->setPenH(penHslider->value());
    updateLabels();
    qDebug() << penHslider->value();
}

void Tools::clearReleased()
{
    disp->clear();

}

void Tools::backDrawPBReleased()
{
    disp->backDraw();
}

void Tools::nextDrawPBReleased()
{
    disp->nextDraw();
}

void Tools::changePenColorPBReleased()
{
    if(cpcWidgetOpen){
        cpcWidgetOpen = false;
        cpc->hide();
    }
    else {
        cpcWidgetOpen = true;
        cpc->show();
    }
}

ChangePenColor::ChangePenColor(Display *disp, QWidget *parent)
    : QWidget(parent)
{
    this->disp = disp;

    colorsBox = new QGroupBox(this);
    colorsBox->setGeometry(width() * 0.01, height() * 0.01, width() * 0.8, height() * 0.15);

    rgbBox = new QGroupBox(this);
    rgbBox->setGeometry(width() * 0.01, height() * 0.2, width() * 0.8, height() * 0.3);

    basicColors.append("black");
    basicColors.append("white");
    basicColors.append("red");
    basicColors.append("green");
    basicColors.append("blue");

    for(int i = 0; i < 5; i++) {
        colors.append(new QPushButton(this));
        colors.at(i)->setStyleSheet("background-color: " + basicColors.at(i) + ";"
                                    "border: 1px solid black;");
    }

    connect(colors.at(0), &QPushButton::released, this, &ChangePenColor::blackPBReleased);
    connect(colors.at(1), &QPushButton::released, this, &ChangePenColor::whitePBReleased);
    connect(colors.at(2), &QPushButton::released, this, &ChangePenColor::redPBReleased);
    connect(colors.at(3), &QPushButton::released, this, &ChangePenColor::greenPBReleased);
    connect(colors.at(4), &QPushButton::released, this, &ChangePenColor::bluePBReleased);

    redSlider = new QSlider;
    redSlider->setOrientation(Qt::Horizontal);

    greenSlider = new QSlider;
    greenSlider->setOrientation(Qt::Horizontal);

    blueSlider = new QSlider;
    blueSlider->setOrientation(Qt::Horizontal);

    redSpinBox = new QSpinBox;

    greenSpinBox = new QSpinBox;

    blueSpinBox = new QSpinBox;

    colorsLay = new QGridLayout(colorsBox);
    colorsLay->setSpacing(width() * 0.1);
    colorsLay->setContentsMargins(0, 0, 0, 0);
    for(int i = 0; i < colors.size(); i++){
        colorsLay->addWidget(colors.at(i), 0, i);
    }

    rgbLay = new QGridLayout(rgbBox);
    rgbLay->setSpacing(10);
    rgbLay->setContentsMargins(10, 10, 10, 10);
    rgbLay->addWidget(redSlider, 0, 0);
    rgbLay->addWidget(redSpinBox, 0, 1);
    rgbLay->addWidget(greenSlider, 1, 0);
    rgbLay->addWidget(greenSpinBox, 1, 1);
    rgbLay->addWidget(blueSlider, 2, 0);
    rgbLay->addWidget(blueSpinBox, 2, 1);

}

void ChangePenColor::resizeEvent(QResizeEvent *e)
{
    colorsBox->setGeometry(width() * 0.01, height() * 0.01, width() * 0.98, height() * 0.15);
}

void ChangePenColor::blackPBReleased()
{
    disp->setPenColor(Qt::black);
}

void ChangePenColor::whitePBReleased()
{
    disp->setPenColor(Qt::white);
}

void ChangePenColor::redPBReleased()
{
    disp->setPenColor(Qt::red);
}

void ChangePenColor::greenPBReleased()
{
    disp->setPenColor(Qt::green);
}

void ChangePenColor::bluePBReleased()
{
    disp->setPenColor(Qt::blue);
}
