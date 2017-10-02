#ifndef QGAMEFIELD_H
#define QGAMEFIELD_H

#include <QFrame>
#include <QPainter>
#include <QObject>

//Текущее направление движения змеи
enum direction{ dir_up = 1, dir_down = 3,
             dir_right = 2, dir_left = 4 };

//Класс для игрового поля
class QGameField : public QFrame
{
    Q_OBJECT

private:
    //Массив координат змейки
    QList<QPoint> snake;
    //Текущее направление движения
    direction m_dir;
    //Запущена ли игра
    bool is_running;
    //Ширина ячейки змейки
    int cell_width;
    //Высота ячейки змейки
    int cell_height;
    //Количество съеденных яблок
    int scores;
    //Уровень сложности: скорость игры, возрастает по мере набора очков
    int speed_rate;
    //Таймер для движения
    QTimer *m_timer;
    //Координаты яблока
    QPoint apple;
    //Нарисовать игровую сетку
    void draw_fields(QPainter *p);
    //Строит изначальную змейку
    void init_snake();
    //Рисует змейку на экране
    void draw_snake(QPainter *p);
    //Рисует яблоко
    void draw_apple(QPainter *p);
    //Проверяет лежит ли интересующая нас точка внутри змейки
    bool is_in_snake(QPoint &p);
    //Находит новые координаты яблоку
    void refresh_apple();
    //Сеттер для очков, посылает внутри сигнал OnChangeScores
    void set_scores(int val);
    void set_speed_rate(int rate);
    //Реверс змейки
    void snake_reverse();

private slots:
    //Передвигает змейку
    void move_snake();

public:
    //Размер поля
    const static int rows=50;
    const static int colums=50;
    //Скорость (интервал срабатывания таймера в миллисекундах)
    const static int speed = 250;
    explicit QGameField(QWidget *parent);
    ~QGameField();      
    void StartGame();
    void StopGame();
    bool IsGameRunning();
signals:
    //Окончание игры
    void OnGameOver();
    //Изменилось количество сожранных яблок
    void OnChangeScores(int scores);
    //Изменилась скорость
    void onChangeSpeedRate(int rate);

protected:
    //Перехватываем события нажатия на клаву и перерисовывания
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    //Здесь будут перехватываться нажатия на кнопки на клавиатуре
    virtual bool eventFilter(QObject *object, QEvent *event);
};

#endif // QGAMEFIELD_H
