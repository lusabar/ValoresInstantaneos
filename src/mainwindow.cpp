#include "../include/mainwindow.h"
#include "../include/ui_mainwindow.h"
#include <QIntValidator>
#include "../include/qcustomplot.h"
#include "../include/phasor.h"
#include <QVector>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->phase_txt->setValidator( new QIntValidator(-90, 90, this) );
    ui->vamp_txt->setValidator( new QDoubleValidator(-1.7e+300, 1.7e+300, 4, this) );
    ui->iamp_txt->setValidator( new QDoubleValidator(-1.7e+300, 1.7e+300, 4, this) );

    ui->phase_txt->setText("0");
    ui->vamp_txt->setText("100");
    ui->iamp_txt->setText("100");

    QPixmap pix("../logo.png");
    int w = ui->logo->width ();
    int h = ui->logo->height ();
//  ui->logo->setPixmap (pix.scaled (w,h,Qt::KeepAspectRatio));

	MainWindow::doPlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

const double pi {3.14159265358979323846};
double vamp{100}, vphase_deg{0}, vfreq{1}, iamp{100}, iphase_deg{0}, ifreq{1};
Phasor phasors(vamp, vphase_deg, vfreq, iamp, iphase_deg, ifreq);

void MainWindow::doPlots(){
	if (phasors.frequencyChanged){
		MainWindow::reconstructPhasor();
		phasors.frequencyChanged = false;
	}
    MainWindow::plotSine(phasors.t, phasors.voltage, phasors.current);
    MainWindow::plotLiss(phasors.t, phasors.voltage, phasors.current);
    if (phasors.vfreq != phasors.ifreq){
	ui->vector->clearItems();
//	ui->vector->clearPlottables();
	ui->vector->xAxis->setVisible(false);
	ui->vector->yAxis->setVisible(false);
	ui->vector->replot();
    }
    else{
	MainWindow::plotVector();
    }
    MainWindow::plotPower(phasors.t, phasors.power);
}

void MainWindow::plotSine(QVector<double> t, QVector<double> v, QVector<double> i){
    // create graph and assign data to it: 
    ui->sine->addGraph();
    ui->sine->graph(0)->setData(t, v);
    // give the axes some labels:
    ui->sine->xAxis->setLabel("Tempo [s]");
    ui->sine->yAxis->setLabel("Tensão [V]");
    // set axes ranges, so we see all data:
    ui->sine->xAxis->setRange(0, 2*pi);
    ui->sine->yAxis->setRange(-1.2*phasors.vamp, 1.2*phasors.vamp);
    QPen pen_v;
    pen_v.setWidth(2);
    pen_v.setColor(QColor(0,0,255));
    ui->sine->graph(0)->setPen(QPen(pen_v));
    ui->sine->replot();

    ui->sine->addGraph(ui->sine->xAxis, ui->sine->yAxis2);
    ui->sine->graph(1)->setData(t, i);
    QPen pen_i;
    pen_i.setWidth(2);
    pen_i.setColor(QColor(255,0,0));
    ui->sine->graph(1)->setPen(QPen(pen_i));
    ui->sine->yAxis2->setVisible(true);
	ui->sine->yAxis2->setRange(-2*phasors.iamp, 2*phasors.iamp);
    ui->sine->yAxis2->setLabel("Corrente [A]");    
	ui->sine->replot();
}



void MainWindow::plotLiss(QVector<double> t, QVector<double> v, QVector<double> i){
	ui->liss->clearPlottables();
	QCPCurve *Lissajous = new QCPCurve(ui->liss->xAxis, ui->liss->yAxis);
	Lissajous->setData(t, v, i);
	QPen pen;
	pen.setWidth(2);
	pen.setColor(QColor(0,134,70));
	Lissajous->setPen(QPen(pen));
	ui->liss->xAxis->setLabel("Tensão [V]");
	ui->liss->yAxis->setLabel("Corrente [A]");
	ui->liss->yAxis->setRange(-1.2*phasors.iamp, 1.2*phasors.iamp);
	ui->liss->xAxis->setRange(-1.2*phasors.vamp, 1.2*phasors.vamp);
	ui->liss->replot();
}

