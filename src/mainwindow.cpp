#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <QFileDialog>
#include <QVector>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)    
    , resource(1)
    , distribution(0,0,0)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lblMatSize->setVisible(false);
    ui->lEditMatSize->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//-------------------   THREAD RESULTS HANDLER
void MainWindow::slotGenerateArrayFinish(const vector<double> &arr) {
    numData = arr.size();
    arrData = arr;
    createDataThread.quit();
    createDataThread.wait();
    QMessageBox::information(this, "Success", "Generate data successful");
    resource.release(1);        
}

void MainWindow::slotArrayExperimentFinish(const vector<Result> &res) {
    results = res;
    experimentThread.quit();
    experimentThread.wait();
    QMessageBox::information(this, "Success", "Array experiment successful");
    resource.release(1);

    try {
            BaseExperiment::staticOutputFile("arrResult.txt",results);
        }
        catch (std::exception ex) {
            qDebug() << "Array experiment output: " << ex.what() << "\n";
            QMessageBox::information(this, "Error", "Save results to file failed\n");
            return;
        }
        QMessageBox::information(this, "Success", "Save results to file successful");
}


//-------------------   FUNCTIONS TO START AND RUN NEW THREADS
bool MainWindow::threadGenerateArray() {
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

    createDataThread.start();

    emit signalGenerateArray(numData);
}

bool MainWindow::threadRunArrayExperiment() {
    if (dataType!=ARRAY)
        throw MainWindowException("threadRunArrayExperiment: dataType != ARRAY");
    if (numData<=0)
        throw MainWindowException("threadRunArrayExperiment: numData<=0");
    if (!distribution.valid())
        throw MainWindowException("threadRunArrayExperiment: distribution invalid");

    if (!resource.tryAcquire()) return false;

    ArrayExperiment *arrExper = new ArrayExperiment(arrData, distribution);
    arrExper -> moveToThread(&experimentThread);
    connect(&experimentThread, &QThread::finished, arrExper, &QObject::deleteLater);
    connect(this, &MainWindow::signalArrayExperiment, arrExper, &ArrayExperiment::slotRunArrayExperiment);
    connect(arrExper, &ArrayExperiment::signalExperimentFinish, this, &MainWindow::slotArrayExperimentFinish);

    experimentThread.start();

    emit signalArrayExperiment(operation, nTest, testAlgos, shuffle);
}

void MainWindow::on_cBoxDataType_currentIndexChanged(int index)
{
    ui->cBoxOperation->setCurrentIndex(0);

    int count = ui->cBoxOperation->count();

    if (count == 3)
    {
        if (index == 1)
        {
            ui->cBoxOperation->removeItem(2);
            ui->lblMatSize->setVisible(true);
            ui->lEditMatSize->setVisible(true);
        }
    }
    else
    {
        if (index < 1)
        {
            ui->lEditMatSize->clear();
            ui->cBoxOperation->insertItem(2, "Element-wise multiplication");
            ui->lblMatSize->setVisible(false);
            ui->lEditMatSize->setVisible(false);
        }
    }
}

void MainWindow::on_pButtonOpenFile_1_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "All files (*.*);;Text File (*.txt)");

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, "Error", "File cannot be opened");
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

        if (ui->lEditParaG_alpha->text().size() != 0 && ui->lEditParaG_lambda->text().size() != 0)
            G_str.append("G(" + ui->lEditParaG_alpha->text() + "," + ui->lEditParaG_lambda->text() + ")");

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
    long long binNumber = (long long)(binNumberStr.toDouble(&valid1));
    double lowerBound = lowerBoundStr.toDouble(&valid2);
    double upperBound = upperBoundStr.toDouble(&valid3);

    if (!valid1 || !valid2 || !valid3) return res;

    res.push_back(binNumber);
    res.push_back(lowerBound);
    res.push_back(upperBound);
    return res;
}

void MainWindow::on_pButtonGen_clicked()
{
    qDebug() << "buttonGen clicked \n";
    if (!resource.available()) {
        QMessageBox::information(this, "Error", "Another task is in progress. Please wait.");
        return;
    }

    QString numDataStr = ui->lEditNumData->text();
    bool validNumData;
    numData = numDataStr.toDouble(&validNumData);
    if (!validNumData || numData <= 0) {
        QMessageBox::information(this, "Error", "Invalid number of data element");
        return;
    }

    vector<double> distributionParams = getDistributionParams();
    if (distributionParams.size() != 3) {
        QMessageBox::information(this, "Error", "Invalid distribution parameters");
        return;
    }

    if (!Parser::validParams(distributionParams[0], distributionParams[1], distributionParams[2])) {
        QMessageBox::information(this, "Error", "Invalid distribution parameters values");
        return;
    }

    Parser parser(distributionParams[0], distributionParams[1], distributionParams[2]);

    QString distributionString = getDistributionString();
    distribution = parser.string2dist(distributionString);

    if (!distribution.valid()) {
        QMessageBox::information(this, "Error", "Distribution expression is invalid");
        return;
    }

    QString dataTypeStr = ui->cBoxDataType->currentText();
    if (dataTypeStr=="Array") {
        dataType = ARRAY;
        ArrayGenerator arrayGenerator(distribution);
        threadGenerateArray();
        QMessageBox::information(this, "Update", "Generate array is in progress");
    }

}

