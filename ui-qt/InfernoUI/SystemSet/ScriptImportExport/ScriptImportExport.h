#ifndef SCRIPTIMPORTEXPORT_H
#define SCRIPTIMPORTEXPORT_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QListWidget>
#include "../UpdateProgressBarDlg.h"
#include "BusinessData/InterfaceLib/KeyBoardLib.h"
namespace Ui {
class ScriptImportExport;
}

class ScriptImportExport : public QWidget
{
    Q_OBJECT

public:
    explicit ScriptImportExport(QWidget *parent = 0);
    ~ScriptImportExport();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void GetShellScriptFilesList(QListWidget *list, QString path);

    void GetLuaScriptFilesList(QListWidget *list, QString path);

    void GetPython2ScriptFilesList(QListWidget *list, QString path);

    void GetPython3ScriptFilesList(QListWidget *list, QString path);

    void on_btnShell_clicked();

    void on_btnLua_clicked();

    void on_btnPython2_clicked();

    void on_btnPython3_clicked();

    void on_radioButtonShell_clicked();

    void on_radioButtonLua_clicked();

    void on_radioButtonPython2_clicked();

    void on_radioButtonPython3_clicked();

    void on_btnExport_clicked();

    void on_btnImport_clicked();

    void UpdateTimerSlot();

    void on_btnShell_U_clicked();

    void on_btnLua_U_clicked();

    void on_btnPython2_U_clicked();

    void on_btnPython3_U_clicked();

    void on_btnExport_U_clicked();

    void on_btnShell_u_import_clicked();

    void on_btnLua_u_import_clicked();

    void on_btnPython2_u_import_clicked();

    void on_btnPython3_u_import_clicked();

    void on_btnImport_u_import_clicked();

private:
    Ui::ScriptImportExport *ui;
    QPushButton *m_btn_pre;
    unsigned int m_script_type;
    QTimer *updateTimer;
    KeyBoardLib m_KeyBoardLib;
    UpdateProgressBarDlg *m_UpdateProgressBarDlg;

    void SetButtonStyle(QPushButton *pre, QPushButton *current);
    bool isLegal(QString text);
};

#endif // SCRIPTIMPORTEXPORT_H
