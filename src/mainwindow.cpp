#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logconsole.h"
#include "ui_logconsole.h"
#include "figurewindow.h"
#include "ui_figurewindow.h"
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <QFileDialog>
#include <QVector>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , resource(1)
    , precision(PSINGLE)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    txtDisplay.push_back("\n1. Distribution\n");
    txtDisplay.push_back("2. Calculation Dataset\n");
    txtDisplay.push_back("3. Algorithm and Experiment setting\n");
    txtDisplay.push_back("4. Run and Save result\n");

    for (int i=0; i < txtDisplay.size(); ++i)
    {
        if (i == 0) ui->txtEditStackedWidgetPage->setTextColor(Qt::black); else ui->txtEditStackedWidgetPage->setTextColor(Qt::gray);
        ui->txtEditStackedWidgetPage->append(txtDisplay[i]);
    }

    ui->sWidget->setCurrentIndex(0);

    ui->lblMatSize->setVisible(false);
    ui->lEditMatSize->setVisible(false);

    for (int i=1; i<AlgoNameList.size(); i++)
        ui->cBoxAlgorithmList->addItem(algo2String(AlgoNameList[i]));

    for (int i=0; i<PrecisionList.size(); i++)
        ui->cBoxPrecisionList->addItem(prec2String(PrecisionList[i]));

    console = new LogConsole();
    console->setModal(false);
    console->show();
    console->activateWindow();

    figure = new FigureWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//-------------------   THREAD RESULTS HANDLER
//https://doc.qt.io/qt-5/qthread.html
void MainWindow::slotGenerateArrayFinish(const vector<double> &arr) {
    numData = arr.size();
    arrData = arr;
    createDataThread.quit();
    createDataThread.wait();
    QMessageBox::information(this, "Success", "Generate array data successful");
    console->getUI()->txtBrowserLog->append("Generate array data successful");
    slotUpdateProgress(100);
    resource.release(1);
}

void MainWindow::slotArrayExperimentFinish(const vector<Result> &res) {
    results = res;
    experimentThread.quit();
    experimentThread.wait();
    QMessageBox::information(this, "Success", "Array experiment successful");
    console->getUI()->txtBrowserLog->append("Array experiment successful");

    try {
            utils::outputFile("arrayResultAutosave.txt",results);
        }
        catch (std::exception ex) {
            qDebug() << "Array experiment output: " << ex.what() << "\n";
            QMessageBox::information(this, "Error", "Auto-save array results to file failed\n");
            console->getUI()->txtBrowserLog->append("Auto-save array results to file failed");
            return;
        }
    QMessageBox::information(this, "Success", "Auto-save array results to file successful");
    console->getUI()->txtBrowserLog->append("Auto-save array results to file successful");
    slotUpdateProgress(100);
    outputResult();
    resource.release(1);
}

void MainWindow::slotGenerateMatrixFinish(const vector<Matrix<double> > &mats) {
    numData = mats.size();
    matData = mats;
    createDataThread.quit();
    createDataThread.wait();
    QMessageBox::information(this, "Success", "Generate matrix data successful");
    console->getUI()->txtBrowserLog->append("Generate matrix data successful");
    slotUpdateProgress(100);
    resource.release(1);
}

void MainWindow::slotMatrixExperimentFinish(const vector<Result> &res) {
    results = res;
    experimentThread.quit();
    experimentThread.wait();
    QMessageBox::information(this, "Success", "Matrix experiment successful");
    console->getUI()->txtBrowserLog->append("Matrix experiment successful");

    try {
            utils::outputFile("matrixResultAutosave.txt",results);
        }
        catch (std::exception ex) {
            qDebug() << "Matrix experiment output: " << ex.what() << "\n";
            QMessageBox::information(this, "Error", "Auto-save matrix results to file failed\n");
            console->getUI()->txtBrowserLog->append("Auto-save matrix results to file failed");
            return;
        }
    QMessageBox::information(this, "Success", "Auto-save matrix results to file successful");
    console->getUI()->txtBrowserLog->append("Auto-save matrix results to file successful");
    slotUpdateProgress(100);
    outputResult();
    resource.release(1);
}

