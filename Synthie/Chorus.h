#pragma once
#include "AudioEffect.h"
class CChorus :
	public CAudioEffect
{
public:
	CChorus();
	virtual ~CChorus();

	virtual void Process(double *input, double *output) override;

	virtual void Start() override;

	virtual bool Generate() override;
};

