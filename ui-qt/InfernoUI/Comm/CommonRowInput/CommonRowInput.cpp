#include "CommonRowInput.h"
#include "ui_CommonRowInput.h"

CommonRowInput::CommonRowInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommonRowInput)
{
    ui->setupUi(this);
}

CommonRowInput::~CommonRowInput()
{
    delete ui;
}

void CommonRowInput::SetInputText(QString text)
{
    ui->lineEdit_CommonRowInput->setText(text);
}

void CommonRowInput::on_btnOK_clicked()
{
    m_input_text = ui->lineEdit_CommonRowInput->text();
    SendInputText(m_input_text);
    ui->lineEdit_CommonRowInput->clear();
    this->close();
}

void CommonRowInput::on_btnCancel_clicked()
{
    ui->lineEdit_CommonRowInput->clear();
    this->close();
}