void MainWindow::slotParseDistributionFinish(const Distribution &parsedDistribution) {
    distribution = parsedDistribution;
    createDistributionThread.quit();
    createDistributionThread.wait();
    if (distribution.valid())
    {
        QMessageBox::information(this, "Success", "Create distribution successful");
        console->getUI()->txtBrowserLog->append("Create distribution successful");
    }
    else {
        QMessageBox::information(this, "Error", "Distribution expression is invalid");
        console->getUI()->txtBrowserLog->append("Distribution expression is invalid");
    }
    slotUpdateProgress(100);
    resource.release(1);
}

void MainWindow::slotReceiveAlert(QString alert) {
    QMessageBox::information(this, "Error", alert);
}

void MainWindow::slotUpdateProgress(int value) {
    console->getUI()->progBar->setValue(value);
}

//-------------------   FUNCTIONS TO START AND RUN NEW THREADS
// https://doc.qt.io/qt-5/qthread.html
bool MainWindow::threadGenerateArray() {
    slotUpdateProgress(0);
    if (numData <= 0)
        throw MainWindowException("MainWindow generateArray: numData <= 0");
    if (!distribution.valid())
        throw MainWindowException("MainWindow generateArray: distribution invalid");

    if (!resource.tryAcquire()) return false;

    ArrayGenerator *arrGen = new ArrayGenerator(distribution);
    arrGen->moveToThread(&createDataThread);
    connect(&createDataThread, &QThread::finished, arrGen, &QObject::deleteLater);
    connect(this, &MainWindow::signalGenerateArray, arrGen, &ArrayGenerator::slotGenerateArray);
    connect(arrGen, &ArrayGenerator::signalGenerateFinish, this, &MainWindow::slotGenerateArrayFinish);
    connect(arrGen, &ArrayGenerator::signalUpdateProgress, this, &MainWindow::slotUpdateProgress);

    createDataThread.start();

    emit signalGenerateArray(numData);

    return true;
}

bool MainWindow::threadRunArrayExperiment() {
    slotUpdateProgress(0);
    if (dataType!=ARRAY)
        throw MainWindowException("threadRunArrayExperiment: dataType != ARRAY");
    if (numData<=0)
        throw MainWindowException("threadRunArrayExperiment: numData<=0");
    if (!distribution.valid())
        throw MainWindowException("threadRunArrayExperiment: distribution invalid");

    if (!resource.tryAcquire()) return false;

    qDebug() << "thread run array: " << arrData.size() << "\n";
    ArrayExperimentController *arrExper = new ArrayExperimentController(arrData, distribution, precision);
    arrExper -> moveToThread(&experimentThread);
    connect(&experimentThread, &QThread::finished, arrExper, &QObject::deleteLater);
    connect(this, &MainWindow::signalArrayExperiment, arrExper, &ArrayExperimentController::slotRunArrayExperiment);
    connect(arrExper, &ArrayExperimentController::signalExperimentFinish, this, &MainWindow::slotArrayExperimentFinish);
    connect(arrExper, &ArrayExperimentController::signalUpdateProgress, this, &MainWindow::slotUpdateProgress);

    experimentThread.start();

    emit signalArrayExperiment(operation, numTest, testAlgos, shuffle);

    return true;
}

bool MainWindow::threadGenerateMatrix() {
    slotUpdateProgress(0);
    if (numData <= 0)
        throw MainWindowException("threadGenerateMatrix: numData <= 0");
    if (matSize <= 0)
        throw MainWindowException("threadGenerateMatrix: matSize <= 0");
    if (!distribution.valid())
        throw MainWindowException("threadGenerateMatrix: distribution invalid");

    if (!resource.tryAcquire()) return false;

    MatrixGenerator *matGen = new MatrixGenerator(distribution);
    matGen->moveToThread(&createDataThread);
    connect(&createDataThread, &QThread::finished, matGen, &QObject::deleteLater);
    connect(this, &MainWindow::signalGenerateMatrix, matGen, &MatrixGenerator::slotGenerateMatrix);
    connect(matGen, &MatrixGenerator::signalGenerateFinish, this, &MainWindow::slotGenerateMatrixFinish);
    connect(matGen, &MatrixGenerator::signalUpdateProgress, this, &MainWindow::slotUpdateProgress);

    createDataThread.start();

    emit signalGenerateMatrix(numData, matSize);

    return true;
}

