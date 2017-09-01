#include "MitFxPlcWidget.h"
#include "ui_MitFxPlcWidget.h"
#include "MitFxPlcGlobal.h"
#include "MitFxPlcListWidgetItem.h"
#include "qmessagebox.h"
#include "WRMRegDialog.h"
#include "RDDRegDialog.h"
#include "WRDRegDialog.h"
#include <QDebug>
MitFxPlcWidget::MitFxPlcWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MitFxPlcWidget)
{
    ui->setupUi(this);
    LoadKeyBoardLib();
    ui->comboBox_Model->addItem(tr("三菱Fx系列"));

    ui->comboBox_form->addItem(tr("无"));
    ui->comboBox_form->addItem(tr("CR+LF"));

    ui->comboBox_too_Type->addItem(tr("读M寄存器"));
    ui->comboBox_too_Type->addItem(tr("写M寄存器"));
    ui->comboBox_too_Type->addItem(tr("读D寄存器"));
    ui->comboBox_too_Type->addItem(tr("写D寄存器"));

    ui->lineEdit_station_number->installEventFilter(this);
    ui->lineEdit_wait_time->installEventFilter(this);
    ui->lineEdit_PC_number->installEventFilter(this);

    MIT_PLC_CFG Plc_cfg;
    mit_fx_plc_cfg_get(&Plc_cfg);
    ui->lineEdit_station_number->setText(QString::number(Plc_cfg.station_id));
    ui->lineEdit_PC_number->setText(QString::number(Plc_cfg.pc_id));
    ui->lineEdit_wait_time->setText(QString::number(Plc_cfg.message_wait));
    ui->comboBox_form->setCurrentIndex(Plc_cfg.format);

    int cnt = mit_fx_plc_list_data_cnt_get();
    for(int i = 0; i < cnt; i++)
    {
        int tool_type = mit_fx_plc_list_data_type_get(i);
        if(tool_type == M_REG_READ)
        {
            AddRDMRegItem();
        }
        else if(tool_type == M_REG_WRITE)
        {
            AddWRMRegItem();
        }
        else if(tool_type == D_REG_READ)
        {
            AddRDDRegItem();
        }
        else if(tool_type == D_REG_WRITE)
        {
            AddWRDRegItem();
        }
    }
}

MitFxPlcWidget::~MitFxPlcWidget()
{
    if(m_keyBoard_Lib.isLoaded())
    {
        m_keyBoard_Lib.unload();
    }
    ui->lineEdit_station_number->removeEventFilter(this);
    ui->lineEdit_wait_time->removeEventFilter(this);
    ui->lineEdit_PC_number->removeEventFilter(this);
    delete ui;
}

void MitFxPlcWidget::AddListWisgetItem(MitFxPlcListWidgetItem* item)
{
    item->setAttribute(Qt::WA_DeleteOnClose);
    int size = ui->listWidget->count();
    QListWidgetItem* List_Item = new QListWidgetItem(ui->listWidget);
    ui->listWidget->setItemWidget(List_Item, (QWidget*)item);
    ui->listWidget->item(size)->setSizeHint(QSize(240,40));
    ui->listWidget->setCurrentRow(size);
}

void MitFxPlcWidget::LoadKeyBoardLib()
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

void MitFxPlcWidget::NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value)
{
    Fun_GetNumkeyBoardDlg GetNumKeyBoardDlg = (Fun_GetNumkeyBoardDlg)m_keyBoard_Lib.resolve("GetNumKeyBoardDialog");
    if(GetNumKeyBoardDlg)
    {
        Numkey = GetNumKeyBoardDlg();
        int ret = Numkey->exec();
        if(ret == QDialog::Accepted)
        {
            Fun_GetNumString GetNumString = (Fun_GetNumString)m_keyBoard_Lib.resolve("GetNum");
            if(GetNumString)
            {
                QString num = GetNumString();
                if(Max_value == 0 && Min_value == 0)
                {
                }
                else if(num.toInt() > Max_value || num.toInt() < Min_value)
                {
                    QMessageBox::about(NULL, tr("提示"), tr("该值无效,请输入")+QString::number(Min_value)+tr("~")+QString::number(Max_value)+tr("之间的值"));
                    return;
                }
                ((QLineEdit *)watched)->setText(num);
            }
        }
        delete Numkey;
    }
    else
    {
        qDebug()<<"get GetDialog func fail:"<<m_keyBoard_Lib.errorString();
    }
}

