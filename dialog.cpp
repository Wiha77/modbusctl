#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    my_mp=new Mod_poller;
    my_mp->num_regs=18;
    my_mp->com_port =ui->lineEdit_port->text();
    my_mp->mod_adr=ui->spinBox_adr->value();


    QObject::connect(ui->pushButton_con,SIGNAL(clicked()),my_mp , SLOT(ConnectComPort()) );
    QObject::connect(ui->pushButton_start,SIGNAL(clicked()),my_mp , SLOT(start_polling()) );
    QObject::connect(ui->pushButton_stop,SIGNAL(clicked()),my_mp , SLOT(stop_polling()) );
    QObject::connect(ui->pushButton_send,SIGNAL(clicked()),this , SLOT(send_registers()) );
    QObject::connect(ui->spinBox_adr ,SIGNAL(valueChanged(int)),my_mp , SLOT(set_mod_addr(int)) );

    QObject::connect(ui->pushButton_kr ,SIGNAL(clicked()),this , SLOT(reset_k()) );
    QObject::connect(ui->pushButton_ks ,SIGNAL(clicked()),this , SLOT(send_k()) );
    QObject::connect(ui->pushButton_fr ,SIGNAL(clicked()),this , SLOT(reset_f()) );
    QObject::connect(ui->pushButton_fs ,SIGNAL(clicked()),this , SLOT(send_f()) );
    QObject::connect(my_mp ,SIGNAL(loging(const QString & )),ui->label_help , SLOT(setText(const QString &)) );
    QObject::connect(my_mp,SIGNAL(loaded_buf()),this , SLOT(get_registers()) );

    QObject::connect(ui->checkBox_f0,SIGNAL(stateChanged(int)),this , SLOT(send_f()) );
    QObject::connect(ui->checkBox_f1,SIGNAL(stateChanged(int)),this , SLOT(send_f()) );
    QObject::connect(ui->checkBox_f2,SIGNAL(stateChanged(int)),this , SLOT(send_f()) );
    QObject::connect(ui->checkBox_f3,SIGNAL(stateChanged(int)),this , SLOT(send_f()) );
    QObject::connect(ui->checkBox_f4,SIGNAL(stateChanged(int)),this , SLOT(send_f()) );
    QObject::connect(ui->checkBox_f5,SIGNAL(stateChanged(int)),this , SLOT(send_f()) );
    QObject::connect(ui->checkBox_f6,SIGNAL(stateChanged(int)),this , SLOT(send_f()) );
    QObject::connect(ui->checkBox_f7,SIGNAL(stateChanged(int)),this , SLOT(send_f()) );
    QObject::connect(ui->checkBox_f8,SIGNAL(stateChanged(int)),this , SLOT(send_f()) );
    QObject::connect(ui->checkBox_f9,SIGNAL(stateChanged(int)),this , SLOT(send_f()) );
    QObject::connect(ui->checkBox_f10,SIGNAL(stateChanged(int)),this , SLOT(send_f()) );
    QObject::connect(ui->checkBox_f11,SIGNAL(stateChanged(int)),this , SLOT(send_f()) );

    QObject::connect(ui->checkBox_k0,SIGNAL(stateChanged(int)),this , SLOT(send_k()) );
    QObject::connect(ui->checkBox_k1,SIGNAL(stateChanged(int)),this , SLOT(send_k()) );
    QObject::connect(ui->checkBox_k2,SIGNAL(stateChanged(int)),this , SLOT(send_k()) );
    QObject::connect(ui->checkBox_k3,SIGNAL(stateChanged(int)),this , SLOT(send_k()) );
    QObject::connect(ui->checkBox_k4,SIGNAL(stateChanged(int)),this , SLOT(send_k()) );
    QObject::connect(ui->checkBox_k5,SIGNAL(stateChanged(int)),this , SLOT(send_k()) );
    QObject::connect(ui->checkBox_k6,SIGNAL(stateChanged(int)),this , SLOT(send_k()) );
    QObject::connect(ui->checkBox_k7,SIGNAL(stateChanged(int)),this , SLOT(send_k()) );
    QObject::connect(ui->checkBox_k8,SIGNAL(stateChanged(int)),this , SLOT(send_k()) );
    QObject::connect(ui->checkBox_k9,SIGNAL(stateChanged(int)),this , SLOT(send_k()) );


   //  my_mp->ConnectComPort();


    ui->tableWidget->setRowCount(my_mp->num_regs+1);
    ui->tableWidget->setColumnCount(2);

    const char * namreg[]={"MBReg_AdrrModbus",
                           "MBReg_CommandFlags",
                           "MBReg_StateFlags",
                           "MBReg_Sensor_Up",
                           "MBReg_Densor_Imotor",
                           "MBReg_Cur_zero_offset",
                           "MBReg_Cur_gain",
                           "MBReg_CardsData_0",
                           "MBReg_CardsData_1",
                           "MBReg_CardsData_2",
                           "MBReg_CardsData_3",
                           "MBReg_CardsData_4",
                           "MBReg_CardsData_5",
                           "MBReg_CardsData_6",
                           "MBReg_CardsData_7",
                           "MBReg_CardsData_8",
                           "MBReg_CardsData_9",
                           "MBReg_CardsData_10"

                          };
    for(int i=0;i<my_mp->num_regs;i++)
    {
    ui->tableWidget->setItem(i,0,new QTableWidgetItem(namreg[i]));
    }

}

Dialog::~Dialog()
{
    my_mp->stop_polling();
    my_mp->wait();
    delete ui;
}

