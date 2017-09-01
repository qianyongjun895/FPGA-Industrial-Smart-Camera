#include <QDebug>
#include "ColorAreaWidget.h"
#include "ui_ColorAreaWidget.h"
#include "FWColorAreaLabel.h"
#include "QMessageBox"

ColorAreaWidget::ColorAreaWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorAreaWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    LoadLearnLib();
    QList<QLineEdit *> lineEdit = this->findChildren<QLineEdit *>();
    foreach (QLineEdit * L, lineEdit) {
        L->installEventFilter(this);
        }
    m_label = new FWColorAreaLabel(this);
    m_label->setGeometry(10,10,640,480);
    m_label->setAutoFillBackground(true);
    QPalette p = m_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_label->setPalette(p);

    m_i_load_first  = 0;
    CalcTimer = new QTimer;
    connect(CalcTimer, &QTimer::timeout, this, &ColorAreaWidget::CalcTimerSlot);
}

ColorAreaWidget::~ColorAreaWidget()
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

QPoint ColorAreaWidget::Get_Image_Pos()
{
    QPoint point(-1024,-768);
    if(m_label != NULL)
    {
        point = m_label->pos();
    }
    return point;
}

int ColorAreaWidget::Set_Parameter_To_Ram()
{
    SetDataToLib();
    return 1;
}

void ColorAreaWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    ((FWColorAreaLabel*)m_label)->SetPenColor(pen_color);
    pInputPara = (COLOR_AREA_INPUT_PARAM *)ptr;
    m_step_index = i_step_index;
    if(pInputPara == NULL)
    {
        QMessageBox::about(this,tr(""),tr("初始化数据失败"));
        return;
    }
    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        pInputPara->area_threshold.high_enable = 0;
        pInputPara->area_threshold.low_enable = 0;
    }
    InitData();
}


bool ColorAreaWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->txtAreaMax){
        if (event->type()==QEvent::MouseButtonPress){
            BlobAreaMaxInputPro();
        }
    }
    if(watched == ui->txtAreaMin){
        if (event->type()==QEvent::MouseButtonPress){
            BlobAreaMinInputPro();
        }
    }
    return QWidget::eventFilter(watched, event);
}


void ColorAreaWidget::BlobAreaMinInputPro()
{
    Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
    QDialog *dlg = GetNumKeyBoardDlg();
    Fun_SetRangeInput SetRangeInput = (Fun_SetRangeInput)m_keyBoard_Lib.resolve("SetRangeInput");
    if(ui->txtAreaMin->text() != "---"){
        SetRangeInput(ui->txtAreaMax->text(),ui->txtAreaMin->text(),0);
    }else{
        SetRangeInput(ui->txtAreaMax->text(),ui->txtAreaResult->text(),0);
    }
    if(dlg->exec()== QDialog::Accepted)
    {
        Fun_GetRangeNum GetRangeNum = (Fun_GetRangeNum)m_keyBoard_Lib.resolve("GetRangeNum");
        ui->txtAreaMin->setText(GetRangeNum());
    }
}
void ColorAreaWidget::BlobAreaMaxInputPro()
{
    Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
    QDialog *dlg = GetNumKeyBoardDlg();
    Fun_SetRangeInput SetRangeInput = (Fun_SetRangeInput)m_keyBoard_Lib.resolve("SetRangeInput");
    if(ui->txtAreaMax->text() != "---"){
        SetRangeInput(ui->txtAreaMax->text(),ui->txtAreaMin->text(),1);
    }else{
        SetRangeInput(ui->txtAreaResult->text(),ui->txtAreaMin->text(),1);
    }
    if(dlg->exec()== QDialog::Accepted)
    {
        Fun_GetRangeNum GetRangeNum = (Fun_GetRangeNum)m_keyBoard_Lib.resolve("GetRangeNum");
        ui->txtAreaMax->setText(GetRangeNum());
    }
}

void ColorAreaWidget::InitData()
{
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
    }

}

void ColorAreaWidget::LoadKeyBoardLib()
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

void ColorAreaWidget::on_btnCalculate_clicked()
{
    SetDataToLib();
    Fun_GetLearnDialog GetDialog = (Fun_GetLearnDialog)m_Learn_Lib.resolve("GetDialog");
    QDialog *dlg = GetDialog();
    CalcTimer->start(10);
    dlg->exec();
}

void ColorAreaWidget::CalcTimerSlot()
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

void ColorAreaWidget::LoadLearnLib()
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

void ColorAreaWidget::GetDataFromLib()
{
    COLOR_AREA_PRIVATE_PARAM *pPrivate = (COLOR_AREA_PRIVATE_PARAM *)Task_Step_Private_Para_Get(m_step_index);
    unsigned int i_area = pPrivate->model_area_rst.area;
    ui->txtAreaResult->setText(QString::number(i_area));
    if(ui->checkBoxAutoSet->isChecked())
    {
        int imax = i_area*1.2;
        int imin = i_area*0.8;
        ui->txtAreaMax->setText(QString::number(imax));
        ui->txtAreaMin->setText(QString::number(imin));
    }
}

void ColorAreaWidget::SetDataToLib()
{
    int value = 0;
    //上门限使能(1:使能； 0：不使能)
    if(ui->txtAreaMax->text() == "---"){
        pInputPara->area_threshold.high_enable = 0;
    }else{
        pInputPara->area_threshold.high_enable = 1;
        value = ui->txtAreaMax->text().toInt();
        pInputPara->area_threshold.high_threshold = value;
    }

    //下门限使能(1:使能； 0：不使能)
    if(ui->txtAreaMin->text() == "---"){
        pInputPara->area_threshold.low_enable = 0;
    }else{
        pInputPara->area_threshold.low_enable = 1;
        value = ui->txtAreaMin->text().toInt();
        pInputPara->area_threshold.low_threshold = value;
    }
}
