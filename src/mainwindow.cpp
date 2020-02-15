#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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

    QString dataType = ui->cBoxDataType->currentText();         // Read Data Type
    QString algorithm = ui->cBoxAlgorithm->currentText();       // Read Algorithm
    QString matrixSize = ui->lEditMatSize->text();              // Read Matrix Size

    if (dataType == "(default)" || dataType == "Array")
    {
        // TO-DO
    }

    if (dataType == "Matrix")
    {
        // TO-DO
    }

    if (algorithm == "(default)" || algorithm == "Sum")
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

    float U_a = ui->lEditPara_1->text().toFloat();
    float U_b = ui->lEditPara_2->text().toFloat();
    float N_mean = ui->lEditPara_3->text().toFloat();
    float N_var = ui->lEditPara_4->text().toFloat();
    float Exp_lambda = ui->lEditPara_5->text().toFloat();
    float G_alpha = ui->lEditPara_7->text().toFloat();
    float G_lambda= ui->lEditPara_8->text().toFloat();

    QString equation = ui->lEditEquation->text();

    // TO-DO


    ui->outputText->append(dataType);
    ui->outputText->append(algorithm);
    ui->outputText->append(matrixSize);
    ui->outputText->append(equation);
    ui->outputText->append(ui->txtBrowser_1->toPlainText());
    ui->outputText->append(ui->txtBrowser_2->toPlainText());
}
