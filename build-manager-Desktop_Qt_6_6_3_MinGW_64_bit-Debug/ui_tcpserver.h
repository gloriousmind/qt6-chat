/********************************************************************************
** Form generated from reading UI file 'tcpserver.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPSERVER_H
#define UI_TCPSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_TcpServer
{
public:
    QProgressBar *progressBar;
    QPushButton *serverOpenBtn;
    QPushButton *serverSendBtn;
    QPushButton *serverCloseBtn;
    QLabel *serverStatusLabel;

    void setupUi(QDialog *TcpServer)
    {
        if (TcpServer->objectName().isEmpty())
            TcpServer->setObjectName("TcpServer");
        TcpServer->resize(623, 400);
        progressBar = new QProgressBar(TcpServer);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(42, 176, 561, 23));
        progressBar->setValue(0);
        serverOpenBtn = new QPushButton(TcpServer);
        serverOpenBtn->setObjectName("serverOpenBtn");
        serverOpenBtn->setGeometry(QRect(42, 280, 93, 28));
        serverSendBtn = new QPushButton(TcpServer);
        serverSendBtn->setObjectName("serverSendBtn");
        serverSendBtn->setGeometry(QRect(255, 280, 93, 28));
        serverCloseBtn = new QPushButton(TcpServer);
        serverCloseBtn->setObjectName("serverCloseBtn");
        serverCloseBtn->setGeometry(QRect(468, 280, 93, 28));
        serverStatusLabel = new QLabel(TcpServer);
        serverStatusLabel->setObjectName("serverStatusLabel");
        serverStatusLabel->setGeometry(QRect(80, 50, 441, 91));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        serverStatusLabel->setFont(font);
        serverStatusLabel->setAlignment(Qt::AlignCenter);

        retranslateUi(TcpServer);

        QMetaObject::connectSlotsByName(TcpServer);
    } // setupUi

    void retranslateUi(QDialog *TcpServer)
    {
        TcpServer->setWindowTitle(QCoreApplication::translate("TcpServer", "Dialog", nullptr));
        serverOpenBtn->setText(QCoreApplication::translate("TcpServer", "\346\211\223\345\274\200", nullptr));
        serverSendBtn->setText(QCoreApplication::translate("TcpServer", "\345\217\221\351\200\201", nullptr));
        serverCloseBtn->setText(QCoreApplication::translate("TcpServer", "\345\205\263\351\227\255", nullptr));
        serverStatusLabel->setText(QCoreApplication::translate("TcpServer", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TcpServer: public Ui_TcpServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPSERVER_H
