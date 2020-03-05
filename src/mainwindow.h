#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <parser.h>
#include <arraygenerator.h>
#include <matrixgenerator.h>
#include <arrayexperimentcontroller.h>
#include <matrixexperimentcontroller.h>
#include <vector>
#include <QThread>
#include <parser.h>
#include <QSemaphore>
#include <logconsole.h>

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


    unsigned dataSize, numData, matSize;
    DataType dataType;
    Distribution distribution;
    long long binNumber;
    double lowerBound, upperBound;
    vector<double> arrData;    
    vector<Matrix<double> > matData;

    Precision precision;
    Op operation;
    vector<Algo> testAlgos;
    unsigned numTest;
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

    void on_pButtonBrowseSaveResult_clicked();

    void on_gBoxAlgorithm_clicked();

    void on_pButtonRun_clicked();

    void on_pButtonSaveDataset_clicked();

    void on_pButtonCreateDistribution_clicked();

    void on_pButtonSaveResult_clicked();

    void on_pButtonLogConsole_clicked();

    //-----------------------   SIGNAL AND SLOTS FOR THREADS
private slots:
    void slotGenerateArrayFinish(const vector<double>& arr);

    void slotArrayExperimentFinish(const vector<Result> &res);

    void slotGenerateMatrixFinish(const vector<Matrix<double> > &mats);

    void slotMatrixExperimentFinish(const vector<Result> &res);

    void slotParseDistributionFinish(const Distribution &distribution);

    void slotReceiveAlert(QString alert);

    void slotUpdateProgress(int value);
signals:
    void signalGenerateArray(int nData);

    void signalArrayExperiment(Op op, unsigned numTest, vector<Algo> testAlgos, bool shuffle);

    void signalGenerateMatrix(int nData, int matSize);

    void signalMatrixExperiment(Op op, unsigned numTest, vector<Algo> testAlgos, bool shuffle);

    void signalParseDistribution(QString distStr);

    //-----------------------   FUNCTIONS FOR CREATE DISTRIBUTION, GENERATE DATA, AND EXPERIMENT USING THREAD
private:
    bool threadGenerateArray();

    bool threadRunArrayExperiment();

    bool threadGenerateMatrix();

    bool threadRunMatrixExperiment();

    bool threadParseDistribution();

    void outputResult();
private:
    Ui::MainWindow *ui;
    LogConsole *console;

    QString getDistributionString();

    vector<double> getDistributionParams();
};
#endif // MAINWINDOW_H
