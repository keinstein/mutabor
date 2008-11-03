// -*- C++ -*-
/** \file
 ********************************************************************
 * Devices Basisklassen.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/Attic/MutRouteShapes.h,v 1.1 2008/11/03 15:31:54 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2008/11/03 15:31:54 $
 * \version $Revision: 1.1 $
 *
 * $Log: MutRouteShapes.h,v $
 * Revision 1.1  2008/11/03 15:31:54  keinstein
 * Added to the system
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/

#ifndef MUTROUTESHAPES_H
#define MUTROUTESHAPES_H

#include "wx/ogl/ogl.h"
#include "wx/icon.h"
#include "wx/stattext.h"

#include "MutIcon.h"
#include "EDevice.h"
extern MutIcon NewInputDevBitmap;
extern MutIcon MidiInputDevBitmap;
extern MutIcon MidiFileBitmap;
extern MutIcon ActiveChannel;
extern MutIcon PassiveChannel;


class MutDeviceShape: public wxIconShape {
public:
  MutDeviceShape(const wxString & name):wxIconShape() { 
    SetShadowMode(SHADOW_RIGHT);
    SetText(name);
  }
  void SetSize(double w, double h, bool WXUNUSED(recursive));
  virtual MutIcon & GetMutIcon() = 0;
  void OnDraw(wxDC & dc);
  void OnDrawContents(wxDC& dc);
  void SetText(const wxString & s);
};

class MutInputDeviceShape: public MutDeviceShape {
  EDevice * device;
public:
  MutInputDeviceShape(const wxString & name):MutDeviceShape(name) {
    device = NULL;
  }
  MutInputDeviceShape(EDevice * d);
  MutIcon & GetMutIcon() { return MidiInputDevBitmap; }
};

class MutNewInputDeviceShape: public MutInputDeviceShape {
public:
  MutNewInputDeviceShape();
  MutIcon & GetMutIcon() { return NewInputDevBitmap; }
};

class MutBoxChannelShape: public wxIconShape {
  ERoute * Route;
  MutBoxChannelShape() {}
};

//typedef MutDeviceShape* MutDeviceShapePtr;
WX_DECLARE_LIST(MutDeviceShape,MutDeviceShapeList);

#endif /* MUTROUTESHAPES_H */
/* \} */
