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
#include <QGridLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QSpinBox>

class Tools;
class ChangePenColor;
class ExamplePenColor;

class Tools : public QWidget
{
public:
    Tools(QWidget *parent, Display *disp);
    ~Tools();
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
    void changePenColorPBReleased();

    void resizeEvent(QResizeEvent *e) override;

private:
    Display *disp;

    QSlider *penSlider;
    QSlider *penWslider;
    QSlider *penHslider;

    QLabel *penSizeLabel;
    QLabel *penWlabel;
    QLabel *penHlabel;

    QPushButton *clear;
    QPushButton *backDrawPB;
    QPushButton *nextDrawPB;
    QPushButton *changePenColorPB;

    ChangePenColor *cpc;

    bool cpcWidgetOpen;
};

class ChangePenColor : public QWidget
{

public:
    ChangePenColor(Display *disp, QWidget *parent = nullptr);

    void updateSpinBoxes();
    void updateSliders();

private slots:
    void resizeEvent(QResizeEvent *e) override;


    void blackPBReleased();
    void whitePBReleased();
    void redPBReleased();
    void greenPBReleased();
    void bluePBReleased();

    void redSliderMoved();
    void greenSliderMoved();
    void blueSliderMoved();

    void redSpinBoxValueChanged();
    void greenSpinBoxValueChanged();
    void blueSpinBoxValueChanged();

private:
    QGroupBox *colorsBox;
    QGroupBox *rgbBox;
    ExamplePenColor *penColorBox;

    QList<QPushButton*> colors;
    QList<QString> basicColors;

    QSlider *redSlider;
    QSlider *greenSlider;
    QSlider *blueSlider;

    QSpinBox *redSpinBox;
    QSpinBox *greenSpinBox;
    QSpinBox *blueSpinBox;

    QGridLayout *colorsLay;
    QGridLayout *rgbLay;

    QHBoxLayout *changeRgbTools;

    Display *disp;

};

class ExamplePenColor : public QGroupBox
{

public:
    ExamplePenColor(QWidget *parent, Display *disp);

    void updateLabels();

private slots:
    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
private:
    Display *disp;

    QString rgbValue;

    QLabel *rgbValueLabel;

    int borderColor;
};

#endif // TOOLS_H
