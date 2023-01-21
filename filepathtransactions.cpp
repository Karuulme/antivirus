#include "filepathtransactions.h"

filePathTransactions::filePathTransactions(QObject *parent): QObject{parent}
{

}
int  filePathTransactions::setRegCreateBank(HKEY hKey, Kstring path, Kstring key, Kstring value) {
    Kstring sPath;
    Kstring sKey= key;
    Kstring sValue= value;
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
    LONG res2 = RegSetValueExA(hkRegOpen, (LPCSTR)sKey.c_str(), 0, REG_SZ, (LPBYTE)sValue.c_str(), strlen((char*)sValue.c_str()) + 1);
    if (res2 != ERROR_SUCCESS)
        return res2;
    RegCloseKey(hkRegOpen);
    return 0;
}


int filePathTransactions::setRegQuestion(QString filePath){
    QFile file(filePath);
    RegProgramList reg;
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray exeFile=file.readAll();
        QString blah = QString(QCryptographicHash::hash((exeFile+"kar"+"ul"),QCryptographicHash::Sha256).toHex());
        reg.pHash = blah.toLocal8Bit().data();
    }
    else{
         file.close();
         return 1;
    }
    file.close();
    //RegProgramList reg;
    RegProgramList regRet;
    regRet = upRegListControl(reg.pHash);
    if (regRet.pRunCount !=-1) {
        setRegCreateBank(HKEY_CURRENT_USER, KBank + regRet.pFile, "pRunCount", KToString(regRet.pRunCount));
        qDebug()<<"VAR::"<<QString::fromStdString(regRet.pHash);
    }
    else
    {
        qDebug()<<"YOK::"<<QString::fromStdString(reg.pHash);
        RegProgramList regProgram;
        regListIndex++;
        setRegCreateBank(HKEY_CURRENT_USER, KBank + KToString(1000 +regListIndex), "pHash", reg.pHash);
        setRegCreateBank(HKEY_CURRENT_USER, KBank + KToString(1000 +regListIndex), "pRunCount", KToString(reg.pRunCount));
        regProgram.pHash=reg.pHash;
        regProgram.pRunCount=reg.pRunCount;
        regProgram.pFile=KToString(1000 +regListIndex);
        regList[regListIndex-1]=regProgram;
    }
    return 0;
}
RegProgramList filePathTransactions::upRegListControl(Kstring regg) {
    RegProgramList regProgramList;
    regProgramList.pRunCount= - 1;
    for (int i = 0; i < regList.size(); i++)
    {
        if (regList[i].pHash == regg) {
            regList[i].pRunCount++;
            regProgramList = regList[i];
            return regProgramList;
        }
    }
    return regProgramList;
}
void filePathTransactions::getFilePahtReg(QString *filePath){
    setRegQuestion(*filePath);
    qDebug()<<"getFilePahtReg::"<<*filePath;
}
void filePathTransactions::getRegList(Kmap<int, RegProgramList> reg){
    regList=reg;
    regListIndex=reg.size();
}


