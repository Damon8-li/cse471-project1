#include "stdafx.h"
#include "SubtractiveInstrument.h"
#include "Notes.h"
#include "Envelope.h"
#include "ADSREnvelope.h"
CSubtractiveInstrument::CSubtractiveInstrument()
{
	m_duration = 0.1;
}


CSubtractiveInstrument::~CSubtractiveInstrument()
{
}
CSubtractiveInstrument::CSubtractiveInstrument(double bpm)
{
	m_duration = 0.1;
	m_bpm = bpm;
}
void CSubtractiveInstrument::SetNote(CNote *note)
{
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	for (int i = 0; i<len; i++)
	{
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		CComBSTR name;
		attrib->get_nodeName(&name);

		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "duration")
		{
			value.ChangeType(VT_R8);
			SetDuration(value.dblVal * (60.0 / m_bpm));
		}

		else if (name == "note")
		{
			SetFreq(NoteToFrequency(value.bstrVal));
		}

		else if (name == "resonFreq") 
		{                             
			mSubtractiveWave.SetReson(true);
			value.ChangeType(VT_R8);
			mSubtractiveWave.SetResonFreq(value.dblVal);
		}
		else if (name == "wavetype")
		{
			if ((wstring)value.bstrVal == L"Sawtooth") {
				mWaveType = L"Sawtooth";
				SetWaveType(L"Sawtooth");
			}
			else if ((wstring)value.bstrVal == L"Triangle") {
				mWaveType = L"Triangle";
				SetWaveType(L"Triangle");
			}
			else if ((wstring)value.bstrVal == L"Square") {
				mWaveType = L"Square";
				SetWaveType(L"Square");
			}
		}
		else if (name == "sweep")
		{
			if ((wstring)value.bstrVal == L"up") {
				mSubtractiveWave.SetMoogUp(true);
			}
			else if ((wstring)value.bstrVal == L"down") {
				mSubtractiveWave.SetMoogDown(true);
			}
			else if ((wstring)value.bstrVal == L"up-down") {
				mSubtractiveWave.SetMoogUpDown(true);
			}
			else if ((wstring)value.bstrVal == L"down-up") {
				mSubtractiveWave.SetMoogDownUp(true);
			}
		}
		else if (name == "bandwidth")
		{
			mSubtractiveWave.SetReson(true);
			value.ChangeType(VT_R8);
			mSubtractiveWave.SetResonBandwidth(value.dblVal);
		}

	}
	
}

void CSubtractiveInstrument::Start()
{
	mSubtractiveWave.SetSampleRate(GetSampleRate());
	mSubtractiveWave.Start();
	m_time = 0;

	m_envelope = new CADSREnvelope();

	static_cast<CADSREnvelope*>(m_envelope)->SetAtt(.05);
	static_cast<CADSREnvelope*>(m_envelope)->SetRel(.05);


	m_filter.SetEnve(m_envelope);

	m_filter.SetSource(&mSubtractiveWave);

	m_filter.SetSampleRate(GetSampleRate());
	m_filter.SetDur(m_duration);
	m_filter.Start();
}
bool CSubtractiveInstrument::Generate()
{
	m_envelope->Generate();

	mSubtractiveWave.Generate();

	auto continuePlay = m_filter.Generate();

	m_frame[0] = mSubtractiveWave.Frame(0);
	m_frame[1] = mSubtractiveWave.Frame(1);

	m_time += GetSamplePeriod();

	return continuePlay;
}

void CSubtractiveInstrument::SetFreq(double freq)
{ 
	mSubtractiveWave.SetFreq(freq); 
}

void CSubtractiveInstrument::SetAmplitude(double amp)
{
	mSubtractiveWave.SetAmp(amp); 
}

void CSubtractiveInstrument::SetWaveType(wstring type)
{ 
	mSubtractiveWave.SetWaveType(type); 
}

void CSubtractiveInstrument::SetDuration(double d)
{ 
	m_duration = d; 
}


