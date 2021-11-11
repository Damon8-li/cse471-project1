#include "stdafx.h"
#include "Instrument.h"


CInstrument::CInstrument()
{

}


CInstrument::~CInstrument()
{
}

CInstrument::CInstrument(double bpm)
{
	m_bpm = bpm;
}
double CInstrument::Send(int i)
{ 
	return mSends[i]; 
}

void CInstrument::SetSend(int i, double value)
{ 
	mSends[i] = value; 
}