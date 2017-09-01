#include "UserInfo.h"
#include <QFile>
#include <QDebug>
#include <cstdlib>

#define PASSWORD_FILE_PATH "/mnt/emmc2/config/password"

pthread_mutex_t UserInfo::mutex;
UserInfo* UserInfo::p = NULL;

UserInfo::UserInfo()
{
    m_pwd.clear();
    m_pwd = "0";

    QFile file(PASSWORD_FILE_PATH);

    if (!file.exists())
    {
        // 创建密码文件并把初始密码写入文件中
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        if (file.isOpen())
        {
//            qDebug()<<"m_pwd:"<<m_pwd;
            QTextStream txtOutput(&file);
            txtOutput << m_pwd;
            file.close();
            system("sync");
        }
    }

    GetPwdFromFile();
}

void UserInfo::GetPwdFromFile()
{
    QFile file(PASSWORD_FILE_PATH);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file [password]!"<<endl;
        return ;
    }
    QTextStream in(&file);
    m_pwd = in.readAll();
    file.close();
}


UserInfo* UserInfo::GetSingleton()
{
    if (p == NULL)
    {
        pthread_mutex_lock(&mutex);
        if (p == NULL)
            p = new UserInfo();
        pthread_mutex_unlock(&mutex);
    }
    return p;
}

bool UserInfo::VerifyPassword(QString pwd)
{
    if (pwd == m_pwd)
    {
        return true;
    }
    return false;
}

bool UserInfo::ModifyPassword(QString oldPwd, QString newPwd)
{
    if (oldPwd == m_pwd)
    {
        QFile file(PASSWORD_FILE_PATH);
        file.open(QIODevice::ReadWrite | QIODevice::Text);
        if(file.isOpen())
        {
            m_pwd = newPwd;
            QTextStream out(&file);
            out<<m_pwd;
            file.close();
            system("sync");
            return true;
        }
        qDebug()<<"Can't open the file [password]!"<<endl;
    }
    return false;
}

void UserInfo::ResetPassword()
{
    m_pwd.clear();
    m_pwd = "0";
}
