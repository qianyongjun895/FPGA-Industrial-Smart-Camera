#include <QDebug>
#include "SSTaskEditCalculator.h"
#include "ui_SSTaskEditCalculator.h"
#include "CalcuatorData.h"
#include "stdio.h"
#include <QMessageBox>

CalcuatorData m_CalcuatorData;
SSTaskEditCalculator::SSTaskEditCalculator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SSTaskEditCalculator)
{

    ui->setupUi(this);
    //ui->btnEdit->setVisible(false);
    m_CalcOperatorSelectDialog = new CalcOperatorSelectDialog;
    m_str_operator_type = "";
    m_b_flag = false;
    this->setWindowTitle(tr("计算器"));
    IniTabaleHead();

    m_Modbus_reg_list.clear();
    m_Modbus_type_list.clear();
    m_pLc_type_list.clear();
    m_Modbus_reg_list.append(tr("1.保持寄存器"));
    m_Modbus_reg_list.append(tr("2.输入寄存器"));

    m_Modbus_type_list.append(tr("1.int"));
    m_Modbus_type_list.append(tr("2.float"));
    m_Modbus_type_list.append(tr("3.long"));
    m_Modbus_type_list.append(tr("4.double"));
    m_Modbus_type_list.append(tr("5.int inverse"));
    m_Modbus_type_list.append(tr("6.float inverse"));
    m_Modbus_type_list.append(tr("7.long inverse"));
    m_Modbus_type_list.append(tr("8.double inverse"));

    m_pLc_type_list.append(tr("1.int"));
    m_pLc_type_list.append(tr("2.float"));
    m_pLc_type_list.append(tr("3.double"));

    m_Data_Input = "数据输入地址";

    ui->txtDataOne->setReadOnly(true);
    ui->txtDataTwo->setReadOnly(true);
    ui->txtDataThree->setReadOnly(true);
    ui->txtDataFour->setReadOnly(true);
    setBtnEnable(false,false,false,false);
    str_operator_info.append("+;2;"+tr("加法\r\nX+Y\r\n返回X+Y的和"));
    str_operator_info.append("-;2;"+tr("减法\r\nX-Y\r\n返回X-Y的差"));
    str_operator_info.append("*;2;"+tr("乘法\r\nX*Y\r\n返回X*Y的积"));
    str_operator_info.append("/;2;"+tr("除法\r\nX/Y\r\n返回X/Y的商"));
    str_operator_info.append("%;2;"+tr("求余数\r\nX%Y,X除以Y后的余数\r\n返回余数"));
    str_operator_info.append("^;2;"+tr("多次方\r\nX^Y,X的Y次方\r\n返回X的Y次方的值"));
    str_operator_info.append("!;1;"+tr("逻辑取反\r\n!X,X的逻辑取反(NOT X)\r\n返回真(1)或假(0)"));
    str_operator_info.append("&&;2;"+tr("逻辑与\r\nX&&Y,X和Y的逻辑与\r\n返回真(1)或假(0)"));
    str_operator_info.append("||;2;"+tr("逻辑或\r\nX||Y,X和Y的逻辑或\r\n返回真(1)或假(0)"));
    str_operator_info.append("XOR;2;"+tr("逻辑异或\r\nX XOR Y,X和Y的逻辑异或\r\n返回真(1)或假(0)"));
    str_operator_info.append("==;2;"+tr("等于\r\nX==Y,比较X和Y是否相等\r\n返回真(1)或假(0)"));
    str_operator_info.append("!=;2;"+tr("不等于\r\nX!=Y,比较X和Y是否不相等\r\n返回真(1)或假(0)"));
    str_operator_info.append(">;2;"+tr("大于\r\nX>Y,比较是否X大于Y\r\n返回真(1)或假(0)"));
    str_operator_info.append("<;2;"+tr("小于\r\nX<Y,比较是否X小于Y\r\n返回真(1)或假(0)"));
    str_operator_info.append(">=;2;"+tr("大于等于\r\nX>=Y,比较是否X大于或等于Y\r\n返回真(1)或假(0)"));
    str_operator_info.append("<=;2;"+tr("小于等于\r\nX<=Y,比较是否X小于或等于Y\r\n返回真(1)或假(0)"));
    str_operator_info.append("Max;4;"+tr("求极大值"));
    str_operator_info.append("Min;4;"+tr("求极小值"));
    str_operator_info.append("Max_ID;4;"+tr("求极大值的索引"));
    str_operator_info.append("Min_ID;4;"+tr("求极小值的索引"));
    str_operator_info.append("Abs(x);1;"+tr("绝对值\r\nAbs(X),求X的绝对值\r\n返回X的绝对值"));
    str_operator_info.append("Deg(x);1;"+tr("弧度转角度\r\nDeg(X),求弧度X的角度\r\n返回弧度X的角度值"));
    str_operator_info.append("Rad(x);1;"+tr("角度转弧度\r\nRad(X),求角度X的弧度\r\n返回角度X的弧度值"));
    str_operator_info.append("Sqr(x);1;"+tr("平方\r\nSqr(X),求X的平方\r\n返回X的平方值"));
    str_operator_info.append("Sqrt(x);1;"+tr("平方根\r\nSqr(X),求X的平方根\r\n返回X的平方根值\r\n提示： 参数X须为大于或等于0的值\r\n否则计算会出错而结束"));
    str_operator_info.append("Ceil(x);1;"+tr("整数化(进位)\r\nCeil(X),把X进化成整数\r\n例如:Ceil(1.5) = 2\r\nCeil(-1.5) = -1"));
    str_operator_info.append("Floor(x);1;"+tr("整数化(舍去)\r\nFloor(X),舍去X的第一位小数\r\n例如:Floor(1.5) = 1\r\nFloor(-1.5) = -2"));
    str_operator_info.append("Int(x);1;"+tr("整数化(舍去小数)\r\nInt(X),舍去X的第一位小数\r\n例如:Int(1.5) = 1\r\nInt(-1.5) = -1"));
    str_operator_info.append("Round(x);1;"+tr("整数化(四舍五入)\r\nRound(X),四舍五入X的第一位小数\r\n例如:Round(1.5) = 2\r\nRound(-1.5) = -2\r\nRound(1.4) = 1\r\nRound(-1.4) = -1"));
    str_operator_info.append("Ln(x);1;"+tr("自然对数\r\nLn(X),计算X的自然对数值\r\n返回X的自然对数值\r\n提示：参数X须为大于0的值\r\n否则计算会出错而结束"));
    str_operator_info.append("Lg(x);1;"+tr("常用对数\r\nLg(X),计算X的常用对数值\r\n返回X的常用对数值\r\n提示:参数X须为大于0的值\r\n否则计算会出错而结束"));
    str_operator_info.append("Cos(x);1;"+tr("余弦\r\nCos(X),求弧度X的余弦值\r\n返回弧度X的余弦值"));
    str_operator_info.append("Sin(x);1;"+tr("正弦\r\nSin(X),求弧度X的正弦值\r\n返回弧度X的正弦值"));
    str_operator_info.append("Tan(x);1;"+tr("正切\r\nTan(X),求弧度X的正切值\r\n返回弧度X的正切值"));
    str_operator_info.append("Acos(x);1;"+tr("反佘弦\r\nAcos(X),求X的反余弦值\r\n返回X的反余弦值\r\n提示:参数X的范围为-1到1"));
    str_operator_info.append("Asin(x);1;"+tr("反正弦\r\nAsin(X),求X的反正弦值\r\n返回X的反正弦值\r\n提示:参数X的范围为-1到1"));
    str_operator_info.append("Atan(x);1;"+tr("反正切\r\nAtan(X),求X的正切值\r\n返回X的反正切值"));
    str_operator_info.append("Atan(x,y);2;"+tr("反正切\r\nAtan(X,Y),求X,y的正切值\r\n返回X,y的反正切值"));
    str_operator_info.append("~;1;"+tr("按位取反\r\n~X,对X按位取反\r\n返回对X按位取反的值"));
    str_operator_info.append("&;2;"+tr("按位与\r\nX&Y,X对Y按位与\r\n返回X对Y按位与的值"));
    str_operator_info.append("|;2;"+tr("按位或\r\nX|Y,X对Y按位或\r\n返回X对Y按位或的值"));
    str_operator_info.append("Bxor(x,y);2;"+tr("按位异或\r\nBxor(X,Y),X对Y按位异或\r\n返回X对Y按位异或的值"));

}
void SSTaskEditCalculator::setBtnEnable(bool bflag1,bool bflag2,bool bflag3,bool bflag4)
{
    ui->btnDataOne->setEnabled(bflag1);
    ui->btnDataTwo->setEnabled(bflag2);
    ui->btnDataThree->setEnabled(bflag3);
    ui->btnDataFour->setEnabled(bflag4);


}

