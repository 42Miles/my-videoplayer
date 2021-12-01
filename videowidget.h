#include <QApplication>
#include <QMouseEvent>
#include <QVideoWidget>
#include <QSlider>
#include <QMediaPlayer>
#include <QFileDialog>

/**
 * @brief The VideoWidget class
 *
 * VideoWidget contains QSlider & QVideoWidget
 */
class VideoWidget : public QWidget
{
    Q_OBJECT
    QVideoWidget* videoWidget;
    QSlider* slider;
public:
    VideoWidget() :
        videoWidget(new QVideoWidget(this)),
        slider(new QSlider(Qt::Horizontal, this))
    {
        slider->hide();
        slider->move(10, 10); // Put slider where you want.
        slider->setRange(0, 100);

        const QMediaContent meida(QFileDialog::getOpenFileUrl());
        QMediaPlayer* player = new QMediaPlayer(this);
        player->setVideoOutput(videoWidget);
        player->setMedia(meida);
        player->play();

        slider->setValue(player->volume());
        connect(slider, &QSlider::valueChanged, player, &QMediaPlayer::setVolume);
    }
    virtual ~VideoWidget() {}
protected:
    /**
     * @brief changeEvent
     * @param event
     *
     * Listen to window state change event,
     * and show the slider only when the state is WindowFullScreen.
     */
    void changeEvent(QEvent* event) {
        if(event->type() == QEvent::WindowStateChange)
            slider->setVisible(windowState() == Qt::WindowFullScreen);
        QWidget::changeEvent(event);
    }

    /**
     * @brief resizeEvent
     * @param event
     *
     * Make videoWidget fill the parent widget.
     */
    void resizeEvent(QResizeEvent* event) {
        videoWidget->resize(size());
        event->accept();
    }

    void mouseDoubleClickEvent(QMouseEvent *event) {
        if(!isFullScreen())
            showFullScreen();
        else
            showNormal();
        event->accept();
    }
};
