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
            QString format = now.toString("dd.MMM.yyyy-hhmmss");
            QString savefile = ui->lEditSaveDir->text() + format + ".txt";
            QFile file(savefile);

            if (!file.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::ReadWrite))
            {
            }

            if (file.open(QIODevice::ReadWrite))
            {
                QTextStream stream(&file);
                stream << "1_XYZ" << endl;
                stream << "2_XYZ" << endl;
            }
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
    }

    QTextStream in(&file);

    ui->txtBrowser_2->setText(in.readAll());
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
    QString operation = ui->cBoxOperation->currentText();                       // Read operation
    QString matrixSize = ui->lEditMatSize->text();                              // Read Matrix Size

    QString dist_str;
    QString equation;

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

    /* Distribution Tab */
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

    /* Calculation Dataset Tab */
    if (ui->tabCalcDataset->currentIndex() == 0)
    {
        varpack.append("0");
    }

    if (ui->tabCalcDataset->currentIndex() == 1)
    {
        varpack.append("0");
    }

    /* Packaging variables' value */
    for (int i = 0; i < varpack.size(); ++i)
        ui->outputText->append(varpack[i]);                                     // Value of the i-th variable
}


