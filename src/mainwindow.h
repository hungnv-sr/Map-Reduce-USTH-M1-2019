#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <parser.h>
#include <arrayexperiment.h>
#include <matrixexperiment.h>
#include <experimentcontroller.h>
#include <vector>
using std::vector;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    unsigned dataSize, numData;
    DataType dataType;
    Distribution distribution;
    vector<double> arrData;
    vector<Matrix<double> > matData;

    Op operation;
    vector<Algo> testAlgos;
    unsigned nTest;
    bool shuffle;
    vector<Result> results;



public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pButtonOpenFile_1_clicked();

    void on_pButtonGen_clicked();

    void on_pButtonOpenFile_2_clicked();

    void on_cBoxDataType_currentIndexChanged(int index);

    void on_pButtonBrowseDir_clicked();

    void on_pButtonSave_clicked();

    void on_gBoxAlgorithm_clicked();

    void on_pButtonRun_clicked();

private:
    Ui::MainWindow *ui;

    QString getDistributionString();

    vector<double> getDistributionParams();
};
#endif // MAINWINDOW_H
