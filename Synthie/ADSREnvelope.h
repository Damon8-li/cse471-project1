#pragma once
#include "Envelope.h"

class CADSREnvelope :
	public CEnvelope
{
public:
	CADSREnvelope();
	virtual ~CADSREnvelope();

	virtual void Start() override;

	virtual bool Generate() override;


	void SetAtt(double attack);

	void SetDec(double decay);

	void SetSus(double sustain);

	void SetRel(double release);

private:
	double m_att;
	double m_dec;
	double m_sus;
	double m_release;
};

