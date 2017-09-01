#include "HeartBeatWidget.h"
#include "ui_HeartBeatWidget.h"
#include <QEvent>
#include <QDebug>
#include <QMessageBox>
#include "HeartBeatGlobal.h"
#include <QComboBox>
HeartBeatWidget::HeartBeatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeartBeatWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    ui->lineEdit_time->installEventFilter(this);
    ui->lineEdit_recv_string->installEventFilter(this);
    ui->lineEdit_send_string->installEventFilter(this);
    IniData();
}

HeartBeatWidget::~HeartBeatWidget()
{
    ui->lineEdit_time->removeEventFilter(this);
    ui->lineEdit_recv_string->removeEventFilter(this);
    ui->lineEdit_send_string->removeEventFilter(this);
    if(m_keyBoard_Lib.isLoaded())
    {
        m_keyBoard_Lib.unload();
    }
    delete ui;
}

void HeartBeatWidget::IniData()
{
    HEART_BEAT_STRUCT heart_Beat;
    heart_beat_config_get(&heart_Beat);
    if(heart_Beat.heart_beat_flag == 1){
        ui->comboBox->setCurrentIndex(heart_Beat.heart_beat_type);
        if(heart_Beat.heart_beat_type == 0){
            ui->lineEdit_time->setEnabled(false);
        }else{
            ui->lineEdit_time->setEnabled(true);
            ui->lineEdit_time->setText(QString::number(heart_Beat.pulse_time));
        }
        ui->lineEdit_recv_string->setText(QString::fromUtf8(heart_Beat.recv_str));
        ui->lineEdit_send_string->setText(QString::fromUtf8(heart_Beat.send_str));
        ui->pushButton_start->setText("关闭");
        ui->comboBox->setEnabled(false);
        ui->lineEdit_time->setEnabled(false);
        ui->lineEdit_recv_string->setEnabled(false);
        ui->lineEdit_send_string->setEnabled(false);
    }else{
        ui->comboBox->setCurrentIndex(heart_Beat.heart_beat_type);
        if(heart_Beat.heart_beat_type == 0){
            ui->lineEdit_time->setEnabled(false);
        }else{
            ui->lineEdit_time->setEnabled(true);
            ui->lineEdit_time->setText(QString::number(heart_Beat.pulse_time));
        }
        ui->lineEdit_recv_string->setText(QString::fromUtf8(heart_Beat.recv_str));
        ui->lineEdit_send_string->setText(QString::fromUtf8(heart_Beat.send_str));
        ui->pushButton_start->setText("启动");
        ui->comboBox->setEnabled(true);
        ui->lineEdit_time->setEnabled(true);
        ui->lineEdit_recv_string->setEnabled(true);
        ui->lineEdit_send_string->setEnabled(true);
    }
}

