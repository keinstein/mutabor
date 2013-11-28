/** \file   -*- C++ -*-
 ********************************************************************
 * Some array definitons
 *
 * Copyright:   (c) 2008 TU Dresden
 * \author R. Krauße,  Tobias Schlemmer <keinstein@users.berlios.de>
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
 * \addtogroup GUI
 * \{
 ********************************************************************/
#ifndef mhARRAY_H
#define mhARRAY_H

#include "wx/dynarray.h"

template <class T>
class mhArray {
protected:
	WX_DEFINE_ARRAY_INT(BYTE, baseType);
	baseType data;
public:
	mhArray(int WXUNUSED(i), int WXUNUSED(j), int WXUNUSED(k)) {};
	~mhArray() {};
	size_t GetItemsInContainer() const { return data.GetCount(); }
	void Flush() { data.Clear(); }
	void Add(T t) { data.Add(t); }
	T& operator[](size_t uiIndex) const { return data[uiIndex]; }
	void Destroy(size_t uiIndex) { data.RemoveAt(uiIndex); }
	void AddAt(T t, size_t uiIndex) { data.Insert(t, uiIndex); }
	void RemoveEntry(size_t uiIndex) { data.RemoveAt(uiIndex); }
};

#define DEF_MHARRAY(T, name, baseType)					\
	class name							\
	{								\
	public:								\
		baseType data;						\
		name(int WXUNUSED(i), int WXUNUSED(j), int WXUNUSED(k)) {}; \
		~name() {};						\
		size_t GetItemsInContainer() const { return data.GetCount(); } \
		void Flush() { data.Clear(); }				\
		void Add(T t) { data.Add(t); }				\
		T& operator[](size_t uiIndex) const { return data[uiIndex]; } \
		void Destroy(size_t uiIndex) { data.RemoveAt(uiIndex); } \
		void AddAt(T t, size_t uiIndex) { data.Insert(t, uiIndex); } \
		void RemoveEntry(size_t uiIndex) { data.RemoveAt(uiIndex); } \
	}								\

/*
*/
#define DEF_MHARRAYPTR(T, name, baseType)				\
	class name							\
	{								\
	public:								\
		baseType data;						\
		name(int WXUNUSED(i), int WXUNUSED(j), int WXUNUSED(k)) {}; \
		~name() {};						\
		size_t GetItemsInContainer() const { return data.GetCount(); } \
		void Add(T t) { data.Add(new T(t)); }			\
		void Flush() { data.Clear(); }				\
		void RemoveEntry(size_t i) { data.RemoveAt(i); }	\
		T& operator[](size_t uiIndex) const { return *(data[uiIndex]); } \
		void Destroy(size_t uiIndex) { /*delete data[uiIndex];*/ data.RemoveAt(uiIndex); } \
		void AddAt(T t, size_t uiIndex) { data.Insert(new T(t), uiIndex); } \
	};								\

#define DEF_STACK(T, name, baseType)											\
class name															\
{                                                                   \
public:                                                             \
	baseType data;												\
    name() {};                       \
    name(int WXUNUSED(i), int WXUNUSED(j), int WXUNUSED(k)) {};                       \
	~name() {};														\
	void Push(T t) { data.Add(t); }									\
	T Pop() { T h = data.Last(); data.RemoveAt(data.GetCount()-1); return h; } \
	bool IsEmpty() const { return data.GetCount() == 0; }			\
	T Top() const { return data.Last(); }							\
};																	\

#endif


///\}
