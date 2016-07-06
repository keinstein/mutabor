// -*- C++ -*-
/** \file
 ********************************************************************
 * Icon class fixing issues with Mac OS.
 *
 * \author Rüdiger Krauße <krausze@mail.berlios.de>,
 * Tobias Schlemmer <keinstein@users.sourceforge.net>
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
 ********************************************************************
 *\addtogroup GUI
 *\{
 ********************************************************************/

#if (!defined(MUWX_MUTICON_H) && !defined(PRECOMPILE)) \
	|| (!defined(MUWX_MUTICON_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MUWX_MUTICON_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"

#ifndef MUWX_MUTICON_H_PRECOMPILED
#define MUWX_MUTICON_H_PRECOMPILED

#if defined(__WXMAC__)
#include "wx/icon.h"
#include "wx/image.h"

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

			DEBUGLOG (other, "max: %d" ,m);
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
			DEBUGLOG (other, "newsize: %d" , newsize);

			wxBitmap bitmap;
			wxImage image;
			image.LoadFile(name,type);
			image.ConvertAlphaToMask();
			DEBUGLOG (other, "Mask: %d; Alpha: %d" ,
				 (int)image.HasMask(),
				 (int)image.HasAlpha());
			image.Resize(wxSize(newsize,newsize),wxPoint(0,0));
			bitmap = image;
			CopyFromBitmap(bitmap);
			DEBUGLOG (other, "Real size: %dx%d" ,
				 wxIcon::GetWidth(),wxIcon::GetHeight());

			SetWidth(width);
			SetHeight(height);
			DEBUGLOG (other, "Set size: %dx%d (%d,%d)" ,
				 GetWidth(),GetHeight(),width,height);

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
#define MutICON MutIcon
#else
#define MutIcon wxIcon
#define MutICON(x) x
#endif /* __WXMAC__ */

#ifdef __WXMAC__
extern MutIcon MutNullIcon; 
#else
#define MutNullIcon wxNullIcon;
#endif

#endif /* precompiled */
#endif /* MUTICON_H */

/** \} */