bool HeartBeatWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEdit_time){
        if(event->type() == QEvent::MouseButtonPress){
            if(((QLineEdit *)watched)->isEnabled()){
                NumKeyBoardDlg(watched, event);
            }
        }
    }
    if(watched == ui->lineEdit_recv_string || watched == ui->lineEdit_send_string){
        if(event->type() == QEvent::MouseButtonPress){
            if(((QLineEdit *)watched)->isEnabled()){
                KeyBoardDlg(watched, event,0, 0, HEART_BEAT_DATA_SIZE);
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void HeartBeatWidget::LoadKeyBoardLib()
{
    m_keyBoard_Lib.setFileName("libFrmInputKeyBoard.so");
    if(m_keyBoard_Lib.isLoaded())
    {
        return;
    }
    if(m_keyBoard_Lib.load())
    {
        qDebug()<<"libFrmInputKeyBoard.so OK";
    }
    else
    {
        qDebug()<<"load libFrmInputKeyBoard.so fail"<<m_keyBoard_Lib.errorString();
    }
}

void HeartBeatWidget::NumKeyBoardDlg(QObject *watched, QEvent *event)
{
    Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
    if(GetNumKeyBoardDlg)
    {
        Numkey = GetNumKeyBoardDlg();
        int ret = Numkey->exec();
        if(ret == QDialog::Accepted)
        {
            Fun_GetNumString GetNumString = (Fun_GetNumString)m_keyBoard_Lib.resolve("GetNum");
            if(GetNumString)
            {
                QString num = GetNumString();
                ((QLineEdit *)watched)->setText(num);
            }
        }
        delete Numkey;
        Numkey = NULL;
    }
    else
    {
        qDebug()<<"get GetDialog func fail:"<<m_keyBoard_Lib.errorString();
    }
}

void HeartBeatWidget::KeyBoardDlg(QObject *watched, QEvent *event, int dlg_x, int dlg_y, int String_Len)
{
    Fun_GetkeyBoardDlg GetKeyBoardDlg = (Fun_GetkeyBoardDlg)m_keyBoard_Lib.resolve("GetKeyBoardDialog");
    Fun_GetInputString GetInputString = (Fun_GetInputString)m_keyBoard_Lib.resolve("GetInputString");
    if(GetKeyBoardDlg)
    {
        m_dlg = GetKeyBoardDlg();
        if(!(dlg_x == 0 && dlg_y == 0))
            m_dlg->move(dlg_x, dlg_y);
        int ret = m_dlg->exec();
        if(ret == QDialog::Accepted)
        {
            if(GetInputString)
            {
                QString labelString =  GetInputString();
                if(labelString.length() > String_Len)
                {
                    QMessageBox::about(NULL, tr("提示"), tr("请输入长度小于")+QString::number(String_Len + 1)+tr("的字符串"));
                }
                else
                {
                    ((QLineEdit *)watched)->setText(labelString);
                }
            }
        }
        delete m_dlg;
        m_dlg = NULL;
    }
    else
    {
        qDebug()<<"get GetDialog func fail:"<<m_keyBoard_Lib.errorString();
    }
}

void HeartBeatWidget::on_pushButton_start_clicked()
{
    if(ui->comboBox->currentIndex() == 0){
        if(ui->lineEdit_recv_string->text() == ""){
            QMessageBox::about(NULL, "提示", "请设置接收数据");
            return;
        }
    }else{
        if(ui->lineEdit_time->text() == ""){
            QMessageBox::about(NULL, "提示", "请设置间隔时间");
            return;
        }
        if(ui->lineEdit_send_string->text() == ""){
            QMessageBox::about(NULL, "提示", "请设置发送数据");
            return;
        }
    }

    HEART_BEAT_STRUCT heart_Beat;
    if(ui->pushButton_start->text() == "启动"){
        heart_Beat.heart_beat_flag = 1;
        heart_Beat.heart_beat_type = ui->comboBox->currentIndex();
        if(heart_Beat.heart_beat_type == 1){
            QString time = ui->lineEdit_time->text();
            heart_Beat.pulse_time = time.toInt();
        }
        QString Recv_String = ui->lineEdit_recv_string->text();
        QString Send_String = ui->lineEdit_send_string->text();
        QByteArray Recv_ba = Recv_String.toUtf8();
        char *recv_string = Recv_ba.data();
        memset(heart_Beat.recv_str, 0, HEART_BEAT_DATA_SIZE);
        memcpy(heart_Beat.recv_str, recv_string, Recv_String.length());
        QByteArray Send_ba = Send_String.toUtf8();
        char *send_string = Send_ba.data();
        memset(heart_Beat.send_str, 0, HEART_BEAT_DATA_SIZE);
        memcpy(heart_Beat.send_str, send_string, Send_String.length());
        ui->comboBox->setEnabled(false);
        ui->lineEdit_time->setEnabled(false);
        ui->lineEdit_recv_string->setEnabled(false);
        ui->lineEdit_send_string->setEnabled(false);
        ui->pushButton_start->setText("关闭");
    }else{
        heart_Beat.heart_beat_flag = 0;
        ui->comboBox->setEnabled(true);
        ui->lineEdit_time->setEnabled(true);
        ui->lineEdit_recv_string->setEnabled(true);
        ui->lineEdit_send_string->setEnabled(true);
        ui->pushButton_start->setText("启动");
    }
    heart_beat_config_set(&heart_Beat);
}

void HeartBeatWidget::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0){
        ui->lineEdit_time->setEnabled(false);
    }else{
        ui->lineEdit_time->setEnabled(true);
    }
}
