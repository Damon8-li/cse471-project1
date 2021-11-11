#include "stdafx.h"
#include "AudioEffect.h"

#include "Note.h"


CAudioEffect::CAudioEffect()
{
	m_queue1.resize(MAXQUEUESIZE);
	m_queue2.resize(MAXQUEUESIZE);
}


CAudioEffect::~CAudioEffect()
{
}

void CAudioEffect::SetNote(CNote *note)
{
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	for (int i = 0; i < len; i++)
	{
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		CComBSTR name;
		attrib->get_nodeName(&name);

		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "dry")
		{
			value.ChangeType(VT_R8);
			SetDry(value.dblVal);
		}
		else if (name == "delay")
		{
			value.ChangeType(VT_R8);
			SetDelay(value.dblVal);
		}
		else if (name == "threshold")
		{
			value.ChangeType(VT_R8);
			SetThreshold(value.dblVal);
		}
		else if (name == "wet")
		{
			value.ChangeType(VT_R8);
			SetWet(value.dblVal);
		}
	}
}

void CAudioEffect::SetDelay(double delay)
{ 
	mDelay = delay;
}

void CAudioEffect::SetWet(double wet)
{
	mWet = wet; 
}

void CAudioEffect::SetDry(double dry)
{
	mDry = dry; 
}

void CAudioEffect::SetThreshold(double threshold)
{ 
	mThreshold = threshold; 
}