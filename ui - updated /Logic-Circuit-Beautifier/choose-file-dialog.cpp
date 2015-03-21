/*
#include "choose-file-dialog.h"
#include "ui_choose-file-dialog.h"

CHOOSEFILEDIALOG::CHOOSEFILEDIALOG(QWidget *parent) :
    QDialog(parent),
    ui(new ChooseFileUi::CHOOSEFILEDIALOG)
{
    ui->setupUi(this);

    QString path = "//";

    DirModel =  new QFileSystemModel(this);
    DirModel->setRootPath(path);
    ui->treeView->setModel(DirModel);
}

CHOOSEFILEDIALOG::~CHOOSEFILEDIALOG()
{
    delete ui;
}
*/
