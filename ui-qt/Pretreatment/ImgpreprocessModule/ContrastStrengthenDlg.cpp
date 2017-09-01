#include "ContrastStrengthenDlg.h"
#include "ui_ContrastStrengthenDlg.h"
#include <QMessageBox>
#include "../../Global/UtilitiesFun.h"
#include "AcceCommon.h"

ContrastStrengthenDlg::ContrastStrengthenDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContrastStrengthenDlg)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->labelPicList->SetImagSmothEnable(1);
    btn = -1;
    //ui->labelPicList->setAttribute(Qt::WA_TranslucentBackground, true);
    connect(ui->labelPicList,&ContrastStrengthenAdjustLabel::sendDataSignal,this,&ContrastStrengthenDlg::sendBlancedDataSlot);
    connect(ui->labelPicList,&ContrastStrengthenAdjustLabel::PointChangeSignal,this,&ContrastStrengthenDlg::PointChangeSlot);
    connect(&ClickTimer,&QTimer::timeout,this ,&ContrastStrengthenDlg::ClickTimerSlot);
}

ContrastStrengthenDlg::~ContrastStrengthenDlg()
{
    delete ui;
}
void ContrastStrengthenDlg::InitData()
{
    m_Points.clear();
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
    m_smooth_mode = ptr->image_acce_param.pre_model_cfg.balance_model_cfg.balance_point_info.balance_point_num;
    m_cfg = ptr->image_acce_param.pre_model_cfg.balance_model_cfg;
    /*int i_hisFlag = ptr->image_acce_param.pre_model_cfg.balance_model_cfg.hist_stat_sel;
    if(i_hisFlag == 0)
    {
        ui->radioButton_Old->setChecked(true);
    }
    else
    {
        ui->radioButton_New->setChecked(true);
    }*/
    int i = 0;
    QPoint m_point;
    if(m_smooth_mode == 2 ||m_smooth_mode == 4 ||m_smooth_mode == 8 ||m_smooth_mode == 16)
    {
        for(i = 0; i < m_smooth_mode; i++)
        {
            m_point.setX(ptr->image_acce_param.pre_model_cfg.balance_model_cfg.balance_point_info.balance_point[i].x_i);
            m_point.setY(ptr->image_acce_param.pre_model_cfg.balance_model_cfg.balance_point_info.balance_point[i].y_i);
            m_Points.append(m_point);
        }

        if(m_smooth_mode == 2){
            ui->radioButton_two->setChecked(true);
        }else if(m_smooth_mode == 4){
            ui->radioButton_four->setChecked(true);
        }else if(m_smooth_mode == 8){
            ui->radioButton_eight->setChecked(true);
        }else{
            ui->radioButton_sixteen->setChecked(true);
        }
    }else
    {
        QVector<QPoint> points;
        points.append(QPoint(85,132));
        points.append(QPoint(170,200));

        ui->labelPicList->SetPointsChange(points,2);
        m_smooth_mode = 2;
        ui->radioButton_two->setChecked(true);

        m_Points.clear();
        m_Points = points;
    }
    ui->labelPicList->SetPointsChange(m_Points,m_smooth_mode);
    ui->labelPicList->SetPointFocus(0);

    ptr->image_acce_param.pre_model_cfg.balance_model_cfg.manual_set_en = 0;
    ptr->image_acce_param.pre_model_cfg.balance_model_cfg.model_enable =1;
    ptr->image_acce_param.pre_model_cfg.pre_wr_ddr_en = 1;
    ptr->image_acce_param.pre_model_cfg.pre_src_out_sel = ACCE_BALANCE_MODEL_ID;
    ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_PRE_MODEL_ID;
    AcceleratorModuleConfig(ACCE_PRE_MODEL_ID,m_step);
    AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
    UtilitiesFun::Instance()->ListVGA(ui->labelPicList->x(),ui->labelPicList->y(),ACCE_BALANCE_MODEL_ID);
    //sendBlancedDataSlot();
    GetGrayVt();
    ui->radioButtonBasic->setChecked(true);
    ui->radioButtonAdvanced->setChecked(false);
    //ui->label_DrawLines->SetBalance(1);
}
void ContrastStrengthenDlg::IniAdvancedData()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
    int num = 0;
    QVector<QPoint> Points;

    char buf[256];
    memset(buf,0,sizeof(buf));
    //GetBalanceLutResultData((unsigned char*)buf,500);
    memcpy(buf,ptr->image_acce_param.pre_model_cfg.balance_model_cfg.balance_lut,sizeof(buf));
    ptr->image_acce_param.pre_model_cfg.balance_model_cfg.manual_set_en = 1;
    AcceleratorModuleConfig(ACCE_BALANCE_MODEL_ID,m_step);
    int y = 0;
    for (int i = 0;i<256;i++)
    {
        y = (int)buf[i];
        QPoint point(i,y);
        Points.append(point);
    }
    num = 256;
    ui->labelPicList->SetPointsChange(Points,num);
    this->m_smooth_mode = 256;
    QString strPoint;
    strPoint ="(";
    strPoint += QString::number(Points[0].x());
    strPoint +=",";
    strPoint += QString::number(Points[0].y());
    strPoint +=")";
    m_x = Points[0].x();
    ui->txtPointY->setText(strPoint);
    ui->txtPointSelect->setText(tr("点")+QString::number(1));
    ui->horizontalSliderPointSelect->setValue(1);
    ui->horizontalSliderPointY->setValue(Points[0].y());
}
void ContrastStrengthenDlg::on_radioButton_two_clicked(bool checked)
{
    if(m_smooth_mode == 2)
    {
        return;
    }else
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("切换数据类型会清空未保存的数据，确定切换?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(rb == QMessageBox::No)
        {
            if(m_smooth_mode == 16)
                ui->radioButton_sixteen->setChecked(true);
            if(m_smooth_mode == 4)
                ui->radioButton_four->setChecked(true);
            if(m_smooth_mode == 8)
                ui->radioButton_eight->setChecked(true);
            return;
        }
        QVector<QPoint> points;
        points.append(QPoint(85,132));
        points.append(QPoint(170,200));
        if(checked){
            ui->labelPicList->SetPointsChange(points,2);
            m_smooth_mode = 2;
        }
        m_Points.clear();
        m_Points = points;
        sendBlancedDataSlot();
    }
}

