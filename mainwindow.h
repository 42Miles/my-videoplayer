#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "effects.h"
#include <QWidget>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QtMultimedia>
#include <QVideoWidget>
#include <QSlider>
#include <Qt>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setActionFullScreen(QAction *newActionFullScreen);

private slots:

    void on_actionOpen_triggered();

    void on_actionPlayPause_triggered();

    void on_actionStop_triggered();

    void on_actionEffects_triggered();

    void play_video();

    void pause_video();

    void on_actionrewindAction_triggered();

    void on_actionfastForwardAction_triggered();

    void actionVolume_triggered();

    void actionFullScreen_triggered();

    void timer_alarm();

    void time_left();

    void keyPressEvent(QKeyEvent *event);

    void volumeSliderMoved();


private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QVideoWidget *vw;
    QSlider *slider;
    QSlider *volumeSlider;
    Effects effects;
    bool playing = false;
    bool fullscreen = false;
    QAction *actionVolume;
    QAction *actionFullScreen;
    QTimer *timer;
    QLabel *videoTime;
    QLabel *videoTimeLeft;
    qint32 previousVolume;

public slots:
    void change_effects();

};
#endif // MAINWINDOW_H
