#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void Refresh();
    ~MainWindow();


private slots:
    void Clear_button_kliked();
    void Ok_button_kliked();
    void Ok_and_Clear_button_activate();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
