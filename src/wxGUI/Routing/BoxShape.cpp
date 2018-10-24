// -*-C++ -*-

/** \file
********************************************************************
* Box shape for route window.
*
* \author Rüdiger Krauße,
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
*\addtogroup GUIroute
*\{
********************************************************************/
#include "src/kernel/Defs.h"
//#include "src/kernel/Global.h"
#include "src/kernel/routing/Route-inlines.h"
#include "src/wxGUI/GUIBoxData.h"
#include "src/wxGUI/Routing/BoxShape.h"
#include "src/wxGUI/Routing/DebugRoute.h"
#include "src/wxGUI/Routing/DeviceShape.h"
#include "src/wxGUI/Routing/BoxDlg.h"
#include "src/wxGUI/MutRouteWnd.h"
#include "src/wxGUI/Routing/GUIRoute-inlines.h"
#include "src/wxGUI/GUIBoxData-inlines.h"
#include "src/wxGUI/Routing/BoxChannelShape.h"
#include "wx/msgdlg.h"
#include "wx/graphics.h"
using namespace mutabor;

namespace mutaborGUI {
#if 0
	static inline wxSize GetStaticBoxSize( MutBoxIconShape *box )
	{
		// this has to be done platform by platform as there is no way to
		// guess the thickness of a wxStaticBox border
		wxSize s  = box->DoGetBestSize();
		mutASSERT(s.x > 0);
		mutASSERT(s.y > 0);
		DEBUGLOGTYPE(other,*box,("Best Size: %dx%d"),s.x,s.y);
		return s;
	}
#endif

	IMPLEMENT_CLASS(MutBoxShape, MutBoxIconShape)

	BEGIN_EVENT_TABLE(MutBoxShape, MutBoxIconShape)
	EVT_KEY_DOWN(MutBoxShape::OnKeyDown)
	EVT_LEFT_DCLICK(MutBoxShape::LeftDblClickEvent)
	EVT_MENU(CM_MOVE_UP, MutBoxShape::CmMoveIcon)
	EVT_MENU(CM_MOVE_DOWN, MutBoxShape::CmMoveIcon)
	//EVT_CLOSE(MutDeviceShape::DeleteSelfEvent)
	END_EVENT_TABLE()

	wxSizerFlags MutBoxShape::sizerFlags;

	MutBoxShape::~MutBoxShape() {
#if 0
		if (channels) {
			wxSizerItemList list = channels->GetChildren();
			Route r;


			for (wxSizerItemList::iterator i = list.begin();
			     i != (list.end()); i++)
				{

					MutBoxChannelShape * channel =
						static_cast<MutBoxChannelShape *> ((*i)->GetWindow());
					mutASSERT(dynamic_cast<MutBoxChannelShape *>(channel));
					mutASSERT(dynamic_cast<
						  MutBoxChannelShape *
						  >((*i)->GetWindow()));
					r = channel->GetRoute();
					disconnect(r,channel);
				}
		}
#endif
		if (box)
			disconnect(box,this);
	}

	//* \todo  fix tab order
	bool MutBoxShape::Create(wxWindow * parent,wxWindowID wid, Box & b)
	{
		if (!b) return false;
		bool fine = Create(parent,wid);
		if (!fine) return false;
		channels = new wxBoxSizer(wxVERTICAL);
		SetSizer(channels);
		//	SetAutoLayout(true); done by SetSizer()
		//	m_icon = new MutBoxIconShape(this,-1);
		if (!m_icon) return false;

		connect(b,this);
		return true;
	}

