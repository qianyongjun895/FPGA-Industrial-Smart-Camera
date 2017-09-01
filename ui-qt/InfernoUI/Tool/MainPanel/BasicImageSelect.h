#ifndef BASICIMAGESELECT_H
#define BASICIMAGESELECT_H

#include <QDialog>

namespace Ui {
class BasicImageSelect;
}

class BasicImageSelect : public QDialog
{
    Q_OBJECT

public:
    explicit BasicImageSelect(QWidget *parent = 0);
    ~BasicImageSelect();

    QString m_pic_name;

private slots:
    void on_btnOk_clicked();

    void on_btnQuit_clicked();

    void on_listWidgetImage_clicked(const QModelIndex &index);

    void on_radioButtonBig_clicked();

    void on_radioButtonSmall_clicked();

    void on_btnRegister_clicked();

private:
    Ui::BasicImageSelect *ui;
    QString m_str_pic_path;
    void IniImageNameList();
    void AddItemData(QString strName);
};

#endif // BASICIMAGESELECT_H
