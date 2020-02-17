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
    QVBoxLayout *vLayoutInput;
    QGroupBox *gBoxInput;
    QGridLayout *gridLayout;
    QVBoxLayout *vLayoutInputComponents;
    QGridLayout *gLayoutInput_1;
    QLabel *lblAlgorithm;
    QLabel *lblMatSize;
    QComboBox *cBoxDataType;
    QLineEdit *lEditMatSize;
    QLabel *lblDataType;
    QComboBox *cBoxAlgorithm;
    QFrame *sepHLine_1;
    QVBoxLayout *vLayoutInput_2;
    QLabel *lblDistribution;
    QTabWidget *tabDistribution;
    QWidget *tabInput_2_Page_1;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *hLayoutInput_2_Page_1;
    QGridLayout *gLayoutDistribution_1;
    QLabel *lblPara_1;
    QLineEdit *lEditPara_1;
    QLabel *lblUniform_1;
    QLabel *lblUniform_2;
    QLabel *lblPara_2;
    QLineEdit *lEditPara_2;
    QFrame *sepVLine_1;
    QGridLayout *gLayoutDistribution_2;
    QLabel *lblGauss_2;
    QLabel *lblGauss_1;
    QLineEdit *lEditPara_4;
    QLabel *lblPara_3;
    QLineEdit *lEditPara_3;
    QLabel *lblPara_4;
    QFrame *sepVLine_2;
    QGridLayout *gLayoutDistribution_3;
    QLabel *lblPara_6;
    QLineEdit *lEditPara_6;
    QLabel *lblExp_1;
    QLabel *lblExp_2;
    QLabel *lblPara_5;
    QLineEdit *lEditPara_5;
    QFrame *sepVLine_3;
    QGridLayout *gLayoutDistribution_4;
    QLabel *lblGamma_1;
    QLineEdit *lEditPara_7;
    QLabel *lblGamma_2;
    QLineEdit *lEditPara_8;
    QLabel *lblPara_7;
    QLabel *lblPara_8;
    QWidget *tabInput_2_Page_2;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout;
    QLabel *lblEquation;
    QLineEdit *lEditEquation;
    QWidget *tabInput_2_Page_3;
    QHBoxLayout *horizontalLayout_4;
    QGridLayout *gLayoutOpenFile_1;
    QGridLayout *gLayoutMessage_1;
    QLabel *lblMessage_1;
    QTextBrowser *txtBrowser_1;
    QPushButton *pButtonOpenFile_1;
    QPushButton *pButtonOK_1;
    QFrame *sepHLine_2;
    QVBoxLayout *vLayoutInput3;
    QLabel *lblCalcDataset;
    QTabWidget *tabCalcDataset;
    QWidget *tabInput_3_Page_1;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *hLayoutInput_3_Page_1;
    QPushButton *pButtonGen;
    QProgressBar *progBar;
    QWidget *tabInput_3_Page_2;
    QHBoxLayout *horizontalLayout_11;
    QGridLayout *gLayoutOpenFile_2;
    QGridLayout *gLayoutMessage_2;
    QTextBrowser *txtBrowser_2;
    QLabel *lblMessage_2;
    QPushButton *pButtonOpenFile_2;
    QPushButton *pButtonOK_2;
    QFrame *sepHLine_3;
    QPushButton *pButtonRun;
    QVBoxLayout *vLayoutOutput;
    QGroupBox *gBoxOutput;
    QGridLayout *gridLayout_2;
    QVBoxLayout *vLayoutDisplay;
    QTextBrowser *outputText;
    QGraphicsView *gViewDisplay;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(761, 801);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_8 = new QVBoxLayout(centralwidget);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        vLayoutInput = new QVBoxLayout();
        vLayoutInput->setObjectName(QString::fromUtf8("vLayoutInput"));
        gBoxInput = new QGroupBox(centralwidget);
        gBoxInput->setObjectName(QString::fromUtf8("gBoxInput"));
        gridLayout = new QGridLayout(gBoxInput);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(9, 5, -1, -1);
        vLayoutInputComponents = new QVBoxLayout();
        vLayoutInputComponents->setSpacing(5);
        vLayoutInputComponents->setObjectName(QString::fromUtf8("vLayoutInputComponents"));
        vLayoutInputComponents->setContentsMargins(5, 5, 5, 5);
        gLayoutInput_1 = new QGridLayout();
        gLayoutInput_1->setObjectName(QString::fromUtf8("gLayoutInput_1"));
        gLayoutInput_1->setHorizontalSpacing(25);
        gLayoutInput_1->setVerticalSpacing(5);
        gLayoutInput_1->setContentsMargins(10, 5, 10, 5);
        lblAlgorithm = new QLabel(gBoxInput);
        lblAlgorithm->setObjectName(QString::fromUtf8("lblAlgorithm"));
        lblAlgorithm->setMinimumSize(QSize(0, 14));
        lblAlgorithm->setMaximumSize(QSize(16777215, 14));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        lblAlgorithm->setFont(font);
        lblAlgorithm->setIndent(10);

        gLayoutInput_1->addWidget(lblAlgorithm, 0, 2, 1, 2);

        lblMatSize = new QLabel(gBoxInput);
        lblMatSize->setObjectName(QString::fromUtf8("lblMatSize"));
        lblMatSize->setMinimumSize(QSize(0, 14));
        lblMatSize->setMaximumSize(QSize(16777215, 14));
        lblMatSize->setFont(font);
        lblMatSize->setIndent(10);

        gLayoutInput_1->addWidget(lblMatSize, 2, 0, 1, 2);

        cBoxDataType = new QComboBox(gBoxInput);
        cBoxDataType->addItem(QString());
        cBoxDataType->addItem(QString());
        cBoxDataType->addItem(QString());
        cBoxDataType->setObjectName(QString::fromUtf8("cBoxDataType"));
        cBoxDataType->setMinimumSize(QSize(0, 23));
        cBoxDataType->setMaximumSize(QSize(250, 16777215));

        gLayoutInput_1->addWidget(cBoxDataType, 1, 0, 1, 2);

        lEditMatSize = new QLineEdit(gBoxInput);
        lEditMatSize->setObjectName(QString::fromUtf8("lEditMatSize"));
        lEditMatSize->setMinimumSize(QSize(50, 23));
        lEditMatSize->setMaximumSize(QSize(250, 16777215));

        gLayoutInput_1->addWidget(lEditMatSize, 3, 0, 1, 2);

        lblDataType = new QLabel(gBoxInput);
        lblDataType->setObjectName(QString::fromUtf8("lblDataType"));
        lblDataType->setMinimumSize(QSize(0, 14));
        lblDataType->setMaximumSize(QSize(16777215, 14));
        lblDataType->setFont(font);
        lblDataType->setIndent(10);

        gLayoutInput_1->addWidget(lblDataType, 0, 0, 1, 2);

        cBoxAlgorithm = new QComboBox(gBoxInput);
        cBoxAlgorithm->addItem(QString());
        cBoxAlgorithm->addItem(QString());
        cBoxAlgorithm->addItem(QString());
        cBoxAlgorithm->addItem(QString());
        cBoxAlgorithm->setObjectName(QString::fromUtf8("cBoxAlgorithm"));
        cBoxAlgorithm->setMinimumSize(QSize(0, 23));
        cBoxAlgorithm->setMaximumSize(QSize(250, 16777215));

        gLayoutInput_1->addWidget(cBoxAlgorithm, 1, 2, 1, 2);


        vLayoutInputComponents->addLayout(gLayoutInput_1);

        sepHLine_1 = new QFrame(gBoxInput);
        sepHLine_1->setObjectName(QString::fromUtf8("sepHLine_1"));
        sepHLine_1->setFrameShape(QFrame::HLine);
        sepHLine_1->setFrameShadow(QFrame::Sunken);

        vLayoutInputComponents->addWidget(sepHLine_1);

        vLayoutInput_2 = new QVBoxLayout();
        vLayoutInput_2->setObjectName(QString::fromUtf8("vLayoutInput_2"));
        vLayoutInput_2->setContentsMargins(10, 5, 10, 5);
        lblDistribution = new QLabel(gBoxInput);
        lblDistribution->setObjectName(QString::fromUtf8("lblDistribution"));
        lblDistribution->setFont(font);
        lblDistribution->setIndent(10);

        vLayoutInput_2->addWidget(lblDistribution);

        tabDistribution = new QTabWidget(gBoxInput);
        tabDistribution->setObjectName(QString::fromUtf8("tabDistribution"));
        tabDistribution->setMinimumSize(QSize(0, 0));
        tabDistribution->setMaximumSize(QSize(16777215, 250));
        tabDistribution->setTabShape(QTabWidget::Rounded);
        tabInput_2_Page_1 = new QWidget();
        tabInput_2_Page_1->setObjectName(QString::fromUtf8("tabInput_2_Page_1"));
        horizontalLayout_7 = new QHBoxLayout(tabInput_2_Page_1);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        hLayoutInput_2_Page_1 = new QHBoxLayout();
        hLayoutInput_2_Page_1->setSpacing(12);
        hLayoutInput_2_Page_1->setObjectName(QString::fromUtf8("hLayoutInput_2_Page_1"));
        hLayoutInput_2_Page_1->setContentsMargins(25, 0, 0, 0);
        gLayoutDistribution_1 = new QGridLayout();
        gLayoutDistribution_1->setObjectName(QString::fromUtf8("gLayoutDistribution_1"));
        gLayoutDistribution_1->setHorizontalSpacing(12);
        gLayoutDistribution_1->setVerticalSpacing(6);
        gLayoutDistribution_1->setContentsMargins(-1, -1, -1, 6);
        lblPara_1 = new QLabel(tabInput_2_Page_1);
        lblPara_1->setObjectName(QString::fromUtf8("lblPara_1"));
        lblPara_1->setMinimumSize(QSize(0, 0));
        lblPara_1->setMaximumSize(QSize(65, 25));
        QFont font1;
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        lblPara_1->setFont(font1);
        lblPara_1->setLayoutDirection(Qt::LeftToRight);
        lblPara_1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gLayoutDistribution_1->addWidget(lblPara_1, 1, 0, 1, 1);

        lEditPara_1 = new QLineEdit(tabInput_2_Page_1);
        lEditPara_1->setObjectName(QString::fromUtf8("lEditPara_1"));
        lEditPara_1->setMinimumSize(QSize(75, 20));
        lEditPara_1->setMaximumSize(QSize(250, 20));

        gLayoutDistribution_1->addWidget(lEditPara_1, 1, 1, 1, 1);

        lblUniform_1 = new QLabel(tabInput_2_Page_1);
        lblUniform_1->setObjectName(QString::fromUtf8("lblUniform_1"));
        lblUniform_1->setMaximumSize(QSize(65, 25));
        QFont font2;
        font2.setPointSize(8);
        font2.setBold(true);
        font2.setItalic(false);
        font2.setUnderline(false);
        font2.setWeight(75);
        lblUniform_1->setFont(font2);
        lblUniform_1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gLayoutDistribution_1->addWidget(lblUniform_1, 0, 0, 1, 1);

        lblUniform_2 = new QLabel(tabInput_2_Page_1);
        lblUniform_2->setObjectName(QString::fromUtf8("lblUniform_2"));
        lblUniform_2->setMaximumSize(QSize(16777215, 16777215));
        QFont font3;
        font3.setItalic(true);
        lblUniform_2->setFont(font3);
        lblUniform_2->setAlignment(Qt::AlignCenter);

        gLayoutDistribution_1->addWidget(lblUniform_2, 0, 1, 1, 1);

        lblPara_2 = new QLabel(tabInput_2_Page_1);
        lblPara_2->setObjectName(QString::fromUtf8("lblPara_2"));
        lblPara_2->setMaximumSize(QSize(65, 25));
        lblPara_2->setFont(font);
        lblPara_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gLayoutDistribution_1->addWidget(lblPara_2, 2, 0, 1, 1);

        lEditPara_2 = new QLineEdit(tabInput_2_Page_1);
        lEditPara_2->setObjectName(QString::fromUtf8("lEditPara_2"));
        lEditPara_2->setMinimumSize(QSize(75, 20));
        lEditPara_2->setMaximumSize(QSize(250, 20));

        gLayoutDistribution_1->addWidget(lEditPara_2, 2, 1, 1, 1);

        gLayoutDistribution_1->setRowStretch(0, 3);
        gLayoutDistribution_1->setRowStretch(1, 2);
        gLayoutDistribution_1->setRowStretch(2, 2);
        gLayoutDistribution_1->setColumnStretch(0, 1);
        gLayoutDistribution_1->setColumnStretch(1, 2);

        hLayoutInput_2_Page_1->addLayout(gLayoutDistribution_1);

        sepVLine_1 = new QFrame(tabInput_2_Page_1);
        sepVLine_1->setObjectName(QString::fromUtf8("sepVLine_1"));
        sepVLine_1->setFrameShape(QFrame::VLine);
        sepVLine_1->setFrameShadow(QFrame::Sunken);

        hLayoutInput_2_Page_1->addWidget(sepVLine_1);

        gLayoutDistribution_2 = new QGridLayout();
        gLayoutDistribution_2->setObjectName(QString::fromUtf8("gLayoutDistribution_2"));
        gLayoutDistribution_2->setHorizontalSpacing(12);
        gLayoutDistribution_2->setVerticalSpacing(6);
        gLayoutDistribution_2->setContentsMargins(0, 0, -1, 6);
        lblGauss_2 = new QLabel(tabInput_2_Page_1);
        lblGauss_2->setObjectName(QString::fromUtf8("lblGauss_2"));
        lblGauss_2->setFont(font3);
        lblGauss_2->setAlignment(Qt::AlignCenter);

        gLayoutDistribution_2->addWidget(lblGauss_2, 0, 1, 1, 1);

        lblGauss_1 = new QLabel(tabInput_2_Page_1);
        lblGauss_1->setObjectName(QString::fromUtf8("lblGauss_1"));
        lblGauss_1->setMaximumSize(QSize(65, 25));
        lblGauss_1->setFont(font2);
        lblGauss_1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gLayoutDistribution_2->addWidget(lblGauss_1, 0, 0, 1, 1);

        lEditPara_4 = new QLineEdit(tabInput_2_Page_1);
        lEditPara_4->setObjectName(QString::fromUtf8("lEditPara_4"));
        lEditPara_4->setMinimumSize(QSize(75, 20));
        lEditPara_4->setMaximumSize(QSize(250, 20));

        gLayoutDistribution_2->addWidget(lEditPara_4, 2, 1, 1, 1);

        lblPara_3 = new QLabel(tabInput_2_Page_1);
        lblPara_3->setObjectName(QString::fromUtf8("lblPara_3"));
        lblPara_3->setMaximumSize(QSize(65, 25));
        lblPara_3->setFont(font);
        lblPara_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gLayoutDistribution_2->addWidget(lblPara_3, 1, 0, 1, 1);

        lEditPara_3 = new QLineEdit(tabInput_2_Page_1);
        lEditPara_3->setObjectName(QString::fromUtf8("lEditPara_3"));
        lEditPara_3->setMinimumSize(QSize(75, 20));
        lEditPara_3->setMaximumSize(QSize(250, 20));

        gLayoutDistribution_2->addWidget(lEditPara_3, 1, 1, 1, 1);

        lblPara_4 = new QLabel(tabInput_2_Page_1);
        lblPara_4->setObjectName(QString::fromUtf8("lblPara_4"));
        lblPara_4->setMaximumSize(QSize(65, 25));
        lblPara_4->setFont(font);
        lblPara_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gLayoutDistribution_2->addWidget(lblPara_4, 2, 0, 1, 1);

        gLayoutDistribution_2->setRowStretch(0, 3);
        gLayoutDistribution_2->setRowStretch(1, 2);
        gLayoutDistribution_2->setRowStretch(2, 2);
        gLayoutDistribution_2->setColumnStretch(0, 1);
        gLayoutDistribution_2->setColumnStretch(1, 2);

        hLayoutInput_2_Page_1->addLayout(gLayoutDistribution_2);

        sepVLine_2 = new QFrame(tabInput_2_Page_1);
        sepVLine_2->setObjectName(QString::fromUtf8("sepVLine_2"));
        sepVLine_2->setFrameShape(QFrame::VLine);
        sepVLine_2->setFrameShadow(QFrame::Sunken);

        hLayoutInput_2_Page_1->addWidget(sepVLine_2);

        gLayoutDistribution_3 = new QGridLayout();
        gLayoutDistribution_3->setObjectName(QString::fromUtf8("gLayoutDistribution_3"));
        gLayoutDistribution_3->setHorizontalSpacing(12);
        gLayoutDistribution_3->setVerticalSpacing(6);
        gLayoutDistribution_3->setContentsMargins(-1, -1, -1, 6);
        lblPara_6 = new QLabel(tabInput_2_Page_1);
        lblPara_6->setObjectName(QString::fromUtf8("lblPara_6"));
        lblPara_6->setEnabled(false);
        lblPara_6->setMaximumSize(QSize(50, 25));

        gLayoutDistribution_3->addWidget(lblPara_6, 2, 0, 1, 1);

        lEditPara_6 = new QLineEdit(tabInput_2_Page_1);
        lEditPara_6->setObjectName(QString::fromUtf8("lEditPara_6"));
        lEditPara_6->setEnabled(false);
        lEditPara_6->setMinimumSize(QSize(75, 20));
        lEditPara_6->setMaximumSize(QSize(250, 20));

        gLayoutDistribution_3->addWidget(lEditPara_6, 2, 1, 1, 1);

        lblExp_1 = new QLabel(tabInput_2_Page_1);
        lblExp_1->setObjectName(QString::fromUtf8("lblExp_1"));
        lblExp_1->setMaximumSize(QSize(65, 25));
        lblExp_1->setFont(font2);
        lblExp_1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gLayoutDistribution_3->addWidget(lblExp_1, 0, 0, 1, 1);

        lblExp_2 = new QLabel(tabInput_2_Page_1);
        lblExp_2->setObjectName(QString::fromUtf8("lblExp_2"));
        lblExp_2->setFont(font3);
        lblExp_2->setAlignment(Qt::AlignCenter);

        gLayoutDistribution_3->addWidget(lblExp_2, 0, 1, 1, 1);

        lblPara_5 = new QLabel(tabInput_2_Page_1);
        lblPara_5->setObjectName(QString::fromUtf8("lblPara_5"));
        lblPara_5->setEnabled(true);
        lblPara_5->setMaximumSize(QSize(65, 25));
        lblPara_5->setFont(font);
        lblPara_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gLayoutDistribution_3->addWidget(lblPara_5, 1, 0, 1, 1);

        lEditPara_5 = new QLineEdit(tabInput_2_Page_1);
        lEditPara_5->setObjectName(QString::fromUtf8("lEditPara_5"));
        lEditPara_5->setEnabled(true);
        lEditPara_5->setMinimumSize(QSize(75, 20));
        lEditPara_5->setMaximumSize(QSize(250, 20));

        gLayoutDistribution_3->addWidget(lEditPara_5, 1, 1, 1, 1);

        gLayoutDistribution_3->setRowStretch(0, 3);
        gLayoutDistribution_3->setRowStretch(1, 2);
        gLayoutDistribution_3->setRowStretch(2, 2);
        gLayoutDistribution_3->setColumnStretch(0, 1);
        gLayoutDistribution_3->setColumnStretch(1, 2);

        hLayoutInput_2_Page_1->addLayout(gLayoutDistribution_3);

        sepVLine_3 = new QFrame(tabInput_2_Page_1);
        sepVLine_3->setObjectName(QString::fromUtf8("sepVLine_3"));
        sepVLine_3->setFrameShape(QFrame::VLine);
        sepVLine_3->setFrameShadow(QFrame::Sunken);

        hLayoutInput_2_Page_1->addWidget(sepVLine_3);

        gLayoutDistribution_4 = new QGridLayout();
        gLayoutDistribution_4->setObjectName(QString::fromUtf8("gLayoutDistribution_4"));
        gLayoutDistribution_4->setHorizontalSpacing(12);
        gLayoutDistribution_4->setVerticalSpacing(6);
        gLayoutDistribution_4->setContentsMargins(-1, -1, -1, 6);
        lblGamma_1 = new QLabel(tabInput_2_Page_1);
        lblGamma_1->setObjectName(QString::fromUtf8("lblGamma_1"));
        lblGamma_1->setMaximumSize(QSize(65, 25));
        lblGamma_1->setFont(font2);
        lblGamma_1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gLayoutDistribution_4->addWidget(lblGamma_1, 0, 0, 1, 1);

        lEditPara_7 = new QLineEdit(tabInput_2_Page_1);
        lEditPara_7->setObjectName(QString::fromUtf8("lEditPara_7"));
        lEditPara_7->setMinimumSize(QSize(75, 20));
        lEditPara_7->setMaximumSize(QSize(250, 20));

        gLayoutDistribution_4->addWidget(lEditPara_7, 1, 1, 1, 1);

        lblGamma_2 = new QLabel(tabInput_2_Page_1);
        lblGamma_2->setObjectName(QString::fromUtf8("lblGamma_2"));
        lblGamma_2->setFont(font3);
        lblGamma_2->setAlignment(Qt::AlignCenter);

        gLayoutDistribution_4->addWidget(lblGamma_2, 0, 1, 1, 1);

        lEditPara_8 = new QLineEdit(tabInput_2_Page_1);
        lEditPara_8->setObjectName(QString::fromUtf8("lEditPara_8"));
        lEditPara_8->setMinimumSize(QSize(75, 20));
        lEditPara_8->setMaximumSize(QSize(250, 20));

        gLayoutDistribution_4->addWidget(lEditPara_8, 2, 1, 1, 1);

        lblPara_7 = new QLabel(tabInput_2_Page_1);
        lblPara_7->setObjectName(QString::fromUtf8("lblPara_7"));
        lblPara_7->setMaximumSize(QSize(65, 25));
        lblPara_7->setFont(font);
        lblPara_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gLayoutDistribution_4->addWidget(lblPara_7, 1, 0, 1, 1);

        lblPara_8 = new QLabel(tabInput_2_Page_1);
        lblPara_8->setObjectName(QString::fromUtf8("lblPara_8"));
        lblPara_8->setMaximumSize(QSize(65, 25));
        lblPara_8->setFont(font);
        lblPara_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gLayoutDistribution_4->addWidget(lblPara_8, 2, 0, 1, 1);

        gLayoutDistribution_4->setRowStretch(0, 3);
        gLayoutDistribution_4->setColumnStretch(0, 1);

        hLayoutInput_2_Page_1->addLayout(gLayoutDistribution_4);

        hLayoutInput_2_Page_1->setStretch(0, 8);
        hLayoutInput_2_Page_1->setStretch(1, 1);
        hLayoutInput_2_Page_1->setStretch(2, 8);
        hLayoutInput_2_Page_1->setStretch(3, 1);
        hLayoutInput_2_Page_1->setStretch(4, 8);
        hLayoutInput_2_Page_1->setStretch(5, 1);
        hLayoutInput_2_Page_1->setStretch(6, 8);

        horizontalLayout_7->addLayout(hLayoutInput_2_Page_1);

        tabDistribution->addTab(tabInput_2_Page_1, QString());
        tabInput_2_Page_2 = new QWidget();
        tabInput_2_Page_2->setObjectName(QString::fromUtf8("tabInput_2_Page_2"));
        horizontalLayout_8 = new QHBoxLayout(tabInput_2_Page_2);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lblEquation = new QLabel(tabInput_2_Page_2);
        lblEquation->setObjectName(QString::fromUtf8("lblEquation"));
        lblEquation->setMinimumSize(QSize(0, 14));
        lblEquation->setMaximumSize(QSize(16777215, 14));
        lblEquation->setFont(font);
        lblEquation->setIndent(10);

        verticalLayout->addWidget(lblEquation);

        lEditEquation = new QLineEdit(tabInput_2_Page_2);
        lEditEquation->setObjectName(QString::fromUtf8("lEditEquation"));
        lEditEquation->setMinimumSize(QSize(50, 23));
        lEditEquation->setMaximumSize(QSize(500, 16777215));

        verticalLayout->addWidget(lEditEquation);


        horizontalLayout_8->addLayout(verticalLayout);

        tabDistribution->addTab(tabInput_2_Page_2, QString());
        tabInput_2_Page_3 = new QWidget();
        tabInput_2_Page_3->setObjectName(QString::fromUtf8("tabInput_2_Page_3"));
        horizontalLayout_4 = new QHBoxLayout(tabInput_2_Page_3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        gLayoutOpenFile_1 = new QGridLayout();
        gLayoutOpenFile_1->setObjectName(QString::fromUtf8("gLayoutOpenFile_1"));
        gLayoutMessage_1 = new QGridLayout();
        gLayoutMessage_1->setObjectName(QString::fromUtf8("gLayoutMessage_1"));
        lblMessage_1 = new QLabel(tabInput_2_Page_3);
        lblMessage_1->setObjectName(QString::fromUtf8("lblMessage_1"));
        lblMessage_1->setMinimumSize(QSize(0, 14));
        lblMessage_1->setMaximumSize(QSize(16777215, 14));
        lblMessage_1->setFont(font);
        lblMessage_1->setIndent(10);

        gLayoutMessage_1->addWidget(lblMessage_1, 0, 0, 1, 1);

        txtBrowser_1 = new QTextBrowser(tabInput_2_Page_3);
        txtBrowser_1->setObjectName(QString::fromUtf8("txtBrowser_1"));

        gLayoutMessage_1->addWidget(txtBrowser_1, 1, 0, 1, 1);


        gLayoutOpenFile_1->addLayout(gLayoutMessage_1, 0, 1, 1, 1);

        pButtonOpenFile_1 = new QPushButton(tabInput_2_Page_3);
        pButtonOpenFile_1->setObjectName(QString::fromUtf8("pButtonOpenFile_1"));
        pButtonOpenFile_1->setMaximumSize(QSize(75, 16777215));

        gLayoutOpenFile_1->addWidget(pButtonOpenFile_1, 0, 0, 1, 1);

        pButtonOK_1 = new QPushButton(tabInput_2_Page_3);
        pButtonOK_1->setObjectName(QString::fromUtf8("pButtonOK_1"));
        pButtonOK_1->setEnabled(true);
        pButtonOK_1->setMinimumSize(QSize(75, 23));
        pButtonOK_1->setMaximumSize(QSize(75, 16777215));

        gLayoutOpenFile_1->addWidget(pButtonOK_1, 0, 2, 1, 1);


        horizontalLayout_4->addLayout(gLayoutOpenFile_1);

        tabDistribution->addTab(tabInput_2_Page_3, QString());

        vLayoutInput_2->addWidget(tabDistribution);


        vLayoutInputComponents->addLayout(vLayoutInput_2);

        sepHLine_2 = new QFrame(gBoxInput);
        sepHLine_2->setObjectName(QString::fromUtf8("sepHLine_2"));
        sepHLine_2->setFrameShape(QFrame::HLine);
        sepHLine_2->setFrameShadow(QFrame::Sunken);

        vLayoutInputComponents->addWidget(sepHLine_2);

        vLayoutInput3 = new QVBoxLayout();
        vLayoutInput3->setObjectName(QString::fromUtf8("vLayoutInput3"));
        vLayoutInput3->setContentsMargins(10, 5, 10, 5);
        lblCalcDataset = new QLabel(gBoxInput);
        lblCalcDataset->setObjectName(QString::fromUtf8("lblCalcDataset"));
        lblCalcDataset->setFont(font);
        lblCalcDataset->setIndent(10);

        vLayoutInput3->addWidget(lblCalcDataset);

        tabCalcDataset = new QTabWidget(gBoxInput);
        tabCalcDataset->setObjectName(QString::fromUtf8("tabCalcDataset"));
        tabCalcDataset->setMaximumSize(QSize(16777215, 225));
        tabCalcDataset->setTabShape(QTabWidget::Rounded);
        tabInput_3_Page_1 = new QWidget();
        tabInput_3_Page_1->setObjectName(QString::fromUtf8("tabInput_3_Page_1"));
        horizontalLayout_9 = new QHBoxLayout(tabInput_3_Page_1);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        hLayoutInput_3_Page_1 = new QHBoxLayout();
        hLayoutInput_3_Page_1->setSpacing(75);
        hLayoutInput_3_Page_1->setObjectName(QString::fromUtf8("hLayoutInput_3_Page_1"));
        hLayoutInput_3_Page_1->setContentsMargins(25, 5, 25, 5);
        pButtonGen = new QPushButton(tabInput_3_Page_1);
        pButtonGen->setObjectName(QString::fromUtf8("pButtonGen"));
        pButtonGen->setMinimumSize(QSize(75, 23));
        pButtonGen->setMaximumSize(QSize(75, 16777215));

        hLayoutInput_3_Page_1->addWidget(pButtonGen);

        progBar = new QProgressBar(tabInput_3_Page_1);
        progBar->setObjectName(QString::fromUtf8("progBar"));
        progBar->setMinimumSize(QSize(0, 23));
        progBar->setMaximumSize(QSize(500, 16777215));
        progBar->setValue(0);

        hLayoutInput_3_Page_1->addWidget(progBar);

        hLayoutInput_3_Page_1->setStretch(0, 1);
        hLayoutInput_3_Page_1->setStretch(1, 8);

        horizontalLayout_9->addLayout(hLayoutInput_3_Page_1);

        tabCalcDataset->addTab(tabInput_3_Page_1, QString());
        tabInput_3_Page_2 = new QWidget();
        tabInput_3_Page_2->setObjectName(QString::fromUtf8("tabInput_3_Page_2"));
        horizontalLayout_11 = new QHBoxLayout(tabInput_3_Page_2);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        gLayoutOpenFile_2 = new QGridLayout();
        gLayoutOpenFile_2->setObjectName(QString::fromUtf8("gLayoutOpenFile_2"));
        gLayoutMessage_2 = new QGridLayout();
        gLayoutMessage_2->setObjectName(QString::fromUtf8("gLayoutMessage_2"));
        txtBrowser_2 = new QTextBrowser(tabInput_3_Page_2);
        txtBrowser_2->setObjectName(QString::fromUtf8("txtBrowser_2"));

        gLayoutMessage_2->addWidget(txtBrowser_2, 1, 0, 1, 1);

        lblMessage_2 = new QLabel(tabInput_3_Page_2);
        lblMessage_2->setObjectName(QString::fromUtf8("lblMessage_2"));
        lblMessage_2->setMinimumSize(QSize(0, 14));
        lblMessage_2->setMaximumSize(QSize(16777215, 14));
        lblMessage_2->setFont(font);
        lblMessage_2->setIndent(10);

        gLayoutMessage_2->addWidget(lblMessage_2, 0, 0, 1, 1);


        gLayoutOpenFile_2->addLayout(gLayoutMessage_2, 0, 1, 1, 1);

        pButtonOpenFile_2 = new QPushButton(tabInput_3_Page_2);
        pButtonOpenFile_2->setObjectName(QString::fromUtf8("pButtonOpenFile_2"));
        pButtonOpenFile_2->setMaximumSize(QSize(75, 16777215));

        gLayoutOpenFile_2->addWidget(pButtonOpenFile_2, 0, 0, 1, 1);

        pButtonOK_2 = new QPushButton(tabInput_3_Page_2);
        pButtonOK_2->setObjectName(QString::fromUtf8("pButtonOK_2"));
        pButtonOK_2->setMinimumSize(QSize(75, 23));
        pButtonOK_2->setMaximumSize(QSize(75, 16777215));

        gLayoutOpenFile_2->addWidget(pButtonOK_2, 0, 2, 1, 1);


        horizontalLayout_11->addLayout(gLayoutOpenFile_2);

        tabCalcDataset->addTab(tabInput_3_Page_2, QString());

        vLayoutInput3->addWidget(tabCalcDataset);


        vLayoutInputComponents->addLayout(vLayoutInput3);

        sepHLine_3 = new QFrame(gBoxInput);
        sepHLine_3->setObjectName(QString::fromUtf8("sepHLine_3"));
        sepHLine_3->setFrameShape(QFrame::HLine);
        sepHLine_3->setFrameShadow(QFrame::Sunken);

        vLayoutInputComponents->addWidget(sepHLine_3);

        pButtonRun = new QPushButton(gBoxInput);
        pButtonRun->setObjectName(QString::fromUtf8("pButtonRun"));
        pButtonRun->setMinimumSize(QSize(100, 23));
        pButtonRun->setMaximumSize(QSize(100, 16777215));

        vLayoutInputComponents->addWidget(pButtonRun);

        vLayoutInputComponents->setStretch(1, 1);

        gridLayout->addLayout(vLayoutInputComponents, 0, 0, 1, 1);


        vLayoutInput->addWidget(gBoxInput);


        verticalLayout_8->addLayout(vLayoutInput);

        vLayoutOutput = new QVBoxLayout();
        vLayoutOutput->setObjectName(QString::fromUtf8("vLayoutOutput"));
        gBoxOutput = new QGroupBox(centralwidget);
        gBoxOutput->setObjectName(QString::fromUtf8("gBoxOutput"));
        gridLayout_2 = new QGridLayout(gBoxOutput);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        vLayoutDisplay = new QVBoxLayout();
        vLayoutDisplay->setSpacing(5);
        vLayoutDisplay->setObjectName(QString::fromUtf8("vLayoutDisplay"));
        vLayoutDisplay->setContentsMargins(5, 5, 5, 5);
        outputText = new QTextBrowser(gBoxOutput);
        outputText->setObjectName(QString::fromUtf8("outputText"));

        vLayoutDisplay->addWidget(outputText);

        gViewDisplay = new QGraphicsView(gBoxOutput);
        gViewDisplay->setObjectName(QString::fromUtf8("gViewDisplay"));

        vLayoutDisplay->addWidget(gViewDisplay);


        gridLayout_2->addLayout(vLayoutDisplay, 0, 0, 1, 1);


        vLayoutOutput->addWidget(gBoxOutput);


        verticalLayout_8->addLayout(vLayoutOutput);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 761, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabDistribution->setCurrentIndex(2);
        tabCalcDataset->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "[M1.07] - REDUCE Paradigm", nullptr));
        gBoxInput->setTitle(QCoreApplication::translate("MainWindow", "Input", nullptr));
        lblAlgorithm->setText(QCoreApplication::translate("MainWindow", "Algorithm", nullptr));
        lblMatSize->setText(QCoreApplication::translate("MainWindow", "Set matrix size", nullptr));
        cBoxDataType->setItemText(0, QCoreApplication::translate("MainWindow", "(default)", nullptr));
        cBoxDataType->setItemText(1, QCoreApplication::translate("MainWindow", "Array", nullptr));
        cBoxDataType->setItemText(2, QCoreApplication::translate("MainWindow", "Matrix", nullptr));

        lblDataType->setText(QCoreApplication::translate("MainWindow", "Data Type", nullptr));
        cBoxAlgorithm->setItemText(0, QCoreApplication::translate("MainWindow", "(default)", nullptr));
        cBoxAlgorithm->setItemText(1, QCoreApplication::translate("MainWindow", "Sum", nullptr));
        cBoxAlgorithm->setItemText(2, QCoreApplication::translate("MainWindow", "Multiplication", nullptr));
        cBoxAlgorithm->setItemText(3, QCoreApplication::translate("MainWindow", "Element-wise multiplication", nullptr));

        lblDistribution->setText(QCoreApplication::translate("MainWindow", "Distribution", nullptr));
