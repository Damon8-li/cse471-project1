#include "stdafx.h"
#include "AudioFilter.h"
#include "Envelope.h"


CAudioFilter::CAudioFilter()
{
}


CAudioFilter::~CAudioFilter()
{
}

void CAudioFilter::SetEnve(CEnvelope* envelope)
{ 
	m_enve = envelope; 
}

void CAudioFilter::SetSource(CAudioNode* source)
{ 
	m_source = source; 
}

void CAudioFilter::SetDur(double duration)
{ 
	m_duration = duration; 
}

void CAudioFilter::Start()
{
	m_time = 0;

	m_enve->SetDuration(m_duration);
	m_enve->SetSampleRate(GetSampleRate());

	m_enve->Start();
}


bool CAudioFilter::Generate()
{

	auto amp_factor = m_enve->GetLevel();

	m_frame[0] = m_source->Frame(0) * amp_factor;
	m_frame[1] = m_source->Frame(1) * amp_factor;

	m_time += GetSamplePeriod();

	return m_duration > m_time;
}
