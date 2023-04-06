#include "../Headers/filepathtransactions.h"

filePathTransactions::filePathTransactions(QObject *parent): QObject{parent}
{

}
//-----------------------------------------------------------------------------------------
int  filePathTransactions::setRegCreateBank(HKEY hKey, Kstring path, Kstring key, Kstring value) { // KAYIT DEFTERİNE VERİ EKLEME VE GÜNCELLEME
    Kstring sPath;
    for (int i = 0; i < path.length(); i++) {		//path space clear; //boşluk olduğunda hatalı dosya işlemi yapıyor.
        if (path[i] != ' ') {
            sPath += path[i];
        }
    }
    HKEY hkRegOpen;
    DWORD dRegReturn;
    sPath = sPath + "\0";
    LONG res1 = RegCreateKeyExA(hKey, sPath.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkRegOpen, &dRegReturn);
    if (res1 != ERROR_SUCCESS)
        return res1;
    LONG res2 = RegSetValueExA(hkRegOpen, (LPCSTR)key.c_str(), 0, REG_SZ, (LPBYTE)value.c_str(), strlen((char*)value.c_str()) + 1);
    if (res2 != ERROR_SUCCESS)
        return res2;
    RegCloseKey(hkRegOpen);
    return 0;
}//-----------------------------------------------------------------------------------------
void filePathTransactions::getProgramTime(unsigned __int8 value){
    setRegCreateBank(KMachine,KLocal,"Time",std::to_string(value));
}
//-----------------------------------------------------------------------------------------
int filePathTransactions::setRegQuestion(QString filePath,unsigned long int pID){// DOSYA HASH'LEME VE KAYIT İŞLEMLERİ
    RegProgramList reg;
    reg.pHash=getfileHash(filePath).toStdString();
    if(reg.pHash=="000"){
        return 1;
    }
    reg = upRegListControl(reg.pHash);
    if (reg.pRunCount !=-1)
    {
        reg.pRunCount=0;
        if(KDllSource > reg.pRunCount){
            //----------------------------------------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
            // DEĞERİ KÜÇÜK İSE
            // DLL injection YAPILACAK
            emit setDllEnjection(pID);
            //----------------------------------------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        }
        setRegCreateBank(KMachine, KBank + reg.pFile, "pRunCount", KToString(reg.pRunCount));// güncelleme

    }
    else
    {
        regeditNewRecord(reg);// yeni kayıt
        //----------------------------------------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        //DLL injection YAPILACAK
        emit setDllEnjection(pID);
        //----------------------------------------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    }
    return 0;
}

//-----------------------------------------------------------------------------------------
QString filePathTransactions::getfileHash(QString filePath){ //DOSYA HASH DEĞERİ
    QString retValue="000";
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray exeFile=file.readAll();
        QString hash = QString(QCryptographicHash::hash((exeFile+"kar"+"ul"),QCryptographicHash::Sha256).toHex());
        retValue= hash.toLocal8Bit().data();
    }
    file.close();
    return retValue;
}
//-----------------------------------------------------------------------------------------
int filePathTransactions::regeditNewRecord(RegProgramList regProgram){ //YENİ KAYIT EKLEME
    regListIndex++;
    setRegCreateBank(KMachine, KBank + KToString(1000 +regListIndex), "pHash", regProgram.pHash);
    setRegCreateBank(KMachine, KBank + KToString(1000 +regListIndex), "pRunCount", KToString(regProgram.pRunCount));
    regList[regListIndex-1]=regProgram;
}
//-----------------------------------------------------------------------------------------
RegProgramList filePathTransactions::upRegListControl(Kstring regg) { // LİSTEDEN KAYDI BULUR VE +1 EKLEYEREK GERİ DÖNDÜRÜR
    RegProgramList regProgramList;
    regProgramList.pHash=regg;
    regProgramList.pRunCount= - 1;
    for (int i = 0; i < regListIndex; i++){
        if (regList[i].pHash == regg) {
            regList[i].pRunCount++;
            regProgramList = regList[i];
            return regProgramList;
        }
    }
    return regProgramList;
}
//-----------------------------------------------------------------------------------------
bool filePathTransactions::boolRegListControl(Kstring regg){
    for (int i = 0; i < regListIndex; i++)
    {
        if (regList[i].pHash == regg) {
            return true;
        }
    }
    return false;
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::getFilePahtReg(QString  filePath,unsigned long int pID){//AÇILAN İŞLEMLER BURAYA GÖNDERİLİR
    setRegQuestion(filePath,pID);
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::getRegList(Kmap<int, RegProgramList> reg){// BAŞLANGIÇTA KAYIT DEFTERİNDEKİ LİSTE BURAYA GÖNDERİLİR
    regList=reg;
    regListIndex=reg.size();
}
//-----------------------------------------------------------------------------------------
void filePathTransactions::getfileChangesNotification(QString filePath){ // BİR .EXE DOSYASI OLUŞTURULDUĞUNDA BURAYA GELİR
      RegProgramList fileChangesProgram;
      fileChangesProgram.pFile=KToString(1000 +regListIndex);
      fileChangesProgram.pHash=getfileHash(filePath).toStdString();
      if(fileChangesProgram.pHash!="000"){
          if(!boolRegListControl(fileChangesProgram.pHash)){
              regeditNewRecord(fileChangesProgram);
              //Bundan sonra taramaya gidecek
          }
      }
}
//-----------------------------------------------------------------------------------------

