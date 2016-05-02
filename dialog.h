#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include "mod_poller.h"


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    modbus_t *mc;
    Mod_poller *my_mp;


public slots:
        void send_registers(void);
        void get_registers(void);
        void reset_k(void);
        void send_k(void);
        void reset_f(void);
        void send_f(void);

};

#endif // DIALOG_H
