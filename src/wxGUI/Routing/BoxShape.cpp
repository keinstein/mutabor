// -*-C++ -*-

/** \file
********************************************************************
* Box shape for route window.
*
* \author Rüdiger Krauße <krausze@mail.berlios.de>,
* Tobias Schlemmer <keinstein@users.berlios.de>
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
*\addtogroup route
*\{
********************************************************************/
#include "src/kernel/Defs.h"
#include "src/kernel/Global.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/wxGUI/Routing/BoxShape.h"
#include "src/wxGUI/Routing/DebugRoute.h"
#include "src/wxGUI/Routing/DeviceShape.h"
#include "src/wxGUI/Routing/BoxDlg.h"
#include "src/wxGUI/MutRouteWnd.h"
#include "src/wxGUI/Routing/GUIRoute-inlines.h"
#include "src/wxGUI/GUIBoxData-inlines.h"
#include "src/wxGUI/Routing/BoxChannelShape.h"
using namespace mutabor;

namespace mutaborGUI {

	wxColour BoxColours[MAX_BOX];
	const wxColour * BoxTextColours[MAX_BOX];

	void initBoxColours() {
		for (int i = 1; i<= MAX_BOX; i++) {
			int r = ((i & 0x01) << 7 ) | ((i & 0x08) << 3) | ((i & 0x40) >> 1);
			r = r?r-1:0;
			int g = ((i & 0x02) << 6 ) | ((i & 0x10) << 2) | ((i & 0x80) >> 2);
			g = g?g-1:0;
			int b = ((i & 0x04) << 5 ) | ((i & 0x20) << 1) | ((i & 0x100) >> 3);
			b = b?b-1:0;
			DEBUGLOG2(other,_T("Box %d color %x,%x,%x"),i-1,r,g,b);
			if (r+b+g < 0x180) 
				BoxTextColours[i-1] = wxWHITE;
			else
				BoxTextColours[i-1] = wxBLACK;
			BoxColours[i-1]=wxColour(r,g,b);
		}
	}

	const wxColour & BoxColour(int nr)
	{

		DEBUGLOG2(other,_T("Colour for box %d requested"),nr);
		if ( nr == GmnBox )
			return wxNullColour;
		else if (nr == NoBox) 
			return wxNullColour;
		//	nr %= 11;
		nr %= MAX_BOX;
		if (nr < 0) nr += MAX_BOX;
		DEBUGLOG2(other,_T("Returning colour for Box number %d"),nr);
		return BoxColours[nr];

	}

	const wxColour & BoxTextColour(int nr)
	{
		DEBUGLOG2(other,_T("Text colour for box %d requested"),nr);
		if ( nr == GmnBox )
			return *wxBLACK;
		//	nr %= 11;
		nr %= MAX_BOX;
		if (nr < 0) nr += MAX_BOX;
		DEBUGLOG2(other,_T("Returning text colour for Box number %d"),nr);
		return *(BoxTextColours[nr]);
	}


	static inline wxSize GetStaticBoxSize( MutBoxIconShape *box )
	{
		// this has to be done platform by platform as there is no way to
		// guess the thickness of a wxStaticBox border
		wxSize s  = box->DoGetBestSize();
		mutASSERT(s.x > 0);
		mutASSERT(s.y > 0);
		DEBUGLOGTYPE(other,*box,_T("Best Size: %dx%d"),s.x,s.y);
		return s;
	}

	IMPLEMENT_CLASS(MutBoxShape, MutBoxIconShape)

	BEGIN_EVENT_TABLE(MutBoxShape, MutBoxIconShape)
	EVT_KEY_DOWN(MutBoxShape::OnKeyDown)
	EVT_LEFT_DCLICK(MutBoxShape::LeftDblClickEvent)
	EVT_MENU(CM_LEFT_DOUBLE_CLICK,MutBoxShape::CmLeftDblClick)
	EVT_MENU(CM_MOVE_UP, MutBoxShape::CmMoveIcon)
	EVT_MENU(CM_MOVE_DOWN, MutBoxShape::CmMoveIcon)
	//EVT_CLOSE(MutDeviceShape::DeleteSelfEvent)
	END_EVENT_TABLE()

	wxSizerFlags MutBoxShape::sizerFlags;
	int MutBoxShape::maxBoxId = Box0 - 1;

