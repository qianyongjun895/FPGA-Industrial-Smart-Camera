#ifndef USERDEFINEDDATAITEM_H
#define USERDEFINEDDATAITEM_H

#include <QWidget>
#include <QStringList>
#include <QVector>

namespace Ui {
class UserDefinedDataItem;
}

class UserDefinedDataItem : public QWidget
{
    Q_OBJECT

public:
    explicit UserDefinedDataItem(QWidget *parent = 0);
    ~UserDefinedDataItem();

    void SetLabelString(QString str);
    void SetTaskString(QString str);

    int List_index;
    QString select_data;
    QString m_Label_string;///<标签
    int m_include_Label_flag;///<包括标签
    int m_link_step;///<关联步骤
    int m_width_flag;///<固定宽度
    int m_data_width;///<字段宽度
    int m_fill;///填充
    QString m_Output_string;
    QString m_Output_string_num;

private slots:
    void on_detail_pushButton_clicked();

private:
    Ui::UserDefinedDataItem *ui;
};

#endif // USERDEFINEDDATAITEM_H
