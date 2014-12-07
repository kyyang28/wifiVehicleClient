#include "ctrlmodedialog.h"
#include "ui_ctrlmodedialog.h"
#include <QMessageBox>

ctrlModeDialog::ctrlModeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ctrlModeDialog)
{
    ui->setupUi(this);
    mainWindow = new MainWindow;
    setObjectName("CtrlMode");
    setStyleSheet("#CtrlMode{border-image:url(:/wifiVehicleImages/image/ctrlModeBackground.png);}");
    ui->autoCtrlModeButton->setObjectName("autoCtrlModeButton");
    ui->autoCtrlModeButton->setStyleSheet("#autoCtrlModeButton{border-image:url(:/wifiVehicleImages/image/autoCtrlMode.png);}");
    ui->manualCtrlModeButton->setObjectName("manualCtrlModeButton");
    ui->manualCtrlModeButton->setStyleSheet("#manualCtrlModeButton{border-image:url(:/wifiVehicleImages/image/manualCtrlMode.png);}");
    ui->exitButton->setObjectName("exitButton");
    ui->exitButton->setStyleSheet("#exitButton{border-image:url(:/wifiVehicleImages/image/exit.png);}");
}

ctrlModeDialog::~ctrlModeDialog()
{
    delete ui;
}

void ctrlModeDialog::keyPressEvent(QKeyEvent *keyEvent)
{
    if ( (keyEvent->key() == Qt::Key_A) && (keyEvent->isAutoRepeat() == false) ) {
        QMessageBox::warning(this, tr("Auto Control Mode Selection Warning"),
                             tr("The auto control mode is TBA"),
                             QMessageBox::Ok);
        keyEvent->ignore();
    }

    if ( (keyEvent->key() == Qt::Key_M) && (keyEvent->isAutoRepeat() == false) ) {
        mainWindow->show();
        this->hide();
        keyEvent->ignore();
    }
}

void ctrlModeDialog::on_autoCtrlModeButton_clicked()
{
    QMessageBox::warning(this, tr("Auto Control Mode Selection Warning"),
                         tr("The auto control mode is TBA"),
                         QMessageBox::Ok);
}

void ctrlModeDialog::on_manualCtrlModeButton_clicked()
{
    mainWindow->show();
    this->hide();
}

void ctrlModeDialog::on_exitButton_clicked()
{
    close();
}
