#include "../include/mainwindow.h"
#include "../include/ui_mainwindow.h"
#include <QIntValidator>
#include "../include/qcustomplot.h"
#include "../include/phasor.h"
#include <QVector>
#include <iostream>
#include <QDebug>
#include <string>

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
	ui->vector->clearPlottables();
	ui->vector->xAxis->setVisible(false);
	ui->vector->yAxis->setVisible(false);
	ui->vector->legend->setVisible(false);
	ui->vector->replot();
    }
    else{
	MainWindow::plotVector();
    }
    MainWindow::plotPower(phasors.t, phasors.power, phasors.active_power, phasors.reactive_power);
}

void MainWindow::plotSine(QVector<double> t, QVector<double> v, QVector<double> i){
	ui->sine->clearPlottables();
	ui->sine->clearItems();
    // create graph and assign data to it: 
    ui->sine->addGraph();
    ui->sine->graph(0)->setData(t, v);
    // give the axes some labels:
    ui->sine->xAxis->setLabel("Ângulo [rad]");
    ui->sine->yAxis->setLabel("Tensão [V]");
    // set axes ranges, so we see all data:
    ui->sine->xAxis->setRange(0, 2*pi);
    ui->sine->yAxis->setRange(-1.2*phasors.vamp, 1.2*phasors.vamp);
    QPen pen_v;
    pen_v.setWidth(2);
    pen_v.setColor(QColor(0,0,255));
    ui->sine->graph(0)->setPen(QPen(pen_v));

	// Sets x axis ticks as a function of pi
	QSharedPointer<QCPAxisTickerPi> piTicker(new QCPAxisTickerPi);
	ui->sine->xAxis->setTicker(piTicker);
	piTicker->setTickCount(7);

    ui->sine->addGraph(ui->sine->xAxis, ui->sine->yAxis2);
    ui->sine->graph(1)->setData(t, i);
    QPen pen_i;
    pen_i.setWidth(2);
    pen_i.setColor(QColor(255,0,0));
    ui->sine->graph(1)->setPen(QPen(pen_i));
    ui->sine->yAxis2->setVisible(true);
	ui->sine->yAxis2->setRange(-2*phasors.iamp, 2*phasors.iamp);
    ui->sine->yAxis2->setLabel("Corrente [A]");    
	ui->sine->graph(0)->setName("Tensão");
	ui->sine->graph(1)->setName("Corrente");
	ui->sine->legend->setVisible(true);
	ui->sine->replot();
}



void MainWindow::plotLiss(QVector<double> t, QVector<double> v, QVector<double> i){
	ui->liss->clearPlottables();
	ui->liss->clearItems();
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
	ui->liss->plottable(0)->setName("Curva de Lissajous");
	ui->liss->legend->setVisible(true);
	ui->liss->replot();
}

void MainWindow::plotVector(){
	ui->vector->clearPlottables();
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
	// The following code is a hack and should be changed
	ui->vector->addGraph();
    ui->vector->graph(0)->setPen(QPen(pen_v));
    ui->vector->graph(0)->setName("Tensão");
	ui->vector->addGraph();
    ui->vector->graph(1)->setPen(QPen(pen_i));
    ui->vector->graph(1)->setName("Corrente");
	ui->vector->legend->setVisible(true);
    ui->vector->replot();
}

void MainWindow::plotPower(QVector<double> t, QVector<double> p, QVector<double> active, QVector<double> reactive){
    // create graph and assign data to it: 
	ui->power->clearPlottables();
	ui->power->clearItems();
	ui->power->legend->clearItems();
    ui->power->addGraph();
    ui->power->graph(0)->setData(t, p);
	// Declares pens
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(255,0,255));
	QPen penActive;
	penActive.setWidth(2);
	penActive.setColor(QColor(0,134,70));
	QPen penReactive;
	penReactive.setWidth(2);
	penReactive.setColor(QColor(255,0,0));
    // give the axes some labels:
    ui->power->xAxis->setLabel("Tempo [s]");
    ui->power->yAxis->setLabel("Potência [W]");
    // set axes ranges, so we see all data:
    ui->power->xAxis->setRange(0, 2*pi);
    ui->power->yAxis->setRange(-1*phasors.vamp*phasors.iamp, 1*phasors.vamp*phasors.iamp);
	if (phasors.ifreq != phasors.vfreq){
		ui->power->graph(0)->setName("Potência Instantânea = Potência Reativa");
		ui->power->graph(0)->setPen(QPen(penReactive));
	}
	else if(phasors.iphase == phasors.vphase){
		ui->power->graph(0)->setName("Potência Instantânea = Potência Ativa");
		ui->power->graph(0)->setPen(QPen(penActive));
	}
	else if(iphase_deg == 90 or iphase_deg == -90){
		ui->power->graph(0)->setName("Potência Instantânea = Potência Reativa");
		ui->power->graph(0)->setPen(QPen(penReactive));
	}
	else{
		ui->power->graph(0)->setPen(QPen(pen));

		ui->power->addGraph();
		ui->power->graph(1)->setData(t, active);
		ui->power->graph(1)->setPen(QPen(penActive));
		ui->power->graph(0)->setName("Potência Instantânea");
		ui->power->graph(1)->setName("Potência Ativa");

		ui->power->addGraph();
		ui->power->graph(2)->setData(t, reactive);
		ui->power->graph(2)->setPen(QPen(penReactive));
		ui->power->graph(2)->setName("Potência Reativa");
	}

	ui->power->legend->setVisible(true);
    ui->power->replot();
}

