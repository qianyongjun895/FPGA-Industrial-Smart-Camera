#ifndef TENDENCYGRAPH_H
#define TENDENCYGRAPH_H

#include <QDialog>
#include <QtCharts/QChartView>
#include <QLineSeries>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class TendencyGraph;
}

class TendencyGraph : public QDialog
{
    Q_OBJECT

public:
    explicit TendencyGraph(QWidget *parent = 0);
    ~TendencyGraph();

private slots:
    void on_ReturnBtn_clicked();

private:
    Ui::TendencyGraph *ui;
};

#endif // TENDENCYGRAPH_H
