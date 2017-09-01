#ifndef EXTERNALCOMMWIDGET_H
#define EXTERNALCOMMWIDGET_H

#include <QWidget>
#include <QLibrary>
#include <QGridLayout>
#include <QTimer>
#include <QHash>
namespace Ui {
class ExternalCommWidget;
}

typedef QWidget* (*Fun_GetToolWidget)();
typedef void (*Fun_SetProcotolType)(int type);
typedef void (*Fun_SetProtocolData)();
typedef void (*InitShowData)();
typedef void (*Fun_InitProtocol)();
class ExternalCommWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExternalCommWidget(QWidget *parent = 0);
    ~ExternalCommWidget();

    void DeleteCommModeWidgetInLayout();
    void LoadWidget();
    void IniData();
    void DeleteProtocolWidgetInLayout();
    void SetProtocolParam();
private slots:
    void on_selectProtocolcomboBox_currentIndexChanged(int index);

    void on_ModelSelectComboBox_currentIndexChanged(int index);

    void on_tabWidget_currentChanged(int index);


    void CheckEnableFlag();

private:
    Ui::ExternalCommWidget *ui;
    QTimer *EnableCheckTimer;
    QWidget* m_p_widget;

    QStringList Protocol_Name_List;
    QStringList Protocol_Lib_Path_List;
    QVector<QLibrary*> Protocol_Lib_Vector;
    QVector<QStringList> CommMode_Vector;
    QHash<QString, int> CommMode_Type_Hash[5];

    QStringList CommMode_Lib_Path_List;
    QVector<QLibrary*> CommMode_Lib_Vector;

    QHash<int,int>Protocol_Type_Hash;
    QHash<QString, int> CommMode_Index_Hash;
    QHash<QString, int> Comm_Type_Hash;



    int Current_Comm_Mode;
    QLibrary *m_Comm_Mode1_lib;
    QLibrary *m_Comm_Mode2_lib;
    QLibrary *m_Comm_Mode3_lib;
    QWidget *m_pWidget;
    QGridLayout *CommModeLayout;

    int Current_Protocol_index;
    int Current_Protocol_Type;
    int Param_Set_Flag;
    QLibrary *m_Protocol1_lib;
    QLibrary *m_Protocol2_lib;
    QLibrary *m_Protocol3_lib;
    QLibrary *m_Protocol4_lib;
    QLibrary *m_Protocol5_lib;
    QWidget *m_Protocol_Widget;

    QGridLayout *ProtocolLayout;
    void LoadAllCommLib();
    void GetProtocolXmlData();
};

#endif // EXTERNALCOMMWIDGET_H
