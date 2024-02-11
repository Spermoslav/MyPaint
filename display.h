#ifndef DISPLAY_H
#define DISPLAY_H

#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QList>
#include <QColor>

class Display;
class DrawItem;

class Display : public QWidget
{
    Q_OBJECT
public:
    Display(QWidget *parent = nullptr);
    ~Display();
    void setPenW(int w);
    void setPenH(int h);
    void setPenColor(QColor pc = QColor(0, 0, 0));

    int getPenW();
    int getPenH();
    QColor getPenColor();

    void clear();
    void backDraw();
    void nextDraw();

private slots:
    void resizeEvent(QResizeEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    void paintEvent(QPaintEvent *e) override;

private:
    QWidget *parent;
    QPainter paint;
    QList<QList<DrawItem*>> draw;
    QList<QColor> drawColors;
    QColor penColor;

    bool mousePress;
    bool mouseRelease;

    bool ctrlPress;
    bool zPress;
    bool yPress;

    int penW;
    int penH;
    int deletedItems;
};

class DrawItem
{
    friend Display;
public:
    DrawItem(int px, int py, int w, int h);

private slots:


private:

    int w;
    int h;
    int px;
    int py;

};

#endif // DISPLAY_H
