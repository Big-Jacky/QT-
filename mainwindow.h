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

    void on_btnXls_clicked();

    bool on_action_input_triggered();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model1;

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
};
#endif // MAINWINDOW_H
