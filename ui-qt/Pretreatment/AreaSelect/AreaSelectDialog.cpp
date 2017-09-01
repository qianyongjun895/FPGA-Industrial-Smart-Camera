#include <qdebug.h>
#include "AreaSelectDialog.h"
#include "ui_AreaSelectDialog.h"
#include <math.h>
#include <stdio.h>
#include <QMessageBox>
#include "../../Global/UtilitiesFun.h"
#include "AcceCommon.h"
#include "cmos_common.h"

#define THREEPOLYGON 3
#define FOURPOLYGON 4
#define FIVEPOLYGON 5
#define SIXPOLYGON 6
#define SEVENPOLYGON 7
#define EIGHTPOLYGON 8
#define THREEPOLYGON_BITMAP 7
#define FOURPOLYGON_BITMAP 15
#define FIVEPOLYGON_BITMAP 31
#define SIXPOLYGON_BITMAP 63
#define SEVENPOLYGON_BITMAP 127
#define EIGHTPOLYGON_BITMAP 255

AreaSelectDialog::AreaSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AreaSelectDialog)
{
    ui->setupUi(this);
    m_i_poloygon_num = 0;
    m_i_circle_num = 0;
    IniToolTable();
    timerUpData = new QTimer(this);
    connect(ui->labelPicOsd,&FWAreaSelect::signalsValueChange,this,&AreaSelectDialog::SlotValueChange);
    ui->radioButtonColor->setVisible(false);
    ui->radioButtonGray->setVisible(false);
    m_image_scale =1;
    ui->labelPicOsd->SetLimit(UtilitiesFun::Instance()->GetStartX(),UtilitiesFun::Instance()->GetEndX(),UtilitiesFun::Instance()->GetStartY(),UtilitiesFun::Instance()->GetEndY());
    /*int ret = Get_HWC_Pixel_Size();

    if(ret == 0x02)
    {
        m_image_scale =1;

    }else if(ret == 0x04)
    {
        m_image_scale =4;

    }else if(ret == 0x10)
    {
        m_image_scale =16;
    }*/
    pen = NULL;
}

AreaSelectDialog::~AreaSelectDialog()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        ptr->image_acce_param.select_model_cfg.mono_pic_wr_en = 0;
        ptr->image_acce_param.select_model_cfg.color_pic_wr_en = 0;
        AcceleratorModuleConfig(ACCE_AREA_SELECT_MODEL_ID,m_step);
    }
    UtilitiesFun::Instance()->ListVGA(ui->labelPicOsd->x(),ui->labelPicOsd->y(),0xffffffff);
    disconnect(this,0,0,0);
    delete timerUpData;
    delete ui;
}

void AreaSelectDialog::on_btnOK_clicked()
{
    SetDataToLib();
    disconnect(this,0,0,0);
    QDialog::accept();
}

void AreaSelectDialog::on_btnQuit_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"),tr("编辑未完成,确定退出!"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(rb == QMessageBox::Yes)
    {
        ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

        if(ptr != NULL)
        {
            ptr->image_acce_param.select_model_cfg = m_select_model_cfg;
        }

        QDialog::reject();
    }
}
void AreaSelectDialog::IniToolTable()
{
    QTableWidget *table = ui->tableWidgetTool;
    table->setRowCount(0);
    table->setColumnCount(1);
    QStringList horizontalHeader;
    horizontalHeader<<QObject::tr("Tool");
    table->setHorizontalHeaderLabels(horizontalHeader);
    table->horizontalHeader()->resizeSection(0,ui->tableWidgetTool->width()-5);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

}
void AreaSelectDialog::RemoveToolTableData()
{
    int row = ui->tableWidgetTool->currentRow();

    if(row >= 0)
    {

        int indexRow = FindToolIndex(row);
        ui->labelPicOsd->DeleteTool(m_vt_tool_kind[row],indexRow);

        ui->tableWidgetTool->removeRow(row);
        m_vt_tool_kind.removeAt(row);

        if(m_vt_tool_kind[row] == RINGTOOL)
        {
            this->m_i_circle_num--;

        }else if(m_vt_tool_kind[row] == POLYGONTOOL)
        {
            this->m_i_poloygon_num--;
        }else if(m_vt_tool_kind[row] == RECTTOOL)
        {
            this->m_i_poloygon_num--;
        }

        //ui->labelPicOsd->DeleteTool()
        row = ui->tableWidgetTool->currentRow();
        if(row >= 0)
        {
            int indexRow = FindToolIndex(row);
            ui->labelPicOsd->SelectTool(m_vt_tool_kind[row],indexRow);
            ListOsdAdjustWidget(m_vt_tool_kind[row]);
        }else
        {
            ListOsdAdjustWidget(OTHERS);
        }

    }

}
void AreaSelectDialog::AddToolTableData(QString strName,TOOL_KIND toolKind)
{
    int count = ui->tableWidgetTool->rowCount();
    ui->tableWidgetTool->setRowCount(count+1);
    ui->tableWidgetTool->setItem(count,0,new QTableWidgetItem(strName));
    ui->tableWidgetTool->setCurrentCell(count,0);
    this->m_vt_tool_kind.append(toolKind);
    ui->labelPicOsd->AddTool(toolKind);
    ListOsdAdjustWidget(toolKind);
    int indexRow = FindToolIndex(count);
    ui->labelPicOsd->SelectTool(m_vt_tool_kind[count],indexRow);
}
int AreaSelectDialog::FindToolIndex(int row)
{
    int count = row+1;
    int index = -1;
    int toolKind = m_vt_tool_kind[row];

    for(int i=0; i< count;i++)
    {
        if(toolKind == m_vt_tool_kind[i])
        {
            index++;
        }
    }

    return index;
}
void AreaSelectDialog::ListOsdAdjustWidget(TOOL_KIND toolKind)
{
    QString strtemp;
    switch (toolKind) {
    case RINGTOOL:
        ui->stackedWidget->setCurrentIndex(2);
        ui->txtRadiusOut->setText(QString::number(ui->labelPicOsd->GetRingROut()));
        ui->txtRadiusIn->setText(QString::number(ui->labelPicOsd->GetRingRIn()));
        ui->txtCenterXOut->setText(QString::number(ui->labelPicOsd->GetRingCenter().x()));
        ui->txtCenterYOut->setText(QString::number(ui->labelPicOsd->GetRingCenter().y()));
        break;
    case POLYGONTOOL:
        ui->stackedWidget->setCurrentIndex(3);
        ui->labelPolygonPointNum->setText(QString::number(ui->labelPicOsd->GetPolygonPointNum()));
        SetLabelXYVisable();
        SetLabelXY();
        break;
    case RECTTOOL:
        ui->stackedWidget->setCurrentIndex(0);
        ui->radioButtonRectLefttop->setChecked(true);
        ui->radioButtonRectRightBottom->setChecked(false);
        strtemp = "(";
        strtemp +=QString::number(ui->labelPicOsd->GetRectPoint(0).x());
        strtemp += ",";
        strtemp +=QString::number(ui->labelPicOsd->GetRectPoint(0).y());
        strtemp += ")";
        ui->LabelRect1->setText(strtemp);
        strtemp = "(";
        strtemp +=QString::number(ui->labelPicOsd->GetRectPoint(2).x());
        strtemp += ",";
        strtemp +=QString::number(ui->labelPicOsd->GetRectPoint(2).y());
        strtemp += ")";
        ui->LabelRect2->setText(strtemp);
        break;
    default:
        ui->stackedWidget->setCurrentIndex(4);
        break;
    }
    ui->labelPicOsd->update();
}
void AreaSelectDialog::on_tableWidgetTool_clicked(const QModelIndex &index)
{

    int row = index.row();

    if(row >=0)
    {
        int indexRow = FindToolIndex(row);
        ui->labelPicOsd->SelectTool(m_vt_tool_kind[row],indexRow);
        ListOsdAdjustWidget(m_vt_tool_kind[row]);
    }
}
void AreaSelectDialog::on_btnRect_clicked()
{
    if(m_i_poloygon_num >= 4)
        return;
    m_i_poloygon_num++;
    AddToolTableData(tr("矩形"),RECTTOOL);
}

