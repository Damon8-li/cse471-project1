#include "stdafx.h"
#include "SubWave.h"
#include <cmath>

CSubWave::CSubWave()
{
	m_phase = 0;
	m_amp = 0.1;
	m_freq = 440;
}


CSubWave::~CSubWave()
{
}

void CSubWave::Start()
{
	m_phase = 0;
	m_time = 0;
	SetWavetables();
}

bool CSubWave::Generate()
{
	m_frame[0] = m_wavetable[m_phase];
	m_frame[1] = m_frame[0];
	m_phase = (m_phase + 1) % m_wavetable.size();

	return true;
}

void CSubWave::SetWavetables()
{
	auto tableSize = GetSampleRate();
	m_wavetable.resize(tableSize);
	double ampFilter = 1.0;

	if (m_freq > 1400. / 44100) {
		ampFilter = 0.4;
	}
	if (m_freq > 1200. / 44100){
		ampFilter = 0.65;
	}
	if (m_freq > 1000. / 44100) {
		ampFilter = 0.75;
	}

	double setFreq = m_freq;
	for (auto i = 0; i < tableSize; i++, m_time += 1. / GetSampleRate()){
		double sam = 0.0;
		
		if (mDown){
			setFreq -= 440.0 / tableSize;
		}
		else if (mUp){
			setFreq += 440.0 / tableSize;
		}
		else if (mDownUp){
			if (i < tableSize / 2){
				setFreq -= 440.0 / tableSize;
			}
			else{
				setFreq += 440.0 / tableSize;
			}
		}
		else if (mUpDown){
			if (i < tableSize / 2){
				setFreq += 440.0 / tableSize;
			}
			else{
				setFreq -= 440.0 / tableSize;
			}
		}

		if (mType == L"Sawtooth"){
			
			sam = ampFilter * m_amp * sin(m_time * 2 * PI * setFreq);

			for (double h = 2.0; h <= (GetSampleRate() / 2.0) / m_freq; h++){
				sam += (ampFilter * m_amp / h) * sin(m_time * 2 * PI  * setFreq * h);
			}
		}

		else if (mType == L"Triangle") {
			int alternatingSign = -1;
			sam = ampFilter * m_amp * sin(m_time * 2 * PI * setFreq);

			for (double h = 3.0; h <= (GetSampleRate() / 2.0) / m_freq; h++) {
				if ((int)h % 2 == 1) {
					sam += (alternatingSign * ampFilter * m_amp / (h * h)) * sin(m_time * 2 * PI * setFreq * h);
					alternatingSign = -alternatingSign;
				}
			}
		}

		else if (mType == L"Square"){
			sam = ampFilter * m_amp * sin(m_time * 2 * PI * setFreq);

			for (double h = 3.0; h <= (GetSampleRate() / 2.0) / m_freq; h++){
				if ((int)h % 2 == 1)
					sam += (ampFilter * m_amp / h) * sin(m_time * 2 * PI  * setFreq * h);
			}
		}


		if (mReson && i > 1){
			ImplementRes(&sam, i);
		}

		m_wavetable[i] = sam;
	}
}

void CSubWave::ImplementRes(double* sample, int tableIndex){

	double R = 1.0 - (mBandwidth / 2.0);
	double cosTheta = (2 * R * cos(2 * PI * mFreq)) / (1 + pow(R, 2));
	double A = (1 - pow(R, 2)) * sqrt(1 - pow(cosTheta, 2));

	int First_PreIndex; 
	int sec_PrevIndex;

	if (tableIndex - 1 < 0)
	{
		First_PreIndex = m_wavetable.size() - 1;
	}
	else
	{
		First_PreIndex = tableIndex - 1;
	}
	if (tableIndex - 2 < 0)
	{
		sec_PrevIndex = m_wavetable.size() - 1;
	}
	else
	{
		sec_PrevIndex = tableIndex - 2;
	}
		
	*sample = A * *sample + (2 * R*cosTheta) * m_wavetable[First_PreIndex] - pow(R, 2) * m_wavetable[sec_PrevIndex];


}

void CSubWave::SetWaveType(std::wstring type)
{
	mType = type; 
}
void CSubWave::SetReson(bool reson)
{ 
	mReson = reson; 
}
void CSubWave::SetResonFreq(double freq)
{ 
	mFreq = freq; 
}
void CSubWave::SetResonBandwidth(double band)
{
	mBandwidth = band;
}
void CSubWave::SetMoogDown(bool flag)
{ 
	mDown = flag;
}
void CSubWave::SetMoogUp(bool flag)
{ 
	mUp = flag; 
}
void CSubWave::SetMoogDownUp(bool flag)
{ 
	mDownUp = flag;
}
void CSubWave::SetMoogUpDown(bool flag)
{ 
	mUpDown = flag;
}

void CSubWave::SetFreq(double f)
{
	m_freq = f;
}

void CSubWave::SetAmp(double a)
{
	m_amp = a;
}