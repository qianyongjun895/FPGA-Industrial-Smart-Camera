#include "GrayMatchWidget.h"
#include "ui_GrayMatchWidget.h"
#include "FWGrayMatchLabel.h"
#include "xmlInitGlobal.h"
#include "LinkDataGlobal.h"
#include <qdebug.h>
#include <QDialog>
#include <QTextEdit>
//#include "QMessageBox"
GrayMatchWidget::GrayMatchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GrayMatchWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    LoadLearnLib();
    QList<QLineEdit *> lineEdit = this->findChildren<QLineEdit *>();
    foreach (QLineEdit * L, lineEdit) {
        L->installEventFilter(this);
    }
    m_label = new FWGrayMatchLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);
    m_i_load_first  = 0;
    CalcTimer = new QTimer;
    connect(CalcTimer, &QTimer::timeout, this, &GrayMatchWidget::CalcTimerSlot);
}

GrayMatchWidget::~GrayMatchWidget()
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

void GrayMatchWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    ((FWGrayMatchLabel*)m_label)->SetPen((QPen *)pen_color); //设置ROI颜色
    pInputPara = (GREAY_MATCH_INPUT_PARAM *)ptr; //输入参数
    m_step_index = i_step_index;
    for(i = 0; i < i_step_index-1; i++)
    {
        int ret =Task_Step_Type_ID_Get(i+1,&i_task_id);
        if(ret == 0)
        {
            QString name = InitPointCombobox(i+1,i_task_id);
            if(!name.isEmpty())
                ui->comboBoxDot->addItem(QString::number(i+1)+"."+name);
            name = InitLineCombobox(i+1,i_task_id);
            if(!name.isEmpty())
                ui->comboBoxLine->addItem(QString::number(i+1)+"."+name);
        }
    }
    if(pInputPara == NULL)
    {
      // QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }
    if(new_flag)
    {
        //初始化数据参数
        qDebug()<<"初始化参数";
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        pInputPara->In_Put_ROI.high_enable=540;
        pInputPara->In_Put_ROI.high_threshold = 100;
        pInputPara->In_Put_ROI.low_enable = 380;
        pInputPara->In_Put_ROI.low_threshold = 100;
        pInputPara->Differential_threshold = 128;
        pInputPara->Max_Score = 1000;
        pInputPara->Min_Score = 0;
        pInputPara->Mod_Image_Ptr = NULL;
        pInputPara->Score = 0;
    }
    InitData();
    //初始化数据
}

void GrayMatchWidget::InitData()
{
    //Get_Point_Or_Line_Flag
    //Get_Task_Name
    //measure_ref_point_result_get //
    /*
    int  Differential_threshold;	 匹配阈值
    THRESHOLD_INT In_Put_ROI; //匹配区域ROI
    int *Score;		 匹配分数
    void *Mod_Image_Ptr;
    int Max_Score;
    int Min_Score;*/
   /* if (pInputPara->Differential_threshold == 0)
    {
        //ui->radioBtnBlack->setChecked(true);
        pInputPara->Differential_threshold = 128;

    }
    else
    {
        ui->radioBtnWhite->setChecked(true);
    }

    int value;
    if(pInputPara->area_threshold.high_enable == 1){
        value = pInputPara->area_threshold.high_threshold;
        ui->txtAreaMax->setText(QString::number(value));
    }else{
        ui->txtAreaMax->setText("---");
    }
    if(pInputPara->area_threshold.low_enable == 1){
        value = pInputPara->area_threshold.low_threshold;
        ui->txtAreaMin->setText(QString::number(value));
    }else{
        ui->txtAreaMin->setText("---");
    }*/
}

int GrayMatchWidget::Set_Parameter_To_Ram()
{
    //SetDataToLib();
    return 1;
}

QPoint GrayMatchWidget::Get_Image_Pos()
{
    QPoint point(10,10);

    if(m_label != NULL)
    {
        point = m_label->pos();
    }
    return point;
}

