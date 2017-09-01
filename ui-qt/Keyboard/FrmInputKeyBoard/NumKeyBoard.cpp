#include <QDebug>
#include "NumKeyBoard.h"
#include "ui_NumKeyBoard.h"
#include "stdio.h"
#include <QMessageBox>

NumKeyBoard::NumKeyBoard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NumKeyBoard)
{
    ui->setupUi(this);
    b_IP = false;
    this->strNum = "";
    ui->txtNum->setText("");
    ui->btnRangeEn->setVisible(false);
//    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

}


NumKeyBoard::~NumKeyBoard()
{
    delete ui;
}

void NumKeyBoard::ShowbtnRangeEn()
{
    ui->btnRangeEn->setVisible(true);
}

void NumKeyBoard::SetNum(QString str_Num)
{
   ui->txtNum->setText(str_Num);
   this->strNum = str_Num;
}


void NumKeyBoard::RangeInput(QString max,QString min,int flag)
{
    m_flag = flag;
    if(flag == 1)
    {
        strNum = max;
        strCmp = min;
    }else
    {
        strNum = min;
        strCmp = max;
    }
    if(strNum.contains("."))
    {
        float num = strNum.toFloat();
        if(flag == 1)
        {
            this->strNum = QString::number(qRound(num+0.5),'f',3);
        }
        else
        {
            this->strNum = QString::number(qRound(num-0.5),'f',3);
        }
    }
    else
    {
        if(strNum == "---")
        {
            strNum = "";
        }
    }
    ui->txtNum->setText(strNum);
    ui->txtNum->selectAll();
}


void NumKeyBoard::SetOldNum(QString str_Num)
{
    ui->txtNum->setText(str_Num);
    this->strNum = str_Num;
}

void NumKeyBoard::InputIp()
{
    b_IP = true;
}

QString NumKeyBoard::GetNum()
{
//    return ui->txtNum->text();
    return strNum;
}


QString NumKeyBoard::GetRangeNum()
{
    if(m_flag == 0)
    {
        if(strNum == "---"){
            return strNum;
        }
        else if(strCmp != "---")
        {
            if(strCmp.contains("."))
            {
                QString num = strNum.split(".")[0];
                if(num.length() > 8)
                {
                    strNum = strCmp;
                }
                else if(strNum.toFloat() > strCmp.toFloat())
                {
                    strNum = strCmp;
                }
                return strNum;
            }else
            {
                if(strNum.length() > 8)
                {
                    strNum = strCmp;
                }else if(strNum.toInt() > strCmp.toInt())
                {
                    strNum = strCmp;
                }
                return strNum;
            }
        }
        else if(strCmp == "---"){
            if(strNum.contains("."))
            {
                QString num = strNum.split(".")[0];
                if(num.length() > 8)
                {
                    strNum = "9999999.999";
                    return strNum;
                }else
                {
                    return strNum;
                }
            }else if(strNum.length() > 8)
            {
                strNum = "99999999";
                return strNum;
            }else
            {
                return strNum;
            }
        }
    }
    if(m_flag == 1)
    {
        if(strNum == "---"){
            return strNum;
        }
        else if(strCmp != "---")
        {
            if(strCmp.contains("."))
            {
                QString num = strNum.split(".")[0];
                if(num.length() > 8)
                {
                    strNum = strCmp;
                }
                else if(strNum.toFloat() < strCmp.toFloat())
                {
                    strNum = strCmp;
                }
                return strNum;
            }else
            {
                if(strNum.length() > 8)
                {
                    strNum = strCmp;
                }else if(strNum.toInt() < strCmp.toInt())
                {
                    strNum = strCmp;
                }
                return strNum;
            }
        }
        else if(strCmp == "---")
        {
            if(strNum.contains("."))
            {
                QString num = strNum.split(".")[0];
                printf("num = %s\r\n",num.toLatin1().data());
                if(num.length() > 8)
                {
                    strNum = "9999999.999";
                    return strNum;
                }else
                {
                    return strNum;
                }
            }else if(strNum.length() > 8)
            {
                strNum = "99999999";
                return strNum;
            }else
            {
                return strNum;
            }
        }
    }
    return strNum;
}

void NumKeyBoard::SetNaturalNumberInputMode(bool b_value)
{
    ui->btnNegative->setEnabled(!b_value);
    ui->btnSpot->setEnabled(!b_value);
}