void AreaSelectDialog::on_btnCircle_clicked()
{
    //AddToolTableData(tr("Circle"),CIRCLETOOL);
}

void AreaSelectDialog::on_btnRing_clicked()
{
    if(m_i_circle_num >= 4)
        return;
    m_i_circle_num++;
    AddToolTableData(tr("Ring"),RINGTOOL);
}

void AreaSelectDialog::on_btnPolygon_clicked()
{
    if(m_i_poloygon_num >= 4)
        return;
    m_i_poloygon_num++;
    AddToolTableData(tr("Polygon"),POLYGONTOOL);
    ui->labelPolygonCurrentPoint->setText("1");
}

void AreaSelectDialog::on_bntDel_clicked()
{
    RemoveToolTableData();
    SetDataToLib();
}
//增加多边形点数 最多8边形，最小三边形
void AreaSelectDialog::on_btnPolygonAddPoint_clicked()
{
    ui->labelPicOsd->AddPolygonPoint();
    int value = ui->labelPicOsd->GetPolygonPointNum();
    ui->labelPolygonPointNum->setText(QString::number(value));
    SetLabelXYVisable();
    SetLabelXY();

}
//减小多边形点数 最多8边形，最小三边形
void AreaSelectDialog::on_btnPolygonSubPoint_clicked()
{
    ui->labelPicOsd->SubPolygonPoint();
    int value = ui->labelPicOsd->GetPolygonPointNum();
    ui->labelPolygonPointNum->setText(QString::number(value));
    SetLabelXYVisable();
    SetLabelXY();
}
//切换多边形角点
void AreaSelectDialog::on_btnPolygonPrev_clicked()
{
    //int value = ui->labelPicOsd->GetPolygonPointNum();
    int currentValue = ui->labelPolygonCurrentPoint->text().toInt();
    if(currentValue > 1)
    {
        currentValue--;
        ui->labelPolygonCurrentPoint->setText(QString::number(currentValue));
    }
}
//切换多边形角点
void AreaSelectDialog::on_btnPolygonNext_clicked()
{
    int currentValue = ui->labelPolygonCurrentPoint->text().toInt();
    int value = ui->labelPicOsd->GetPolygonPointNum();
    if(currentValue < value )
    {
        currentValue++;
        ui->labelPolygonCurrentPoint->setText(QString::number(currentValue));
    }
}

