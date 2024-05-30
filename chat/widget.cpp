#include "widget.h"
#include "ui_widget.h"
#include <QUdpSocket>
#include <QHostInfo>
#include <QMessageBox>
#include <QScrollBar>
#include <QDateTime>
#include <QNetworkInterface>
#include <QProcess>
#include "tcpclient.h"
#include "tcpserver.h"
#include <QFileDialog>
#include <QColorDialog>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->boldToolBtn->setIcon(QIcon(":/image/bold.png"));
    ui->italicToolBtn->setIcon(QIcon(":/image/italic.png"));
    ui->underlineToolBtn->setIcon(QIcon(":/image/under.png"));
    ui->colorToolBtn->setIcon(QIcon(":/image/color.png"));
    ui->sendToolBtn->setIcon(QIcon(":/image/send.png"));
    ui->saveToolBtn->setIcon(QIcon(":/image/save.png"));
    ui->clearToolBtn->setIcon(QIcon(":/image/clear.png"));

    ui->messageTextEdit->setFocus();

    udpSocket = new QUdpSocket(this);
    port = 45454;
    udpSocket->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(udpSocket, &QUdpSocket::readyRead, this, &Widget::processPendingDatagrams);
    sendMessage(NewParticipant, getIP());

    server = new TcpServer(this);
    connect(server, &TcpServer::sendFileName, this, &Widget::getFileName);

    connect(ui->messageTextEdit, &QTextEdit::currentCharFormatChanged, this, &Widget::currentFormatChanged);
}

Widget::~Widget()
{
    delete ui;
}

//获取ip地址
QString Widget::getIP()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol)
            return address.toString();
    }
    return 0;
}

//获取用户名
QString Widget::getUserName()
{
    QStringList envVariables;
    envVariables << "USERNAME.*" << "USER.*" << "USERDOMAIN.*" << "HOSTNAME.*" << "DOMAINNAME.*";
    QStringList environment = QProcess::systemEnvironment();
    foreach (QString str, envVariables)
    {
        int index = environment.indexOf(QRegularExpression(str));
        if (index != -1)
        {
            QStringList stringList = environment.at(index).split('=');
            if (stringList.size() == 2)
            {
                return stringList.at(1);
            }
        }
    }
    return "unknown";
}

//获得要发送的信息
QString Widget::getMessage()
{
    QString msg = ui->messageTextEdit->toHtml();

    ui->messageTextEdit->clear();
    ui->messageTextEdit->setFocus();
    return msg;
}

//使用Udp广播发送信息
void Widget::sendMessage(MessageType type, QString address)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    QString localHostName = QHostInfo::localHostName();
    out << type << getUserName() << localHostName;

    switch(type)
    {
        case Message:
        {
            if (ui->messageTextEdit->toPlainText() == "")
            {
                QMessageBox::warning(nullptr, "警告", "发送内容不能为空", QMessageBox::Ok);
                return;
            }
            out << address << getMessage();
            ui->messageBrowser->verticalScrollBar()->setValue(ui->messageBrowser->verticalScrollBar()->maximum());
            break;
        }
        case NewParticipant:
        {
            out << address;
            break;
        }
        case ParticipantLeft:
            break;
        case FileName:
        {
            int row = ui->userTableWidget->currentRow();
            QString receiver_ip = ui->userTableWidget->item(row, 2)->text();
            QString sender_ip = address;
            out << sender_ip << receiver_ip << fileName;
            break;
        }
        case Refuse:
        {
            out << address;
            break;
        }
    }
    udpSocket->writeDatagram(data, data.length(), QHostAddress::Broadcast, port);
}

//处理新用户加入
void Widget::newParticipant(QString userName, QString localHostName, QString ipAddress)
{
    bool isEmpty = ui->userTableWidget->findItems(localHostName, Qt::MatchExactly).isEmpty();
    if (isEmpty)
    {
        QTableWidgetItem * user = new QTableWidgetItem(userName);
        QTableWidgetItem * host = new QTableWidgetItem(localHostName);
        QTableWidgetItem * ip = new QTableWidgetItem(ipAddress);

        ui->userTableWidget->insertRow(0);
        ui->userTableWidget->setItem(0, 0, user);
        ui->userTableWidget->setItem(0, 1, host);
        ui->userTableWidget->setItem(0, 2, ip);
        ui->messageBrowser->setTextColor(Qt::gray);
        ui->messageBrowser->setCurrentFont(QFont("Times New Roman", 10));
        ui->messageBrowser->append(QString("%1 在线!").arg(userName));
        ui->userNumLabel->setText(QString("在线人数: %1").arg(ui->userTableWidget->rowCount()));

        sendMessage(NewParticipant, getIP());
    }
}

//处理用户离开
void Widget::participantLeft(QString userName, QString localHostName, QString time)
{
    int rowNum = ui->userTableWidget->findItems(localHostName, Qt::MatchExactly).first()->row();
    ui->userTableWidget->removeRow(rowNum);
    ui->messageBrowser->setTextColor(Qt::gray);
    ui->messageBrowser->setCurrentFont(QFont("Times New Roman", 10));
    ui->messageBrowser->append(QString("%1 于 %2 离开!").arg(userName).arg(time));
    ui->userNumLabel->setText(QString("在线人数: %1").arg(ui->userTableWidget->rowCount()));
}

