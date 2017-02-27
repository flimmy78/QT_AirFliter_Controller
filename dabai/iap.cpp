#include "iap.h"
extern crc8 mycrc;
namespace Ui {
class dabai;
}

void dabai::choose_app(int app)
{
    if(ui->label_tcm300ID->text()== "ID:")
    {
        myHelper::ShowMessageBoxErrorX("未选择设备!或者设备不在线!请检查或者点击刷新后重试!");
        return;
    }
    QByteArray send_data;
    QByteArray ID;
    ID.resize(4);
    QString target = ui->device->currentText();
    int clientID = target.split(":")[0].toInt();
    QString TCM300_id = (ui->label_tcm300ID->text()).split(":")[1];
    ID = myHelper::HexStrToByteArray(TCM300_id);
    send_data.resize(19);
    send_data[0] = 0XAA;
    send_data[1] = 0X55;
    send_data[2] = 0X11;
    send_data[3] = ID.at(0);
    send_data[4] = ID.at(1);
    send_data[5] = ID.at(2);
    send_data[6] = ID.at(3);
    send_data[7] = 0X01;
    send_data[8] = 0X0A;
    send_data[9] = 0XE1;
    send_data[10] = app;
    send_data[11] = 0XFF;
    send_data[12] = 0XFF;
    send_data[13] = 0XFF;
    send_data[14] = 0XFF;
    send_data[15] = 0XFF;
    send_data[16] = 0XFF;
    send_data[17] = 0XFF;
    //send_data[18] = 0X11;
    mycrc.SetCRC8Sub(send_data.data(),18);
    tcpServer->SendData(clientID,send_data);
}
void dabai::transmission_begin_code_by_wifi(QFile* &app)
{
    //char send_buf[6] = {0};
    int send_size;
    qint64 file_size = app->size();
    send_size = file_size/128;
    if(file_size%128)
    {
        send_size++;
    }
    ui->progressBar_download->setRange(0,send_size-1);
    char* send_buf = (char*)malloc(5);

    send_buf[0] = 03;//SEND开始传输数据信号
    send_buf[2] = send_size & 0X000000FF;
    send_buf[1] = send_size>>8 & 0X000000FF;
    send_buf[3] = 0;
    send_buf[4] = 0;

    //send_buf[1] = 01;
    dabai::transmission_data_by_wifi(0XF1,send_buf,5);
    free((void*)send_buf);
}

void dabai::transmission_start_code_by_wifi()
{
    //char send_buf[6] = {0};
    char* send_buf = (char*)malloc(5);

    send_buf[0] = 01;
    send_buf[1] = 0;
    send_buf[2] = 0;
    send_buf[3] = 0;
    send_buf[4] = 0;

    //send_buf[1] = 01;
    dabai::transmission_data_by_wifi(0XF1,send_buf,5);
    free((void*)send_buf);
}

