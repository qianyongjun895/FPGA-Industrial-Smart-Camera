/**
  * @file  [FileIniControl.h]
  * @brief  FileIniControl
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef FILEINICONTROL_H
#define FILEINICONTROL_H
#include <QString>

/**
  * @class  <FileIniControl>  [FileIniControl.h]  [FileIniControl]
  * @brief  ini文件读写类
  * @author  <szj>
  * @note
  * detailed  description
  */
class FileIniControl
{
public:
    FileIniControl();
    /**
     * @brief WriteSettings
     * @param strIniName
     * @param strSection
     * @param strkey
     * @param strValue
     * @author szj
     * @date 2017/05/08
     * @note 写ini文件
     */
    static void WriteSettings(QString strIniName,QString strSection, QString strkey,QString strValue);
    /**
     * @brief ReadSettings
     * @param strIniName
     * @param strSection
     * @param strkey
     * @return 读到的相应key的值
     * @author szj
     * @date 2017/05/08
     * @note 读ini文件
     */
    static QString ReadSettings(QString strIniName,QString strSection, QString strkey);
};

#endif // FILEINICONTROL_H