	bool MutBoxShape::SetBackgroundColour(const wxColour& colour) {
		bool retval
			= MutBoxIconShape::SetBackgroundColour(colour);
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

	void MutBoxShape::BoxChanged() {
		if (!box) {
			SetBackgroundStyle(wxBG_STYLE_SYSTEM);
			return;
		}
		BoxData * guibox = ToGUIBase(box);
		int boxId = box->get_routefile_id();
		switch (boxId) {
		case NewBox:
			m_icon->SetLabel(_("New Box"));
			m_icon->SetBackgroundStyle(wxBG_STYLE_SYSTEM);
			break;
		case NoBox:
			SetBox(false);
			break;
		case GmnBox:
			m_icon->SetLabel(_("GUIDO Box"));
			break;
		default:
			m_icon->SetLabel(wxString::Format(_("Box %d"),boxId));
			break;
		}
		m_icon->SetForegroundColour(guibox->GetTextColour());
		m_icon->SetBackgroundColour(guibox->GetBackgroundColour());
	}

	void MutBoxShape::SetBox(Box & b, bool layout) {
		box = b;
		if (m_icon) {
			if (!box)
				SetBox();
			BoxChanged();
			if (layout) {
				InvalidateBestSize();
				Fit();
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
			DEBUGLOG (other, "channel best size: %dx%d" ,s.x,s.y);
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

		connect(route,box); // this might be ovewritten by ReadPanel

		MutBoxChannelShape * channel =
			GUIRouteFactory::CreateBoxChannelShape(route,
							       GetParent());
		Add(channel);

		mutASSERT(channel);
		mutASSERT(channel->GetParent() == this);
		mutASSERT(GetChannels()->GetItem(channel) != NULL);

		if (channel) {
			channel->ReadPanel(panel);
		}
		return channel;
	}

#if 0
	MutBoxChannelShape * MutBoxShape::AddChannel(Route & route)
	{
		DEBUGLOG (other, "Adding route %p to window %p" ,(void*)route.get(), (void*)m_parent);
		MutBoxChannelShape * channel =
			GUIRouteFactory::CreateBoxChannelShape(route,this);
		return Add(channel);
	}
#endif

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


	void MutBoxShape::DrawLines(wxGraphicsContext & gc,
				    wxWindow * paintingWindow /*,
								const wxPoint & origin*/
				    )
	{
		mutASSERT(paintingWindow);
#if 0
		// code for checking that certain positions are correct.
		// Unfortunately this ClientToScreen does not work correctly for GTK
		wxRect rect1 = GetScreenRect();
		wxRect rect2 = GetRect();

		wxPoint pos1 = GetScreenPosition();
		wxPoint pos2 = GetParent()->ClientToScreen(GetPosition());
		wxPoint pos3 = rect1.GetTopLeft();
		wxPoint pos4 = rect2.GetTopLeft();
		wxPoint pos5 = GetParent()->ClientToScreen(pos4);
		wxSize parentborder = (GetSize()-GetClientSize()).Scale(0.5,0.5);
		DEBUGLOG (routinggui, "screen pos (%d,%d), client pos (%d,%d)" ,
			 pos1.x,pos1.y,pos2.x,pos2.y);
		mutASSERT(pos1 == pos2 + parentborder);
		mutASSERT(pos1 == pos3);
		mutASSERT(pos2 == pos5);
#endif


		//mutASSERT(screenpos.width > 0);
		//mutASSERT(screenpos.height > 0);
		wxSizerItemList list = channels->GetChildren();
		wxPen pen(*wxBLACK,2);
		if (box) {
			pen.SetColour(ToGUIBase(box)->GetBackgroundColour());
		}
		gc.SetPen(pen);
		for (int j = 0 ; j < 2 ; j++) {
			for (wxSizerItemList::iterator i = list.begin();
			     i != (list.end()); i++) {

				MutBoxChannelShape * channel =
					static_cast<MutBoxChannelShape *> ((*i)->GetWindow());
				mutASSERT(dynamic_cast<MutBoxChannelShape *>(channel));
				mutASSERT(dynamic_cast<
					  MutBoxChannelShape *
					  >((*i)->GetWindow()));
				channel->DrawLines(gc, paintingWindow/* , origin */);
#if 0
				wxPoint pos = GetPosition();
#if __WXMAC__
				pos += maxBorderSize - borderOffset;
#endif
				channel->DrawLines(gc, pos, screenpos);
#endif
			}
			if (box) {
				pen.SetWidth(1);
				pen.SetColour(*wxBLACK);
				gc.SetPen(pen);
			}
		}
	}

#if 0
	void MutBoxShape::Add(BoxData * box) {
		SetBox(box);
	}
	bool MutBoxShape::Remove(BoxData * box){
		if (boxId == box->GetId()) {
			SetBoxId(NoBox);
			return true;
		}
		return false;
	}
#endif

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
		BoxDlg * dlg = ShowBoxDialog();
		mutASSERT(dlg);
		bool destroySelf = false;
		wxWindow * parent = m_parent; // we may lose the object
		if (!dlg) return;

		int Res, type, boxid;
		mutabor::Box b;
		MutBoxShape * newbox = NULL;

		/** \todo Move this check into MutBoxDlg */
		do {
			Res = dlg->ShowModal();

			if (Res != wxID_OK) break;

			type = dlg->GetBoxType();
			DEBUGLOG(routinggui, "Dialog box type : %d", type);
			boxid = (type == Box0) ?dlg->GetBoxNumber() : type;
			DEBUGLOG(routinggui, "Dialog box id : %d", boxid);
			b = mutabor::BoxClass::GetBox(boxid, mutabor::BoxClass::IDTypeFile);

			DEBUGLOG(routinggui, "Dialog box pointers : %p = %p", b.get(), box.get());
			if (!b || b == box)
				break;

			wxMessageBox(_("You selected a box id that is already in use. Please, try another one."),
				     _("Error"), wxOK | wxICON_ERROR);
		} while  (true);

		if (Res == wxID_OK) {

			if (CanHandleType (type)) {
				newbox = this;
				readDialog (dlg);
			} else {
				mutabor::Box box2 = BoxFactory::Create(type, boxid);
				if (box2) {
					newbox = GUIBoxFactory::CreateBoxShape(box2, GetParent());

					if (!newbox) {
						UNREACHABLEC;
						return;
					}
					mutASSERT(newbox->box);

					newbox->readDialog(dlg);
					if (LogicOn && !(newbox->box->IsOpen()))
						newbox->box->Open();

					destroySelf = replaceSelfBy(newbox);
				}
			}
		} else if (Res == wxID_REMOVE) {
			destroySelf = DeleteBox();
			// now we must not use this anymore
		}

		dlg->Destroy();

		DebugCheckRoutes();

		if (Res != ::wxID_REMOVE && !destroySelf) {
			Layout();
			InvalidateBestSize();
			Fit();
			Refresh();
		} else if (newbox) {
			newbox->Layout();
			newbox->InvalidateBestSize();
			newbox->Fit();
		}

		if (parent) {
			parent->InvalidateBestSize();
			parent->Layout();
			parent->FitInside();
			parent->Refresh();
			parent->Update();
		} else if (Res != ::wxID_REMOVE && !destroySelf) Update();
		/* we don't need to destroy this control.
		   This should have been done during device destruction
		*/
		TRACE;
	}


	void MutBoxShape::GotFocus() {
		SetCurrentBox(box);
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

		BoxDlg * dlg = new BoxDlg (parentwin);
		mutASSERT(dlg);
		if (!dlg) return NULL;

		/* get the route area in the dialog */
		wxWindow * routeWindow = dlg->GetRouteWindow();
		mutASSERT(routeWindow);
		if (!routeWindow) {
			dlg->Destroy();
			return NULL;
		}

		/* this is the wrong place to manipulate a window */
		wxSizer * routeSizer = routeWindow->GetSizer();
		mutASSERT(routeSizer);
		mutASSERT(!routeSizer || dynamic_cast<wxGridSizer *>(routeSizer));

		if (!routeSizer) {
			routeSizer = new wxGridSizer(4);
			if (!routeSizer) {
				dlg->Destroy();
				return NULL;
			}
			routeWindow->SetSizer(routeSizer);
		}

		// channels may be NULL e.g. for NewBoxShape
		if (channels) {
			wxSizerItemList list = channels->GetChildren();
			for (wxSizerItemList::iterator i = list.begin();
			     i != (list.end()); i++) {
				mutASSERT(dynamic_cast<MutBoxChannelShape *> ((*i) -> GetWindow()));
				MutBoxChannelShape::CreateRoutePanel(static_cast<MutBoxChannelShape *> ((*i)->GetWindow()),
								     parentwin,
								     routeWindow,
								     box);
			}
		}

		InitializeDialog(dlg);

		routeWindow->Layout();
		routeWindow->FitInside();
		dlg->Layout();
		dlg->Fit();
		dlg->CenterOnParent(wxBOTH);

		return dlg;
	}

	void MutBoxShape::InitializeDialog(BoxDlg * dlg) const {
		mutASSERT(dlg);
		int boxId = box ? box->get_routefile_id() : mutabor::NoBox;
		dlg->SetBoxType(boxId);
		if (boxId >= Box0)
			dlg->SetBoxNumber(boxId);
		else
			dlg->SetBoxNumber(mutabor::BoxClass::GetNextFreeBox());
	}

	bool MutBoxShape::readDialog (BoxDlg * dlg) {
		mutASSERT(dlg);
		if (!dlg) return false;
		int id = dlg->GetBoxType();
		if (id == Box0) id = dlg->GetBoxNumber();
		Box newbox = mutabor::BoxClass::GetBox(id,
						       mutabor::BoxClass::IDTypeFile);
		mutASSERT(!newbox || newbox == box);
		if (newbox && newbox != box)
			return false;
		if (box) box->set_routefile_id(id);
		else {
			box = BoxClass::GetOrCreateBox(id);
			connect (box, this);
		}
#if 0
		int boxid = box ? box->get_routefile_id : NoBox;
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
			int newBoxId = dlg->GetBoxNumber();
			if (newBoxId != boxId) {
				BoxData * oldboxdata = &BoxData::GetBox(boxId);
				Detatch(oldboxdata);
				BoxData * newboxdata = &BoxData::GetBox(newBoxId);
				Attatch(newboxdata);
			}
			break;
		}
#endif

		wxWindow * routeWindow = dlg->GetRouteWindow();
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

		SetCurrentBox(box);
		return true;
	}

	bool MutBoxShape::replaceSelfBy (MutBoxShape  * newshape)
	{
		mutUnused (newshape);
		mutASSERT (newshape);

		// this is only used in NewMutBoxShape so far.
		// But we may need it, when we implement other Box types
		UNREACHABLEC;

		return false;
	}

	bool MutBoxShape::DeleteBox() {
		// We delete the channels as the GUI access to routes
		// depends on the corresponding BoxShape.
		// Without it is not acessible anymore.

		// channels may be NULL e.g. for NewBoxShape
		if (channels) {
			wxSizerItemList list = channels->GetChildren();
			for (wxSizerItemList::iterator i = list.begin();
			     i != (list.end()); i++) {
				mutASSERT(dynamic_cast<MutBoxChannelShape *> ((*i) -> GetWindow()));
				MutBoxChannelShape * shape = static_cast<MutBoxChannelShape *> ((*i)->GetWindow());
				Route r = shape->GetRoute();
				r->Destroy();
			}
		}
		box->Destroy();
		return true;
	}


	/**
	 * Move the box in the box and update the GUI according to the
	 * new order.
	 *
	 * \param event wxCommandEvent containing the request
	 */
	void MutBoxShape::CmMoveIcon (wxCommandEvent & event) {
		switch (event.GetId()) {
		case CM_MOVE_UP:
			MoveBox(-1);
			break;
		case CM_MOVE_DOWN:
			MoveBox(+1);
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
