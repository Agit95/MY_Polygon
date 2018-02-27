#include "mcanvas.h"
#include <QDebug>

bool Ok_pressd_flag = false;

int MCanvas::m_counter=0;

MCanvas::MCanvas(QWidget *parent) : QWidget(parent)
{

}

void MCanvas::paintEvent(QPaintEvent *)
{
    //activate  paint  tool
    QPainter t_oPainter(this);

    //activate Pen  from painting
    t_oPainter.setPen(QPen(Qt::red, 6 , Qt::SolidLine));

    //Draws the edge of the Canvas_widget
    QRectF _size (0,0,this->width(),this->height());
    t_oPainter.drawRect(_size);

    //set Pen style  from  painting points
    t_oPainter.setPen(QPen(Qt::black, 5 , Qt::SolidLine));
    t_oPainter.setRenderHint(QPainter::Antialiasing, true);

    //if counter is 1 Draw first point in Widget
    if(m_counter==1)
    {
        t_oPainter.setPen(QPen(Qt::black, 5 , Qt::SolidLine));
        QPoint top_point =m_oVector_top[0].toPoint();
        t_oPainter.drawPoint(top_point);

        //activate Ok and Clear button's
        Ok_and_Clear_buutton_activate_Slot();
        qDebug() << "first point" ;
    }
    else
    {
        if(m_counter!=0)
        {
            qDebug() << " paint line " ;
            for(int i=0; i<m_oVector_top.size()-1; ++i)
            {
                t_oPainter.setPen(QPen(Qt::black, 5 , Qt::SolidLine));
                t_oPainter.drawPoint(m_oVector_top[i].toPoint());
                t_oPainter.drawPoint(m_oVector_top[i+1].toPoint());
                t_oPainter.setPen(QPen(Qt::black, 2 , Qt::SolidLine));
                t_oPainter.drawLine(m_oVector_top[i].toPoint(),m_oVector_top[i+1].toPoint());
            }
        }
    }
    if(Ok_pressd_flag)  //if button ok  isCliced  then print last line and excequite
    {
        qDebug() << "paint last line" ;
        t_oPainter.drawLine(m_oVector_top[0].toPoint(),m_oVector_top[m_oVector_top.size()-1].toPoint());
    }
    //incremetne  counter
    ++m_counter;
}

void MCanvas::mousePressEvent(QMouseEvent * event)
{
    //if Mouse pressed then event position  is a tops  there  are polygon
    m_oVector_top.push_back(event->pos());
    qDebug() << event->pos().x() <<event->pos().y();
    update(); //update  Canvas_widget  and  call paintEvent
}


qreal MCanvas::Line_equation(const QLineF& Side_1, const QPointF& Side_Point)
{
    qreal Sum_1 = ((Side_Point.x() - Side_1.x2()) * Side_1.y1()) / (Side_1.x1() - Side_1.x2());
    qreal Sum_2 = ((Side_Point.x() - Side_1.x1()) * Side_1.y2()) / (Side_1.x2() - Side_1.x1()) ;

    //Direct equation by Lagrange's interplanetary multiplex
    return Sum_1 + Sum_2 - Side_Point.y();
}


bool MCanvas::verification()
{
    //compare the castle with the rest of the lateral edges
    for(int i = 0 ; i < m_oVector_top.size() - 1; ++i)
    {
        //selection's  comparative side
        QLineF line_object(m_oVector_top[i].toPoint(), m_oVector_top[i+1].toPoint());

        for(int j = 0; j < m_oVector_top.size() - 1; ++j)
        {
            if(j != (i+1) && j != i)
            {
                qreal e = Line_equation(line_object,m_oVector_top[j].toPoint());
                qreal f = Line_equation(line_object,m_oVector_top[j+1].toPoint());
                if(e * f < 0)
                    return  false;
            }
        }
    }

    //if first  top  and  last  top  equal then  we dont  compare  this  situatons
    if(m_oVector_top[0].toPoint().x()!= m_oVector_top[m_oVector_top.size()-1].toPoint().x() &&
       m_oVector_top[0].toPoint().y()!= m_oVector_top[m_oVector_top.size()-1].toPoint().y()   )
    {
        //We compare the suture to the left and the left side with the rest
        QLineF line_object(m_oVector_top[0].toPoint(), m_oVector_top[m_oVector_top.size()-1].toPoint());
        for(int j = 1; j < m_oVector_top.size() - 2; ++j)
        {
            qreal e = Line_equation(line_object,m_oVector_top[j].toPoint());
            qreal f = Line_equation(line_object,m_oVector_top[j+1].toPoint());
            if(e * f < 0 )
                return  false;
        }
    }
    return true;
}

void MCanvas::Ok_and_Clear_buutton_activate_Slot()
{
    emit Ok_and_Clear_buutton_activate();
}







