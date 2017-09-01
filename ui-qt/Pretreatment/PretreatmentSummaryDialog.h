#ifndef PRETREATMENTSUMMARYDIALOG_H
#define PRETREATMENTSUMMARYDIALOG_H

#include <QDialog>

namespace Ui {
class PretreatmentSummaryDialog;
}

class PretreatmentSummaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PretreatmentSummaryDialog(QWidget *parent = 0);
    ~PretreatmentSummaryDialog();
    void SetLocation(int x, int y);
    QString GetStrName(){return m_str_name;}
    int GetIndex(){return m_index;}
    int GetNameIndexById(int id);
    QString GetStrNameByArrIndex(int index);

private slots:
    void on_btnOk_clicked();

    void on_btnQuit_clicked();

private:
    Ui::PretreatmentSummaryDialog *ui;
    QString m_str_name;
    void IniListData();
    QVector<int> m_vt_index;
    QVector<QString>m_vt_strName;
    int m_index;
};

#endif // PRETREATMENTSUMMARYDIALOG_H
