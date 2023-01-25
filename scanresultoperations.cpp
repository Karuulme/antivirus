#include "scanresultoperations.h"
scanResultOperations::scanResultOperations(QObject *parent): QObject{parent}
{

}
void scanResultOperations::virusProcesses(QString path,int Options){
    switch(Options){
    case 0: // Quarantine
        qDebug()<<"DOSYAYI KARANTINAYA AL";

    break;
    case 1: // Delete
        qDebug()<<"DOSYAYI SIL";
    break;
    default:

    break;
    }
}
void scanResultOperations::computerOperations(int Options){
    switch(Options){
    case 0: //Wait

    break;
    case 1: //Shut Down
        qDebug()<<"BILGISAYARI KAPAT";

    break;
    case 2: //Restart
         qDebug()<<"BILGISAYARI YENIDEN BASLAT";
    break;
    default:

    break;
    }

}
void scanResultOperations::getApplyResults(QMap<int,QString> malwaress,QMap<int,int> malwareListOptions,int virusOptions,int computerOptions){
    for(int i=0;i<malwaress.size();i++){
        if(virusOptions==0){
            virusProcesses(malwaress[i],malwareListOptions[i]);
        }
        else{
            virusProcesses(malwaress[i],virusOptions-1);
        }
    }
    computerOperations(computerOptions);
}
