#include "BlobCountWidget.h"
#include "ui_BlobCountWidget.h"
#include <QDebug>
#include <QMessageBox>
#include "TaskManageGlobal.h"
#include "FWBlobsCountLabel.h"
BlobCountWidget::BlobCountWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlobCountWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    LoadLearnLib();
    QList<QLineEdit *> lineEdit = this->findChildren<QLineEdit *>();
    foreach (QLineEdit * L, lineEdit) {
        L->installEventFilter(this);
    }
    m_label = new FWBlobsCountLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);
    CalcTimer = new QTimer;
    connect(CalcTimer, &QTimer::timeout, this, &BlobCountWidget::CalcTimerSlot);

}

BlobCountWidget::~BlobCountWidget()
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

/**
 * @brief BlobCountWidget::Get_Image_Pos
 * @return
 * @author dgq
 * @note 获取图像显示区域的位置
 */
QPoint BlobCountWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }

    return point;
}

/**
 * @brief BlobCountWidget::InitData
 * @author dgq
 * @note 初始化界面显示
 */
void BlobCountWidget::InitData()
{
    if(pInputPara->single_area.high_enable == TH_ENABLE){
        ui->lineEditSingleBlobAreaMax->setText(QString::number(pInputPara->single_area.high_threshold));
    }
    if(pInputPara->single_area.low_enable == TH_ENABLE){
        ui->lineEditSingleBlobAreaMin->setText(QString::number(pInputPara->single_area.low_threshold));
    }
    if(pInputPara->total_num.high_enable == TH_ENABLE)
    {
        ui->lineEditBlobCountMax->setText(QString::number(pInputPara->total_num.high_threshold));
    }
    if(pInputPara->total_num.low_enable == TH_ENABLE){
        ui->lineEditBlobCountMin->setText(QString::number(pInputPara->total_num.low_threshold));
    }
}

/**
 * @brief BlobCountWidget::SetInputData
 * @author dgq
 * @note 将界面数据写入内存
 */
void BlobCountWidget::SetInputData()
{
    if(ui->lineEditSingleBlobAreaMax->text() == "---"){
        pInputPara->single_area.high_enable = TH_DISABLE;
    }else{
        pInputPara->single_area.high_enable = TH_ENABLE;
        pInputPara->single_area.high_threshold = ui->lineEditSingleBlobAreaMax->text().toInt();
    }

    if(ui->lineEditSingleBlobAreaMin->text() == "---"){
        pInputPara->single_area.low_enable = TH_DISABLE;
    }else{
        pInputPara->single_area.low_enable = TH_ENABLE;
        pInputPara->single_area.low_threshold = ui->lineEditSingleBlobAreaMin->text().toInt();
    }

    if(ui->lineEditBlobCountMax->text() == "---"){
        pInputPara->total_num.high_enable = TH_DISABLE;
    }else{
        pInputPara->total_num.high_enable = TH_ENABLE;
        pInputPara->total_num.high_threshold = ui->lineEditBlobCountMax->text().toInt();
    }

    if(ui->lineEditBlobCountMin->text() == "---"){
        pInputPara->total_num.low_enable = TH_DISABLE;
    }else{
        pInputPara->total_num.low_enable = TH_ENABLE;
        pInputPara->total_num.low_threshold = ui->lineEditBlobCountMin->text().toInt();
    }
}

/**
 * @brief BlobCountWidget::Set_Parameter_To_Ram
 * @author dgq
 * @note 将界面的配置参数写入内存
 */
int BlobCountWidget::Set_Parameter_To_Ram()
{
    SetInputData();
    return 1;
}

/**
 * @brief BlobCountWidget::Init_Input_Ptr
 * @param ptr input结构体指针
 * @param i_step_index 当前步骤号
 * @param new_flag 新加步骤标志：1新加，0编辑
 * @author dgq
 * @note 初始化设置Input结构体指针
 */
void BlobCountWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    pInputPara = (BLOBCOUNT_INPUT_PARAM*)ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }
    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        pInputPara->single_area.high_enable = 0;
        pInputPara->single_area.low_enable = 0;
        pInputPara->total_num.high_enable = 0;
        pInputPara->total_num.low_enable = 0;
    }
    InitData();
}

/**
 * @brief BlobCountWidget::LoadKeyBoardLib
 * @author dgq
 * @note 加载输入软键盘库
 */
void BlobCountWidget::LoadKeyBoardLib()
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

/**
 * @brief BlobCountWidget::NumKeyBoardDlg
 * @param watched 监听对象
 * @param event 监听事件
 * @param Min_value 输入的最小值
 * @param Max_value 输入的最大值
 * @author th
 * @note 行文本框输入响应函数
 */
void BlobCountWidget::NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value)
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

/**
 * @brief BlobCountWidget::eventFilter
 * @param watched
 * @param event
 * @return
 * @author th
 * @note 事件过滤器，行文本框模拟点击事件
 */
bool BlobCountWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEditSingleBlobAreaMax)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(ui->lineEditSingleBlobAreaMin->text() != "---")
            {
                NumKeyBoardDlg(watched, event, ui->lineEditSingleBlobAreaMin->text().toInt(), 5000000);
            }
            else
            {
                NumKeyBoardDlg(watched, event, 0, 5000000);
            }
        }
    }
    if(watched == ui->lineEditSingleBlobAreaMin)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(ui->lineEditSingleBlobAreaMax->text() != "---")
            {
                NumKeyBoardDlg(watched, event, 0, ui->lineEditSingleBlobAreaMax->text().toInt());
            }
            else
            {
                NumKeyBoardDlg(watched, event, 0, 5000000);
            }
        }
    }
    if(watched == ui->lineEditBlobCountMax)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(ui->lineEditBlobCountMin->text() != "---")
            {
                NumKeyBoardDlg(watched, event, ui->lineEditBlobCountMin->text().toInt(), 5000000);
            }
            else
            {
                NumKeyBoardDlg(watched, event, 0, 5000000);
            }
        }
    }
    if(watched == ui->lineEditBlobCountMin)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(ui->lineEditBlobCountMax->text() != "---")
            {
                NumKeyBoardDlg(watched, event, 0, ui->lineEditBlobCountMax->text().toInt());
            }
            else
            {
                NumKeyBoardDlg(watched, event, 0, 5000000);
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

/**
 * @brief BlobCountWidget::GetCalcDataShow
 * @author th
 * @note 获取计算结果更新界面显示
 */
void BlobCountWidget::GetCalcDataShow()
{
    int num = 0;
    BLOBCOUNT_PRIVATE_PARAM *p_Private = (BLOBCOUNT_PRIVATE_PARAM*)Task_Step_Private_Para_Get(m_step_index);
    if(p_Private != NULL){
        ui->labelCalcValue->setText(QString::number(p_Private->model_blob_num));
        if(ui->checkBoxAuto->isChecked()){
            num = p_Private->model_blob_num * 1.2;
            ui->lineEditBlobCountMax->setText(QString::number(num));

            num = p_Private->model_blob_num * 0.8;
            ui->lineEditBlobCountMin->setText(QString::number(num));
        }
    }
}

/**
 * @brief BlobCountWidget::on_pushButtonCalc_clicked
 * @author dgq
 * @note 计算按钮响应函数
 */
void BlobCountWidget::on_pushButtonCalc_clicked()
{
    SetInputData();
    Fun_GetLearnDialog GetDialog = (Fun_GetLearnDialog)m_Learn_Lib.resolve("GetDialog");
    QDialog *dlg = GetDialog();
    CalcTimer->start(10);
    dlg->exec();
}

/**
 * @brief BlobCountWidget::CalcTimerSlot
 * @author dgq
 * @note 计算过程的定时器响应函数
 */
void BlobCountWidget::CalcTimerSlot()
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

/**
 * @brief BlobCountWidget::LoadLearnLib
 * @author dgq
 * @note 加载取样进度条弹窗库
 */
void BlobCountWidget::LoadLearnLib()
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
