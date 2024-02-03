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
    int getPenW();
    int getPenH();

    void clear();
    void backDraw();
    void nextDraw();

private slots:
    void resizeEvent(QResizeEvent *e) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
    void paintEvent(QPaintEvent *e) override;

private:
    QWidget *parent;
    QPainter paint;
 //   QList<DrawItem*> drawItems;
    QList<QList<DrawItem*>> draw;

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
