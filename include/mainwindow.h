#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QVector>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void reconstructPhasor();

    void doPlots();

    void on_phase_slider_valueChanged(int value);

    void on_phase_txt_returnPressed();

    void on_vamp_txt_returnPressed();

    void plotSine(QVector<double> t, QVector<double> v, QVector<double> i);
    void plotLiss(QVector<double> t, QVector<double> v, QVector<double> i);
    void plotVector();

    void on_iamp_txt_returnPressed();

    void on_freqList_currentIndexChanged(int index);

    void on_vamp_txt_editingFinished();

    void on_iamp_txt_editingFinished();

    void on_phase_txt_editingFinished();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
