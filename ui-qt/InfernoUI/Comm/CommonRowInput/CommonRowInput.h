#ifndef COMMONROWINPUT_H
#define COMMONROWINPUT_H

#include <QWidget>

namespace Ui {
class CommonRowInput;
}

class CommonRowInput : public QWidget
{
    Q_OBJECT

public:
    explicit CommonRowInput(QWidget *parent = 0);
    ~CommonRowInput();

    void SetInputText(QString text);

signals:
    void SendInputText(QString text);

private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    Ui::CommonRowInput *ui;
    QString m_input_text;
};

#endif // COMMONROWINPUT_H
