#include "MeanBrightnessWidget.h"
#include "ui_MeanBrightnessWidget.h"
#include "MeanBrightnessGlobal.h"
#include <QMessageBox>
#include <QDebug>
#include "FWMeanBrightnessLabel.h"
MeanBrightnessWidget::MeanBrightnessWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeanBrightnessWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    LoadLearnLib();
    QList<QLineEdit *> lineEdit = this->findChildren<QLineEdit *>();
    foreach (QLineEdit * L, lineEdit) {
        L->installEventFilter(this);
    }
    m_label = new FWMeanBrightnessLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);
    CalcTimer = new QTimer;
    connect(CalcTimer, &QTimer::timeout, this, &MeanBrightnessWidget::CalcTimerSlot);
}

MeanBrightnessWidget::~MeanBrightnessWidget()
{
    QList<QLineEdit *> lineEdit = this->findChildren<QLineEdit *>();
    foreach (QLineEdit * L, lineEdit) {
        L->removeEventFilter(this);
    }

    if(m_label !=NULL)
    {
        delete m_label;
        m_label = NULL;
    }
    delete CalcTimer;
    delete ui;
}

int MeanBrightnessWidget::Set_Parameter_To_Ram()
{
    SetInputData();
    return 1;
}

void MeanBrightnessWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    ((FWMeanBrightnessLabel*)m_label)->SetPenColor(pen_color);
    pInputPara = (MEANBRI_INPUT_PARAM*)ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }
    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        pInputPara->valid_brightness_range.high_enable = 0;
        pInputPara->valid_brightness_range.low_enable = 0;
    }
    InitData();
}

void MeanBrightnessWidget::InitData()
{
    if(pInputPara->valid_brightness_range.high_enable == TH_ENABLE)
        ui->lineEditMeanBrightnessMax->setText(QString::number(pInputPara->valid_brightness_range.high_threshold));

    if(pInputPara->valid_brightness_range.low_enable == TH_ENABLE)
        ui->lineEditMeanBrightnessMin->setText(QString::number(pInputPara->valid_brightness_range.low_threshold));
}

bool MeanBrightnessWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEditMeanBrightnessMax){
        if(event->type() == QEvent::MouseButtonPress){
            if(ui->lineEditMeanBrightnessMin->text() != "---"){
                NumKeyBoardDlg(watched, event, ui->lineEditMeanBrightnessMin->text().toInt(), 5000000);
            } else{
                NumKeyBoardDlg(watched, event, 0, 5000000);
            }
        }
    }
    if(watched == ui->lineEditMeanBrightnessMin){
        if(event->type() == QEvent::MouseButtonPress){
            if(ui->lineEditMeanBrightnessMax->text() != "---"){
                NumKeyBoardDlg(watched, event, 0, ui->lineEditMeanBrightnessMax->text().toInt());
            }else{
                NumKeyBoardDlg(watched, event, 0, 5000000);
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void MeanBrightnessWidget::LoadKeyBoardLib()
{
    m_keyBoard_Lib.setFileName("libFrmInputKeyBoard.so");
    if(m_keyBoard_Lib.isLoaded())
    {
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

void MeanBrightnessWidget::NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value)
{
    Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
    if(GetNumKeyBoardDlg){
        Numkey = GetNumKeyBoardDlg();
        ShowRangeEn RangEn = (ShowRangeEn)m_keyBoard_Lib.resolve("SetRangeEnvBtn");
        if(RangEn){
            RangEn();
        }else{
            return;
        }
        int ret = Numkey->exec();
        if(ret == QDialog::Accepted){
            Fun_GetNumString GetNumString = (Fun_GetNumString)m_keyBoard_Lib.resolve("GetNum");
            if(GetNumString){
                QString num = GetNumString();
                if(num.toInt() > Max_value || num.toInt() < Min_value){
                    QMessageBox::about(NULL, tr("提示"), tr("该值无效,请输入")+QString::number(Min_value)+tr("~")+QString::number(Max_value)+tr("之间的值"));
                    return;
                }
                ((QLineEdit *)watched)->setText(num);
            }
        }
        delete Numkey;
    }else{
        qDebug()<<"get GetDialog func fail:"<<m_keyBoard_Lib.errorString();
    }
}

void MeanBrightnessWidget::GetCalcDataShow()
{
    MEANBRI_PRIVATE_PARAM* p_Private = (MEANBRI_PRIVATE_PARAM*)Task_Step_Private_Para_Get(m_step_index);
    if(p_Private != NULL){
        ui->lineEditPixelNum->setText(QString::number(p_Private->model_meanbri_rst.total_area_num));
        ui->lineEditMeanValue->setText(QString::number(p_Private->model_meanbri_rst.mean_brightness));
        if(ui->checkBoxAuto->isChecked()){
            int value = p_Private->model_meanbri_rst.mean_brightness*1.2;
            ui->lineEditMeanBrightnessMax->setText(QString::number(value));
            value = p_Private->model_meanbri_rst.mean_brightness*0.8;
            ui->lineEditMeanBrightnessMin->setText(QString::number(value));
        }
    }
}

void MeanBrightnessWidget::SetInputData()
{
    if(ui->lineEditMeanBrightnessMax->text() == "---"){
        pInputPara->valid_brightness_range.high_enable = TH_DISABLE;
    }else{
        pInputPara->valid_brightness_range.high_enable = TH_ENABLE;
        pInputPara->valid_brightness_range.high_threshold = ui->lineEditMeanBrightnessMax->text().toInt();
    }
    if(ui->lineEditMeanBrightnessMin->text() == "---"){
        pInputPara->valid_brightness_range.low_enable = TH_DISABLE;
    }else{
        pInputPara->valid_brightness_range.low_enable = TH_ENABLE;
        pInputPara->valid_brightness_range.low_threshold = ui->lineEditMeanBrightnessMin->text().toInt();
    }
}

void MeanBrightnessWidget::on_pushButtonCalc_clicked()
{
    SetInputData();
    Fun_GetLearnDialog GetDialog = (Fun_GetLearnDialog)m_Learn_Lib.resolve("GetDialog");
    QDialog *dlg = GetDialog();
    CalcTimer->start(10);
    dlg->exec();
}

void MeanBrightnessWidget::CalcTimerSlot()
{

    Fun_SetResultString SetResultString = (Fun_SetResultString)m_Learn_Lib.resolve("SetResultString");
    QString info = tr("正在计算，请稍等");
    SetResultString(info);
    int ret = TaskStepLearnProc(m_step_index);
    if(ret == 0)
    {
        GetCalcDataShow();
        info = tr("计算成功!");
    }else
    {
        info = tr("计算失败!")+tr("错误码:")+QString::number(ret,16);
    }
    SetResultString(info);
    CalcTimer->stop();
}

void MeanBrightnessWidget::LoadLearnLib()
{
    m_Learn_Lib.setFileName("libLearningDialog.so");
    if(m_Learn_Lib.isLoaded())
    {
        qDebug()<<"load libLearningDialog.so isLoaded";
        return;
    }
    if(m_Learn_Lib.load())
    {
        printf("libLearningDialog.so OK\n");
    }
    else
    {
        qDebug()<<"load libLearningDialog.so fail"<<m_Learn_Lib.errorString();
    }
}
