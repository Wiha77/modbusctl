#ifndef MOD_POLLER_H
#define MOD_POLLER_H

#include <QObject>
#include <QThread>
#include <QMutex>

extern "C" {
#include <modbus.h>
}
#include <cstdio>
#include <errno.h>

class Mod_poller : public QThread
{
    Q_OBJECT
public:
    explicit Mod_poller(QObject *parent = 0);
    uint16_t buf[1024];
    modbus_t *mc;
    QString com_port;
    int     mod_adr;
    int num_regs;
    bool is_conected;
signals:
    void loging (const QString & link);
    void loaded_buf (void);

public slots:
        void ConnectComPort(void);
        void start_polling(void);
        void stop_polling(void);
        void send_reg(int reg_adr, int val );
private:


        void load_regs(void);
        void run();
        QMutex mutex;
        bool is_polling;

};



#endif // MOD_POLLER_H
