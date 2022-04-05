#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTableView>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    double outdata(double a);
private slots:
    void on_cal_clicked();

    bool on_Tab2Text_clicked();

    bool on_showdata_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model1;
};
#endif // MAINWINDOW_H
