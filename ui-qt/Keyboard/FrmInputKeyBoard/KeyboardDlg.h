#ifndef KEYBOARDDLG_H
#define KEYBOARDDLG_H

#include <QDialog>
#include <QButtonGroup>
//#include <QLineEdit>


namespace Ui {
class KeyboardDlg;
}

class KeyboardDlg : public QDialog
{
    Q_OBJECT

public:
    explicit KeyboardDlg(QWidget *parent = 0);
    ~KeyboardDlg();

    QString GetInputString();
    void SetInputString(QString str);
    void PassWordInput();
    void SetInputObj(QObject *w);
private slots:
    void on_pushButton_ok_clicked();

    void on_pushButton_backspace_clicked();


    void PreeditContent(QString str);
    void SetKeyBoard();
    void ButtonJudge(int id);

    void on_pushButton_Cancel_clicked();

    void on_pushButton_Caps_clicked();

    void on_pushButton_Quit_clicked();

private:
    Ui::KeyboardDlg *ui;
    QWidget *currentObj;
    QButtonGroup *button_group;
    QString m_InputStr;
    bool b_Caps;

//    QLineEdit *currentLineEdit;     //当前焦点的单行文本框
//    QTextEdit *currentTextEdit;     //当前焦点的多行文本框
//    QPlainTextEdit *currentPlain;   //当前焦点的富文本框
//    QTextBrowser *currentBrowser;   //当前焦点的文本浏览框


    void ChangeCapital();
    void ChangeLowercase();
signals:
    void SendInputMessage(QString);
};

#endif // KEYBOARDDLG_H
