// -*- C++ -*-
/** \file
 ********************************************************************
 * Devices Basisklassen.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Attic/MutRouteShapes.cpp,v 1.1 2008/11/03 15:31:54 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2008/11/03 15:31:54 $
 * \version $Revision: 1.1 $
 *
 * $Log: MutRouteShapes.cpp,v $
 * Revision 1.1  2008/11/03 15:31:54  keinstein
 * Added to the system
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/
#include "Defs.h"
#include "wx/wx.h"
#include "MutRouteShapes.h"
#include "MutApp.h"
#include "MutIcon.h"


MutIcon MidiInputDevBitmap;
MutIcon NewInputDevBitmap;
MutIcon MidiFileBitmap;

void MutDeviceShape::OnDraw(wxDC & dc) {
  if (!GetIcon().Ok())
    return;

  int x, y;
  x = WXROUND(m_xpos - GetMutIcon().GetWidth() / 2.0);
  y = WXROUND(m_ypos - GetMutIcon().GetHeight() / 2.0);
  DEBUGLOG(_T("Size: %dx%d"),GetIcon().GetHeight(),GetIcon().GetWidth());
  dc.DrawIcon(GetIcon(), x, y);
}

void MutDeviceShape::OnDrawContents(wxDC& dc)
{
  double bound_x, bound_y;
  double x_pos, y_pos;
  GetBoundingBoxMin(&bound_x, &bound_y);
  if (m_regions.GetCount() < 1) return;
  
  if (m_pen) dc.SetPen(* m_pen);
  
  wxShapeRegion *region = (wxShapeRegion *)m_regions.GetFirst()->GetData();
  if (region->GetFont()) dc.SetFont(* region->GetFont());

  dc.SetTextForeground(region->GetActualColourObject());
  dc.SetBackgroundMode(wxTRANSPARENT);
  if (!m_formatted) {
    DEBUGLOG(_T("Formatting"));
      oglCentreTextNoClipping(dc, &(region->GetFormattedText()), m_xpos, m_ypos, bound_x-2*m_textMarginX, bound_y-2*m_textMarginY);
      m_formatted = true;
    }
  if (!GetDisableLabel())
    {
      DEBUGLOG(_T("already formatted"));
      oglGetCentredTextExtent(dc,&(region->GetFormattedText()), 
			       m_xpos, m_ypos, 0, 0, &bound_x, &bound_y);
      region->GetPosition(&x_pos,&y_pos);
      oglDrawFormattedText(dc, &(region->GetFormattedText()), x_pos+m_xpos, y_pos+m_ypos, bound_x, bound_y, region->GetFormatMode());
    }
}


void MutDeviceShape::SetSize(double w, double h, bool WXUNUSED(recursive))
{
  if (GetMutIcon().Ok())
  {
    w = GetMutIcon().GetWidth();
    h = GetMutIcon().GetHeight();
  }

  // SetAttachmentSize(w, h);

  m_width = w;
  m_height = h;
  if (m_regions.GetCount() < 1) return;

  wxScreenDC dc;
  
  wxShapeRegion *region = (wxShapeRegion *)m_regions.GetFirst()->GetData();
  if (m_pen) dc.SetPen(* m_pen);
  if (region->GetFont()) dc.SetFont(* region->GetFont());

  dc.SetTextForeground(region->GetActualColourObject());
  dc.SetBackgroundMode(wxTRANSPARENT);

  if (!m_formatted) {
    DEBUGLOG(_T("Formatting"));
    oglCentreTextNoClipping(dc, &(region->GetFormattedText()), m_xpos, m_ypos, 
			    w-2*m_textMarginX, h-2*m_textMarginY);
    m_formatted = true;
  }
  double textwidth,textheight;
  oglGetCentredTextExtent(dc, &(region->GetFormattedText()),
                              m_xpos, m_ypos, w, h,
			  &textwidth, &textheight);
  region->SetPosition(0,WXROUND((h+textheight)/2+m_textMarginY));
  m_height += textheight + 2*m_textMarginY;
  if (textwidth + 2* m_textMarginX > m_width)
    m_width = textwidth + 2* m_textMarginX;
  
  //  wxShapeTextLine *line = 
  //  (wxShapeTextLine *)(region->GetFormattedText().GetFirst()->GetData());
  //line->SetY(h);
  DEBUGLOG(_T(""));
  region->SetSize(textwidth+2*m_textMarginX,textheight+2*m_textMarginY);
  SetAttachmentSize(m_width,m_height);
}

void MutDeviceShape::SetText(const wxString & s) {
  ClearText();
  AddText(s); 
  DEBUGLOG(_T("Setting Text \"%s\""),s.c_str());
  //  SetDisableLabel(false);
  
  /*
  wxShapeRegion * region = new wxShapeRegion();
  region->SetName(_T("Device Label"));
  region->SetFont(GetFont());
  region->SetFormatMode(FORMAT_CENTRE_HORIZ);
  region->SetText(s);
  AddRegion(region);
  AddRegion(region);
  */
  DEBUGLOG(_T(" %d text regions."),GetNumberOfTextRegions());
  
}

MutInputDeviceShape::MutInputDeviceShape(EDevice * d):
  MutDeviceShape(d->Name)
{
  device = d;
  SetFilename(wxGetApp().GetResourceName(_T("InputDevice.png")));
  DEBUGLOG(_T("Checking icon"));
  if (!MidiInputDevBitmap.IsOk())
    MidiInputDevBitmap.LoadFile(GetFilename(),wxBITMAP_TYPE_PNG);
  SetFilename(wxGetApp().GetResourceName(_T("MidiFile.png")));
  DEBUGLOG(_T("Checking icon"));
  if (!MidiFileBitmap.IsOk())
    MidiFileBitmap.LoadFile(GetFilename(),wxBITMAP_TYPE_PNG);
  DEBUGLOG(_T("Icon should be availlable"));
  SetIcon(MidiFileBitmap);
  SetSize(0,0,false);
  DEBUGLOG(_T(" %d text regions."),GetNumberOfTextRegions());
  //SetDisableLabel(false);
}


MutNewInputDeviceShape::MutNewInputDeviceShape():
  MutInputDeviceShape(_("New Input device")) 
{
  SetFilename(wxGetApp().GetResourceName(_T("NewInputDevice.png")));
  DEBUGLOG(_T("Checking icon"));
  if (!NewInputDevBitmap.IsOk())
    NewInputDevBitmap.LoadFile(GetFilename(),wxBITMAP_TYPE_PNG);
  DEBUGLOG(_T("Icon should be availlable"));
  SetIcon(NewInputDevBitmap);
  SetSize(0,0,false);
  DEBUGLOG(_T(" %d text regions."),GetNumberOfTextRegions());
  //SetDisableLabel(false);
}

#include <wx/listimpl.cpp>
WX_DEFINE_LIST(MutDeviceShapeList);


/* \} */
