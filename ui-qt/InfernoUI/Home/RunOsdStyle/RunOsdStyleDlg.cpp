#include "RunOsdStyleDlg.h"
#include "ui_RunOsdStyleDlg.h"
#include <QMessageBox>
#include <qdebug.h>
#include "RunOsdStyleItem.h"
#include "Comm/OSDStyle.h"

COLOR_SELECT g_run_color;
RunOsdStyleDlg::RunOsdStyleDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RunOsdStyleDlg)
{
    ui->setupUi(this);
    iniFirst = 0;
    m_label = NULL;

    initCombColor(ui->comboBoxOKColor);
    initCombColor(ui->comboBoxNGColor);
    ui->comboBoxNGColor->setFocus();
    ui->comboBoxNGColor->setCurrentIndex(OSDStyle::pen_color.run_osd.runNG_color);
    ui->comboBoxOKColor->setCurrentIndex(OSDStyle::pen_color.run_osd.runOK_color);
    ui->txtNGWidth->setText(QString::number(OSDStyle::pen_color.run_osd.runNGWidth));
    ui->txtOKWidth->setText(QString::number(OSDStyle::pen_color.run_osd.runOKWidth));
    ui->txtNGWidth->installEventFilter(this);
    ui->txtOKWidth->installEventFilter(this);
    iniFirst = 1;

    this->setGeometry(630,0,this->width(),this->height());
}

