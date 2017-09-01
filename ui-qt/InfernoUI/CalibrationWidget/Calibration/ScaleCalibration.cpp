#include "ScaleCalibration.h"
#include "ui_ScaleCalibration.h"
#include <QMessageBox>
#include <QDebug>
#include "math.h"
#include "ScaleRatio.h"
#include "../Global/UtilitiesFun.h"


ScaleCalibration::ScaleCalibration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScaleCalibration)
{
    ui->setupUi(this);

    qApp->installEventFilter(this);

    m_image_label = new ScaleImageLabel(this);
    m_image_label->setGeometry(10,40,640,480);
    m_image_label->setAutoFillBackground(true);
    QPalette p = m_image_label->palette();
    p.setColor(QPalette::Background,QColor(50,50,50,255));
    m_image_label->setPalette(p);

    m_auto_repeat_count = 0;
    m_self_inc = 1;
    param_index = 0;
    m_edit_ratio_flag = 0;

    connect(m_image_label, &ScaleImageLabel::CurrentPointChangeSignal, \
            this, &ScaleCalibration::CurPointChangedSlot);
    PanelInit();
    UtilitiesFun::Instance()->ListVGA(m_image_label->x(),m_image_label->y());
    UtilitiesFun::Instance()->SetCPT(CPT_CMOS_PIC);
}

ScaleCalibration::~ScaleCalibration()
{
    if(m_image_label != NULL)
    {
        delete m_image_label;
        m_image_label = NULL;
    }
    delete ui;
    qApp->removeEventFilter(this);
}

QString ScaleCalibration::GetRatio()
{
    return ui->lineEditRatio->text();
}

void ScaleCalibration::SetRatio(QString ratio)
{
    ui->lineEditRatio->setText(ratio);
    m_edit_ratio_flag = 2;
}

void ScaleCalibration::SetParamIndex(int paramIndex)
{
    param_index = paramIndex;
    ui->labelTitle->setText("刻度校准 参数"+QString::number(paramIndex+1));
}


bool ScaleCalibration::eventFilter(QObject *watched, QEvent *event)
{
//    QList<QPushButton *> btnMove = this->findChildren<QPushButton *>();
    QList<QPushButton *> btnMove;
    btnMove.append(ui->btnMoveUp);
    btnMove.append(ui->btnMoveDown);
    btnMove.append(ui->btnMoveLeft);
    btnMove.append(ui->btnMoveRight);

    foreach (QPushButton * L, btnMove)
    {
        if ((L->objectName() == watched->objectName()))
        {
            if (event->type() == QEvent::MouseButtonRelease)
            {
                if (!((QKeyEvent *)event)->isAutoRepeat())
                {
                    m_auto_repeat_count = 0;
                    m_self_inc = 1;
                }
            }
        }
    }

    QList<QLineEdit *> lineEidt;
//    lineEidt.append(ui->lineEditPixDist);
    lineEidt.append(ui->lineEditPhyDist);
    lineEidt.append(ui->lineEditRatio);

    QLineEdit *pLineEdit;
    foreach (pLineEdit, lineEidt)
    {
        if (pLineEdit->objectName() == watched->objectName())
        {
            if (event->type()== QEvent::MouseButtonPress)
            {
                QDialog * dlg = m_keyBoardLib.GetNumKeyBoardDialog();
//                dlg.SetNaturalNumberInputMode(true);
                m_keyBoardLib.SetOldNum(((QLineEdit *)watched)->text());
                int ret = dlg->exec();
                if(ret == QDialog::Accepted)
                {
                    ((QLineEdit *)watched)->setText(m_keyBoardLib.GetNum());
                    if (ui->lineEditPhyDist->objectName() == watched->objectName())
                    {
                        double iPhyDis = ui->lineEditPhyDist->text().toDouble();
                        SetScaleRatioPhyDist(iPhyDis);
                        double iScaleRatio;
                        GetScaleRatio(&iScaleRatio);
                        ui->lineEditRatio->setText(QString::number(iScaleRatio,'f', 6));
                    }
                }
            }
        }
    }

    return QWidget::eventFilter(watched, event);
}

