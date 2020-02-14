#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pButtonOK_1_clicked();

    void on_pButtonOK_2_clicked();

    void on_pButtonOK_3_clicked();

    void on_pButtonOpenFile_1_clicked();

    void on_pButtonOK_4_clicked();

    void on_pButtonGen_clicked();

    void on_pButtonOK_5_clicked();

    void on_pButtonOpenFile_2_clicked();

    void on_pButtonOK_6_clicked();

    void on_progBar_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