RunOsdStyleDlg::~RunOsdStyleDlg()
{
    ui->txtNGWidth->removeEventFilter(this);
    ui->txtOKWidth->removeEventFilter(this);
    disconnect(this,0,0,0);
    for(int i = 0;i<ui->listWidget->count();i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        QWidget *dlg = ui->listWidget->itemWidget(item);
        delete dlg;
        dlg =NULL;
        delete item;
        item = NULL;
    }
    delete ui;
}
void RunOsdStyleDlg::initCombColor(QComboBox *cmb)
{

    QString strPath ="./image/color/";
    QString strName = "Red.png";
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
    //cmb->setIconSize(QSize(70,20));
    //cmb->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    //cmb->addItem(IconRed,tr("红"));
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
void RunOsdStyleDlg::InitVt(QListWidget *listWidget)
{
    int i = 0;

    if(OSDStyle::vt_task_enable.count()==0)
    {
        for(i = 0; i<listWidget->count();i++)
            OSDStyle::vt_task_enable.append(1);

    }else if(OSDStyle::vt_task_enable.count() != listWidget->count())
    {
        OSDStyle::vt_task_enable.clear();

        for(i = 0; i<listWidget->count();i++)
        {
            OSDStyle::vt_task_enable.append(1);       
        }
    }

}
void RunOsdStyleDlg::InitVtEnable(QListWidget *listWidget)
{
    int i = 0;

    if(OSDStyle::vt_task_enable.count()==0)
    {
        for(i = 0; i<listWidget->count();i++)
            OSDStyle::vt_task_enable.append(1);

    }else if(OSDStyle::vt_task_enable.count() != listWidget->count())
    {
        OSDStyle::vt_task_enable.clear();

        for(i = 0; i<listWidget->count();i++)
            OSDStyle::vt_task_enable.append(1);
    }
    for(i = 0; i<listWidget->count();i++)
    {

        QString strName = listWidget->item(i)->text();
        AddItem(strName,OSDStyle::vt_task_enable[i]);
    }
}
void RunOsdStyleDlg::AddItem(QString strName,int value)
{
    int size = ui->listWidget->count();
    RunOsdStyleItem *dlg = new RunOsdStyleItem();
    QListWidgetItem* mItem = new QListWidgetItem(ui->listWidget);
    dlg->SetTaskName(strName,value);
    ui->listWidget->setItemWidget(mItem,(QWidget*)dlg);
    ui->listWidget->item(size)->setSizeHint(QSize(300,60));
    connect(dlg,&RunOsdStyleItem::ChangeItemCheck,this,&RunOsdStyleDlg::ItemCheckSlot);
}
void RunOsdStyleDlg::SetLable(QLabel *label)
{
    m_label = label;
    this->m_vt = OSDStyle::vt_task_enable;
    m_OK_Color = OSDStyle::pen_color.run_osd.runOK_color;
    m_NG_Color = OSDStyle::pen_color.run_osd.runNG_color;
    m_OK_Width = OSDStyle::pen_color.run_osd.runOKWidth;
    m_NG_Width = OSDStyle::pen_color.run_osd.runNGWidth;
}
void RunOsdStyleDlg::ItemCheckSlot(int value,QString strStept)
{
    int index = strStept.toInt()-1;
    OSDStyle::vt_task_enable[index] = value;
    /*if(m_label != NULL)
        m_label->update();*/
}
void RunOsdStyleDlg::on_btnOK_clicked()
{
    OSDStyle::InitPenStyle();
    QDialog::accept();
}
void RunOsdStyleDlg::GetColor(int index)
{
    switch (index) {
    case 0:
        g_run_color = COLOR_RED_TYPE; //红
        break;
    case 1:
        g_run_color= COLOR_ORANGE_TYPE; //橙
        break;
    case 2:
        g_run_color = COLOR_YELLOW_TYPE; //黄
        break;
    case 3:
        g_run_color = COLOR_GREEN_TYPE; //绿
        break;
    case 4:
        g_run_color = COLOR_BLUE_TYPE; //蓝
        break;
    case 5:
        g_run_color= COLOR_CYAN_TYPE; //靛
        break;
    case 6:
        g_run_color = COLOR_PURPLE_TYPE; //紫
        break;
    case 7:
        g_run_color = COLOR_WHILTE_TYPE; //白
        break;
    case 8:
        g_run_color = COLOR_BLACK_TYPE; //黑
        break;
    case 9:
        g_run_color = COLOR_GRAY_TYPE; //灰
        break;
    default:
        break;
    }
}

void RunOsdStyleDlg::on_btnQuit_clicked()
{
    GetColor(m_OK_Color);
    OSDStyle::pen_color.run_osd.runOK_color = g_run_color;
    GetColor(m_NG_Color);
    OSDStyle::pen_color.run_osd.runNG_color = g_run_color;
    OSDStyle::pen_color.run_osd.runOKWidth = m_OK_Width;
    OSDStyle::pen_color.run_osd.runNGWidth = m_NG_Width;
    OSDStyle::vt_task_enable = this->m_vt;
    QDialog::reject();
}

void RunOsdStyleDlg::on_comboBoxOKColor_currentIndexChanged(int index)
{
    if(iniFirst ==1)
    {
        GetColor(index);
        OSDStyle::pen_color.run_osd.runOK_color = g_run_color;
    }
    //m_label->update();

}
void RunOsdStyleDlg::on_comboBoxNGColor_currentIndexChanged(int index)
{
    if(iniFirst ==1)
    {
        GetColor(index);
        OSDStyle::pen_color.run_osd.runNG_color = g_run_color;
    }
    //m_label->update();
}
bool RunOsdStyleDlg::eventFilter(QObject *watched, QEvent *event)
{
    if(!((QLineEdit*)watched)->isEnabled() || ((QLineEdit*)watched)->isReadOnly())
    {
        return QWidget::eventFilter(watched, event);
    }
    if (watched == ui->txtOKWidth)         //首先判断控件(这里指 lineEdit1)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            SelectWidth(ui->txtOKWidth);
            OSDStyle::pen_color.run_osd.runOKWidth = ui->txtOKWidth->text().toInt();
            //m_label->update();
        }
    }
    if (watched == ui->txtNGWidth)         //首先判断控件(这里指 lineEdit1)
    {
        if (event->type()==QEvent::MouseButtonPress)
        {
            SelectWidth(ui->txtNGWidth);
            OSDStyle::pen_color.run_osd.runNGWidth = ui->txtNGWidth->text().toInt();
            //m_label->update();
        }
    }
    return QWidget::eventFilter(watched, event);
}
void RunOsdStyleDlg::SelectWidth(QLineEdit *txtLineEdit)
{
    QDialog *dlg = m_keyBoardLib.GetNumKeyBoardDialog();
    int ret = dlg->exec();
    if(ret == QDialog::Accepted)
    {
        if(m_keyBoardLib.GetNum().toInt()>=1 && m_keyBoardLib.GetNum().toInt()<=16)
        {
            txtLineEdit->setText(m_keyBoardLib.GetNum());
        }
        else
        {
            QString strTemp;
            strTemp = tr("请输入1到16之间数");
            QMessageBox::information(NULL,tr("提示"),strTemp);
        }
    }
}

