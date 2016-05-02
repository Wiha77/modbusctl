#include "dialog.h"
#include <modbus.h>
#include <QApplication>
#include "mod_poller.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    int ret;
    w.show();



    ret = a.exec();


    return ret;
}
