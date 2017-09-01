#include "OSDColorSetDlg.h"
#include "ui_OSDColorSetDlg.h"
#include <QMessageBox>
#include "Comm/OSDStyle.h"
#include <qdebug.h>

COLOR_SELECT g_color_selet;
OSDColorSetDlg::OSDColorSetDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OSDColorSetDlg)
{
    ui->setupUi(this);
    iFirst = 0;
    initCombColor(ui->comboBoxAreaSelectColor);
    initCombColor(ui->comboBoxEdgePointColor);
    initCombColor(ui->comboBoxImgBorderColor);
    initCombColor(ui->comboBoxParaCalColor);
    initCombColor(ui->comboBoxParaEditColor);
    initCombColor(ui->comboBoxParaSelectColor);
    InitControl();
    InstallEvent();
    m_widget = NULL;

}
void OSDColorSetDlg::InitControl()
{
    iFirst = 0;
    ui->comboBoxAreaSelectColor->setCurrentIndex(OSDStyle::pen_color.task_osd.task_osd_AreaSelect_color);
    ui->comboBoxEdgePointColor->setCurrentIndex(OSDStyle::pen_color.task_osd.task_osd_edgePoint_color);
    ui->comboBoxImgBorderColor->setCurrentIndex(OSDStyle::pen_color.task_osd.task_osd_ImageBorder_color);
    ui->comboBoxParaCalColor->setCurrentIndex(OSDStyle::pen_color.task_osd.task_osd_Calc_color);
    ui->comboBoxParaEditColor->setCurrentIndex(OSDStyle::pen_color.task_osd.task_osd_edit_color);
    ui->comboBoxParaSelectColor->setCurrentIndex(OSDStyle::pen_color.task_osd.task_osd_select_color);

    ui->txtAreaSelectWidth->setText(QString::number(OSDStyle::pen_color.task_osd.task_osd_AreaSelect_width));
    ui->txtEdgePointWidth->setText(QString::number(OSDStyle::pen_color.task_osd.task_osd_edgePoint_width));
    ui->txtImageBorderWidth->setText(QString::number(OSDStyle::pen_color.task_osd.task_osd_ImageBorder_width));
    ui->txtParaCalWidth->setText(QString::number(OSDStyle::pen_color.task_osd.task_osd_edit_width));
    ui->txtParaEditWidth->setText(QString::number(OSDStyle::pen_color.task_osd.task_osd_edit_width));
    ui->txtParaSelectWidth->setText(QString::number(OSDStyle::pen_color.task_osd.task_osd_select_width));


    OSDAreaSelectColor = OSDStyle::pen_color.task_osd.task_osd_AreaSelect_color;
    OSDEdgePointColor = OSDStyle::pen_color.task_osd.task_osd_edgePoint_color;
    OSDImageBorderColor = OSDStyle::pen_color.task_osd.task_osd_ImageBorder_color;
    OSDCalcColor = OSDStyle::pen_color.task_osd.task_osd_Calc_color;
    OSDParamEditColor = OSDStyle::pen_color.task_osd.task_osd_edit_color;
    OSDCheckedColor = OSDStyle::pen_color.task_osd.task_osd_select_color;

    OSDAreaSelectWidth = OSDStyle::pen_color.task_osd.task_osd_AreaSelect_width;
    OSDEdgePointWidth = OSDStyle::pen_color.task_osd.task_osd_edgePoint_width;
    OSDImageBorderWidth = OSDStyle::pen_color.task_osd.task_osd_ImageBorder_width;
    OSDCalcWidth = OSDStyle::pen_color.task_osd.task_osd_edit_width;
    OSDParamEditWidth = OSDStyle::pen_color.task_osd.task_osd_edit_width;
    OSDCheckedWidth = OSDStyle::pen_color.task_osd.task_osd_select_width;
    iFirst =1;
}
void OSDColorSetDlg::initCombColor(QComboBox *cmb)
{
    QString strName;
    QString strPath ="./image/color/";
    strName = "Red.png";
    QPixmap IconRed (strPath+strName);
    strName = "Orange.png";
    QPixmap IconOrange (strPath+strName);
    strName = "Yellow.png";
    QPixmap IconYellow (strPath+strName);
    strName = "Green.png";
    QPixmap IconGreen (strPath+strName);
    strName = "Blue.png";
    QPixmap IconBlue (strPath+strName);
    strName = "Cyan.png";
    QPixmap IconCyan (strPath+strName);
    strName = "Purple.png";
    QPixmap IconPurple (strPath+strName);
    strName = "Whilte.png";
    QPixmap IconWhilte (strPath+strName);
    strName = "Black.png";
    QPixmap IconBlack (strPath+strName);
    strName = "Gray.png";
    QPixmap IconGray (strPath+strName);

    cmb->addItem(QIcon(IconRed),tr("红"));
    cmb->addItem(QIcon(IconOrange),tr("橙"));
    cmb->addItem(QIcon(IconYellow),tr("黄"));
    cmb->addItem(QIcon(IconGreen),tr("绿"));
    cmb->addItem(QIcon(IconBlue),tr("蓝"));
    cmb->addItem(QIcon(IconCyan),tr("青"));
    cmb->addItem(QIcon(IconPurple),tr("紫"));
    cmb->addItem(QIcon(IconWhilte),tr("白"));
    cmb->addItem(QIcon(IconBlack),tr("黑"));
    cmb->addItem(QIcon(IconGray),tr("灰"));
}

