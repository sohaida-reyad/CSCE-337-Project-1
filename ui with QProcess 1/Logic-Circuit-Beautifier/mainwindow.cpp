#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QProcess>

QString VerilogFileName;

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

   VerilogFileName = QFileDialog :: getOpenFileName(
                this,
                tr("Choose File"),                              // Dialog Name
                "//",                                           // path starts from root
                "All files (*.txt)"                              // shows only .v files (i.e. Verilog files)
                );

    ui->textBrowser->setText(VerilogFileName);                  // displays path of file in the text browser
}

void MainWindow::on_pushButton_clicked()
{
    QFileInfo filePath(VerilogFileName);
    QString fileName = filePath.fileName();

    // RUN
    /*
    //system ("perl netlist.pl");
    system ("cd /Users/mac/Library/Developer/Xcode/DerivedData/CSCE337Project1-groosmpjonvudfaudxeyovpzjfoy/Build/Products/Debug/CSCE337Project1");
    system ("./" + fileName);
    */

    QString program = "/Users/mac/Library/Developer/Xcode/DerivedData/CSCE337Project1-groosmpjonvudfaudxeyovpzjfoy/Build/Products/Debug/CSCE337Project1";
    //QStringList arguments = fileName;
    //QProcess myProcess; // = new QProcess(this);
    //myProcess.start(program + " " + fileName);
    // myProcess.start("./CSCE337Project1 "+ fileName);

    QProcess process;
    process.startDetached(program, QStringList() << fileName);

    //process.start("./CSCE337Project1 "+ fileName);
}
