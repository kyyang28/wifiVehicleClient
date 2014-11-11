#ifndef GRAPDIALOG_H
#define GRAPDIALOG_H

#include <QDialog>

namespace Ui {
    class grapDialog;
}

class grapDialog : public QDialog
{
    Q_OBJECT

public:
    explicit grapDialog(QWidget *parent = 0);
    ~grapDialog();

    QString pictureDir;

private slots:
    void on_setDirButton_clicked();
    void on_saveDirButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::grapDialog *ui;
};

#endif // GRAPDIALOG_H
