#include "FileIniControl.h"
#include <QSettings>
#include <qdebug.h>
FileIniControl::FileIniControl()
{

}
void FileIniControl::WriteSettings(QString strIniName,QString strSection, QString strkey,QString strValue)
{
//    QSettings settings(strIniName, QSettings::IniFormat); // 当前目录的INI文件
    QSettings *settings = new QSettings(strIniName, QSettings::IniFormat);
    settings->beginGroup(strSection);
    settings->setValue(strkey,strValue);
    settings->endGroup();
    delete settings;

}
QString FileIniControl::ReadSettings(QString strIniName,QString strSection, QString strkey)
{
    QString strValue;
//    QSettings settings(strIniName, QSettings::IniFormat); // 当前目录的INI文件
    QSettings *settings = new QSettings(strIniName, QSettings::IniFormat);
    settings->beginGroup(strSection);
    strValue = settings->value(strkey).toString();
    settings->endGroup();
    delete settings;
    return strValue;
}
