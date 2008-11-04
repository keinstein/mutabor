/////////////////////////////////////////////////////////////////////////////
// Name:        bmpshape.h
// Purpose:     wxBitmapShape
// Author:      Julian Smart
// Modified by:
// Created:     12/07/98
// RCS-ID:      $Id: iconshape.h,v 1.1 2008/11/04 09:38:25 keinstein Exp $
// Copyright:   (c) Julian Smart, Tobias Schlemmer
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _OGL_ICON_H_
#define _OGL_ICON_H_


class WXDLLIMPEXP_OGL wxIconShape: public wxRectangleShape
{
 DECLARE_DYNAMIC_CLASS(wxIconShape)
 public:
  wxIconShape();
  ~wxIconShape();

  void OnDraw(wxDC& dc);

#if wxUSE_PROLOGIO
  // I/O
  void WriteAttributes(wxExpr *clause);
  void ReadAttributes(wxExpr *clause);
#endif

  // Does the copying for this object
  void Copy(wxShape& copy);

  void SetSize(double w, double h, bool recursive = true);
  inline wxIcon& GetIcon() const { return (wxIcon&) m_icon; }
  void SetIcon(const wxIcon& bm);
  inline void SetFilename(const wxString& f) { m_filename = f; };
  inline wxString GetFilename() const { return m_filename; }

private:
  wxIcon      m_icon;
  wxString      m_filename;
};

#endif
  // _OGL_ICON_H_


