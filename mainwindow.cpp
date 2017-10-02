#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addtorecordtable.h"
#include "bestscores.h"
#include <QMessageBox>
#include <QFile>
#include <QDate>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->frame, SIGNAL(OnGameOver()), SLOT(on_game_over()));
    connect(ui->frame, SIGNAL(OnChangeScores(int)), SLOT(refresh_scores(int)));
    connect(ui->frame, SIGNAL(onChangeSpeedRate(int)), SLOT(refresh_speed(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Клик по кнопке "Начать/завершить игру"
void MainWindow::on_pbMain_clicked()
{
    if (ui->frame->IsGameRunning())
    {
        ui->frame->StopGame();
        ui->pbMain->setText("Розпочати гру");
        ui->scores->setEnabled(true);
    }
    else
    {
        ui->frame->StartGame();
        ui->pbMain->setText("Завершити гру");
        ui->frame->setFocus();
        ui->scores->setEnabled(false);
    }

}

//Слот, обрабатывающий сигнал окончания игры
void MainWindow::on_game_over()
{
    ui->pbMain->setText("Розпочати гру");
    ui->scores->setEnabled(true);
    if (ui->scores->value() > 0)
    {
    AddToRecordTable dlg(this);    
    dlg.SetScores(ui->scores->value());
    if (dlg.exec()== QDialog::Accepted && dlg.UserName.length()>0 )
    {
      //Записываем в файл результат героя
      QFile f;
      f.setFileName(QCoreApplication::applicationDirPath().append("/scores.txt"));
      if (f.open(QIODevice::Append| QFile::Text))
      {
         QTextStream s(&f);
         s.setCodec("UTF-8");
         s << dlg.UserName << ";" << ui->scores->value() << ";" << QDate::currentDate().toString("dd.MM.yyyy") <<"\n";
         f.close();
      }
    }
    }
    else
        QMessageBox::warning(0,"Гру завершено", "Ви не набрали жодного очка :(");
}

//Слот обрабатывающий сигнал изменения очков
void MainWindow::refresh_scores(int val)
{
    ui->scores->display(val);
}

void MainWindow::refresh_speed(int val)
{
   ui->speed_rate->display(val);
}

void MainWindow::on_pushButton_clicked()
{
    BestScores *dlg = new BestScores(this);
    dlg->exec();
    delete dlg;
}
