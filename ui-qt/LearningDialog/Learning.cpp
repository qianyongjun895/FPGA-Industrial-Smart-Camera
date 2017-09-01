#include "Learning.h"
#include "ui_Learning.h"
#include <QSettings>
#include <QDebug>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
Learning::Learning(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Learning)
{
    ui->setupUi(this);
    this->move(272,520);
    this->setWindowFlags(Qt::WindowTitleHint);
    m_Timer = new QTimer;
    connect(m_Timer,&QTimer::timeout,this,&Learning::TimerSlot);
    ui->pushButton->setVisible(false);
    m_Timer->start(200);
}

Learning::~Learning()
{
    delete ui;
}

/**
 * @brief Learning::on_pushButton_clicked
 * @author dgq
 * @note OK按钮响应函数
 */
void Learning::on_pushButton_clicked()
{
    QDialog::reject();
}

/**
 * @brief Learning::SetResultString
 * @param code_str
 * @author dgq
 * @note 设置取样结果信息
 */
void Learning::SetResultString(QString code_str)
{
    ui->pushButton->setVisible(true);
    m_Timer->stop();
    m_rst_Str = code_str;
    ui->textBrowser->setText(code_str);
    ui->progressBar->setValue(100);

}

/**
 * @brief Learning::TimerSlot
 * @author dgq
 * @note 刷新进度条的定时器响应函数
 */
void Learning::TimerSlot()
{
//    qDebug()<<"ui->progressBar->value() =="<<ui->progressBar->value();
    if(ui->progressBar->value() < 99)
        ui->progressBar->setValue(ui->progressBar->value()+1);
    else
    {
        m_Timer->stop();
        ui->textBrowser->setText(tr("取样超时！"));
    }
}
