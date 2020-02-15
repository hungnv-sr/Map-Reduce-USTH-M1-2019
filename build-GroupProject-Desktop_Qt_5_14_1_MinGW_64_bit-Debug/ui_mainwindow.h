/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QComboBox *comboBoxDataType;
    QLabel *label_2;
    QComboBox *comboBoxAlgorithm;
    QPushButton *pushButton;
    QFrame *line;
    QVBoxLayout *verticalLayout;
    QLabel *label_19;
    QTabWidget *tabWidget;
    QWidget *tabWidgetPage1;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout_6;
    QLabel *label_11;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLabel *label_7;
    QLabel *label_12;
    QLineEdit *lineEdit_2;
    QFrame *line_2;
    QGridLayout *gridLayout_7;
    QLabel *label_8;
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QLabel *label_13;
    QLineEdit *lineEdit_3;
    QLabel *label_14;
    QFrame *line_4;
    QGridLayout *gridLayout_8;
    QLabel *label_15;
    QLineEdit *lineEdit_6;
    QLabel *label_5;
    QLabel *label_9;
    QLabel *label_16;
    QLineEdit *lineEdit_7;
    QFrame *line_5;
    QGridLayout *gridLayout_9;
    QLabel *label_6;
    QLineEdit *lineEdit_5;
    QLabel *label_10;
    QLineEdit *lineEdit_8;
    QLabel *label_17;
    QLabel *label_18;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushButton_8;
    QWidget *tabWidgetPage2;
    QHBoxLayout *horizontalLayout_8;
    QGridLayout *gridLayout_10;
    QLineEdit *lineEdit_9;
    QPushButton *pushButton_2;
    QLabel *label_23;
    QWidget *tabWidgetPage3;
    QHBoxLayout *horizontalLayout_4;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_11;
    QLabel *label_21;
    QTextBrowser *textBrowser;
    QPushButton *pushButton_5;
    QPushButton *pushButton_7;
    QFrame *line_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_20;
    QTabWidget *tabWidget_2;
    QWidget *tabWidgetPage1_2;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButton_4;
    QProgressBar *progressBar;
    QPushButton *pushButton_3;
    QWidget *tabWidgetPage3_2;
    QHBoxLayout *horizontalLayout_11;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_12;
    QTextBrowser *textBrowser_2;
    QLabel *label_22;
    QPushButton *pushButton_6;
    QPushButton *pushButton_9;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_4;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(973, 642);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_8 = new QVBoxLayout(centralwidget);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(9, 5, -1, -1);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(5, 5, 5, 5);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(25);
        gridLayout_3->setVerticalSpacing(5);
        gridLayout_3->setContentsMargins(10, 5, 10, 5);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 14));
        label->setMaximumSize(QSize(16777215, 14));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setIndent(10);

        gridLayout_3->addWidget(label, 0, 0, 1, 2);

        comboBoxDataType = new QComboBox(groupBox);
        comboBoxDataType->addItem(QString());
        comboBoxDataType->addItem(QString());
        comboBoxDataType->addItem(QString());
        comboBoxDataType->setObjectName(QString::fromUtf8("comboBoxDataType"));
        comboBoxDataType->setMinimumSize(QSize(0, 23));
        comboBoxDataType->setMaximumSize(QSize(250, 16777215));

        gridLayout_3->addWidget(comboBoxDataType, 1, 0, 1, 2);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 14));
        label_2->setMaximumSize(QSize(16777215, 14));
        label_2->setFont(font);
        label_2->setIndent(10);

        gridLayout_3->addWidget(label_2, 0, 2, 1, 2);

        comboBoxAlgorithm = new QComboBox(groupBox);
        comboBoxAlgorithm->addItem(QString());
        comboBoxAlgorithm->addItem(QString());
        comboBoxAlgorithm->addItem(QString());
        comboBoxAlgorithm->addItem(QString());
        comboBoxAlgorithm->setObjectName(QString::fromUtf8("comboBoxAlgorithm"));
        comboBoxAlgorithm->setMinimumSize(QSize(0, 23));
        comboBoxAlgorithm->setMaximumSize(QSize(250, 16777215));

        gridLayout_3->addWidget(comboBoxAlgorithm, 1, 2, 1, 2);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(75, 23));
        pushButton->setMaximumSize(QSize(75, 16777215));

        gridLayout_3->addWidget(pushButton, 0, 4, 2, 1);

        gridLayout_3->setColumnStretch(0, 1);
        gridLayout_3->setColumnStretch(1, 1);
        gridLayout_3->setColumnStretch(2, 1);
        gridLayout_3->setColumnStretch(3, 1);

        verticalLayout_2->addLayout(gridLayout_3);

        line = new QFrame(groupBox);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(10, 5, 10, 5);
        label_19 = new QLabel(groupBox);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setFont(font);
        label_19->setIndent(10);

        verticalLayout->addWidget(label_19);

        tabWidget = new QTabWidget(groupBox);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(0, 0));
        tabWidget->setMaximumSize(QSize(16777215, 250));
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidgetPage1 = new QWidget();
        tabWidgetPage1->setObjectName(QString::fromUtf8("tabWidgetPage1"));
        horizontalLayout_7 = new QHBoxLayout(tabWidgetPage1);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(12);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(25, 0, 0, 0);
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setHorizontalSpacing(12);
        gridLayout_6->setVerticalSpacing(6);
        gridLayout_6->setContentsMargins(-1, -1, -1, 6);
        label_11 = new QLabel(tabWidgetPage1);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMinimumSize(QSize(0, 0));
        label_11->setMaximumSize(QSize(65, 25));
        QFont font1;
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        label_11->setFont(font1);
        label_11->setLayoutDirection(Qt::LeftToRight);
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_11, 1, 0, 1, 1);

        lineEdit = new QLineEdit(tabWidgetPage1);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(75, 20));
        lineEdit->setMaximumSize(QSize(250, 20));

        gridLayout_6->addWidget(lineEdit, 1, 1, 1, 1);

        label_3 = new QLabel(tabWidgetPage1);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMaximumSize(QSize(65, 25));
        QFont font2;
        font2.setPointSize(8);
        font2.setBold(true);
        font2.setItalic(false);
        font2.setUnderline(false);
        font2.setWeight(75);
        label_3->setFont(font2);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_3, 0, 0, 1, 1);

        label_7 = new QLabel(tabWidgetPage1);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMaximumSize(QSize(16777215, 16777215));
        QFont font3;
        font3.setItalic(true);
        label_7->setFont(font3);
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_7, 0, 1, 1, 1);

        label_12 = new QLabel(tabWidgetPage1);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMaximumSize(QSize(65, 25));
        label_12->setFont(font);
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_12, 2, 0, 1, 1);

        lineEdit_2 = new QLineEdit(tabWidgetPage1);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setMinimumSize(QSize(75, 20));
        lineEdit_2->setMaximumSize(QSize(250, 20));

        gridLayout_6->addWidget(lineEdit_2, 2, 1, 1, 1);

        gridLayout_6->setRowStretch(0, 3);
        gridLayout_6->setRowStretch(1, 2);
        gridLayout_6->setRowStretch(2, 2);
        gridLayout_6->setColumnStretch(0, 1);
        gridLayout_6->setColumnStretch(1, 2);

        horizontalLayout_2->addLayout(gridLayout_6);

        line_2 = new QFrame(tabWidgetPage1);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_2);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setHorizontalSpacing(12);
        gridLayout_7->setVerticalSpacing(6);
        gridLayout_7->setContentsMargins(0, 0, -1, 6);
        label_8 = new QLabel(tabWidgetPage1);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font3);
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_8, 0, 1, 1, 1);

        label_4 = new QLabel(tabWidgetPage1);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMaximumSize(QSize(65, 25));
        label_4->setFont(font2);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_7->addWidget(label_4, 0, 0, 1, 1);

        lineEdit_4 = new QLineEdit(tabWidgetPage1);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setMinimumSize(QSize(75, 20));
        lineEdit_4->setMaximumSize(QSize(250, 20));

        gridLayout_7->addWidget(lineEdit_4, 2, 1, 1, 1);

        label_13 = new QLabel(tabWidgetPage1);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setMaximumSize(QSize(65, 25));
        label_13->setFont(font);
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_7->addWidget(label_13, 1, 0, 1, 1);

        lineEdit_3 = new QLineEdit(tabWidgetPage1);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setMinimumSize(QSize(75, 20));
        lineEdit_3->setMaximumSize(QSize(250, 20));

        gridLayout_7->addWidget(lineEdit_3, 1, 1, 1, 1);

        label_14 = new QLabel(tabWidgetPage1);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setMaximumSize(QSize(65, 25));
        label_14->setFont(font);
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_7->addWidget(label_14, 2, 0, 1, 1);

        gridLayout_7->setRowStretch(0, 3);
        gridLayout_7->setRowStretch(1, 2);
        gridLayout_7->setRowStretch(2, 2);
        gridLayout_7->setColumnStretch(0, 1);
        gridLayout_7->setColumnStretch(1, 2);

        horizontalLayout_2->addLayout(gridLayout_7);

        line_4 = new QFrame(tabWidgetPage1);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_4);

        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setHorizontalSpacing(12);
        gridLayout_8->setVerticalSpacing(6);
        gridLayout_8->setContentsMargins(-1, -1, -1, 6);
        label_15 = new QLabel(tabWidgetPage1);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setEnabled(false);
        label_15->setMaximumSize(QSize(50, 25));

        gridLayout_8->addWidget(label_15, 2, 0, 1, 1);

        lineEdit_6 = new QLineEdit(tabWidgetPage1);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setEnabled(false);
        lineEdit_6->setMinimumSize(QSize(75, 20));
        lineEdit_6->setMaximumSize(QSize(250, 20));

        gridLayout_8->addWidget(lineEdit_6, 2, 1, 1, 1);

        label_5 = new QLabel(tabWidgetPage1);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMaximumSize(QSize(65, 25));
        label_5->setFont(font2);
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_5, 0, 0, 1, 1);

        label_9 = new QLabel(tabWidgetPage1);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font3);
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(label_9, 0, 1, 1, 1);

        label_16 = new QLabel(tabWidgetPage1);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setEnabled(true);
        label_16->setMaximumSize(QSize(65, 25));
        label_16->setFont(font);
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_16, 1, 0, 1, 1);

        lineEdit_7 = new QLineEdit(tabWidgetPage1);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setEnabled(true);
        lineEdit_7->setMinimumSize(QSize(75, 20));
        lineEdit_7->setMaximumSize(QSize(250, 20));

        gridLayout_8->addWidget(lineEdit_7, 1, 1, 1, 1);

        gridLayout_8->setRowStretch(0, 3);
        gridLayout_8->setRowStretch(1, 2);
        gridLayout_8->setRowStretch(2, 2);
        gridLayout_8->setColumnStretch(0, 1);
        gridLayout_8->setColumnStretch(1, 2);

        horizontalLayout_2->addLayout(gridLayout_8);

        line_5 = new QFrame(tabWidgetPage1);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_5);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_9->setHorizontalSpacing(12);
        gridLayout_9->setVerticalSpacing(6);
        gridLayout_9->setContentsMargins(-1, -1, -1, 6);
        label_6 = new QLabel(tabWidgetPage1);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMaximumSize(QSize(65, 25));
        label_6->setFont(font2);
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_9->addWidget(label_6, 0, 0, 1, 1);

        lineEdit_5 = new QLineEdit(tabWidgetPage1);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setMinimumSize(QSize(75, 20));
        lineEdit_5->setMaximumSize(QSize(250, 20));

        gridLayout_9->addWidget(lineEdit_5, 1, 1, 1, 1);

        label_10 = new QLabel(tabWidgetPage1);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font3);
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(label_10, 0, 1, 1, 1);

        lineEdit_8 = new QLineEdit(tabWidgetPage1);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        lineEdit_8->setMinimumSize(QSize(75, 20));
        lineEdit_8->setMaximumSize(QSize(250, 20));

        gridLayout_9->addWidget(lineEdit_8, 2, 1, 1, 1);

        label_17 = new QLabel(tabWidgetPage1);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setMaximumSize(QSize(65, 25));
        label_17->setFont(font);
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_9->addWidget(label_17, 1, 0, 1, 1);

        label_18 = new QLabel(tabWidgetPage1);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setMaximumSize(QSize(65, 25));
        label_18->setFont(font);
        label_18->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_9->addWidget(label_18, 2, 0, 1, 1);

        gridLayout_9->setRowStretch(0, 3);
        gridLayout_9->setColumnStretch(0, 1);

        horizontalLayout_2->addLayout(gridLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(0);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout_10->setContentsMargins(100, 0, 25, 0);
        pushButton_8 = new QPushButton(tabWidgetPage1);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setMaximumSize(QSize(75, 16777215));
        pushButton_8->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_10->addWidget(pushButton_8);

        horizontalLayout_10->setStretch(0, 1);

        horizontalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_2->setStretch(0, 8);
        horizontalLayout_2->setStretch(1, 1);
        horizontalLayout_2->setStretch(2, 8);
        horizontalLayout_2->setStretch(3, 1);
        horizontalLayout_2->setStretch(4, 8);
        horizontalLayout_2->setStretch(5, 1);
        horizontalLayout_2->setStretch(6, 8);

        horizontalLayout_7->addLayout(horizontalLayout_2);

        tabWidget->addTab(tabWidgetPage1, QString());
        tabWidgetPage2 = new QWidget();
        tabWidgetPage2->setObjectName(QString::fromUtf8("tabWidgetPage2"));
        horizontalLayout_8 = new QHBoxLayout(tabWidgetPage2);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        gridLayout_10 = new QGridLayout();
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_10->setHorizontalSpacing(25);
        gridLayout_10->setVerticalSpacing(0);
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        lineEdit_9 = new QLineEdit(tabWidgetPage2);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));
        lineEdit_9->setMinimumSize(QSize(50, 23));
        lineEdit_9->setMaximumSize(QSize(500, 16777215));

        gridLayout_10->addWidget(lineEdit_9, 1, 0, 1, 1);

        pushButton_2 = new QPushButton(tabWidgetPage2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(75, 23));
        pushButton_2->setMaximumSize(QSize(75, 16777215));
        pushButton_2->setCheckable(false);

        gridLayout_10->addWidget(pushButton_2, 1, 1, 1, 1);

        label_23 = new QLabel(tabWidgetPage2);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setMinimumSize(QSize(0, 14));
        label_23->setMaximumSize(QSize(16777215, 14));
        label_23->setFont(font);
        label_23->setIndent(10);

        gridLayout_10->addWidget(label_23, 0, 0, 1, 2);


        horizontalLayout_8->addLayout(gridLayout_10);

        tabWidget->addTab(tabWidgetPage2, QString());
        tabWidgetPage3 = new QWidget();
        tabWidgetPage3->setObjectName(QString::fromUtf8("tabWidgetPage3"));
        horizontalLayout_4 = new QHBoxLayout(tabWidgetPage3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_11 = new QGridLayout();
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        label_21 = new QLabel(tabWidgetPage3);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setMinimumSize(QSize(0, 14));
        label_21->setMaximumSize(QSize(16777215, 14));
        label_21->setFont(font);
        label_21->setIndent(10);

        gridLayout_11->addWidget(label_21, 0, 0, 1, 1);

        textBrowser = new QTextBrowser(tabWidgetPage3);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        gridLayout_11->addWidget(textBrowser, 1, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_11, 0, 1, 1, 1);

        pushButton_5 = new QPushButton(tabWidgetPage3);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setMaximumSize(QSize(75, 16777215));

        gridLayout_4->addWidget(pushButton_5, 0, 0, 1, 1);

        pushButton_7 = new QPushButton(tabWidgetPage3);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setMinimumSize(QSize(75, 23));
        pushButton_7->setMaximumSize(QSize(75, 16777215));

        gridLayout_4->addWidget(pushButton_7, 0, 2, 1, 1);


        horizontalLayout_4->addLayout(gridLayout_4);

        tabWidget->addTab(tabWidgetPage3, QString());

        verticalLayout->addWidget(tabWidget);


        verticalLayout_2->addLayout(verticalLayout);

        line_3 = new QFrame(groupBox);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_3);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(10, 5, 10, 5);
        label_20 = new QLabel(groupBox);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setFont(font);
        label_20->setIndent(10);

        verticalLayout_3->addWidget(label_20);

        tabWidget_2 = new QTabWidget(groupBox);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tabWidget_2->setMaximumSize(QSize(16777215, 225));
        tabWidget_2->setTabShape(QTabWidget::Rounded);
        tabWidgetPage1_2 = new QWidget();
        tabWidgetPage1_2->setObjectName(QString::fromUtf8("tabWidgetPage1_2"));
        horizontalLayout_9 = new QHBoxLayout(tabWidgetPage1_2);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(75);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(25, 5, 25, 5);
        pushButton_4 = new QPushButton(tabWidgetPage1_2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(75, 23));
        pushButton_4->setMaximumSize(QSize(75, 16777215));

        horizontalLayout_6->addWidget(pushButton_4);

        progressBar = new QProgressBar(tabWidgetPage1_2);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMinimumSize(QSize(0, 23));
        progressBar->setMaximumSize(QSize(500, 16777215));
        progressBar->setValue(24);

        horizontalLayout_6->addWidget(progressBar);

        pushButton_3 = new QPushButton(tabWidgetPage1_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(75, 23));
        pushButton_3->setMaximumSize(QSize(75, 16777215));

        horizontalLayout_6->addWidget(pushButton_3);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 8);
        horizontalLayout_6->setStretch(2, 1);

        horizontalLayout_9->addLayout(horizontalLayout_6);

        tabWidget_2->addTab(tabWidgetPage1_2, QString());
        tabWidgetPage3_2 = new QWidget();
        tabWidgetPage3_2->setObjectName(QString::fromUtf8("tabWidgetPage3_2"));
        horizontalLayout_11 = new QHBoxLayout(tabWidgetPage3_2);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_12 = new QGridLayout();
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        textBrowser_2 = new QTextBrowser(tabWidgetPage3_2);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));

        gridLayout_12->addWidget(textBrowser_2, 1, 0, 1, 1);

        label_22 = new QLabel(tabWidgetPage3_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setMinimumSize(QSize(0, 14));
        label_22->setMaximumSize(QSize(16777215, 14));
        label_22->setFont(font);
        label_22->setIndent(10);

        gridLayout_12->addWidget(label_22, 0, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_12, 0, 1, 1, 1);

        pushButton_6 = new QPushButton(tabWidgetPage3_2);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setMaximumSize(QSize(75, 16777215));

        gridLayout_5->addWidget(pushButton_6, 0, 0, 1, 1);

        pushButton_9 = new QPushButton(tabWidgetPage3_2);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setMinimumSize(QSize(75, 23));
        pushButton_9->setMaximumSize(QSize(75, 16777215));

        gridLayout_5->addWidget(pushButton_9, 0, 2, 1, 1);


        horizontalLayout_11->addLayout(gridLayout_5);

        tabWidget_2->addTab(tabWidgetPage3_2, QString());

        verticalLayout_3->addWidget(tabWidget_2);


        verticalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_2->setStretch(1, 1);

        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);


        verticalLayout_6->addWidget(groupBox);


        verticalLayout_8->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(5);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(5, 5, 5, 5);
        graphicsView = new QGraphicsView(groupBox_2);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        verticalLayout_4->addWidget(graphicsView);


        gridLayout_2->addLayout(verticalLayout_4, 0, 0, 1, 1);


        verticalLayout_7->addWidget(groupBox_2);


        verticalLayout_8->addLayout(verticalLayout_7);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 973, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "[M1.07] - REDUCE Paradigm", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Input", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Data Type", nullptr));
        comboBoxDataType->setItemText(0, QCoreApplication::translate("MainWindow", "(default)", nullptr));
        comboBoxDataType->setItemText(1, QCoreApplication::translate("MainWindow", "Array", nullptr));
        comboBoxDataType->setItemText(2, QCoreApplication::translate("MainWindow", "Matrix", nullptr));

        label_2->setText(QCoreApplication::translate("MainWindow", "Algorithm", nullptr));
        comboBoxAlgorithm->setItemText(0, QCoreApplication::translate("MainWindow", "(default)", nullptr));
        comboBoxAlgorithm->setItemText(1, QCoreApplication::translate("MainWindow", "Sum", nullptr));
        comboBoxAlgorithm->setItemText(2, QCoreApplication::translate("MainWindow", "Multiplication", nullptr));
        comboBoxAlgorithm->setItemText(3, QCoreApplication::translate("MainWindow", "Element-wise multiplication", nullptr));

        pushButton->setText(QCoreApplication::translate("MainWindow", "OK", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "Distribution", nullptr));
#if QT_CONFIG(accessibility)
        tabWidget->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
        label_11->setText(QCoreApplication::translate("MainWindow", "a =", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Uniform", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "U(a,b)", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "b =", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "N(\316\274, \317\203^2)", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Gaussian", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\316\274 =", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "\317\203^2 =", nullptr));
        label_15->setText(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "Exponential", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Exp(\316\273)", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "\316\273 =", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Gamma", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "G(\316\261, \316\273)", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "\316\261 =", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "\316\273 =", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "OK", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage1), QCoreApplication::translate("MainWindow", "Parameters only", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "OK", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "Edit an equation...", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage2), QCoreApplication::translate("MainWindow", "Mixture", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "Message", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Open File...", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "OK", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage3), QCoreApplication::translate("MainWindow", "Import from a file", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "Calculation dataset", nullptr));
#if QT_CONFIG(accessibility)
        tabWidget_2->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Generate!", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "OK", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tabWidgetPage1_2), QCoreApplication::translate("MainWindow", "Generated randomly", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "Message", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Open File...", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "OK", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tabWidgetPage3_2), QCoreApplication::translate("MainWindow", "Import from a file", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Output", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
