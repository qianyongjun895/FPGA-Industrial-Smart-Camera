#ifndef USERINFO_H
#define USERINFO_H

#include <QString>

class UserInfo
{
public:
    static pthread_mutex_t mutex;
    static UserInfo* GetSingleton();
    bool VerifyPassword(QString pwd);
    bool ModifyPassword(QString oldPwd, QString newPwd);
    void ResetPassword();

private:
    UserInfo();
    static UserInfo *p;
    QString m_pwd; // 用户密码

    void GetPwdFromFile();
};

#endif // USERINFO_H
