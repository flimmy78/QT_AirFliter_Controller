#ifndef DABAI_H
#define DABAI_H

#include <QMainWindow>
#include "myhelper.h"
#include "mytcpclient.h"
#include "mytcpserver.h"
#include <QRegExpValidator>
#include <QThread>
#include<QTime>
#include<QTimer>
#include <QDateTime>
#include <QDirModel>
#include <QFile>
#include <strstream>
#include <QDebug>
#include "crc.h"

//#include <QProgressDialog>

namespace Ui {
class dabai;
}

class save_data
{
private:
    QByteArray TCM300ID;
};

class dabai : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit dabai(QWidget *parent = 0);
    ~dabai();

private:
    Ui::dabai *ui;
    QList<int> g_pm25_data;
    QList<float> g_tem_data;
    QList<int> g_hum_data;
    int g_time_value;
    int pm2_5_point;


private:
    QTcpSocket *tcpClient;
    myTcpServer *tcpServer;
    save_data *save_datas;
    QTimer *my_timer;
    QFile *G_App_file;

private:
    void init();
    void graph_init();
    void graph_replot();
    void graph_set_key_range(int time_value);
    void get_meachine_state(int index);
    void deal_with_data(QByteArray in_put_data);
    void set_fan_speed(unsigned char speed);

    void switch_operat(unsigned char operat_value);
    void switch_learn();
    void switch_clear();
    void switch_all_clear();


    void sensor_operat(unsigned char operat_value);

    void windows_sensor_learn();
    void windows_sensor_clear();
    void windows_sensor_all_clear();

    void body_sensor_learn();
    void body_sensor_clear();
    void body_sensor_all_clear();

    void get_priority();
    void set_priority(char priority_type,char priority_num);

    void get_life();

    void get_meachine_time();
    void set_meachine_time();

    void choose_app(int app);
    void check_file();
    int check_file_then_open(QFile* &file);
    void read_bin_file();
    int read_iap_page_data_by_wifi(QFile* &app, int num,char* buff ,int &read_num);

    void transmission_iap_data_by_wifi(QFile* &app,int num);
    void transmission_data_by_wifi(int command,char* data,int length);

    void transmission_start_code_by_wifi();
    void transmission_begin_code_by_wifi(QFile* &app);
    void transmission_end_code_by_wifi();

    void device_iap_need_file(int app_num);

private slots:

    void ReadData();
    void ReadError(QAbstractSocket::SocketError);

    void ClientReadData(int clientID,QString IP,int Port,QByteArray data);
    void ClientConnect(int clientID,QString IP,int Port);
    void ClientDisConnect(int clientID,QString IP,int Port);

    //void on_cboxMax_currentIndexChanged(int index);

    void on_listen_clicked();
    void on_clear_rx_buf_clicked();
    void on_clear_tx_buf_clicked();
    void on_send_clicked();
    void on_connect_num_currentIndexChanged(const QString &arg1);
    void on_send_all_clicked();
    void on_device_currentIndexChanged(int index);
    void on_state_refresh_clicked();
    void on_switch_power_clicked();
    void on_switch_low_clicked();
    void on_switch_mid_clicked();
    void on_switch_high_clicked();
    void on_switch_auto_clicked();

    void on_comboBox_operat_currentIndexChanged(int index);
    void on_comboBox_device_type_currentIndexChanged(int index);
    void on_button_execute_clicked();
    void on_button_refresh_clicked();
    void on_comboBox_device_stat_currentIndexChanged(int index);
    void on_state_refresh_2_clicked();
    void on_client_currentIndexChanged(int index);
    void on_button_get_priority_clicked();
    //void on_button_set_priority_clicked();
    void on_button_set_priority_1_clicked();
    void on_button_set_priority_2_clicked();
    void on_button_set_priority_3_clicked();
    void on_button_set_priority_4_clicked();
    void on_button_set_priority_5_clicked();
    void on_button_set_priority_6_clicked();
    void on_button_set_priority_7_clicked();
    void on_button_set_priority_8_clicked();
    void on_comboBox_priority_1_currentIndexChanged(int index);
    void on_comboBox_priority_2_currentIndexChanged(int index);
    void on_comboBox_priority_3_currentIndexChanged(int index);
    void on_comboBox_priority_4_currentIndexChanged(int index);
    void on_comboBox_priority_5_currentIndexChanged(int index);
    void on_comboBox_priority_6_currentIndexChanged(int index);
    void on_comboBox_priority_7_currentIndexChanged(int index);
    void on_comboBox_priority_8_currentIndexChanged(int index);
    void on_button_life_clicked();


    void timer_updata();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_button_check_file_clicked();
    void on_button_iap_clicked();
    void on_button_jump_f_clicked();
    void on_button_jump_clicked();
};

class SleeperThread : public QThread { public:     static void msleep(unsigned long msecs)     {         QThread::msleep(msecs);     } };

#endif // DABAI_H
