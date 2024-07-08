#ifndef PHASOR_H
#define PHASOR_H

#include <QVector>

class Phasor{
public:
	Phasor(double v_a, double v_phase_deg, double v_f, double i_a, double i_phase_deg, double i_f);
	QVector <double> t;
	QVector <double> voltage;
	QVector <double> current;
	QVector <double> power;
	bool frequencyChanged;
	double vamp, vphase, vfreq, iamp, iphase, ifreq;
	void updateVoltage();
	void updateCurrent();
private:
	int n_points;
	void calculateTimeVector();
	void calculateVoltageVector();
	void calculateCurrentVector();
	void calculatePowerVector();
};
#endif
