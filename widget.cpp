#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#pragma execution_character_set("utf-8")

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //setBackImg();

    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setVideoOutput(ui->widget);

    connect(mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(mediaStateChanged(QMediaPlayer::State)));
    connect(mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));

    setPlayBtn();

    ui->toolButton_open->setToolTip("打开");
    ui->toolButton_open->setIcon(QPixmap(":/file.png"));

    ui->horizontalSlider->setToolTip("进度条");
    ui->label->setToolTip("剩余播放时长");

    duration_ = 0;
    position_ = 0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::play()
{
    switch (mediaPlayer->state()) {
    case QMediaPlayer::PlayingState:
        mediaPlayer->pause();
        break;
    default:
        mediaPlayer->play();
        break;
    }
}

void Widget::mediaStateChanged(QMediaPlayer::State state)
{
    switch (state) {
    case QMediaPlayer::PlayingState:
        setPauseBtn();
        break;
    default:
        setPlayBtn();
        break;
    }
}

void Widget::positionChanged(qint64 position)
{
    getTimeStr(position);
    position_ = position;
    ui->horizontalSlider->setValue(position_);
    ui->label->setText(getTimeStr(duration_ - position_));
}

void Widget::durationChanged(qint64 duration)
{
    qDebug() <<"positionChanged position====" << duration << endl;
    duration_ = duration;
    ui->horizontalSlider->setRange(0, duration_);
    ui->label->setText(getTimeStr(duration_));
}

void Widget::on_toolButton_clicked()
{
    play();
}

void Widget::on_horizontalSlider_sliderMoved(int position)
{
    mediaPlayer->setPosition(position);
}

void Widget::on_toolButton_open_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "play file", "d:/", "video(*.mp4 *.mkv *.avi)");
    if (filename.length()>0) {
         mediaPlayer->setMedia(QUrl::fromLocalFile(filename));
         //play
         on_toolButton_clicked();
    }
}

void Widget::mouseDoubleClickEvent ( QMouseEvent * )
{
    if (false == isFullScreen()) {
        setWindowFlags(Qt::Window);
        showFullScreen();
    } else {
        setWindowFlags (Qt::SubWindow);
        showNormal();
    }
}

QString Widget::getTimeStr(qint64 ms)
{
    int sec = ms/1000;
    int min = 0;
    int hour = 0;

    if (sec >= 60)
    {
        min = sec / 60;
        sec = sec % 60;
        if (min >= 60)
        {
            hour = min /60;
            min = min % 60;
        }
    }

    return tr("%1:%2:%3").arg(hour).arg(min).arg(sec);
}

void Widget::setPlayBtn()
{
    ui->toolButton->setToolTip("播放");
    ui->toolButton->setIcon(QPixmap(":/play.png"));
}

void Widget::setPauseBtn()
{
    ui->toolButton->setToolTip("暂停");
    ui->toolButton->setIcon(QPixmap(":/pause.png"));
}

void Widget::setBackImg()
{
    QPixmap pixmap(":/timg.png");
    QPalette palette;
    palette.setBrush(backgroundRole(), QBrush(pixmap));
    setPalette(palette);
}
