#include "display.h"

Display::Display(QWidget *parent)
    : QWidget(parent)
{
    this->parent = parent;
    mousePress = false;
    mouseRelease = true;
    ctrlPress = false;
    zPress = false;
    yPress = false;
    penW = 22;
    penH = 22;
    deletedItems = 0;
    this->setStyleSheet("border: 1px solid black;");

    qDebug() << size();
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

void Display::resizeEvent(QResizeEvent *e)
{

}

void Display::mousePressEvent(QMouseEvent *event)
{
    mousePress = true;
    for(int i = 0; i < deletedItems; i++) {
        for(int j = 0; j < draw.last().size(); j++) {
            draw.last().removeAt(j);
            qDebug() << draw.size();
        }
        draw.removeAt(draw.size() - 1);
    }
    deletedItems = 0;
    QList<DrawItem*> drawitems;
    draw.append(drawitems);
}

void Display::mouseReleaseEvent(QMouseEvent *event)
{
    mousePress = false;
}

void Display::mouseMoveEvent(QMouseEvent *e)
{
    if(mousePress){
        draw.last().append(new DrawItem(e->x(), e->y(), penW, penH));
        mousePress = true;
        mouseRelease = false;
        repaint();

    }
}

void Display::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Control) {
        ctrlPress = true;
        if(zPress) {
            deletedItems++;
            repaint();
        }
        if(yPress && deletedItems > 0) {
            deletedItems--;
            repaint();
        }
    }
    if(e->key() == Qt::Key_Z) {
        zPress = true;
        if(ctrlPress) {
            deletedItems++;
            repaint();
        }
    }
    if(e->key() == Qt::Key_Y) {
        yPress = true;
        if(ctrlPress && deletedItems > 0) {
            deletedItems--;
            repaint();
        }
    }

}

void Display::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Control) ctrlPress = false;
    if(e->key() == Qt::Key_Z) zPress = false;
    if(e->key() == Qt::Key_Y) yPress = false;
}

void Display::paintEvent(QPaintEvent *e)
{
    if(mousePress || deletedItems >= 0) {
        for(int i = 0; i < draw.size() - deletedItems; i++) {
            for(int j = 0; j < draw.at(i).size(); j++) {
                paint.begin(this);
                paint.setBrush(QBrush(QColor(0, 0, 0)));
                paint.drawEllipse(draw.at(i).at(j)->px, draw.at(i).at(j)->py, draw.at(i).at(j)->w, draw.at(i).at(j)->h);

                paint.end();
            }
        }
        qDebug() << draw.size();
        qDebug() << deletedItems;
    }
}

Display::~Display(){}

void Display::setPenW(int w)
{
    penW = w;
}

void Display::setPenH(int h)
{
    penH = h;
}

int Display::getPenW()
{
    return penW;
}

int Display::getPenH()
{
    return penH;
}


DrawItem::DrawItem(int px, int py, int w, int h)
{
    this->w = w;
    this->h = h;
    this->px = px - w / 2;
    this->py = py - h / 2;

}