void ContrastStrengthenDlg::on_radioButton_four_clicked(bool checked)
{
    if(m_smooth_mode == 4)
    {
        return;
    }else
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("切换数据类型会清空未保存的数据，确定切换?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(rb == QMessageBox::No)
        {
            if(m_smooth_mode == 2)
                ui->radioButton_two->setChecked(true);
            if(m_smooth_mode == 16)
                ui->radioButton_sixteen->setChecked(true);
            if(m_smooth_mode == 8)
                ui->radioButton_eight->setChecked(true);
            return;
        }
        QVector<QPoint> points;
        points.append(QPoint(51,97));
        points.append(QPoint(102,147));
        points.append(QPoint(153,188));
        points.append(QPoint(204,223));
        if(checked){
            ui->labelPicList->SetPointsChange(points,4);
            m_smooth_mode = 4;
        }
        m_Points.clear();
        m_Points = points;
        sendBlancedDataSlot();
    }
}

void ContrastStrengthenDlg::on_radioButton_eight_clicked(bool checked)
{
    if(m_smooth_mode == 8)
    {
        return;
    }else
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("切换数据类型会清空未保存的数据，确定切换?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(rb == QMessageBox::No)
        {
            if(m_smooth_mode == 2)
                ui->radioButton_two->setChecked(true);
            if(m_smooth_mode == 4)
                ui->radioButton_four->setChecked(true);
            if(m_smooth_mode == 16)
                ui->radioButton_sixteen->setChecked(true);
            return;
        }
        QVector<QPoint> points;
        points.append(QPoint(28,68));
        points.append(QPoint(56,103));
        points.append(QPoint(84,131));
        points.append(QPoint(112,156));
        points.append(QPoint(140,178));
        points.append(QPoint(168,199));
        points.append(QPoint(196,218));
        points.append(QPoint(224,236));
        if(checked){
            ui->labelPicList->SetPointsChange(points,8);
            m_smooth_mode = 8;
        }
        m_Points.clear();
        m_Points = points;
        sendBlancedDataSlot();
    }
}

