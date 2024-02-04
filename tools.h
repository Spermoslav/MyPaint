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

    void updateLabels();
    void updateSliders();

private slots:
    void penSliderMoved();
    void penWsliderMoved();
    void penHsliderMoved();
    void clearReleased();
    void backDrawPBReleased();
    void nextDrawPBReleased();

private:
    Display *disp;

    QSlider *penSlider;
    QSlider *penWslider;
    QSlider *penHslider;

    QLabel *penWlabel;
    QLabel *penHlabel;

    QPushButton *clear;
    QPushButton *backDrawPB;
    QPushButton *nextDrawPB;
};

#endif // TOOLS_H
