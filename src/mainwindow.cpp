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
                "D://",
                "All files (*.*);;Text File (*.txt)");

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
    }

    QTextStream in(&file);

    ui->txtBrowser_1->setText(in.readAll());
}


QString MainWindow::getDistributionString() {

    if (ui->tabDistribution->currentIndex() == 0)
    {
        QString U_str = "";
        QString N_str = "";
        QString Exp_str = "";
        QString G_str = "";

        if (ui->lEditPara_1->text().size() != 0 && ui->lEditPara_2->text().size() != 0)
            U_str.append("U(" + ui->lEditPara_1->text() + "," + ui->lEditPara_2->text() + ")");

        if (ui->lEditPara_3->text().size() != 0 && ui->lEditPara_4->text().size() != 0)
            N_str.append("N(" + ui->lEditPara_3->text() + "," + ui->lEditPara_4->text() + ")");

        if (ui->lEditPara_5->text().size() != 0)
            Exp_str.append("Exp(" + ui->lEditPara_5->text() + ")");

        if (ui->lEditPara_7->text().size() != 0 && ui->lEditPara_8->text().size() != 0)
            G_str.append("G(" + ui->lEditPara_7->text() + "," + ui->lEditPara_8->text() + ")");

        QStringList dist_list = (QStringList() << U_str << N_str << Exp_str << G_str);
        dist_list.removeAll("");

        return dist_list.join(" + ");
    }

    if (ui->tabDistribution->currentIndex() == 1)
        return ui->lEditEquation->text();

    return "";
}

vector<double> MainWindow::getDistributionParams() {
    vector<double> res;
    res.push_back(10000);
    res.push_back(-20);
    res.push_back(20);
}

void MainWindow::on_pButtonGen_clicked()
{
    try {
        qDebug() << "buttonGen clicked \n";

        QString distributionString = getDistributionString();
        vector<double> distributionParams = getDistributionParams();

        qDebug() << "reached here\n";
        Parser parser;
        qDebug() << "reached here2\n";
        try {
            parser = Parser((long long)distributionParams[0], distributionParams[1], distributionParams[2]);
        }
        catch (ParserException ex) {
            qDebug() << "Hello we're here";
            QMessageBox::information(this, "Error", ex.what());
            qDebug() << "messaged box is displayed\n";
            return;
        }

        qDebug() << "Hello raeched here\n";
        distribution = parser.string2dist(distributionString);

        if (!distribution.valid()) {
            QMessageBox::information(this, "Error", "Expression is invalid");
            return;
        }
    }
    catch (std::exception &ex) {
        qDebug() << "crashed here\n";
        QMessageBox::information(this, "Error", ex.what());
        return;
    }

    int nData = 10;
    int dataSize = 5;

    QString dataTypeStr = ui->cBoxDataType->currentText();
    DataType dataType;
    if (dataTypeStr=="Array") {
        dataType = ARRAY;
        ArrayGenerator arrayGenerator(distribution);
        arrayGenerator.generateArray(nData, arrData);
    }

    QMessageBox::information(this, "Warning", "Generate data successful");

    if (ui->rButtonSave->isChecked() == true)
    {
        if (ui->lEditSaveDir->text() == "")
        {
            QMessageBox::information(this, "Warning", "Save Directory is NOT set!");
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
                QString savefile = ui->lEditSaveDir->text() + format + ".array";
                bool fileSaveSuccess = utils::saveArray(savefile, arrData, 12);
                if (!fileSaveSuccess) {
                    QMessageBox::information(this, "Warning", "Can't save file. Please try again.");
                }
                else {
                    QMessageBox::information(this, "Warning", "File save successful");
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
                "D://",
                "All files (*.*);;Text File (*.txt)");

    qDebug() << "on button open file 2 \n";
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
    }

    QTextStream in(&file);

    ui->txtBrowser_2->setText(in.readAll());
}

void MainWindow::on_rButtonSave_clicked()
{
    qDebug() << " rButtonSave_clicked\n";
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
    qDebug() << "button run clicked\n";
    ui->outputText->clear();

    QString dataType = ui->cBoxDataType->currentText();                         // Read Data Type
    QString operationStr = ui->cBoxOperation->currentText();                       // Read operation
    QString matrixSize = ui->lEditMatSize->text();                              // Read Matrix Size

    QString dist_str;
    QString equation;

    QVector<QString> varpack;

    if (operationStr=="Sum") operation = ADD;

    testAlgos.clear();
    testAlgos.push_back(LINEAR);
    testAlgos.push_back(SPLIT_MERGE);
    testAlgos.push_back(SORT);
    testAlgos.push_back(SORT_APPEND);

    bool shuffle = 1;

    /* DataType & Operation */
    if (dataType == "Array")
    {
        if (arrData.size()==0) {
            QMessageBox::information(this, "Warning", "Can't save file. Please try again.");
            return;
        }

        ArrayExperiment arrExper;
        arrExper.experiment(arrData, operation, 5, testAlgos, shuffle, distribution);
    }    
}