#if QT_CONFIG(accessibility)
        tabDistribution->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
        lblPara_1->setText(QCoreApplication::translate("MainWindow", "a =", nullptr));
        lblUniform_1->setText(QCoreApplication::translate("MainWindow", "Uniform", nullptr));
        lblUniform_2->setText(QCoreApplication::translate("MainWindow", "U(a,b)", nullptr));
        lblPara_2->setText(QCoreApplication::translate("MainWindow", "b =", nullptr));
        lblGauss_2->setText(QCoreApplication::translate("MainWindow", "N(\316\274, \317\203^2)", nullptr));
        lblGauss_1->setText(QCoreApplication::translate("MainWindow", "Gaussian", nullptr));
        lblPara_3->setText(QCoreApplication::translate("MainWindow", "\316\274 =", nullptr));
        lblPara_4->setText(QCoreApplication::translate("MainWindow", "\317\203^2 =", nullptr));
        lblPara_6->setText(QString());
        lblExp_1->setText(QCoreApplication::translate("MainWindow", "Exponential", nullptr));
        lblExp_2->setText(QCoreApplication::translate("MainWindow", "Exp(\316\273)", nullptr));
        lblPara_5->setText(QCoreApplication::translate("MainWindow", "\316\273 =", nullptr));
        lblGamma_1->setText(QCoreApplication::translate("MainWindow", "Gamma", nullptr));
        lblGamma_2->setText(QCoreApplication::translate("MainWindow", "G(\316\261, \316\273)", nullptr));
        lblPara_7->setText(QCoreApplication::translate("MainWindow", "\316\261 =", nullptr));
        lblPara_8->setText(QCoreApplication::translate("MainWindow", "\316\273 =", nullptr));
        tabDistribution->setTabText(tabDistribution->indexOf(tabInput_2_Page_1), QCoreApplication::translate("MainWindow", "Parameters only", nullptr));
        lblEquation->setText(QCoreApplication::translate("MainWindow", "Edit an equation...", nullptr));
        tabDistribution->setTabText(tabDistribution->indexOf(tabInput_2_Page_2), QCoreApplication::translate("MainWindow", "Mixture", nullptr));
        lblMessage_1->setText(QCoreApplication::translate("MainWindow", "Message", nullptr));
        pButtonOpenFile_1->setText(QCoreApplication::translate("MainWindow", "Open File...", nullptr));
        pButtonOK_1->setText(QCoreApplication::translate("MainWindow", "OK", nullptr));
        tabDistribution->setTabText(tabDistribution->indexOf(tabInput_2_Page_3), QCoreApplication::translate("MainWindow", "Import from a file", nullptr));
        lblCalcDataset->setText(QCoreApplication::translate("MainWindow", "Calculation dataset", nullptr));
#if QT_CONFIG(accessibility)
        tabCalcDataset->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
        pButtonGen->setText(QCoreApplication::translate("MainWindow", "Generate!", nullptr));
        tabCalcDataset->setTabText(tabCalcDataset->indexOf(tabInput_3_Page_1), QCoreApplication::translate("MainWindow", "Generated randomly", nullptr));
        lblMessage_2->setText(QCoreApplication::translate("MainWindow", "Message", nullptr));
        pButtonOpenFile_2->setText(QCoreApplication::translate("MainWindow", "Open File...", nullptr));
        pButtonOK_2->setText(QCoreApplication::translate("MainWindow", "OK", nullptr));
        tabCalcDataset->setTabText(tabCalcDataset->indexOf(tabInput_3_Page_2), QCoreApplication::translate("MainWindow", "Import from a file", nullptr));
        pButtonRun->setText(QCoreApplication::translate("MainWindow", "Run Experiment", nullptr));
        gBoxOutput->setTitle(QCoreApplication::translate("MainWindow", "Output", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
