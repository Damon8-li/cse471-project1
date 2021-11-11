#include "stdafx.h"
#include "ADSREnvelope.h"


CADSREnvelope::CADSREnvelope()
{
	m_att = 0.05;
	m_dec = 0.;
	m_sus = 1.;
	m_release = 0.05;
}


CADSREnvelope::~CADSREnvelope()
{
}


void CADSREnvelope::Start()
{
	m_le = 1.;
	m_time = 0.;
}


bool CADSREnvelope::Generate()
{
	if (m_time <= m_att)
	{
		m_le = m_time / m_att * m_sus;
	}

	else if (m_time <= m_att + m_dec && m_att < m_time)
	{
		m_le = (m_le - 1) * ((m_time - (m_dur - m_dec)) / m_dec) + 1;
	}

	else if ((m_dur - m_release) < m_time)
	{	

		m_le = (1 - (m_time - (m_dur - m_release)) / m_release) * m_sus;
	}

	else
	{
		m_le = m_sus;
	}

	m_time += GetSamplePeriod();

	return m_dur > m_time;
}

void CADSREnvelope::SetAtt(double attack)
{
	m_att = attack; 
}

void CADSREnvelope::SetDec(double decay)
{ 
	m_dec = decay; 
}

void CADSREnvelope::SetSus(double sustain)
{ 
	m_sus = sustain; 
}

void CADSREnvelope::SetRel(double release)
{ 
	m_release = release; 
}