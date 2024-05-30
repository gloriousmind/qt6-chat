/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QFontComboBox *fontComboBox;
    QToolButton *italicToolBtn;
    QToolButton *sendToolBtn;
    QToolButton *underlineToolBtn;
    QToolButton *boldToolBtn;
    QToolButton *colorToolBtn;
    QTextBrowser *messageBrowser;
    QTextEdit *messageTextEdit;
    QLabel *userNumLabel;
    QComboBox *sizeComboBox;
    QTableWidget *userTableWidget;
    QPushButton *sendButton;
    QPushButton *exitButton;
    QToolButton *clearToolBtn;
    QToolButton *saveToolBtn;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(925, 602);
        fontComboBox = new QFontComboBox(Widget);
        fontComboBox->setObjectName("fontComboBox");
        fontComboBox->setGeometry(QRect(13, 341, 105, 21));
        fontComboBox->setMinimumSize(QSize(60, 0));
        fontComboBox->setMaximumSize(QSize(250, 16777215));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(9);
        fontComboBox->setFont(font);
        fontComboBox->setEditable(false);
        italicToolBtn = new QToolButton(Widget);
        italicToolBtn->setObjectName("italicToolBtn");
        italicToolBtn->setGeometry(QRect(233, 341, 42, 21));
        italicToolBtn->setIconSize(QSize(30, 30));
        italicToolBtn->setCheckable(true);
        sendToolBtn = new QToolButton(Widget);
        sendToolBtn->setObjectName("sendToolBtn");
        sendToolBtn->setGeometry(QRect(381, 341, 43, 21));
        sendToolBtn->setIconSize(QSize(30, 30));
        underlineToolBtn = new QToolButton(Widget);
        underlineToolBtn->setObjectName("underlineToolBtn");
        underlineToolBtn->setGeometry(QRect(282, 341, 43, 21));
        underlineToolBtn->setIconSize(QSize(30, 30));
        underlineToolBtn->setCheckable(true);
        boldToolBtn = new QToolButton(Widget);
        boldToolBtn->setObjectName("boldToolBtn");
        boldToolBtn->setGeometry(QRect(183, 341, 43, 21));
        boldToolBtn->setIconSize(QSize(30, 30));
        boldToolBtn->setCheckable(true);
        boldToolBtn->setAutoRaise(true);
        colorToolBtn = new QToolButton(Widget);
        colorToolBtn->setObjectName("colorToolBtn");
        colorToolBtn->setGeometry(QRect(332, 341, 42, 21));
        colorToolBtn->setIconSize(QSize(30, 30));
        messageBrowser = new QTextBrowser(Widget);
        messageBrowser->setObjectName("messageBrowser");
        messageBrowser->setGeometry(QRect(10, 0, 514, 331));
        messageTextEdit = new QTextEdit(Widget);
        messageTextEdit->setObjectName("messageTextEdit");
        messageTextEdit->setGeometry(QRect(10, 370, 521, 181));
        userNumLabel = new QLabel(Widget);
        userNumLabel->setObjectName("userNumLabel");
        userNumLabel->setGeometry(QRect(508, 569, 98, 16));
        sizeComboBox = new QComboBox(Widget);
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->addItem(QString());
        sizeComboBox->setObjectName("sizeComboBox");
        sizeComboBox->setGeometry(QRect(125, 341, 47, 21));
        sizeComboBox->setFont(font);
        userTableWidget = new QTableWidget(Widget);
        if (userTableWidget->columnCount() < 3)
            userTableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        userTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        userTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        userTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        userTableWidget->setObjectName("userTableWidget");
        userTableWidget->setGeometry(QRect(533, 1, 381, 551));
        userTableWidget->setMinimumSize(QSize(120, 0));
        userTableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        userTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        userTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        userTableWidget->setShowGrid(false);
        userTableWidget->horizontalHeader()->setMinimumSectionSize(45);
        userTableWidget->horizontalHeader()->setDefaultSectionSize(120);
        userTableWidget->verticalHeader()->setDefaultSectionSize(45);
        sendButton = new QPushButton(Widget);
        sendButton->setObjectName("sendButton");
        sendButton->setGeometry(QRect(209, 560, 93, 28));
        exitButton = new QPushButton(Widget);
        exitButton->setObjectName("exitButton");
        exitButton->setGeometry(QRect(815, 560, 93, 28));
        clearToolBtn = new QToolButton(Widget);
        clearToolBtn->setObjectName("clearToolBtn");
        clearToolBtn->setGeometry(QRect(480, 341, 42, 21));
        clearToolBtn->setIconSize(QSize(30, 30));
        saveToolBtn = new QToolButton(Widget);
        saveToolBtn->setObjectName("saveToolBtn");
        saveToolBtn->setGeometry(QRect(431, 341, 42, 21));
        saveToolBtn->setIconSize(QSize(30, 30));

        retranslateUi(Widget);

        sizeComboBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        fontComboBox->setCurrentText(QCoreApplication::translate("Widget", "\345\256\213\344\275\223", nullptr));
