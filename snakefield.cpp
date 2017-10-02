#include "snakefield.h"
#include "ui_snakefield.h"

SnakeField::SnakeField(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SnakeField)
{
    ui->setupUi(this);
}

SnakeField::~SnakeField()
{
    delete ui;
}
