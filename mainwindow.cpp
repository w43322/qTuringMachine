#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QFontDatabase::addApplicationFont(":/fonts/Menlo.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Monaco.ttf");
    ui->setupUi(this);
    QFont font("Menlo",30);
    ui->String_label->setFont(font);
    ui->Pointer_label->setFont(font);
    ui->String_label->setText("");
    ui->Pointer_label->setText("");
    ui->K_lineEdit->setReadOnly(true);
    ui->Sigma_lineEdit->setReadOnly(true);
    ui->Gamma_lineEdit->setReadOnly(true);
    ui->q0_lineEdit->setReadOnly(true);
    ui->B_lineEdit->setReadOnly(true);
    ui->F_lineEdit->setReadOnly(true);
    ui->Delta_plainTextEdit->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Update(TuringMachine *TurMac)
{
    ui->String_label->setText(TurMac->Str());
    ui->Pointer_label->setText(TurMac->Pointer()+TurMac->Sta());
}

void MainWindow::SetStatus(const QString &str)
{
    ui->statusbar->showMessage(str);
}

void MainWindow::on_Load_pushButton_clicked()
{
    QRegExp rx("[\\ ]");
    QRegExp rx_endl("[\r\n]");
    QString FilePath=ui->FilePath_lineEdit->text();
    QFile File(FilePath);
    if(!File.open(QFile::ReadOnly|QFile::Text))
    {
        SetStatus("Failed to Open Preset File!");
        ui->str_lineEdit->setEnabled(false);
        ui->Step_pushButton->setEnabled(false);
        ui->Auto_pushButton->setEnabled(false);
        ui->verticalSlider->setEnabled(false);
        return;
    }
    QTextStream TextIn(&File);
    ui->K_lineEdit->setText(TextIn.readLine());
    ui->Sigma_lineEdit->setText(TextIn.readLine());
    ui->Gamma_lineEdit->setText(TextIn.readLine());
    ui->q0_lineEdit->setText(TextIn.readLine());
    ui->B_lineEdit->setText(TextIn.readLine());
    ui->F_lineEdit->setText(TextIn.readLine());
    ui->Delta_plainTextEdit->setPlainText(TextIn.readAll());
    QStringList _K=ui->K_lineEdit->text().split(rx,QString::SkipEmptyParts);
    QStringList _Sigma=ui->Sigma_lineEdit->text().split(rx,QString::SkipEmptyParts);
    QStringList _Gamma=ui->Gamma_lineEdit->text().split(rx,QString::SkipEmptyParts);
    QStringList _Delta=ui->Delta_plainTextEdit->toPlainText()
            .split(rx_endl,QString::SkipEmptyParts);
    QString _q0=ui->q0_lineEdit->text();
    QString _B=ui->B_lineEdit->text();
    QStringList _F=ui->F_lineEdit->text().split(rx,QString::SkipEmptyParts);
    if(TM)delete TM;
    TM=new TuringMachine(_K,_Sigma,_Gamma,_Delta,_q0,_B,_F);
    ui->str_lineEdit->setText("");
    ui->str_lineEdit->setEnabled(true);
    ui->Step_pushButton->setEnabled(true);
    ui->Auto_pushButton->setEnabled(true);
    ui->verticalSlider->setEnabled(true);
    Update(TM);
    SetStatus("Turing Machine Loaded!");
}

void MainWindow::on_Step_pushButton_clicked()
{
    int res=TM->Step();
    switch(res)
    {
    case QTM_OK:
        SetStatus("Iteration Successful.");
        break;
    case QTM_ERROR:
        SetStatus("Iteration Failed! String is not valid language.");break;
    case QTM_FINISHED:
        SetStatus("Iteration Finished.");
        break;
    }
    Update(TM);
}

void MainWindow::on_Auto_pushButton_clicked()
{
    ui->FilePath_lineEdit->setEnabled(false);
    ui->Browse_pushButton->setEnabled(false);
    ui->Load_pushButton->setEnabled(false);
    ui->str_lineEdit->setEnabled(false);
    ui->Step_pushButton->setEnabled(false);
    ui->Auto_pushButton->setEnabled(false);
    ui->checkBox->setEnabled(true);
    bool GoOn=true;
    while(GoOn&&!ui->checkBox->isChecked())
    {
        int Wait=ui->verticalSlider->sliderPosition();
        int res=TM->Step();
        switch(res)
        {
        case QTM_OK:
            SetStatus("Iteration Successful.");
            break;
        case QTM_ERROR:
            SetStatus("Iteration Failed! String is not valid language.");
            GoOn=false;
            break;
        case QTM_FINISHED:
            SetStatus("Iteration Finished.");
            GoOn=false;
            break;
        }
        Update(TM);
        Sleep(100*Wait);
    }
    ui->FilePath_lineEdit->setEnabled(true);
    ui->Browse_pushButton->setEnabled(true);
    ui->Load_pushButton->setEnabled(true);
    ui->str_lineEdit->setEnabled(true);
    ui->Step_pushButton->setEnabled(true);
    ui->Auto_pushButton->setEnabled(true);
    ui->checkBox->setCheckState(Qt::Unchecked);
    ui->checkBox->setEnabled(false);
}

void MainWindow::on_Browse_pushButton_clicked()
{
    QFileDialog *QFD=new QFileDialog();
    ui->FilePath_lineEdit->setText(QFD->getOpenFileName());
    QFD->close();
    delete QFD;
}

void MainWindow::on_FilePath_lineEdit_textChanged(const QString &arg1)
{
    if(!(arg1.endsWith(".tm")&&arg1.length()>=4))
    {
        SetStatus("Invalid File Name! Make sure the file ends with \".tm\"!");
        ui->Load_pushButton->setEnabled(false);
    }
    else
    {
        SetStatus("Valid File Name. Press \"Load\" to load this Turing Machine...");
        ui->Load_pushButton->setEnabled(true);
    }
    ui->str_lineEdit->setText("");
    ui->str_lineEdit->setEnabled(false);
    ui->Step_pushButton->setEnabled(false);
    ui->Auto_pushButton->setEnabled(false);
    ui->verticalSlider->setEnabled(false);
    ui->String_label->setText("");
    ui->Pointer_label->setText("");
    ui->K_lineEdit->setText("");
    ui->Sigma_lineEdit->setText("");
    ui->Gamma_lineEdit->setText("");
    ui->q0_lineEdit->setText("");
    ui->B_lineEdit->setText("");
    ui->F_lineEdit->setText("");
    ui->Delta_plainTextEdit->setPlainText("");
    if(TM)
    {
        delete(TM);
        TM=NULL;
    }
}

void MainWindow::on_str_lineEdit_textChanged(const QString &arg1)
{
    TM->Reset(arg1);
    Update(TM);
}

void MainWindow::Sleep(const int &msec)
{
    QTime dieTime=QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}
