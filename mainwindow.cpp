#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cryptography.h"
#include "QFileDialog"
#include "QDebug"
#include "QCryptographicHash"
#include "QDropEvent"
#include "QUrl"
#include "QMimeData"
#include "QStandardPaths"
#include "QTextStream"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setAcceptDrops(true);
    ui->setupUi(this);
    ui->lGitHub->setOpenExternalLinks(true);
    ui->lGitHub->setText(tr("<a href=\"https://github.com/Laonuan/Hash-for-Mac/\">@GitHub"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_text(QString strText)
{
    ui->textBrowser->append(strText);
}

void MainWindow::on_btnBrowser_clicked()
{
    ui->btnBrowser->setEnabled(false);
    //定义文件对话框类
    QFileDialog fileDialog;
    //打开文件模式
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    //定义文件对话框标题
    fileDialog.setWindowTitle(tr("Open File"));
    //设置默认文件路径
    QString strPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    fileDialog.setDirectory(strPath);
    //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
    fileDialog.setFileMode(QFileDialog::ExistingFiles);
    //设置视图模式
    fileDialog.setViewMode(QFileDialog::List);

    if(fileDialog.exec())
    {
        QStringList strFilePathList = fileDialog.selectedFiles();
        foreach(QString strFilePath, strFilePathList)
            this->GetInfo(strFilePath);
    }

    ui->btnBrowser->setEnabled(true);

}

void MainWindow::on_btnClear_clicked()
{
    ui->textBrowser->clear();
}

void MainWindow::on_btnCopy_clicked()
{
    ui->textBrowser->selectAll();
    ui->textBrowser->copy();
}

void MainWindow::on_btnSave_clicked()
{
    ui->btnSave->setEnabled(false);

    QString strText = ui->textBrowser->document()->toPlainText();
    //定义文件对话框类
    QFileDialog fileDialog;
    //打开文件模式
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    //定义文件对话框标题
    fileDialog.setWindowTitle(tr("Save As"));
    //设置默认文件路径
    QString strPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    fileDialog.setDirectory(strPath);
    fileDialog.setNameFilter(tr("Text (*.txt)"));

    if(fileDialog.exec())
    {
        QString strFilePath = fileDialog.selectedFiles().at(0);
        QFile file(strFilePath);
        if(file.open(QIODevice::WriteOnly))
        {
            QTextStream out(&file);
            QString strText = ui->textBrowser->document()->toPlainText();
            out<<strText;
            file.close();
        }
    }

    ui->btnSave->setEnabled(true);
}

void MainWindow::on_btnExit_clicked()
{
    this->close();
}


void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    e->acceptProposedAction(); //可以在这个窗口部件上拖放对象
}


void MainWindow::dropEvent(QDropEvent *e)
{
    QList<QUrl> urls = e->mimeData()->urls();
    foreach(QUrl url, urls)
    {
        QString strFilePath = url.toLocalFile();
        this->GetInfo(strFilePath);
    }
}

void MainWindow::GetInfo(QString strFilePath)
{
    Cryptography crypt(strFilePath);
    if(crypt.isExist())
    {
        this->add_text("File: " + strFilePath);

        if(ui->cbSize->isChecked())
        {
            QString strSize = "Size: " + crypt.size();
            this->add_text(strSize);
        }

        if(ui->cbDate->isChecked())
        {
            QString strDate = "Modify: " + crypt.Date();
            this->add_text(strDate);
        }

        if(ui->cbMD5->isChecked())
        {
            QString strMD5 = "MD5: " + crypt.MD5();
            this->add_text(strMD5);
        }

        if(ui->cbMD5->isChecked())
        {
            QString strSHA1 = "SHA1: " + crypt.SHA1();
            this->add_text(strSHA1);
        }

        this->add_text("");
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)//判断左键是否按下
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bPressed = false;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
        move(event->pos() - m_point + pos());//移动当前窗口
}


void MainWindow::on_actionMinimize_triggered()
{
    this->showMinimized();
}

void MainWindow::on_actionClose_triggered()
{
    this->close();
}
