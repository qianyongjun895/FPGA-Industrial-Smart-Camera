#ifndef DATAINPUTWIDGET_H
#define DATAINPUTWIDGET_H

#include <QWidget>
#include <QLibrary>
namespace Ui {
class DataInputWidget;
}
typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();
class DataInputWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DataInputWidget(QWidget *parent = 0);
    ~DataInputWidget();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:

    void on_pushButton_Down_clicked();

    void on_pushButton_Up_clicked();

    void on_pushButton_GO_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_Down_dynamic_clicked();

    void on_pushButton_Up_dynamic_clicked();

    void on_pushButton_GO_dynamic_clicked();

private:
    Ui::DataInputWidget *ui;
    QLibrary m_keyBoard_Lib;
    QDialog *Numkey;
    int page_index;
    int dynamic_page_index;
    void ShowItemData();
    void SetItemData();
    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value);
    void ShowDynamicItemData();
};

#endif // DATAINPUTWIDGET_H
