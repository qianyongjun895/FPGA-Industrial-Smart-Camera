#ifndef IMAGEPARAMSELECTDIALOG_H
#define IMAGEPARAMSELECTDIALOG_H

#include <QDialog>

namespace Ui {
class ImageParamSelectDialog;
}

class ImageParamSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImageParamSelectDialog(QWidget *parent = 0);
    ~ImageParamSelectDialog();

    int GetSelectParamIndex();
private slots:
    void on_pushButton_Select_Param_OK_clicked();

    void on_pushButton_Select_Param_Cancel_clicked();

private:
    Ui::ImageParamSelectDialog *ui;
    int Select_Param_index;
};

#endif // IMAGEPARAMSELECTDIALOG_H
