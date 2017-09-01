#ifndef IMAGEMANAGEMNET_H
#define IMAGEMANAGEMNET_H

#include <QDialog>


namespace Ui {
class ImageManagemnet;
}

class ImageManagemnet : public QDialog
{
    Q_OBJECT

public:
    explicit ImageManagemnet(QWidget *parent = 0);
    ~ImageManagemnet();
    void InitData();
private slots:
    void on_btnExit_clicked();

    void on_radioButton_Save_clicked();

    void on_radioButton_Failed_clicked();

    void on_radioButton_OK_clicked();

    void on_radioButton_Base_clicked();

    void on_btnFirst_clicked();

    void on_btnPrev_clicked();

    void on_btnNext_clicked();

    void on_btnLast_clicked();

    void on_btnDeleteImage_clicked();

    void on_listWidgetImage_clicked(const QModelIndex &index);

    void on_btnCleanImage_clicked();

private:
    Ui::ImageManagemnet *ui;
    int m_image_count;
    int m_image_index;
    void IniImageNameList();
    void AddItemData(QString strName);
    QString GetPageNumber(int index,int count);
};

#endif // IMAGEMANAGEMNET_H
