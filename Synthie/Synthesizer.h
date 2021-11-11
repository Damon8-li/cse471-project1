#pragma once

#include "msxml2.h"
#include "Instrument.h"
#include "ToneInstrument.h"
#include "Note.h"
#include "SubtractiveInstrument.h"

#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Chorus.h"
#include "Flange.h"
#include "Compressor.h"


using namespace std;

class CSynthesizer
{
public:
	CSynthesizer();
	virtual ~CSynthesizer();

public:
	//! Number of audio channels
	int GetNumChannels() { return m_channels; }

	//! Sample rate in samples per second
	double GetSampleRate() { return m_sampleRate; }

	//! Sample period in seconds (1/samplerate)
	double GetSamplePeriod() { return m_samplePeriod; }

	//! Set the number of channels
	void SetNumChannels(int n) { m_channels = n; }

	//! Set the sample rate
	void SetSampleRate(double s) { m_sampleRate = s;  m_samplePeriod = 1.0 / s; }

	void Start();

	bool Generate(double * frame);

	double GetTime() { return m_time; }

	void Clear();

	void OpenScore(CString & filename);

	double GetBPM() { return m_bpm; }

private:
	int		m_channels;
	double	m_sampleRate;
	double	m_samplePeriod;
	double m_time;
	double  m_bpm;                  //!< Beats per minute
	int     m_beatspermeasure;  //!< Beats per measure
	double  m_secperbeat;        //!< Seconds per beat
	int m_currentNote;          //!< The current note we are playing
	int m_measure;              //!< The current measure
	double m_beat;              //!< The current beat within the measure
	vector<CNote> m_notes;
	list<CInstrument*> m_instruments;

private:
	void XmlLoadScore(IXMLDOMNode * xml);
	void XmlLoadInstrument(IXMLDOMNode * xml);
	void XmlLoadNote(IXMLDOMNode * xml, std::wstring & instrument);

private:
	CChorus mChorusEffect;
	CFlange mFlangeEffect;
	CCompressor mCompressorEffect;

	
};