void MainWindow::plotVector(){
    ui->vector->clearItems();
    QCPItemLine *vVector = new QCPItemLine(ui->vector);
    vVector->start->setCoords(0,0);
    vVector->end->setCoords(phasors.vamp*cos(phasors.vphase), phasors.vamp*sin(phasors.vphase));
    vVector->setHead(QCPLineEnding::esSpikeArrow);
    QPen pen_v;
    pen_v.setWidth(2);
    pen_v.setColor(QColor(0,0,255));
    vVector->setPen(QPen(pen_v));
    
    QCPItemLine *iVector = new QCPItemLine(ui->vector);
    iVector->start->setCoords(0,0);
    iVector->end->setCoords(phasors.iamp*cos(phasors.iphase), phasors.iamp*sin(phasors.iphase));
    iVector->setHead(QCPLineEnding::esSpikeArrow);
    QPen pen_i;
    pen_i.setWidth(2);
    pen_i.setColor(QColor(255,0,0));
    iVector->setPen(QPen(pen_i));

    double aux = 1*std::max(phasors.vamp, phasors.iamp);
    ui->vector->xAxis->setVisible(true);
    ui->vector->yAxis->setVisible(true);
    ui->vector->yAxis->setRange(-aux, aux);
    ui->vector->xAxis->setRange(0, aux*1.2);

    ui->vector->xAxis->setScaleRatio(ui->vector->yAxis,1.0);
    ui->vector->replot();
}

void MainWindow::plotPower(QVector<double> t, QVector<double> p){
    // create graph and assign data to it: 
	ui->power->clearPlottables();
	ui->power->clearItems();
	ui->power->legend->clearItems();
    ui->power->addGraph();
    ui->power->graph(0)->setData(t, p);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(255,0,255));
    ui->power->graph(0)->setPen(QPen(pen));
    // give the axes some labels:
    ui->power->xAxis->setLabel("Tempo [s]");
    ui->power->yAxis->setLabel("Potência [W]");
    // set axes ranges, so we see all data:
    ui->power->xAxis->setRange(0, 2*pi);
    ui->power->yAxis->setRange(-1*phasors.vamp*phasors.iamp, 1*phasors.vamp*phasors.iamp);
	if (phasors.ifreq != phasors.vfreq){
		ui->power->graph(0)->setName("Potência Instantânea = Potência Reativa");
	}
	else if(phasors.iphase == phasors.vphase){
		ui->power->graph(0)->setName("Potência Instantânea = Potência Ativa");
	}

	ui->power->legend->setVisible(true);
    ui->power->replot();
}

void MainWindow::reconstructPhasor(){
    phasors.~Phasor();
    new(&phasors) Phasor(vamp, vphase_deg, vfreq, iamp, iphase_deg, ifreq);
}

void MainWindow::on_phase_slider_valueChanged(int value)
{
    iphase_deg = value;
    ui -> phase_txt -> setText(QString::number(iphase_deg));
	phasors.iphase = iphase_deg*pi / 180;
	phasors.updateCurrent();
    doPlots();
}

void MainWindow::on_phase_txt_returnPressed()
{
    iphase_deg = ui -> phase_txt -> text().toInt();
    ui -> phase_slider -> setValue(iphase_deg);
	phasors.iphase = iphase_deg*pi / 180;
	phasors.updateCurrent();
    doPlots();
}


void MainWindow::on_vamp_txt_returnPressed()
{
    vamp = ui->vamp_txt->text().toDouble();
	phasors.vamp = vamp;
	phasors.updateVoltage();
    doPlots();
}

void MainWindow::on_iamp_txt_returnPressed()
{
    iamp = ui->iamp_txt->text().toDouble();
	phasors.iamp = iamp;
	phasors.updateCurrent();
    doPlots();
}

void MainWindow::on_freqList_currentIndexChanged(int index)
{
    switch(index){
	case(0):
	    vfreq = 1;
	    ifreq = 1;
	    break; 
	case(1):
	    vfreq = 1;
	    ifreq = 2;
	    break;
	case(2):
	    vfreq = 1;
	    ifreq = 3;
	    break;
	case (3):
	    vfreq = 2;
	    ifreq = 3;
	    break;
	case (4):
	    vfreq = 3;
	    ifreq = 4;
	    break;
	case (5):
	    vfreq = 4;
	    ifreq = 5;
	    break;
	case (6):
	    vfreq = 5;
	    ifreq = 6;
	    break;
    }

	phasors.frequencyChanged = true;

    MainWindow::doPlots();
}


void MainWindow::on_vamp_txt_editingFinished()
{
    vamp = ui->vamp_txt->text().toDouble();
	phasors.vamp = vamp;
	phasors.updateVoltage();
    doPlots();
}


void MainWindow::on_iamp_txt_editingFinished()
{
    iamp = ui->iamp_txt->text().toDouble();
	phasors.iamp = iamp;
	phasors.updateCurrent();
    doPlots();
}


void MainWindow::on_phase_txt_editingFinished()
{
    iphase_deg = ui -> phase_txt -> text().toInt();
    ui -> phase_slider -> setValue(iphase_deg);
	phasors.iphase = iphase_deg*pi / 180;
	phasors.updateCurrent();
    doPlots();
}
