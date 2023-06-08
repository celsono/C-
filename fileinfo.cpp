#include "fileinfo.h"


#define CN QString::fromLocal8Bit

FileInfo::FileInfo(QWidget* parent)
    : QDialog(parent)
{
    this->setWindowTitle(CN("�����ļ�"));
    fileLabel = new QLabel(CN("�����ļ���:"));
    fileLineEdit = new QLineEdit;
    QDateTime currentTime = QDateTime::currentDateTime();
    QString default_name = currentTime.toString("yyyy-MM-dd-HH_mm_ss");

    fileLineEdit->setText(tr("screenshot-") + default_name);
    fileBtn = new QPushButton(CN("ȷ��"));
    cancel = new QPushButton(CN("ȡ��"));

    select_suffix = new QComboBox(this);
    select_suffix->setGeometry(10, 10, 80, 30);
    select_suffix->setMaxCount(4);
    select_suffix->addItem(tr(".jpg"), 1);
    select_suffix->addItem(tr(".png"), 2);
    select_suffix->addItem(tr(".bmp"), 3);


    //top
    QGridLayout* topLayout = new QGridLayout;
    topLayout->addWidget(fileLabel, 0, 0);
    topLayout->addWidget(fileLineEdit, 0, 1);
    topLayout->addWidget(select_suffix, 0, 2);
    topLayout->addWidget(fileBtn, 1, 0);
    topLayout->addWidget(cancel,1 ,2);



    //main
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    mainLayout->addLayout(topLayout);

    connect(fileBtn, SIGNAL(clicked()), this, SLOT(slotFile()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(slotCancel()));

    connect(select_suffix, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSuffix(int)));
}

//��ȡ�ļ���
void FileInfo::slotFile() {
    QString fileName = fileLineEdit->text() + suffix;
    QScreen* screen = QGuiApplication::primaryScreen();
    QPixmap pixmap = screen->grabWindow(parentWidget()->winId());//videoWidget->winId()����Ҫ��ͼ�Ŀؼ���winID��������Ϊ0
    pixmap.save(fileName, suffix.mid(1).toUtf8());
    QMessageBox::information(this, CN("�����ͼ"), CN("��ͼ����ɹ�"));
    this->close();
}


void FileInfo::slotSuffix(int i) {
    suffix = select_suffix->currentText();
}

void FileInfo::slotCancel() {
    this->close();
}

FileInfo::~FileInfo()
{
}





