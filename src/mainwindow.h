#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <parser.h>
#include <arraygenerator.h>
#include <arrayexperiment.h>
#include <matrixexperiment.h>
#include <vector>
#include <QThread>
#include <QSemaphore>
using std::vector;

struct MainWindowException : public std::exception {
private:
    QString msg;

public:
    MainWindowException(QString mess) {
        msg = mess;
    }
    const char* what() const throw() {
        return msg.toStdString().c_str();
    }
};


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QSemaphore resource;
    QThread createDistributionThread;
    QThread createDataThread;
    QThread experimentThread;


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

    void on_rButtonSave_clicked();

    void on_pButtonBrowseDir_clicked();

    void on_rButtonDontSave_clicked();

    void on_gBoxAlgorithm_clicked();

    void on_pButtonRun_clicked();

    void on_pButtonSaveDataset_clicked();

    //-----------------------   SIGNAL AND SLOTS FOR THREADS
private slots:
    void slotGenerateArrayFinish(const vector<double>& arr);

    void slotArrayExperimentFinish(const vector<Result> &res);
signals:
    void signalGenerateArray(int nData);

    void signalArrayExperiment(Op op, unsigned nTest, vector<Algo> testAlgos, bool shuffle);
    //-----------------------   FUNCTIONS FOR CREATE DISTRIBUTION, GENERATE DATA, AND EXPERIMENT USING THREAD
private:
    bool threadGenerateArray();

    bool threadRunArrayExperiment();





private:
    Ui::MainWindow *ui;

    QString getDistributionString();

    vector<double> getDistributionParams();
};
#endif // MAINWINDOW_H
