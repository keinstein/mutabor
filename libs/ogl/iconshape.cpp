/////////////////////////////////////////////////////////////////////////////
// Name:        bmpshape.cpp
// Purpose:     Bitmap shape class
// Author:      Julian Smart
// Modified by:
// Created:     12/07/98
// RCS-ID:      $Id: iconshape.cpp,v 1.2 2009/08/10 11:15:46 keinstein Exp $
// Copyright:   (c) Julian Smart, Tobias Schlemmer
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#if wxUSE_PROLOGIO
#include "wx/deprecated/wxexpr.h"
#endif

#include "wx/ogl/ogl.h"


/*
 * Icon object
 *
 */

IMPLEMENT_DYNAMIC_CLASS(wxIconShape, wxRectangleShape)

wxIconShape::wxIconShape():wxRectangleShape(100.0, 50.0)
{
	m_filename = wxEmptyString;
}

wxIconShape::~wxIconShape()
{}

void wxIconShape::OnDraw(wxDC& dc)
{
	if (!m_icon.Ok())
		return;

	int x, y;

	x = WXROUND(m_xpos - m_icon.GetWidth() / 2.0);

	y = WXROUND(m_ypos - m_icon.GetHeight() / 2.0);

	dc.DrawIcon(m_icon, x, y);
}

void wxIconShape::SetSize(double w, double h, bool WXUNUSED(recursive))
{
	if (m_icon.Ok()) {
		w = m_icon.GetWidth();
		h = m_icon.GetHeight();
	}

	SetAttachmentSize(w, h);

	m_width = w;
	m_height = h;
	SetDefaultRegionSize();
}

#if wxUSE_PROLOGIO
void wxIconShape::WriteAttributes(wxExpr *clause)
{
	// Can't really save the icon; so instantiate the icon
	// at a higher level in the application, from a symbol library.
	wxRectangleShape::WriteAttributes(clause);
	clause->AddAttributeValueString(_T("filename"), m_filename);
}

void wxIconShape::ReadAttributes(wxExpr *clause)
{
	wxRectangleShape::ReadAttributes(clause);
	clause->GetAttributeValue(_T("filename"), m_filename);
}

#endif

// Does the copying for this object
void wxIconShape::Copy(wxShape& copy)
{
	wxRectangleShape::Copy(copy);

	wxASSERT( copy.IsKindOf(CLASSINFO(wxIconShape)) ) ;

	wxIconShape& iconCopy = (wxIconShape&) copy;

	iconCopy.m_icon = m_icon;
	iconCopy.SetFilename(m_filename);
}

void wxIconShape::SetIcon(const wxIcon& bm)
{
	m_icon = bm;

	if (m_icon.Ok())
		SetSize(m_icon.GetWidth(), m_icon.GetHeight());
}


