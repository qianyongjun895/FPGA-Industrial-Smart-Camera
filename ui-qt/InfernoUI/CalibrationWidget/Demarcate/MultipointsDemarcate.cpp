#include <QDebug>
#include <QMessageBox>
#include <cstring>
#include "ui_MultipointsDemarcate.h"
#include "MultipointsDemarcate.h"
#include "../Global/UtilitiesFun.h"
#include "Comm/GlobalParameter.h"
#include "xmlInitGlobal.h"
#include "TaskGlobal.h"
#include "LinkDataGlobal.h"
#include "HansRobotGlobal.h"
#include "BasicDefine.h"

MultipointsDemarcate::MultipointsDemarcate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MultipointsDemarcate)
{
    ui->setupUi(this);

    m_point_step = 0;
    m_point_result = 0;
    m_line_step = 0;
    m_line_result = 0;
    m_robot_id = 0;

    qApp->installEventFilter(this);
    m_image_label = new MultipointDemarcateImageLabel(this);
    m_image_label->setGeometry(10,40,640,480);
    m_image_label->setAutoFillBackground(true);
    QPalette p = m_image_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_image_label->setPalette(p);

    if (GlobalParameter::g_user_mode == 1)
    {
        ui->btnImportTestData->show();
    }
    else
    {
        ui->btnImportTestData->hide();
    }

    m_auto_repeat_count = 0;
    m_self_inc = 1;
    param_index = 0;
//    homo_calc_flag = 0;

    int i = 0;
    for(i = 0; i < 9; ++ i)
    {
        phy_points[i].x_f = 0.0f;
        phy_points[i].y_f = 0.0f;
        m_sub_theta[i] = 0.0f;
    }

    for (i = 0; i < 3; ++ i)
    {
        ClearTablePixelDataAxisR(i);
        ccc_point[i].x_f = 0.0f;
        ccc_point[i].y_f = 0.0f;
    }

    memset(&m_homo, 0, sizeof(HOMO_T));

    ui->comboBox_CameraInstallMode->addItem(tr("Fixed"));
    ui->comboBox_CameraInstallMode->addItem(tr("Follow"));
    ui->comboBox_CameraInstallMode->addItem(tr("AGV"));

    // 相机安装方式
    CameraInstallModeComboboxSet(m_homo.install_mode);

    RbtnArmPicDirInit(m_homo.dir_revert);

    connect(m_image_label, & MultipointDemarcateImageLabel::SendCurPoint, \
            this, & MultipointsDemarcate::ShowCurPointCoordinate);
    connect(m_image_label, & MultipointDemarcateImageLabel::CurPointIndexChanged, \
            this, & MultipointsDemarcate::CurPointIndexChangedSlot);
    connect(m_image_label, &MultipointDemarcateImageLabel::UpdateCoordinateTable, \
            this, &MultipointsDemarcate::UpdateCoordinateTableSlot);

    UpdateCoordinateTableSlot();
    UtilitiesFun::Instance()->ListVGA(m_image_label->x(),m_image_label->y());
    UtilitiesFun::Instance()->SetCPT(CPT_CMOS_PIC);

    AgvLinkInfoComboboxInit();
}

MultipointsDemarcate::~MultipointsDemarcate()
{
    if(m_image_label != NULL)
    {
        delete m_image_label;
        m_image_label = NULL;
    }
    delete ui;
    qApp->removeEventFilter(this);
}

bool MultipointsDemarcate::eventFilter(QObject *watched, QEvent *event)
{
//    QList<QPushButton *> btnMove = this->findChildren<QPushButton *>();
    QList<QPushButton *> btnMove;
    btnMove.append(ui->btnMoveUp);
    btnMove.append(ui->btnMoveDown);
    btnMove.append(ui->btnMoveLeft);
    btnMove.append(ui->btnMoveRight);

    foreach (QPushButton * L, btnMove)
    {
        if ((L->objectName() == watched->objectName()) && L->isEnabled())
        {
            if (event->type() == QEvent::MouseButtonRelease)
            {
                if (!((QKeyEvent *)event)->isAutoRepeat())
                {
                    m_auto_repeat_count = 0;
                    m_self_inc = 1;
                    UpdateCoordinateTableSlot();
                }
            }
        }
    }

    return QWidget::eventFilter(watched, event);
}

void MultipointsDemarcate::ShowCurPointCoordinate(QPoint &curPoint)
{
    ui->labelCurPointCoordinate->setText("("+QString::number(curPoint.x())+"," \
                                         +QString::number(curPoint.y())+")");
}