	MutBoxShape::~MutBoxShape() {
		BoxData::GetBox(boxId).Detatch(this);
	}

//* \todo  fix tab order
	bool MutBoxShape::Create(wxWindow * parent,wxWindowID wid, int Id)
	{
		MutBoxIconShape::Create(parent,wid);
		channels = new wxBoxSizer(wxVERTICAL);
		SetSizer(channels);
		//	SetAutoLayout(true); done by SetSizer()
                //	m_icon = new MutBoxIconShape(this,-1);
		m_icon = this;
		SetBoxId(Id,false);
		BoxData::GetBox(Id).Attatch(this);
		if (!m_icon) return false;
		return true;
	}

	bool MutBoxShape::SetBackgroundColour(const wxColour& colour) {
		bool retval = MutBoxIconShape::SetBackgroundColour(colour);
		if (!retval) return false;
		if (!channels) return true;
		wxSizerItemList list = channels->GetChildren();
		for (wxSizerItemList::iterator i = list.begin(); 
		     i != (list.end()); i++)
		{
      
			MutBoxChannelShape * channel = 
				static_cast<MutBoxChannelShape *> ((*i)->GetWindow());
			mutASSERT(dynamic_cast<MutBoxChannelShape *>(channel));
			mutASSERT(dynamic_cast<MutBoxChannelShape *>((*i)->GetWindow()));
			retval = retval && channel->SetBackgroundColour(colour);
		}
		return retval;

	}


	void MutBoxShape::SetBoxId(int Id, bool layout) {
		boxId = Id;
		if (boxId >= maxBoxId) maxBoxId = boxId + 1;
		if (m_icon) {
			switch (boxId) {
			case NewBox:
				m_icon->SetLabel(_("New Box"));
				m_icon->SetBackgroundStyle(wxBG_STYLE_SYSTEM);
				break;
			case NoBox:
				m_icon->SetLabel(_("No Box / Though mode"));
				m_icon->SetBackgroundStyle(wxBG_STYLE_SYSTEM);
				break;
			case GmnBox:
				m_icon->SetLabel(_("GUIDO Box"));
				m_icon->SetForegroundColour(BoxTextColour(boxId));
				m_icon->SetBackgroundColour(BoxColour(boxId));
				break;
			default:
				m_icon->SetLabel(wxString::Format(_("Box %d"),
								  boxId));
				m_icon->SetForegroundColour(BoxTextColour(boxId));
				m_icon->SetBackgroundColour(BoxColour(boxId));
				break;
			}
			if (layout) {
				InvalidateBestSize();
				SetInitialSize(wxDefaultSize);
				m_parent->Layout();
			}
		}
	
	}


	MutBoxChannelShape * MutBoxShape::Add(MutBoxChannelShape * channel) {
		if (channel) {
			channels->Add(channel,0,wxALIGN_CENTER_HORIZONTAL | wxEXPAND);
			if (channel->GetParent() != this) {
				mutASSERT(!channel->GetParent());
				AddChild(channel);
			}

			channel->SetBackgroundColour(GetBackgroundColour());
#ifdef DEBUG
			mutASSERT(channel->GetContainingSizer() == channels);
			wxSize s = channel->GetBestSize();
			mutASSERT(s.x > 0);
			mutASSERT(s.y > 0);
			DEBUGLOG (other, _T("channel best size: %dx%d"),s.x,s.y);
#endif		
			InvalidateBestSize();
			SetInitialSize(wxDefaultSize);
			m_parent->Layout();
		}
		return channel;
	}

	MutBoxChannelShape * MutBoxShape::AddChannel(RoutePanel * panel) {
		Route  route  = RouteFactory::Create();
		mutASSERT(route);
		if (!route) return NULL;
		connect(route,boxId); // this might be ovewritten by ReadPanel
		BoxData::OpenRoute(boxId);
					
	

		MutBoxChannelShape * channel = 
#ifdef DEBUG
			ToGUIBase(route)->GetShape(GetParent());
		mutASSERT(!channel);
		channel = 
#endif
			GUIRouteFactory::CreateBoxChannelShape(route,this);

		if (channel) {
			Add(channel);
			channel->ReadPanel(panel);
		}
		return channel;
	}