void GrayMatchWidget::LoadLearnLib()
{
    m_Learn_Lib.setFileName("libLearningDialog.so");
    if(m_Learn_Lib.isLoaded())
    {
       // qDebug()<<"load libLearningDialog.so isLoaded";
        return;
    }
    if(m_Learn_Lib.load())
    {
        printf("libLearningDialog.so OK\n");
    }
    else
    {
       // qDebug()<<"load libLearningDialog.so fail"<<m_Learn_Lib.errorString();
    }
}

void GrayMatchWidget::LoadKeyBoardLib()
{
    m_keyBoard_Lib.setFileName("libFrmInputKeyBoard.so");
    if(m_keyBoard_Lib.isLoaded())
    {
        //qDebug()<<"load libFrmInputKeyBoard.so isLoaded";
        return;
    }
    if(m_keyBoard_Lib.load())
    {
        printf("libFrmInputKeyBoard.so OK\n");
    }
    else
    {
       // qDebug()<<"load libFrmInputKeyBoard.so fail"<<m_keyBoard_Lib.errorString();
    }
}

void GrayMatchWidget::CalcTimerSlot()
{
    Fun_SetResultString SetResultString = (Fun_SetResultString)m_Learn_Lib.resolve("SetResultString");
    QString info = tr("正在计算，请稍等");
    SetResultString(info);
    int ret = TaskStepLearnProc(m_step_index);
    if(ret == 0)
    {
        GetDataFromLib();
        info = tr("计算成功!");
    }else
    {
        info = tr("计算失败!")+tr("错误码:")+QString::number(ret,16);
    }
    SetResultString(info);
    CalcTimer->stop();
}

void GrayMatchWidget::GetDataFromLib()
{
   /* MONO_AREA_PRIVATE_PARAM *pPrivate = \
            (MONO_AREA_PRIVATE_PARAM *)Task_Step_Private_Para_Get(m_step_index);
    unsigned int i_area = pPrivate->model_area_rst.area;
    ui->txtAreaResult->setText(QString::number(i_area));
    if(ui->checkBoxAutoSet->isChecked())
    {
        int imax = i_area*1.2;
        int imin = i_area*0.8;
        ui->txtAreaMax->setText(QString::number(imax));
        ui->txtAreaMin->setText(QString::number(imin));
    }*/
}

void GrayMatchWidget::on_horizontalSlider11_valueChanged(int value)
{
    pInputPara->Differential_threshold = value;
    ui->label_2->setText(QString::number(value));
}

bool GrayMatchWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->txtMax){
        if (event->type()==QEvent::MouseButtonPress){
            GrayMatchMaxInputPro();
        }
    }
    if(watched == ui->txtMin){
        if (event->type()==QEvent::MouseButtonPress){
            GrayMatchMinInputPro();
        }
    }
    return QWidget::eventFilter(watched, event);
}

void GrayMatchWidget::GrayMatchMaxInputPro()
{
    Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = \
            (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
    QDialog *dlg = GetNumKeyBoardDlg();
    //Fun_SetRangeInput SetRangeInput = (Fun_SetRangeInput)m_keyBoard_Lib.resolve("SetRangeInput");
    //SetRangeInput(ui->txtMax->text(),ui->txtMin->text(),1);
    if(dlg->exec()== QDialog::Accepted)
    {
        Fun_GetRangeNum GetRangeNum = (Fun_GetRangeNum)m_keyBoard_Lib.resolve("GetRangeNum");
        ui->txtMax->setText(GetRangeNum());
    }
}

void GrayMatchWidget::GrayMatchMinInputPro()
{
    Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = \
            (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
    QDialog *dlg = GetNumKeyBoardDlg();
    //Fun_SetRangeInput SetRangeInput = (Fun_SetRangeInput)m_keyBoard_Lib.resolve("SetRangeInput");
    //SetRangeInput(ui->txtMax->text(),ui->txtMin->text(),0);
    if(dlg->exec()== QDialog::Accepted)
    {
        Fun_GetRangeNum GetRangeNum = (Fun_GetRangeNum)m_keyBoard_Lib.resolve("GetRangeNum");
        ui->txtMin->setText(GetRangeNum());
    }
}
