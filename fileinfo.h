#ifndef FILEINFO_H
#define FILEINFO_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>
#include <QDateTime>
#include <QComboBox>  
#include <QtWidgets/QApplication>
#include <QScreen>
#include <QPixmap>
#include <QImageWriter>
#include <qDebug>
#include <QMessageBox>

class FileInfo : public QDialog
{
    Q_OBJECT

public:
    FileInfo(QWidget* parent = nullptr);
    ~FileInfo();

public slots:
    void slotFile();
    void slotSuffix(int i);
    void slotCancel();

private:
    QLabel* fileLabel;
    QLineEdit* fileLineEdit;
    QPushButton* fileBtn;
    QPushButton* cancel;
    QComboBox* select_suffix;
    QString suffix = ".jpg";

};
#endif // FILEINFO_H


