#include "ContourPointsWidget.h"
#include "ui_ContourPointsWidget.h"
#include <QMessageBox>
#include "FWContourPointLabel.h"
#include <QDebug>
ContourPointsWidget::ContourPointsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContourPointsWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    LoadLearnLib();
    QList<QLineEdit *> lineEdit = this->findChildren<QLineEdit *>();
    foreach (QLineEdit * L, lineEdit) {
        L->installEventFilter(this);
    }
    m_label = new FWContourPointLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);
    CalcTimer = new QTimer;
    connect(CalcTimer, &QTimer::timeout, this, &ContourPointsWidget::CalcTimerSlot);

}

ContourPointsWidget::~ContourPointsWidget()
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
 * @brief ContourPointsWidget::Get_Image_Pos
 * @return
 * @author dgq
 * @note 获取图像显示区域的位置
 */
QPoint ContourPointsWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }

    return point;
}

/**
 * @brief ContourPointsWidget::Set_Parameter_To_Ram
 * @author dgq
 * @note 取样
 */
int ContourPointsWidget::Set_Parameter_To_Ram()
{
    SetInputData();
    return 1;
}



/**
 * @brief ContourPointsWidget::Init_Input_Ptr
 * @param ptr
 * @author dgq
 * @note 获取任务内存指针
 */
void ContourPointsWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    pInputPara = (OLPXNUM_INPUT_PARAM*)ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }
    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        pInputPara->valid_pixel_num_range.high_enable = 0;
        pInputPara->valid_pixel_num_range.low_enable = 0;
    }
    InitData();
}

/**
 * @brief ContourPointsWidget::InitData
 * @author dgq
 * @note 初始化界面显示
 */
void ContourPointsWidget::InitData()
{
    if(pInputPara->valid_pixel_num_range.high_enable == TH_ENABLE){
        ui->MaxValidData->setText(QString::number(pInputPara->valid_pixel_num_range.high_threshold));
    }

    if(pInputPara->valid_pixel_num_range.low_enable == TH_ENABLE){
        ui->MinValidData->setText(QString::number(pInputPara->valid_pixel_num_range.low_threshold));
    }
}

/**
 * @brief ContourPointsWidget::SetInputData
 * @author dgq
 * @note 将界面数据写入内存
 */
void ContourPointsWidget::SetInputData()
{
    if(ui->MaxValidData->text() == "---"){
        pInputPara->valid_pixel_num_range.high_enable = TH_DISABLE;
    }else{
        pInputPara->valid_pixel_num_range.high_enable = TH_ENABLE;
        pInputPara->valid_pixel_num_range.high_threshold = ui->MaxValidData->text().toInt();
    }

    if(ui->MinValidData->text() == "---"){
        pInputPara->valid_pixel_num_range.low_enable = TH_DISABLE;
    }else{
        pInputPara->valid_pixel_num_range.low_enable = TH_ENABLE;
        pInputPara->valid_pixel_num_range.low_threshold = ui->MinValidData->text().toInt();
    }
}

/**
 * @brief ContourPointsWidget::GetCalcDataShow
 * @author th
 * @note 获取计算结果数据更新界面显示
 */
void ContourPointsWidget::GetCalcDataShow()
{
    int num = 0;
    OLPXNUM_PRIVATE_PARAM* p_Private = (OLPXNUM_PRIVATE_PARAM*)Task_Step_Private_Para_Get(m_step_index);
    if(p_Private != NULL){
        ui->ModelContourPointsLabel->setText(QString::number(p_Private->model_olpxnum_rst.outline_pixel_num));
        if(ui->checkBox_AutoSet->isChecked())
        {
            num = p_Private->model_olpxnum_rst.outline_pixel_num * 1.2;
            ui->MaxValidData->setText(QString::number(num));

            num = p_Private->model_olpxnum_rst.outline_pixel_num * 0.8;
            ui->MinValidData->setText(QString::number(num));
        }
    }
}

/**
 * @brief ContourPointsWidget::on_btnCalculation_clicked
 * @author th
 * @note 计算按钮响应和函数
 */
void ContourPointsWidget::on_btnCalculation_clicked()
{
    SetInputData();
    Fun_GetLearnDialog GetDialog = (Fun_GetLearnDialog)m_Learn_Lib.resolve("GetDialog");
    QDialog *dlg = GetDialog();
    CalcTimer->start(10);
    dlg->exec();
}

/**
 * @brief ContourPointsWidget::CalcTimerSlot
 * @author dgq
 * @note 计算过程的定时器响应函数
 */
void ContourPointsWidget::CalcTimerSlot()
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
 * @brief ContourPointsWidget::LoadLearnLib
 * @author dgq
 * @note 加载取样、计算过程显示的进度条弹窗库
 */
void ContourPointsWidget::LoadLearnLib()
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

/**
 * @brief ContourPointsWidget::LoadKeyBoardLib
 * @author th
 * @note 加载输入软键盘界面库
 */
void ContourPointsWidget::LoadKeyBoardLib()
{
    m_keyBoard_Lib.setFileName("libFrmInputKeyBoard.so");
    if(m_keyBoard_Lib.isLoaded()){
        return;
    }
    if(m_keyBoard_Lib.load()){
        printf("libFrmInputKeyBoard.so OK\n");
    }else{
        qDebug()<<"load libFrmInputKeyBoard.so fail"<<m_keyBoard_Lib.errorString();
    }
}

/**
 * @brief ContourPointsWidget::NumKeyBoardDlg
 * @param watched 监听对象
 * @param event 监听事件
 * @param Min_value 输入最小值
 * @param Max_value 输入最大值
 * @author th
 * @note 行文本框输入函数
 */
void ContourPointsWidget::NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value)
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
                if((num != "---") && (num.toInt() > Max_value || num.toInt() < Min_value)){
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
 * @brief ContourPointsWidget::eventFilter
 * @param watched
 * @param event
 * @return
 * @author th
 * @note 事件过滤器，行文本框模拟点击事件
 */
bool ContourPointsWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->MaxValidData){
        if(event->type() == QEvent::MouseButtonPress){
            if(ui->MinValidData->text() != "---"){
                NumKeyBoardDlg(watched, event, ui->MinValidData->text().toInt(), 5000000);
            }else{
                NumKeyBoardDlg(watched, event, 0, 5000000);
            }
        }
    }
    if(watched == ui->MinValidData){
        if(event->type() == QEvent::MouseButtonPress){
            if(ui->MaxValidData->text() != "---"){
                NumKeyBoardDlg(watched, event, 0, ui->MaxValidData->text().toInt());
            }else{
                NumKeyBoardDlg(watched, event, 0, 5000000);
            }
        }
    }
}
