///////////////////////////////////////////////////////////////////////////////
// Name:        wx/convauto.h
// Purpose:     wxConvAuto class declaration
// Author:      Vadim Zeitlin
// Created:     2006-04-03
// RCS-ID:      $Id: muconvauto.h,v 1.1 2008/01/25 10:04:30 keinstein Exp $
// Copyright:   (c) 2006 Vadim Zeitlin
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef _MYWX_CONVAUTO_H_
#define _MYWX_CONVAUTO_H_

#include "wx/convauto.h"
#include "wx/strconv.h"

extern wxMBConv * muConvAutoFallback;

#if wxUSE_WCHAR_T

// ----------------------------------------------------------------------------
// wxConvAuto: uses BOM to automatically detect input encoding
// ----------------------------------------------------------------------------

class muConvAuto : public wxMBConv
{
public:
    // default ctor, the real conversion will be created on demand
    muConvAuto() { m_conv = NULL; 
				   m_fallback = muConvAutoFallback;
				   m_ownsFallback = false;
					/* the rest will be initialized later */ 
				 }

    // copy ctor doesn't initialize anything neither as conversion can only be
    // deduced on first use
    muConvAuto(const muConvAuto& other) : wxMBConv() { 
		m_conv = NULL; 
		m_fallback = other.m_fallback->Clone(); 
		m_ownsFallback = true;
		}

    virtual ~muConvAuto() { 
		if ( m_conv && m_ownsConv ) delete m_conv; 
		if ( m_fallback && m_ownsFallback ) delete m_fallback;
	}

    // override the base class virtual function(s) to use our m_conv
    virtual size_t ToWChar(wchar_t *dst, size_t dstLen,
                           const char *src, size_t srcLen = wxNO_LEN) const;

    virtual size_t FromWChar(char *dst, size_t dstLen,
                             const wchar_t *src, size_t srcLen = wxNO_LEN) const;

    virtual size_t GetMBNulLen() const { return m_conv->GetMBNulLen(); }

    virtual wxMBConv *Clone() const { return new muConvAuto(*this); }

private:
    // all currently recognized BOM values
    enum BOMType
    {
        BOM_None,
        BOM_UTF32BE,
        BOM_UTF32LE,
        BOM_UTF16BE,
        BOM_UTF16LE,
        BOM_UTF8
    };

    // return the BOM type of this buffer
    static BOMType DetectBOM(const char *src, size_t srcLen);

    // initialize m_conv with the conversion to use by default (UTF-8)
    void InitWithDefault()
    {
        m_conv = &wxConvUTF8;
        m_ownsConv = false;
    }

    // create the correct conversion object for the given BOM type
    void InitFromBOM(BOMType bomType);

    // create the correct conversion object for the BOM present in the
    // beginning of the buffer; adjust the buffer to skip the BOM if found
    void InitFromInput(const char **src, size_t *len);

    // adjust src and len to skip over the BOM (identified by m_bomType) at the
    // start of the buffer
    void SkipBOM(const char **src, size_t *len) const;


    // conversion object which we really use, NULL until the first call to
    // either ToWChar() or FromWChar()
    wxMBConv *m_conv;
	
    // true if we allocated m_conv ourselves, false if we just use an existing
    // global conversion
    bool m_ownsConv;

	// fallback conversion object
	wxMBConv *m_fallback;

    // true if we allocated m_conv ourselves, false if we just use an existing
    // global conversion
    bool m_ownsFallback;

    // our BOM type
    BOMType m_bomType;

    // true if we already skipped BOM when converting (and not just calculating
    // the size)
    bool m_consumedBOM;


    DECLARE_NO_ASSIGN_CLASS(muConvAuto)
};

#else // !wxUSE_WCHAR_T

// it doesn't matter how we define it in this case as it's unused anyhow, but
// do define it to allow the code using wxConvAuto() as default argument (this
// is done in many places) to compile
typedef wxMBConv muConvAuto;

#endif // wxUSE_WCHAR_T/!wxUSE_WCHAR_T



#endif // _MYWX_CONVAUTO_H_
