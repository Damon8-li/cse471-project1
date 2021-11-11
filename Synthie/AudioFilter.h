#pragma once
#include "AudioNode.h"

class CEnvelope;

class CAudioFilter :
	public CAudioNode
{
public:
	CAudioFilter();
	virtual ~CAudioFilter();

	void SetEnve(CEnvelope* envelope);
	void SetSource(CAudioNode* source);
	void SetDur(double duration);

	virtual void Start() override;
	virtual bool Generate() override;

protected:
	CAudioNode* m_source;

	CEnvelope* m_enve;

	double m_duration;

	double m_time;
};

