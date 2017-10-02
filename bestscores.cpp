#include "bestscores.h"
#include "ui_bestscores.h"

#include <QFile>

BestScores::BestScores(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BestScores)
{
    ui->setupUi(this);
    loadFromFile();
}

BestScores::~BestScores()
{
    delete ui;
}

void BestScores::loadFromFile()
{
  QFile f;
  //Рекорды хранятся в csv файле, в неотсортированном виде
  //сортировка будет делаться табличкой
  f.setFileName(QCoreApplication::applicationDirPath().append("/scores.txt"));

  if (f.exists())
  {
     f.open(QIODevice::ReadOnly);
     QStringList rows;
     QStringList cols;
     QString data;
     data.clear();
     rows.clear();
     cols.clear();
     //Считываем весь файл в строку
     data = f.readAll();
     f.close();
     //разбиваем строку на массив строк по символам перевода строки
     rows = data.split("\n");
     ui->tblMain->setColumnWidth(0, 250);
     ui->tblMain->setRowCount(0);
     //Устанавливаем кол-во строк в таблице результатов
     ui->tblMain->setRowCount(rows.count()-1);
     //Заливаем данные в табличку с результатами
     for (int i=0; i<rows.count(); ++i)
     {
         //Бъем каждую строчку файла на составные части по символу ;
         cols = rows[i].split(";");
         if (cols.count() > 2)
         {
             QTableWidgetItem *user = new QTableWidgetItem;
             user->setData(Qt::DisplayRole, cols[0]);
             //Делает колонку только для чтения
             user->setFlags(user->flags() & (~Qt::ItemIsEditable));
             ui->tblMain->setItem(i,0,user);

             QTableWidgetItem *score = new QTableWidgetItem;
             //Преобразуем строку в число для корректной сортировки
             score->setData(Qt::DisplayRole, cols[1].toInt());
             //Делает колонку только для чтения
             score->setFlags(score->flags() & (~Qt::ItemIsEditable));

             ui->tblMain->setItem(i,1,score);

             QTableWidgetItem *date = new QTableWidgetItem;
             date->setData(Qt::DisplayRole, cols[2]);
             //Делает колонку только для чтения
             date->setFlags(date->flags() & (~Qt::ItemIsEditable));
             ui->tblMain->setItem(i,2,date);
         }

     }
  }

  //Сортируем по колонке с результатами
  ui->tblMain->sortByColumn(1, Qt::DescendingOrder);
}
