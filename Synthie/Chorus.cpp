#include "stdafx.h"
#include "Chorus.h"


CChorus::CChorus()
{
}


CChorus::~CChorus()
{
}


void CChorus::Process(double* input, double* output)
{

	double delayVariance = (RANGE * mDelay) * sin(2 * PI * RATE);
	double newDelay = mDelay + delayVariance;

	mWrloc = (mWrloc + 1) % MAXQUEUESIZE;
	m_queue1[mWrloc] = input[0];
	mWrloc = (mWrloc + 1) % MAXQUEUESIZE;
	m_queue2[mWrloc] = input[1];

	int delayLen = int((newDelay * GetSampleRate() + 0.5)) * 2;
	int rdloc = (mWrloc + MAXQUEUESIZE - delayLen) % MAXQUEUESIZE;

	output[0] = input[0] / 2 + m_queue1[rdloc] / 2;
	output[0] *= mWet;
	output[0] += input[0] * mDry;

	mWrloc = (mWrloc + 1) % MAXQUEUESIZE;
	m_queue2[mWrloc] = input[1];
	rdloc = (mWrloc + MAXQUEUESIZE - delayLen) % MAXQUEUESIZE;
	output[1] = input[1] / 2 + m_queue2[rdloc] / 2;
	output[1] *= mWet;


	output[1] += input[1] * mDry;

}

void CChorus::Start()
{
	mWrloc = 0;
	mRdloc = 0;
	m_queue1.resize(MAXQUEUESIZE);
	m_queue2.resize(MAXQUEUESIZE);
}

bool CChorus::Generate()
{
	return true;
}