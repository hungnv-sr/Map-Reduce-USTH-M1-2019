#ifndef FIGUREWINDOW_H
#define FIGUREWINDOW_H

#include <QDialog>
#include "qcustomplot.h"

namespace Ui {
class FigureWindow;
}

class FigureWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FigureWindow(QWidget *parent = nullptr);
    void FigurePlot(int numPoint, QVector<double> data);
    ~FigureWindow();

private:
    Ui::FigureWindow *ui;
    QCustomPlot *wGraphic;
    QCPCurve *verticalLine;
    QCPItemTracer *tracer;
};

#endif // FIGUREWINDOW_H