void SSTaskEditCalculator::setCellClear(int paramCount)
{
    QVector<QPushButton*>sele_btn;
    sele_btn.append(ui->btnDataOne);
    sele_btn.append(ui->btnDataTwo);
    sele_btn.append(ui->btnDataThree);
    sele_btn.append(ui->btnDataFour);
    ui->btnDataOne->setEnabled(true);
    ui->btnDataTwo->setEnabled(true);
    ui->btnDataThree->setEnabled(true);
    ui->btnDataFour->setEnabled(true);

    QVector<QLineEdit*>txt_data;
    txt_data.append(ui->txtDataOne);
    txt_data.append(ui->txtDataTwo);
    txt_data.append(ui->txtDataThree);
    txt_data.append(ui->txtDataFour);
    for(int i = paramCount; i < 4;i++)
    {
        ui->tableWidgetData->setItem(ui->tableWidgetData->currentRow(),i+1,new QTableWidgetItem(""));
        sele_btn[i]->setEnabled(false);
        txt_data[i]->clear();
    }
}

//初始表格列
void SSTaskEditCalculator::IniTabaleHead()
{
    ui->tableWidgetData->setRowCount(0);
    ui->tableWidgetData->setColumnCount(5);
    QStringList horizontalHeader;
    horizontalHeader<<QObject::tr("运算符")<<QObject::tr("数据1")<<QObject::tr("数据2")<<QObject::tr("数据3")<<QObject::tr("数据4");
    QStringList verticalHeader;
    ui->tableWidgetData->setColumnWidth(0,100);
    ui->tableWidgetData->setColumnWidth(1,235);
    ui->tableWidgetData->setColumnWidth(2,235);
    ui->tableWidgetData->setColumnWidth(3,200);
    ui->tableWidgetData->setColumnWidth(4,200);

    ui->tableWidgetData->setHorizontalHeaderLabels(horizontalHeader);
    ui->tableWidgetData->setVerticalHeaderLabels(verticalHeader);
    ui->tableWidgetData->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

SSTaskEditCalculator::~SSTaskEditCalculator()
{
    delete ui;

    if(m_CalcOperatorSelectDialog !=NULL)
    {
        delete m_CalcOperatorSelectDialog;
        m_CalcOperatorSelectDialog = NULL;
    }

}

void SSTaskEditCalculator::on_listWidgetOperatorType_itemClicked(QListWidgetItem *item)
{

    QString strTemp = item->text();
    ui->txtDataFour->setText("");
    ui->txtDataOne->setText("");
    ui->txtDataThree->setText("");
    ui->txtDataTwo->setText("");
    ui->textBrowser->setText("");
    ui->listWidgetOperator->clear();
    m_str_operator_type="";
    setBtnEnable(false,false,false,false);
    if(strTemp == "算术运算符")
    {
        ui->listWidgetOperator->addItem(tr("+:数据1加上数据2的和"));
        ui->listWidgetOperator->addItem(tr("-:数据1减去数据2的差"));
        ui->listWidgetOperator->addItem(tr("*:数据1乘上数据2的积"));
        ui->listWidgetOperator->addItem(tr("/:数据1除以数据2的商"));
        ui->listWidgetOperator->addItem(tr("%:求余数"));
        ui->listWidgetOperator->addItem(tr("^:多次方"));
    }else if(strTemp == "逻辑运算符")
    {
        ui->listWidgetOperator->addItem(tr("!:取反"));
        ui->listWidgetOperator->addItem(tr("&&:逻辑与"));
        ui->listWidgetOperator->addItem(tr("||:逻辑或"));
        ui->listWidgetOperator->addItem(tr("XOR:逻辑异或"));

    }else if(strTemp == "比较运算符")
    {
        ui->listWidgetOperator->addItem(tr("==:等于"));
        ui->listWidgetOperator->addItem(tr("!=:不等于"));
        ui->listWidgetOperator->addItem(tr(">:大于"));
        ui->listWidgetOperator->addItem(tr("<:小于"));
        ui->listWidgetOperator->addItem(tr(">=:大于等于"));
        ui->listWidgetOperator->addItem(tr("<=:小于等于"));
        ui->listWidgetOperator->addItem(tr("Max:极大值"));
        ui->listWidgetOperator->addItem(tr("Min:极小值"));
        ui->listWidgetOperator->addItem(tr("Max_ID:极大值索引"));
        ui->listWidgetOperator->addItem(tr("Min_ID:极小值索引"));

    }
    else if(strTemp == "普通运算函数")
    {
        ui->listWidgetOperator->addItem(tr("Abs(x):绝对值"));
        ui->listWidgetOperator->addItem(tr("Deg(x):弧度转角度"));
        ui->listWidgetOperator->addItem(tr("Rad(x):角度转弧度"));
        ui->listWidgetOperator->addItem(tr("Sqr(x):平方"));
        ui->listWidgetOperator->addItem(tr("Sqrt(x):平方根"));
        ui->listWidgetOperator->addItem(tr("Ceil(x):整数化(进位)"));
        ui->listWidgetOperator->addItem(tr("Floor(x):整数化(舍去)"));
        ui->listWidgetOperator->addItem(tr("Int(x):整数化(舍去小数)"));
        ui->listWidgetOperator->addItem(tr("Round(x):整数化(四舍五入)"));
        ui->listWidgetOperator->addItem(tr("Ln(x):自然对数"));
        ui->listWidgetOperator->addItem(tr("Lg(x):常用对数"));
    }else if(strTemp == "三角运算函数")
    {
        ui->listWidgetOperator->addItem(tr("Cos(x):佘弦"));
        ui->listWidgetOperator->addItem(tr("Sin(x):正弦"));
        ui->listWidgetOperator->addItem(tr("Tan(x):正切"));
        ui->listWidgetOperator->addItem(tr("Acos(x):反佘弦"));
        ui->listWidgetOperator->addItem(tr("Asin(x):反正弦"));
        ui->listWidgetOperator->addItem(tr("Atan(x):反正切"));
        ui->listWidgetOperator->addItem(tr("Atan(x,y):反正切(x,y)"));

    }else if(strTemp == "位运算")
    {
        ui->listWidgetOperator->addItem(tr("~:按位取反"));
        ui->listWidgetOperator->addItem(tr("&:按位与"));
        ui->listWidgetOperator->addItem(tr("|:按位或"));
        ui->listWidgetOperator->addItem(tr("Bxor(x,y):按位异或"));
    }

}
//运算符列表单击事件
void SSTaskEditCalculator::on_listWidgetOperator_itemClicked(QListWidgetItem *item)
{
    ui->txtDataFour->setText("");
    ui->txtDataOne->setText("");
    ui->txtDataThree->setText("");
    ui->txtDataTwo->setText("");

    ui->textBrowser->setText("");

    SetDataByOperator(ui->listWidgetOperatorType->currentRow(),ui->listWidgetOperator->currentRow());


    if (m_use_data_count == 1)
    {
        setBtnEnable(true,false,false,false);
    }else if(m_use_data_count == 2)
    {
        setBtnEnable(true,true,false,false);
    }else if(m_use_data_count == 3)
    {
        setBtnEnable(true,true,true,false);
    }else if(m_use_data_count == 4)
    {
        setBtnEnable(true,true,true,true);
    }


    ui->textBrowser->setText(strInfo);
}


void SSTaskEditCalculator::SetDataByOperator(int Op_type_index,int Op_index)
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

    m_str_operator_type = ui->listWidgetOperator->currentItem()->text().split(":")[0];
    m_use_data_count = str_operator_info[i_real_index].split(";")[1].toInt();
    strInfo = str_operator_info[i_real_index].split(";")[2];
}


