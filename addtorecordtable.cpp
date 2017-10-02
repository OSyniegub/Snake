#include "addtorecordtable.h"
#include "ui_addtorecordtable.h"

AddToRecordTable::AddToRecordTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddToRecordTable)
{
    ui->setupUi(this);
}

AddToRecordTable::~AddToRecordTable()
{
    delete ui;
}

void AddToRecordTable::SetScores(int scores)
{
    ui->lblScores->setText(QString::number(scores));
}

void AddToRecordTable::on_buttonBox_accepted()
{
  UserName = ui->edtUserName->text();
}