void Dialog::get_registers(void)
{


  // ui->label_help->setText("Dialog::get_registers");

   uint16_t *regs=my_mp->buf;



   for(int i=0;i<my_mp->num_regs;i++)
   {

   ui->tableWidget->setItem(i,1,new QTableWidgetItem(QStringLiteral("%1").arg(*regs)));
   regs++;

   }
   regs=my_mp->buf+1;
   ui->checkBox_k0->setChecked(*regs & 0x01);
   ui->checkBox_k1->setChecked(*regs & 0x02);
   ui->checkBox_k2->setChecked(*regs & 0x04);
   ui->checkBox_k3->setChecked(*regs & 0x08);
   ui->checkBox_k4->setChecked(*regs & 0x10);
   ui->checkBox_k5->setChecked(*regs & 0x20);
   ui->checkBox_k6->setChecked(*regs & 0x40);
   ui->checkBox_k7->setChecked(*regs & 0x80);
   ui->checkBox_k8->setChecked(*regs & 0x0100);
   ui->checkBox_k9->setChecked(*regs & 0x0200);
   ui->checkBox_k10->setChecked(*regs & 0x0400);
   ui->checkBox_k11->setChecked(*regs & 0x0800);
   regs=my_mp->buf+2;
   ui->checkBox_f0->setChecked(*regs & 0x01);
   ui->checkBox_f1->setChecked(*regs & 0x02);
   ui->checkBox_f2->setChecked(*regs & 0x04);
   ui->checkBox_f3->setChecked(*regs & 0x08);
   ui->checkBox_f4->setChecked(*regs & 0x10);
   ui->checkBox_f5->setChecked(*regs & 0x20);
   ui->checkBox_f6->setChecked(*regs & 0x40);
   ui->checkBox_f7->setChecked(*regs & 0x80);
   ui->checkBox_f8->setChecked(*regs & 0x0100);
   ui->checkBox_f9->setChecked(*regs & 0x0200);
   ui->checkBox_f10->setChecked(*regs & 0x0400);
   ui->checkBox_f11->setChecked(*regs & 0x0800);


   return ;

}

void Dialog::reset_k(void)
{
    ui->checkBox_k0->setChecked(0);
    ui->checkBox_k1->setChecked(0);
    ui->checkBox_k2->setChecked(0);
    ui->checkBox_k3->setChecked(0);
    ui->checkBox_k4->setChecked(0);
    ui->checkBox_k5->setChecked(0);
    ui->checkBox_k6->setChecked(0);
    ui->checkBox_k7->setChecked(0);
    ui->checkBox_k8->setChecked(0);
    ui->checkBox_k9->setChecked(0);
    ui->checkBox_k10->setChecked(0);
    ui->checkBox_k11->setChecked(0);
    send_k();
}

void Dialog::send_k(void)
{
    int val=0;
    val|=ui->checkBox_k11->isChecked(); val=val<<1;
    val|=ui->checkBox_k10->isChecked();val= val<<1;
    val|=ui->checkBox_k9->isChecked(); val=val<<1;
    val|=ui->checkBox_k8->isChecked(); val=val<<1;
    val|=ui->checkBox_k7->isChecked(); val=val<<1;
    val|=ui->checkBox_k6->isChecked(); val=val<<1;
    val|=ui->checkBox_k5->isChecked(); val=val<<1;
    val|=ui->checkBox_k4->isChecked(); val=val<<1;
    val|=ui->checkBox_k3->isChecked(); val=val<<1;
    val|=ui->checkBox_k2->isChecked(); val=val<<1;
    val|=ui->checkBox_k1->isChecked(); val=val<<1;
    val|=ui->checkBox_k0->isChecked();

    my_mp->send_reg(1, val);


}

void Dialog::reset_f(void)
{
    ui->checkBox_f0->setChecked(0);
    ui->checkBox_f1->setChecked(0);
    ui->checkBox_f2->setChecked(0);
    ui->checkBox_f3->setChecked(0);
    ui->checkBox_f4->setChecked(0);
    ui->checkBox_f5->setChecked(0);
    ui->checkBox_f6->setChecked(0);
    ui->checkBox_f7->setChecked(0);
    ui->checkBox_f8->setChecked(0);
    ui->checkBox_f9->setChecked(0);
    ui->checkBox_f10->setChecked(0);
    ui->checkBox_f11->setChecked(0);
    send_f();
}

void Dialog::send_f(void)
{
    int val=0;
    val|=ui->checkBox_f11->isChecked(); val=val<<1;
    val|=ui->checkBox_f10->isChecked();val= val<<1;
    val|=ui->checkBox_f9->isChecked(); val=val<<1;
    val|=ui->checkBox_f8->isChecked(); val=val<<1;
    val|=ui->checkBox_f7->isChecked(); val=val<<1;
    val|=ui->checkBox_f6->isChecked(); val=val<<1;
    val|=ui->checkBox_f5->isChecked(); val=val<<1;
    val|=ui->checkBox_f4->isChecked(); val=val<<1;
    val|=ui->checkBox_f3->isChecked(); val=val<<1;
    val|=ui->checkBox_f2->isChecked(); val=val<<1;
    val|=ui->checkBox_f1->isChecked(); val=val<<1;
    val|=ui->checkBox_f0->isChecked();


 my_mp->send_reg(2, val);

}

void Dialog::send_registers(void)
{
       if(my_mp->is_conected)my_mp->send_reg(ui->spinBox_Reg->value(),ui->spinBox_Val->value());
}

