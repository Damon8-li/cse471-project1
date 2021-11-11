#pragma once
#include "AudioNode.h"

class CEnvelope :
	public CAudioNode
{
public:
	CEnvelope();
	virtual ~CEnvelope();

	virtual void Start() override {};

	virtual bool Generate() override { return false; }


	double GetLevel();


	void SetDuration(double duration);

protected:

	double m_dur;

	double m_time;

	double m_le;
};

