#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mcanvas.h"

extern bool Ok_pressd_flag;

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setDisabled(true);
    ui->textEdit->setDisabled(true);
    ui->OK_button->setDisabled(true);
    ui->Clear_button->setDisabled(true);

    connect(ui->Clear_button,SIGNAL(clicked()),this,SLOT(Clear_button_kliked()));
    connect(ui->OK_button,SIGNAL(clicked()),this,SLOT(Ok_button_kliked()));
    connect(ui->Close_button,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->Canvas_widget,SIGNAL(Ok_and_Clear_buutton_activate()),this,SLOT(Ok_and_Clear_button_activate()));

}

void MainWindow::Refresh()
{
   ui->Canvas_widget->m_oVector_top.clear();
   ui->Canvas_widget->m_counter=0;
   ui->Canvas_widget->setEnabled(true);
   ui->Clear_button->setDisabled(true);
   ui->OK_button->setDisabled(true);
   Ok_pressd_flag = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Clear_button_kliked()
{
    ui->lineEdit->clear();
    Refresh();
    ui->Canvas_widget->update();
}

void MainWindow::Ok_button_kliked()
{
    Ok_pressd_flag=true;
    ui->Canvas_widget->setEnabled(false);

    //point or  line  is a nonconvex polygon
    if(ui->Canvas_widget->m_oVector_top.size()==1 || ui->Canvas_widget->m_oVector_top.size()==2)
    {
        ui->lineEdit->setEnabled(true);
        ui->lineEdit->setText("The shape is a not polygon");
        ui->lineEdit->setEnabled(false);

        return;
    }

    if(ui->Canvas_widget->verification())
    {
        ui->lineEdit->setEnabled(true);
        ui->lineEdit->setText("The shape is convex polygon");
        ui->lineEdit->setEnabled(false);
    }
    else
    {
        ui->lineEdit->setEnabled(true);
        ui->lineEdit->setText("The shape is nonconvex polygon");
        ui->lineEdit->setEnabled(false);
    }
}

void MainWindow::Ok_and_Clear_button_activate()
{
    ui->Clear_button->setEnabled(true);
    ui->OK_button->setEnabled(true);
}


