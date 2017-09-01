#include "FileView.h"
#include "ui_FileView.h"
#include <QMessageBox>
#include <qdebug.h>
FileView::FileView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileView)
{
    ui->setupUi(this);
    LineEditDir=ui->lineEdit;
    ListWidgetFile=ui->listWidget;
    LineEditDir->setText("/mnt/usb");
    m_str_root="/mnt/usb";
    QDir rootDir(m_str_root);
    QStringList string;
    string << "*" ;
    QFileInfoList list=rootDir.entryInfoList (string);
    showFileInfoList(list);


}

FileView::~FileView()
{
    delete ui;
}

void FileView::on_btnOk_clicked()
{
    if(LineEditDir->text() == m_str_root)
    {
        QMessageBox::about(NULL,"提示","请选择u盘中的目录！");
        return;
    }
    if(ListWidgetFile->currentRow() <0)
    {
        QMessageBox::about(NULL,"提示","请选择目录！");
        return;
    }
    QDir dir;
    dir.setPath(LineEditDir->text()+"/"+ListWidgetFile->currentItem()->text());
    if(!dir.exists())
    {
        QMessageBox::about(NULL,"提示","请选择目录！");
        return;
    }
    QDialog::accept();
}

void FileView::on_btnQuit_clicked()
{
    QDialog::reject();
}
void FileView::showFileInfoList(QFileInfoList list)
{
    ListWidgetFile->clear();
    itemnum=0;
    ListWidgetFile->setCurrentRow(itemnum);
    ListWidgetFile->setIconSize(QSize(32,32));
    m=ListWidgetFile->currentRow();
    int i_width = ui->listWidget->width();
    for(int i=0;i<list.size();i++)
    {
        QFileInfo tmpFileInfo=list.at(i);
        if(tmpFileInfo.isDir())
        {
            QIcon icon("./image/Buttons/dir.png");
            QString filename=tmpFileInfo.fileName();
            QListWidgetItem *tmp=new QListWidgetItem(icon,filename);
            ListWidgetFile->addItem(tmp);
            ui->listWidget->item(i)->setSizeHint(QSize(i_width-30,40));
        }
        else if(tmpFileInfo.isFile())
        {
            QIcon icon("./image/Buttons/file.png");
            QString filename=tmpFileInfo.fileName();
            QListWidgetItem *tmp=new QListWidgetItem(icon,filename);
            ListWidgetFile->addItem(tmp);
            ui->listWidget->item(i)->setSizeHint(QSize(i_width-30,40));
        }
    }
    ListWidgetFile->setItemSelected(ListWidgetFile->item(itemnum),true);
    ListWidgetFile->setCurrentRow(itemnum);
    m=ListWidgetFile->currentRow();
}

void FileView::slotShow(QDir dir)
{
    QStringList string;
    string<<"*";
    QFileInfoList list=dir.entryInfoList(string,QDir::AllEntries,QDir::DirsFirst);
    showFileInfoList(list);
}

void FileView::on_listWidget_itemDoubleClicked(QListWidgetItem* item)
{
    QString str=item->text();
    QDir dir;
    dir.setPath(LineEditDir->text());
    dir.cd(str);
    LineEditDir->setText(dir.absolutePath());
    slotShow(dir);
}

void FileView::on_listWidget_itemClicked(QListWidgetItem* item)
{
    itemnum=ListWidgetFile->currentRow();
}

void FileView::on_copyButton_clicked()
{

}

void FileView::on_pasteButton_clicked()
{

}

void FileView::on_enterButton_clicked()
{
    QString str;
    str=ListWidgetFile->currentItem()->text();
    QDir dir;
    dir.setPath(LineEditDir->text());
    dir.cd(str);
    LineEditDir->setText(dir.absolutePath());
    slotShow(dir);

}

void FileView::on_upButton_clicked()
{
    if(itemnum>0)
    {
        itemnum--;
        ListWidgetFile->setItemSelected(ListWidgetFile->item(itemnum),true);
        ListWidgetFile->setCurrentRow(itemnum);
        m=ListWidgetFile->currentRow();
    }
}

