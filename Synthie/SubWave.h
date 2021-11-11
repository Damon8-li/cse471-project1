#pragma once
#include "AudioNode.h"
#include <string> 
#include <stdlib.h> 
using namespace std;

class CSubWave :
	public CAudioNode
{
public:
	CSubWave();
	~CSubWave();

	void Start();
	bool Generate();

	void ImplementRes(double* sample, int tableIndex);

	void SetWaveType(std::wstring type);
	void SetReson(bool reson);
	void SetResonFreq(double freq);
	void SetResonBandwidth(double band);
	void SetMoogDown(bool flag);
	void SetMoogUp(bool flag);
	void SetMoogDownUp(bool flag);
	void SetMoogUpDown(bool flag);
	void SetWavetables();

private:
	std::wstring mType;

	double m_time;
	bool mReson = false;
	double mFreq = 0.01134;
	double mBandwidth = 0.01;

	double mSweep = 0.0;
	bool mDown = false;
	bool mUp = false;
	bool mDownUp = false;
	bool mUpDown = false;

public:
	void SetFreq(double f);
	void SetAmp(double a);

private:
	std::vector<double> m_wavetable;
	double m_freq;
	double m_amp;
	int m_phase;
};

