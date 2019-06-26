#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include <choosekeydialog.h>
#include <QMainWindow>
#include <typedefine.h>
#include <QMessageBox>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTextBrowser>
#include <QTextCodec>
#include "usbthread.h"
#include "verifypin.h"
#include <QSharedPointer>
#include <QListWidgetItem>
#include "SM4.h"
#include "utilfunction.h"
#include <QFileDialog>
#include <QFile>
#include <QMenu>
#include <dialogforcreatefile.h>
#include <certparse.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    int verifyPIN(HAPPLICATION phApp);

signals:
//    void treeViewItemInfo(char*);
    void deletefile( HAPPLICATION phApp,QString curItemName);

//    void apiTypeChooseMsg(typeDefApi*);

private slots:
    void usbMsgS(int);

    void on_FileTree_clicked(const QModelIndex &index);

    void deleteButton(HAPPLICATION phApp,QString curItemName);

    void on_deleteButton_clicked();

    void on_reflashButton_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_ContainerList_itemClicked(QListWidgetItem *item);

    void on_unlockPinButton_clicked();

    void on_ImportSymmKeyButton_clicked();

    void on_WriteESealDataButton_clicked();

    void on_exitUKey_clicked();

    void on_ReadESealDataButton_clicked();

    void on_EncryptButton_clicked();

    void on_DecryptButton_clicked();

    void on_MacButton_clicked();

    void on_base64Decode_clicked();

    void on_base64Encode_clicked();

    void ShowContextMenu(const QPoint& pos);
    void on_TEXT2SM4Button_clicked();

private:
    void changeDll();
    void treeView_model();
    void connectDev(char*);
    QString getFormatCertText(char*,ULONG);
    int Base64Encode(unsigned char* bin_data, int bin_size, char* base64_data, unsigned int* base64_size);
private:
    Ui::MainWindow *ui = nullptr;

    typeDefApi *Dapi = nullptr;

    QStandardItemModel *model = nullptr;

    VerifyPin *pinDailog = nullptr;

    ChooseKeyDialog *chooseKeyD = nullptr;

    usbThread *HaiTaiUsb;

    usbThread *LongMaiUsb;

    DEVHANDLE phDev = nullptr;
    HAPPLICATION phApp = nullptr;
    HCONTAINER mhContainer = nullptr;

    QString curItemName = nullptr;
    QString pinCode = nullptr;
    QString ContainerName = nullptr;

};

#endif // MAINWINDOW_H
