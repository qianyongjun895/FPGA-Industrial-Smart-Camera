#include "TendencyGraph.h"
#include "ui_TendencyGraph.h"

TendencyGraph::TendencyGraph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TendencyGraph)
{
    ui->setupUi(this);
}

TendencyGraph::~TendencyGraph()
{
    delete ui;
}

void TendencyGraph::on_ReturnBtn_clicked()
{
//    QLineSeries *series = new QLineSeries();
//    //![1]

//    //![2]
//        series->append(0, 6);
//        series->append(2, 4);
//        series->append(3, 8);
//        series->append(7, 4);
//        series->append(55, 500);
//        //int max = ui->lineEdit->text().toInt();
//        //*series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(max, 2);
//        QChart *chart = new QChart();
//        chart->legend()->hide();
//        chart->addSeries(series);
//        chart->createDefaultAxes();
//        chart->setTitle(tr("趋势图"));
//    //![3]

//    //![4]
//        QChartView *chartView = new QChartView(chart);
//        chartView->setRenderHint(QPainter::Antialiasing);
//        QHBoxLayout *layout = new QHBoxLayout();
//        layout->setContentsMargins(370, 0, 30, 410);
//        layout->addWidget(chartView);
//        setLayout(layout);
    QDialog::accept();
}
