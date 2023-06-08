#pragma once
#include <QtWidgets/QMainWindow>
#include<qmdiarea.h>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include<QHBoxLayout>
#include<qaction.h>
#include<qtoolbar.h>
#include<qstatusbar.h>
#include<qcolordialog.h>
#include <QGuiApplication>
#include<qmenubar.h>
#include<qcoreapplication.h>
#include "DrawWidget.h"
#include <QScreen>
#include <QPixmap>
#include <QtWidgets/QApplication>
#include "fileinfo.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QLineEdit* select_width;
    DrawWidget* mywidget;
    int width;

public:
    MainWindow();
    ~MainWindow();

    QMdiArea* m_mdiarea;
    void CreateBar();
    void createMenuBar();


public slots:
    void SaveFile();
    void Exit();
    void slotWidth();
};