bool MainWindow::threadRunMatrixExperiment() {
    slotUpdateProgress(0);
    if (dataType!=MATRIX)
        throw MainWindowException("threadRunMatrixExperiment: dataType != MATRIX");
    if (numData<=0)
        throw MainWindowException("threadRunMatrixExperiment: numData<=0");
    if (matSize<=0)
        throw MainWindowException("threadRunMatrixExperiment: numData<=0");
    if (!distribution.valid())
        throw MainWindowException("threadRunMatrixExperiment: distribution invalid");

    if (!resource.tryAcquire()) return false;

    MatrixExperimentController *matExper = new MatrixExperimentController(matData, distribution, precision);
    matExper -> moveToThread(&experimentThread);
    connect(&experimentThread, &QThread::finished, matExper, &QObject::deleteLater);
    connect(this, &MainWindow::signalMatrixExperiment, matExper, &MatrixExperimentController::slotRunMatrixExperiment);
    connect(matExper, &MatrixExperimentController::signalExperimentFinish, this, &MainWindow::slotMatrixExperimentFinish);
    connect(matExper, &MatrixExperimentController::signalUpdateProgress, this, &MainWindow::slotUpdateProgress);

    experimentThread.start();

    emit signalMatrixExperiment(operation, numTest, testAlgos, shuffle);

    return true;
}

bool MainWindow::threadParseDistribution() {
    slotUpdateProgress(0);

    if (!resource.tryAcquire()) return false;

    Parser *parser = new Parser(binNumber, lowerBound, upperBound);
    parser->moveToThread(&createDistributionThread);
    connect(&createDistributionThread, &QThread::finished, parser, &QObject::deleteLater);
    connect(this, &MainWindow::signalParseDistribution, parser, &Parser::slotParseDistribution);
    connect(parser, &Parser::signalParseFinish, this, &MainWindow::slotParseDistributionFinish);
    connect(parser, &Parser::signalUpdateProgress, this, &MainWindow::slotUpdateProgress);

    createDistributionThread.start();

    emit signalParseDistribution(getDistributionString());

    return true;
}


//--------------------  ON-CLICK LISTENER
void MainWindow::on_pButtonPrev_clicked()
{
    ui->txtEditStackedWidgetPage->clear();

    int currentIndex = ui->sWidget->currentIndex();
    int first = 0;

    for (int i=0; i < txtDisplay.size(); ++i)
    {
        if (currentIndex <= first+1) currentIndex = first+1;
        if (i == currentIndex-1) ui->txtEditStackedWidgetPage->setTextColor(Qt::black); else ui->txtEditStackedWidgetPage->setTextColor(Qt::gray);
        ui->txtEditStackedWidgetPage->append(txtDisplay[i]);
    }

    if (currentIndex > first)
        ui->sWidget->setCurrentIndex(currentIndex - 1);
    if (currentIndex <= first+1)
    {
        currentIndex = first+1;
        console->getUI()->txtBrowserLog->append("  Reached the first page");
    }
}

void MainWindow::on_pButtonNext_clicked()
{
    ui->txtEditStackedWidgetPage->clear();

    int currentIndex = ui->sWidget->currentIndex();
    int last = ui->sWidget->count()-1;

    for (int i=0; i < txtDisplay.size(); ++i)
    {
        if (currentIndex >= last-1) currentIndex = last-1;
        if (i == currentIndex+1) ui->txtEditStackedWidgetPage->setTextColor(Qt::black); else ui->txtEditStackedWidgetPage->setTextColor(Qt::gray);
        ui->txtEditStackedWidgetPage->append(txtDisplay[i]);
    }

    if (currentIndex < last)
        ui->sWidget->setCurrentIndex(currentIndex + 1);
    if (currentIndex >= last-1)
    {
        currentIndex = last-1;
        console->getUI()->txtBrowserLog->append("  Reached the last page");
    }
}

