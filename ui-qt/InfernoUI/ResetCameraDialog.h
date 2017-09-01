#ifndef RESETCAMERADIALOG_H
#define RESETCAMERADIALOG_H

#include <QDialog>
#include <QGridLayout>

namespace Ui {
class ResetCameraDialog;
}

class ResetCameraDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResetCameraDialog(QWidget *parent = 0);
    ~ResetCameraDialog();

    void ShowDnaErrorPanel();
    void ShowLicenseExpirePanel();

public slots:
    void closeBtnShow();

private slots:
    void on_btnClose_clicked();

private:
    Ui::ResetCameraDialog *ui;
    QGridLayout *m_ViewLayout;

    void DeleteWidgetInLayout();
};

#endif // RESETCAMERADIALOG_H
