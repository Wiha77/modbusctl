#include "mod_poller.h"



Mod_poller::Mod_poller(QObject *parent) : QThread(parent)
{
    mc=0;
    is_conected=false;
    is_polling=false;

}

void Mod_poller::set_mod_addr(int val)
{
 mod_adr=val;
}

void Mod_poller::ConnectComPort()
{
if(mc!=0) {
    modbus_close(mc);
    modbus_free(mc);
    mc=0;}
if(!mc)mc=modbus_new_rtu((const char*)com_port.toUtf8().constData(),115200,'N',8,1);

if (mc)
{

    if(modbus_connect(mc)==-1)
    {
        //fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        emit(loging ("Don't connect to port"));
        modbus_close(mc);
        modbus_free(mc);
        mc=0;
        return;

        //
    }
    else emit(loging ("Connected"));
    modbus_set_slave(mc, mod_adr);
    modbus_set_response_timeout(mc, 0,500000);
    is_conected=true;
   return ;
}




}

void Mod_poller::send_reg(int reg_adr, int val )
{
    emit(loging("try mutex lock"));
     mutex.lock();
     emit(loging("mutex unlocked"));
    if(modbus_write_register(mc, reg_adr, val)==1)emit(loging("Saved registers"));
    else emit(loging("don't save registers"));
      mutex.unlock();
}

void Mod_poller::load_regs(void)
{
    int ret;

if(mc)
    if((ret=modbus_read_registers(mc,0 ,num_regs,buf))==-1)
    {
      //emit(loging("Don't read registers"));
      return ;
    }

 //emit(loging("Readed registers"));
 emit(loaded_buf());

}

void Mod_poller::start_polling(void)
{
 if(is_conected)
 {
    is_polling=true;
         this->start();
 }
}

void Mod_poller::stop_polling(void)
{
 is_polling=false;
}

void Mod_poller::run()
{
     //qDebug() << "poller thread: " << thread()->currentThreadId();
 emit(loging("Start  reading registers"));

while(1)
{

    if((!is_conected) || (!is_polling)){emit(loging("Stoping  read registers"));return;}
    mutex.lock();
     load_regs();
     mutex.unlock();
     msleep(100);


}
}
