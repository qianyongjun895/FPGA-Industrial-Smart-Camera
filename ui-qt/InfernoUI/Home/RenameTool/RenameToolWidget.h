#ifndef RENAMETOOLWIDGET_H
#define RENAMETOOLWIDGET_H

#include <QWidget>

namespace Ui {
class RenameToolWidget;
}

class RenameToolWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RenameToolWidget(QWidget *parent = 0);
    ~RenameToolWidget();
    void SetTaskId(QVector<int> vt);
    void AddItemData(QString strName,QString strReName);
private slots:
    void on_btnQuit_clicked();

    void on_btnModifyName_clicked();

    void on_btnReset_clicked();

    void on_listWidgetName_clicked(const QModelIndex &index);
signals:
    void SignalsExit(int index,QString strName);
private:
    Ui::RenameToolWidget *ui;
    QVector<int> m_vt_task_id;
    QString m_strName;
    void SetInfor(QString str,int flag);
    bool isLegal(QString text);

};

#endif // RENAMETOOLWIDGET_H
