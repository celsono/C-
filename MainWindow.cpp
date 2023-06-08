#include "MainWindow.h"


#define CN QString::fromLocal8Bit
MainWindow::MainWindow()
{
	this->setGeometry(600, 250, 800, 600);      // 设置窗口大小
    setWindowTitle(CN("绘图工具"));          // 设置窗口名称
    setWindowIcon(QIcon(":/drawing/icon/appleworks.ico"));
    createMenuBar();
    CreateBar();
}

void MainWindow::Exit() {
    QMainWindow::close();
}

void MainWindow::createMenuBar() {
    QMenu* file = menuBar()->addMenu(CN("文件"));      // menubar菜单栏
    QAction* save_file = new QAction(CN("保存为"), this);
    QAction* exit = new QAction(CN("退出"), this);
    exit->setStatusTip(CN("退出程序"));
    file->addAction(save_file);
    file->addAction(exit);
    connect(save_file, SIGNAL(triggered()), this, SLOT(SaveFile()));
    connect(exit, SIGNAL(triggered()), this, SLOT(Exit()));
}

void MainWindow::CreateBar() 
{
    QIcon icon1(":/drawing/icon/color.ico");        // 创建图标
    QIcon icon2(":/drawing/icon/delete.ico");
    QIcon icon3(":/drawing/icon/pencil.ico");
    QIcon icon4(":/drawing/icon/line.ico");
    QIcon icon5(":/drawing/icon/Ellipse.ico");
    QIcon icon6(":/drawing/icon/rect.ico");
    QIcon icon7(":/drawing/icon/cancel.ico");
    QIcon icon8(":/drawing/icon/undo.ico");

    mywidget = new DrawWidget;//实例化

    QToolBar* m_tool_bar = new QToolBar();//创建工具栏
    addToolBar(Qt::TopToolBarArea, m_tool_bar);

    QAction* toolbar1 = new QAction(icon1, CN("改变颜色"), this);//添加按钮
    QAction* toolbar2 = new QAction(icon2, CN("清空画布"), this);
    QAction* toolbar3 = new QAction(icon3, CN("画笔"), this);
    QAction* toolbar4 = new QAction(icon4, CN("绘制线段"), this);
    QAction* toolbar5 = new QAction(icon5, CN("绘制椭圆"), this);
    QAction* toolbar6 = new QAction(icon6, CN("绘制矩形"), this);
    QAction* toolbar7 = new QAction(icon7, CN("撤销"), this);
    QAction* toolbar8 = new QAction(icon8, CN("恢复"), this);

    select_width = new QLineEdit;
    select_width->setText(CN("5"));
    QPushButton* confirm = new QPushButton(CN("确定"));

    m_tool_bar->addAction(toolbar1);
    m_tool_bar->addAction(toolbar2);
    m_tool_bar->addAction(toolbar3);
    m_tool_bar->addAction(toolbar4);
    m_tool_bar->addAction(toolbar5);
    m_tool_bar->addAction(toolbar6);
    m_tool_bar->addAction(toolbar7);
    m_tool_bar->addAction(toolbar8);
    m_tool_bar->addWidget(select_width);
    m_tool_bar->addWidget(confirm);

    connect(toolbar1, &QAction::triggered, mywidget, &DrawWidget::slotChangePntColor);//连接按钮功能
    connect(toolbar2, &QAction::triggered, mywidget, &DrawWidget::slotClearPoint);
    connect(toolbar3, &QAction::triggered, mywidget, &DrawWidget::slotDrawCurve);
    connect(toolbar4, &QAction::triggered, mywidget, &DrawWidget::slotDrawLine);
    connect(toolbar5, &QAction::triggered, mywidget, &DrawWidget::slotDrawEllipse);
    connect(toolbar6, &QAction::triggered, mywidget, &DrawWidget::slotDrawRect);
    connect(toolbar7, &QAction::triggered, mywidget, &DrawWidget::slotCancel);
    connect(toolbar8, &QAction::triggered, mywidget, &DrawWidget::slotUndo);
    connect(confirm, SIGNAL(clicked()), this, SLOT(slotWidth()));

    this->setCentralWidget(mywidget);
}




void MainWindow::SaveFile()
{
    FileInfo f(this);
    f.show();
    f.exec();
}

void MainWindow::slotWidth() {

    QString str_width = select_width->text();
    bool ok;
    width = str_width.toInt(&ok);
    if (!ok)
        QMessageBox::critical(this, CN("错误!"), CN("请输入一个整数！"));
    mywidget->transmit(width);
}


MainWindow::~MainWindow()
{

}