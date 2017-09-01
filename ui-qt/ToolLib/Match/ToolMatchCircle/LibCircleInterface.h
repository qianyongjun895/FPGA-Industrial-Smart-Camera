#ifndef LIBCIRCLEINTERFACE_H
#define LIBCIRCLEINTERFACE_H
#include <QLibrary>
#include <QString>

class LibCircleInterface
{
public:
    LibCircleInterface();
    ~LibCircleInterface();
    /**
     * @brief IniLib
     * @param strName 控件lib路径
     * @return 返回1 成功 0失败
     * @author szj
     * @date 2017/05/18
     * @note 初始化lib
     */
    int IniLib(QString strName);

    /**
     * @brief 设置圆形定位输入参数X,Y坐标
     * @param step_index: 步骤号
     *        x:圆心X值
     *        y:圆心Y值
     * @return 0:成功，其它：失败
     * @author <szj>
     * @note
     */
    int Circle_Input_Center_X_Y_Set(unsigned int step_index, unsigned int x, unsigned int y);

    /**
     * @brief 设置圆形定位输入参数半径
     * @param step_index: 步骤号
     *        radius:圆半径值
     * @return 0:成功，其它：失败
     * @author <szj>
     * @note
     */
    int Circle_Input_Radius_Set(unsigned int step_index, unsigned int radius);

    /**
     * @brief 获取圆形定位输入参数X,Y坐标
     * @param step_index: 步骤号
     *        p_x:圆心X值
     *        p_y:圆心Y值
     * @return 0:成功，其它：失败
     * @author <szj>
     * @note
     */
    int Circle_Input_Center_XY_Get(unsigned int step_index, unsigned int *p_x, unsigned int *p_y);

    /**
     * @brief 获取圆形定位输入参数半径
     * @param step_index: 步骤号
     *        p_radius:圆半径值
     * @return 0:成功，其它：失败
     * @author <szj>
     * @note
     */
    int Circle_Input_Radius_Get(unsigned int step_index, unsigned int *p_radius);
public:
    QString m_strLib;
    QLibrary m_lib;

};

#endif // LIBCIRCLEINTERFACE_H
