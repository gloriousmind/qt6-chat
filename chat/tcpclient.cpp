#include "tcpclient.h"
#include "ui_tcpclient.h"
#include <QMessageBox>

TcpClient::TcpClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TcpClient)
{
    ui->setupUi(this);

    TotalBytes = 0;
    bytesReceived = 0;
    fileNameSize = 0;

    tcpClient_socket = new QTcpSocket(this);
    tcpPort = 6666;
    connect(tcpClient_socket, &QTcpSocket::readyRead, this, &TcpClient::receiveFile);
    connect(tcpClient_socket, &QAbstractSocket::errorOccurred, this, &TcpClient::displayError);
}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::set_fileInterface(QString selectedFile)
{
    fileInterface = new QFile(selectedFile);
}


void TcpClient::initialize_connection(QHostAddress address)
{
    hostAddress = address;
    newConnect();
}

void TcpClient::newConnect()
{
    blockSize = 0;
    tcpClient_socket->abort();
    tcpClient_socket->connectToHost(hostAddress, tcpPort);
    time.start();
}

void TcpClient::receiveFile()
{
    qDebug() << tcpClient_socket->bytesAvailable();
    QDataStream in(tcpClient_socket);
    in.setVersion(QDataStream::Qt_5_15);

    float useTime = time.elapsed();

    if (bytesReceived <= (qint64) sizeof(qint64) * 2)
    {
        if (tcpClient_socket->bytesAvailable() >= (qint64) sizeof(qint64) * 2)
        {
            in >> TotalBytes >> fileNameSize;
            bytesReceived += sizeof(qint64) * 2;
        }
    }

    if (bytesReceived == (qint64) sizeof (qint64) * 2)
    {
        if (tcpClient_socket->bytesAvailable() >= fileNameSize)
        {
            in >> fileName;
            bytesReceived += fileNameSize;

            if (!fileInterface->open(QFile::WriteOnly))
            {
                QMessageBox::warning(this, "应用程序", QString("无法读取文件 %1:\n%2.").arg(fileName).arg(fileInterface->errorString()));
            }
            else
                return;
        }
    }

    if (fileNameSize != 0 && bytesReceived >= (qint64) sizeof (qint64) * 2 + fileNameSize && bytesReceived < TotalBytes)
    {
        qDebug() << "try to rad remaining data";
        bytesReceived += tcpClient_socket->bytesAvailable();
        inBlock = tcpClient_socket->readAll();
        fileInterface->write(inBlock);
        inBlock.resize(0);
    }

    ui->progressBar->setMaximum(TotalBytes);
    ui->progressBar->setValue(bytesReceived);

    double speed = bytesReceived / useTime;
    ui->tcpClientStatusLabel->setText(QString("已接收 %1MB (%2MB/s) \n共%3MB已用时:%4秒\n估计剩余时间:%5秒")
                                      .arg(bytesReceived / (1024 * 1024))
                                      .arg(speed * 1000 / (1024 * 1024), 0, 'f', 0)
                                      .arg(TotalBytes / (1024 * 1024))
                                      .arg(useTime / 1000, 0, 'f', 0)
                                      .arg(TotalBytes / speed / 1000 - useTime / 1000, 0, 'f', 0));
    if (bytesReceived == TotalBytes)
    {
        fileInterface->close();
        tcpClient_socket->close();
        ui->tcpClientStatusLabel->setText(QString("接收文件 %1 完毕").arg(fileName));
    }
}

void TcpClient::displayError(QAbstractSocket::SocketError socketError)
{
    switch(socketError)
    {
    case QAbstractSocket::RemoteHostClosedError :
        break;
    default : qDebug() << tcpClient_socket->errorString();
    }
}

void TcpClient::on_tcpClientCancleBtn_clicked()
{
    tcpClient_socket->abort();
    if (fileInterface->isOpen())
        fileInterface->close();
}

void TcpClient::on_tcpClientCloseBtn_clicked()
{
    tcpClient_socket->abort();
    if (fileInterface->isOpen())
        fileInterface->close();
    close();
}

void TcpClient::closeEvent(QCloseEvent *)
{
    on_tcpClientCloseBtn_clicked();
}
