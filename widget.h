#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMultimedia>
#include <QVideoWidget>
#include <QMediaPlayer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void play();
    void mediaStateChanged(QMediaPlayer::State state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);

    void on_toolButton_clicked();
    void on_horizontalSlider_sliderMoved(int position);
    void on_toolButton_open_clicked();

private:
    void setPlayBtn();
    void setPauseBtn();
    void setBackImg();
    void mouseDoubleClickEvent ( QMouseEvent * );
    QString getTimeStr(qint64 ms);

private:
    Ui::Widget *ui;

    QMediaPlayer *mediaPlayer;
    qint64 duration_;
    qint64 position_;
};

#endif // WIDGET_H
