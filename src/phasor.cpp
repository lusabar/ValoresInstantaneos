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

Phasor::Phasor(double v_a, double v_phase_deg, double v_f, double i_a, double i_phase_deg, double i_f){

	vamp = v_a;
    vphase = v_phase_deg * pi / 180;
	vfreq = v_f;

	iamp = i_a;
    iphase = i_phase_deg * pi / 180;
	ifreq = i_f;

	n_points = ceil(std::max(vfreq, ifreq)*80);

    t = linspace(0,4*pi,n_points);
    voltage = create_sinusoid(vamp, vphase, vfreq, t);
    current = create_sinusoid(iamp, iphase, ifreq, t);
}
