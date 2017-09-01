#ifndef FILEVIEW_H
#define FILEVIEW_H

#include <QDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QFileInfoList>
#include <QDir>
#include "BusinessData/InterfaceLib/KeyBoardLib.h"

namespace Ui {
class FileView;
}

class FileView : public QDialog
{
    Q_OBJECT

public:
    explicit FileView(QWidget *parent = 0);
    ~FileView();
    QString GetFolderPath();
private slots:
    void on_btnOk_clicked();

    void on_btnQuit_clicked();

    void on_downButton_clicked();
    void on_upButton_clicked();
    void on_enterButton_clicked();
    void on_pasteButton_clicked();
    void on_copyButton_clicked();
    void on_listWidget_itemClicked(QListWidgetItem* item);
    void on_listWidget_itemDoubleClicked(QListWidgetItem* item);
    void on_btnReturn_clicked();

    void on_btnCreate_clicked();

    void on_btnDel_clicked();

    void on_btnRename_clicked();

private:
    Ui::FileView *ui;
    QLineEdit *LineEditDir;
    QListWidget *ListWidgetFile;
    QListWidgetItem item;
    QString m_str_root;
    int itemnum;
    int m;
    KeyBoardLib m_KeyBoardLib;
    void showFileInfoList(QFileInfoList list);
    void slotShow(QDir dir);
    bool copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist);
    bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
    bool DeleteDirectory(const QString &path);

};

#endif // FILEVIEW_H