	MutBoxChannelShape * MutBoxShape::AddChannel(Route & route)
	{
		DEBUGLOG (other, _T("Adding route %p to window %p"),(void*)route.get(), (void*)m_parent);
		MutBoxChannelShape * channel = 
			GUIRouteFactory::CreateBoxChannelShape(route,this);
		return Add(channel);
	}

	bool MutBoxShape::Remove(MutBoxChannelShape * shape) {
		return Detach(shape);
	}

	bool MutBoxShape::HasChannel(const Route & route) {
		wxSizerItemList & list = channels->GetChildren();
		for (wxSizerItemList::iterator i = 
			     list.begin() ; i!= list.end() ; i++) {
			MutBoxChannelShape * channel = 
				static_cast<MutBoxChannelShape *> ((*i)->GetWindow());
			mutASSERT(dynamic_cast<MutBoxChannelShape *>(channel));
			mutASSERT(dynamic_cast<MutBoxChannelShape *>((*i)->GetWindow()));
			if (channel->GetRoute() == route) return true;
		}
		return false;
	}

	void MutBoxShape::AddPossibleOutput(MutOutputDeviceShape * device) {
		wxSizerItemList list = channels->GetChildren();
		for (wxSizerItemList::iterator i = list.begin(); 
		     i != (list.end()); i++)
		{
      
			MutBoxChannelShape * channel = (MutBoxChannelShape *) ((*i)->GetWindow());
			mutASSERT(dynamic_cast<MutBoxChannelShape *>(channel));
			mutASSERT(dynamic_cast<MutBoxChannelShape *>((*i)->GetWindow()));
			connect(channel,device);
		}
	}


	void MutBoxShape::DrawLines(wxDC & dc, const wxRect & screenpos) 
	{
		mutASSERT(screenpos.width > 0);
		mutASSERT(screenpos.height > 0);
		wxSizerItemList list = channels->GetChildren();
		for (wxSizerItemList::iterator i = list.begin(); 
		     i != (list.end()); i++)
		{
      
			MutBoxChannelShape * channel = 
				static_cast<MutBoxChannelShape *> ((*i)->GetWindow());
			mutASSERT(dynamic_cast<MutBoxChannelShape *>(channel));
			mutASSERT(dynamic_cast<
				  MutBoxChannelShape *
				  >((*i)->GetWindow()));
			wxPoint pos = GetPosition();
#if __WXMAC__
			pos += maxBorderSize - borderOffset;
#endif
			channel->DrawLines(dc, pos, screenpos);
		}
	}


	void MutBoxShape::Add(BoxData * box) {
		SetBoxId(box->GetId());
	}
	bool MutBoxShape::Remove(BoxData * box){
		if (boxId == box->GetId()) {
			SetBoxId(NoBox);
			return true;
		}
		return false;
	}

	bool MutBoxShape::Detach( wxWindow *window )
	{
		// avoid deleting m_staticBox in our dtor if it's being detached from the
		// sizer (which can happen because it's being already destroyed for
		// example)
		if ( window == m_icon )
		{
			UNREACHABLEC;
			m_icon = NULL;
		}

		bool ok = true;
		
		// reset the top-level parent's default item if it is this widget
		wxTopLevelWindow *tlw = 
			wxDynamicCast(wxGetTopLevelParent((wxWindow*)this),
				      wxTopLevelWindow);

		if ( tlw )
		{
			wxWindow* tmpDefaultItem = tlw->GetTmpDefaultItem();
			if ( tmpDefaultItem == this )
				tlw->SetTmpDefaultItem(NULL);
			else if ( tmpDefaultItem )
			{
				// A temporary default item masks the real 
				// default item, so
				// temporarily unset the temporary default
				// item so we can access the

				// real default item.
				tlw->SetTmpDefaultItem(NULL);

				if ( tlw->GetDefaultItem() == this )
					tlw->SetDefaultItem(NULL);

				// Set the temporary default item back.
				tlw->SetTmpDefaultItem(tmpDefaultItem);
			}
			else if ( tlw->GetDefaultItem() == this )
				tlw->SetDefaultItem(NULL);
		}
		
		RemoveChild(window);
		return ok && channels -> Detach( window );
	}

