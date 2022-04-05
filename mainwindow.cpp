#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model1=new QStandardItemModel();
    ui->ForwardTab->setModel(model1);

    QStringList st_h_headers;
    st_h_headers<<"序号"<<"原数"<<"结果";
    model1->setHorizontalHeaderLabels(st_h_headers);
    model1->setRowCount(100);
    for (int i=0;i<model1->rowCount();i++) {
        model1->setItem(i,0,new QStandardItem(QString("%1").arg(i+1)));
        model1->item(i,0)->setTextAlignment(Qt::AlignCenter);
    }
    ui->ForwardTab->verticalHeader()->hide();
    ui->ForwardTab->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_cal_clicked()//实现TableView 的取数和计算输出
{
    double a=0;
    for (int i = 0; i<100; ++i)
    {
        QModelIndex index=model1->index(i,1);
        a=index.data().toDouble();

        a=a*5;
        model1->setItem(i,2,new QStandardItem(QString("%1").arg(a)));
        index=model1->index(i,2);
        if(index.data().toDouble()==0)
        {
            model1->setItem(i,1,new QStandardItem(QString("0")));
        }
    }
    //以下修复布局
    ui->ForwardTab->setFixedWidth(this->width()/2);
    ui->ForwardTab->setColumnWidth(0,ui->ForwardTab->width()/6-7);
    ui->ForwardTab->setColumnWidth(1,ui->ForwardTab->width()/3-7);
    ui->ForwardTab->setColumnWidth(2,ui->ForwardTab->width()/2-8);
}

bool MainWindow::on_Tab2Text_clicked()//实现TableView的数据输出和预览
{
    //保存为文件
    QString curPath=QCoreApplication::applicationDirPath(); //获取应用程序的路径
    //调用打开文件对话框选择一个文件
    QString aFileName=QFileDialog::getSaveFileName(this,tr("选择一个文件"),curPath,
                                                   "文本文件(*.txt);;所有文件(*.*)");

    if (aFileName.isEmpty()) //未选择文件，退出
        return false;

    QFile aFile(aFileName);
    if (!(aFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)))
        return false; //以读写、覆盖原有内容方式打开文件

    QTextStream aStream(&aFile); //用文本流读取文件

    QStandardItem   *aItem;
    int i,j;
    QString str;

    ui->forText->clear();
    //获取表头文字
    for (i=0;i<model1->columnCount();i++)
    {
        aItem=model1->horizontalHeaderItem(i); //获取表头的项数据
        str=str+aItem->text()+"\t";  //以TAB见隔开
    }
    aStream<<str<<"\n";  //文件里需要加入换行符 \n
//    ui->forText->appendPlainText(str);//显示数据*****

    //获取数据区文字
    for (i=0;i<model1->rowCount();i++)
    {
        str="";
        for( j=0;j<model1->columnCount();j++)
        {
            aItem=model1->item(i,j);
            double index=model1->index(i,2).data().toDouble();
            if(index==0)
            {
                continue;
            }
            else
            {
                str=str+aItem->text()+QString::asprintf("\t");
                if(j==2)
                {
                    aStream<<str<<"\n";
                }
            }
        }
//        ui->forText->appendPlainText(str);//显示数据*****
    }
    aFile.close();

    QFile   aFile1(aFileName);
    if (!aFile1.exists()) //文件不存在
        return false;

    if (!aFile1.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    ui->forText->setPlainText(aFile1.readAll());
    aFile1.close();
    return  true;
}

bool MainWindow::on_showdata_clicked()
{//打开文件
    QString curPath=QDir::currentPath();//获取系统当前目录
//调用打开文件对话框打开一个文件
    QString aFileName=QFileDialog::getOpenFileName(this,"打开一个文件",curPath,
                 "程序文件(*.h *cpp);;文本文件(*.txt);;所有文件(*.*)");

    if (aFileName.isEmpty())
        return false; //如果未选择文件，退出
    QFile   aFile(aFileName);

    if (!aFile.exists()) //文件不存在
        return false;

    if (!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream aStream(&aFile); //用文本流读取文件
//    aStream.setAutoDetectUnicode(true); //自动检测Unicode,才能正常显示文档内的汉字

    ui->forText->setPlainText(aStream.readAll());

//    ui->textEditStream->clear();//清空
//    while (!aStream.atEnd())
//    {
//        str=aStream.readLine();//读取文件的一行
//        ui->textEditStream->appendPlainText(str); //添加到文本框显示
//    }

    aFile.close();//关闭文件

    return  true;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    if(nullptr!=this->ui)
    {
        ui->ForwardTab->setFixedWidth(this->width()/2);
        ui->ForwardTab->setColumnWidth(0,ui->ForwardTab->width()/6-7);
        ui->ForwardTab->setColumnWidth(1,ui->ForwardTab->width()/3-7);
        ui->ForwardTab->setColumnWidth(2,ui->ForwardTab->width()/2-8);
    }

}
