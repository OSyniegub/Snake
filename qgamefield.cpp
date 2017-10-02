#include "qgamefield.h"

#include <QMessageBox>
#include <QKeyEvent>
#include <QtGui>


//Рисует игровую сетку
void QGameField::draw_fields(QPainter *p)
{
    p->fillRect(this->rect(), Qt::white);
    p->setPen(Qt::gray);
    for (int i=0; i<rows; ++i)
    {
        p->drawLine(0, i*cell_height, width(), i*cell_height);
    }
    for (int i=0; i<colums; ++i)
    {
        p->drawLine(i*cell_width, 0, i*cell_width, height());
    }
}

void QGameField::init_snake()
{
    snake.clear();
    //Змейка из 3х элементов в центре экрана
    int center_x = rows/2;
    int center_y = colums /2;
    snake.append(QPoint(center_x-1, center_y));
    snake.append(QPoint(center_x, center_y));
    snake.append(QPoint(center_x+1, center_y));
    update();
}

void QGameField::draw_snake(QPainter *p)
{
    //Рисуем массив квадратиков на поле
    for (int i=0; i<snake.count(); ++i)
    {
        QColor col;
        //Голову змени рисуем красным цветом, остальное синим
        if (i != snake.count()-1) {col=Qt::blue;}
        else {col = Qt::red;}
        QPoint cell = snake[i];
        QRect rct = QRect(cell.x()*cell_width,
                          cell.y()*cell_height,
                          cell_width,
                          cell_height);
        p->fillRect(rct, col);
        p->setPen(Qt::black);
        p->drawRect(rct);
    }

}

void QGameField::draw_apple(QPainter *p)
{
  p->fillRect(QRect(apple.x()*cell_width,
                    apple.y()*cell_height,
                    cell_width,
                    cell_height), Qt::green);
}

bool QGameField::is_in_snake(QPoint &p)
{
  for (QList<QPoint>::iterator i=snake.begin(); i!=snake.end(); ++i)
  {
    if (i->x() == p.x() && i->y()==p.y())
        return true;
  }
  return false;
}

void QGameField::refresh_apple()
{
    //Генерируем случайную точку до тех пор
    //пока она не будет вне нашей змейки
    do{
        apple.setX(qrand()%rows);
        apple.setY(qrand()%colums);
    }
    while (is_in_snake(apple));
}

void QGameField::set_scores(int val)
{
    if (scores != val)
    {
        scores = val;
        //При каждом увеличении очков на 3 скорость растет на 1
        if (scores > 3*10)
          set_speed_rate(10);
        else
          set_speed_rate(scores/3);
        emit OnChangeScores(val);
    }
}

void QGameField::set_speed_rate(int rate)
{
    speed_rate = rate;
    m_timer->setInterval(speed-20*speed_rate);
    emit onChangeSpeedRate(rate);
}

void QGameField::snake_reverse()
{
    for (int i=0; i<snake.count() /2; ++i)
    {
      snake.swap(i, snake.count()-i-1);
    }
}

void QGameField::move_snake()
{
  if(!is_running) {return;}
  QPoint next_point = snake.last();
  switch(m_dir){
   case dir_down:{
      next_point.setY(next_point.y()+1);
      break;
      }
   case dir_left:{
      next_point.setX(next_point.x()-1);
      break;
  }
   case dir_right:{
      next_point.setX(next_point.x()+1);
      break;
  }
  case dir_up:{
      next_point.setY(next_point.y()-1);
      break;
  }
  }
  //Делаем стены "прозрачные", т.е змейка, выйдя за
  //пределы игрового поля появляется с другой стороны
  if (next_point.x() < 0)
      next_point.setX(rows-1);
  if (next_point.x()>=rows)
      next_point.setX(0);
  if (next_point.y() < 0)
      next_point.setY(colums-1);
  if (next_point.y()>=colums )
      next_point.setY(0);

  //Если есть самопересечение, умираем
  if (is_in_snake(next_point))
  {
      StopGame();
  }
  else
  {

    //Добавляем элемент в голову
    snake.append(next_point);
    //Если попали в яблоко не удаляем хвост
    if (is_in_snake(apple))
    {
      refresh_apple();
      set_scores(scores+1);
    }
    else
    {
      //Удаляем хвост
      snake.removeFirst();
    }
  }
  update();
}

QGameField::QGameField(QWidget *parent):
     QFrame(parent)
{
    scores=0;
    speed_rate = 0;
    m_dir = dir_left;
    is_running = false;
    parent->installEventFilter(this);
    m_timer = new QTimer(this);
    QObject::connect(m_timer, SIGNAL(timeout()), SLOT(move_snake()));
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    init_snake();
    refresh_apple();
}

QGameField::~QGameField()
{   
}

void QGameField::StartGame()
{
  set_scores(0);  
  is_running = true;
  init_snake();
  m_dir = dir_right;
  m_timer->start(speed);
}

void QGameField::StopGame()
{
  is_running = false;
  m_timer->stop();
  emit OnGameOver();
}

bool QGameField::IsGameRunning()
{
    return is_running;
}

void QGameField::paintEvent(QPaintEvent *event)
{

    QPainter paint(this);

    draw_fields(&paint);
    draw_apple(&paint);
    draw_snake(&paint);

    QFrame::paintEvent(event);
}

void QGameField::resizeEvent(QResizeEvent *event)
{
    QFrame::resizeEvent(event);
    cell_width = width() / rows;
    cell_height = height() / colums;
}

bool QGameField::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyRelease && is_running)
    {
      QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
      direction new_dir = m_dir;
      //Меняем направление движение змеи в зависимости от нажатых клавиш
      switch(keyEvent->key()){
      case Qt::Key_Left:{
          new_dir = dir_left;
      } break;
      case Qt::Key_Right:{
          new_dir = dir_right;
      } break;
      case Qt::Key_Down:{
          new_dir = dir_down;
      } break;
      case Qt::Key_Up:{
          new_dir = dir_up;
      } break;
      default: return false;
      }
      //Делаем реверс змейки в случае противоположных направлений, чтоб было как в тетрисе
      if (abs(m_dir-new_dir)==2)
        snake_reverse();
      if (m_dir == new_dir)
        move_snake();
      m_dir = new_dir;
      return true;
    }
    else
       return QFrame::eventFilter(object, event);
}