	void MutBoxShape::DoLeftDblClick() {
		BoxDlg * box = ShowBoxDialog();
		mutASSERT(box);
	
		if (!box) return;
		int Res = box->ShowModal();
		bool destroySelf = false;
	
		if (Res == wxID_OK) {
			int type = box->GetBoxType();
		
			if (CanHandleType (type)) {
				readDialog (box);
			} else {
				MutBoxShape * newbox = 
					new MutBoxShape(m_parent, wxID_ANY, type);
				if (newbox) {
					newbox->readDialog(box);
					destroySelf = replaceSelfBy(newbox);
//				m_parent->SetInitialSize(wxDefaultSize);
//				m_parent->InvalidateBestSize();
				}
			}
		} else if (Res == wxID_REMOVE) {
			wxSizerItemList list = channels->GetChildren();
			for (wxSizerItemList::iterator i = list.begin(); 
			     i != (list.end()); i++) {
				mutASSERT(dynamic_cast<MutBoxChannelShape *> ((*i) -> GetWindow()));
				static_cast<MutBoxChannelShape *> ((*i)->GetWindow())->GetRoute()->Destroy();
			}

			destroySelf = DetachBox();
		}
	
		box->Destroy();
	
		DebugCheckRoutes();

		Layout();
		InvalidateBestSize();
		Fit();
		Refresh();
		if (m_parent) {
			m_parent->Layout();
			m_parent->InvalidateBestSize();
			m_parent->FitInside();
			m_parent->Update();
			m_parent->Refresh();
		} else Update();
	
		// Signalize to delete this control
		if (destroySelf) Destroy();
	
	}


	void MutBoxShape::GotFocus() {
		int box = GetBoxId();
		mutASSERT(MIN_BOX <= box && box < MAX_BOX);
		if (box>=0 && mut_box[box].used)
			curBox = box;
		MutBoxIconShape::GotFocus();
	}


/// Constructs the box configuration dialog.
/**
 * \todo use value “unknown” for dynamic dialog creation
 *
 */
	BoxDlg * MutBoxShape::ShowBoxDialog() const{
		MutRouteWnd * parentwin = dynamic_cast<MutRouteWnd *>(GetParent());
		mutASSERT(parentwin);
		if (!parentwin) return NULL;
	
		BoxDlg * box = new BoxDlg (parentwin);
		mutASSERT(box);
		if (!box) return NULL;

		wxWindow * routeWindow = box->GetRouteWindow();
		mutASSERT(routeWindow);
		if (!routeWindow) {
			box->Destroy();
			return NULL;
		}
		wxGridSizer * routeSizer = dynamic_cast<wxGridSizer *> (routeWindow->GetSizer());
	
		if (!routeSizer) {
			if (routeWindow->GetSizer()) UNREACHABLEC;
		
			routeSizer = new wxGridSizer(4);
			if (!routeSizer) {
				box->Destroy(); 
				return NULL;
			}
			routeWindow->SetSizer(routeSizer);		
		}
	
		wxSizerItemList list = channels->GetChildren();
		for (wxSizerItemList::iterator i = list.begin(); 
		     i != (list.end()); i++) {
			mutASSERT(dynamic_cast<MutBoxChannelShape *> ((*i) -> GetWindow()));
			MutBoxChannelShape::CreateRoutePanel(static_cast<MutBoxChannelShape *> ((*i)->GetWindow()),
							     parentwin, 
							     routeWindow, 
							     GetBoxId());
		}
	 
		InitializeDialog(box);

		routeWindow->Layout();
		routeWindow->FitInside();
		box->Layout();
		box->Fit();
		box->CenterOnParent(wxBOTH);
	
		return box;
	}

	void MutBoxShape::InitializeDialog(BoxDlg * dlg) const {
		mutASSERT(dlg);
		dlg->SetBoxType(boxId);
		if (boxId >= Box0) 
			dlg->SetBoxNumber(boxId);
		else
			dlg->SetBoxNumber(maxBoxId);
	}