void dabai::device_iap_need_file(int app_num)
{

    QMessageBox msg(this);
    switch(app_num)
    {
    case 1://当前设备使用app_base固件需要app_1.bin文件升级
        ui->read_data->append(tr("读取设备固件信息成功\n当前设备正在运行固件 app_base\n需要固件app_1.bin文件"));
        G_App_file->setFileName("./app_1.bin");
        if(check_file_then_open(G_App_file))
        {
            msg.setStyleSheet("font:10pt '宋体'");
            msg.setWindowTitle("固件升级");
            msg.setText("已经查找到适配的固件文件\n是否开始升级");
            msg.setIcon(QMessageBox::Warning);
            QAbstractButton *yes = msg.addButton("开始升级",QMessageBox::ActionRole);
            QAbstractButton *no = msg.addButton("取消升级",QMessageBox::RejectRole);
            msg.exec();
            if(msg.clickedButton() == yes)
            {
               ui->read_data->append(tr("正在升级"));
               transmission_begin_code_by_wifi(G_App_file);
            }
            if(msg.clickedButton() == no)
            {
               ui->read_data->append(tr("取消升级"));

            }
        }
        else
            {
            myHelper::ShowMessageBoxErrorX("当前设备需要的固件'app_1.bin'未找到!");
            ui->read_data->append(tr("取消升级"));
            }
        break;

    case 2://当前设备使用app_1固件需要app_2.bin文件升级
        ui->read_data->append(tr("读取设备固件信息成功\n当前设备正在运行固件 app_1\n需要固件app_2.bin文件"));
        G_App_file->setFileName("./app_2.bin");
        if(check_file_then_open(G_App_file))
        {
            msg.setStyleSheet("font:10pt '宋体'");
            msg.setWindowTitle("固件升级");
            msg.setText("已经查找到适配的固件文件\n是否开始升级");
            msg.setIcon(QMessageBox::Warning);
            QAbstractButton *yes = msg.addButton("开始升级",QMessageBox::ActionRole);
            QAbstractButton *no = msg.addButton("取消升级",QMessageBox::RejectRole);
            msg.exec();
            if(msg.clickedButton() == yes)
            {
               ui->read_data->append(tr("正在升级"));
               transmission_begin_code_by_wifi(G_App_file);
            }
            if(msg.clickedButton() == no)
            {
               ui->read_data->append(tr("取消升级"));

            }
        }
        else
            {
            myHelper::ShowMessageBoxErrorX("当前设备需要的固件'app_2.bin'未找到!");
            ui->read_data->append(tr("取消升级"));
            }
        break;

    case 3://当前设备使用app_2固件需要app_3.bin文件升级
        ui->read_data->append(tr("读取设备固件信息成功\n当前设备正在运行固件 app_2\n需要固件app_3.bin文件"));
        G_App_file->setFileName("./app_3.bin");
        if(check_file_then_open(G_App_file))
        {
            msg.setStyleSheet("font:10pt '宋体'");
            msg.setWindowTitle("固件升级");
            msg.setText("已经查找到适配的固件文件\n是否开始升级");
            msg.setIcon(QMessageBox::Warning);
            QAbstractButton *yes = msg.addButton("开始升级",QMessageBox::ActionRole);
            QAbstractButton *no = msg.addButton("取消升级",QMessageBox::RejectRole);
            msg.exec();
            if(msg.clickedButton() == yes)
            {
               ui->read_data->append(tr("正在升级"));
               transmission_begin_code_by_wifi(G_App_file);
            }
            if(msg.clickedButton() == no)
            {
               ui->read_data->append(tr("取消升级"));

            }
        }
        else
            {
            myHelper::ShowMessageBoxErrorX("当前设备需要的固件'app_3.bin'未找到!");
            ui->read_data->append(tr("取消升级"));
            }
        break;

    case 4://当前设备使用app_3固件需要app_1.bin文件升级
        ui->read_data->append(tr("读取设备固件信息成功\n当前设备正在运行固件 app_3\n需要固件app_1.bin文件"));
        G_App_file->setFileName("./app_1.bin");
        if(check_file_then_open(G_App_file))
        {
            msg.setStyleSheet("font:10pt '宋体'");
            msg.setWindowTitle("固件升级");
            msg.setText("已经查找到适配的固件文件\n是否开始升级");
            msg.setIcon(QMessageBox::Warning);
            QAbstractButton *yes = msg.addButton("开始升级",QMessageBox::ActionRole);
            QAbstractButton *no = msg.addButton("取消升级",QMessageBox::RejectRole);
            msg.exec();
            if(msg.clickedButton() == yes)
            {
               ui->read_data->append(tr("正在升级"));
               transmission_begin_code_by_wifi(G_App_file);
            }
            if(msg.clickedButton() == no)
            {
               ui->read_data->append(tr("取消升级"));

            }
        }
        else
            {
            myHelper::ShowMessageBoxErrorX("当前设备需要的固件'app_1.bin'未找到!");
            ui->read_data->append(tr("取消升级"));
            }
        break;
    default:
        break;
    }
}