void MultipointsDemarcate::CurPointIndexChangedSlot(int curIndex)
{
    ui->lineEditCurPointIndex->setText(QString::number(curIndex));
}

void MultipointsDemarcate::on_btnQuit_clicked()
{    
    QMessageBox::StandardButton rb = \
            QMessageBox::warning(NULL, \
                                 tr("提示"), \
                                 tr("确定退出?"), \
                                 QMessageBox::Yes | QMessageBox::No, \
                                 QMessageBox::No);

    if(rb == QMessageBox::No)
    {
        return ;
    }

    this->close();
}

void MultipointsDemarcate::on_btnPrev_clicked()
{
    m_image_label->PrevPonitSelected();
    ui->lineEditCurPointIndex->setText(QString::number(m_image_label->GetCurPointIndex()));
}

void MultipointsDemarcate::on_btnNext_clicked()
{
    m_image_label->NextPointSelected();
    ui->lineEditCurPointIndex->setText(QString::number(m_image_label->GetCurPointIndex()));
}

void MultipointsDemarcate::on_btnPointNumInc_clicked()
{
    m_image_label->AddPoint();
    ui->lineEditPointNum->setText(QString::number(m_image_label->GetPointNum()));
    ui->lineEditCurPointIndex->setText(QString::number(m_image_label->GetCurPointIndex()));
}

void MultipointsDemarcate::on_btnPointNumDec_clicked()
{
    m_image_label->DelPoint();
    ui->lineEditPointNum->setText(QString::number(m_image_label->GetPointNum()));
    ui->lineEditCurPointIndex->setText(QString::number(m_image_label->GetCurPointIndex()));
}

void MultipointsDemarcate::UpdateCoordinateTableSlot()
{
    int rowCnt = m_image_label->m_points.count();
//    qDebug() << rowCnt;

    if (rowCnt >= 0)
    {
        ui->tableWidgetPixel->clearContents();
        ui->tableWidgetPixel->setRowCount(rowCnt);
        ui->tableWidgetPhysical->clearContents();
        ui->tableWidgetPhysical->setRowCount(rowCnt);

        int i,j;
        for (i = 0; i < rowCnt; ++ i)
        {
            for (j = 0; j < 2; ++ j)
            {
                ui->tableWidgetPixel->setItem(i,j,new QTableWidgetItem("0"));
                ui->tableWidgetPhysical->setItem(i,j,new QTableWidgetItem("0"));
            }
        }

        int m_x,m_y;
        QPoint m_point;
        for(i = 0; i < rowCnt; ++ i)
        {
            m_x = m_image_label->m_points[i].x();
            m_y = m_image_label->m_points[i].y();
            PixelCvt(&m_x, &m_x, CVT_VGA2REAL | CVT_I2I | CVT_DATA);
            PixelCvt(&m_y, &m_y, CVT_VGA2REAL | CVT_I2I | CVT_DATA);
            m_point.rx() = m_x;
            m_point.ry() = m_y;

            m_real_point[i] = m_point;
            SetTablePixelData(i,m_point);
            SetTablePhyicalData(i,phy_points[i]);
        }
    }
}

void MultipointsDemarcate::SetTablePixelData(int row, QPoint &pixPoint)
{
    ui->tableWidgetPixel->item(row,0)->setText(QString::number(pixPoint.x()));
    ui->tableWidgetPixel->item(row,1)->setText(QString::number(pixPoint.y()));
}

void MultipointsDemarcate::SetTablePhyicalData(int row, POINT_F &phyPoint)
{
    ui->tableWidgetPhysical->item(row,0)->setText(QString::number(phyPoint.x_f,'f',3));
    ui->tableWidgetPhysical->item(row,1)->setText(QString::number(phyPoint.y_f,'f',3));
}

void MultipointsDemarcate::SetTablePixelDataAxisR(int row, QPoint &pixPoint)
{
    ui->tableWidget_AxisR->item(row,0)->setText(QString::number(pixPoint.x()));
    ui->tableWidget_AxisR->item(row,1)->setText(QString::number(pixPoint.y()));
}

void MultipointsDemarcate::SetTableRealPixelDataAxisR(int row, POINT_F &realPixPoint)
{
    ui->tableWidget_AxisR->item(row,0)->setText(QString::number(realPixPoint.x_f,'f',3));
    ui->tableWidget_AxisR->item(row,1)->setText(QString::number(realPixPoint.y_f,'f',3));
}

