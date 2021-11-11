#include "stdafx.h"
#include "Envelope.h"


CEnvelope::CEnvelope()
{
	m_le = 1;
}


CEnvelope::~CEnvelope()
{
}

double CEnvelope::GetLevel()
{ 
	return m_le; 
}


void CEnvelope::SetDuration(double duration)
{ 
	m_dur = duration;
}