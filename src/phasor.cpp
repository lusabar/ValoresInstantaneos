#include "../include/phasor.h"
#include <cmath>
#include <QVector>

const double pi {3.14159265358979323846};

QVector<double> linspace(double a, double b, int n){
	QVector<double> result(n,0);
	double inc = (b-a) / (n-1);
	for (int i = 0; i <= n-1; i++){
		result[i] = a + inc*i;
	}
	return result;
}

QVector<double> create_sinusoid(double amplitude, double phase, double frequency, QVector<double> time){
    QVector<double> result(std::size(time),0);
    for(int i = 0; i <= std::size(result)-1; i++){
        result[i] = amplitude*sin(frequency*time[i]+phase);
	}
	return result;
}

QVector<double> calculate_active_power(double iamp, double vamp, double phase, double freq, QVector<double> time){
    QVector<double> result(std::size(time),0);
	double amplitude = (iamp*vamp/2)*cos(phase);
    for(int i = 0; i <= std::size(result)-1; i++){
        result[i] = amplitude*(1-cos(2*freq*time[i]));
	}
	return result;
}

QVector<double> calculate_reactive_power(double iamp, double vamp, double phase, double freq, QVector<double> time){
    QVector<double> result(std::size(time),0);
	double amplitude = (iamp*vamp/2)*sin(phase);
    for(int i = 0; i <= std::size(result)-1; i++){
        result[i] = amplitude*sin(2*freq*time[i]);
	}
	return result;
}

QVector<double> elementwise_product(QVector<double> v, QVector<double> i){
    QVector<double> result(std::size(v),0);
    for (int x = 0; x <= std::size(v)-1; x++){
	result[x] = v[x] * i[x];
    }
    return result;
}

void Phasor::updateVoltage(){
	calculateVoltageVector();
	calculatePowerVector();
}

void Phasor::updateCurrent(){
	calculateCurrentVector();
	calculatePowerVector();
}

void Phasor::calculateTimeVector(){
	n_points = ceil(std::max(vfreq, ifreq)*40);
	t = linspace(0,2*pi,n_points);
}

void Phasor::calculateVoltageVector(){
	voltage = create_sinusoid(vamp, vphase, vfreq, t);
}

void Phasor::calculateCurrentVector(){
	current = create_sinusoid(iamp, iphase, ifreq, t);
}

void Phasor::calculatePowerVector(){
	power = elementwise_product(voltage, current);
	if ((ifreq == vfreq) and (vphase != iphase)){
		active_power = calculate_active_power(iamp, vamp, iphase, vfreq, t);
		reactive_power = calculate_reactive_power(iamp, vamp, iphase, vfreq, t);
	}
}

Phasor::Phasor(double v_a, double v_phase_deg, double v_f, double i_a, double i_phase_deg, double i_f){

	vamp = v_a;
    vphase = v_phase_deg * pi / 180;
	vfreq = v_f;

	iamp = i_a;
    iphase = i_phase_deg * pi / 180;
	ifreq = i_f;

	Phasor::calculateTimeVector();
	Phasor::calculateVoltageVector();
	Phasor::calculateCurrentVector();
	Phasor::calculatePowerVector();
	
	frequencyChanged = false;
}
