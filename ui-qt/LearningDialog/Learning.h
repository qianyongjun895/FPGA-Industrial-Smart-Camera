#ifndef LEARNING_H
#define LEARNING_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class Learning;
}

typedef enum{
    LEARN_ING,
    LEARN_FAIL,
    LRARN_SUCCESS
}Mode;

typedef enum{
    MATCH_ERR,
    MEASURE_ERR,
}TYPE;
class Learning : public QDialog
{
    Q_OBJECT

public:
    explicit Learning(QWidget *parent = 0);
    ~Learning();

    void SetResultString(QString code_str);
private slots:

    void on_pushButton_clicked();

    void TimerSlot();
private:
    Ui::Learning *ui;
    QString m_rst_Str;
    QTimer *m_Timer;
};

#endif // LEARNING_H
