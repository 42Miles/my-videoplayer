#include "effects.h"
#include "ui_effects.h"

Effects::Effects(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Effects)
{
    ui->setupUi(this);
}

Effects::~Effects()
{
    delete ui;
}

void Effects::on_brightnessSlider_sliderMoved(int position)
{
    ui->brightness_value->display(position);
    brightness = position;
}

void Effects::on_contrastSlider_sliderMoved(int position)
{
    ui->contrast_value->display(position);
    contrast = position;
}


void Effects::on_hueSlider_sliderMoved(int position)
{
    ui->hue_value->display(position);
    hue = position;
}


void Effects::on_saturationSlider_sliderMoved(int position)
{
    ui->saturation_value->display(position);
    saturation = position;
}

void Effects::on_applyButton_clicked()
{
    emit effectSignal();
}

void Effects::on_okButton_clicked()
{
    emit effectSignal();
    this->close();
}
