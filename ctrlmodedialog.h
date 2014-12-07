#ifndef CTRLMODEDIALOG_H
#define CTRLMODEDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
    class ctrlModeDialog;
}

class MainWindow;

class ctrlModeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ctrlModeDialog(QWidget *parent = 0);
    ~ctrlModeDialog();

    void keyPressEvent(QKeyEvent *keyEvent);
    //void keyReleaseEvent(QKeyEvent *keyEvent);

private slots:
    void on_autoCtrlModeButton_clicked();
    void on_manualCtrlModeButton_clicked();
    void on_exitButton_clicked();

private:
    Ui::ctrlModeDialog *ui;
    class MainWindow *mainWindow;
};

#endif // CTRLMODEDIALOG_H
