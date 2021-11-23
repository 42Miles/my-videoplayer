#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    vw = new QVideoWidget(this);
    player->setVideoOutput(vw);
    this->setCentralWidget(vw);

    actionVolume = new QAction(this);
    actionVolume->setIcon(QIcon(":/icons/icons/volume.png"));
    connect(actionVolume, &QAction::triggered, [this]()
    {
        actionVolume_triggered();
    });

    player->setVolume(50);

    volumeSlider = new QSlider(this);
    volumeSlider->setOrientation(Qt::Horizontal);
    volumeSlider->setRange(0, 100);
    volumeSlider->setFixedWidth(100);
    volumeSlider->setValue(50);
    volumeSlider->setFocusPolicy(Qt::NoFocus);
    volumeSlider->setPageStep(5);

    connect(volumeSlider, &QSlider::sliderMoved, [this]()
    {
        volumeSliderMoved();
    });

    connect(&effects, &Effects::effectSignal, this, &MainWindow::change_effects);

    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);
    slider->setFocusPolicy(Qt::NoFocus); 

    videoTime = new QLabel(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::timer_alarm);
    timer->start(1000);

    videoTimeLeft = new QLabel(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::time_left);

    actionFullScreen = new QAction(this);
    actionFullScreen->setIcon(QIcon(":/icons/icons/full-screen-button.png"));
    connect(actionFullScreen, &QAction::triggered, [this]()
    {
        actionFullScreen_triggered();
    });

    ui->mainToolBar->addWidget(videoTime);
    ui->mainToolBar->addWidget(slider); //adding a slider to the statusbar
    ui->mainToolBar->addWidget(videoTimeLeft);
    ui->mainToolBar->addAction(actionVolume);
    ui->mainToolBar->addWidget(volumeSlider); //adding a volume to the statusbar
    ui->mainToolBar->addAction(actionFullScreen);

    connect(player, &QMediaPlayer::volumeChanged, volumeSlider, &QSlider::setValue);
    //connect(volumeSlider,&QSlider::valueChanged, player,&QMediaPlayer::setVolume);
    connect(volumeSlider, &QSlider::sliderMoved, player, &QMediaPlayer::setVolume);

    connect(player, &QMediaPlayer::durationChanged, slider, &QSlider::setMaximum); //Connecting player
    connect(player, &QMediaPlayer::positionChanged, slider, &QSlider::setValue);   //with
    connect(slider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);    //slider

    QString filename = QFileDialog::getOpenFileName(this, "Open a File", "", "Video File(*.avi, *.mpg, *.mp4)"); //adding a filter for the source files
    on_actionStop_triggered();
    player->setMedia(QUrl::fromLocalFile(filename)); //setting media files
    on_actionPlayPause_triggered();

    this->setWindowTitle(filename.leftJustified(filename.indexOf('/'), '.', true));

    if(filename.isNull()){
        exit(EXIT_FAILURE);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open a File", "", "Video File(*.avi, *.mpg, *.mp4)"); //adding a filter for the source files
    on_actionStop_triggered();
    player->setMedia(QUrl::fromLocalFile(filename)); //setting media files
    on_actionPlayPause_triggered();
}

void MainWindow::on_actionPlayPause_triggered() //Play
{
    playing = !playing;
    playing ? play_video() : pause_video();
}

void MainWindow::on_actionStop_triggered() //Stop
{
    playing = false;
    ui->actionPlayPause->setIcon(QIcon(":/icons/icons/noun_play_64196.png"));
    player->stop();
}

void MainWindow::on_actionEffects_triggered()
{
    playing = false;
    player->pause();
    ui->actionPlayPause->setIcon(QIcon(":/icons/icons/noun_play_64196.png"));
    effects.setModal(true);
    effects.exec();
}

void MainWindow::change_effects()
{
    vw->setBrightness(effects.brightness);
    vw->setContrast(effects.contrast);
    vw->setHue(effects.hue);
    vw->setSaturation(effects.saturation);
}

void MainWindow::play_video()
{
    player->play();
    ui->actionPlayPause->setIcon(QIcon(":/icons/icons/noun_pause_64198.png"));
}

void MainWindow::pause_video()
{
    player->pause();
    ui->actionPlayPause->setIcon(QIcon(":/icons/icons/noun_play_64196.png"));

}

void MainWindow::on_actionrewindAction_triggered()
{
    player->setPosition(player->position() - 10000);
}

void MainWindow::on_actionfastForwardAction_triggered()
{
    player->setPosition(player->position() + 10000);
}

void MainWindow::actionVolume_triggered()
{
    if(player->volume() > 0)
    {
        previousVolume = player->volume();
        player->setVolume(0);
        volumeSlider->setValue(0);
    }
    else if(player->volume() <= 0)
    {
        player->setVolume(previousVolume);
        volumeSlider->setValue(previousVolume);
    }
    volumeSliderMoved();
}

void MainWindow::actionFullScreen_triggered()
{
    vw->setFullScreen(true);
}

void MainWindow::timer_alarm()
{
    qint64 position = player->position();
    int seconds = (position/1000) % 60;
    int minutes = (position/60000) % 60;
    int hours = (position/3600000) % 24;

    QTime time(hours, minutes,seconds);
    videoTime->setText(time.toString());
}

void MainWindow::time_left()
{
    qint64 timeleft = player->duration() - player->position();
    int seconds = (timeleft/1000) % 60;
    int minutes = (timeleft/60000) % 60;
    int hours = (timeleft/3600000) % 24;

    QTime time(hours, minutes,seconds);
    videoTimeLeft->setText(time.toString());
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
        on_actionPlayPause_triggered();
    else if(event->key() == Qt::Key_Escape)
        vw->setFullScreen(false);

}

void MainWindow::volumeSliderMoved()
{
 if(volumeSlider->value() <= 0)
     actionVolume->setIcon(QIcon(":/icons/icons/volume_mute.png"));
 else if(volumeSlider->value() < 50)
     actionVolume->setIcon(QIcon(":/icons/icons/volume_low.png"));
 else if(volumeSlider->value() >= 50)
     actionVolume->setIcon(QIcon(":/icons/icons/volume.png"));
}
