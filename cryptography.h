#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include "QString"
#include "QFileInfo"

class Cryptography
{
public:
    Cryptography(QString strFileName);
    bool isExist();
    QString MD5();
    QString size();
    QString Date();
    QString SHA1();
private:
    QString m_strFilePath;
    QFileInfo m_fileInfo;
};

#endif // CRYPTOGRAPHY_H
