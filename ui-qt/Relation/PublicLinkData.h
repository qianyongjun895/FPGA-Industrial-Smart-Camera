#ifndef PUBLICLINKDATA_H
#define PUBLICLINKDATA_H

#include <QObject>
#include <QString>
#include <QStringList>

#define COMPASS_INFO_SIZE   3
class PublicLinkData : public QObject
{
    Q_OBJECT
public:

    enum{
        SELECT_X_DATA = 0,
        SELECT_Y_DATA,
        SELECT_ANGLE_DATA
    };

    PublicLinkData();
    ~PublicLinkData();

    static PublicLinkData *GetPublicLinkInstance();

    //初始化数据
    int PublicLinkDataInit(int task_index);

    //完成后设置数据到SSP
    int PublicLinkDataHandleFinish();


    //获取列表任务数
    unsigned int GetListAllTask();

    //获取有关点的任务字符串
    QString GetLinkDataPointTaskStr(int task_index);

    //获取有关角度的任务字符串
    QString GetLinkDataAngleString(int task_index);

    //获取有关X的结果字符串
    QStringList GetLinkDataXResultStr(int task_index);

    //获取有关Y的结果字符串
    QStringList GetLinkDataYResultStr(int task_index);

    //获取有关角度的结果字符串
    QStringList GetLinkDataAngleStr(int task_index);


    //获取关联数据使能标志(0:disable; 1:enable)
    unsigned int GetLinkDataEnableFlag(){return compass_enable;}


    //获取关联数据类型(0:无; 1:手动输入; 2:引用;); unsigned int index:下标: 0:X; 1:Y; 2:角度*/
    unsigned int GetLinkDataType(unsigned int index){return compass_type[index];}

    //获取关联步骤; unsigned int index:下标: 0:X; 1:Y; 2:角度*/
    unsigned int GetLinkDataStep(unsigned int index){return compass_step[index];}

    //获取结果索引; unsigned int index:下标: 0:X; 1:Y; 2:角度*/
    unsigned int GetLinkDataResult(unsigned int index){return ref_value_index[index];}

    //获取手动输入的值; unsigned int index:下标: 0:X; 1:Y; 2:角度*/
    double GetLinkDataValue(unsigned int index){return compass_ori_value[index];}




    //设置关联数据使能标志(0:disable; 1:enable)
    void SetLinkDataEnableFlag(unsigned int enable){compass_enable = enable;}


    //设置关联数据类型(0:无; 1:手动输入; 2:引用;); unsigned int index:下标: 0:X; 1:Y; 2:角度*/
    void SetLinkDataType(unsigned int index, unsigned int type){compass_type[index] = type;}

    //设置关联步骤; unsigned int index:下标: 0:X; 1:Y; 2:角度*/
    void SetLinkDataStep(unsigned int index, unsigned int step_index){compass_step[index] = step_index;}

    //设置结果索引; unsigned int index:下标: 0:X; 1:Y; 2:角度*/
    void SetLinkDataResult(unsigned int index, unsigned int result_index){ref_value_index[index] = result_index;}

    //设置手动输入的值; unsigned int index:下标: 0:X; 1:Y; 2:角度*/
    void GetLinkDataValue(unsigned int index, double value){compass_ori_value[index] = value;}


private:

    unsigned int current_step;   /* 步骤索引 */
    unsigned int compass_enable;/* 使能compass，0：disable，1：enable */
    unsigned int compass_type[COMPASS_INFO_SIZE];				/* 关联设置类型 0:无; 1:手动输入; 2:引用;*/
    unsigned int compass_step[COMPASS_INFO_SIZE];				/* 关联步骤 */
    unsigned int ref_value_index[COMPASS_INFO_SIZE];			/* 从ref_value取值索引 */
    double compass_ori_value[COMPASS_INFO_SIZE];			/* 手动输入的值 */

    static PublicLinkData *PublicInstance;
    QStringList GetResultString(int task_index, int link_type_index);
};

#endif // PUBLICLINKDATA_H
