#include "cryptography.h"
#include "QCryptographicHash"
#include "QFile"
#include "QByteArray"
#include "QFileInfo"
#include "QDateTime"

Cryptography::Cryptography(QString strFileName)
{
    m_strFilePath = strFileName;
    m_fileInfo.setFile(strFileName);
}

bool Cryptography::isExist()
{
    return m_fileInfo.isFile();
}

QString Cryptography::size()
{
    int iSize = m_fileInfo.size();
    QString strSize;
    if(iSize == 1)
        strSize = QString::number(iSize) + " byte";
    else
        strSize = QString::number(iSize) + " bytes";
    return strSize;
}

QString Cryptography::Date()
{
    return m_fileInfo.lastModified().toString("yyyy-MM-dd hh:mm:ss");
}

QString Cryptography::MD5()
{
   QFile file(m_strFilePath);
   file.open(QIODevice::ReadOnly);
   QByteArray ba = QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5);
   file.close();
   return ba.toHex().constData();
}

QString Cryptography::SHA1()
{
   QFile file(m_strFilePath);
   file.open(QIODevice::ReadOnly);
   QByteArray ba = QCryptographicHash::hash(file.readAll(), QCryptographicHash::Sha1);
   file.close();
   return ba.toHex().constData();
}
