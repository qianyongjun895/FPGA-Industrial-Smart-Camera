#ifndef HEARTBEATWIDGET_H
#define HEARTBEATWIDGET_H

#include <QWidget>
#include <QLibrary>
#include <QString>
#include <QHash>
#include <QListWidgetItem>
namespace Ui {
class HeartBeatWidget;
}
typedef QDialog* (*Fun_GetkeyBoardDlg)();
typedef QString (*Fun_GetInputString)();

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();

class HeartBeatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HeartBeatWidget(QWidget *parent = 0);
    ~HeartBeatWidget();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void on_pushButton_start_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::HeartBeatWidget *ui;
    QLibrary m_keyBoard_Lib;
    QDialog *m_dlg;
    QDialog *Numkey;
    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, QEvent *event);
    void KeyBoardDlg(QObject *watched, QEvent *event, int dlg_x, int dlg_y, int String_Len);

    void IniData();
};

#endif // HEARTBEATWIDGET_H