void AreaSelectDialog::btnPolygonUp()
{
    if(this->m_iPresstimes >0 && m_iPresstimes<8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int currentPoint = ui->labelPolygonCurrentPoint->text().toInt()-1;
    ui->labelPicOsd->UpPolygonAdjust(currentPoint);
}

void AreaSelectDialog::btnPolygonRight()
{
    if(this->m_iPresstimes >0 && m_iPresstimes<8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int currentPoint = ui->labelPolygonCurrentPoint->text().toInt()-1;
    ui->labelPicOsd->RightPolygonAdjust(currentPoint);

}

void AreaSelectDialog::btnPolygonDown()
{
    if(this->m_iPresstimes >0 && m_iPresstimes<8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int currentPoint = ui->labelPolygonCurrentPoint->text().toInt()-1;
    ui->labelPicOsd->DownPolygonAdjust(currentPoint);
}

void AreaSelectDialog::btnPolygonLeft()
{
    if(this->m_iPresstimes >0 && m_iPresstimes<8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int currentPoint = ui->labelPolygonCurrentPoint->text().toInt()-1;
    ui->labelPicOsd->LeftPolygonAdjust(currentPoint);
}

//增加圆环外半径
void AreaSelectDialog::btnAddRadiusOut()
{
    if(this->m_iPresstimes >0 && m_iPresstimes<8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;
    int r,value;
    value =1;
    r = ui->txtRadiusOut->text().toInt();
    if(m_iPresstimes > 20)
        value = 12;
    else if(m_iPresstimes > 15)
        value = 4;
    else if(m_iPresstimes >10)
        value = 2;

    if(value+r <= 250)
    {
        r = value+r;
        ui->txtRadiusOut->setText(QString::number(r));
        ui->labelPicOsd->SetRingROut(r);
    }
}
//减小圆环外半径
void AreaSelectDialog::btnSubRadiusOut()
{

    if(this->m_iPresstimes >0 && m_iPresstimes<8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int valueIn = ui->txtRadiusIn->text().toInt();
    int valueOut = ui->txtRadiusOut->text().toInt();
    int r,value;
    value =1;
    if(m_iPresstimes > 20)
        value = 12;
    else if(m_iPresstimes > 15)
        value = 4;
    else if(m_iPresstimes >10)
        value = 2;

    if(valueOut-value >= valueIn)
    {
        r = valueOut-value;
        ui->txtRadiusOut->setText(QString::number(r));
        ui->labelPicOsd->SetRingROut(r);
    }

}
//设置圆环外中心点向上移
void AreaSelectDialog::btnCircleUPOut()
{
    if(this->m_iPresstimes >0 && m_iPresstimes<8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int x, y;
    x = ui->labelPicOsd->GetRingCenter().x();
    y = ui->labelPicOsd->GetRingCenter().y()-1;
    ui->labelPicOsd->SetRingCenter(x,y);
    SlotValueChange(RINGTOOL);
}
//设置圆环外中心点向下移
void AreaSelectDialog::btnCircleDownOut()
{
    if(this->m_iPresstimes >0 && m_iPresstimes<8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int x, y;
    x = ui->labelPicOsd->GetRingCenter().x();
    y = ui->labelPicOsd->GetRingCenter().y()+1;
    ui->labelPicOsd->SetRingCenter(x,y);
    SlotValueChange(RINGTOOL);
}
//设置圆环外中心点向左移
void AreaSelectDialog::btnCircleLeftOut()
{
    if(this->m_iPresstimes >0 && m_iPresstimes<8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int x, y;
    x = ui->labelPicOsd->GetRingCenter().x() - 1;
    y = ui->labelPicOsd->GetRingCenter().y();
    ui->labelPicOsd->SetRingCenter(x,y);
    SlotValueChange(RINGTOOL);
}
//设置圆环外中心点向右移
void AreaSelectDialog::btnCircleRightOut()
{
    if(this->m_iPresstimes >0 && m_iPresstimes<8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int x, y;
    x = ui->labelPicOsd->GetRingCenter().x() + 1;
    y = ui->labelPicOsd->GetRingCenter().y();
    ui->labelPicOsd->SetRingCenter(x,y);
    SlotValueChange(RINGTOOL);
}
//设置增加内圆环半径
void AreaSelectDialog::btnAddRadiusIn()
{
    if(this->m_iPresstimes >0 && m_iPresstimes<8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int valueIn = ui->txtRadiusIn->text().toInt();
    int valueOut = ui->txtRadiusOut->text().toInt();
    int r,value;
    value =1;
    if(m_iPresstimes > 20)
        value = 12;
    else if(m_iPresstimes > 15)
        value = 4;
    else if(m_iPresstimes >10)
        value = 2;

    if(valueOut >= valueIn+value)
    {
        r = valueIn + value;
        ui->txtRadiusIn->setText(QString::number(r));
        ui->labelPicOsd->SetRingRIn(r);
    }

}
//设置减小内圆环半径
void AreaSelectDialog::btnSubRadiusIn()
{

    if(this->m_iPresstimes >0 && m_iPresstimes<8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int valueIn = ui->txtRadiusIn->text().toInt();
    int r,value;
    value =1;
    if(m_iPresstimes > 20)
        value = 12;
    else if(m_iPresstimes > 15)
        value = 4;
    else if(m_iPresstimes >10)
        value = 2;

    if(valueIn-value >= 0)
    {
        r = valueIn - value;
        ui->txtRadiusIn->setText(QString::number(r));
        ui->labelPicOsd->SetRingRIn(r);
    }

}
void AreaSelectDialog::SlotValueChange(TOOL_KIND kind)
{
    if(kind == RINGTOOL)
    {
        ui->txtCenterXOut->setText(QString::number(ui->labelPicOsd->GetRingCenter().x()));
        ui->txtCenterYOut->setText(QString::number(ui->labelPicOsd->GetRingCenter().y()));

    }else if(kind == POLYGONTOOL)
    {
        SetLabelXY();

    }else if(kind == RECTTOOL)
    {
        QString strtemp;
        strtemp = "(";
        strtemp +=QString::number(ui->labelPicOsd->GetRectPoint(0).x());
        strtemp += ",";
        strtemp +=QString::number(ui->labelPicOsd->GetRectPoint(0).y());
        strtemp += ")";
        ui->LabelRect1->setText(strtemp);
        strtemp = "(";
        strtemp +=QString::number(ui->labelPicOsd->GetRectPoint(2).x());
        strtemp += ",";
        strtemp +=QString::number(ui->labelPicOsd->GetRectPoint(2).y());
        strtemp += ")";
        ui->LabelRect2->setText(strtemp);
    }
}
QString AreaSelectDialog::GetStrXY(int ix,int iy)
{
    QString strTemp;
    strTemp = "(";
    strTemp += QString::number(ix);
    strTemp += ",";
    strTemp += QString::number(iy);
    strTemp += ")";
    return strTemp;
}

void AreaSelectDialog::SetLabelXYVisable()
{
    ui->labelPoint1->setVisible(true);
    ui->labelPoint2->setVisible(true);
    ui->labelPoint3->setVisible(true);
    ui->labelPoint4->setVisible(true);
    ui->labelPoint5->setVisible(true);
    ui->labelPoint6->setVisible(true);
    ui->labelPoint7->setVisible(true);
    ui->labelPoint8->setVisible(true);

    ui->labelPointName1->setVisible(true);
    ui->labelPointName2->setVisible(true);
    ui->labelPointName3->setVisible(true);
    ui->labelPointName4->setVisible(true);
    ui->labelPointName5->setVisible(true);
    ui->labelPointName6->setVisible(true);
    ui->labelPointName7->setVisible(true);
    ui->labelPointName8->setVisible(true);

    int inum = ui->labelPicOsd->GetPolygonPointNum();
    if(inum == 3)
    {
        ui->labelPoint4->setVisible(false);
        ui->labelPoint5->setVisible(false);
        ui->labelPoint6->setVisible(false);
        ui->labelPoint7->setVisible(false);
        ui->labelPoint8->setVisible(false);

        ui->labelPointName4->setVisible(false);
        ui->labelPointName5->setVisible(false);
        ui->labelPointName6->setVisible(false);
        ui->labelPointName7->setVisible(false);
        ui->labelPointName8->setVisible(false);

    }else if(inum == 4)
    {
        ui->labelPoint5->setVisible(false);
        ui->labelPoint6->setVisible(false);
        ui->labelPoint7->setVisible(false);
        ui->labelPoint8->setVisible(false);

        ui->labelPointName5->setVisible(false);
        ui->labelPointName6->setVisible(false);
        ui->labelPointName7->setVisible(false);
        ui->labelPointName8->setVisible(false);

    }else if(inum == 5)
    {
        ui->labelPoint6->setVisible(false);
        ui->labelPoint7->setVisible(false);
        ui->labelPoint8->setVisible(false);

        ui->labelPointName6->setVisible(false);
        ui->labelPointName7->setVisible(false);
        ui->labelPointName8->setVisible(false);
    }
    else if(inum == 6)
    {
        ui->labelPoint7->setVisible(false);
        ui->labelPoint8->setVisible(false);

        ui->labelPointName7->setVisible(false);
        ui->labelPointName8->setVisible(false);
    }else if(inum == 7)
    {
        ui->labelPoint8->setVisible(false);
        ui->labelPointName8->setVisible(false);
    }

}

void AreaSelectDialog::SetLabelXY()
{
    int ix,iy;

    ix = ui->labelPicOsd->GetPolyGonPoint(0).x();
    iy = ui->labelPicOsd->GetPolyGonPoint(0).y();
    ui->labelPoint1->setText(GetStrXY(ix,iy));

    ix = ui->labelPicOsd->GetPolyGonPoint(1).x();
    iy = ui->labelPicOsd->GetPolyGonPoint(1).y();
    ui->labelPoint2->setText(GetStrXY(ix,iy));

    ix = ui->labelPicOsd->GetPolyGonPoint(2).x();
    iy = ui->labelPicOsd->GetPolyGonPoint(2).y();
    ui->labelPoint3->setText(GetStrXY(ix,iy));

    ix = ui->labelPicOsd->GetPolyGonPoint(3).x();
    iy = ui->labelPicOsd->GetPolyGonPoint(3).y();
    ui->labelPoint4->setText(GetStrXY(ix,iy));

    ix = ui->labelPicOsd->GetPolyGonPoint(4).x();
    iy = ui->labelPicOsd->GetPolyGonPoint(4).y();
    ui->labelPoint5->setText(GetStrXY(ix,iy));

    ix = ui->labelPicOsd->GetPolyGonPoint(5).x();
    iy = ui->labelPicOsd->GetPolyGonPoint(5).y();
    ui->labelPoint6->setText(GetStrXY(ix,iy));

    ix = ui->labelPicOsd->GetPolyGonPoint(6).x();
    iy = ui->labelPicOsd->GetPolyGonPoint(6).y();
    ui->labelPoint7->setText(GetStrXY(ix,iy));

    ix = ui->labelPicOsd->GetPolyGonPoint(7).x();
    iy = ui->labelPicOsd->GetPolyGonPoint(7).y();
    ui->labelPoint8->setText(GetStrXY(ix,iy));
}

void AreaSelectDialog::on_btnAddRadiusOut_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(btnAddRadiusOut()));
    m_iPresstimes =0;
    btnAddRadiusOut();
    timerUpData->start(100);
}

void AreaSelectDialog::on_btnAddRadiusOut_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(btnAddRadiusOut()));
    m_iPresstimes =0;
}

void AreaSelectDialog::on_btnSubRadiusOut_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(btnSubRadiusOut()));
    m_iPresstimes =0;
    btnSubRadiusOut();
    timerUpData->start(100);
}

void AreaSelectDialog::on_btnSubRadiusOut_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(btnSubRadiusOut()));
    m_iPresstimes =0;
}

void AreaSelectDialog::on_btnAddRadiusIn_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(btnAddRadiusIn()));
    m_iPresstimes =0;
    btnAddRadiusIn();
    timerUpData->start(100);
}
void AreaSelectDialog::on_btnAddRadiusIn_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(btnAddRadiusIn()));
    m_iPresstimes =0;
}
void AreaSelectDialog::on_btnSubRadiusIn_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(btnSubRadiusIn()));
    m_iPresstimes =0;
    btnSubRadiusIn();
    timerUpData->start(100);
}
void AreaSelectDialog::on_btnSubRadiusIn_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(btnSubRadiusIn()));
    m_iPresstimes =0;
}

