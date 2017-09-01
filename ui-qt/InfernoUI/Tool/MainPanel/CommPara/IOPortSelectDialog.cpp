#include "IOPortSelectDialog.h"
#include "ui_IOPortSelectDialog.h"
#include <stdio.h>
IOPortSelectDialog::IOPortSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IOPortSelectDialog)
{
    ui->setupUi(this);
    m_radioNull_x = ui->IONullradioButton->pos().x();
    m_radioNull_y = ui->IONullradioButton->pos().y();
    Widget_Height = this->height();
    IO_Data.insert(ui->IO1radioButton, 1);
    IO_Data.insert(ui->IO2radioButton, 2);
    IO_Data.insert(ui->IO3radioButton, 3);
    IO_Data.insert(ui->IO4radioButton, 4);
    IO_Data.insert(ui->IO5radioButton, 5);
    IO_Data.insert(ui->IO6radioButton, 6);
    IO_Data.insert(ui->IO7radioButton, 7);
    IO_Data.insert(ui->IO8radioButton, 8);
    IO_Data.insert(ui->IO9radioButton, 9);
    IO_Data.insert(ui->IO10radioButton, 10);
    IO_Data.insert(ui->IO11radioButton, 11);
    IO_Data.insert(ui->IO12radioButton, 12);
    IO_Data.insert(ui->IO13radioButton, 13);
    IO_Data.insert(ui->IO14radioButton, 14);
    IO_Data.insert(ui->IO15radioButton, 15);
    IO_Data.insert(ui->IONullradioButton, 0);
}

IOPortSelectDialog::~IOPortSelectDialog()
{
    delete ui;
}

void IOPortSelectDialog::SetModel(int flag, int io_port)
{
    if(flag == 0)
    {
        ui->IONullradioButton->move(ui->IO5radioButton->pos().x(), ui->IO5radioButton->pos().y());
        ui->IO5radioButton->setHidden(true);
        ui->IO6radioButton->setHidden(true);
        ui->IO7radioButton->setHidden(true);
        ui->IO8radioButton->setHidden(true);
        ui->IO9radioButton->setHidden(true);
        ui->IO10radioButton->setHidden(true);
        ui->IO11radioButton->setHidden(true);
        ui->IO12radioButton->setHidden(true);
        ui->IO13radioButton->setHidden(true);
        ui->IO14radioButton->setHidden(true);
        ui->IO15radioButton->setHidden(true);
        this->setFixedHeight(Widget_Height/2);
    }
    else
    {
        ui->IONullradioButton->move(m_radioNull_x, m_radioNull_y);
        ui->IO5radioButton->setVisible(true);
        ui->IO6radioButton->setVisible(true);
        ui->IO7radioButton->setVisible(true);
        ui->IO8radioButton->setVisible(true);
        ui->IO9radioButton->setVisible(true);
        ui->IO10radioButton->setVisible(true);
        ui->IO11radioButton->setVisible(true);
        ui->IO12radioButton->setVisible(true);
        ui->IO13radioButton->setVisible(true);
        ui->IO14radioButton->setVisible(true);
        ui->IO15radioButton->setVisible(true);
        this->setFixedHeight(Widget_Height);
    }
    if(io_port > 0 && io_port < 16)
        IO_Data.key(io_port)->setEnabled(false);
}

void IOPortSelectDialog::on_IO1radioButton_clicked()
{
    text = ui->IO1radioButton->text();
    Port = 1;
    QDialog::accept();
}

void IOPortSelectDialog::on_IO2radioButton_clicked()
{
    text = ui->IO2radioButton->text();
    Port = 2;
    QDialog::accept();
}

void IOPortSelectDialog::on_IO3radioButton_clicked()
{
    text = ui->IO3radioButton->text();
    Port = 3;
    QDialog::accept();
}

void IOPortSelectDialog::on_IO4radioButton_clicked()
{
    text = ui->IO4radioButton->text();
    Port = 4;
    QDialog::accept();
}

void IOPortSelectDialog::on_IO5radioButton_clicked()
{
    text = ui->IO5radioButton->text();
    Port = 5;
    QDialog::accept();
}

void IOPortSelectDialog::on_IO6radioButton_clicked()
{
    text = ui->IO6radioButton->text();
    Port = 6;
    QDialog::accept();
}

void IOPortSelectDialog::on_IO7radioButton_clicked()
{
    text = ui->IO7radioButton->text();
    Port = 7;
    QDialog::accept();
}

void IOPortSelectDialog::on_IO8radioButton_clicked()
{
    text = ui->IO8radioButton->text();
    Port = 8;
    QDialog::accept();
}

void IOPortSelectDialog::on_IO9radioButton_clicked()
{
    text = ui->IO9radioButton->text();
    Port = 9;
    QDialog::accept();
}

void IOPortSelectDialog::on_IO10radioButton_clicked()
{
    text = ui->IO10radioButton->text();
    Port = 10;
    QDialog::accept();
}

void IOPortSelectDialog::on_IO11radioButton_clicked()
{
    text = ui->IO11radioButton->text();
    Port = 11;
    QDialog::accept();
}

void IOPortSelectDialog::on_IO12radioButton_clicked()
{
    text = ui->IO12radioButton->text();
    Port = 12;
    QDialog::accept();
}

void IOPortSelectDialog::on_IO13radioButton_clicked()
{
    text = ui->IO13radioButton->text();
    Port = 13;
    QDialog::accept();
}

void IOPortSelectDialog::on_IO14radioButton_clicked()
{
    text = ui->IO14radioButton->text();
    Port = 14;
    QDialog::accept();
}

void IOPortSelectDialog::on_IO15radioButton_clicked()
{
    text = ui->IO15radioButton->text();
    Port = 15;
    QDialog::accept();
}

void IOPortSelectDialog::on_IONullradioButton_clicked()
{
    text = ui->IONullradioButton->text();
    Port = 0;
    QDialog::accept();
}