void NumKeyBoard::SelectTextReplace(QPushButton *object)
{
    int i_len = ui->txtNum->selectedText().length();
    int i_cus_pos = 0;
    if(i_len != 0)/*如果选中字符的长度不为零*/
    {
        i_cus_pos = ui->txtNum->selectionStart();
        if(object == ui->btnBack)
        {
            /*将选中的字符删除，光标位置不变*/
            strNum.replace(i_cus_pos,i_len,"");
        }
        else
        {
            /*将选中的字符替换为按键内容，光标位置往前移动一位*/
            strNum.replace(i_cus_pos,i_len,object->text());
            i_cus_pos++;
        }
    }else /*如果选中字符长度为零，即没有选中任何字符*/
    {
        i_cus_pos = ui->txtNum->cursorPosition();
        if(object == ui->btnBack)
        {
            /*删除光标前的一个字符，光标位置后移一位*/
            strNum.replace(i_cus_pos-1,1,"");
            i_cus_pos--;
        }
        else
        {
            /*在光标位置插入按键内容，光标位置往前移一位*/
            strNum.insert(i_cus_pos,object->text());
            i_cus_pos++;
        }
    }
    ui->txtNum->setText(strNum);
    ui->txtNum->setCursorPosition(i_cus_pos);
}

void NumKeyBoard::on_btn1_clicked()
{
    SelectTextReplace(ui->btn1);
}

void NumKeyBoard::on_btn2_clicked()
{
    SelectTextReplace(ui->btn2);
}

void NumKeyBoard::on_btn3_clicked()
{
    SelectTextReplace(ui->btn3);
}

void NumKeyBoard::on_btn4_clicked()
{
    SelectTextReplace(ui->btn4);
}

void NumKeyBoard::on_btn5_clicked()
{
    SelectTextReplace(ui->btn5);
}

void NumKeyBoard::on_btn6_clicked()
{
    SelectTextReplace(ui->btn6);
}

void NumKeyBoard::on_btn7_clicked()
{
    SelectTextReplace(ui->btn7);
}

void NumKeyBoard::on_btn8_clicked()
{
    SelectTextReplace(ui->btn8);
}

void NumKeyBoard::on_btn9_clicked()
{
    SelectTextReplace(ui->btn9);
}

void NumKeyBoard::on_btnSpot_clicked()
{
    if(ui->txtNum->text().length() > 0)
    {
        if(b_IP)
        {
            SelectTextReplace(ui->btnSpot);
        }
        else if(!strNum.contains("."))
        {
            SelectTextReplace(ui->btnSpot);
        }
    }
}

void NumKeyBoard::on_btn0_clicked()
{
    SelectTextReplace(ui->btn0);
}

void NumKeyBoard::on_btnNegative_clicked()
{
    if(ui->txtNum->text() == "" || ui->txtNum->selectedText() == ui->txtNum->text())
    {
        strNum = "-";
        ui->txtNum->setText(strNum);
    }
}

void NumKeyBoard::on_btnClear_clicked()
{
    strNum = "";
    ui->txtNum->setText(strNum);
}

void NumKeyBoard::on_btnBack_clicked()
{
    SelectTextReplace(ui->btnBack);
}

void NumKeyBoard::on_btnOk_clicked()
{
    if(ui->txtNum->text()=="")
    {
        QMessageBox::about(NULL,tr("警告"),tr("请输入正确的数字"));
        return;
    }
    else if(ui->txtNum->text() == "-")
    {
        QMessageBox::about(NULL,tr("警告"),tr("请输入正确的数字"));
        return ;
    }else if(ui->txtNum->text().left(1) == ".")
    {
        QMessageBox::about(NULL,tr("警告"),tr("请输入正确的数字"));
        return;
    }else if(ui->txtNum->text().right(1)==".")
    {
        QMessageBox::about(NULL,tr("警告"),tr("请输入正确的数字"));
        return;
    }else
    {
        if(ui->txtNum->text().length() >= 2)
        {
          if(ui->txtNum->text().left(2) == "-.")
          {
              QMessageBox::about(NULL,tr("警告"),tr("请输入正确的数字"));
              return;
          }
        }
    }
    QDialog::accept();
}

void NumKeyBoard::on_btnQuit_clicked()
{
    QDialog::reject();
}


void NumKeyBoard::on_btnRangeEn_clicked()
{
    strNum.clear();
    strNum = "---";
    QDialog::accept();
}

void NumKeyBoard::on_txtNum_selectionChanged()
{
    m_StrSelect = ui->txtNum->selectedText();
}