void AreaSelectDialog::on_btnCircleUPOut_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(btnCircleUPOut()));
    m_iPresstimes =0;
    btnCircleUPOut();
    timerUpData->start(100);
}

void AreaSelectDialog::on_btnCircleUPOut_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(btnCircleUPOut()));
    m_iPresstimes =0;
}

void AreaSelectDialog::on_btnCircleRightOut_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(btnCircleRightOut()));
    m_iPresstimes =0;
    btnCircleRightOut();
    timerUpData->start(100);
}

void AreaSelectDialog::on_btnCircleRightOut_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(btnCircleRightOut()));
    m_iPresstimes =0;
}

void AreaSelectDialog::on_btnCircleDownOut_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(btnCircleDownOut()));
    m_iPresstimes =0;
    btnCircleDownOut();
    timerUpData->start(100);
}

void AreaSelectDialog::on_btnCircleDownOut_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(btnCircleDownOut()));
    m_iPresstimes =0;
}

void AreaSelectDialog::on_btnCircleLeftOut_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(btnCircleLeftOut()));
    m_iPresstimes =0;
    btnCircleLeftOut();
    timerUpData->start(100);
}

void AreaSelectDialog::on_btnCircleLeftOut_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(btnCircleLeftOut()));
    m_iPresstimes =0;
}

void AreaSelectDialog::on_btnPolygonLeft_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(btnPolygonLeft()));
    m_iPresstimes =0;
    btnPolygonLeft();
    timerUpData->start(100);
}

void AreaSelectDialog::on_btnPolygonLeft_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(btnPolygonLeft()));
    m_iPresstimes =0;
}

void AreaSelectDialog::on_btnPolygonUp_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(btnPolygonUp()));
    m_iPresstimes =0;
    btnPolygonUp();
    timerUpData->start(100);

}

void AreaSelectDialog::on_btnPolygonUp_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(btnPolygonUp()));
    m_iPresstimes =0;
}
void AreaSelectDialog::on_btnPolygonRight_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(btnPolygonRight()));
    m_iPresstimes =0;
    btnPolygonRight();
    timerUpData->start(100);
}

void AreaSelectDialog::on_btnPolygonRight_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(btnPolygonRight()));
    m_iPresstimes =0;
}

void AreaSelectDialog::on_btnPolygonDown_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(btnPolygonDown()));
    m_iPresstimes =0;
    btnPolygonDown();
    timerUpData->start(100);
}

