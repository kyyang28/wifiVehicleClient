#include "grapdialog.h"
#include "ui_grapdialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>

grapDialog::grapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::grapDialog)
{
    ui->setupUi(this);
    pictureDir = ui->pictureSavedDir->text();
}

grapDialog::~grapDialog()
{
    delete ui;
}

void grapDialog::on_setDirButton_clicked()
{
    QString path;
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    options |= QFileDialog::DontUseNativeDialog;
    //path = QDir::currentPath();
    path = QFileDialog::getExistingDirectory(this, "Open directory", "D:/", options);
    if (!path.isEmpty())
        ui->pictureSavedDir->setText(path);
}

void grapDialog::on_saveDirButton_clicked()
{
    //pictureDir = ui->pictureSavedDir->text();

    if (ui->pictureSavedDir->text() == "") {
        QMessageBox box;
        box.setWindowTitle(tr("Warning"));
        box.setIcon(QMessageBox::Warning);
        box.setText(tr("Please select the directory for saved pictures"));
        box.addButton(tr("OK"), QMessageBox::AcceptRole);
        if (box.exec() == QMessageBox::Accepted)
            box.close();
    }else {
        //qDebug() << "pictureDir = " << pictureDir;
        pictureDir = ui->pictureSavedDir->text();
        QMessageBox::information(this, tr("Save dialog"),
                                            tr("the directory is saved successfully!"),
                                            QMessageBox::Ok, QMessageBox::Ok);
        close();
    }
}

void grapDialog::on_closeButton_clicked()
{
    close();
}
