#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QDialog>

namespace Ui {
    class SetupDialog;
}

class SetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetupDialog(QWidget *parent = 0);
    ~SetupDialog();

    QString ipAddr;
    QString controlPort;
    QString videoPort;

private slots:
    void on_saveButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::SetupDialog *ui;
};

#endif // SETUPDIALOG_H