//#ifndef EPSINON
//#define EPSINON 0.000001
//#endif
//void ScaleCalibration::CalcRatio()
//{
//    double iPixDist;
//    m_image_label->GetSubPixDist(iPixDist);
//    double iPhyDis = ui->lineEditPhyDist->text().toDouble();

//    if (iPixDist > -EPSINON && iPixDist < EPSINON)
//        return ;

//    double iRatio = iPhyDis/iPixDist;
//    ui->lineEditRatio->setText(QString::number(iRatio,'f',3));
//}

void ScaleCalibration::CurPointChangedSlot(int curIndex, QPoint Point)
{
    double pixDist;
    double scaleRatio;

    if (curIndex == 0)
    {
        ui->radioButtonP1->setChecked(true);
        ui->labelP1Coordinate->setText("("+QString::number(Point.x())+","+QString::number(Point.y())+")");
    }
    else
    {
        ui->radioButtonP2->setChecked(true);
        ui->labelP2Coordinate->setText("("+QString::number(Point.x())+","+QString::number(Point.y())+")");
    }

    SetScaleRatioVgaPoint(curIndex, Point.x(), Point.y());

    GetSubPixDist(&pixDist);
    ui->lineEditPixDist->setText(QString::number(pixDist, 'f', 3));

    GetScaleRatio(&scaleRatio);
    ui->lineEditRatio->setText(QString::number(scaleRatio, 'f', 6));
}


void ScaleCalibration::on_btnQuit_clicked()
{
    QDialog::reject();
}

void ScaleCalibration::on_radioButtonP1_clicked()
{
    m_image_label->SetCurrentPointIndex(0);
}

void ScaleCalibration::on_radioButtonP2_clicked()
{
    m_image_label->SetCurrentPointIndex(1);
}

void ScaleCalibration::SeleIncValuePro()
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

void ScaleCalibration::PanelInit()
{
    double pixDist;
    QPoint Point;

    m_image_label->GetPointByIndex(0, Point);
    ui->radioButtonP1->setChecked(true);
    ui->labelP1Coordinate->setText("("+QString::number(Point.x())+","+QString::number(Point.y())+")");
    SetScaleRatioVgaPoint(0, Point.x(), Point.y());

    m_image_label->GetPointByIndex(1, Point);
    ui->radioButtonP2->setChecked(true);
    ui->labelP2Coordinate->setText("("+QString::number(Point.x())+","+QString::number(Point.y())+")");
    SetScaleRatioVgaPoint(1, Point.x(), Point.y());

    SetScaleRatioPhyDist(0.0);

    GetSubPixDist(&pixDist);
    ui->lineEditPixDist->setText(QString::number(pixDist, 'f', 3));
}

void ScaleCalibration::on_btnMoveUp_clicked()
{
   SeleIncValuePro();
   m_image_label->KeyMoveUp(m_self_inc);
}

void ScaleCalibration::on_btnMoveDown_clicked()
{
    SeleIncValuePro();
    m_image_label->KeyMoveDown(m_self_inc);
}

void ScaleCalibration::on_btnMoveLeft_clicked()
{
    SeleIncValuePro();
    m_image_label->KeyMoveLeft(m_self_inc);
}

void ScaleCalibration::on_btnMoveRight_clicked()
{
    SeleIncValuePro();
    m_image_label->KeyMoveRight(m_self_inc);
}

void ScaleCalibration::on_btnOk_clicked()
{
    double curRatio = ui->lineEditRatio->text().toDouble();
    SaveScaleRatio(param_index, curRatio);
    qDebug() << "index:" << param_index << "ratio:" << curRatio;
    QDialog::accept();
}