void AreaSelectDialog::on_btnPolygonDown_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(btnPolygonDown()));
    m_iPresstimes =0;
}
void AreaSelectDialog::on_btnOrNot_clicked()
{
    int row = ui->tableWidgetTool->currentRow();

    if(row >= 0)
    {
//        int indexRow = FindToolIndex(row);

        bool bflag = false;
        if(m_vt_tool_kind[row] == RINGTOOL)
        {
            bflag = ui->labelPicOsd->GetRingOrNot();
            ui->labelPicOsd->SetRingOrNot(!bflag);

        }else if(m_vt_tool_kind[row] == POLYGONTOOL)
        {
            bflag = ui->labelPicOsd->GetPolygonOrNot();
            ui->labelPicOsd->SetPolygonOrNot(!bflag);
        }else if(m_vt_tool_kind[row] == RECTTOOL)
        {
            bflag = ui->labelPicOsd->GetRectOrNot();
            ui->labelPicOsd->SetRectOrNot(!bflag);
        }

        row = ui->tableWidgetTool->currentRow();
        if(row >= 0)
        {
            ListOsdAdjustWidget(m_vt_tool_kind[row]);

        }else
        {
            ListOsdAdjustWidget(OTHERS);
        }
    }
}
void AreaSelectDialog::IniData()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
        return;
    ui->labelPicOsd->SetPen(pen);
    SELECT_MODEL_CFG cfg;
    cfg = ptr->image_acce_param.select_model_cfg;
    m_select_model_cfg = ptr->image_acce_param.select_model_cfg;
    ui->stackedWidget->setCurrentIndex(4);

    if(cfg.mono_pic_wr_en == 1)
    {
        ui->radioButtonGray->setChecked(true);
        ui->radioButtonColor->setChecked(false);
    }
    if(cfg.color_pic_wr_en == 1)
    {
        ui->radioButtonGray->setChecked(false);
        ui->radioButtonColor->setChecked(true);
    }

    int iRingCount = 0;
    int iPoloygonCount = 0;
    int iEnbale = 0;
    int x,y,rIn,rOut;
    unsigned char rings_en;
    unsigned char rings_inv_en;

    for(int i=0; i< 8;i++)
    {
        if(cfg.select_model[i] == OCTAGON_TYPE)
        {
            if(iPoloygonCount == 0)
            {
                iEnbale = cfg.octagons_cfg[0].octagon_inv_flag;
                IniPolygon(cfg.octagons_cfg[0].octagon_vertex_en,iEnbale,(void*)cfg.octagons_cfg[0].octagon_vertexs);

            }else if(iPoloygonCount == 1)
            {
                iEnbale = cfg.octagons_cfg[1].octagon_inv_flag;
                IniPolygon(cfg.octagons_cfg[1].octagon_vertex_en,iEnbale,(void*)cfg.octagons_cfg[1].octagon_vertexs);
            }else if(iPoloygonCount == 2)
            {
                iEnbale = cfg.octagons_cfg[2].octagon_inv_flag;
                IniPolygon(cfg.octagons_cfg[2].octagon_vertex_en,iEnbale,(void*)cfg.octagons_cfg[2].octagon_vertexs);

            }else if(iPoloygonCount == 3)
            {
                iEnbale = cfg.octagons_cfg[3].octagon_inv_flag;
                IniPolygon(cfg.octagons_cfg[3].octagon_vertex_en,iEnbale,(void*)cfg.octagons_cfg[3].octagon_vertexs);
            }

            iPoloygonCount++;

        }else if(cfg.select_model[i] == RECT_TYPE)
        {
            if(iPoloygonCount == 0)
            {
                iEnbale = cfg.octagons_cfg[0].octagon_inv_flag;
                AddToolTableData(tr("矩形"),RECTTOOL);
                ui->labelPicOsd->IniRectPoint(cfg.octagons_cfg[0].octagon_vertexs[0].vertex_x / m_image_scale, \
                                              cfg.octagons_cfg[0].octagon_vertexs[0].vertex_y / m_image_scale, \
                                              cfg.octagons_cfg[0].octagon_vertexs[2].vertex_x / m_image_scale, \
                                              cfg.octagons_cfg[0].octagon_vertexs[2].vertex_y / m_image_scale,
                                              iEnbale);

            }else if(iPoloygonCount == 1)
            {
                iEnbale = cfg.octagons_cfg[1].octagon_inv_flag;
                AddToolTableData(tr("矩形"),RECTTOOL);

                ui->labelPicOsd->IniRectPoint(cfg.octagons_cfg[1].octagon_vertexs[0].vertex_x / m_image_scale, \
                                              cfg.octagons_cfg[1].octagon_vertexs[0].vertex_y / m_image_scale, \
                                              cfg.octagons_cfg[1].octagon_vertexs[2].vertex_x / m_image_scale, \
                                              cfg.octagons_cfg[1].octagon_vertexs[2].vertex_y / m_image_scale,
                                              iEnbale);

            }else if(iPoloygonCount == 2)
            {
                iEnbale = cfg.octagons_cfg[2].octagon_inv_flag;
                AddToolTableData(tr("矩形"),RECTTOOL);
                ui->labelPicOsd->IniRectPoint(cfg.octagons_cfg[2].octagon_vertexs[0].vertex_x / m_image_scale, \
                                              cfg.octagons_cfg[2].octagon_vertexs[0].vertex_y / m_image_scale, \
                                              cfg.octagons_cfg[2].octagon_vertexs[2].vertex_x / m_image_scale, \
                                              cfg.octagons_cfg[2].octagon_vertexs[2].vertex_y / m_image_scale,
                                              iEnbale);

            }else if(iPoloygonCount == 3)
            {
                iEnbale = cfg.octagons_cfg[3].octagon_inv_flag;
                AddToolTableData(tr("矩形"),RECTTOOL);
                ui->labelPicOsd->IniRectPoint(cfg.octagons_cfg[3].octagon_vertexs[0].vertex_x / m_image_scale, \
                                              cfg.octagons_cfg[3].octagon_vertexs[0].vertex_y / m_image_scale, \
                                              cfg.octagons_cfg[3].octagon_vertexs[2].vertex_x / m_image_scale, \
                                              cfg.octagons_cfg[3].octagon_vertexs[2].vertex_y / m_image_scale,
                                              iEnbale);
            }

            iPoloygonCount++;
            m_i_poloygon_num++;
            //ui->labelPicOsd->IniPolygonPoint(i,value,pointArr[i].vertex_x, pointArr[i].vertex_y,ibEnable);
        }
        else if(cfg.select_model[i] == RING_TYPE)
        {
            if(iRingCount == 0)
            {
                rings_en = cfg.ring_cfg[0].ring_en_flag;
                rings_inv_en = cfg.ring_cfg[0].ring_inv_flag;
                x =cfg.ring_cfg[0].ring.center_x / m_image_scale;
                y =cfg.ring_cfg[0].ring.center_y / m_image_scale;
                rIn = sqrt(cfg.ring_cfg[0].ring.inner_radius_square) / m_image_scale;
                rOut = sqrt(cfg.ring_cfg[0].ring.outer_radius_square) / m_image_scale;
                if(rings_en)
                {
                    IniCircleData((int)rings_inv_en,rOut,rIn,x,y);
                }

            }else if(iRingCount == 1)
            {
                rings_en = cfg.ring_cfg[1].ring_en_flag;
                rings_inv_en = cfg.ring_cfg[1].ring_inv_flag;
                x =cfg.ring_cfg[1].ring.center_x / m_image_scale;
                y =cfg.ring_cfg[1].ring.center_y / m_image_scale;

                rIn = sqrt(cfg.ring_cfg[1].ring.inner_radius_square) / m_image_scale;
                rOut = sqrt(cfg.ring_cfg[1].ring.outer_radius_square) / m_image_scale;
                if(rings_en)
                {
                    IniCircleData((int)rings_inv_en,rOut,rIn,x,y);
                }

            }else if(iRingCount == 2)
            {
                rings_en = cfg.ring_cfg[2].ring_en_flag;
                rings_inv_en = cfg.ring_cfg[2].ring_inv_flag;
                x =cfg.ring_cfg[2].ring.center_x / m_image_scale;
                y =cfg.ring_cfg[2].ring.center_y / m_image_scale;

                rIn = sqrt(cfg.ring_cfg[2].ring.inner_radius_square) / m_image_scale;
                rOut = sqrt(cfg.ring_cfg[2].ring.outer_radius_square) / m_image_scale;
                if(rings_en)
                {
                    IniCircleData((int)rings_inv_en,rOut,rIn,x,y);
                }

            }else if(iRingCount == 3)
            {
                rings_en = cfg.ring_cfg[3].ring_en_flag;
                rings_inv_en = cfg.ring_cfg[3].ring_inv_flag;
                x =cfg.ring_cfg[3].ring.center_x / m_image_scale;
                y =cfg.ring_cfg[3].ring.center_y / m_image_scale;

                rIn = sqrt(cfg.ring_cfg[3].ring.inner_radius_square) / m_image_scale;
                rOut = sqrt(cfg.ring_cfg[3].ring.outer_radius_square) / m_image_scale;
                if(rings_en)
                {
                    IniCircleData((int)rings_inv_en,rOut,rIn,x,y);
                }
            }
            iRingCount++;
        }
    }

    int row = ui->tableWidgetTool->rowCount()-1;

    if(row >=0)
    {
        int indexRow = FindToolIndex(row);
        ui->labelPicOsd->SelectTool(m_vt_tool_kind[row],indexRow);
        ListOsdAdjustWidget(m_vt_tool_kind[row]);
    }

    if(cfg.select_src_sel == ACCE_COLOR_EXTRACT_MODLE_ID)
    {
        ptr->image_acce_param.select_model_cfg.mono_pic_wr_en = 0;
        ptr->image_acce_param.select_model_cfg.color_pic_wr_en =1;

    }else
    {
        ptr->image_acce_param.select_model_cfg.mono_pic_wr_en = 1;
        ptr->image_acce_param.select_model_cfg.color_pic_wr_en =0;

    }
    ui->radioButtonGray->setChecked(false);
    ui->radioButtonColor->setChecked(true);

    //ptr->image_acce_param.select_model_cfg.select_src_sel= 17;
    qDebug()<<"select_src_sel=="<<ptr->image_acce_param.select_model_cfg.select_src_sel;
    ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ptr->image_acce_param.select_model_cfg.select_src_sel;
    AcceleratorModuleConfig(ACCE_AREA_SELECT_MODEL_ID,m_step);
    AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
    UtilitiesFun::Instance()->ListVGA(ui->labelPicOsd->x(),ui->labelPicOsd->y(),ACCE_AREA_SELECT_MODEL_ID);
    qDebug()<<"AreaSelectDialog::IniData() end";
}
void AreaSelectDialog::IniCircleData(int ibEnable,int rOut,int rIn,int x, int y)
{
    m_i_circle_num++;
    AddToolTableData(tr("Ring"),RINGTOOL);
    ui->labelPicOsd->SetRingCenter(x,y);
    ui->labelPicOsd->SetRingRIn(rIn);
    ui->labelPicOsd->SetRingROut(rOut);
    ui->labelPicOsd->SetRingOrNot(ibEnable);

}
void AreaSelectDialog::IniPolygon(unsigned char value,int ibEnable,void *p_point_arr)
{
    if(value == THREEPOLYGON_BITMAP)
    {
        m_i_poloygon_num++;
        AddToolTableData(tr("Polygon"),POLYGONTOOL);
        IniPolygonOsdPoint(3,p_point_arr,ibEnable);

    }else if(value == FOURPOLYGON_BITMAP)
    {
        m_i_poloygon_num++;
        AddToolTableData(tr("Polygon"),POLYGONTOOL);
        IniPolygonOsdPoint(4,p_point_arr,ibEnable);
    }else if(value == FIVEPOLYGON_BITMAP)
    {
        m_i_poloygon_num++;
        AddToolTableData(tr("Polygon"),POLYGONTOOL);
        IniPolygonOsdPoint(5,p_point_arr,ibEnable);

    }else if(value == SIXPOLYGON_BITMAP)
    {
        m_i_poloygon_num++;
        AddToolTableData(tr("Polygon"),POLYGONTOOL);
        IniPolygonOsdPoint(6,p_point_arr,ibEnable);

    }else if(value == SEVENPOLYGON_BITMAP)
    {
        m_i_poloygon_num++;
        AddToolTableData(tr("Polygon"),POLYGONTOOL);
        IniPolygonOsdPoint(7,p_point_arr,ibEnable);

    }else if(value == EIGHTPOLYGON_BITMAP)
    {
        m_i_poloygon_num++;
        AddToolTableData(tr("Polygon"),POLYGONTOOL);
        IniPolygonOsdPoint(8,p_point_arr,ibEnable);
    }

}
void AreaSelectDialog::IniPolygonOsdPoint(int value,void *p_point_arr,int ibEnable)
{

    VERTEX_POINT *pointArr = (VERTEX_POINT *)p_point_arr;
    for(int i=0; i< 8;i++)
    {
        if(i==value)
            break;

        ui->labelPicOsd->IniPolygonPoint(i,value,pointArr[i].vertex_x/m_image_scale, pointArr[i].vertex_y/m_image_scale,ibEnable);

    }
}
void AreaSelectDialog::ClearOsdData()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    memset(ptr->image_acce_param.select_model_cfg.select_model,0,sizeof(ptr->image_acce_param.select_model_cfg.select_model));
    memset(ptr->image_acce_param.select_model_cfg.ring_cfg,0,sizeof(ptr->image_acce_param.select_model_cfg.ring_cfg));
    memset(ptr->image_acce_param.select_model_cfg.octagons_cfg,0,sizeof(ptr->image_acce_param.select_model_cfg.octagons_cfg));
}
void AreaSelectDialog::SetDataToLib()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
         return;
    ClearOsdData();
    int count = m_vt_tool_kind.count();
    int iRingCount = 0;
    int iPolygonCount = 0;
    int j,i;
    unsigned char uEnabel = 0;
    unsigned char uoctagons_inv_en = 0;

    for(i = 0; i< count;i++)
    {
         //Area[i].osd_type = m_vt_tool_kind[i];

         int indexRow = FindToolIndex(i);
         ui->labelPicOsd->SelectTool(m_vt_tool_kind[i],indexRow);
         if(m_vt_tool_kind[i] == RINGTOOL)
         {
             ptr->image_acce_param.select_model_cfg.select_model[i] = RING_TYPE;
             iRingCount++;
             if(iRingCount == 1)
             {
                if(ui->labelPicOsd->GetRingOrNot() == 1)
                    uEnabel = 1;
                else
                    uEnabel = 0;
                ptr->image_acce_param.select_model_cfg.ring_cfg[0].ring_en_flag = 1;
                ptr->image_acce_param.select_model_cfg.ring_cfg[0].ring_inv_flag = uEnabel;
                ptr->image_acce_param.select_model_cfg.ring_cfg[0].ring.center_x = ui->labelPicOsd->GetRingCenter().x() * m_image_scale;
                ptr->image_acce_param.select_model_cfg.ring_cfg[0].ring.center_y= ui->labelPicOsd->GetRingCenter().y() * m_image_scale;
                ptr->image_acce_param.select_model_cfg.ring_cfg[0].ring.inner_radius_square = ui->labelPicOsd->GetRingRIn()*ui->labelPicOsd->GetRingRIn() * m_image_scale;
                ptr->image_acce_param.select_model_cfg.ring_cfg[0].ring.outer_radius_square = ui->labelPicOsd->GetRingROut()*ui->labelPicOsd->GetRingROut() * m_image_scale;
                qDebug()<<"m_image_scale==="<<m_image_scale;
                qDebug()<<"rin=="<<ui->labelPicOsd->GetRingRIn()<<"rout==="<<ui->labelPicOsd->GetRingROut();
             }else if(iRingCount == 2)
             {
                if(ui->labelPicOsd->GetRingOrNot() == 1)
                    uEnabel = 1;
                else
                    uEnabel = 0;

                ptr->image_acce_param.select_model_cfg.ring_cfg[1].ring_en_flag = 1;
                ptr->image_acce_param.select_model_cfg.ring_cfg[1].ring_inv_flag = uEnabel;
                ptr->image_acce_param.select_model_cfg.ring_cfg[1].ring.center_x = ui->labelPicOsd->GetRingCenter().x() * m_image_scale;
                ptr->image_acce_param.select_model_cfg.ring_cfg[1].ring.center_y= ui->labelPicOsd->GetRingCenter().y() * m_image_scale;
                ptr->image_acce_param.select_model_cfg.ring_cfg[1].ring.inner_radius_square = ui->labelPicOsd->GetRingRIn()*ui->labelPicOsd->GetRingRIn() * m_image_scale;
                ptr->image_acce_param.select_model_cfg.ring_cfg[1].ring.outer_radius_square = ui->labelPicOsd->GetRingROut()*ui->labelPicOsd->GetRingROut() * m_image_scale;

             }else if(iRingCount == 3)
             {
                if(ui->labelPicOsd->GetRingOrNot() == 1)
                    uEnabel = 1;
                else
                    uEnabel = 0;

                ptr->image_acce_param.select_model_cfg.ring_cfg[2].ring_en_flag = 1;
                ptr->image_acce_param.select_model_cfg.ring_cfg[2].ring_inv_flag = uEnabel;
                ptr->image_acce_param.select_model_cfg.ring_cfg[2].ring.center_x = ui->labelPicOsd->GetRingCenter().x() * m_image_scale;
                ptr->image_acce_param.select_model_cfg.ring_cfg[2].ring.center_y= ui->labelPicOsd->GetRingCenter().y() * m_image_scale;
                ptr->image_acce_param.select_model_cfg.ring_cfg[2].ring.inner_radius_square = ui->labelPicOsd->GetRingRIn()*ui->labelPicOsd->GetRingRIn() * m_image_scale;
                ptr->image_acce_param.select_model_cfg.ring_cfg[2].ring.outer_radius_square = ui->labelPicOsd->GetRingROut()*ui->labelPicOsd->GetRingROut() * m_image_scale;

             }else if(iRingCount == 4)
             {
                 if(ui->labelPicOsd->GetRingOrNot() == 1)
                     uEnabel = 1;
                 else
                     uEnabel = 0;

                 ptr->image_acce_param.select_model_cfg.ring_cfg[3].ring_en_flag = 1;
                 ptr->image_acce_param.select_model_cfg.ring_cfg[3].ring_inv_flag = uEnabel;
                 ptr->image_acce_param.select_model_cfg.ring_cfg[3].ring.center_x = ui->labelPicOsd->GetRingCenter().x() * m_image_scale;
                 ptr->image_acce_param.select_model_cfg.ring_cfg[3].ring.center_y= ui->labelPicOsd->GetRingCenter().y() * m_image_scale;
                 ptr->image_acce_param.select_model_cfg.ring_cfg[3].ring.inner_radius_square = ui->labelPicOsd->GetRingRIn()*ui->labelPicOsd->GetRingRIn() * m_image_scale;
                 ptr->image_acce_param.select_model_cfg.ring_cfg[3].ring.outer_radius_square = ui->labelPicOsd->GetRingROut()*ui->labelPicOsd->GetRingROut() * m_image_scale;
             }
         }
         else if(m_vt_tool_kind[i] == POLYGONTOOL)
         {
            iPolygonCount++;
            ptr->image_acce_param.select_model_cfg.select_model[i] = OCTAGON_TYPE;
            int pointNum = ui->labelPicOsd->GetPolygonPointNum();;

            if(iPolygonCount == 1)
            {
                ptr->image_acce_param.select_model_cfg.octagons_cfg[0].octagon_vertex_en = GetOctagonVertexEn(pointNum);

                if(ui->labelPicOsd->GetPolygonOrNot() == 1)
                    uoctagons_inv_en = 1;
                else
                    uoctagons_inv_en = 0;

                ptr->image_acce_param.select_model_cfg.octagons_cfg[0].octagon_inv_flag = uoctagons_inv_en;
                for(j = 0; j<8;j++)
                {
                    if(j<pointNum)
                    {
                        ptr->image_acce_param.select_model_cfg.octagons_cfg[0].octagon_vertexs[j].vertex_x = ui->labelPicOsd->GetPolyGonPoint(j).x() * m_image_scale;
                        ptr->image_acce_param.select_model_cfg.octagons_cfg[0].octagon_vertexs[j].vertex_y = ui->labelPicOsd->GetPolyGonPoint(j).y() * m_image_scale;
                    }else
                    {
                        ptr->image_acce_param.select_model_cfg.octagons_cfg[0].octagon_vertexs[j].vertex_x = ui->labelPicOsd->GetPolyGonPoint(0).x() * m_image_scale;
                        ptr->image_acce_param.select_model_cfg.octagons_cfg[0].octagon_vertexs[j].vertex_y = ui->labelPicOsd->GetPolyGonPoint(0).y() * m_image_scale;
                    }


                }
            }else if(iPolygonCount == 2)
            {
                ptr->image_acce_param.select_model_cfg.octagons_cfg[1].octagon_vertex_en = GetOctagonVertexEn(pointNum);
                if(ui->labelPicOsd->GetPolygonOrNot() == 1)
                    uoctagons_inv_en = 1;
                else
                    uoctagons_inv_en = 0;
                ptr->image_acce_param.select_model_cfg.octagons_cfg[1].octagon_inv_flag = uoctagons_inv_en;
                for(j = 0; j<8;j++)
                {
                    if(j<pointNum)
                    {
                        ptr->image_acce_param.select_model_cfg.octagons_cfg[1].octagon_vertexs[j].vertex_x = ui->labelPicOsd->GetPolyGonPoint(j).x() * m_image_scale;
                        ptr->image_acce_param.select_model_cfg.octagons_cfg[1].octagon_vertexs[j].vertex_y = ui->labelPicOsd->GetPolyGonPoint(j).y() * m_image_scale;
                    }else
                    {
                        ptr->image_acce_param.select_model_cfg.octagons_cfg[1].octagon_vertexs[j].vertex_x = ui->labelPicOsd->GetPolyGonPoint(0).x() * m_image_scale;
                        ptr->image_acce_param.select_model_cfg.octagons_cfg[1].octagon_vertexs[j].vertex_y = ui->labelPicOsd->GetPolyGonPoint(0).y() * m_image_scale;
                    }


                }

            }else if(iPolygonCount == 3)
            {
                ptr->image_acce_param.select_model_cfg.octagons_cfg[2].octagon_vertex_en = GetOctagonVertexEn(pointNum);

                if(ui->labelPicOsd->GetPolygonOrNot() == 1)
                    uoctagons_inv_en = 1;
                else
                    uoctagons_inv_en = 0;
                ptr->image_acce_param.select_model_cfg.octagons_cfg[2].octagon_inv_flag = uoctagons_inv_en;
                for(j = 0; j<8;j++)
                {
                    if(j<pointNum)
                    {
                        ptr->image_acce_param.select_model_cfg.octagons_cfg[2].octagon_vertexs[j].vertex_x = ui->labelPicOsd->GetPolyGonPoint(j).x() * m_image_scale;
                        ptr->image_acce_param.select_model_cfg.octagons_cfg[2].octagon_vertexs[j].vertex_y = ui->labelPicOsd->GetPolyGonPoint(j).y() * m_image_scale;
                    }else
                    {
                        ptr->image_acce_param.select_model_cfg.octagons_cfg[2].octagon_vertexs[j].vertex_x = ui->labelPicOsd->GetPolyGonPoint(0).x() * m_image_scale;
                        ptr->image_acce_param.select_model_cfg.octagons_cfg[2].octagon_vertexs[j].vertex_y = ui->labelPicOsd->GetPolyGonPoint(0).y() * m_image_scale;
                    }


                }

            }else if(iPolygonCount == 4)
            {
                ptr->image_acce_param.select_model_cfg.octagons_cfg[3].octagon_vertex_en = GetOctagonVertexEn(pointNum);
                if(ui->labelPicOsd->GetPolygonOrNot() == 1)
                    uoctagons_inv_en = 1;
                else
                    uoctagons_inv_en = 0;
                ptr->image_acce_param.select_model_cfg.octagons_cfg[3].octagon_inv_flag = uoctagons_inv_en;
                for(j = 0; j<8;j++)
                {
                    if(j<pointNum)
                    {
                        ptr->image_acce_param.select_model_cfg.octagons_cfg[3].octagon_vertexs[j].vertex_x = ui->labelPicOsd->GetPolyGonPoint(j).x() * m_image_scale;
                        ptr->image_acce_param.select_model_cfg.octagons_cfg[3].octagon_vertexs[j].vertex_y = ui->labelPicOsd->GetPolyGonPoint(j).y() * m_image_scale;
                    }else
                    {
                        ptr->image_acce_param.select_model_cfg.octagons_cfg[3].octagon_vertexs[j].vertex_x = ui->labelPicOsd->GetPolyGonPoint(0).x() * m_image_scale;
                        ptr->image_acce_param.select_model_cfg.octagons_cfg[3].octagon_vertexs[j].vertex_y = ui->labelPicOsd->GetPolyGonPoint(0).y() * m_image_scale;
                    }


                }
            }
         }else if(m_vt_tool_kind[i] == RECTTOOL)
         {
             iPolygonCount++;
             ptr->image_acce_param.select_model_cfg.select_model[i] = RECT_TYPE;
             int pointNum = 4;
             if(iPolygonCount == 1)
             {
                 ptr->image_acce_param.select_model_cfg.octagons_cfg[0].octagon_vertex_en = GetOctagonVertexEn(pointNum);

                 if(ui->labelPicOsd->GetRectOrNot() == 1)
                     uoctagons_inv_en = 1;
                 else
                     uoctagons_inv_en = 0;

                 ptr->image_acce_param.select_model_cfg.octagons_cfg[0].octagon_inv_flag = uoctagons_inv_en;
                 for(j = 0; j<8;j++)
                 {
                     if(j<pointNum)
                     {
                         ptr->image_acce_param.select_model_cfg.octagons_cfg[0].octagon_vertexs[j].vertex_x = ui->labelPicOsd->GetRectPoint(j).x() * m_image_scale;
                         ptr->image_acce_param.select_model_cfg.octagons_cfg[0].octagon_vertexs[j].vertex_y = ui->labelPicOsd->GetRectPoint(j).y() * m_image_scale;
                     }else
                     {
                         ptr->image_acce_param.select_model_cfg.octagons_cfg[0].octagon_vertexs[j].vertex_x = ui->labelPicOsd->GetRectPoint(0).x() * m_image_scale;
                         ptr->image_acce_param.select_model_cfg.octagons_cfg[0].octagon_vertexs[j].vertex_y = ui->labelPicOsd->GetRectPoint(0).y() * m_image_scale;
                     }


                 }
             }else if(iPolygonCount == 2)
             {
                 ptr->image_acce_param.select_model_cfg.octagons_cfg[1].octagon_vertex_en = GetOctagonVertexEn(pointNum);
                 if(ui->labelPicOsd->GetRectOrNot() == 1)
                     uoctagons_inv_en = 1;
                 else
                     uoctagons_inv_en = 0;
                 ptr->image_acce_param.select_model_cfg.octagons_cfg[1].octagon_inv_flag = uoctagons_inv_en;
                 for(j = 0; j<8;j++)
                 {
                     if(j<pointNum)
                     {
                         ptr->image_acce_param.select_model_cfg.octagons_cfg[1].octagon_vertexs[j].vertex_x = ui->labelPicOsd->GetRectPoint(j).x() * m_image_scale;
                         ptr->image_acce_param.select_model_cfg.octagons_cfg[1].octagon_vertexs[j].vertex_y = ui->labelPicOsd->GetRectPoint(j).y() * m_image_scale;
                     }else
                     {
                         ptr->image_acce_param.select_model_cfg.octagons_cfg[1].octagon_vertexs[j].vertex_x = ui->labelPicOsd->GetRectPoint(0).x() * m_image_scale;
                         ptr->image_acce_param.select_model_cfg.octagons_cfg[1].octagon_vertexs[j].vertex_y = ui->labelPicOsd->GetRectPoint(0).y() * m_image_scale;
                     }
                 }

             }else if(iPolygonCount == 3)
             {
                 ptr->image_acce_param.select_model_cfg.octagons_cfg[2].octagon_vertex_en = GetOctagonVertexEn(pointNum);

                 if(ui->labelPicOsd->GetRectOrNot() == 1)
                     uoctagons_inv_en = 1;
                 else
                     uoctagons_inv_en = 0;
                 ptr->image_acce_param.select_model_cfg.octagons_cfg[2].octagon_inv_flag = uoctagons_inv_en;
                 for(j = 0; j<8;j++)
                 {
                     if(j<pointNum)
                     {
                         ptr->image_acce_param.select_model_cfg.octagons_cfg[2].octagon_vertexs[j].vertex_x = ui->labelPicOsd->GetRectPoint(j).x() * m_image_scale;
                         ptr->image_acce_param.select_model_cfg.octagons_cfg[2].octagon_vertexs[j].vertex_y = ui->labelPicOsd->GetRectPoint(j).y() * m_image_scale;
                     }else
                     {
                         ptr->image_acce_param.select_model_cfg.octagons_cfg[2].octagon_vertexs[j].vertex_x = ui->labelPicOsd->GetRectPoint(0).x() * m_image_scale;
                         ptr->image_acce_param.select_model_cfg.octagons_cfg[2].octagon_vertexs[j].vertex_y = ui->labelPicOsd->GetRectPoint(0).y() * m_image_scale;
                     }


                 }

             }else if(iPolygonCount == 4)
             {
                 ptr->image_acce_param.select_model_cfg.octagons_cfg[3].octagon_vertex_en = GetOctagonVertexEn(pointNum);
                 if(ui->labelPicOsd->GetRectOrNot() == 1)
                     uoctagons_inv_en = 1;
                 else
                     uoctagons_inv_en = 0;
                 ptr->image_acce_param.select_model_cfg.octagons_cfg[3].octagon_inv_flag = uoctagons_inv_en;

                 for(j = 0; j<8;j++)
                 {
                     if(j<pointNum)
                     {
                         ptr->image_acce_param.select_model_cfg.octagons_cfg[3].octagon_vertexs[j].vertex_x = ui->labelPicOsd->GetRectPoint(j).x() * m_image_scale;
                         ptr->image_acce_param.select_model_cfg.octagons_cfg[3].octagon_vertexs[j].vertex_y = ui->labelPicOsd->GetRectPoint(j).y() * m_image_scale;

                     }else
                     {
                         ptr->image_acce_param.select_model_cfg.octagons_cfg[3].octagon_vertexs[j].vertex_x = ui->labelPicOsd->GetRectPoint(0).x() * m_image_scale;
                         ptr->image_acce_param.select_model_cfg.octagons_cfg[3].octagon_vertexs[j].vertex_y = ui->labelPicOsd->GetRectPoint(0).y() * m_image_scale;
                     }


                 }
             }
         }
    }
    //ptr->image_acce_param.select_model_cfg.mono_pic_wr_en = 0;
    //ptr->image_acce_param.select_model_cfg.color_pic_wr_en =0;
    AcceleratorModuleConfig(ACCE_AREA_SELECT_MODEL_ID,m_step);

}
//八边形顶点使能参数
int AreaSelectDialog::GetOctagonVertexEn(int num)
{
    int ret = 0;
    //3边形
    if(num == THREEPOLYGON)
    {
        ret = 7;

    }else if(num == FOURPOLYGON)
    {
        ret = 15;
    }
    else if(num == FIVEPOLYGON)
    {
       ret = 31;
    }
    else if(num == SIXPOLYGON)
    {
       ret = 63;

    }else if(num == SEVENPOLYGON)
    {
       ret = 127;

    }else if(num == EIGHTPOLYGON)
    {

       ret = 255;

    }else
    {
       ret = 0;
    }
    return ret;
}
void AreaSelectDialog::updatImage(QPixmap pix)
{
    ui->labelPicOsd->setPixmap(pix);
}
void AreaSelectDialog::on_btnRectUp_clicked()
{
    if(this->m_iPresstimes >0 && m_iPresstimes<8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int value =1;
    if(ui->radioButtonRectLefttop->isChecked())
    {
        ui->labelPicOsd->UpRectAdjust(1,value);
    }else
    {
        ui->labelPicOsd->UpRectAdjust(2,value);
    }

}

void AreaSelectDialog::on_btnRectDown_clicked()
{
    if(this->m_iPresstimes >0 && m_iPresstimes<8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int value =1;
    if(ui->radioButtonRectLefttop->isChecked())
    {
        ui->labelPicOsd->DownRectAdjust(1,value);
    }else
    {
        ui->labelPicOsd->DownRectAdjust(2,value);
    }
}

void AreaSelectDialog::on_btnRectLeft_clicked()
{
    if(this->m_iPresstimes >0 && m_iPresstimes<8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int value =1;
    if(ui->radioButtonRectLefttop->isChecked())
    {
        ui->labelPicOsd->LeftRectAdjust(1,value);
    }else
    {
        ui->labelPicOsd->LeftRectAdjust(2,value);
    }
}

void AreaSelectDialog::on_btnRectRight_clicked()
{
    if(this->m_iPresstimes >0 && m_iPresstimes<8)
    {
        m_iPresstimes++;
        return;
    }
    m_iPresstimes++;

    int value =1;
    if(ui->radioButtonRectLefttop->isChecked())
    {
        ui->labelPicOsd->RightRectAdjust(1,value);
    }else
    {
        ui->labelPicOsd->RightRectAdjust(2,value);
    }
}

void AreaSelectDialog::on_btnRectUp_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnRectUp_clicked()));
    m_iPresstimes =0;
    /*int value =1;
    if(ui->radioButtonRectLefttop->isChecked())
    {
        ui->labelPicOsd->UpRectAdjust(1,value);
    }else
    {
        ui->labelPicOsd->UpRectAdjust(2,value);
    }*/
    timerUpData->start(100);
}

