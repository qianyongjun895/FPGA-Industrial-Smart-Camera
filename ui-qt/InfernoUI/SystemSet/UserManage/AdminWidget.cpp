#include "AdminWidget.h"
#include "ui_AdminWidget.h"
#include "UserInfo.h"
#include <QMessageBox>

AdminWidget::AdminWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminWidget)
{
    ui->setupUi(this);
    qApp->installEventFilter(this);
    ui->txtAdmin->setReadOnly(true);

    ui->txtOldPwd->setEchoMode(QLineEdit::Password);
    ui->txtNewPwd->setEchoMode(QLineEdit::Password);
    ui->txtConfirmPwd->setEchoMode(QLineEdit::Password);
}

AdminWidget::~AdminWidget()
{
    qApp->removeEventFilter(this);
    delete ui;
}

bool AdminWidget::eventFilter(QObject *watched, QEvent *event)
{
    QList<QLineEdit *> lineEdit = this->findChildren<QLineEdit *>();
    foreach (QLineEdit * L, lineEdit) {
        if (L->objectName() == watched->objectName() && !L->isReadOnly()) {
            if (event->type()==QEvent::MouseButtonPress){
                QDialog *dlg = m_KeyBoardLib.GetKeyBoardDialog();
                if(!ui->checkBox->isChecked()){
                    m_KeyBoardLib.PassWordInput();
                }
                m_KeyBoardLib.SetInputString(((QLineEdit *)watched)->text());
                m_KeyBoardLib.SetInputObj(watched);
                dlg->exec();
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void AdminWidget::on_btnModify_clicked()
{
    if (ui->txtOldPwd->text().isEmpty())
    {
        QMessageBox::about(NULL,tr("about"),tr("输入不能为空!"));
        return ;
    }
    if (ui->txtNewPwd->text().isEmpty())
    {
        QMessageBox::about(NULL,tr("about"),tr("输入不能为空!"));
        return ;
    }
    if (ui->txtConfirmPwd->text().isEmpty())
    {
        QMessageBox::about(NULL,tr("about"),tr("输入不能为空!"));
        return ;
    }
    UserInfo *p = UserInfo::GetSingleton();
    if (ui->txtNewPwd->text() == ui->txtConfirmPwd->text())
    {
        if (p->ModifyPassword(ui->txtOldPwd->text(), ui->txtNewPwd->text()))
        {
            QMessageBox::about(NULL,tr("about"),tr("修改成功!"));
        }
        else
        {
            QMessageBox::about(NULL,tr("about"),tr("修改失败!"));
        }
        return ;
    }
    else
    {
        QMessageBox::about(NULL,tr("about"),tr("两次输入的密码不一致!"));
    }
}

void AdminWidget::on_checkBox_clicked()
{
    if (ui->checkBox->isChecked())
    {
        ui->txtOldPwd->setEchoMode(QLineEdit::Normal);
        ui->txtNewPwd->setEchoMode(QLineEdit::Normal);
        ui->txtConfirmPwd->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->txtOldPwd->setEchoMode(QLineEdit::Password);
        ui->txtNewPwd->setEchoMode(QLineEdit::Password);
        ui->txtConfirmPwd->setEchoMode(QLineEdit::Password);
    }
}
