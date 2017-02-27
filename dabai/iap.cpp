#include "iap.h"
extern crc8 mycrc;
namespace Ui {
class dabai;
}

void dabai::choose_app(int app)
{
    if(ui->label_tcm300ID->text()== "ID:")
    {
        myHelper::ShowMessageBoxErrorX("δѡ���豸!�����豸������!������ߵ��ˢ�º�����!");
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

    send_buf[0] = 03;//SEND��ʼ���������ź�
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
    case 1://��ǰ�豸ʹ��app_base�̼���Ҫapp_1.bin�ļ�����
        ui->read_data->append(tr("��ȡ�豸�̼���Ϣ�ɹ�\n��ǰ�豸�������й̼� app_base\n��Ҫ�̼�app_1.bin�ļ�"));
        G_App_file->setFileName("./app_1.bin");
        if(check_file_then_open(G_App_file))
        {
            msg.setStyleSheet("font:10pt '����'");
            msg.setWindowTitle("�̼�����");
            msg.setText("�Ѿ����ҵ�����Ĺ̼��ļ�\n�Ƿ�ʼ����");
            msg.setIcon(QMessageBox::Warning);
            QAbstractButton *yes = msg.addButton("��ʼ����",QMessageBox::ActionRole);
            QAbstractButton *no = msg.addButton("ȡ������",QMessageBox::RejectRole);
            msg.exec();
            if(msg.clickedButton() == yes)
            {
               ui->read_data->append(tr("��������"));
               transmission_begin_code_by_wifi(G_App_file);
            }
            if(msg.clickedButton() == no)
            {
               ui->read_data->append(tr("ȡ������"));

            }
        }
        else
            {
            myHelper::ShowMessageBoxErrorX("��ǰ�豸��Ҫ�Ĺ̼�'app_1.bin'δ�ҵ�!");
            ui->read_data->append(tr("ȡ������"));
            }
        break;

    case 2://��ǰ�豸ʹ��app_1�̼���Ҫapp_2.bin�ļ�����
        ui->read_data->append(tr("��ȡ�豸�̼���Ϣ�ɹ�\n��ǰ�豸�������й̼� app_1\n��Ҫ�̼�app_2.bin�ļ�"));
        G_App_file->setFileName("./app_2.bin");
        if(check_file_then_open(G_App_file))
        {
            msg.setStyleSheet("font:10pt '����'");
            msg.setWindowTitle("�̼�����");
            msg.setText("�Ѿ����ҵ�����Ĺ̼��ļ�\n�Ƿ�ʼ����");
            msg.setIcon(QMessageBox::Warning);
            QAbstractButton *yes = msg.addButton("��ʼ����",QMessageBox::ActionRole);
            QAbstractButton *no = msg.addButton("ȡ������",QMessageBox::RejectRole);
            msg.exec();
            if(msg.clickedButton() == yes)
            {
               ui->read_data->append(tr("��������"));
               transmission_begin_code_by_wifi(G_App_file);
            }
            if(msg.clickedButton() == no)
            {
               ui->read_data->append(tr("ȡ������"));

            }
        }
        else
            {
            myHelper::ShowMessageBoxErrorX("��ǰ�豸��Ҫ�Ĺ̼�'app_2.bin'δ�ҵ�!");
            ui->read_data->append(tr("ȡ������"));
            }
        break;

    case 3://��ǰ�豸ʹ��app_2�̼���Ҫapp_3.bin�ļ�����
        ui->read_data->append(tr("��ȡ�豸�̼���Ϣ�ɹ�\n��ǰ�豸�������й̼� app_2\n��Ҫ�̼�app_3.bin�ļ�"));
        G_App_file->setFileName("./app_3.bin");
        if(check_file_then_open(G_App_file))
        {
            msg.setStyleSheet("font:10pt '����'");
            msg.setWindowTitle("�̼�����");
            msg.setText("�Ѿ����ҵ�����Ĺ̼��ļ�\n�Ƿ�ʼ����");
            msg.setIcon(QMessageBox::Warning);
            QAbstractButton *yes = msg.addButton("��ʼ����",QMessageBox::ActionRole);
            QAbstractButton *no = msg.addButton("ȡ������",QMessageBox::RejectRole);
            msg.exec();
            if(msg.clickedButton() == yes)
            {
               ui->read_data->append(tr("��������"));
               transmission_begin_code_by_wifi(G_App_file);
            }
            if(msg.clickedButton() == no)
            {
               ui->read_data->append(tr("ȡ������"));

            }
        }
        else
            {
            myHelper::ShowMessageBoxErrorX("��ǰ�豸��Ҫ�Ĺ̼�'app_3.bin'δ�ҵ�!");
            ui->read_data->append(tr("ȡ������"));
            }
        break;

    case 4://��ǰ�豸ʹ��app_3�̼���Ҫapp_1.bin�ļ�����
        ui->read_data->append(tr("��ȡ�豸�̼���Ϣ�ɹ�\n��ǰ�豸�������й̼� app_3\n��Ҫ�̼�app_1.bin�ļ�"));
        G_App_file->setFileName("./app_1.bin");
        if(check_file_then_open(G_App_file))
        {
            msg.setStyleSheet("font:10pt '����'");
            msg.setWindowTitle("�̼�����");
            msg.setText("�Ѿ����ҵ�����Ĺ̼��ļ�\n�Ƿ�ʼ����");
            msg.setIcon(QMessageBox::Warning);
            QAbstractButton *yes = msg.addButton("��ʼ����",QMessageBox::ActionRole);
            QAbstractButton *no = msg.addButton("ȡ������",QMessageBox::RejectRole);
            msg.exec();
            if(msg.clickedButton() == yes)
            {
               ui->read_data->append(tr("��������"));
               transmission_begin_code_by_wifi(G_App_file);
            }
            if(msg.clickedButton() == no)
            {
               ui->read_data->append(tr("ȡ������"));

            }
        }
        else
            {
            myHelper::ShowMessageBoxErrorX("��ǰ�豸��Ҫ�Ĺ̼�'app_1.bin'δ�ҵ�!");
            ui->read_data->append(tr("ȡ������"));
            }
        break;
    default:
        break;
    }
}
