#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include "Comm/GlobalParameter.h"
#include "UserInfo.h"


LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->txtPwd->installEventFilter(this);
}

LoginDialog::~LoginDialog()
{
    ui->txtPwd->removeEventFilter(this);
    delete ui;
}

void LoginDialog::on_btnLogin_clicked()
{
    QString curPwd = ui->txtPwd->text();
    if (curPwd == "root")
    {
        ui->txtPwd->clear();
        ui->labelInfo->setText(tr("Developer mode!"));
        GlobalParameter::g_user_mode = 1;
        return ;
    }

    UserInfo* p = UserInfo::GetSingleton();

    // 超级密码
    if (curPwd == "19830503")
    {
        // 重置密码
        system("echo -n 0 > /mnt/emmc2/config/password && sync");
        p->ResetPassword();
        GlobalParameter::g_login =1;
        QDialog::accept();
        return ;
    }


    if(p->VerifyPassword(curPwd))
    {
        GlobalParameter::g_login =1;
        QDialog::accept();
    }
    else
    {
        ui->labelInfo->setText(tr("密码错误！"));
    }
}

void LoginDialog::on_btnQuit_clicked()
{
    QDialog::reject();
}

bool LoginDialog::eventFilter(QObject *watched, QEvent *event)
{
    QList<QLineEdit *> lineEdit = this->findChildren<QLineEdit *>();
    foreach (QLineEdit * L, lineEdit) {
        if (L->objectName() == watched->objectName() && L->isEnabled()) {
            if (event->type()==QEvent::MouseButtonPress){
                QDialog *dlg = m_KeyBoardLib.GetKeyBoardDialog();
                if(!ui->checkBox_PswVisible->isChecked()){
                    m_KeyBoardLib.PassWordInput();
                }
                m_KeyBoardLib.SetInputString(((QLineEdit *)watched)->text());
                m_KeyBoardLib.SetInputObj(watched);
                dlg->move(0,200);
                dlg->exec();
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

/**
 * @brief LoginDialog::on_checkBox_PswVisible_clicked
 * @note 登录密码可见
 */
void LoginDialog::on_checkBox_PswVisible_clicked()
{
    if(ui->checkBox_PswVisible->isChecked()){
        ui->txtPwd->setEchoMode(QLineEdit::Normal);
    }
    else{
        ui->txtPwd->setEchoMode(QLineEdit::Password);
    }
}