//删除
void SSTaskEditCalculator::on_btnDel_clicked()
{
    int iIndex = ui->tableWidgetData->currentRow();

    if(iIndex >= 0)
    {
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("确定要删除本行数据？"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(rb == QMessageBox::Yes)
        {
            ui->tableWidgetData->removeRow(iIndex);
            DeletTableAndEditData(iIndex);
            iIndex = ui->tableWidgetData->currentRow();
            if(iIndex >=0)
            {
                QString strType = ui->tableWidgetData->item(iIndex,0)->text();
                FindOperator(strType);
                EditIniList();
            }

        }
    }else
    {
        QMessageBox::about(NULL,tr("提示"),tr("请选中要删除的行"));
    }
}
void SSTaskEditCalculator::DeletTableAndEditData(int index)
{
    int icount = ui->tableWidgetData->rowCount();
    int i =0;
    bool bEdit =false;
    for(i = index;i<icount;i++)
    {
        QString strType = ui->tableWidgetData->item(i,0)->text();
        QString strData1 = ui->tableWidgetData->item(i,1)->text();
        QString strData2 = ui->tableWidgetData->item(i,2)->text();

        QString strData1Temp1;
        QString strData1Temp2;
        strData1Temp1 = strData1;
        strData1Temp2 = strData2;
        bEdit =false;

        if(strData1 !="")
        {
            if(strData1.left(1)=="P")
            {
                bEdit = true;
                int icalc_item_index = strData1.mid(1,1).toInt();
                if((icalc_item_index-1) == index)
                {
                    strData1Temp1 = "PError";

                }else
                {
                    if(strData1 == "PError")
                        strData1Temp1 = "PError";
                    else
                        strData1Temp1 = "P"+QString::number(icalc_item_index-1)+"算式"+QString::number(icalc_item_index-1)+";"+"结果1";

                }
            }

        }
        if(strData2 !="")
        {
            if(strData2.left(1)=="P")
            {
                bEdit = true;

                int icalc_item_index = strData2.mid(1,1).toInt();

                if((icalc_item_index-1) == index)
                {
                    strData1Temp2 = "PError";

                }
                else
                {
                    if(strData2 == "PError")
                        strData1Temp2 = "PError";
                    else
                        strData1Temp2 = "P"+QString::number(icalc_item_index-1)+"算式"+QString::number(icalc_item_index-1)+";"+"结果1";

                }

            }
        }
        if(bEdit)
        {
            ui->tableWidgetData->item(i,0)->setText(strType);
            ui->tableWidgetData->item(i,1)->setText(strData1Temp1);
            ui->tableWidgetData->item(i,2)->setText(strData1Temp2);

        }
    }

}

//追加
void SSTaskEditCalculator::on_btnAdd_clicked()
{
    if(ui->tableWidgetData->rowCount()<40)
    {
        if(m_str_operator_type.isEmpty())
        {
            QMessageBox::about(NULL,tr("提示"),tr("请选中运算符"));
            return;
        }
        QString strData[4];
        strData[0] =ui->txtDataOne->text();
        strData[1] =ui->txtDataTwo->text();
        strData[2] =ui->txtDataThree->text();
        strData[3] =ui->txtDataFour->text();
        QString emptyIndex;
        for(int i = 0; i < m_use_data_count;i++)
        {
            if(strData[i].isEmpty())
            {
                emptyIndex.append(QString::number(i+1)+",");
            }
        }
        if(!emptyIndex.isEmpty())
        {
            QString strMessage = tr("请输入数据")+emptyIndex.left(emptyIndex.length()-1)+tr("文本框中的数据");
            QMessageBox::about(NULL,tr("提示"),strMessage);
            return;
        }

        if(DataIsInTable(m_str_operator_type,strData[0],strData[1],strData[2],strData[3]))
        {
            QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("列表中已存在相同的算式，确认追加？"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
            if(rb == QMessageBox::No)
            {
                return;
            }
        }

        AddDataToTable(m_str_operator_type,strData[0],strData[1],strData[2],strData[3]);
    }else
    {
        QMessageBox::about(NULL,tr("提示"),tr("已经到最大40行数据！"));
    }
}
//判断重复数据
bool SSTaskEditCalculator::DataIsInTable(QString strOperatorType,QString strData1,QString strData2,QString strData3,QString strData4)
{
    int icount = ui->tableWidgetData->rowCount();
    int i = 0;
    bool bRet = false;
    for (i = 0;i<icount;i++)
    {
        QString strType = ui->tableWidgetData->item(i,0)->text();
        QString data1 = ui->tableWidgetData->item(i,1)->text();
        QString data2 = ui->tableWidgetData->item(i,2)->text();
        QString data3 = ui->tableWidgetData->item(i,3)->text();
        QString data4 = ui->tableWidgetData->item(i,4)->text();

        if(strType == strOperatorType)
        {
            if(strData1 == data1)
            {
                if(data2 == strData2)
                {
                    if(data3 == strData3)
                    {
                        if(data4 == strData4)
                        {
                            bRet = true;
                            break;
                        }
                    }
                }
            }
        }
    }
    return bRet;
}

//向表格中增加数据
void SSTaskEditCalculator::AddDataToTable(QString strOperatorType,QString strData1,QString strData2,QString strData3,QString strData4)
{
    int icount = ui->tableWidgetData->rowCount();
    ui->tableWidgetData->setRowCount(icount + 1);//总行数增加1

    ui->tableWidgetData->setItem(icount, 0, new QTableWidgetItem(strOperatorType));
    ui->tableWidgetData->setItem(icount , 1, new QTableWidgetItem(strData1));
    ui->tableWidgetData->setItem(icount , 2, new QTableWidgetItem(strData2));
    ui->tableWidgetData->setItem(icount , 3, new QTableWidgetItem(strData3));
    ui->tableWidgetData->setItem(icount , 4, new QTableWidgetItem(strData4));

    ui->tableWidgetData->setItemSelected(ui->tableWidgetData->item(icount+1,1),true);
}
//修改表格中数据
void SSTaskEditCalculator::EditDataToTable(QString strOperatorType,QString strData1,QString strData2,QString strData3,QString strData4)
{
//    QModelIndex index =  ui->tableWidgetData->currentIndex();
    QList<QTableWidgetItem *> listItem = ui->tableWidgetData->selectedItems();

    if(listItem.count()==0)
        return;

    listItem[0]->setText(strOperatorType);
    listItem[1]->setText(strData1);
    listItem[2]->setText(strData2);
    listItem[3]->setText(strData3);
    listItem[4]->setText(strData4);

}
//修改确定
void SSTaskEditCalculator::on_btnEdit_clicked()
{
    int row = ui->tableWidgetData->currentRow();
    int column = ui->tableWidgetData->currentColumn();
    if(row > -1 && column < 5)
    {
        on_tableWidgetData_cellDoubleClicked(row,column);
    }
}
//数据1下拉框选择事件

void SSTaskEditCalculator::on_btnClear_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("确定要清空表格中的数据?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(rb == QMessageBox::Yes)
    {
        while(ui->tableWidgetData->rowCount() > 0)
        {
            ui->tableWidgetData->removeRow(0);
        }
        ui->txtDataOne->clear();
        ui->txtDataTwo->clear();
        ui->txtDataThree->clear();
        ui->txtDataFour->clear();
    }
}

//表格列表单击事件
void SSTaskEditCalculator::on_tableWidgetData_clicked(const QModelIndex &index)
{
    int irow = index.row();
    QString strType = ui->tableWidgetData->item(irow,0)->text();
    QString strData1 = ui->tableWidgetData->item(irow,1)->text();
    QString strData2 = ui->tableWidgetData->item(irow,2)->text();
    QString strData3 = ui->tableWidgetData->item(irow,3)->text();
    QString strData4 = ui->tableWidgetData->item(irow,4)->text();
    FindOperator(strType);
    EditIniList();

    ui->txtDataOne->setText(strData1);
    ui->txtDataTwo->setText(strData2);
    ui->txtDataThree->setText(strData3);
    ui->txtDataFour->setText(strData4);

}

void SSTaskEditCalculator::EditIniList()
{
    ui->listWidgetOperatorType->setCurrentRow(m_listTypeRow);
    QListWidgetItem *listType = ui->listWidgetOperatorType->item(m_listTypeRow);
    on_listWidgetOperatorType_itemClicked(listType);
    ui->listWidgetOperator->setCurrentRow(m_listOperatorRow);
    QListWidgetItem *listOper = ui->listWidgetOperator->item(m_listOperatorRow);
    on_listWidgetOperator_itemClicked(listOper);
}

void SSTaskEditCalculator::FindOperator(QString strType)
{
    int i_Index = 0;
    for(int i = 0; i < str_operator_info.count();i++)
    {
        if(strType == str_operator_info[i].split(";")[0])
        {
            i_Index = i;
            break;
        }
    }
    m_calc_operator = i_Index;
    m_use_data_count = str_operator_info[i_Index].split(";")[1].toInt();
    if(i_Index < 6)//算术运算符
    {
        m_listTypeRow = 0;
        m_calc_operator_type = CalcuatorData::CALCOP_TYPE_ARITHMETIC_OPERATOR;
        m_listOperatorRow = i_Index;
    }
    else if(i_Index >= 6  &&i_Index < 10)//逻辑运算符
    {
        m_listTypeRow = 1;
        m_calc_operator_type = CalcuatorData::CALCOP_TYPE_LOGICAL_OPERATOR;
        m_listOperatorRow = i_Index - 6;
    }
    else if(i_Index >= 10  &&i_Index < 20)//比较运算符
    {
        m_listTypeRow = 2;
        m_calc_operator_type = CalcuatorData::CALCOP_TYPE_COMPARE_OPERATOR;
        m_listOperatorRow = i_Index - 10;
    }
    else if(i_Index >= 20  &&i_Index < 31)//普通运算函数
    {
        m_listTypeRow = 3;
        m_calc_operator_type = CalcuatorData::CALCOP_TYPE_GENERAL_FUNCTION;
        m_listOperatorRow = i_Index - 20;
    }
    else if(i_Index >= 31  &&i_Index < 38)//三角运算函数
    {
        m_listTypeRow = 4;
        m_calc_operator_type = CalcuatorData::CALCOP_TYPE_TRIGONOMETRY_FUNCTION;
        m_listOperatorRow = i_Index - 31;
    }
    else if(i_Index >= 38  &&i_Index < 42)//位运算
    {
        m_listTypeRow = 5;
        m_calc_operator_type = CalcuatorData::CALCOP_TYPE_BIT_OPERATOR;
        m_listOperatorRow = i_Index - 38;
    }
}

QString SSTaskEditCalculator::GetOperator(int calc_operator)
{
    return str_operator_info[calc_operator].split(";")[0];
}

void SSTaskEditCalculator::Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color)
{
    m_currentStep = i_step_index;
//    CalcuatorData m_CalcuatorData;
    m_CalcuatorData.LoadPositionData(ptr, i_step_index, new_flag);
    QString str_data1 = "";
    QString str_data2 = "";
    QString str_data3 = "";
    QString str_data4 = "";
    //获取计算项个数
    int calc_item_cnt = m_CalcuatorData.GetCalcCount();
    int i = 0;
    for(i = 0; i < calc_item_cnt; i++)
    {
        //获取运算符类型
        int calc_main_type = m_CalcuatorData.GetMainType(i);
        m_calc_operator_type = calc_main_type;
        //获取运算符类型
        int calc_sub_type = m_CalcuatorData.GetSubType(i);
        //获取运算符字符串
        QString str_operator = GetOperator(calc_sub_type);
        //ui->tableWidgetData->item(i,0)->setText(str_operator);
        //列表添加空行
        AddDataToTable(str_operator,str_data1,str_data2,str_data3,str_data4);
        //获取数据来源
        //获取计算项参数个数
        int parma_cnt = m_CalcuatorData.GetOprandNum(i);
        int j = 0;
        for(j = 0; j < parma_cnt;j++)
        {
            //获取参数来源类型
            int param_source = m_CalcuatorData.GetParamType(i,j);
            if(param_source == CALC_DATA_MANUAL)//手动输入
            {
                //获取手动输入数据
                float input_data = m_CalcuatorData.GetManualInputValue(i,j);
                ui->tableWidgetData->item(i,j+1)->setText("I"+QString::number(input_data));
                //                m_data[j].strInputByHand = QString::number(input_data);
                //                m_data[j].dataKind = 0;

            }
            if(param_source == CALC_DATA_REF)//数据引用
            {
                //获取引用任务序号
                int task_index = (int)m_CalcuatorData.GetLinkDataStepIndex(i,j);
                //获取引用结果序号
                int index = (int)m_CalcuatorData.GetLinkDataResultIndex(i,j);
//                int result_index = m_CalcuatorData.GetResultID(task_index,index);
                int result_index;
                int i_result_num;
                result_index = m_CalcuatorData.NewGetResultID(&i_result_num,task_index,index)-1;
                QString task_str = m_CalcuatorData.GetTaskListString(task_index);
                if(i_result_num == -1)//不是多结果任务
                {
                    //获取任务序号对应的任务字符串
                    QString result_str;
                    //获取结果字符串
                    QStringList result_list = m_CalcuatorData.GetSendDataStringList(task_index,-1);
                    if(result_list.count() > result_index)
                    {
                        result_str = result_list[result_index];
                    }
                    ui->tableWidgetData->item(i,j+1)->setText("$"+task_str+";"+QString::number(result_index+1)+"."+result_str);
                }
                else //是多结果任务
                {
                    QStringList mul_result = m_CalcuatorData.GetTaskResultString(task_index);
                    //获取结果字符串
                    QStringList result_list = m_CalcuatorData.GetSendDataStringList(task_index,i_result_num);

                    QString result_str,data_str;
                    if(mul_result.count() > i_result_num)
                    {
                        data_str = mul_result[i_result_num];
                    }
                    if(result_list.count() > result_index && result_index >= 0)
                    {
                        result_str = result_list[result_index];
                    }
                    if(result_str.isEmpty())
                    {
                        ui->tableWidgetData->item(i,j+1)->setText("$"+task_str+";"+QString::number(i_result_num+1)+"."+data_str);
                    }
                    else
                    {
                        ui->tableWidgetData->item(i,j+1)->setText("$"+task_str+";"+QString::number(i_result_num+1)+"."+data_str+ \
                                                                  ";"+QString::number(result_index+1)+"."+result_str);
                    }
                }
            }
            if(param_source == CALC_DATA_MODBUS)//Modb数据
            {
                //获取Modbus寄存器类型
                int reg_type = (int)m_CalcuatorData.GetModbusRegType(i,j);
                //获取Modbus数据类型
                int data_type = (int)m_CalcuatorData.GetModbusDataType(i,j);
                //获取起始地址
                int address = m_CalcuatorData.GetModbusRegAddr(i,j);
                ui->tableWidgetData->item(i,j+1)->setText("M"+m_Modbus_reg_list[reg_type]+";" +m_Modbus_type_list[data_type]+";"+QString::number(address));

            }
            if(param_source == CALC_DATA_PRE_ITEM)//计算项结果
            {
                //获取计算项任务序号
                int calc_item_index = (int)m_CalcuatorData.GetItemIndex(i,j);
                //获取计算项的结果序号
                int calc_result_index = (int)m_CalcuatorData.GetItemResultIndex(i,j);
                ui->tableWidgetData->item(i,j+1)->setText("P"+QString::number(calc_item_index+1).append(".").append("算式").append(";").append(QString::number(calc_result_index+1)).append(".结果1"));

            }
            if(param_source == CALC_DATA_MIT_FX_PLC)//Modb数据
            {
                //获取Modbus寄存器类型
                //获取Modbus数据类型
                int data_type = (int)m_CalcuatorData.GetPLCDataType(i,j);
                if(data_type == 4)
                    data_type = 3;
                //获取起始地址
                int address = m_CalcuatorData.GetPLCRegAddr(i,j);
                ui->tableWidgetData->item(i,j+1)->setText("L"+m_pLc_type_list[data_type]+";"+QString::number(address));
            }

            if(param_source == CALC_DATA_DATA_INPUT)//数据输入
            {
                unsigned int address = m_CalcuatorData.GetDataInputAddr(i,j);
                unsigned int type = m_CalcuatorData.GetDataInputType(i,j);
                ui->tableWidgetData->item(i,j+1)->setText("D"+m_Data_Input+";"+QString::number(type)+";"+QString::number(address));
            }
            //AddDataToVector();
        }
    }
}

int SSTaskEditCalculator::Set_Parameter_To_Ram()
{
    QString NG_index;
    for(int i = 0;i<ui->tableWidgetData->rowCount();i++)
    {
        FindOperator(ui->tableWidgetData->item(i,0)->text());
        for(int j = 1; j < m_use_data_count+1; j++)
        {
            if(ui->tableWidgetData->item(i,j)->text().isEmpty())
            {
                NG_index.append(QString::number(i+1)+",");
                break;
            }
        }
    }
    if(!NG_index.isEmpty())
    {
        QString str_message = tr("第")+NG_index.left(NG_index.length()-1)+tr("条算式存在空参数,请修改对应空参数后再执行该操作");
        QMessageBox::warning(NULL, tr("警告"), str_message, QMessageBox::Ok);
        return 0;
    }
    if(ui->tableWidgetData->rowCount() == 0)
    {
        QMessageBox::warning(NULL, tr("警告"), tr("请至少追加一条计算式！"), QMessageBox::Ok);
        return 0;
    }
    if(IsTableErrorData())
        return 0;
    SendDataToMonkeyLib();
    m_CalcuatorData.LearnStart(m_currentStep);
    m_b_flag = true;
    return 1;
}

void SSTaskEditCalculator::on_tableWidgetData_cellDoubleClicked(int row, int column)
{
    QString strData = ui->tableWidgetData->item(row,column)->text();
    int ret;
    QString strData1,strData2,strData3,strData4,strType;
    strType = ui->tableWidgetData->item(row,0)->text();
    strData1 = ui->tableWidgetData->item(row,1)->text();
    strData2 = ui->tableWidgetData->item(row,2)->text();
    strData3 = ui->tableWidgetData->item(row,3)->text();
    strData4 = ui->tableWidgetData->item(row,4)->text();

//    if(strData != "")
    if(column <= m_use_data_count)
    {
        if(column == 0)//修改运算符
        {
            m_CalcOperatorSelectDialog->InitOperatorInfo(str_operator_info);
            ret = m_CalcOperatorSelectDialog->exec();

            if(ret == QDialog::Accepted)
            {
                if(DataIsInTable(m_CalcOperatorSelectDialog->m_str_operator_type,strData1,strData2,strData3,strData4))
                {
                    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("列表中已存在相同的算式，确认修改？"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
                    if(rb == QMessageBox::No)
                    {
                        return;
                    }
                }
               ui->tableWidgetData->item(row,column)->setText(m_CalcOperatorSelectDialog->m_str_operator_type);
               FindOperator(m_CalcOperatorSelectDialog->m_str_operator_type);
               setCellClear(m_use_data_count);

            }
        }else//修改数据
        {
            CalcDataSelectDialog *p_CalcDataSelectDialog = new CalcDataSelectDialog();
            if(strData.isEmpty())
            {
                p_CalcDataSelectDialog->m_input_str = strData.right(strData.length()-1);
                p_CalcDataSelectDialog->InitDataSelect(CALC_DATA_MANUAL-1,row,m_currentStep);
            }
            if(strData.left(1) == "I")
            {
                p_CalcDataSelectDialog->m_input_str = strData.right(strData.length()-1);
                p_CalcDataSelectDialog->InitDataSelect(CALC_DATA_MANUAL-1,row,m_currentStep);
            }else if(strData.left(1) == "$")
            {
                p_CalcDataSelectDialog->InitDataSelect(CALC_DATA_REF-1,row,m_currentStep);
            }else if(strData.left(1) == "M")
            {
                p_CalcDataSelectDialog->InitDataSelect(CALC_DATA_MODBUS-1,row,m_currentStep);

            }else if(strData.left(1) == "P")
            {
                p_CalcDataSelectDialog->InitDataSelect(CALC_DATA_PRE_ITEM-1,row,m_currentStep);
            }
            else if(strData.left(1) == "L")
            {
                p_CalcDataSelectDialog->InitDataSelect(CALC_DATA_MIT_FX_PLC-1,row,m_currentStep);
            }
            else if(strData.left(1) == "D")
            {
                p_CalcDataSelectDialog->InitDataSelect(CALC_DATA_DATA_INPUT-1,row,m_currentStep);
            }
            ret = p_CalcDataSelectDialog->exec();
            if(ret == QDialog::Accepted)
            {
                QString strInPutData = "";

                if(p_CalcDataSelectDialog->m_data_source == 0)
                    strInPutData = p_CalcDataSelectDialog->m_input_str;
                if(p_CalcDataSelectDialog->m_data_source == 1)
                    strInPutData = p_CalcDataSelectDialog->m_task_str;
                if(p_CalcDataSelectDialog->m_data_source == 2)
                    strInPutData = "M"+m_Modbus_reg_list[p_CalcDataSelectDialog->m_reg_type]+";"
                            +m_Modbus_type_list[p_CalcDataSelectDialog->m_data_type]+";"
                            +QString::number(p_CalcDataSelectDialog->m_address);
                if(p_CalcDataSelectDialog->m_data_source == 3)
                    strInPutData =  p_CalcDataSelectDialog->m_calc_str;
//                if(p_CalcDataSelectDialog->m_data_source == 4)
//                {
//                    strInPutData = "L" + m_pLc_type_list[p_CalcDataSelectDialog->m_plc_data_type]+";"
//                            +QString::number(p_CalcDataSelectDialog->m_plc_address);
//                }
                if(p_CalcDataSelectDialog->m_data_source == 5){
                    strInPutData = "D" + m_Data_Input+";"+QString::number(p_CalcDataSelectDialog->Data_Input_Type)+";"+QString::number(p_CalcDataSelectDialog->Data_Input_Addr);
                }

                 if(column == 1)
                 {
                    strData1 =  strInPutData;
                 }else if(column ==2)
                 {
                     strData2 = strInPutData;
                 }else if(column ==3)
                 {
                     strData3 = strInPutData;
                 }else if(column ==4)
                 {
                     strData4 = strInPutData;
                 }
                 if(DataIsInTable(strType ,strData1,strData2,strData3,strData4))
                 {
                     QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("警告"), tr("列表中已存在相同的算式，确认修改？"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
                     if(rb == QMessageBox::No)
                     {
                         return;
                     }
                 }

                ui->tableWidgetData->item(row,column)->setText(strInPutData);

                ui->txtDataOne->setText(strData1);
                ui->txtDataTwo->setText(strData2);
                ui->txtDataThree->setText(strData3);
                ui->txtDataFour->setText(strData4);

            }
            if(p_CalcDataSelectDialog != NULL)
            {
                delete p_CalcDataSelectDialog;
                p_CalcDataSelectDialog = NULL;
            }
        }
    }
}
void SSTaskEditCalculator::SendDataToMonkeyLib()
{
//    CalcuatorData m_CalcuatorData;
    m_CalcuatorData.CleanData();
    int count = ui->tableWidgetData->rowCount();
    m_CalcuatorData.SetCalcCount(count);
    int i = 0;
    for(i = 0; i<count;i++)
    {
        m_CalcuatorData.SetSelectFlag(i,true);
        //m_CalcuatorData.SetMainType();
        QString strType = ui->tableWidgetData->item(i,0)->text();
        QString strData1 = ui->tableWidgetData->item(i,1)->text();
        QString strData2 = ui->tableWidgetData->item(i,2)->text();
        QString strData3 = ui->tableWidgetData->item(i,3)->text();
        QString strData4 = ui->tableWidgetData->item(i,4)->text();
        FindOperator(strType);
        m_CalcuatorData.SetMainType(i,m_calc_operator_type);
        m_CalcuatorData.SetSubType(i,m_calc_operator);
        m_CalcuatorData.SetOprandNum(i,m_use_data_count);

        if(strData1 !="")
            AnalysisAndSetDataToLib(strData1,i,0);
        if(strData2 !="")
            AnalysisAndSetDataToLib(strData2,i,1);
        if(strData3 !="")
            AnalysisAndSetDataToLib(strData3,i,2);
        if(strData4 !="")
            AnalysisAndSetDataToLib(strData4,i,3);

    }
}
void SSTaskEditCalculator::AnalysisAndSetDataToLib(QString strData,int iTableIndex,int DataIndex)
{
    QString strInputType = strData.left(1);
//    CalcuatorData m_CalcuatorData;
    if(strInputType == "I")
    {
        QString data = strData.mid(1,strData.length()-1);
        float fdata = data.toFloat();
        m_CalcuatorData.SetParamType(iTableIndex,DataIndex,CALC_DATA_MANUAL);
        m_CalcuatorData.SetManualInputValue(iTableIndex,DataIndex,fdata);

    }else if(strInputType == "M")
    {
        m_CalcuatorData.SetParamType(iTableIndex,DataIndex,CALC_DATA_MODBUS);
        int i_reg_type;//Modbus寄存器类型
        int i_data_type;// Modbus数据类型
        int i_address;//Modbus 起始地址
        i_reg_type = strData.mid(1,1).toInt()-1;
        QStringList strListM = strData.split(";");
        QString strDataType = strListM[1];
        int index = strDataType.indexOf(".");
        i_data_type = strDataType.left(index).toInt() -1;
        i_address = strListM[2].toInt();
        m_CalcuatorData.SetModbusRegType(iTableIndex,DataIndex,i_reg_type);
        m_CalcuatorData.SetModbusDataType(iTableIndex,DataIndex,i_data_type);
        m_CalcuatorData.SetModbusRegAddr(iTableIndex,DataIndex,i_address);

    }else if(strInputType == "$")
    {
        m_CalcuatorData.SetParamType(iTableIndex,DataIndex,CALC_DATA_REF);
        int i_task_index;//数据引用任务索引
        int i_result_index;// 数据引用结果索引
        int i_data_index;

        QStringList  strList = strData.split(";");
        QString strTask = strList[0];
        int index = strTask.indexOf(".");
        i_task_index = strTask.mid(1,index-1).toInt();
        int flag = m_CalcuatorData.GetTaskTypeFlag(i_task_index);
        if(flag != 0)//引用的是多结果任务
        {
            if(strList.count() == 3)
            {

                QString str_data_index = strList[2];
                index = str_data_index.indexOf(".");
                i_data_index = str_data_index.left(index).toInt()-1;

                QString str_result_index = strList[1];
                index = str_result_index.indexOf(".");
                i_result_index = m_CalcuatorData.NewSetResultID(i_task_index,str_result_index.left(index).toInt()-1,i_data_index);
            }else{
                QString str_data_index = strList[1];
                index = str_data_index.indexOf(".");
                i_data_index = str_data_index.left(index).toInt()-1;
                i_result_index = m_CalcuatorData.NewSetResultID(i_task_index,0,i_data_index);
            }
            m_CalcuatorData.SetLinkDataStepIndex(iTableIndex,DataIndex,i_task_index);

            m_CalcuatorData.SetLinkDataResultIndex(iTableIndex,DataIndex,i_result_index);
        }else
        {
            QString str_result_index = strList[1];
            index = str_result_index.indexOf(".");

            i_result_index = m_CalcuatorData.NewSetResultID(i_task_index, -1, str_result_index.left(index).toInt()-1);
            m_CalcuatorData.SetLinkDataStepIndex(iTableIndex,DataIndex,i_task_index);

            m_CalcuatorData.SetLinkDataResultIndex(iTableIndex,DataIndex,i_result_index);
        }

    }else if(strInputType == "P")
    {
        m_CalcuatorData.SetParamType(iTableIndex,DataIndex,CALC_DATA_PRE_ITEM);
        int i_calc_item_index;//计算项索引
        int i_calc_result_index;//计算项结果索引（现在都为1）
        i_calc_result_index = 0;
        QStringList  strList = strData.split(";");
        QString strCalCitem = strList[0];
        int index = strCalCitem.indexOf(".");
        i_calc_item_index = strCalCitem.mid(1,index-1).toInt()-1;


        m_CalcuatorData.SetItemIndex(iTableIndex,DataIndex,i_calc_item_index);
        m_CalcuatorData.SetItemResultIndex(iTableIndex,DataIndex,i_calc_result_index);
    }else if(strInputType == "L")
    {
        m_CalcuatorData.SetParamType(iTableIndex,DataIndex,CALC_DATA_MIT_FX_PLC);
        int i_data_type;// Modbus数据类型
        int i_address;//Modbus 起始地址
        QStringList strListM = strData.split(";");
        QString strDataType = strListM[0];
        i_data_type = strDataType.mid(1,1).toInt() -1;
        if(i_data_type == 2)
            i_data_type = 3;
        i_address = strListM[1].toInt();
        m_CalcuatorData.SetPLCDataType(iTableIndex,DataIndex,i_data_type);
        m_CalcuatorData.SetPLCRegAddr(iTableIndex,DataIndex,i_address);
    }else if(strInputType == "D")
    {
        unsigned int addr;
        unsigned int type;
        QStringList strListD = strData.split(";");
        QString Str_Type = strListD.at(1);
        QString Str_addr = strListD.at(2);
        addr = Str_addr.toUInt();
        type = Str_Type.toUInt();
        m_CalcuatorData.SetParamType(iTableIndex,DataIndex,CALC_DATA_DATA_INPUT);
        m_CalcuatorData.SetDataInputType(iTableIndex, DataIndex,type);
        m_CalcuatorData.SetDataInputAddr(iTableIndex, DataIndex,addr);
    }
}
bool SSTaskEditCalculator::IsTableErrorData()
{
    int count = ui->tableWidgetData->rowCount();
    int i = 0;
    bool bFlag;
    bFlag = false;
    QString strTemp;
    strTemp = "表格第";
    int iNum = 0;
    for(i = 0; i<count;i++)
    {
        QString strData1 = ui->tableWidgetData->item(i,1)->text();
        QString strData2 = ui->tableWidgetData->item(i,2)->text();
        QString str = "";
        if(strData1 == "PError")
        {
            str = QString::number(i+1);
            bFlag = true;
        }
        if(strData2 =="PError")
        {
            bFlag = true;
            str = QString::number(i+1);
        }
        if(str !="")
        {
            iNum++;
            if(iNum > 1)
            {
                strTemp +=",";
            }
            strTemp +=str;
        }

    }
    if(bFlag)
    {
        strTemp+="行中存在错误数据，请处理!" ;
        QMessageBox::about(NULL,tr("提示"),strTemp);
    }

    return bFlag;

}
bool SSTaskEditCalculator::IsDataFloat(QString strData)
{
    bool bOk;

   float fData = strData.toFloat(&bOk);

   return bOk;

}

void SSTaskEditCalculator::on_btnDataOne_clicked()
{
    CalcDataSelectDialog *p_CalcDataSelectDialog = new CalcDataSelectDialog();
    p_CalcDataSelectDialog->InitDataSelect(0,ui->tableWidgetData->rowCount(),m_currentStep);
    int ret = p_CalcDataSelectDialog->exec();
    if(ret == QDialog::Accepted)
    {
        printf("p_CalcDataSelectDialog->m_data_source === %d\n",p_CalcDataSelectDialog->m_data_source);
        if(p_CalcDataSelectDialog->m_data_source == 0)
            ui->txtDataOne->setText(p_CalcDataSelectDialog->m_input_str);
        if(p_CalcDataSelectDialog->m_data_source == 1)
            ui->txtDataOne->setText(p_CalcDataSelectDialog->m_task_str);
        if(p_CalcDataSelectDialog->m_data_source == 3)
            ui->txtDataOne->setText(p_CalcDataSelectDialog->m_calc_str);
        if(p_CalcDataSelectDialog->m_data_source == 2)
        {
            ui->txtDataOne->setText("M"+m_Modbus_reg_list[p_CalcDataSelectDialog->m_reg_type]+";"
                    +m_Modbus_type_list[p_CalcDataSelectDialog->m_data_type]+";"
                    +QString::number(p_CalcDataSelectDialog->m_address));
        }
        if(p_CalcDataSelectDialog->m_data_source == 4)
        {
            ui->txtDataOne->setText("L" + m_pLc_type_list[p_CalcDataSelectDialog->m_plc_data_type]+";"
                    +QString::number(p_CalcDataSelectDialog->m_plc_address));
        }
        if(p_CalcDataSelectDialog->m_data_source == 5){
            ui->txtDataOne->setText("D" + m_Data_Input+";"+QString::number(p_CalcDataSelectDialog->Data_Input_Type)+";"+QString::number(p_CalcDataSelectDialog->Data_Input_Addr));
        }
    }
    if(p_CalcDataSelectDialog !=NULL)
    {
        delete p_CalcDataSelectDialog;
        p_CalcDataSelectDialog = NULL;
    }
}

void SSTaskEditCalculator::on_btnDataTwo_clicked()
{
    CalcDataSelectDialog *p_CalcDataSelectDialog = new CalcDataSelectDialog();
    p_CalcDataSelectDialog->InitDataSelect(0,ui->tableWidgetData->rowCount(),m_currentStep);
    int ret = p_CalcDataSelectDialog->exec();
    if(ret == QDialog::Accepted)
    {
        if(p_CalcDataSelectDialog->m_data_source == 0)
            ui->txtDataTwo->setText(p_CalcDataSelectDialog->m_input_str);
        if(p_CalcDataSelectDialog->m_data_source == 1)
            ui->txtDataTwo->setText(p_CalcDataSelectDialog->m_task_str);
        if(p_CalcDataSelectDialog->m_data_source == 3)
            ui->txtDataTwo->setText(p_CalcDataSelectDialog->m_calc_str);
        if(p_CalcDataSelectDialog->m_data_source == 2)
        {
            ui->txtDataTwo->setText("M"+m_Modbus_reg_list[p_CalcDataSelectDialog->m_reg_type]+";"
                    +m_Modbus_type_list[p_CalcDataSelectDialog->m_data_type]+";"
                    +QString::number(p_CalcDataSelectDialog->m_address));
        }
        if(p_CalcDataSelectDialog->m_data_source == 4)
        {
            ui->txtDataTwo->setText("L" + m_pLc_type_list[p_CalcDataSelectDialog->m_plc_data_type]+";"
                    +QString::number(p_CalcDataSelectDialog->m_plc_address));
        }
        if(p_CalcDataSelectDialog->m_data_source == 5){
            ui->txtDataTwo->setText("D" + m_Data_Input+";"+QString::number(p_CalcDataSelectDialog->Data_Input_Type)+";"+QString::number(p_CalcDataSelectDialog->Data_Input_Addr));
        }
    }
    if(p_CalcDataSelectDialog !=NULL)
    {
        delete p_CalcDataSelectDialog;
        p_CalcDataSelectDialog = NULL;
    }
}

void SSTaskEditCalculator::on_btnDataThree_clicked()
{
    CalcDataSelectDialog *p_CalcDataSelectDialog = new CalcDataSelectDialog();
    p_CalcDataSelectDialog->InitDataSelect(0,ui->tableWidgetData->rowCount(),m_currentStep);
    int ret = p_CalcDataSelectDialog->exec();
    if(ret == QDialog::Accepted)
    {
        if(p_CalcDataSelectDialog->m_data_source == 0)
            ui->txtDataThree->setText(p_CalcDataSelectDialog->m_input_str);
        if(p_CalcDataSelectDialog->m_data_source == 1)
            ui->txtDataThree->setText(p_CalcDataSelectDialog->m_task_str);
        if(p_CalcDataSelectDialog->m_data_source == 3)
            ui->txtDataThree->setText(p_CalcDataSelectDialog->m_calc_str);
        if(p_CalcDataSelectDialog->m_data_source == 2)
        {
            ui->txtDataThree->setText("M"+m_Modbus_reg_list[p_CalcDataSelectDialog->m_reg_type]+";"
                    +m_Modbus_type_list[p_CalcDataSelectDialog->m_data_type]+";"
                    +QString::number(p_CalcDataSelectDialog->m_address));
        }
        if(p_CalcDataSelectDialog->m_data_source == 4)
        {
            ui->txtDataThree->setText("L" + m_pLc_type_list[p_CalcDataSelectDialog->m_plc_data_type]+";"
                    +QString::number(p_CalcDataSelectDialog->m_plc_address));
        }
        if(p_CalcDataSelectDialog->m_data_source == 5){
            ui->txtDataThree->setText("D" + m_Data_Input +";"+QString::number(p_CalcDataSelectDialog->Data_Input_Type)+";"+QString::number(p_CalcDataSelectDialog->Data_Input_Addr));
        }
    }
    if(p_CalcDataSelectDialog !=NULL)
    {
        delete p_CalcDataSelectDialog;
        p_CalcDataSelectDialog = NULL;
    }
}

void SSTaskEditCalculator::on_btnDataFour_clicked()
{
    CalcDataSelectDialog *p_CalcDataSelectDialog = new CalcDataSelectDialog();
    p_CalcDataSelectDialog->InitDataSelect(0,ui->tableWidgetData->rowCount(),m_currentStep);
    int ret = p_CalcDataSelectDialog->exec();
    if(ret == QDialog::Accepted)
    {
        if(p_CalcDataSelectDialog->m_data_source == 0)
            ui->txtDataFour->setText(p_CalcDataSelectDialog->m_input_str);
        if(p_CalcDataSelectDialog->m_data_source == 1)
            ui->txtDataFour->setText(p_CalcDataSelectDialog->m_task_str);
        if(p_CalcDataSelectDialog->m_data_source == 3)
            ui->txtDataFour->setText(p_CalcDataSelectDialog->m_calc_str);
        if(p_CalcDataSelectDialog->m_data_source == 2)
        {
            ui->txtDataFour->setText("M"+m_Modbus_reg_list[p_CalcDataSelectDialog->m_reg_type]+";"
                    +m_Modbus_type_list[p_CalcDataSelectDialog->m_data_type]+";"
                    +QString::number(p_CalcDataSelectDialog->m_address));
        }
        if(p_CalcDataSelectDialog->m_data_source == 4)
        {
            ui->txtDataFour->setText("L" + m_pLc_type_list[p_CalcDataSelectDialog->m_plc_data_type]+";"
                    +QString::number(p_CalcDataSelectDialog->m_plc_address));
        }
        if(p_CalcDataSelectDialog->m_data_source == 5){
            ui->txtDataFour->setText("D" + m_Data_Input+";"+QString::number(p_CalcDataSelectDialog->Data_Input_Type)+";"+QString::number(p_CalcDataSelectDialog->Data_Input_Addr));
        }
    }
    if(p_CalcDataSelectDialog !=NULL)
    {
        delete p_CalcDataSelectDialog;
        p_CalcDataSelectDialog = NULL;
    }
}
