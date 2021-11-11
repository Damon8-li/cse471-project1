#pragma once
#include "Instrument.h"
#include <vector>
class CAudioEffect :
	public CInstrument
{
public:
	virtual ~CAudioEffect();

	virtual void Process(double *frameIn, double *frameOut) = 0;

	virtual void SetNote(CNote *note) override;

	void SetDelay(double delay);

	void SetWet(double wet);

	void SetDry(double dry);

	void SetThreshold(double threshold);

protected:
	CAudioEffect();

	double	mDelay;
	double	mWet;
	double	mDry;
	double  mThreshold;

	int mWrloc;
	int mRdloc;

	double mTime = 5.0;

	std::vector<double> m_queue1;
	std::vector<double> m_queue2;

	const double RANGE = .5;
	const int RATE = 2;
	const int LEVEL = 2;
	const int MAXQUEUESIZE = 200000;
	const double M_PI = 3.14159265359;
};

