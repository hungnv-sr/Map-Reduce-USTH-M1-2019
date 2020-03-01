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
        qDebug() << "reached here\n";
        try {
            arrayGenerator.generateArray(numData, arrData);
            ui->progBar->setValue((int)(arrData.size()/numData)*100);
        }
        catch (SamplingException ex) {
            QMessageBox::information(this, "Error", "Distribution caused underflow. Decrease lower bound and increase upper bound");
            arrData.clear();
            return;
        }
    }

    QMessageBox::information(this, "Success", "Generate data successful");


    if (ui->rButtonSave->isChecked() == true)
    {
        if (ui->lEditSaveDir->text() == "")
        {
            QMessageBox::information(this, "Error", "Save Directory is NOT set!");
            return;
        }
        else
        {
            // Do randomly generated

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
    ui->progBar->setValue(0);
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

    QString dataType = ui->cBoxDataType->currentText();                         // Read Data Type
    QString operation = ui->cBoxOperation->currentText();                       // Read Operation
    QString matrixSize = ui->lEditMatSize->text();                              // Read Matrix Size
    QString numData = ui->lEditNumData->text();                                 // Read Number of Data

    QString dist_str;
    QString equation;

    QString algo_str;

    QVector<QString> varpack;

    /* DataType & Operation */
    if (dataType == "Array")
    {
        // TO-DO
    }

    if (dataType == "Matrix")
    {
        // TO-DO
    }

    if (operation == "Sum")
    {
        // TO-DO
    }

    if (operation == "Multiplication")
    {
        // TO-DO
    }

    if (operation == "Element-wise multiplication")
    {
        // TO-DO
    }

    varpack.append(dataType);
    varpack.append(operation);
    varpack.append(matrixSize);
    varpack.append(numData);


    if (ui->tabDistribution->currentIndex() == 2)
        varpack.append(ui->txtBrowser_1->toPlainText());

    /* Set Bin Number - Lower Bound - Upper Bound */
    QString binNumber = ui->lEditBinNum->text();
    QString lowerBound = ui->lEditLowerBound->text();
    QString upperBound = ui->lEditUpperBound->text();

    varpack.append(binNumber + " " + lowerBound + " " + upperBound);

    /* Calculation Dataset Tab */
    if (ui->tabCalcDataset->currentIndex() == 0)
    {
        if (ui->lEditSaveDir->text() == "")
            varpack.append("No direction found");

        if (ui->lEditSaveDir->text() != "")
            varpack.append("Dataset stored at " + ui->lEditSaveDir->text());
    }

    if (ui->tabCalcDataset->currentIndex() == 1)
    {
        varpack.append("0");
    }

    /* Algorithm */
    QStringList algo_list;

    if (ui->chkBoxLinear->isChecked()) algo_list.append("0 - Linear");
    if (ui->chkBoxSplitMerge->isChecked()) algo_list.append("1 - Split/Merge");
    if (ui->chkBoxSortLinear->isChecked()) algo_list.append("2 - Sort [Linear]");
    if (ui->chkBoxSortAppend->isChecked()) algo_list.append("3 - Sort [Append]");
    algo_str = algo_list.join("; ");

    varpack.append(algo_str);

    /*  */
    if (ui->chkBoxGenNewData->isChecked())
        varpack.append("New Dataset [ON]");
    else varpack.append("New Dataset [OFF]");

    /* Packaging variables' value */
    for (int i = 0; i < varpack.size(); ++i)
        ui->outputText->append(varpack[i]);                                     // Value of the i-th variable
}


