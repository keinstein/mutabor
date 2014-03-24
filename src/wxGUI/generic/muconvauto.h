/** \file 
 ********************************************************************
 * Automatic Character set detection and conversion
 *
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \license GPL
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 *
 ********************************************************************
 * \addtogroup GUI
 * \{
 * \todo remove this file: a character set error implies that the whole file has to be reconverted.
 ********************************************************************/
///////////////////////////////////////////////////////////////////////////////
// Name:        wx/convauto.h
// Purpose:     wxConvAuto class declaration
// Author:      Vadim Zeitlin
// Created:     2006-04-03
// RCS-ID:      $Id: muconvauto.h,v 1.4 2011/02/20 22:35:59 keinstein Exp $
// Copyright:   (c) 2006 Vadim Zeitlin
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef _MYWX_CONVAUTO_H_
#define _MYWX_CONVAUTO_H_

#if 0

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
	muConvAuto() : wxMBConv(),
		       m_conv(NULL),
		       m_ownsConv(false),
		       m_fallback(muConvAutoFallback),
		       m_ownsFallback(false),
		       m_bomType(BOM_None),
		       m_consumedBOM(false)
	{
		TRACEC;
		m_conv = NULL;
		m_fallback = muConvAutoFallback;
		m_ownsFallback = false;
		/* the rest will be initialized later */
	}

	// copy ctor doesn't initialize anything neither as conversion can only be
	// deduced on first use

	muConvAuto(const muConvAuto& other) : wxMBConv(),
		       m_conv(NULL),
		       m_ownsConv(false),
		       m_fallback(other.m_fallback->Clone()),
		       m_ownsFallback(true),
		       m_bomType(BOM_None),
		       m_consumedBOM(false)
	{
		TRACEC;
	}

	virtual ~muConvAuto()

	{
		TRACEC;
		if ( m_conv && m_ownsConv ) delete m_conv;
		if ( m_fallback && m_ownsFallback ) delete m_fallback;
	}

	// override the base class virtual function(s) to use our m_conv
	virtual size_t ToWChar(wchar_t *dst, size_t dstLen,
	                       const char *src, size_t srcLen = wxNO_LEN) const;

	virtual size_t FromWChar(char *dst, size_t dstLen,
	                         const wchar_t *src, size_t srcLen = wxNO_LEN) const;

	virtual size_t GetMBNulLen() const
	{
		TRACEC;
		return m_conv->GetMBNulLen();
	}

	virtual wxMBConv *Clone() const
	{
		TRACEC;
		return new muConvAuto(*this);
	}

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
		TRACEC;
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

#endif // 0

#endif // _MYWX_CONVAUTO_H_



///\}
