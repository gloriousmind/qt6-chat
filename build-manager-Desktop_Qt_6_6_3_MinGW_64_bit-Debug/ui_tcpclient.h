/********************************************************************************
** Form generated from reading UI file 'tcpclient.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPCLIENT_H
#define UI_TCPCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_TcpClient
{
public:
    QPushButton *tcpClientCancleBtn;
    QPushButton *tcpClientCloseBtn;
    QLabel *tcpClientStatusLabel;
    QProgressBar *progressBar;

    void setupUi(QDialog *TcpClient)
    {
        if (TcpClient->objectName().isEmpty())
            TcpClient->setObjectName("TcpClient");
        TcpClient->resize(564, 428);
        tcpClientCancleBtn = new QPushButton(TcpClient);
        tcpClientCancleBtn->setObjectName("tcpClientCancleBtn");
        tcpClientCancleBtn->setGeometry(QRect(21, 381, 93, 28));
        tcpClientCloseBtn = new QPushButton(TcpClient);
        tcpClientCloseBtn->setObjectName("tcpClientCloseBtn");
        tcpClientCloseBtn->setGeometry(QRect(437, 381, 93, 28));
        tcpClientStatusLabel = new QLabel(TcpClient);
        tcpClientStatusLabel->setObjectName("tcpClientStatusLabel");
        tcpClientStatusLabel->setGeometry(QRect(102, 79, 351, 71));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        tcpClientStatusLabel->setFont(font);
        tcpClientStatusLabel->setAlignment(Qt::AlignCenter);
        progressBar = new QProgressBar(TcpClient);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(40, 210, 501, 23));
        progressBar->setValue(0);

        retranslateUi(TcpClient);

        QMetaObject::connectSlotsByName(TcpClient);
    } // setupUi

    void retranslateUi(QDialog *TcpClient)
    {
        TcpClient->setWindowTitle(QCoreApplication::translate("TcpClient", "\346\216\245\346\224\266\347\253\257", nullptr));
        tcpClientCancleBtn->setText(QCoreApplication::translate("TcpClient", "\345\217\226\346\266\210", nullptr));
        tcpClientCloseBtn->setText(QCoreApplication::translate("TcpClient", "\345\205\263\351\227\255", nullptr));
        tcpClientStatusLabel->setText(QCoreApplication::translate("TcpClient", "\347\255\211\345\276\205\346\216\245\346\224\266\346\226\207\344\273\266\342\200\242\342\200\242\342\200\242 \342\200\242\342\200\242\342\200\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TcpClient: public Ui_TcpClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPCLIENT_H
