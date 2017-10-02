#ifndef ADDTORECORDTABLE_H
#define ADDTORECORDTABLE_H

#include <QDialog>

namespace Ui {
class AddToRecordTable;
}

class AddToRecordTable : public QDialog
{
    Q_OBJECT

public:
    explicit AddToRecordTable(QWidget *parent = 0);
    ~AddToRecordTable();
    void SetScores(int scores);
    QString UserName;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddToRecordTable *ui;
};

#endif // ADDTORECORDTABLE_H
