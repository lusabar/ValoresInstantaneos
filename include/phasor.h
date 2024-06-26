#ifndef PHASOR_H
#define PHASOR_H

#include <QVector>

class Phasor{
public:
	Phasor(double v_a, double v_phase_deg, double v_f, double i_a, double i_phase_deg, double i_f);
	QVector <double> t;
	QVector <double> voltage;
	QVector <double> current;
	double vamp, vphase, vfreq, iamp, iphase, ifreq;
private:
	int n_points;
};
#endif