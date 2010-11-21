// -*- C++ -*-
/** \file
 ********************************************************************
 * Devices Basisklassen.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutIcon.h,v 1.3 2010/11/21 13:15:47 keinstein Exp $
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 1998
 * $Date: 2010/11/21 13:15:47 $
 * \version $Revision: 1.3 $
 *
 * $Log: MutIcon.h,v $
 * Revision 1.3  2010/11/21 13:15:47  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.3  2010-03-30 08:38:26  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.1.2.2  2009/11/30 12:08:57  keinstein
 * split MutRouteShapes into several files into directory Routing
 *
 * Revision 1.1.2.1  2009/08/10 11:23:12  keinstein
 * merged from wrong tree
 *
 * Revision 1.2  2009/08/10 11:15:46  keinstein
 * some steps towards new route window
 *
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

/// redefine the icon class to circumvent Icon restrictions
/**
 * On Mac OS icons will retain transparancy only if they have one
 * of the special icon sizes of the operating system. To circumvent
 * this the icon will be resized.
 *
 * On other systems this class will be omitted.
 */

class MutIcon:public wxIcon
{
protected:
	int width;
	int height;
public:

	/// Default constructor
	MutIcon():wxIcon(),width(-1),height(-1) {}

	/// Constructor to inherit frem wxIcon.
	/**
	 * Make a MutIcon from a normal wxIcon
	 * \param icon Icon to be added
	 */
	MutIcon(const wxIcon & icon):wxIcon(icon) {
		if (IsOk()) {
			width = wxIcon::GetWidth();
			height = wxIcon::GetHeight();
		}
	}

	/// Return the height of the icon.
	/** \retval Integer of the height of the icon.
	 */
	virtual int GetHeight() const
	{
		return height;
	}

	/// Return the height of the icon.
	/** \retval Integer of the width of the icon.
	 */
	virtual int GetWidth() const
	{
		return width;
	}

	/// Loads the icon and possibly resizes it.
	/**
	 * \param name name of the file to be loaded
	 * \param type bitmap type
	 * \retval true if succeeded, else otherwise
	 */
	bool LoadFile(const wxString& name, wxBitmapType type)
	{
		bool ret = wxIcon::LoadFile(name,type);
		if (!ret) return false;
		if (!IsOk ()) return false;

		width = wxIcon::GetWidth();
		height = wxIcon::GetHeight();
		int m = std::max(width,height);
		int newsize;

		DEBUGLOG(other, _T("max: %d"),m);
		if ((m == 16) || (m == 32) || (m == 48) || (m >= 128)) {
			// if >128  I don't know, what to do
			newsize = m;
			//return ret;
		}
		if (m > 32) {
			if (m > 48) newsize = 128;
			else newsize = 48;
		} else {
			if (m > 16)
				newsize = 32;
			else newsize = 16;
		}
		DEBUGLOG(other, _T("newsize: %d"), newsize);

		wxBitmap bitmap;
		wxImage image;
		image.LoadFile(name,type);
		image.ConvertAlphaToMask();
		DEBUGLOG(other, _T("Mask: %d; Alpha: %d"),
		         (int)image.HasMask(),
		         (int)image.HasAlpha());
		image.Resize(wxSize(newsize,newsize),wxPoint(0,0));
		bitmap = image;
		CopyFromBitmap(bitmap);
		DEBUGLOG(other, _T("Real size: %dx%d"),wxIcon::GetWidth(),wxIcon::GetHeight());

		SetWidth(width);
		SetHeight(height);
		DEBUGLOG(other, _T("Set size: %dx%d (%d,%d)"),GetWidth(),GetHeight(),width,height);

		return true;
	}
  

  /// Allow assignment of normal icons
  /**
   * \param icon icon to be copied.
   * \return self reference
   */
  MutIcon & operator = (wxIcon & icon) 
  {
    *(static_cast<wxIcon *>(this)) = icon;
    if (IsOk()) {
      width = wxIcon::GetWidth();
      height = wxIcon::GetHeight();
    }
    return *this;
  }    
};

#else
#define MutIcon wxIcon
#endif /* __WXMAC__ */

#ifdef __WXMAC__
extern MutIcon MutNullIcon; 
#else
#define MutNullIcon wxNullIcon;
#endif

#endif /* MUTROUTESHAPES_H */
/* \} */
