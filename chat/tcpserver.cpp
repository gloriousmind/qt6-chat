#include "tcpserver.h"
#include "ui_tcpserver.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QMessageBox>
#include <QElapsedTimer>
#include <QFileDialog>

TcpServer::TcpServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TcpServer)
{
    ui->setupUi(this);

    tcpPort = 6666;
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &TcpServer::sendMessage);

    initServer();
}

TcpServer::~TcpServer()
{
    delete ui;
}


void TcpServer::initServer()
{
    payloadSize = 64 * 1024;
    TotalBytes = 0;
    bytesWritten = 0;
    bytesToWrite = 0;

    ui->serverStatusLabel->setText("请选择要传送的文件!");
    ui->progressBar->reset();
    ui->serverOpenBtn->setEnabled(true);
    ui->serverSendBtn->setEnabled(false);

    tcpServer->close();
}

void TcpServer::on_serverOpenBtn_clicked()
{
    fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
    {
        theFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/') - 1);
        ui->serverStatusLabel->setText(QString("要传送的文件为:%1 ").arg(theFileName));
        ui->serverOpenBtn->setEnabled(false);
        ui->serverSendBtn->setEnabled(true);
    }
}

void TcpServer::on_serverSendBtn_clicked()
{
    emit sendFileName(theFileName);
    if (!tcpServer->listen(QHostAddress::Any, tcpPort))
    {
        qDebug() << tcpServer->errorString();
        close();
        return;
    }
    ui->serverStatusLabel->setText("等待对方接收... ...");

}

void TcpServer::sendMessage()
{
    ui->serverSendBtn->setEnabled(false);
    server_socket = tcpServer->nextPendingConnection();
    connect(server_socket, &QTcpSocket::bytesWritten, this, &TcpServer::updateClientProgress);
    ui->serverStatusLabel->setText(QString("开始传送文件 %1 !").arg(theFileName));

    localFile = new QFile(fileName);
    if (!localFile->open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, "应用程序", QString("无法读取文件 %1:\n%2").arg(fileName).arg(localFile->errorString()));
        return;
    }

    TotalBytes = localFile->size();
    QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_15);
    time.start();
    QString currentFile = fileName.right(fileName.size() - fileName.lastIndexOf('/') - 1);
    sendOut << qint64(0) << qint64(0) << currentFile;
    TotalBytes += outBlock.size();
    sendOut.device()->seek(0);
    sendOut << TotalBytes << qint64(outBlock.size() - sizeof(qint64) * 2);
    bytesToWrite = TotalBytes - server_socket->write(outBlock);
    outBlock.resize(0);

}

void TcpServer::updateClientProgress(qint64 numBytes)
{
    qApp->processEvents();
    bytesWritten += numBytes;
    if (bytesToWrite > 0)
    {
        outBlock = localFile->read(qMin(bytesToWrite, payloadSize));
        bytesToWrite -= server_socket->write(outBlock);
        outBlock.resize(0);
    }
    else
    {
        localFile->close();
    }
    ui->progressBar->setMaximum(TotalBytes);
    ui->progressBar->setValue(bytesWritten);

    float useTime = time.elapsed();
    double speed = bytesWritten / useTime;
    ui->serverStatusLabel->setText(QString("已发送 %1MB (%2MB/s) \n共%3MB 已用时：%4秒\n估计剩余时间:%5秒")
                                   .arg(bytesWritten / (1024 * 1024)).arg(speed * 1000 /(1024 * 1024))
                                   .arg(TotalBytes / (1024 * 1024)).arg(useTime / 1000, 0, 'f', 0)
                                   .arg(TotalBytes / speed / 1000 - useTime / 1000, 0, 'f', 0));
    if (bytesWritten == TotalBytes)
    {
        localFile->close();
        tcpServer->close();
        ui->serverStatusLabel->setText(tr("传送文件 %1 成功").arg(theFileName));
    }
}

void TcpServer::on_serverCloseBtn_clicked()
{
    if (tcpServer->isListening())
    {
        tcpServer->close();
        if (localFile->isOpen())
            localFile->close();
        server_socket->abort();
    }
    close();
}

void TcpServer::refused()
{
    tcpServer->close();
    ui->serverStatusLabel->setText("对方拒绝接收!!!");
}

void TcpServer::closeEvent(QCloseEvent * event)
{
    on_serverCloseBtn_clicked();
}
