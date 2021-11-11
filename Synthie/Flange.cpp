#include "stdafx.h"
#include "Flange.h"


CFlange::CFlange()
{
}


CFlange::~CFlange()
{
}

void CFlange::Process(double* input, double* output)
{
	double delayVariance = (RANGE * mDelay) * sin(2 * PI * RATE);
	double newDelay = mDelay + delayVariance;

	mWrloc = (mWrloc + 1) % MAXQUEUESIZE;
	m_queue1[mWrloc] = input[0];

	int delayLength = int((newDelay * m_sampleRate + 0.5)) * 2;
	int rdloc = (mWrloc + MAXQUEUESIZE - delayLength) % MAXQUEUESIZE;

	output[0] = input[0] / 3 + m_queue1[rdloc] / 3 + (mOutL[rdloc] * LEVEL) / 3;
	output[0] *= mWet;

	output[0] += input[0] * mDry;
	mOutL[mWrloc] = output[0];


	mWrloc = (mWrloc + 1) % MAXQUEUESIZE;
	m_queue2[mWrloc] = input[1];
	rdloc = (mWrloc + MAXQUEUESIZE - delayLength) % MAXQUEUESIZE;

	output[1] = input[1] / 3 + m_queue2[(rdloc + 1) % MAXQUEUESIZE] / 3 + (mOutR[(rdloc + 1) % MAXQUEUESIZE] * LEVEL) / 3;
	output[1] *= mWet;

	output[1] += input[1] * mDry;

	mOutR[mWrloc] = output[1];
}

void CFlange::Start()
{
	mWrloc = 0;
	mRdloc = 0;
	mOutL.resize(MAXQUEUESIZE);
	mOutR.resize(MAXQUEUESIZE);
}

bool CFlange::Generate()
{
	return true;
}