void MitFxPlcWidget::AddRDMRegItem()
{
    MitFxPlcListWidgetItem* item = new MitFxPlcListWidgetItem;
    item->SetLableText(tr("读M寄存器"));
    item->SetCurrentIndex(ui->listWidget->count());
    item->SetToolType(M_REG_READ);
    AddListWisgetItem(item);
}

void MitFxPlcWidget::AddWRMRegItem()
{
    MitFxPlcListWidgetItem* item = new MitFxPlcListWidgetItem;
    item->SetLableText(tr("写M寄存器"));
    item->SetCurrentIndex(ui->listWidget->count());
    item->SetToolType(M_REG_WRITE);
    AddListWisgetItem(item);
}

void MitFxPlcWidget::AddRDDRegItem()
{
    MitFxPlcListWidgetItem* item = new MitFxPlcListWidgetItem;
    item->SetLableText(tr("读D寄存器"));
    item->SetCurrentIndex(ui->listWidget->count());
    item->SetToolType(D_REG_READ);
    AddListWisgetItem(item);
}

void MitFxPlcWidget::AddWRDRegItem()
{
    MitFxPlcListWidgetItem* item = new MitFxPlcListWidgetItem;
    item->SetLableText(tr("写D寄存器"));
    item->SetCurrentIndex(ui->listWidget->count());
    item->SetToolType(D_REG_WRITE);
    AddListWisgetItem(item);
}

void MitFxPlcWidget::on_pushButton_Add_clicked()
{
    if(ui->listWidget->count() >= PLC_DATA_LIST_NUM_MAX)
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("数据流达到最大限制100条,不能再添加"), QMessageBox::Yes);
        return;
    }
    int tool_type = ui->comboBox_too_Type->currentIndex();
    if(tool_type == M_REG_READ)
    {
        WRMRegDialog* dlg = new WRMRegDialog;
        dlg->SetToolType(M_REG_READ);
        dlg->SetCurrentIndex(ui->listWidget->count());
        dlg->IniWRMRegData();
        int ret = dlg->exec();
        if(ret == QDialog::Accepted)
        {
            AddRDMRegItem();
        }
    }
    else if(tool_type == M_REG_WRITE)
    {
        WRMRegDialog* dlg = new WRMRegDialog;
        dlg->SetToolType(M_REG_WRITE);
        dlg->SetCurrentIndex(ui->listWidget->count());
        dlg->IniWRMRegData();
        int ret = dlg->exec();
        if(ret == QDialog::Accepted)
        {
            AddWRMRegItem();
        }
    }
    else if(tool_type == D_REG_READ)
    {
        RDDRegDialog *dlg = new RDDRegDialog;
        dlg->SetToolType(D_REG_READ);
        dlg->SetCurrentIndex(ui->listWidget->count());
        dlg->IniRDDRegData();
        int ret = dlg->exec();
        if(ret == QDialog::Accepted)
        {
            AddRDDRegItem();
        }
    }
    else if(tool_type == D_REG_WRITE)
    {
        WRDRegDialog *dlg = new WRDRegDialog;
        dlg->SetDlgType(0);
        dlg->SetDataListIndex(ui->listWidget->count());
        dlg->IniRegData();
        int ret = dlg->exec();
        if(ret == QDialog::Accepted)
        {
            AddWRDRegItem();
        }
    }
    mit_fx_plc_list_data_cnt_set(ui->listWidget->count());
}

