#include <QDebug>
#include "DelayWidget.h"
#include "ui_DelayWidget.h"
#include "QMessageBox"

DelayWidget::DelayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DelayWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    ui->txtMinute->installEventFilter(this);
    ui->txtSecond->installEventFilter(this);
    ui->txtMicrosecond->installEventFilter(this);
    ui->txtMillisecond->installEventFilter(this);
}

DelayWidget::~DelayWidget()
{
    ui->txtMinute->removeEventFilter(this);
    ui->txtSecond->removeEventFilter(this);
    ui->txtMicrosecond->removeEventFilter(this);
    ui->txtMillisecond->removeEventFilter(this);
    delete ui;
}


QPoint DelayWidget::Get_Image_Pos()
{
    return QPoint(0,0);
}

void DelayWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    pInputPara = ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("pInputPara"));
        return;
    }
    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        ((DELAY_INPUT_PARAM *)pInputPara)->minutes = 0;
        ((DELAY_INPUT_PARAM *)pInputPara)->seconds = 0;
        ((DELAY_INPUT_PARAM *)pInputPara)->ms = 0;
        ((DELAY_INPUT_PARAM *)pInputPara)->us = 0;
    }
    InitData(i_step_index);
}


int DelayWidget::Set_Parameter_To_Ram()
{
    ((DELAY_INPUT_PARAM *)pInputPara)->minutes = ui->txtMinute->text().toInt();
    ((DELAY_INPUT_PARAM *)pInputPara)->seconds = ui->txtSecond->text().toInt();
    ((DELAY_INPUT_PARAM *)pInputPara)->ms = ui->txtMillisecond->text().toInt();
    ((DELAY_INPUT_PARAM *)pInputPara)->us = ui->txtMicrosecond->text().toInt();
    return 1;
}

bool DelayWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->txtMicrosecond ||watched == ui->txtMillisecond ||watched == ui->txtMinute ||watched == ui->txtSecond)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(!((QLineEdit *)watched)->isReadOnly())
            {
                Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
                if(GetNumKeyBoardDlg)
                {
                    QDialog *Numkey = GetNumKeyBoardDlg();
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
                }
            }
        }
    }
    return QWidget::eventFilter(watched,event);
}

void DelayWidget::InitData(int i_step_index)
{
    unsigned int minutes = ((DELAY_INPUT_PARAM *)pInputPara)->minutes;
    unsigned int seconds = ((DELAY_INPUT_PARAM *)pInputPara)->seconds;       //秒
    unsigned int ms = ((DELAY_INPUT_PARAM *)pInputPara)->ms;            //毫秒
    unsigned int us = ((DELAY_INPUT_PARAM *)pInputPara)->us;            //微秒
    ui->txtMinute->setText(QString::number(minutes));
    ui->txtMillisecond->setText(QString::number(ms));
    ui->txtMicrosecond->setText(QString::number(us));
    ui->txtSecond->setText(QString::number(seconds));
}

void DelayWidget::LoadKeyBoardLib()
{
    m_keyBoard_Lib.setFileName("libFrmInputKeyBoard.so");
    if(m_keyBoard_Lib.isLoaded())
    {
        qDebug()<<"load libFrmInputKeyBoard.so isLoaded";
        return;
    }
    if(m_keyBoard_Lib.load())
    {
        printf("libFrmInputKeyBoard.so OK\n");
    }
    else
    {
        qDebug()<<"load libFrmInputKeyBoard.so fail"<<m_keyBoard_Lib.errorString();
    }
}
