#ifndef LOGCONSOLE_H
#define LOGCONSOLE_H

#include <QDialog>

namespace Ui {
class LogConsole;
}

class LogConsole : public QDialog
{
    Q_OBJECT

public:
    explicit LogConsole(QWidget *parent = nullptr);
    Ui::LogConsole *getUI()
    {
        return ui;
    }
    ~LogConsole();

private:
    Ui::LogConsole *ui;
};

#endif // LOGCONSOLE_H
