#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "TuringMachine.h"
#include <QFileDialog>
#include <QTextStream>
#include <QTime>
#include <QCoreApplication>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    TuringMachine *TM=NULL;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Load_pushButton_clicked();

    void on_Step_pushButton_clicked();

    void on_Browse_pushButton_clicked();

    void on_FilePath_lineEdit_textChanged(const QString &arg1);

    void on_str_lineEdit_textChanged(const QString &arg1);

    void on_Auto_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void Update(TuringMachine *TurMac);
    void SetStatus(const QString &str);
    void Sleep(const int &msec);
};
#endif // MAINWINDOW_H