void ContrastStrengthenDlg::on_radioButton_sixteen_clicked(bool checked)
{
    if(m_smooth_mode == 16)
    {
        if(m_smooth_mode == 2)
            ui->radioButton_two->setChecked(true);
        if(m_smooth_mode == 4)
            ui->radioButton_four->setChecked(true);
        if(m_smooth_mode == 8)
            ui->radioButton_eight->setChecked(true);
        return;
    }else
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("切换数据类型会清空未保存的数据，确定切换?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(rb == QMessageBox::No)
        {
            return;
        }
        QVector<QPoint> points;
        points.append(QPoint(15,45));
        points.append(QPoint(30,71));
        points.append(QPoint(45,90));
        points.append(QPoint(60,107));
        points.append(QPoint(75,122));
        points.append(QPoint(90,137));
        points.append(QPoint(105,150));
        points.append(QPoint(120,162));
        points.append(QPoint(135,174));
        points.append(QPoint(150,185));
        points.append(QPoint(165,196));
        points.append(QPoint(180,207));
        points.append(QPoint(195,217));
        points.append(QPoint(210,227));
        points.append(QPoint(225,237));
        points.append(QPoint(240,246));
        if(checked){
            ui->labelPicList->SetPointsChange(points,16);
            m_smooth_mode = 16;
        }
        m_Points.clear();
        m_Points = points;
        sendBlancedDataSlot();
    }
}
void ContrastStrengthenDlg::SetDataToLib()
{
    int i;
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
    m_Points.clear();
    m_Points = ui->labelPicList->GetPoints();

    if(m_smooth_mode <=16)
    {
        ptr->image_acce_param.pre_model_cfg.balance_model_cfg.balance_point_info.balance_point_num = m_smooth_mode;
        POINT_I m_point;
        for(i = 0; i< m_smooth_mode; i++)
        {
            m_point.x_i = m_Points[i].x();
            m_point.y_i = m_Points[i].y();
            ptr->image_acce_param.pre_model_cfg.balance_model_cfg.balance_point_info.balance_point[i] = m_point;
        }
    }else
    {
        for(i = 0; i< m_smooth_mode; i++)
        {
            ptr->image_acce_param.pre_model_cfg.balance_model_cfg.balance_lut[i] = m_Points[i].y();;
        }
    }

    AcceleratorModuleConfig(ACCE_BALANCE_MODEL_ID,m_step);
}
void ContrastStrengthenDlg::GetGrayVt()
{
    /*int i;
    unsigned int data[256];
    QVector<int> Value;
    QThread::msleep(20);
    GetBalanceHistResultData(data,100);
    unsigned int iMax = data[0];
    unsigned int iMin = data[0];
    for(i = 0;i<256;i++)
    {
        if(iMax < data[i])
        {
            iMax = data[i];
        }
        if(iMin > data[i])
        {
            iMin = data[i];
        }
        Value.append(data[i]);
    }
    ui->txtPixMaxNum->setText(QString::number(iMax));
    ui->label_DrawLines->BalanceValueChangeSlot(iMin,iMax,Value);*/
}
void ContrastStrengthenDlg::sendBlancedDataSlot()
{
    SetDataToLib();
    GetGrayVt();
}
void ContrastStrengthenDlg::DealPicGray()
{
   /* QVector<int> m_vt;

    for(int i = 0; i<256;i++)
        m_vt.append(0);

    memset(m_gray_num,0,sizeof(m_gray_num));
    void *picAddr = m_CGetImageThread->GetPicAddr();
    char *imageAddr = (char*)((unsigned int)picAddr+m_CGetImageThread->m_image_adr.gray_hist_proc_rst_addr-m_CGetImageThread->m_image_adr.cpt_color_pic_addr);
    QRect rect = ui->labelPicList->GetRect();
    int xStart = rect.topLeft().x();
    int yStart = rect.topLeft().y();
    int xEnd = rect.bottomRight().x();
    int yEnd = rect.bottomRight().y();

    int iMin = 255;
    int iMax = 0;
    char picvalue;
    for(int i = yStart;i<yEnd;i++)
    {
        for(int j = xStart;j<xEnd;j++)
        {
            picvalue = imageAddr[i*640+j];

            for(int k = 0; k<256;k++)
            {
                if(picvalue == k)
                    m_vt[k] = m_vt[k] +1;
            }
        }
    }

    iMin=0;
    iMax = 0;

    for(int i = 0;i<256;i++)
    {
        if(iMin > m_vt[i])
            iMin = m_vt[i];
        if(iMax < m_vt[i])
            iMax = m_vt[i];
    }

    ui->txtPixMaxNum->setText(QString::number(iMax));
    ui->label_DrawLines->BalanceValueChangeSlot(iMin,iMax,m_vt);*/
}
void ContrastStrengthenDlg::PointChangeSlot(int num, QPoint point)
{
    if(num ==-10)
    {
        //处理区域里的图形灰度数据
        DealPicGray();
        if(ui->radioButtonAdvanced->isChecked())
        {
            int value =ui->horizontalSliderPointSelect->value();
            ui->labelPicList->SetCurrentIndexAd(value);
        }

    }else
    {
        if(ui->radioButtonBasic->isChecked())
        {
            ui->txtPointSerial->setText(tr("点")+QString::number(num+1));
            ui->txtPoint1Coor->setText("("+QString::number((point.x()-64)/2)+","+QString::number(400-point.y())+")"); //400-->255
        }else
        {
            ui->txtPointSelect->setText(tr("点")+QString::number(num+1));
            QPoint point = ui->labelPicList->GetCurrentPoint();
            ui->horizontalSliderPointY->setValue(point.y());
            m_x = point.x();
            QString strPoint;
            strPoint ="(";
            strPoint += QString::number(m_x);
            strPoint +=",";
            strPoint += QString::number(point.y());
            strPoint +=")";
            ui->txtPointY->setText(strPoint);
        }
    }

}