	bool MutBoxShape::readDialog (BoxDlg * box) {
		mutASSERT(box);
		if (!box) return false;
		int type = box->GetBoxType();
		switch (type) {
		case NoBox:
		case GmnBox:
			if (type != boxId) {
				BoxData * oldboxdata = &BoxData::GetBox(boxId);
				Detatch(oldboxdata);
				BoxData * newboxdata = &BoxData::GetBox(type);
				Attatch(newboxdata);
			}
			break;
		default:
			int newBoxId = box->GetBoxNumber();
			if (newBoxId != boxId) {
				BoxData * oldboxdata = &BoxData::GetBox(boxId);
				Detatch(oldboxdata);
				BoxData * newboxdata = &BoxData::GetBox(newBoxId);
				Attatch(newboxdata);
			}
			break;
		}
	
		wxWindow * routeWindow = box->GetRouteWindow();
		mutASSERT(routeWindow);
		if (!routeWindow) {
			return false;
		}
	
		wxWindowList & routePanels = routeWindow->GetChildren();
		for (wxWindowList::iterator i = routePanels.begin(); 
		     i != routePanels.end(); i++) {
			RoutePanel * panel = dynamic_cast<RoutePanel *> (*i);
			if (!panel) continue;
			mutASSERT(dynamic_cast<RoutePanel *> (*i));
			MutBoxChannelShape * channel = panel -> GetChannel();
			if (!channel && panel->IsEnabled()) {
				channel = AddChannel(panel);
			}
			if (channel) {
				channel -> ReadPanel(panel);
			}
		}

		int boxid = GetBoxId();
		mutASSERT(MIN_BOX <= boxid && boxid < MAX_BOX);
		if (boxid >=0 && mut_box[boxid].used)
			curBox = boxid;

		return true;
	}

	bool MutBoxShape::replaceSelfBy (MutBoxShape  * newshape)
	{
		mutASSERT (newshape);
	
		// this is only used in NewMutBoxShape so far.
		// But we need it, when we implement other Box types
		UNREACHABLEC;
	
/*
  for(Route  route = newshape->device->ReplaceDevice (device);
  route; route = route->Next) 
  {
  void * p = route->getUserData();
  mutASSERT (wxDynamicCast (p,MutBoxChannelShape));
  MutBoxChannelShape * channel = (MutBoxChannelShape *) p;
		
  mutASSERT (channel->GetInput() == this);
  channel->SetInput (newshape);
		
		
  }
	
  delete device;
  device = NULL;
	
  newshape->MoveBeforeInTabOrder (this);
	
  wxSizer * sizer = GetContainingSizer();
  sizer -> Replace (this, newshape, false);
	
  if (FindFocus()==this) {
  m_parent->Layout();
  m_parent->FitInside();
  m_parent->SetVirtualSize(wxDefaultSize);
  newshape->SetFocus();
  }
	
  Hide();	
  return true;
*/
		return false;
	}

	bool MutBoxShape::DetachBox() {
		wxSizerItemList &list = channels->GetChildren();
		for (wxSizerItemList::iterator i = list.begin(); 
		     i != (list.end()); i++) {
			MutBoxChannelShape * channel = dynamic_cast<MutBoxChannelShape *> ((*i) -> GetWindow());
			mutASSERT(channel);
			channel->DetachChannel();
		}
		return true;
	}


	void MutBoxShape::CmMoveIcon(wxCommandEvent & event) {
		switch (event.GetId()) {
		case CM_MOVE_UP:
			DEBUGLOG(routinggui,_T("Implement move up"));
			break;
		case CM_MOVE_DOWN:
			DEBUGLOG(routinggui,_T("Implement move down"));
			break;
		default:
			UNREACHABLEC;
		}
	}

	void MutBoxShape::OnKeyDown (wxKeyEvent & event) {
		if (event.HasModifiers()) {
			event.Skip();
			return;
		}

                /* Other inspirations:
		   case WXK_DELETE:
		   // cursor keys
		   */
		switch (event.GetKeyCode()) {
		case WXK_NUMPAD_ENTER:
		case WXK_RETURN:
		case WXK_SPACE:
		case WXK_NUMPAD_SPACE:
		case WXK_NUMPAD_ADD:
		case WXK_ADD:
		case WXK_WINDOWS_MENU:
		case WXK_MENU:
		{
			wxCommandEvent command(wxEVT_COMMAND_MENU_SELECTED,
					       CM_LEFT_DOUBLE_CLICK); 
			wxPostEvent(this,command); 
			return;
		}
		default:
			event.Skip();
		}
	}

	

}


/*
 * \}
 */