void MainWindow::on_cBoxDataType_currentIndexChanged(int index)
{
    ui->cBoxOperation->setCurrentIndex(0);

    int count = ui->cBoxOperation->count();

    qDebug() << "cBox data type count " << count << "\n";

    if (index == 0)
    {
        if (count > 2) ui->cBoxOperation->removeItem(2);
        ui->lblMatSize->setVisible(false);
        ui->lEditMatSize->setVisible(false);
    }
    if (index == 1)
    {
        ui->lEditMatSize->clear();
        if (count < 3) ui->cBoxOperation->insertItem(2, "Matmul");
        ui->lblMatSize->setVisible(true);
        ui->lEditMatSize->setVisible(true);
    }
}

void MainWindow::on_pButtonOpenFile_1_clicked()
{
    if (!resource.available()) {
        QMessageBox::information(this, "Error", "Another task is in progress. Please wait.");
        console->getUI()->txtBrowserLog->append("Another task is in progress. Please wait.");
        return;
    }

    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "All files (*.*);;Text File (*.txt)");

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, "Error", "File cannot be opened");
        console->getUI()->txtBrowserLog->append("File cannot be opened");
        return;
    }

    QTextStream in(&file);

    ui->txtBrowser_1->setText(in.readAll());

    file.close();
}

QString MainWindow::getDistributionString() {
    /* Distribution Tab */
    if (ui->tabDistribution->currentIndex() == 0)
    {
        QString U_str = "";
        QString N_str = "";
        QString Exp_str = "";
        QString G_str = "";

        if (ui->lEditParaU_a->text().size() != 0 && ui->lEditParaU_b->text().size() != 0)
            U_str.append("U(" + ui->lEditParaU_a->text() + "," + ui->lEditParaU_b->text() + ")");

        if (ui->lEditParaN_mean->text().size() != 0 && ui->lEditParaN_var->text().size() != 0)
            N_str.append("N(" + ui->lEditParaN_mean->text() + "," + ui->lEditParaN_var->text() + ")");

        if (ui->lEditParaExp_lambda->text().size() != 0)
            Exp_str.append("E(" + ui->lEditParaExp_lambda->text() + ")");

        QStringList dist_list = (QStringList() << U_str << N_str << Exp_str << G_str);
        dist_list.removeAll("");

        return dist_list.join(" + ");
    }

    if (ui->tabDistribution->currentIndex() == 1)
    {
        return ui->lEditEquation->text();
    }

    if (ui->tabDistribution->currentIndex() == 2)
    {
        return ui->txtBrowser_1->toPlainText();
    }

    return "";
}


vector<double> MainWindow::getDistributionParams() {
    vector<double> res;
    QString binNumberStr = ui->lEditBinNum->text();
    QString lowerBoundStr = ui->lEditLowerBound->text();
    QString upperBoundStr = ui->lEditUpperBound->text();

    bool valid1, valid2, valid3;
    long long binNumber = utils::str2double(binNumberStr, valid1);// (binNumberStr.toDouble(&valid1));
    double lowerBound = utils::str2double(lowerBoundStr, valid2); //lowerBoundStr.toDouble(&valid2);
    double upperBound = utils::str2double(upperBoundStr, valid3);//upperBoundStr.toDouble(&valid3);

    if (!valid1 || !valid2 || !valid3) return res; // return empty vector

    res.push_back(binNumber);
    res.push_back(lowerBound);
    res.push_back(upperBound);
    return res;
}

