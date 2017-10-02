#ifndef BESTSCORES_H
#define BESTSCORES_H

#include <QDialog>

namespace Ui {
class BestScores;
}

class BestScores : public QDialog
{
    Q_OBJECT

public:
    explicit BestScores(QWidget *parent = 0);
    ~BestScores();

private:
    Ui::BestScores *ui;
    void loadFromFile();
};

#endif // BESTSCORES_H
