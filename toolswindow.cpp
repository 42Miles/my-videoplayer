#include "toolswindow.h"
#include "ui_toolswindow.h"

ToolsWindow::ToolsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ToolsWindow)
{
    ui->setupUi(this);
}

ToolsWindow::~ToolsWindow()
{
    delete ui;
}
