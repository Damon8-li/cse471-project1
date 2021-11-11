#pragma once
#include "AudioNode.h"

class CCAR :
	public CAudioNode
{
public:
	CCAR();
	virtual ~CCAR();

private:
	double m_attack;
	double m_release;
	double m_duration;
	double m_time;
	CAudioNode* m_source;

public:
	void SetSource(CAudioNode* const& source) { m_source = source; }
	void SetDuration(double duration) { m_duration = duration; }
	virtual void Start();
	virtual bool Generate();

};