void ContrastStrengthenDlg::on_btnMoveUp_pressed()
{
    //    ui->labelPicList->MoveUp();
    btn = 0;
    ClickTimer.start(10);
}

void ContrastStrengthenDlg::on_btnMoveDown_pressed()
{
    //    ui->labelPicList->MoveDown();
    btn = 1;
    ClickTimer.start(10);
}

void ContrastStrengthenDlg::on_btnMoveLeft_pressed()
{
    //    ui->labelPicList->MoveLeft();
    btn = 2;
    ClickTimer.start(10);
}

void ContrastStrengthenDlg::on_btnMoveRight_pressed()
{
    //ui->labelPicList->MoveRight();
    btn = 3;
    ClickTimer.start(10);
}

void ContrastStrengthenDlg::on_btnMoveUp_released()
{
    btn = -1;
    ClickTimer.stop();
}

void ContrastStrengthenDlg::on_btnMoveDown_released()
{

    btn = -1;
    ClickTimer.stop();
}

void ContrastStrengthenDlg::on_btnMoveLeft_released()
{

    btn = -1;
    ClickTimer.stop();
}

void ContrastStrengthenDlg::on_btnMoveRight_released()
{

    btn = -1;
    ClickTimer.stop();
}

void ContrastStrengthenDlg::ClickTimerSlot()
{
    if(btn ==4 || btn ==5 || btn ==6 || btn ==7)
    {
        if(iTimes < 15)
        {
            iTimes++;
            return;
        }
    }
    if(btn == 0)
        ui->labelPicList->MoveUp();
    else if(btn == 1)
        ui->labelPicList->MoveDown();
    else if(btn == 2)
        ui->labelPicList->MoveLeft();
    else if(btn ==3)
        ui->labelPicList->MoveRight();
    else if(btn ==4)
        SubPointselect();
    else if(btn == 5)
        AddPointSelect();
    else if(btn == 6)
        SubPointY();
    else if(btn == 7)
        AddPointY();
}

void ContrastStrengthenDlg::on_radioButtonBasic_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    InitData();
}

void ContrastStrengthenDlg::on_radioButtonAdvanced_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    IniAdvancedData();
}
void ContrastStrengthenDlg::AddPointSelect()
{
    int iNum = ui->horizontalSliderPointSelect->value();
    if(iNum < 256)
    {
        iNum++;
        ui->horizontalSliderPointSelect->setValue(iNum);
        ui->txtPointSelect->setText(tr("点")+QString::number(iNum));
    }
}
void ContrastStrengthenDlg::SubPointselect()
{
    int iNum = ui->horizontalSliderPointSelect->value();
    if(iNum > 1)
    {
        iNum--;
        ui->horizontalSliderPointSelect->setValue(iNum);
        ui->txtPointSelect->setText(tr("点")+QString::number(iNum));
    }
}
void ContrastStrengthenDlg::AddPointY()
{
    int iY = ui->horizontalSliderPointY->value();
    if(iY < 255)
    {
        iY++;
        ui->horizontalSliderPointY->setValue(iY);
        QString strPoint;
        strPoint ="(";
        strPoint += QString::number(m_x);
        strPoint +=",";
        strPoint += QString::number(iY);
        strPoint +=")";
        ui->txtPointY->setText(strPoint);
    }
}
void ContrastStrengthenDlg::SubPointY()
{

    int iY = ui->horizontalSliderPointY->value();
    if(iY > 0)
    {
        iY--;
        ui->horizontalSliderPointY->setValue(iY);
        QString strPoint;
        strPoint ="(";
        strPoint += QString::number(m_x);
        strPoint +=",";
        strPoint += QString::number(iY);
        strPoint +=")";
        ui->txtPointY->setText(strPoint);
    }
}
void ContrastStrengthenDlg::on_btnSupPointSelect_pressed()
{
    btn = 4;
    iTimes =1;
    SubPointselect();
    ClickTimer.start(10);
}

