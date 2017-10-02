#ifndef SNAKEFIELD_H
#define SNAKEFIELD_H

#include <QFrame>

namespace Ui {
class SnakeField;
}

class SnakeField : public QFrame
{
    Q_OBJECT

public:
    explicit SnakeField(QWidget *parent = 0);
    ~SnakeField();

private:
    Ui::SnakeField *ui;
};

#endif // SNAKEFIELD_H
