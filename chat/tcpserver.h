#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QDialog>
#include <QElapsedTimer>

class QFile;
class QTcpServer;
class QTcpSocket;

namespace Ui {
class TcpServer;
}

class TcpServer : public QDialog
{
    Q_OBJECT

public:
    explicit TcpServer(QWidget *parent = nullptr);
    ~TcpServer();

    void initServer();
    void refused();

protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::TcpServer *ui;

    qint16 tcpPort;
    QTcpServer * tcpServer;
    QString selectedFile;
    QString fileName;
    QFile * selectedFile_interface;

    qint64 TotalBytes;
    qint64 bytesWritten;
    qint64 bytesToWrite;
    qint64 payloadSize;
    QByteArray outBlock;

    QTcpSocket * server_socket;

    QElapsedTimer time;

private slots:
    void transferFile();
    void updateClientProgress(qint64 numBytes);

    void on_serverOpenBtn_clicked();
    void on_serverSendBtn_clicked();
    void on_serverCloseBtn_clicked();

signals:
    void sendfile(QString selectedFile);
};

#endif // TCPSERVER_H