void MainWindow::on_pButtonCreateDistribution_clicked()
{
    if (!resource.available()) {
        QMessageBox::information(this, "Error", "Another task is in progress. Please wait.");
        console->getUI()->txtBrowserLog->append("Another task is in progress. Please wait.");

        return;
    }

    vector<double> distributionParams = getDistributionParams();
    if (distributionParams.size() != 3) {
        QMessageBox::information(this, "Error", "Invalid distribution parameters");
        console->getUI()->txtBrowserLog->append("Invalid distribution parameters");
        return;
    }

    if (!Parser::validParams(distributionParams[0], distributionParams[1], distributionParams[2])) {
        QMessageBox::information(this, "Error", "Invalid distribution parameters values");
        console->getUI()->txtBrowserLog->append("Invalid distribution parameters values");
        return;
    }

    binNumber = distributionParams[0];
    lowerBound = distributionParams[1];
    upperBound = distributionParams[2];
qDebug() << " Reached here\n";
    if (!threadParseDistribution()) {
        QMessageBox::information(this, "Error", "Another task is in progress. Please wait and try again");
        console->getUI()->txtBrowserLog->append("Another task is in progress. Please wait and try again");
        return;
    }
    else {
        QMessageBox::information(this, "Update", "Creating distribution is in progress");
        console->getUI()->txtBrowserLog->append("Creating distribution is in progress");
    }
}


void MainWindow::on_pButtonGen_clicked()
{
    qDebug() << "buttonGen clicked \n";
    if (!resource.available()) {
        QMessageBox::information(this, "Error", "Another task is in progress. Please wait.");
        console->getUI()->txtBrowserLog->append("Another task is in progress. Please wait.");
        return;
    }

    QString numDataStr = ui->lEditNumData->text();
    bool validNumData = false;
    numData = utils::str2double(numDataStr, validNumData); //numDataStr.toDouble(&validNumData);
    if (!validNumData || numData <= 0) {
        QMessageBox::information(this, "Error", "Invalid number of data element");
        console->getUI()->txtBrowserLog->append("Invalid number of data element");
        return;
    }

    if (!distribution.valid()) {
        QMessageBox::information(this, "Error", "Please create a distribution first");
        console->getUI()->txtBrowserLog->append("Please create a distribution first");
        return;
    }

    QString dataTypeStr = ui->cBoxDataType->currentText();
    if (dataTypeStr=="Matrix") {
        QString matSizeStr = ui->lEditMatSize->text();
        bool validMatSize;
        matSize = utils::str2double(matSizeStr, validMatSize); //matSizeStr.toDouble(&validMatSize);
        if (!validMatSize || matSize <= 0) {
            QMessageBox::information(this, "Error", "Invalid matrix size");
            console->getUI()->txtBrowserLog->append("Invalid matrix size");
            return;
        }
    }


    if (dataTypeStr=="Array") {
        dataType = ARRAY;
        ArrayGenerator arrayGenerator(distribution);

        if (!threadGenerateArray()) {
            QMessageBox::information(this, "Error", "Generate failed. Please try again");
            console->getUI()->txtBrowserLog->append("Generate failed. Please try again");
            return;

        }
        QMessageBox::information(this, "Update", "Generate array is in progress");
        console->getUI()->txtBrowserLog->append("Generate array is in progress");
    }
    else if (dataTypeStr=="Matrix") {
        dataType = MATRIX;
        MatrixGenerator matrixGenerator(distribution);
        if (!threadGenerateMatrix()) {
            QMessageBox::information(this, "Error", "Generate failed. Please try again");
            console->getUI()->txtBrowserLog->append("Generate failed. Please try again");
            return;
        }
        QMessageBox::information(this, "Update", "Generate array is in progress");
        console->getUI()->txtBrowserLog->append("Generate array is in progress");
    }
}

