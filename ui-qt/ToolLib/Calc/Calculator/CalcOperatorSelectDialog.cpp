#include "CalcOperatorSelectDialog.h"
#include "ui_CalcOperatorSelectDialog.h"
#include <QMessageBox>
CalcOperatorSelectDialog::CalcOperatorSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalcOperatorSelectDialog)
{
    ui->setupUi(this);
}

CalcOperatorSelectDialog::~CalcOperatorSelectDialog()
{
    delete ui;
}

void CalcOperatorSelectDialog::InitOperatorInfo(QStringList info)
{
    str_operator_info = info;
}


void CalcOperatorSelectDialog::SetDataByOperator(int Op_type_index,int Op_index)
{
    int i_real_index = 0;
    switch (Op_type_index) {
    case 0:
        i_real_index = Op_index;
        break;
    case 1:
        i_real_index = Op_index + 6;
        break;
    case 2:
        i_real_index = Op_index + 6 + 4;
        break;
    case 3:
        i_real_index = Op_index + 6 + 4 + 10;
        break;
    case 4:
        i_real_index = Op_index + 6 + 4 + 10 + 11;
        break;
    case 5:
        i_real_index = Op_index + 6 + 4 + 10 + 11 + 7;
        break;
    default:
        break;
    }
    if(str_operator_info.isEmpty())
    {
        QMessageBox::about(this,tr("提示"),tr("运算符初始化错误!"));
        return;
    }
    m_str_operator_type = str_operator_info[i_real_index].split(";")[0];
    m_use_data_count = str_operator_info[i_real_index].split(";")[1].toInt();
    strInfo = str_operator_info[i_real_index].split(";")[2];
}

void CalcOperatorSelectDialog::AddOperatorItem(QString strTemp,QListWidget *plistWidgetOperatorSelect)
{
    if(strTemp == "算术运算符")
    {
        plistWidgetOperatorSelect->addItem(tr("+:数据1加上数据2的和"));
        plistWidgetOperatorSelect->addItem(tr("-:数据1减去数据2的差"));
        plistWidgetOperatorSelect->addItem(tr("*:数据1乘上数据2的积"));
        plistWidgetOperatorSelect->addItem(tr("/:数据1除以数据2的商"));
        plistWidgetOperatorSelect->addItem(tr("%:求余数"));
        plistWidgetOperatorSelect->addItem(tr("^:多次方"));
    }else if(strTemp == "逻辑运算符")
    {
        plistWidgetOperatorSelect->addItem(tr("!:取反"));
        plistWidgetOperatorSelect->addItem(tr("&&:逻辑与"));
        plistWidgetOperatorSelect->addItem(tr("||:逻辑或"));
        plistWidgetOperatorSelect->addItem(tr("XOR:逻辑异或"));

    }else if(strTemp == "比较运算符")
    {
        plistWidgetOperatorSelect->addItem(tr("==:等于"));
        plistWidgetOperatorSelect->addItem(tr("!=:不等于"));
        plistWidgetOperatorSelect->addItem(tr(">:大于"));
        plistWidgetOperatorSelect->addItem(tr("<:小于"));
        plistWidgetOperatorSelect->addItem(tr(">=:大于等于"));
        plistWidgetOperatorSelect->addItem(tr("<=:小于等于"));
        plistWidgetOperatorSelect->addItem(tr("Max:极大值"));
        plistWidgetOperatorSelect->addItem(tr("Min:极小值"));
        plistWidgetOperatorSelect->addItem(tr("Max_ID:极大值索引"));
        plistWidgetOperatorSelect->addItem(tr("Min_ID:极小值索引"));

    }
    else if(strTemp == "普通运算函数")
    {
        plistWidgetOperatorSelect->addItem(tr("Abs(x):绝对值"));
        plistWidgetOperatorSelect->addItem(tr("Deg(x):弧度转角度"));
        plistWidgetOperatorSelect->addItem(tr("Rad(x):角度转弧度"));
        plistWidgetOperatorSelect->addItem(tr("Sqr(x):平方"));
        plistWidgetOperatorSelect->addItem(tr("Sqrt(x):平方根"));
        plistWidgetOperatorSelect->addItem(tr("Ceil(x):整数化(进位)"));
        plistWidgetOperatorSelect->addItem(tr("Floor(x):整数化(舍去)"));
        plistWidgetOperatorSelect->addItem(tr("Int(x):整数化(舍去小数)"));
        plistWidgetOperatorSelect->addItem(tr("Round(x):整数化(四舍五入)"));
        plistWidgetOperatorSelect->addItem(tr("Ln(x):自然对数"));
        plistWidgetOperatorSelect->addItem(tr("Lg(x):常用对数"));
    }else if(strTemp == "三角运算函数")
    {
        plistWidgetOperatorSelect->addItem(tr("Cos(x):佘弦"));
        plistWidgetOperatorSelect->addItem(tr("Sin(x):正弦"));
        plistWidgetOperatorSelect->addItem(tr("Tan(x):正切"));
        plistWidgetOperatorSelect->addItem(tr("Acos(x):反佘弦"));
        plistWidgetOperatorSelect->addItem(tr("Asin(x):反正弦"));
        plistWidgetOperatorSelect->addItem(tr("Atan(x):反正切"));
        plistWidgetOperatorSelect->addItem(tr("Atan(x,y):反正切(x,y)"));

    }else if(strTemp == "位运算")
    {
        plistWidgetOperatorSelect->addItem(tr("~:按位取反"));
        plistWidgetOperatorSelect->addItem(tr("&:按位与"));
        plistWidgetOperatorSelect->addItem(tr("|:按位或"));
        plistWidgetOperatorSelect->addItem(tr("Bxor(x,y):按位异或"));
    }
}


void CalcOperatorSelectDialog::on_btnOk_clicked()
{
    if(ui->listWidgetOperatorTypeSelect->currentRow()<0)
    {
        QMessageBox::about(NULL,tr("提示"),tr("请选择运算符类型!"));
        return ;
    }
    if(ui->listWidgetOperatorTypeSelect->currentRow() < 0)
    {
        QMessageBox::about(NULL,tr("提示"),tr("请选择具体的运算符!"));
        return ;
    }
    QDialog::accept();
}

void CalcOperatorSelectDialog::on_btnQuit_clicked()
{
    QDialog::reject();
}

void CalcOperatorSelectDialog::on_listWidgetOperatorTypeSelect_itemClicked(QListWidgetItem *item)
{
    QString strTemp = item->text();
    ui->listWidgetOperatorSelect->clear();
    m_str_operator_type="";
    AddOperatorItem(strTemp,ui->listWidgetOperatorSelect);
}

void CalcOperatorSelectDialog::on_listWidgetOperatorSelect_itemClicked(QListWidgetItem *item)
{
    QString strTemp = item->text();
//    SetDataByOperator(strTemp);
    SetDataByOperator(ui->listWidgetOperatorTypeSelect->currentRow(),ui->listWidgetOperatorSelect->currentRow());
    ui->textBrowser->setText(strInfo);
}
