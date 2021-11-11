#pragma once
#include "Instrument.h"
#include "SubWave.h"
class CSubtractiveInstrument :
	public CInstrument
{
public:
	CSubtractiveInstrument();
	~CSubtractiveInstrument();
	CSubtractiveInstrument(double bpm);

	virtual void Start() override;
	virtual bool Generate() override;
	virtual void SetNote(CNote *note) override;

	void SetFreq(double freq);
	void SetAmplitude(double amp);
	void SetWaveType(wstring type);
	void SetDuration(double d);

private:
	CSubWave mSubtractiveWave;
	wstring mWaveType;
	double m_duration;
	double m_time;
};

