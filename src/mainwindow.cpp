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
    ui->cBoxAlgorithm->setCurrentIndex(0);

    int count = ui->cBoxAlgorithm->count();

    if (count == 3)
    {
        if (index == 1)
        {
            ui->cBoxAlgorithm->removeItem(2);
            ui->lblMatSize->setVisible(true);
            ui->lEditMatSize->setVisible(true);
        }
    }
    else
    {
        if (index < 1)
        {
            ui->cBoxAlgorithm->insertItem(2, "Element-wise multiplication");
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

void MainWindow::on_pButtonRun_clicked()
{
    ui->outputText->clear();

    QString dataType = ui->cBoxDataType->currentText();                         // Read Data Type
    QString algorithm = ui->cBoxAlgorithm->currentText();                       // Read Algorithm
    QString matrixSize = ui->lEditMatSize->text();                              // Read Matrix Size

    QString dist_str;
    QString equation;

    QVector<QString> varpack;

    if (dataType == "Array")
    {
        // TO-DO
    }

    if (dataType == "Matrix")
    {
        // TO-DO
    }

    if (algorithm == "Sum")
    {
        // TO-DO
    }

    if (algorithm == "Multiplication")
    {
        // TO-DO
    }

    if (algorithm == "Element-wise multiplication")
    {
        // TO-DO
    }

    varpack.append(dataType);
    varpack.append(algorithm);
    varpack.append(matrixSize);

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

    varpack.append(ui->txtBrowser_2->toPlainText());

    for (int i = 0; i < varpack.size(); ++i)
        ui->outputText->append(varpack[i]);                                     // Value of the i-th variable
}