void MainWindow::on_pButtonSaveDataset_clicked()
{
    qDebug() << "buttonSaveDataset clicked\n";
    if (!resource.available()) {
        QMessageBox::information(this, "Error", "Another task is in progress. Please wait");
        console->getUI()->txtBrowserLog->append("Another task is in progress. Please wait");
        return;
    }

    if (arrData.size() == 0 && matData.size() == 0) {
        QMessageBox::information(this, "Error", "No dataset to save");
        return;
    }

    if (ui->lEditSaveDir->text() == "")
    {
        QMessageBox::information(this, "Error", "Save Directory is NOT set!");
        console->getUI()->txtBrowserLog->append("Save Directory is NOT set!");
        return;
    }
    else
    {
        // Save to Dir
        QDateTime now = QDateTime::currentDateTime();
        QString format = now.toString("dd.MMM.yyyy-hhmmss");
        QString savefile = ui->lEditSaveDir->text() + format + ".txt";

        if (dataType==ARRAY) {
            if (arrData.size()==0) {
                QMessageBox::information(this, "Error", "No array dataset to save");
                return;
            }
            console->getUI()->txtBrowserLog->append("Start saving array dataset.");

            QString savefile = ui->lEditSaveDir->text() + "/" + format + ".array";
            bool fileSaveSuccess = utils::saveArray(savefile, arrData, 12);
            if (!fileSaveSuccess) {
                QMessageBox::information(this, "Error", "Can't save array to file. Please try again.");
                console->getUI()->txtBrowserLog->append("Can't save array to file. Please try again.");
            }
            else {
                QMessageBox::information(this, "Success", "File save array successful");
                console->getUI()->txtBrowserLog->append("File save array successful");
            }
        }
        else {
            if (matData.size()==0) {
                QMessageBox::information(this, "Error", "No matrix dataset to save!");
                return;
            }
            console->getUI()->txtBrowserLog->append("Start saving matrix dataset.");

            QString savefile = ui->lEditSaveDir->text() + "/" + format + ".matrix";
            bool fileSaveSuccess = utils::saveMatrix(savefile, matData, 12);
            if (!fileSaveSuccess) {
                QMessageBox::information(this, "Error", "Can't save matrix file. Please try again.");
                console->getUI()->txtBrowserLog->append("Can't save matrix file. Please try again.");
            }
            else {
                QMessageBox::information(this, "Success", "File save matrix successful");
                console->getUI()->txtBrowserLog->append("File save matrix successful");
            }
        }
    }

}

void MainWindow::on_pButtonOpenFile_2_clicked()
{
    if (!resource.available()) {
        QMessageBox::information(this, "Error", "Another task is in progress. Please wait");
        console->getUI()->txtBrowserLog->append("Another task is in progress. Please wait");
        return;
    }

    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "All files (*.*);;Text File (*.txt)");

    if (!filename.contains(".array") && !filename.contains(".matrix")) {
        QMessageBox::information(this, "Error", "Invalid file format. Must be .array or .matrix file");
        console->getUI()->txtBrowserLog->append("Invalid file format. Must be .array or .matrix file");
        ui->txtBrowser_2->setText("Invalid file format");
        return;
    }

    QString dataTypeStr = ui->cBoxDataType->currentText();
    if (dataTypeStr=="Array") dataType = ARRAY;
    else if (dataTypeStr=="Matrix") dataType = MATRIX;

    if ((dataType==ARRAY && filename.contains(".matrix"))
            || (dataType==MATRIX && filename.contains(".array"))) {
        QMessageBox::information(this, "Error", "File has wrong data type");
        console->getUI()->txtBrowserLog->append("File has wrong data type");
        ui->txtBrowser_2->setText("File has wrong data type");
        return;
    }

    std::ifstream fin;

    fin = std::ifstream(filename.toStdString().c_str());
    if (!fin.is_open()) {
        QMessageBox::information(this, "Error", "File cannot be opened");
        console->getUI()->txtBrowserLog->append("File cannot be opened");
        ui->txtBrowser_2->setText("File cannot be opened");
        return;
    }

    ui->txtBrowser_2->setText("Importing file...");
    try {
        if (dataType==ARRAY) {
            console->getUI()->txtBrowserLog->append("Start loading array dataset.");
            fin >> numData;
            arrData.clear();
            for (unsigned i=0; i<numData; i++) {
                double val;
                fin >> val;
                arrData.push_back(val);
            }
            fin.close();
        }
        else if (dataType==MATRIX) {
            console->getUI()->txtBrowserLog->append("Start loading matrix dataset.");
            fin >> numData >> matSize >> matSize;
            matData.clear();
            Matrix<double> currentMat(matSize, matSize);
            for (unsigned i=0; i<numData; i++) {
                for (unsigned t=0; t<matSize*matSize; t++) fin >> currentMat[i];
                matData.push_back(currentMat);
            }
            fin.close();
        }
    }
    catch (...) {
        QMessageBox::information(this, "Error", "File cannot be read or corrupted");
        console->getUI()->txtBrowserLog->append("File cannot be read or corrupted");
        ui->txtBrowser_2->setText("File cannot be read or corrupted");
        fin.close();
        return;
    }

    ui->txtBrowser_2->setText("Data imported successfully!");
}