#if QT_CONFIG(tooltip)
        italicToolBtn->setToolTip(QCoreApplication::translate("Widget", "\346\226\234\344\275\223", nullptr));
#endif // QT_CONFIG(tooltip)
        italicToolBtn->setText(QCoreApplication::translate("Widget", "...", nullptr));
#if QT_CONFIG(tooltip)
        sendToolBtn->setToolTip(QCoreApplication::translate("Widget", "\344\274\240\350\276\223\346\226\207\344\273\266", nullptr));
#endif // QT_CONFIG(tooltip)
        sendToolBtn->setText(QCoreApplication::translate("Widget", "...", nullptr));
#if QT_CONFIG(tooltip)
        underlineToolBtn->setToolTip(QCoreApplication::translate("Widget", "\344\270\213\345\210\222\347\272\277", nullptr));
#endif // QT_CONFIG(tooltip)
        underlineToolBtn->setText(QCoreApplication::translate("Widget", "...", nullptr));
#if QT_CONFIG(tooltip)
        boldToolBtn->setToolTip(QCoreApplication::translate("Widget", "\345\212\240\347\262\227", nullptr));
#endif // QT_CONFIG(tooltip)
        boldToolBtn->setText(QCoreApplication::translate("Widget", "...", nullptr));
#if QT_CONFIG(tooltip)
        colorToolBtn->setToolTip(QCoreApplication::translate("Widget", "\346\233\264\346\224\271\345\255\227\344\275\223\351\242\234\350\211\262", nullptr));
#endif // QT_CONFIG(tooltip)
        colorToolBtn->setText(QCoreApplication::translate("Widget", "...", nullptr));
        userNumLabel->setText(QCoreApplication::translate("Widget", "\345\234\250\347\272\277\347\224\250\346\210\267\357\274\2320\344\272\272", nullptr));
        sizeComboBox->setItemText(0, QCoreApplication::translate("Widget", "9", nullptr));
        sizeComboBox->setItemText(1, QCoreApplication::translate("Widget", "10", nullptr));
        sizeComboBox->setItemText(2, QCoreApplication::translate("Widget", "11", nullptr));
        sizeComboBox->setItemText(3, QCoreApplication::translate("Widget", "12", nullptr));
        sizeComboBox->setItemText(4, QCoreApplication::translate("Widget", "13", nullptr));
        sizeComboBox->setItemText(5, QCoreApplication::translate("Widget", "14", nullptr));
        sizeComboBox->setItemText(6, QCoreApplication::translate("Widget", "15", nullptr));
        sizeComboBox->setItemText(7, QCoreApplication::translate("Widget", "16", nullptr));
        sizeComboBox->setItemText(8, QCoreApplication::translate("Widget", "17", nullptr));
        sizeComboBox->setItemText(9, QCoreApplication::translate("Widget", "18", nullptr));
        sizeComboBox->setItemText(10, QCoreApplication::translate("Widget", "19", nullptr));
        sizeComboBox->setItemText(11, QCoreApplication::translate("Widget", "20", nullptr));
        sizeComboBox->setItemText(12, QCoreApplication::translate("Widget", "21", nullptr));
        sizeComboBox->setItemText(13, QCoreApplication::translate("Widget", "22", nullptr));

        sizeComboBox->setCurrentText(QCoreApplication::translate("Widget", "9", nullptr));
        QTableWidgetItem *___qtablewidgetitem = userTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Widget", "\347\224\250\346\210\267\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = userTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Widget", "\344\270\273\346\234\272\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = userTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Widget", "IP\345\234\260\345\235\200", nullptr));
        sendButton->setText(QCoreApplication::translate("Widget", "\345\217\221\351\200\201", nullptr));
        exitButton->setText(QCoreApplication::translate("Widget", "\351\200\200\345\207\272", nullptr));
#if QT_CONFIG(tooltip)
        clearToolBtn->setToolTip(QCoreApplication::translate("Widget", "\346\270\205\347\251\272\350\201\212\345\244\251\350\256\260\345\275\225", nullptr));
#endif // QT_CONFIG(tooltip)
        clearToolBtn->setText(QCoreApplication::translate("Widget", "...", nullptr));
#if QT_CONFIG(tooltip)
        saveToolBtn->setToolTip(QCoreApplication::translate("Widget", "\344\277\235\345\255\230\350\201\212\345\244\251\350\256\260\345\275\225", nullptr));
#endif // QT_CONFIG(tooltip)
        saveToolBtn->setText(QCoreApplication::translate("Widget", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
