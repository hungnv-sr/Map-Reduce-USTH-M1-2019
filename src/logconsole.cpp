#include "logconsole.h"
#include "ui_logconsole.h"

LogConsole::LogConsole(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogConsole)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

LogConsole::~LogConsole()
{
    delete ui;
}