void AreaSelectDialog::on_btnRectUp_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnRectUp_clicked()));

}

void AreaSelectDialog::on_btnRectDown_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnRectDown_clicked()));
    m_iPresstimes =0;

    timerUpData->start(100);
}

void AreaSelectDialog::on_btnRectDown_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnRectDown_clicked()));

}

void AreaSelectDialog::on_btnRectLeft_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnRectLeft_clicked()));
    m_iPresstimes =0;
    /*int value =1;
    if(ui->radioButtonRectLefttop->isChecked())
    {
        ui->labelPicOsd->LeftRectAdjust(1,value);
    }else
    {
        ui->labelPicOsd->LeftRectAdjust(2,value);
    }*/
    timerUpData->start(100);
}

void AreaSelectDialog::on_btnRectLeft_released()
{
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnRectLeft_clicked()));

}

void AreaSelectDialog::on_btnRectRight_pressed()
{
    connect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnRectRight_clicked()));
    m_iPresstimes =0;
    /*int value =1;
    if(ui->radioButtonRectLefttop->isChecked())
    {
        ui->labelPicOsd->RightRectAdjust(1,value);
    }else
    {
        ui->labelPicOsd->RightRectAdjust(2,value);
    }*/
    timerUpData->start(100);
}

void AreaSelectDialog::on_btnRectRight_released()
{
    m_iPresstimes =0;
    timerUpData->stop();
    disconnect(timerUpData,SIGNAL(timeout()),this,SLOT(on_btnRectRight_clicked()));

}