OSDColorSetDlg::~OSDColorSetDlg()
{
    UninstallEvent();
    delete ui;
}
void OSDColorSetDlg::SetStep(int step)
{
    this->m_step = step;
}
void OSDColorSetDlg::on_btnOk_clicked()
{
    SetData();
    //OSDStyle::SetOSDConfig(m_step);
    QDialog::accept();
}
void OSDColorSetDlg::InitLibColor()
{
    TASK_STEP_HEADER *p_task_header = Task_Step_Head_Get(m_step);
    if(p_task_header ==NULL)
        return;
    OSDAreaSelectColor = OSDStyle::pen_color.task_osd.task_osd_AreaSelect_color;
    OSDEdgePointColor = OSDStyle::pen_color.task_osd.task_osd_edgePoint_color;
    OSDImageBorderColor = OSDStyle::pen_color.task_osd.task_osd_ImageBorder_color;
    OSDCalcColor = OSDStyle::pen_color.task_osd.task_osd_Calc_color;
    OSDParamEditColor = OSDStyle::pen_color.task_osd.task_osd_edit_color;
    OSDCheckedColor = OSDStyle::pen_color.task_osd.task_osd_select_color;

    OSDAreaSelectWidth = OSDStyle::pen_color.task_osd.task_osd_AreaSelect_width;
    OSDEdgePointWidth = OSDStyle::pen_color.task_osd.task_osd_edgePoint_width;
    OSDImageBorderWidth = OSDStyle::pen_color.task_osd.task_osd_ImageBorder_width;
    OSDCalcWidth = OSDStyle::pen_color.task_osd.task_osd_edit_width;
    OSDParamEditWidth = OSDStyle::pen_color.task_osd.task_osd_edit_width;
    OSDCheckedWidth = OSDStyle::pen_color.task_osd.task_osd_select_width;

    p_task_header->osd_config.area_select_osd.osd_color = OSDAreaSelectColor;
    p_task_header->osd_config.area_select_osd.osd_width = OSDAreaSelectWidth;
    p_task_header->osd_config.calc_osd.osd_color = OSDCalcColor;
    p_task_header->osd_config.calc_osd.osd_width = OSDCalcWidth;
    p_task_header->osd_config.checked_osd.osd_color = OSDCheckedColor;
    p_task_header->osd_config.checked_osd.osd_width = OSDCheckedWidth;
    p_task_header->osd_config.edge_point_osd.osd_color = OSDEdgePointColor;
    p_task_header->osd_config.edge_point_osd.osd_width = OSDEdgePointWidth;
    p_task_header->osd_config.image_border_osd.osd_color = OSDImageBorderColor;
    p_task_header->osd_config.image_border_osd.osd_width = OSDImageBorderWidth;
    p_task_header->osd_config.param_edit_osd.osd_color = OSDParamEditColor;
    p_task_header->osd_config.param_edit_osd.osd_width = OSDParamEditWidth;

}
void OSDColorSetDlg::SetData()
{
    GetColor(ui->comboBoxAreaSelectColor->currentIndex());
    OSDStyle::pen_color.task_osd.task_osd_AreaSelect_color = g_color_selet;
    GetColor(ui->comboBoxEdgePointColor->currentIndex());
    OSDStyle::pen_color.task_osd.task_osd_edgePoint_color = g_color_selet;
    GetColor(ui->comboBoxImgBorderColor->currentIndex());
    OSDStyle::pen_color.task_osd.task_osd_ImageBorder_color = g_color_selet;
    GetColor(ui->comboBoxParaCalColor->currentIndex());
    OSDStyle::pen_color.task_osd.task_osd_Calc_color = g_color_selet;
    GetColor(ui->comboBoxParaEditColor->currentIndex());
    OSDStyle::pen_color.task_osd.task_osd_edit_color = g_color_selet;
    GetColor(ui->comboBoxParaSelectColor->currentIndex());
    OSDStyle::pen_color.task_osd.task_osd_select_color = g_color_selet;

    OSDStyle::pen_color.task_osd.task_osd_AreaSelect_width = ui->txtAreaSelectWidth->text().toInt();
    OSDStyle::pen_color.task_osd.task_osd_edgePoint_width = ui->txtEdgePointWidth->text().toInt();
    OSDStyle::pen_color.task_osd.task_osd_ImageBorder_width = ui->txtImageBorderWidth->text().toInt();
    OSDStyle::pen_color.task_osd.task_osd_Calc__width = ui->txtParaCalWidth->text().toInt();
    OSDStyle::pen_color.task_osd.task_osd_edit_width = ui->txtParaEditWidth->text().toInt();
    OSDStyle::pen_color.task_osd.task_osd_select_width = ui->txtParaSelectWidth->text().toInt();
    TASK_STEP_HEADER *p_task_header = Task_Step_Head_Get(m_step);
    if(p_task_header ==NULL)
        return;

    p_task_header->osd_config.area_select_osd.osd_color = ui->comboBoxAreaSelectColor->currentIndex();
    p_task_header->osd_config.area_select_osd.osd_width = ui->txtAreaSelectWidth->text().toInt();
    p_task_header->osd_config.calc_osd.osd_color = ui->comboBoxParaCalColor->currentIndex();
    p_task_header->osd_config.calc_osd.osd_width = ui->txtParaCalWidth->text().toInt();
    p_task_header->osd_config.checked_osd.osd_color = ui->comboBoxParaSelectColor->currentIndex();
    p_task_header->osd_config.checked_osd.osd_width = ui->txtParaSelectWidth->text().toInt();
    p_task_header->osd_config.edge_point_osd.osd_color = ui->comboBoxEdgePointColor->currentIndex();
    p_task_header->osd_config.edge_point_osd.osd_width = ui->txtEdgePointWidth->text().toInt();
    p_task_header->osd_config.image_border_osd.osd_color = ui->comboBoxImgBorderColor->currentIndex();
    p_task_header->osd_config.image_border_osd.osd_width = ui->txtImageBorderWidth->text().toInt();
    p_task_header->osd_config.param_edit_osd.osd_color = ui->comboBoxParaEditColor->currentIndex();
    p_task_header->osd_config.param_edit_osd.osd_width = ui->txtParaEditWidth->text().toInt();


}
int OSDColorSetDlg::GetWidthValueFromLib(unsigned char value)
{
    int ret =1;
    if(value <1)
        ret= 1;
    else if(value >16)
        ret = 1;
    else
        ret = value;
    return ret;
}
void OSDColorSetDlg::GetDataFromLib()
{
    TASK_STEP_HEADER *p_task_header = Task_Step_Head_Get(m_step);
    if(p_task_header ==NULL)
        return;
    GetColor(p_task_header->osd_config.area_select_osd.osd_color);
    OSDStyle::pen_color.task_osd.task_osd_AreaSelect_color = g_color_selet;
    OSDStyle::pen_color.task_osd.task_osd_AreaSelect_width = GetWidthValueFromLib(p_task_header->osd_config.area_select_osd.osd_width);
    GetColor(p_task_header->osd_config.calc_osd.osd_color);
    OSDStyle::pen_color.task_osd.task_osd_Calc_color = g_color_selet;
    OSDStyle::pen_color.task_osd.task_osd_Calc__width = GetWidthValueFromLib(p_task_header->osd_config.calc_osd.osd_width);
    GetColor(p_task_header->osd_config.checked_osd.osd_color);
    OSDStyle::pen_color.task_osd.task_osd_select_color = g_color_selet;
    OSDStyle::pen_color.task_osd.task_osd_select_width = GetWidthValueFromLib(p_task_header->osd_config.checked_osd.osd_width);
    GetColor(p_task_header->osd_config.edge_point_osd.osd_color);
    OSDStyle::pen_color.task_osd.task_osd_edgePoint_color = g_color_selet;
    OSDStyle::pen_color.task_osd.task_osd_edgePoint_width = GetWidthValueFromLib(p_task_header->osd_config.edge_point_osd.osd_width);
    GetColor(p_task_header->osd_config.image_border_osd.osd_color);
    OSDStyle::pen_color.task_osd.task_osd_ImageBorder_color = g_color_selet;
    OSDStyle::pen_color.task_osd.task_osd_ImageBorder_width = GetWidthValueFromLib(p_task_header->osd_config.image_border_osd.osd_width);
    GetColor(p_task_header->osd_config.param_edit_osd.osd_color);
    OSDStyle::pen_color.task_osd.task_osd_edit_color = g_color_selet;
    OSDStyle::pen_color.task_osd.task_osd_AreaSelect_width = GetWidthValueFromLib(p_task_header->osd_config.param_edit_osd.osd_width);
    InitControl();

}
void OSDColorSetDlg::SetLabel(QLabel *lable)
{
    this->m_label = lable;
}
void OSDColorSetDlg::on_btnQuit_clicked()
{

    GetColor(OSDAreaSelectColor);
    OSDStyle::pen_color.task_osd.task_osd_AreaSelect_color  =  g_color_selet;
    GetColor(OSDEdgePointColor);
    OSDStyle::pen_color.task_osd.task_osd_edgePoint_color =  g_color_selet;
    GetColor(OSDImageBorderColor);
    OSDStyle::pen_color.task_osd.task_osd_ImageBorder_color = g_color_selet;
    GetColor(OSDCalcColor);
    OSDStyle::pen_color.task_osd.task_osd_Calc_color = g_color_selet;
    GetColor(OSDParamEditColor);
    OSDStyle::pen_color.task_osd.task_osd_edit_color = g_color_selet;
    GetColor(OSDCheckedColor);
    OSDStyle::pen_color.task_osd.task_osd_select_color = g_color_selet;

    OSDStyle::pen_color.task_osd.task_osd_AreaSelect_width = OSDAreaSelectWidth ;
    OSDStyle::pen_color.task_osd.task_osd_edgePoint_width = OSDEdgePointWidth;
    OSDStyle::pen_color.task_osd.task_osd_ImageBorder_width = OSDImageBorderWidth ;
    OSDStyle::pen_color.task_osd.task_osd_Calc__width = OSDCalcWidth;
    OSDStyle::pen_color.task_osd.task_osd_edit_width = OSDParamEditWidth ;
    OSDStyle::pen_color.task_osd.task_osd_select_width = OSDCheckedWidth;
    QDialog::reject();
}
void OSDColorSetDlg::GetColor(int index)
{
    switch (index) {
    case 0:
        g_color_selet = COLOR_RED_TYPE; //红
        break;
    case 1:
        g_color_selet= COLOR_ORANGE_TYPE; //橙
        break;
    case 2:
        g_color_selet = COLOR_YELLOW_TYPE; //黄
        break;
    case 3:
        g_color_selet = COLOR_GREEN_TYPE; //绿
        break;
    case 4:
        g_color_selet = COLOR_BLUE_TYPE; //蓝
        break;
    case 5:
        g_color_selet= COLOR_CYAN_TYPE; //靛
        break;
    case 6:
        g_color_selet = COLOR_PURPLE_TYPE; //紫
        break;
    case 7:
        g_color_selet = COLOR_WHILTE_TYPE; //白
        break;
    case 8:
        g_color_selet = COLOR_BLACK_TYPE; //黑
        break;
    case 9:
        g_color_selet = COLOR_GRAY_TYPE; //灰
        break;
    default:
        break;
    }
}
bool OSDColorSetDlg::eventFilter(QObject *watched, QEvent *event)
{
    if(!((QLineEdit*)watched)->isEnabled() || ((QLineEdit*)watched)->isReadOnly())
        return QWidget::eventFilter(watched, event);
    if (watched == ui->txtAreaSelectWidth)         //首先判断控件(这里指 lineEdit1)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            SelectWidth(ui->txtAreaSelectWidth);
        }
    }
    if(watched == ui->txtEdgePointWidth)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            SelectWidth(ui->txtEdgePointWidth);
        }
    }
    if(watched == ui->txtImageBorderWidth)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            SelectWidth(ui->txtImageBorderWidth);
        }
    }
    if(watched == ui->txtParaCalWidth)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            SelectWidth(ui->txtParaCalWidth);
        }
    }
    if(watched == ui->txtParaEditWidth)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            SelectWidth(ui->txtParaEditWidth);
        }
    }
    if(watched == ui->txtParaSelectWidth)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            SelectWidth(ui->txtParaSelectWidth);
        }
    }

    return QWidget::eventFilter(watched, event);
}
void OSDColorSetDlg::SelectWidth(QLineEdit *txtLineEdit)
{
    QDialog *dlg = m_keyBoardLib.GetNumKeyBoardDialog();

    if(dlg->exec()== QDialog::Accepted)
    {
        if(m_keyBoardLib.GetNum().toInt()>=1 && m_keyBoardLib.GetNum().toInt()<=16)
        {
            txtLineEdit->setText(m_keyBoardLib.GetNum());
            SetData();
            RefreshWidget();
        }
        else
        {
            QString strTemp;
            strTemp = tr("请输入1到16之间数");
            QMessageBox::information(NULL,tr("提示"),strTemp);
        }
    }
}
void OSDColorSetDlg::RefreshWidget()
{
    if(m_widget != NULL)
    {
        m_widget->hide();
        m_widget->show();
    }
}
void OSDColorSetDlg::InstallEvent()
{
    ui->txtAreaSelectWidth->installEventFilter(this);
    ui->txtEdgePointWidth->installEventFilter(this);
    ui->txtImageBorderWidth->installEventFilter(this);
    ui->txtParaCalWidth->installEventFilter(this);
    ui->txtParaEditWidth->installEventFilter(this);
    ui->txtParaSelectWidth->installEventFilter(this);
}
void OSDColorSetDlg::UninstallEvent()
{
    ui->txtAreaSelectWidth->removeEventFilter(this);
    ui->txtEdgePointWidth->removeEventFilter(this);
    ui->txtImageBorderWidth->removeEventFilter(this);
    ui->txtParaCalWidth->removeEventFilter(this);
    ui->txtParaEditWidth->removeEventFilter(this);
    ui->txtParaSelectWidth->removeEventFilter(this);
}

