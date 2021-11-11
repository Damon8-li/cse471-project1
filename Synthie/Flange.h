#pragma once
#include "AudioEffect.h"
class CFlange :
	public CAudioEffect
{
public:
	CFlange();
	virtual ~CFlange();

	virtual void Process(double *input, double *output) override;

	virtual void Start() override;

	virtual bool Generate() override;

private:
	std::vector<double> mOutL;
	std::vector<double> mOutR;
};

