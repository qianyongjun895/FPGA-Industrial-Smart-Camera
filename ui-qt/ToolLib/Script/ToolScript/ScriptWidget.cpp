#include "QDebug"
#include "ScriptWidget.h"
#include "ui_ScriptWidget.h"
#include "QFileDialog"

ScriptWidget::ScriptWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScriptWidget)
{
    ui->setupUi(this);

    QString tabBarStyle = "QTabBar::tab {min-width:80px;color: rgb(0,0,0);border: 1px solid;border-top-left-radius: 10px;border-top-right-radius: 10px;padding:5px;}\
            QTabBar::tab:!selected {margin-top: 5px;background: rgb(230, 230, 230);} \
            QTabBar::tab:selected {color: rgb(0,0,0);background: rgb(249,220, 117);}";
    ui->tabWidget->setStyleSheet(tabBarStyle);
}

ScriptWidget::~ScriptWidget()
{
    delete ui;
}

int ScriptWidget::Set_Parameter_To_Ram()
{
    if(ui->listWidget->currentRow() < 0)
    {
        return 0;
    }
    pInputpara->script_type = ui->tabWidget->currentIndex()+1;
    memcpy(pInputpara->script_file_name,ui->listWidget->currentItem()->text().toUtf8().data(),SCRIPT_FILE_NAME_MAX);
//    pInputpara->script_file_name = ui->listWidget->currentItem()->text().toLocal8Bit().data();
    return 1;
}

void ScriptWidget::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    pInputpara = (SCRIPT_INPUT_PARAM*)ptr;
    if(new_flag)
    {
        Task_Step_Synthetic_Judge_Flag_Set(i_step_index,1);
        pInputpara->script_type = SCRIPT_TYPE_PY2;
    }
    ui->tabWidget->setCurrentIndex(pInputpara->script_type - 1);
    on_tabWidget_tabBarClicked(pInputpara->script_type - 1);
    char script_file_name[SCRIPT_FILE_NAME_MAX];
    memcpy(script_file_name,pInputpara->script_file_name,SCRIPT_FILE_NAME_MAX);
    QString Script_name = QString::fromUtf8(script_file_name);
    qDebug()<<"Script_name  = "<<Script_name ;
    ui->lineEdit->setText(Script_name);
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        if(Script_name == ui->listWidget->item(i)->text())
        {
            ui->listWidget->setCurrentRow(i);
        }
    }
}


void ScriptWidget::Get_Result_From_Ram()
{

}


void ScriptWidget::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0)
    {
        LoadPython2Script();
    }
    else if(index == 1)
    {
        LoadPython3Script();
    }else
    {
        LoadLuaScript();
    }
}

void ScriptWidget::LoadPython2Script()
{
    ui->listWidget->clear();
    QDir dir(PY2_ROOT_DIR);
    foreach(QFileInfo mfi, dir.entryInfoList())
    {
        if(mfi.isFile())
        {
            if(0 == (mfi.suffix().compare("py")))
            {
                ui->listWidget->addItem(QString::fromUtf8(mfi.baseName().toLocal8Bit().data()));
//                qDebug()<<"curFileName:"<<QString::fromUtf8(mfi.baseName().toLocal8Bit().data());
            }
        }
    }
    ui->listWidget->setCurrentRow(0);
}
void ScriptWidget::LoadPython3Script()
{
    ui->listWidget->clear();
    QDir dir(PY3_ROOT_DIR);
    foreach(QFileInfo mfi, dir.entryInfoList())
    {
        if(mfi.isFile())
        {
            if(0 == (mfi.suffix().compare("py")))
            {
                ui->listWidget->addItem(QString::fromUtf8(mfi.baseName().toLocal8Bit().data()));
//                qDebug()<<"curFileName:"<<QString::fromUtf8(mfi.baseName().toLocal8Bit().data());
            }
        }
    }
}
void ScriptWidget::LoadLuaScript()
{
    ui->listWidget->clear();
    QDir dir(LUA_ROOT_DIR);
    foreach(QFileInfo mfi, dir.entryInfoList())
    {
        if(mfi.isFile())
        {
            if(0 == (mfi.suffix().compare("lua")))
            {
                ui->listWidget->addItem(QString::fromUtf8(mfi.baseName().toLocal8Bit().data()));
//                qDebug()<<"curFileName:"<<QString::fromUtf8(mfi.baseName().toLocal8Bit().data());
            }
        }
    }
}

void ScriptWidget::on_tabWidget_tabBarClicked(int index)
{
    if(index == 0)
    {
        LoadPython2Script();
    }
    else if(index == 1)
    {
        LoadPython3Script();
    }else
    {
        LoadLuaScript();
    }
}

void ScriptWidget::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->lineEdit->clear();
    ui->lineEdit->setText(item->text());
}