bool MitFxPlcWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEdit_station_number)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            NumKeyBoardDlg(watched, event, 0, 255);
        }
    }
    if(watched == ui->lineEdit_wait_time)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            NumKeyBoardDlg(watched, event, 0, 15);
        }
    }
    if(watched == ui->lineEdit_PC_number)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            NumKeyBoardDlg(watched, event, 0, 255);
        }
    }
    QWidget::eventFilter(watched, event);
}


void MitFxPlcWidget::SetMitFxPLCConfig()
{
    MIT_PLC_CFG Plc_cfg;
    Plc_cfg.station_id = ui->lineEdit_station_number->text().toUInt();
    Plc_cfg.pc_id = ui->lineEdit_PC_number->text().toUInt();
    Plc_cfg.format = ui->comboBox_form->currentIndex();
    Plc_cfg.message_wait = ui->lineEdit_wait_time->text().toUInt();
    mit_fx_plc_cfg_set(&Plc_cfg);
}

void MitFxPlcWidget::on_pushButton_Del_clicked()
{
    int row = ui->listWidget->currentRow();
    if(row >= 0)
    {
        mit_fx_plc_del_data_list(row);
        QListWidgetItem *List_Item =  ui->listWidget->takeItem(row);
        delete List_Item;
    }
    mit_fx_plc_list_data_cnt_set(ui->listWidget->count());
}

void MitFxPlcWidget::on_pushButton_Up_clicked()
{
    int row = ui->listWidget->currentRow();
    if(row > 0)
    {
        mit_fx_plc_data_list_move_up(row);

        QListWidgetItem *List_Item = ui->listWidget->item(row);
        QWidget *m_Widget = ui->listWidget->itemWidget(List_Item);

        QListWidgetItem *Pre_List_Item = ui->listWidget->item(row - 1);
        QWidget *Pre_Widget = ui->listWidget->itemWidget(Pre_List_Item);
        QString Pre_String = ((MitFxPlcListWidgetItem*)Pre_Widget)->GetLabelText();
        int Pre_Tool = ((MitFxPlcListWidgetItem*)Pre_Widget)->GetToolType();

        ((MitFxPlcListWidgetItem*)Pre_Widget)->SetLableText(((MitFxPlcListWidgetItem*)m_Widget)->GetLabelText());
        ((MitFxPlcListWidgetItem*)Pre_Widget)->SetToolType(((MitFxPlcListWidgetItem*)m_Widget)->GetToolType());

        ((MitFxPlcListWidgetItem*)m_Widget)->SetLableText(Pre_String);
        ((MitFxPlcListWidgetItem*)m_Widget)->SetToolType(Pre_Tool);

        ui->listWidget->setCurrentRow(row - 1);
    }
}

void MitFxPlcWidget::on_pushButton_Down_clicked()
{
    int row = ui->listWidget->currentRow();
    if(row >= 0 && row < ui->listWidget->count() - 1)
    {
        mit_fx_plc_data_list_move_down(row);

        QListWidgetItem *List_Item = ui->listWidget->item(row);
        QWidget *m_Widget = ui->listWidget->itemWidget(List_Item);

        QListWidgetItem *Pre_List_Item = ui->listWidget->item(row + 1);
        QWidget *Pre_Widget = ui->listWidget->itemWidget(Pre_List_Item);
        QString Pre_String = ((MitFxPlcListWidgetItem*)Pre_Widget)->GetLabelText();
        int Pre_Tool = ((MitFxPlcListWidgetItem*)Pre_Widget)->GetToolType();

        ((MitFxPlcListWidgetItem*)Pre_Widget)->SetLableText(((MitFxPlcListWidgetItem*)m_Widget)->GetLabelText());
        ((MitFxPlcListWidgetItem*)Pre_Widget)->SetToolType(((MitFxPlcListWidgetItem*)m_Widget)->GetToolType());

        ((MitFxPlcListWidgetItem*)m_Widget)->SetLableText(Pre_String);
        ((MitFxPlcListWidgetItem*)m_Widget)->SetToolType(Pre_Tool);

        ui->listWidget->setCurrentRow(row + 1);
    }
}
