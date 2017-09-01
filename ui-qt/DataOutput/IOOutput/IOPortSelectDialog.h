#ifndef IOPORTSELECTDIALOG_H
#define IOPORTSELECTDIALOG_H

#include <QDialog>
#include <QHash>
#include <QRadioButton>
namespace Ui {
class IOPortSelectDialog;
}

class IOPortSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IOPortSelectDialog(QWidget *parent = 0);
    ~IOPortSelectDialog();

    void SetModel(int flag, int io_port);
    void SetOKOrNGFlag(int flag){OK_Or_NG_Flag = flag;}
    QString GetSelectString(){return text;}
    int GetSelectPortNumber(){return Port;}
private slots:
    void on_IO1radioButton_clicked();
    void on_IO2radioButton_clicked();
    void on_IO3radioButton_clicked();
    void on_IO4radioButton_clicked();
    void on_IO5radioButton_clicked();
    void on_IO6radioButton_clicked();
    void on_IO7radioButton_clicked();
    void on_IO8radioButton_clicked();
    void on_IO9radioButton_clicked();
    void on_IO10radioButton_clicked();
    void on_IO11radioButton_clicked();
    void on_IO12radioButton_clicked();
    void on_IO13radioButton_clicked();
    void on_IO14radioButton_clicked();
    void on_IO15radioButton_clicked();
    void on_IONullradioButton_clicked();
private:
    Ui::IOPortSelectDialog *ui;
    int Widget_Height;
    int Model_Flag;///<0:基础; 1:高级
    int OK_Or_NG_Flag;///<0:NG; 1:OK
    int m_radioNull_x;
    int m_radioNull_y;

    QHash<QRadioButton*, int>IO_Data;
    QString text;
    int Port;
};

#endif // IOPORTSELECTDIALOG_H
