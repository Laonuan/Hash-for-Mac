#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_btnBrowser_clicked();
    void on_btnClear_clicked();
    void on_btnCopy_clicked();
    void on_btnSave_clicked();
    void on_btnExit_clicked();

    void on_actionMinimize_triggered();

    void on_actionClose_triggered();

private:
    Ui::MainWindow *ui;

    void add_text(QString);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *e);
    void GetInfo(QString strFilePath);

    //声明三个鼠标事件函数
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    //鼠标是否按下属性
    bool m_bPressed=false;

    //按下后当前鼠标位置属性
    QPoint m_point;

};

#endif // MAINWINDOW_H
