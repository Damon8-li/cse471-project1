#pragma once
#include "AudioNode.h"
#include "Note.h"
#include "AudioFilter.h"

class CInstrument :
	public CAudioNode
{
public:
	CInstrument();
	~CInstrument();
	CInstrument(double);

	virtual void SetNote(CNote *note) = 0;
	double Send(int i);
	void SetSend(int i, double value);


protected:

	CAudioFilter m_filter;
	CEnvelope* m_envelope;

	double mSends[5] = { 1, 0, 0, 0, 0};
};