void MultipointsDemarcate::ClearTablePixelDataAxisR(int row)
{
    ui->tableWidget_AxisR->item(row,0)->setText("--");
    ui->tableWidget_AxisR->item(row,1)->setText("--");
}

void MultipointsDemarcate::PointsParamAdjustEnable(bool bValue)
{
    ui->btnPointNumDec->setEnabled(bValue);
    ui->btnPointNumInc->setEnabled(bValue);
    ui->btnPrev->setEnabled(bValue);
    ui->btnNext->setEnabled(bValue);
    ui->btnMoveUp->setEnabled(bValue);
    ui->btnMoveDown->setEnabled(bValue);
    ui->btnMoveLeft->setEnabled(bValue);
    ui->btnMoveRight->setEnabled(bValue);
}

void MultipointsDemarcate::SeleIncValuePro()
{
    if (m_self_inc < 20)
    {
        ++ m_auto_repeat_count;
        m_self_inc += m_auto_repeat_count / 10;
    }
    else
    {
        m_self_inc = 20;
    }
}

void MultipointsDemarcate::GetPhyDataFromTable()
{
    int rowCnt = ui->tableWidgetPhysical->rowCount();
    if (rowCnt > 9)
    {
        return ;
    }

    int i;
    for (i = 0; i < rowCnt; ++ i)
    {
        phy_points[i].x_f = ui->tableWidgetPhysical->item(i,0)->text().toFloat();
        phy_points[i].y_f = ui->tableWidgetPhysical->item(i,1)->text().toFloat();
    }
}