void MainWindow::reconstructPhasor(){
    phasors.~Phasor();
    new(&phasors) Phasor(vamp, vphase_deg, vfreq, iamp, iphase_deg, ifreq);
}

// If needed, adds a number to the end of the file
// to avoid overwriting
QString MainWindow::renameFile(QString fileName){
	int n = 0;
	while (true){
		if (!QFile::exists(fileName)){
			break;
		}
		else{
			n++;
			fileName.replace(fileName.size()-4, 1, "-" + QString::number(n) + ".");
		}
	}
	return fileName;
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

void MainWindow::on_actionExportarComo_triggered(){
	QString fileName = QFileDialog::getSaveFileName(this, tr("Salvar Arquivo"),
                           "/home/jana/untitled.pdf",
                           tr("Arquivo PDF (*.pdf);;Arquivo de imagem (*.png *.bmp *.jpg)"));
	QString fileExtension;
	fileExtension.resize(3);
	fileExtension[2] = fileName[fileName.size()-1] ;
	fileExtension[1] = fileName[fileName.size()-2] ;
	fileExtension[0] = fileName[fileName.size()-3] ;

	QString fileNameSine = fileName;
	fileNameSine.replace(fileNameSine.size()-4, 1, "-sine.");
	QFile sineFile(fileNameSine);
	QString fileNamePhasor = fileName;
	fileNamePhasor.replace(fileNamePhasor.size()-4, 1, "-phasor.");
	QFile phasorFile(fileNamePhasor);
	QString fileNameLiss = fileName;
	fileNameLiss.replace(fileNameLiss.size()-4, 1, "-liss.");
	QFile lissFile(fileNameLiss);
	QString fileNamePower = fileName;
	fileNamePower.replace(fileNamePower.size()-4, 1, "-power.");
	QFile powerFile(fileNamePower);

	// Checks if files exists and renames them accordingly
	fileNameSine = MainWindow::renameFile(fileNameSine);
	fileNamePhasor = MainWindow::renameFile(fileNamePhasor);
	fileNameLiss = MainWindow::renameFile(fileNameLiss);
	fileNamePower = MainWindow::renameFile(fileNamePower);

	// Saves files
	if (fileExtension == "pdf"){
		ui->sine->savePdf(fileNameSine);
		ui->vector->savePdf(fileNamePhasor);
		ui->liss->savePdf(fileNameLiss);
		ui->power->savePdf(fileNamePower);
	}
	else if(fileExtension == "png"){
		ui->sine->savePng(fileNameSine);
		ui->vector->savePng(fileNamePhasor);
		ui->liss->savePng(fileNameLiss);
		ui->power->savePng(fileNamePower);
	}
	else if(fileExtension == "jpg"){
		ui->sine->saveJpg(fileNameSine);
		ui->vector->saveJpg(fileNamePhasor);
		ui->liss->saveJpg(fileNameLiss);
		ui->power->saveJpg(fileNamePower);
	}
	else if(fileExtension == "bmp"){
		ui->sine->saveBmp(fileNameSine);
		ui->vector->saveBmp(fileNamePhasor);
		ui->liss->saveBmp(fileNameLiss);
		ui->power->saveBmp(fileNamePower);
	}
}


void MainWindow::on_actionSobre_triggered(){
	QString aboutTxt = "ValoresInstantaneos"
		"\n"
		"Copyright (c) 2024 lusabar"
		"\n"
		"Aplicação simples que traça as"
		" senoides, o diagrama fasorial,"
		" a curva de Lissajous e as componentes"
		" da potência elétrica com base em dados"
		" inseridos pelo usuário.";
	QMessageBox::about(this, "Sobre", aboutTxt);
}
