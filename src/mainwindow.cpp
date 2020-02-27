#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <QFileDialog>
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

    QString equation = ui->lEditEquation->text();

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

    ui->outputText->append(dataType);
    ui->outputText->append(algorithm);
    ui->outputText->append(matrixSize);

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

        QStringList Dist_list = (QStringList() << U_str << N_str << Exp_str << G_str);
        Dist_list.removeAll("");
        QString Dist_str = Dist_list.join(" + ");

        ui->outputText->append(Dist_str);
    }

    if (ui->tabDistribution->currentIndex() == 1)
    {
        QString equation = ui->lEditEquation->text();
        ui->outputText->append(equation);
    }

    if (ui->tabDistribution->currentIndex() == 2)
        ui->outputText->append(ui->txtBrowser_1->toPlainText());

    ui->outputText->append(ui->txtBrowser_2->toPlainText());
}
