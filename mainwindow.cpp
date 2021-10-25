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

    slider = new QSlider(this);
    //bar = new QProgressBar(this);

    volumeSlider = new QSlider(this);
    volumeSlider->setOrientation(Qt::Horizontal);
    volumeSlider->setRange(0, 100);
    volumeSlider->setFixedWidth(100);
    volumeSlider->setValue(50);

    slider->setOrientation(Qt::Horizontal);

    ui->statusbar->addPermanentWidget(slider); //adding a slider to the statusbar
    ui->statusbar->addPermanentWidget(volumeSlider); //adding a volume to the statusbar
    //ui->statusbar->addPermanentWidget(bar);

    connect(volumeSlider, SIGNAL(valueChanged(int)), this, SIGNAL(volumeChanged(int)));
    connect(volumeSlider, SIGNAL(valueChanged(int)), player, SLOT(setVolume(int)));

    connect(player, &QMediaPlayer::durationChanged, slider, &QSlider::setMaximum); //Connecting player
    connect(player, &QMediaPlayer::positionChanged, slider, &QSlider::setValue);   //with
    connect(slider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);    //slider

    //connect(player, &QMediaPlayer::durationChanged, bar, &QProgressBar::setMaximum);
    //connect(player, &QMediaPlayer::positionChanged, bar, &QProgressBar::setValue);

    QString filename = QFileDialog::getOpenFileName(this, "Open a File", "", "Video File(*.avi, *.mpg, *.mp4)"); //adding a filter for the source files
    player->setMedia(QUrl::fromLocalFile(filename)); //setting media files
    on_actionPlay_triggered();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void startOpen()
{

}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open a File", "", "Video File(*.avi, *.mpg, *.mp4)"); //adding a filter for the source files
    on_actionStop_triggered();
    player->setMedia(QUrl::fromLocalFile(filename)); //setting media files
    on_actionPlay_triggered();
}


void MainWindow::on_actionPlay_triggered() //Play
{
    player->play();
    ui->statusbar->showMessage("Playing");
}


void MainWindow::on_actionPause_triggered() //Pause
{
    player->pause();
    ui->statusbar->showMessage("Paused...");
}


void MainWindow::on_actionStop_triggered() //Stop
{
    player->stop();
    ui->statusbar->showMessage("Stopped");
}


