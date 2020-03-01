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
        return;
    }

    QTextStream in(&file);

    ui->txtBrowser_1->setText(in.readAll());
}

void MainWindow::on_pButtonGen_clicked()
{
    if (ui->rButtonSave->isChecked() == true)
    {
        if (ui->lEditSaveDir->text() == "")
        {
            QMessageBox::information(this, "Warning", "Save Directory has NOT set!");
            return;
        }
        else
        {
            // Do randomly generated

            // Save to Dir
            QDateTime now = QDateTime::currentDateTime();
            QString format = now.toString("dd MMM yyyy - hh mm ss");
            QString savefile = ui->lEditSaveDir->text() + format + ".txt";
            QFile file(savefile);

            if (!file.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::ReadWrite))
            {
                return;
            }

            if (file.open(QIODevice::ReadWrite))
            {
            }

            QTextStream out(&file);
            out << "1 - abc" << endl;
            out << "2 - def" << endl;
        }
    }
    else
    {
        // Do randomly generated


    }

    for (int i=0; i<1000; ++i)
    {
        // TO-DO

        ui->progBar->setValue(int((i+1)/10));
    }
}

void MainWindow::on_pButtonOpenFile_2_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "D://",
                "All files (*.*);;Text File (*.txt)");

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        ui->txtBrowser_2->setText("Failed to import file...");
        return;
    }

    QTextStream in(&file);

    ui->txtBrowser_2->setText("Imported Successfully!");
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
            Exp_str.append("Exp(" + ui->lEditParaExp_lambda->text() + ")");

        if (ui->lEditParaG_alpha->text().size() != 0 && ui->lEditParaG_lambda->text().size() != 0)
            G_str.append("G(" + ui->lEditParaG_alpha->text() + "," + ui->lEditParaG_lambda->text() + ")");

        QStringList dist_list = (QStringList() << U_str << N_str << Exp_str << G_str);
        dist_list.removeAll("");
        dist_str = dist_list.join(" + ");

        varpack.append(dist_str);
    }

    if (ui->tabDistribution->currentIndex() == 1)
    {
        equation = ui->lEditEquation->text();
        varpack.append(equation);
    }

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

    /* Packaging variables' value */
    for (int i = 0; i < varpack.size(); ++i)
        ui->outputText->append(varpack[i]);                                     // Value of the i-th variable
}

