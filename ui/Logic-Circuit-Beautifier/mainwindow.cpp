#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <QDir>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    // BROWSE

    QString VerilogFileName = QFileDialog :: getOpenFileName(
                this,
                tr("Choose File"),                              // Dialog Name
                "//",                                           // path starts from root
                "All files (*.v)"                              // shows only .v files (i.e. Verilog files)
                );

    ui->textBrowser->setText(VerilogFileName);                  // displays path of file in the text browser
}

void MainWindow::on_pushButton_clicked()
{
    // RUN
}
