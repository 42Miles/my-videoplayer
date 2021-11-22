#ifndef EFFECTS_H
#define EFFECTS_H

#include <QWidget>
#include <QFrame>
#include <QVideoWidgetControl>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QtMultimedia>
#include <QVideoWidget>
#include <QFileDialog>
#include <QProgressBar>
#include <QSlider>
#include <QDebug>
#include <QPixmap>
#include <Qt>

namespace Ui {
class Effects;
}

class Effects : public QDialog
{
    Q_OBJECT

public:
    explicit Effects(QDialog *parent = nullptr);
    qint32 brightness = 0;
    qint32 contrast = 0;
    qint32 hue = 0;
    qint32 saturation = 0;

    ~Effects();

private slots:

    void on_brightnessSlider_sliderMoved(int position);

    void on_applyButton_clicked();

    void on_okButton_clicked();

    void on_contrastSlider_sliderMoved(int position);

    void on_hueSlider_sliderMoved(int position);

    void on_saturationSlider_sliderMoved(int position);

private:
    Ui::Effects *ui;


signals:
    void effectSignal();


};

#endif // EFFECTS_H
