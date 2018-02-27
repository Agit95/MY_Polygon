#ifndef MCANVAS_H
#define MCANVAS_H

#include <QWidget>
#include <QPainter>
#include <QPointF>
#include <QVector>
#include <QLineF>
#include <QMouseEvent>


class MCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit MCanvas(QWidget *parent = nullptr);

    qreal Line_equation(const QLineF& Side_1, const QPointF& Side_Point);
    bool  verification();


    QVector<QPointF>  m_oVector_top;
    static  int       m_counter;

signals:
    Ok_and_Clear_buutton_activate();
private slots:
    void Ok_and_Clear_buutton_activate_Slot();

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent * event);

};

#endif // MCANVAS_H
