#include "graph.h"
namespace Ui {
class dabai;
}

void dabai::graph_init()
{
    ui->graph->yAxis2->setVisible(true);
    //ui->graph->xAxis->setVisible(false);
    ui->graph->xAxis2->setVisible(true);
    ui->graph->xAxis2->setLabel("时间/s");
    ui->graph->xAxis->setLabel("时间/s");
    ui->graph->xAxis->setBasePen(QPen(Qt::red));
    ui->graph->yAxis->setBasePen(QPen(Qt::red));
    ui->graph->xAxis->setLabelColor(Qt::red);
    ui->graph->yAxis->setLabelColor(Qt::red);
    ui->graph->xAxis2->setLabelColor(Qt::blue);
    ui->graph->yAxis2->setLabelColor(Qt::blue);
    ui->graph->xAxis2->setBasePen(QPen(Qt::blue));
    ui->graph->yAxis2->setBasePen(QPen(Qt::blue));
    ui->graph->yAxis->setLabel("温度/℃");
    ui->graph->yAxis2->setLabel("PM2.5");
    ui->graph->xAxis2->setRange(0,100*30);
    ui->graph->xAxis->setRange(0,100*30);
    ui->graph->yAxis->setRange(-10,50);
    ui->graph->yAxis2->setRange(0,600);
    ui->graph->xAxis2->setRangeReversed(true);
    ui->graph->addGraph(ui->graph->xAxis,ui->graph->yAxis);
    ui->graph->addGraph(ui->graph->xAxis2,ui->graph->yAxis2);
    ui->graph->graph(0)->setName("温度");
    ui->graph->graph(1)->setName("pm2.5");
    ui->graph->graph(0)->setPen(QPen(Qt::red));
    ui->graph->graph(1)->setPen(QPen(Qt::blue));
    ui->graph->legend->setVisible(true);
    g_time_value = 30;
}
void dabai::graph_set_key_range(int time_value)
{
    ui->graph->xAxis2->setRange(0,100*time_value);
    ui->graph->xAxis->setRange(0,100*time_value);
    g_tem_data.clear();
    g_pm25_data.clear();
    ui->graph->replot();
}

void dabai::graph_replot()
{
    int loop;
    QVector<double> x_tem(101),y_tem(101);
    QVector<double> x_pm25(101),y_pm25(101);
    for(loop = 0 ; loop < dabai::g_pm25_data.size() ; loop ++)
    {
        x_tem[loop] = loop*g_time_value;
        y_tem[loop] = dabai::g_tem_data.at(loop);
    }
    for(loop = 0 ; loop < dabai::g_pm25_data.size() ; loop ++)
    {
        x_pm25[loop] = loop*g_time_value;
        y_pm25[loop] = dabai::g_pm25_data.at(loop);
    }
    ui->graph->graph(0)->setData(x_tem,y_tem);
    ui->graph->graph(1)->setData(x_pm25,y_pm25);
    ui->graph->replot();
}
