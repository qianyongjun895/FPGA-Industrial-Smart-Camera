#include "WRDRegDialog.h"
#include "ui_WRDRegDialog.h"
#include "TaskHeaderGlobal.h"
#include "TaskStepGlobal.h"
#include "LinkDataGlobal.h"
#include "ProtocolManageGlobal.h"
#include <QDebug>
#include <QMessageBox>
WRDRegDialog::WRDRegDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WRDRegDialog)
{
    ui->setupUi(this);
    Ini_Flag = 0;
    LoadKeyBoardLib();
    IniData();
}

WRDRegDialog::~WRDRegDialog()
{
    if(m_keyBoard_Lib.isLoaded())
    {
        m_keyBoard_Lib.unload();
    }
    ui->lineEdit_StartAddr->removeEventFilter(this);
    ui->lineEdit_Length->removeEventFilter(this);
    delete ui;
}


void WRDRegDialog::IniData()
{
    Page_cnt = 1;
    current_page = 1;
    ui->lineEdit_StartAddr->installEventFilter(this);
    ui->lineEdit_Length->installEventFilter(this);

    char taskName[40];
    for(unsigned int i = 0; i < GetTaskStepCount(); i ++)
    {
        memset(taskName, 0, 40);
        int ret = Get_Task_Name(i+1, taskName);
        if(ret != -1)
        {
            ui->comboBox_TaskList->addItem(QString::number(i+1) +"."+ QString::fromUtf8(taskName));
        }
    }
    ui->comboBox_DataType->addItem("int");
    ui->comboBox_DataType->addItem("int inverse");
    ui->comboBox_DataType->addItem("uint");
    ui->comboBox_DataType->addItem("uint inverse");
    ui->comboBox_DataType->addItem("float");
    ui->comboBox_DataType->addItem("float inverse");
    ui->comboBox_DataType->addItem("long");
    ui->comboBox_DataType->addItem("long inverse");
    ui->comboBox_DataType->addItem("double");
    ui->comboBox_DataType->addItem("double inverse");
}

void WRDRegDialog::IniRegData()
{
    ui->lineEdit_StartAddr->setText("1");
    ui->lineEdit_Length->setText("8");

    ui->comboBox_DataType->setCurrentIndex(0);
    ui->comboBox_TaskList->setCurrentIndex(0);
    ui->checkBox_Pre->setChecked(false);
}

void WRDRegDialog::GetRegData()
{
    Ini_Flag = 1;

    mit_fx_plc_data_list_get(Data_List_Index, &WR_D_Reg);

    ui->lineEdit_StartAddr->setText(QString::number(WR_D_Reg.reg_start));
    ui->lineEdit_Length->setText(QString::number(WR_D_Reg.reg_num));
    ui->comboBox_DataType->setCurrentIndex(WR_D_Reg.data_type);

    ui->comboBox_TaskList->setCurrentIndex(mit_fx_plc_list_exec_step_get(Data_List_Index) - 1);

    if(mit_fx_plc_list_pre_post_exec_step_get(Data_List_Index) == DATA_EXEC_PRE_STEP)
    {
        ui->checkBox_Pre->setChecked(true);
    }
    else
    {
        ui->checkBox_Pre->setChecked(false);
    }
}

void WRDRegDialog::SetDataListIndex(int List_Index)
{
    Data_List_Index = List_Index;
}

void WRDRegDialog::LoadKeyBoardLib()
{
    m_keyBoard_Lib.setFileName("libFrmInputKeyBoard.so");
    if(m_keyBoard_Lib.isLoaded())
    {
        return;
    }
    if(m_keyBoard_Lib.load())
    {
    }
    else
    {
        qDebug()<<"load libFrmInputKeyBoard.so fail"<<m_keyBoard_Lib.errorString();
    }
}

void WRDRegDialog::NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value)
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
                if(num.toInt() > Max_value || num.toInt() < Min_value)
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

bool WRDRegDialog::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEdit_StartAddr)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            NumKeyBoardDlg(watched, event, 1, 10000);
        }
    }
    if(watched == ui->lineEdit_Length)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            NumKeyBoardDlg(watched, event, 1, 64);
        }
    }
    return QWidget::eventFilter(watched, event);
}