void MainWindow::on_pButtonAddAlgo_clicked()
{
    if (ui->cBoxAlgorithmSelected->findText(ui->cBoxAlgorithmList->currentText()) == -1) {
        QString selectedAlgo = ui->cBoxAlgorithmList->currentText();
        ui->cBoxAlgorithmSelected->addItem(selectedAlgo);
    }
    ui->cBoxAlgorithmSelected->update();
}

void MainWindow::on_pButtonRemoveAlgo_clicked()
{
    ui->cBoxAlgorithmSelected->removeItem(ui->cBoxAlgorithmSelected->currentIndex());
    ui->cBoxAlgorithmSelected->update();
}



void MainWindow::on_pButtonBrowseDir_clicked()
{
    if (!resource.available()) {
        QMessageBox::information(this, "Error", "Another task is in progress. Please wait.");
        console->getUI()->txtBrowserLog->append("Another task is in progress. Please wait.");
        return;
    }

    QString folderDir = QFileDialog::getExistingDirectory(
                this,
                tr("Open Directory"),
                qApp->applicationDirPath(),
                QFileDialog::ShowDirsOnly);

    ui->lEditSaveDir->setText(folderDir);
}

void MainWindow::on_pButtonBrowseSaveResult_clicked()
{
    if (!resource.available()) {
        QMessageBox::information(this, "Error", "Another task is in progress. Please wait.");
        console->getUI()->txtBrowserLog->append("Another task is in progress. Please wait.");
        return;
    }

    QString folderDir = QFileDialog::getExistingDirectory(
                this,
                tr("Open Directory"),
                qApp->applicationDirPath(),
                QFileDialog::ShowDirsOnly);

    ui->lEditSaveResult->setText(folderDir);
}

void MainWindow::on_pButtonRun_clicked()
{
    if (!resource.available()) {
        QMessageBox::information(this, "Error", "Another task is in progress. Please wait.");
        console->getUI()->txtBrowserLog->append("Another task is in progress. Please wait.");
        return;
    }

    ui->txtBrowserOutput->clear();

    if (numData <= 0) {
        QMessageBox::information(this, "Error", "Number of data element <= 0");
        console->getUI()->txtBrowserLog->append("Number of data element <= 0");
        return;
    }

    if (!distribution.valid()) {
        QMessageBox::information(this, "Error", "Please create a distribution first");
        console->getUI()->txtBrowserLog->append("Please create a distribution first");
        return;
    }
    qDebug() << "after distribution";

    QString numTestStr = ui->lEditNumTest->text();
    bool validNumTest;
    numTest = utils::str2double(numTestStr, validNumTest); //numTestStr.toDouble(&validNumTest);
    if (!validNumTest || numTest <= 0) {
        QMessageBox::information(this, "Error", "Invalid number of test");
        console->getUI()->txtBrowserLog->append("Invalid number of test");
        return;
    }

    if (ui->chkBoxGenNewData->isChecked()) shuffle = false; else shuffle = true;

    testAlgos.clear();

    for (int i=0; i<ui->cBoxAlgorithmSelected->count(); i++)
        testAlgos.push_back(string2Algo(ui->cBoxAlgorithmSelected->itemText(i)));

    if (testAlgos.empty()) {
        QMessageBox::information(this, "Error", "Please select some algorithms");
        console->getUI()->txtBrowserLog->append("Please select some algorithms");
        return;
    }
    qDebug() << "after testAlgos";

    QString operationStr = ui->cBoxOperation->currentText();
    if (operationStr=="Sum") operation = ADD;
    else if (operationStr=="Multiplication") operation = MUL;
    else if (operationStr=="Matmul") operation = MATMUL;

    qDebug() << "after operation";

    results.clear();

    if (dataType==ARRAY) {
        threadRunArrayExperiment();
        QMessageBox::information(this, "Update", "Array experiment is in progress");
        console->getUI()->txtBrowserLog->append("Array experiment is in progress");
    }
    else {
        threadRunMatrixExperiment();
        QMessageBox::information(this, "Update", "Matrix experiment is in progress");
        console->getUI()->txtBrowserLog->append("Matrix experiment is in progress");
    }
}