void MainWindow::on_pButtonSaveDataset_clicked()
{
    if (!resource.available()) {
        QMessageBox::information(this, "Error", "Another task is in progress. Please wait");
        return;
    }

    if (ui->lEditSaveDir->text() == "")
    {
        QMessageBox::information(this, "Error", "Save Directory is NOT set!");
        return;
    }
    else
    {
        // Save to Dir
        QDateTime now = QDateTime::currentDateTime();
        QString format = now.toString("dd.MMM.yyyy-hhmmss");
        QString savefile = ui->lEditSaveDir->text() + format + ".txt";
        QFile file(savefile);


        if (dataType==ARRAY) {
            QString savefile = ui->lEditSaveDir->text() + "/" + format + ".array";
            bool fileSaveSuccess = utils::saveArray(savefile, arrData, 12);
            if (!fileSaveSuccess) {
                QMessageBox::information(this, "Error", "Can't save file. Please try again.");
            }
            else {
                QMessageBox::information(this, "Success", "File save successful");
            }
        }
    }
}

void MainWindow::on_pButtonOpenFile_2_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://",
                "All files (*.*);;Text File (*.txt)");

    if (!filename.contains(".array") && !filename.contains(".matrix")) {
        QMessageBox::information(this, "Error", "Invalid file format. Must be .array or .matrix file");
        ui->txtBrowser_2->setText("Invalid file format");
        return;
    }

    QString dataTypeStr = ui->cBoxDataType->currentText();
    if (dataTypeStr=="Array") dataType = ARRAY;
    else if (dataTypeStr=="Matrix") dataType = MATRIX;

    if ((dataType==ARRAY && filename.contains(".matrix"))
            || (dataType==MATRIX && filename.contains(".array"))) {
        QMessageBox::information(this, "Error", "File has wrong data type");
        ui->txtBrowser_2->setText("File has wrong data type");
        return;
    }

    std::ifstream fin;

    fin = std::ifstream(filename.toStdString().c_str());
    if (!fin.is_open()) {
        QMessageBox::information(this, "Error", "File cannot be opened");
        ui->txtBrowser_2->setText("File cannot be opened");
        return;
    }

    try {
        if (dataType==ARRAY) {
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
            qDebug() << "Need to code import file for matrix\n";
        }
    }
    catch (...) {
        QMessageBox::information(this, "Error", "File cannot be read or corrupted");
        ui->txtBrowser_2->setText("File cannot be read or corrupted");
        fin.close();
        return;
    }

    ui->txtBrowser_2->setText("Data imported successfully!");
}

void MainWindow::on_rButtonSave_clicked()
{
    ui->progBar->setValue(0);
    ui->lEditSaveDir->setEnabled(true);
    ui->pButtonBrowseDir->setEnabled(true);
}

void MainWindow::on_pButtonBrowseDir_clicked()
{
    QString folderDir = QFileDialog::getExistingDirectory(
                this,
                tr("Open Directory"),
                qApp->applicationDirPath(),
                QFileDialog::ShowDirsOnly);

    ui->lEditSaveDir->setText(folderDir);
}

void MainWindow::on_rButtonDontSave_clicked()
{
    ui->lEditSaveDir->clear();
    ui->lEditSaveDir->setEnabled(false);
    ui->pButtonBrowseDir->setEnabled(false);
}

void MainWindow::on_gBoxAlgorithm_clicked()
{

}

void MainWindow::on_pButtonRun_clicked()
{
    ui->outputText->clear();


    nTest = 10;
    if (ui->chkBoxGenNewData->isChecked()) shuffle = false; else shuffle = true;

    if (!distribution.valid()) {
        QMessageBox::information(this, "Error", "Please create a distribution first");
        return;
    }
    qDebug() << "after distribution";

    testAlgos.clear();
    if (ui->chkBoxLinear->isChecked()) testAlgos.push_back(LINEAR);
    if (ui->chkBoxSplitMerge->isChecked()) testAlgos.push_back(SPLIT_MERGE);
    if (ui->chkBoxSortLinear->isChecked()) testAlgos.push_back(SORT);
    if (ui->chkBoxSortAppend->isChecked()) testAlgos.push_back(SORT_APPEND);

    if (testAlgos.empty()) {
        QMessageBox::information(this, "Error", "Please select some algorithms");
        return;
    }
    qDebug() << "after testAlgos";

    results.clear();

    QString operationStr = ui->cBoxOperation->currentText();
    if (operationStr=="Sum") operation = ADD;
    else if (operationStr=="Multiplication") operation = MUL;
    else if (operationStr=="Matmul") operation = MATMUL;
    qDebug() << "after operation";

    if (dataType==ARRAY) {
        ArrayExperiment arrExperiment(arrData, distribution);
        threadRunArrayExperiment();
        QMessageBox::information(this, "Update", "Array experiment is in progress");
    }
}