void MultipointsDemarcate::CameraInstallModeComboboxSet(int installMode)
{
    m_image_label->SetPointMoveFlag(true);
    ShowAgvPrivateBtn(false);
    if (installMode == CAMERA_INSTALL_FIX)
    {
        ui->comboBox_CameraInstallMode->setCurrentIndex(0);
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if (installMode == CAMERA_INSTALL_MOVE)
    {
        ui->comboBox_CameraInstallMode->setCurrentIndex(1);
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if (installMode == CAMERA_INSTALL_AGV)
    {
        ui->comboBox_CameraInstallMode->setCurrentIndex(2);
        ui->stackedWidget->setCurrentIndex(1);
        ShowAgvPrivateBtn(true);
        SetButtonStyle(ui->btnCenterAxisR, ui->btnDemarcateData);
        m_image_label->SetPointMoveFlag(false);
    }
}

void MultipointsDemarcate::AgvLinkInfoComboboxInit()
{
    unsigned int stepCount = 0;
    unsigned int stepType = 0;
    unsigned int stepIndex = 0;
    QString nameString;
    char taskName[40];
    int ret = 0;

    ui->comboBox_LineStep->addItem(tr("无"));
    ui->comboBox_PointStep->addItem(tr("无"));
    stepCount = GetTaskStepCount();
    for(stepIndex = 1; stepIndex <= stepCount; ++ stepIndex)
    {
        Task_Step_Type_ID_Get(stepIndex, &stepType);
        ret = Get_Point_Or_Line_Flag(stepType);
        if (ret == 0 || ret == 1)
        {
            memset(taskName, 0, sizeof(taskName));
            int res = Get_Task_Name(stepIndex, taskName);
            if(res != -1)
            {
                nameString = QString::number(stepIndex) + "." + QString::fromUtf8(taskName);

                if(ret == 0) // 点
                {
                    ui->comboBox_PointStep->addItem(nameString);
                }
                else if (ret == 1) // 线
                {
                    ui->comboBox_LineStep->addItem(nameString);
                }
            }
        }
    }
}

int MultipointsDemarcate::Line_Osd_Init(LineParameter *pLinePara, QLine *pOsdLine)
{
    float line_kf = 0;
    float line_bf = 0;
    float line_k, line_b;

    float pix_vga_y = 0.0;
    float pix_vga_x = 0.0;
    float pix_sub_y = (float)pLinePara->y;
    float pix_sub_x = (float)pLinePara->x;
    PixelCvt((void *)(&pix_sub_y),(void *)(&pix_vga_y),CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    PixelCvt((void *)(&pix_sub_x),(void *)(&pix_vga_x),CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    line_kf = tan(pLinePara->theta);
//    line_bf = (X_Y_CONVERT_SUB2UI((float)pLinePara->y) - line_kf * X_Y_CONVERT_SUB2UI((float)pLinePara->x));
    line_bf = (pix_vga_y - line_kf * pix_vga_x);
    line_k = (int)(line_kf*10000);
    line_b = (int)(line_bf*10000);

    if(line_k == 0x7fffffff || line_k == 0x80000000 || line_b == 0x7fffffff || line_b == 0x80000000)
    {
//        Vertical_Line_Paint((unsigned int)pLinePara->x, pOsdLine);

        pOsdLine->setP1(QPoint(pix_vga_x,0));
        pOsdLine->setP2(QPoint(pix_vga_x,VGA_HEIGHT));
    }
    else
    {
        Line_Paint_Base_On_KB_SubPixel(line_kf, line_bf, pOsdLine);
    }

    return 0;
}

int MultipointsDemarcate::Line_Paint_Base_On_KB_SubPixel(float k_f, float b_f, QLine *pOsd_line)
{
    int i = 0;
    int count = 0;
    QPointF calc_point[4];

    calc_point[0].setX(0);
    calc_point[0].setY(b_f);
    /* Point1 x=640, calculate y  */
    calc_point[1].setX(VGA_WIDTH);
    calc_point[1].setY(k_f*VGA_WIDTH+b_f);
    /* Point1 y=0, calculate x  */
    calc_point[2].setX((0-b_f)/k_f);
    calc_point[2].setY(0);
    /* Point1 y=480, calculate x  */
    calc_point[3].setX((VGA_HEIGHT-b_f)/k_f);
    calc_point[3].setY(VGA_HEIGHT);

    for(i = 0; i < 4; i++)
    {
        //DRV_PRINT(LOCATION_DEBUG, "point%d: x=%d, y=%d\n", i, (int)calc_point[i].x_f, (int)calc_point[i].y_f);
        if(calc_point[i].x()>=0 && calc_point[i].x()<=VGA_WIDTH && calc_point[i].y()>=0 && calc_point[i].y()<=VGA_HEIGHT)
        {
            if(count == 0)
            {
                count++;
                pOsd_line->setP1(QPoint(calc_point[i].x(),calc_point[i].y()));
            }
            else
            {
                pOsd_line->setP2(QPoint(calc_point[i].x(),calc_point[i].y()));
            }
        }
    }

    return 0;
}

void MultipointsDemarcate::SetButtonStyle(QPushButton *pre, QPushButton *current)
{
    if(pre != NULL)
    {
        pre->setStyleSheet("background-color: rgb(255, 255, 255);");
    }

    if(current != NULL)
    {
        current->setStyleSheet("background-color: rgb(249, 220, 117);");
    }
}

void MultipointsDemarcate::ShowAgvPrivateBtn(bool bValue)
{
    if (bValue)
    {
        ui->btnCenterAxisR->show();
        ui->btnDemarcateData->show();
        ui->btnClearAllData->show();
        ui->btnDeleteLastOne->show();
        ui->btnStartDemarcate->show();
    }
    else
    {
        ui->btnCenterAxisR->hide();
        ui->btnDemarcateData->hide();
        ui->btnClearAllData->hide();
        ui->btnDeleteLastOne->hide();
        ui->btnStartDemarcate->hide();
    }
}

void MultipointsDemarcate::RbtnArmPicDirInit(int armPicDir)
{
    if (armPicDir == PIC_ARM_DIR_SAME)
    {
        on_rBtnArmPicDirSame_clicked();
        ui->rBtnArmPicDirSame->setChecked(true);
    }
    else
    {
        on_rBtnArmPicDirReverse_clicked();
        ui->rBtnArmPicDirReverse->setChecked(true);
    }
}

int MultipointsDemarcate::ParamDataInit(int paramIndex)
{
    param_index = paramIndex;

    HOMO_T homo;

    // 获取参数数据并加载到本模块中
    int ret = HomoParamLoadFromFile(paramIndex, &homo);
    if (ret != 0)
    {
        QMessageBox::about(NULL, "提示", "获取参数失败!");
        return -1;
    }

    // 设置标题
    char* name = GetHomoParamName(paramIndex);
    QString m_title = QString::number(paramIndex+1) + "." + QString::fromUtf8(name);
    ui->labelTitle->setText(m_title);

    // 相机安装方式
    m_homo.install_mode = homo.install_mode;
    CameraInstallModeComboboxSet(homo.install_mode);    

    if (homo.install_mode == CAMERA_INSTALL_AGV)
    {

        QPoint point;
        QPoint point_real;
        float point_pix_vga_x = 0.0;
        float point_pix_vga_y = 0.0;
        float point_pix_sub_x = 0.0;
        float point_pix_sub_y = 0.0;

        for (int i = 0; i < 3; ++ i)
        {
            PixelCvt(&homo.ccc_points[i].x_f,&point_pix_sub_x,CVT_REAL2SUB|CVT_F2F|CVT_DATA);
            PixelCvt(&homo.ccc_points[i].y_f,&point_pix_sub_y,CVT_REAL2SUB|CVT_F2F|CVT_DATA);

            PixelCvt(&point_pix_sub_x,&point_pix_vga_x,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
            PixelCvt(&point_pix_sub_y,&point_pix_vga_y,CVT_SUB2VGA|CVT_F2F|CVT_DATA);

            point.setX(point_pix_vga_x);
            point.setY(point_pix_vga_y);

            point_real.setX(homo.ccc_points[i].x_f);
            point_real.setY(homo.ccc_points[i].y_f);

            m_image_label->AddPointAxisR(point.x(), point.y());
            SetTablePixelDataAxisR(i, point_real);
            ccc_point[i].x_f = homo.ccc_points[i].x_f;
            ccc_point[i].y_f = homo.ccc_points[i].y_f;
        }

        SetTableRealPixelDataAxisR(3, homo.c_center);
    }

    QPoint tmpPoint;

    m_image_label->m_points.clear();
    for(int i = 0; i < homo.numpt; ++ i)
    {
        tmpPoint.rx() = static_cast<int>(homo.pts[i].img_x);
        tmpPoint.ry() = static_cast<int>(homo.pts[i].img_y);
        m_image_label->m_points.append(tmpPoint);

        phy_points[i].x_f = static_cast<float>(homo.pts[i].true_x);
        phy_points[i].y_f = static_cast<float>(homo.pts[i].true_y);
    }

    ui->lineEditPointNum->setText(QString::number(m_image_label->GetPointNum()));
//    qDebug() << m_image_label->GetPointNum();

    UpdateCoordinateTableSlot();

    return 0;
}

void MultipointsDemarcate::SetParamIndex(int paramIndex)
{
    param_index = paramIndex;
}

void MultipointsDemarcate::SetCurRobotID(int id)
{
    m_robot_id = id;
}

void MultipointsDemarcate::on_btnMoveUp_clicked()
{
    SeleIncValuePro();
    m_image_label->CurPointMoveUp(m_self_inc);
    UpdateCoordinateTableSlot();
}

void MultipointsDemarcate::on_btnMoveDown_clicked()
{
    SeleIncValuePro();
    m_image_label->CurPointMoveDown(m_self_inc);
    UpdateCoordinateTableSlot();
}

void MultipointsDemarcate::on_btnMoveLeft_clicked()
{
    SeleIncValuePro();
    m_image_label->CurPointMoveLeft(m_self_inc);
    UpdateCoordinateTableSlot();
}

void MultipointsDemarcate::on_btnMoveRight_clicked()
{
    SeleIncValuePro();
    m_image_label->CurPointMoveRight(m_self_inc);
    UpdateCoordinateTableSlot();
}

void MultipointsDemarcate::on_btnCalc_clicked()
{
    int i = 0, pointNum = 0;

    QMessageBox::StandardButton rb = \
            QMessageBox::warning(NULL, \
                                 tr("提示"), \
                                 tr("参数是否完整?"), \
                                 QMessageBox::Yes | QMessageBox::No, \
                                 QMessageBox::No);

    if(rb == QMessageBox::No)
    {
        return ;
    }

    GetPhyDataFromTable();
    pointNum = m_image_label->m_points.count();
    m_homo.trigger_mode = 0;
    m_homo.numpt = pointNum;
    qDebug() << "pointNum:" << pointNum;

    m_theta = 0.0;
    for (i = 0; i < pointNum; ++ i)
    {
        m_homo.pts[i].img_x = m_image_label->m_points[i].x();
        m_homo.pts[i].img_y = m_image_label->m_points[i].y();

        m_homo.pts[i].true_x = phy_points[i].x_f;
        m_homo.pts[i].true_y = phy_points[i].y_f;

//        m_theta += m_sub_theta[i];
    }

    if (pointNum > 0)
    {
//        m_theta /= pointNum;
        m_theta = m_sub_theta[0];
        m_homo.origin_theta = m_theta;
        qDebug() << "origin theta: " << m_homo.origin_theta;
    }

    for (i = 0; i < 3; ++ i)
    {
        m_homo.ccc_points[i].x_f = ccc_point[i].x_f;
        m_homo.ccc_points[i].y_f = ccc_point[i].y_f;
    }

    m_homo.dir_revert = m_arm_pic_dir;

    int ret = Homo_Calc_Conver_Parameter(&m_homo);
    if (ret == 0)
    {
        HomoParamSaveToFile(param_index, &m_homo);
        SetTableRealPixelDataAxisR(3,m_homo.c_center);
        QMessageBox::about(NULL, tr("提示"), tr("标定成功"));
    }
    else
    {
        QMessageBox::about(NULL, tr("提示"), tr("标定失败"));
    }
}

void MultipointsDemarcate::on_tableWidgetPhysical_cellClicked(int row, int column)
{
    QDialog *dlg = m_KeyBoardLib.GetNumKeyBoardDialog();
//            dlg.SetNaturalNumberInputMode(true);
//    dlg.SetOldNum(ui->tableWidgetPhysical->item(row,column)->text());
    int ret = dlg->exec();
    if(ret == QDialog::Accepted)
    {
        ui->tableWidgetPhysical->item(row,column)->setText(m_KeyBoardLib.GetNum());
        GetPhyDataFromTable();
    }
}

//void MultipointsDemarcate::on_btnSave_clicked()
//{
//    if (homo_calc_flag == 1)
//    {
//        HomoParamSaveToFile(param_index, &m_homo);
//    }
//}

void MultipointsDemarcate::on_btnImportTestData_clicked()
{
    int i = 0, pointNum = 0;

    pointNum = m_image_label->m_points.count();
    qDebug() << __FUNCTION__ << " pointNum:" << pointNum;

    for (i = 0; i < pointNum; ++ i)
    {
        ui->tableWidgetPhysical->item(i,0)->setText(QString::number(m_real_point[i].x(),'f',3));
        ui->tableWidgetPhysical->item(i,1)->setText(QString::number(m_real_point[i].y(),'f',3));
    }
}

void MultipointsDemarcate::on_comboBox_CameraInstallMode_currentIndexChanged(int index)
{
    m_homo.install_mode = index;
    if (index == 2)
    {
        m_image_label->SetPointMoveFlag(false);
        ui->stackedWidget->setCurrentIndex(1);
        SetButtonStyle(ui->btnCenterAxisR, ui->btnDemarcateData);
        ShowAgvPrivateBtn(true);
    }
    else
    {
        m_image_label->SetPointMoveFlag(true);
        ui->stackedWidget->setCurrentIndex(0);
        ui->stackedWidget_Data->setCurrentIndex(0);
        ShowAgvPrivateBtn(false);
    }
}

void MultipointsDemarcate::on_comboBox_PointStep_currentIndexChanged(int index)
{
    int stepIndex = atoi(ui->comboBox_PointStep->currentText().toStdString().c_str());
    m_point_step = stepIndex;
    if(stepIndex == 0)
    {
        ui->comboBox_PointResult->clear();
        return;
    }

    ui->comboBox_PointResult->setEnabled(true);

    ui->comboBox_PointResult->clear();
    ui->comboBox_PointResult->addItem(" ");
    m_point_result = 0;
    unsigned int stepType;
    Task_Step_Type_ID_Get(stepIndex ,&stepType);
    int  mul_rst_flg = Get_Multi_Result_Task_Flag(stepType);
    if(mul_rst_flg == 1)
    {
        unsigned int i_mul_rst_cnt = 0;
        TaskMultiRstNumGet(stepIndex, 1, &i_mul_rst_cnt);
        for(unsigned int i = 1; i <= i_mul_rst_cnt; ++ i)
        {
            QString strLineIndex;
            strLineIndex = tr("点")+QString::number(i);
            ui->comboBox_PointResult->addItem(strLineIndex);
        }
    }
    else
    {
        ui->comboBox_PointResult->setEnabled(false);
    }
}

void MultipointsDemarcate::on_comboBox_LineStep_currentIndexChanged(int index)
{
    int stepIndex = atoi(ui->comboBox_LineStep->currentText().toStdString().c_str());
    m_line_step = stepIndex;
    if(stepIndex == 0)
    {
        ui->comboBox_LineResult->clear();
        return;
    }

    ui->comboBox_LineResult->setEnabled(true);

    ui->comboBox_LineResult->clear();
    ui->comboBox_LineResult->addItem(" ");
    m_line_result = 0;
    unsigned int stepType;
    Task_Step_Type_ID_Get(stepIndex ,&stepType);
    int  mul_rst_flg = Get_Multi_Result_Task_Flag(stepType);
    if(mul_rst_flg == 1)
    {
        unsigned int i_mul_rst_cnt = 0;
        TaskMultiRstNumGet(stepIndex, 1, &i_mul_rst_cnt);
        for(unsigned int i = 1; i <= i_mul_rst_cnt; ++ i)
        {
            QString strLineIndex;
            strLineIndex = tr("线")+QString::number(i);
            ui->comboBox_LineResult->addItem(strLineIndex);
        }
    }
    else
    {
        ui->comboBox_LineResult->setEnabled(false);
    }
}

void MultipointsDemarcate::on_comboBox_PointResult_currentIndexChanged(int index)
{
    m_point_result = index;
}

void MultipointsDemarcate::on_comboBox_LineResult_currentIndexChanged(int index)
{
    m_line_result = index;
}

void MultipointsDemarcate::on_btnClearAllData_clicked()
{
    QMessageBox::StandardButton rb = \
            QMessageBox::warning(NULL, \
                                 tr("提示"), \
                                 tr("清空当前全部数据?"), \
                                 QMessageBox::Yes | QMessageBox::No, \
                                 QMessageBox::No);

    if(rb == QMessageBox::No)
    {
        return ;
    }

    int i = 0;
    int pointCount = 0;
    pointCount = m_image_label->GetPointNum();
    for (i = 0; i < pointCount; ++ i)
    {
        phy_points[i].x_f = 0.0;
        phy_points[i].y_f = 0.0;
    }
    m_image_label->ClearAllPoints();
    ui->lineEditPointNum->setText("0");
    ui->lineEditCurPointIndex->setText("0");
}

void MultipointsDemarcate::on_btnStartDemarcate_clicked()
{
    unsigned int i_ng_step[256];
    unsigned int i_ng_step_cnt = 0;
    i_ng_step_cnt = GetStepParamInvalidInfo(i_ng_step, sizeof(i_ng_step));

    if(i_ng_step_cnt == 0)
    {
        SetRoundOverFlag(0);
        TaskExecNRound(1);
    }

    QPoint point;
    float point_pix_vga_x = 0.0;
    float point_pix_vga_y = 0.0;
    float point_pix_sub_x = 0.0;
    float point_pix_sub_y = 0.0;

    POINT_F pointf;
    unsigned int p_id;
    Task_Step_Type_ID_Get(m_point_step, &p_id);
    int result_index = Get_Point_Or_Line_Result_Id(p_id,m_point_result);
    int ret = measure_ref_point_result_get(m_point_step,result_index,&pointf,0);
    if(ret != 0)
    {
//        qDebug() << "measure_ref_point_result_get ret = " << QString::number(ret;
        qDebug("measure_ref_point_result_get ret = %x", ret);
        return ;
    }

    point_pix_sub_x = pointf.x_f;
    point_pix_sub_y = pointf.y_f;
    PixelCvt(&point_pix_sub_x,&point_pix_vga_x,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    PixelCvt(&point_pix_sub_y,&point_pix_vga_y,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    point.setX(point_pix_vga_x);
    point.setY(point_pix_vga_y);
    qDebug() << "point.x:" << point.x() << "point.y" << point.y();
    m_image_label->AddPoint(point.x(), point.y());

    double i_robot_info[6];
    hans_robot_phy_coor_get(i_robot_info, m_robot_id);
    int curPointIndex = m_image_label->GetCurPointIndex();
    phy_points[curPointIndex - 1].x_f = static_cast<float>(i_robot_info[0]);
    phy_points[curPointIndex - 1].y_f = static_cast<float>(i_robot_info[1]);

    LineParameter lineParam;
    unsigned int l_id;
    Task_Step_Type_ID_Get(m_line_step, &l_id);
    result_index = Get_Point_Or_Line_Result_Id(l_id, m_line_result);
    ret = measure_ref_line_result_get(m_line_step, result_index, &lineParam, 0);
    if (ret == 0)
    {
        m_sub_theta[curPointIndex - 1] = static_cast<float>(lineParam.theta);
        qDebug() << "cur line theta: " << m_sub_theta[curPointIndex - 1];
        QLine i_line;
        Line_Osd_Init(&lineParam, &i_line);
        m_image_label->SetBaseLine(i_line);
    }

    UpdateCoordinateTableSlot();
}

void MultipointsDemarcate::on_btnDeleteLastOne_clicked()
{
    m_image_label->DeleteLastOnePoint();
}

void MultipointsDemarcate::on_btnCenterAxisR_clicked()
{
    SetButtonStyle(ui->btnDemarcateData, ui->btnCenterAxisR);
    ui->stackedWidget_Data->setCurrentIndex(1);
    m_image_label->SetOsdPaintContent(1);
}

void MultipointsDemarcate::on_btnDemarcateData_clicked()
{
    SetButtonStyle(ui->btnCenterAxisR, ui->btnDemarcateData);
    ui->stackedWidget_Data->setCurrentIndex(0);
    m_image_label->SetOsdPaintContent(0);
}

void MultipointsDemarcate::on_btnGetOnePointAxisR_clicked()
{
    unsigned int i_ng_step[256];
    unsigned int i_ng_step_cnt = 0;
    i_ng_step_cnt = GetStepParamInvalidInfo(i_ng_step, sizeof(i_ng_step));

    if(i_ng_step_cnt != 0)
    {
        QString ngSteps;
        ngSteps.clear();
        for (unsigned int i = 0; i < i_ng_step_cnt; ++ i)
        {
            ngSteps += QString::number(i_ng_step[i]) + ",";
        }
        QMessageBox::about(NULL, tr("提示"), tr("以下步骤参数无效:") + ngSteps);
        return ;
    }

    SetRoundOverFlag(0);
    TaskExecNRound(1);

    QPoint point;
    QPoint point_real;
    float point_pix_vga_x = 0.0;
    float point_pix_vga_y = 0.0;
    float point_pix_sub_x = 0.0;
    float point_pix_sub_y = 0.0;
    float point_pix_real_x = 0.0;
    float point_pix_real_y = 0.0;

    POINT_F pointf;
    unsigned int p_id;
    Task_Step_Type_ID_Get(m_point_step, &p_id);
    int result_index = Get_Point_Or_Line_Result_Id(p_id,m_point_result);
    int ret = measure_ref_point_result_get(m_point_step,result_index,&pointf,0);
    if(ret != 0)
    {
//        qDebug() << "measure_ref_point_result_get ret = " << QString::number(ret;
        qDebug("measure_ref_point_result_get ret = %x", ret);
        return ;
    }

    point_pix_sub_x = pointf.x_f;
    point_pix_sub_y = pointf.y_f;
    PixelCvt(&point_pix_sub_x,&point_pix_vga_x,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    PixelCvt(&point_pix_sub_y,&point_pix_vga_y,CVT_SUB2VGA|CVT_F2F|CVT_DATA);
    PixelCvt(&point_pix_sub_x,&point_pix_real_x,CVT_SUB2REAL|CVT_F2F|CVT_DATA);
    PixelCvt(&point_pix_sub_y,&point_pix_real_y,CVT_SUB2REAL|CVT_F2F|CVT_DATA);
    point.setX(point_pix_vga_x);
    point.setY(point_pix_vga_y);
    point_real.setX(point_pix_real_x);
    point_real.setY(point_pix_real_y);
    qDebug() << "point.x:" << point.x() << "point.y" << point.y();
    m_image_label->AddPointAxisR(point.x(), point.y());
    int row = m_image_label->GetCurPointIndexAxisR();
    if (row > 0)
    {
        SetTablePixelDataAxisR(row - 1, point_real);
        ccc_point[row - 1].x_f = point_pix_real_x;
        ccc_point[row - 1].y_f = point_pix_real_y;
    }
}

void MultipointsDemarcate::on_btnClearAllDataAxisR_clicked()
{
    int i = 0;
    m_image_label->ClearAllPoints();
    for (i = 0; i < 3; ++ i)
    {
        ClearTablePixelDataAxisR(i);
        ccc_point[i].x_f = 0.0;
        ccc_point[i].y_f = 0.0;
        m_image_label->DeleteLastOnePointAxisR();
    }
    ClearTablePixelDataAxisR(3);
}

void MultipointsDemarcate::on_btnDeleteLastOneAxisR_clicked()
{
    int row = m_image_label->GetCurPointIndexAxisR();
    if (row > 0)
    {
        ClearTablePixelDataAxisR(row - 1);
        ccc_point[row - 1].x_f = 0.0;
        ccc_point[row - 1].y_f = 0.0;
    }
    m_image_label->DeleteLastOnePointAxisR();
}

void MultipointsDemarcate::on_rBtnArmPicDirSame_clicked()
{
    m_arm_pic_dir = PIC_ARM_DIR_SAME;
}

void MultipointsDemarcate::on_rBtnArmPicDirReverse_clicked()
{
    m_arm_pic_dir = PIC_ARM_DIR_REVERT;
}
