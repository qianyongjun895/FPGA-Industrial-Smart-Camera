#ifndef BOUNDARYWIDGET_H
#define BOUNDARYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLabel>
#include <QTime>
#include <QPushButton>

namespace Ui {
class BoundaryWidget;
}

class BoundaryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BoundaryWidget(QWidget *parent = 0);
    ~BoundaryWidget();
    QPoint Get_Image_Pos();
private slots:
    void on_radioButtonIncongruous_clicked();

    void on_radioButtonSyntropy_clicked();

    void on_radioButtonEdgeX_clicked();

    void on_radioButtonEdgeY_clicked();

    void on_radioButtonRoiX_clicked();

    void on_radioButtonRoiY_clicked();

    void on_btnSkeletonUp_pressed();

    void on_btnSkeletonDown_pressed();

    void on_btnSkeletonLeft_pressed();

    void on_btnSkeletonRight_pressed();

    void GetCurrentTime();
    void ShowCurrentPointCoordinate(QPoint point, int index);
private:
    Ui::BoundaryWidget *ui;
    QLabel *m_label;
    QTime startTime;
    QTime stopTime;
    void SetBtnRepeatParam(QPushButton *btn);
};

#endif // BOUNDARYWIDGET_H