void Widget::hasPendingFile(QString userName, QString serverAddress, QString clientAddress, QString fileName)
{
    QString ipAddress = getIP();
    if (ipAddress == clientAddress)
    {
        int btn = QMessageBox::information(this, "接受文件", QString("来自%1(%2)的文件:%3, 是否接收?").arg(userName).arg(serverAddress).arg(fileName), QMessageBox::Yes, QMessageBox::No);
        if (btn == QMessageBox::Yes)
        {
            QString name = QFileDialog::getSaveFileName(0, "保存文件", fileName);
            if (!name.isEmpty())
            {
                TcpClient * client = new TcpClient(this);
                client->setFileName(name);
                client->setHostAddress(QHostAddress(serverAddress));
                client->show();
            }
        }
        else
        {
            sendMessage(Refuse, serverAddress);
        }
    }
}

//接受udp广播发送来的消息
void Widget::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        QDataStream in(&datagram, QIODevice::ReadOnly);
        int messageType;
        in >> messageType;
        QString userName, localHostName, ipAddress, message;
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        switch(messageType)
        {
            case Message:
                in >> userName >> localHostName >> ipAddress >> message;
                ui->messageBrowser->setTextColor(Qt::blue);
                ui->messageBrowser->setCurrentFont(QFont("Times New Roman", 12));
                ui->messageBrowser->append("[ " + userName + " ] " + time);
                ui->messageBrowser->append(message);
                break;

            case NewParticipant:
                in >> userName >> localHostName >> ipAddress;
                newParticipant(userName, localHostName, ipAddress);
                break;

            case ParticipantLeft:
                in >> userName >> localHostName;
                participantLeft(userName, localHostName, time);
                break;
            case FileName:
            {
                in >> userName >> localHostName >> ipAddress;
                QString clientAddress, fileName;
                in >> clientAddress >> fileName;
                hasPendingFile(userName, ipAddress, clientAddress, fileName);
                break;
            }

            case Refuse:
            {
                in >> userName >> localHostName;
                QString refused_serverAddress;
                in >> refused_serverAddress;
                QString ipAddress = getIP();

                if (ipAddress == refused_serverAddress)
                    server->refused();
                break;
            }
        }
    }
}

void Widget::on_sendButton_clicked()
{
    sendMessage(Message, getIP());
}

void Widget::getFileName(QString name)
{
    fileName = name;
    sendMessage(FileName,getIP());
}

void Widget::on_sendToolBtn_clicked()
{
    if (ui->userTableWidget->selectedItems().isEmpty())
    {
        QMessageBox::warning(0, "选择用户", "请先从用户列表选择要传送的用户!", QMessageBox::Ok);
        return;
    }
    server->show();
    server->initServer();
}

void Widget::on_boldToolBtn_clicked(bool checked)
{
    if (checked)
        ui->messageTextEdit->setFontWeight(QFont::Bold);
    else
        ui->messageTextEdit->setFontWeight(QFont::Normal);
    ui->messageTextEdit->setFocus();
}

void Widget::on_italicToolBtn_clicked(bool checked)
{
    ui->messageTextEdit->setFontItalic(checked);
    ui->messageTextEdit->setFocus();
}

void Widget::on_underlineToolBtn_clicked(bool checked)
{
    ui->messageTextEdit->setFontUnderline(checked);
    ui->messageTextEdit->setFocus();
}

void Widget::on_colorToolBtn_clicked()
{
    color = QColorDialog::getColor(color, this);
    ui->messageTextEdit->setTextColor(color);
    ui->messageTextEdit->setFocus();
}

void Widget::on_fontComboBox_currentFontChanged(const QFont &f)
{
    ui->messageTextEdit->setCurrentFont(f);
    ui->messageTextEdit->setFocus();
}

void Widget::on_sizeComboBox_currentIndexChanged(int index)
{
    ui->messageTextEdit->setFontPointSize(ui->sizeComboBox->itemText(index).toDouble());
    ui->messageTextEdit->setFocus();
}

void Widget::currentFormatChanged(const QTextCharFormat &format)
{
    ui->fontComboBox->setCurrentFont(format.font());

    if (format.fontPointSize() < 9)
        ui->sizeComboBox->setCurrentIndex(0);
    else
        ui->sizeComboBox->setCurrentIndex(ui->sizeComboBox->findText(QString::number(format.fontPointSize())));
    ui->boldToolBtn->setChecked(format.font().bold());
    ui->italicToolBtn->setChecked(format.font().italic());
    ui->underlineToolBtn->setChecked(format.font().underline());
    color = format.foreground().color();
}

void Widget::on_saveToolBtn_clicked()
{
    if (ui->messageBrowser->document()->isEmpty())
    {
        QMessageBox::warning(0, "警告", "聊天记录为空, 无法保存!");
    }
    else
    {
        QString fileName = QFileDialog::getSaveFileName(this, "保存聊天记录", "聊天记录.txt", "Text File(*.txt);;All File(*.*)");
        if (!fileName.isEmpty())
            saveFile(fileName);
    }
}

bool Widget::saveFile(const QString & fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "保存文件", QString("无法保存文件 %1:\n %2").arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out << ui->messageBrowser->toPlainText();
    return true;
}

void Widget::on_clearToolBtn_clicked()
{
    ui->messageBrowser->clear();
}

void Widget::on_exitButton_clicked()
{
    close();
}

void Widget::closeEvent(QCloseEvent * e)
{
    sendMessage(ParticipantLeft, getIP());
    QWidget::closeEvent(e);
}
