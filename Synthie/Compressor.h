#pragma once
#include "AudioEffect.h"
class CCompressor :
	public CAudioEffect
{
public:
	CCompressor();
	virtual ~CCompressor();

	virtual void Process(double *input, double *output) override;

	virtual void Start() override;

	virtual bool Generate() override;
};