void MainWindow::on_pButtonSaveResult_clicked()
{
    if (!resource.available()) {
        QMessageBox::information(this, "Error", "Auto-save matrix results to file failed\n");
        console->getUI()->txtBrowserLog->append("Auto-save matrix results to file failed");
    }

    if (results.size() <= 2) {
        QMessageBox::information(this, "Error", "There is no result to save");
        console->getUI()->txtBrowserLog->append("There is no result to save");
        return;
    }

    QString folder = ui->lEditSaveResult->text();

    QDateTime now = QDateTime::currentDateTime();
    QString format = now.toString("dd.MMM.yyyy-hhmmss");
    QString savefile = folder + "/result" + format + ".csv";

    try {
            console->getUI()->txtBrowserLog->append("Start saving result.");
            utils::outputFile(savefile,results);
        }
        catch (std::exception ex) {
            qDebug() << "Matrix experiment output: " << ex.what() << "\n";
            QMessageBox::information(this, "Error", "Save current results to file failed");
            console->getUI()->txtBrowserLog->append("Save current results to file failed");
            return;
        }
    QMessageBox::information(this, "Success", "Save current results to file " + savefile + " successful");
    console->getUI()->txtBrowserLog->append("Save current results to file " + savefile + " successful");
}

void MainWindow::outputResult()
{
    qDebug() << "outputting result\n";
    if (results.size() <= 0)
        throw MainWindowException("outputResult: no result to output");

    QString outputStr = "3 numbers are: mean, variance, standard deviation\n";

    vector<QString> algoNames;
    vector<AlgoName> algoTypes;
    std::map<AlgoName, bool> mp;

    int n = results.size();
    for (int i=0; i<n;i++) {
        if (!mp[results[i].algoUsed] && results[i].algoUsed!=GROUND_TRUTH) {
            mp[results[i].algoUsed] = 1;

            algoTypes.push_back(results[i].algoUsed);
            algoNames.push_back(algo2String(results[i].algoUsed));
        }
    }

    for (unsigned t=0; t<algoTypes.size(); t++) {
        iFloat mean = 0;
        int nSample = 0;

        outputStr = outputStr + algo2String(algoTypes[t]) + " ";
        for (unsigned i=0; i<results.size(); i++)
            if (results[i].algoUsed==algoTypes[t]) {
                mean = mean + results[i].value;
                nSample++;
            }
        mean = mean / nSample;

        iFloat variance = 0;
        for (unsigned i=0; i<results.size(); i++)
            if (results[i].algoUsed==algoTypes[t]) {
                iFloat dX = (results[i].value - mean);
                variance = variance + dX*dX;
            }
        variance = variance / nSample;

        iFloat std = utils::isqrt(variance);

        outputStr = outputStr + mean.toString() + " " + variance.toString() + " " + std.toString();
        outputStr += "\n";
    }

    ui->txtBrowserOutput->setText(outputStr);
}

void MainWindow::on_pButtonLogConsole_clicked()
{
    console->setModal(false);
    console->show();
    console->activateWindow();
}

void MainWindow::on_pButtonPlot_clicked()
{    
    long long psize = distribution.getPdfSize();

    if (psize == 0)
    {
        QMessageBox::information(this, "Error", "No Distribution was ever created!");
        console->getUI()->txtBrowserLog->append("No Distribution was ever created!");
        return;
    }

    figure->setModal(false);

    /* Toy data to test plot */
    QVector<double> data(binNumber); //data(psize);

    for (long long i = 0; i<binNumber; ++i)
    {
        data[i] = distribution.getPdf(i).getValue().convert_to<double>()*1000;
    }

    //qDebug() << psize << " " << data.size();

    /* Real data goes here */

    figure->FigurePlot(binNumber,data);          // Tested plot upto 100000 points
    figure->show();
    figure->activateWindow();
}
