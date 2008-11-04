// -*- C++ -*-
/** \file
 ********************************************************************
 * Devices Basisklassen.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutIcon.h,v 1.1 2008/11/04 13:55:58 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2008/11/04 13:55:58 $
 * \version $Revision: 1.1 $
 *
 * $Log: MutIcon.h,v $
 * Revision 1.1  2008/11/04 13:55:58  keinstein
 * new file
 *
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/

#ifndef MUTICON_H
#define MUTICON_H

#if defined(__WXMAC__)
#include "Defs.h"
#include <limits>

class MutIcon:public wxIcon {
protected:
  int width;
  int height;
public:
  virtual int GetHeight() const {
    return height;
  }
  virtual int GetWidth() const {
    return width;
  }

  bool LoadFile(const wxString& name, wxBitmapType type) {
    bool ret = wxIcon::LoadFile(name,type);
    if (!ret) return false;
    width = wxIcon::GetWidth();
    height = wxIcon::GetHeight();
    int m = std::max(width,height);
    int newsize;
    DEBUGLOG(_T("max: %d"),m);
    if ((m == 16) || (m == 32) || (m == 48) || (m >= 128)) 
      // if >128  I don't know, what to do
      return ret;
    if (m > 32) {
      if (m > 48) newsize = 128; 
      else newsize = 48;
    } else {
      if (m > 16)
	newsize = 32;
      else newsize = 16;
    }
    DEBUGLOG(_T("newsize: %d"), newsize);
    wxBitmap bitmap;
    wxImage image;
    image.LoadFile(name,type);
    image.ConvertAlphaToMask();
    DEBUGLOG(_T("Mask: %d; Alpha: %d"),
	     (int)image.HasMask(),
	     (int)image.HasAlpha());
    image.Resize(wxSize(newsize,newsize),wxPoint(0,0));
    bitmap = image;
    CopyFromBitmap(bitmap);
    DEBUGLOG(_T("Real size: %dx%d"),wxIcon::GetWidth(),wxIcon::GetHeight());
    SetWidth(width);
    SetHeight(height);
    DEBUGLOG(_T("Set size: %dx%d (%d,%d)"),GetWidth(),GetHeight(),width,height);
    
    return true;
  }
};

#else
#define MutIcon wxIcon
#endif /* __WXMAC__ */
#endif /* MUTROUTESHAPES_H */
/* \} */
