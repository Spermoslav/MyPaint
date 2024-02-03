#ifndef TOOLS_H
#define TOOLS_H

#include "display.h"
#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QResizeEvent>


class Tools : public QWidget
{
public:
    Tools(QWidget *parent, Display *disp);
    void resize();

    void update();

private slots:
    void penWsliderMoved();
    void penHsliderMoved();

private:
    Display *disp;

    QSlider *penWslider;
    QSlider *penHslider;

    QLabel *penWlabel;
    QLabel *penHlabel;

    QPushButton *clear;
};

#endif // TOOLS_H