void ContrastStrengthenDlg::on_btnSupPointSelect_released()
{
    btn = -1;
    iTimes =1;
    ClickTimer.stop();
    int value = ui->horizontalSliderPointSelect->value();
    ui->labelPicList->SetCurrentIndexAd(value);
    QPoint point = ui->labelPicList->GetCurrentPoint();
    ui->horizontalSliderPointY->setValue(point.y());
    m_x = point.x();
    QString strPoint;
    strPoint ="(";
    strPoint += QString::number(m_x);
    strPoint +=",";
    strPoint += QString::number(point.y());
    strPoint +=")";
    ui->txtPointY->setText(strPoint);


}

void ContrastStrengthenDlg::on_btnAddPointSelect_pressed()
{
    btn = 5;
    iTimes =1;
    AddPointSelect();
    ClickTimer.start(10);
}

void ContrastStrengthenDlg::on_btnAddPointSelect_released()
{
    btn = -1;
    ClickTimer.stop();
    int value = ui->horizontalSliderPointSelect->value();
    ui->labelPicList->SetCurrentIndexAd(value);
    QPoint point = ui->labelPicList->GetCurrentPoint();
    ui->horizontalSliderPointY->setValue(point.y());
    m_x = point.x();
    QString strPoint;
    strPoint ="(";
    strPoint += QString::number(m_x);
    strPoint +=",";
    strPoint += QString::number(point.y());
    strPoint +=")";
    ui->txtPointY->setText(strPoint);

}

void ContrastStrengthenDlg::on_btnSubPointY_pressed()
{
    btn = 6;
    iTimes =1;
    SubPointY();
    ClickTimer.start(10);
}

void ContrastStrengthenDlg::on_btnSubPointY_released()
{
    btn = -1;
    ClickTimer.stop();
    int value = ui->horizontalSliderPointY->value();
    ui->labelPicList->SetCurrentPoint(value);
}

void ContrastStrengthenDlg::on_btnAddPointY_pressed()
{
    btn = 7;
    iTimes =1;
    AddPointY();
    ClickTimer.start(10);
}

void ContrastStrengthenDlg::on_btnAddPointY_released()
{
    btn = -1;
    ClickTimer.stop();
    int value = ui->horizontalSliderPointY->value();
    ui->labelPicList->SetCurrentPoint(value);
    sendBlancedDataSlot();
}

void ContrastStrengthenDlg::on_horizontalSliderPointY_valueChanged(int value)
{
    QString strPoint;
    strPoint ="(";
    strPoint += QString::number(m_x);
    strPoint +=",";
    strPoint += QString::number(value);
    strPoint +=")";
    ui->txtPointY->setText(strPoint);
    //ui->labelPicList->SetCurrentPoint(value);
}

void ContrastStrengthenDlg::on_horizontalSliderPointSelect_valueChanged(int value)
{
    ui->txtPointSelect->setText(tr("点")+QString::number(value));
    //ui->labelPicList->SetCurrentIndexAd(value);
}

void ContrastStrengthenDlg::on_horizontalSliderPointSelect_sliderReleased()
{
    int value = ui->horizontalSliderPointSelect->value();
    ui->labelPicList->SetCurrentIndexAd(value);
    QPoint point = ui->labelPicList->GetCurrentPoint();
    ui->horizontalSliderPointY->setValue(point.y());
    m_x = point.x();
    QString strPoint;
    strPoint ="(";
    strPoint += QString::number(m_x);
    strPoint +=",";
    strPoint += QString::number(point.y());
    strPoint +=")";
    ui->txtPointY->setText(strPoint);
}

void ContrastStrengthenDlg::on_horizontalSliderPointY_sliderReleased()
{
    int value = ui->horizontalSliderPointY->value();
    ui->labelPicList->SetCurrentPoint(value);
    sendBlancedDataSlot();
}

void ContrastStrengthenDlg::on_btnOk_clicked()
{
    QDialog::accept();
}

void ContrastStrengthenDlg::on_btnQuit_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"),tr("编辑未完成,确定退出!"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(rb == QMessageBox::Yes)
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.pre_model_cfg.balance_model_cfg = m_cfg;
            AcceleratorModuleConfig(ACCE_BALANCE_MODEL_ID,m_step);
        }

        QDialog::reject();
    }

}