void OSDColorSetDlg::on_comboBoxImgBorderColor_currentIndexChanged(int index)
{
    if(iFirst ==1)
    {
        SetData();
       RefreshWidget();
    }
}

void OSDColorSetDlg::on_comboBoxParaEditColor_currentIndexChanged(int index)
{
    if(iFirst ==1)
    {
        SetData();
        RefreshWidget();
    }
}

void OSDColorSetDlg::on_comboBoxParaSelectColor_currentIndexChanged(int index)
{
    if(iFirst ==1)
    {
        SetData();
        RefreshWidget();
    }
}

void OSDColorSetDlg::on_comboBoxParaCalColor_currentIndexChanged(int index)
{
    if(iFirst ==1)
    {
        SetData();
        RefreshWidget();
    }
}

void OSDColorSetDlg::on_comboBoxEdgePointColor_currentIndexChanged(int index)
{
    if(iFirst ==1)
    {
        SetData();
        RefreshWidget();
    }
}

void OSDColorSetDlg::on_comboBoxAreaSelectColor_currentIndexChanged(int index)
{
    if(iFirst ==1)
    {
        SetData();
        RefreshWidget();
    }
}
void *OSDColorSetDlg::GetPenColorDrr()
{
    return OSDStyle::GetPenColor();
}
void OSDColorSetDlg::SetWidget(QWidget *widget)
{
    this->m_widget = widget;
}
