#ifndef RUNOSDSTYLEDLG_H
#define RUNOSDSTYLEDLG_H

#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include "BusinessData/InterfaceLib/KeyBoardLib.h"
namespace Ui {
class RunOsdStyleDlg;
}

class RunOsdStyleDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RunOsdStyleDlg(QWidget *parent = 0);
    void SetLable(QLabel *label);
    ~RunOsdStyleDlg();
    void AddItem(QString strName, int value=1);
    void InitVtEnable(QListWidget *listWidget);
    void InitVt(QListWidget *listWidget);
private slots:

    void ItemCheckSlot(int value,QString strStept);

    void on_btnOK_clicked();

    void on_btnQuit_clicked();

    void on_comboBoxOKColor_currentIndexChanged(int index);

    void on_comboBoxNGColor_currentIndexChanged(int index);
protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::RunOsdStyleDlg *ui;
    QLabel *m_label;
    void initCombColor(QComboBox *cmb);
    void SelectWidth(QLineEdit *txtLineEdit);
    QVector<unsigned char>m_vt;
    KeyBoardLib m_keyBoardLib;
    unsigned char m_OK_Color;
    unsigned char m_NG_Color;
    unsigned char m_OK_Width;
    unsigned char m_NG_Width;
    int iniFirst;
    void GetColor(int index);
};

#endif // RUNOSDSTYLEDLG_H