void WRDRegDialog::AddMultiRegItem(WRDRegItem *item)
{
    item->setAttribute(Qt::WA_DeleteOnClose);
    int size = ui->listWidget_Reg->count();
    QListWidgetItem *list_item = new QListWidgetItem(ui->listWidget_Reg);
    ui->listWidget_Reg->setItemWidget(list_item, item);
    ui->listWidget_Reg->item(size)->setSizeHint(QSize(240,45));
}
void WRDRegDialog::RegSetChanged()
{
    if(Ini_Flag == 0)
    {
        memset(&WR_D_Reg, 0, sizeof(WR_D_Reg));
    }
    int start_addr = ui->lineEdit_StartAddr->text().toInt();
    int length = ui->lineEdit_Length->text().toInt();
    ui->current_Page_label->setText("1");
    current_page = 1;
    if(length > 8)
    {
        RegCofingChanged(1, start_addr, 8);
    }
    else
    {
        RegCofingChanged(1, start_addr, length);
    }
}

void WRDRegDialog::RegCofingChanged(int number, int coil_addr, int data_cnts)
{
    ui->listWidget_Reg->clear();
    for(int i = 1; i <= data_cnts; i++)
    {
        WRDRegItem * item = new WRDRegItem;
        item->SetNumber(number++);
        item->SetRegAddr(coil_addr++);
        item->SetDataType(ui->comboBox_DataType->currentIndex(), ui->lineEdit_Length->text().toInt());
        item->SetDataSource(&WR_D_Reg, Dlg_Type);

        AddMultiRegItem(item);
    }
}

void WRDRegDialog::CalcPageData()
{
    int length = ui->lineEdit_Length->text().toInt();
    if(length > 8)
    {
        Page_cnt = ((length -1) / 8) + 1;
    }
    else
    {
        Page_cnt = 1;
    }
    ui->Page_cnt_label->setText(QString::number(Page_cnt));
}

void WRDRegDialog::on_pushButton_pre_clicked()
{
    if(current_page == 1)
    {
        return;
    }
    else
    {
        current_page--;
        ui->current_Page_label->setText(QString::number(current_page));
        int number = current_page * 8 - 8 + 1;
        int start_addr = ui->lineEdit_StartAddr->text().toInt();
        int coilAddr = start_addr + number - 1;
        RegCofingChanged(number, coilAddr, 8);
    }
}

void WRDRegDialog::on_pushButton_next_clicked()
{
    if(current_page < Page_cnt)
    {
        current_page++;
        ui->current_Page_label->setText(QString::number(current_page));
        int number = current_page * 8 - 8 + 1;
        int start_addr = ui->lineEdit_StartAddr->text().toInt();
        int coilAddr = start_addr + number - 1;
        int length = ui->lineEdit_Length->text().toInt();
        if(length > current_page*8)
        {
            RegCofingChanged(number, coilAddr, 8);
        }
        else
        {
            int item_count = length - (current_page - 1)*8;
            RegCofingChanged(number, coilAddr, item_count);
        }
    }
}

void WRDRegDialog::on_lineEdit_StartAddr_textChanged(const QString &arg1)
{
    RegSetChanged();
}

void WRDRegDialog::on_lineEdit_Length_textChanged(const QString &arg1)
{
    RegSetChanged();
    CalcPageData();
}

void WRDRegDialog::on_comboBox_DataType_currentIndexChanged(int index)
{
    RegSetChanged();
}

void WRDRegDialog::on_btn_Finish_clicked()
{
    WR_D_Reg.reg_start = ui->lineEdit_StartAddr->text().toInt();
    WR_D_Reg.reg_num = ui->lineEdit_Length->text().toInt();
    WR_D_Reg.data_type = ui->comboBox_DataType->currentIndex();
    WR_D_Reg.link_cnt = 0;
    for(int i = 0; i < WR_D_Reg.reg_num; i++)
    {
        if(WR_D_Reg.data_source[i] == 1)
        {
            WR_D_Reg.link_cnt++;
        }
    }
    mit_fx_plc_data_list_set(Data_List_Index, &WR_D_Reg, D_REG_WRITE);

    mit_fx_plc_list_exec_step_set(Data_List_Index, ui->comboBox_TaskList->currentIndex()+1);

    if(ui->checkBox_Pre->isChecked())
    {
        mit_fx_plc_list_pre_post_exec_step_set(Data_List_Index, DATA_EXEC_PRE_STEP);
    }
    else
    {
        mit_fx_plc_list_pre_post_exec_step_set(Data_List_Index, DATA_EXEC_POST_STEP);
    }

    QDialog::accept();
}

void WRDRegDialog::on_btn_Quit_clicked()
{
    QDialog::reject();
}
