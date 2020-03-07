#include "figurewindow.h"
#include "ui_figurewindow.h"
#include "QDebug"

FigureWindow::FigureWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FigureWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

}

void FigureWindow::FigurePlot(int numPoint, QVector<double> data)
{
    wGraphic = new QCustomPlot();
    ui->gLayoutContainer->addWidget(wGraphic,0,0,0,0);

    /* Sampling the original data */
    QVector<double> dataSampled(numPoint), indices(numPoint);
    double max = 0;

    int j = 0;
    int distance = (int)(data.size()/(numPoint-1));

    if (distance > 1) distance-=1;

    for (int i=0; i<data.size(); i+=distance)
    {
        dataSampled[j] = data[i];
        if (dataSampled[j] > max) max = dataSampled[j];
        indices[j] = i;
        ++j;
    }

    /* Plot */
    wGraphic->addGraph();
    wGraphic->graph(0)->setData(indices,dataSampled);
    wGraphic->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));
    wGraphic->xAxis->setRange(0,data.size());
    wGraphic->yAxis->setRange(0,max);

    wGraphic->replot();
}

FigureWindow::~FigureWindow()
{
    delete ui;
}