void FileView::on_downButton_clicked()
{
    QDir dir;
    QStringList string;
    dir.setPath(LineEditDir->text());
    string<<"*";
    QFileInfoList list=dir.entryInfoList(string,QDir::AllEntries,QDir::DirsFirst);
    if(itemnum<list.size()-1)
    {
        itemnum=itemnum+1;
        ListWidgetFile->setItemSelected(ListWidgetFile->item(itemnum),true);
        ListWidgetFile->setCurrentRow(itemnum);
        m=ListWidgetFile->currentRow();
    }
}

void FileView::on_btnReturn_clicked()
{
    QString str;
    str=ListWidgetFile->currentItem()->text();

    if(LineEditDir->text() == m_str_root)
        return;

    QDir dir;
    dir.setPath(LineEditDir->text());
    dir.cdUp();
    LineEditDir->setText(dir.absolutePath());
    slotShow(dir);
}
//拷贝文件：
bool FileView::copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist)
{
    toDir.replace("\\","/");
    if (sourceDir == toDir){
        return true;
    }
    if (!QFile::exists(sourceDir)){
        return false;
    }
    QDir *createfile     = new QDir;
    bool exist = createfile->exists(toDir);
    if (exist){
        if(coverFileIfExist){
            createfile->remove(toDir);
        }
    }//end if

    if(!QFile::copy(sourceDir, toDir))
    {
        return false;
    }
    return true;
}

//拷贝文件夹：
bool FileView::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir()){    /**< 当为目录时，递归的进行copy */
            if(!copyDirectoryFiles(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()),
                coverFileIfExist))
                return false;
        }
        else{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
                targetDir.remove(fileInfo.fileName());
            }

            /// 进行文件copy
            if(!QFile::copy(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()))){
                    return false;
            }
        }
    }
    return true;
}
//新建文件夹
void FileView::on_btnCreate_clicked()
{
    QString str;
    str=ListWidgetFile->currentItem()->text();
    QDir dir;
    dir.setPath(LineEditDir->text());
    if(LineEditDir->text() == m_str_root)
    {
        QMessageBox::about(NULL,"提示","请在u盘目录下创建目录！");
        return;
    }

    QDialog *dlg = m_KeyBoardLib.GetKeyBoardDialog();
    m_KeyBoardLib.SetInputString("newFolder");
    dlg->move(0,450);

    int ret = dlg->exec();

    if(ret == QDialog::Accepted)
    {
        QString strName = m_KeyBoardLib.GetInputString();
        dir.mkdir(strName);
        slotShow(dir);
    }
}
bool FileView::DeleteDirectory(const QString &path)
{
    if (path.isEmpty())
        return false;

    QDir dir(path);

    if(!dir.exists())
    {
        QFile::remove(path);
        return true;
    }

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo fi, fileList)
    {
        if (fi.isFile())
            fi.dir().remove(fi.fileName());
        else
            DeleteDirectory(fi.absoluteFilePath());
    }

    return dir.rmpath(dir.absolutePath());
}
void FileView::on_btnDel_clicked()
{
    if(ListWidgetFile->currentRow() < 0)
        return;
    QString str;
    str=ListWidgetFile->currentItem()->text();
    QDir dir;
    dir.setPath(LineEditDir->text());
    //dir.rmdir(str);
    DeleteDirectory(LineEditDir->text()+"/"+str);
    slotShow(dir);
}

void FileView::on_btnRename_clicked()
{
    if(ListWidgetFile->currentRow() < 0)
        return;
    QString str;
    str=ListWidgetFile->currentItem()->text();
    QDir dir;
    dir.setPath(LineEditDir->text());
    QDialog *dlg = m_KeyBoardLib.GetKeyBoardDialog();
    m_KeyBoardLib.SetInputString(str);
    dlg->move(0,450);

    int ret = dlg->exec();

    if(ret == QDialog::Accepted)
    {
        QString strName = m_KeyBoardLib.GetInputString();
        if(!dir.exists())
        {
            QFile::rename(LineEditDir->text()+"/"+str,LineEditDir->text()+"/"+"hao123.txt");
            return ;
        }else
        {
          dir.rename(str,strName);
        }
        slotShow(dir);
    }
}
QString FileView::GetFolderPath()
{
    QString str;
    if(ListWidgetFile->currentRow() >=0)
    {
        str=ListWidgetFile->currentItem()->text();
    }else
    {
        return "";
    }
    QString Path =LineEditDir->text()+"/"+str;
    return Path;
}
