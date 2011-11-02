/** \file 
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/mu32/Defs.h,v 1.24 2011/11/02 14:31:57 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/11/02 14:31:57 $
 * \version $Revision: 1.24 $
 * \license GPL
 *
 * $Log: Defs.h,v $
 * Revision 1.24  2011/11/02 14:31:57  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.23  2011-10-04 17:16:13  keinstein
 * make program compile on Mac (wx 2.9) and fix some memory corruption
 *
 * Revision 1.22  2011-09-30 18:07:04  keinstein
 * * make compile on windows
 * * s/wxASSERT/mutASSERT/g to get assert handler completely removed
 * * add ax_boost_base for boost detection
 *
 * Revision 1.21  2011-09-29 05:26:58  keinstein
 * debug intrusive_ptr
 * fix storage and retrieving of input/output devices in treestorage
 * save maximum border size in icons
 * Apply the calculated offset in IconShape (box and box channels still missing)
 * Fix debug saving and restoring route information/route window on activation
 * Add wxWANTS_CHARS to MutEditWindow
 *
 * Revision 1.20  2011-09-28 07:35:53  keinstein
 * Make distclean happy
 *
 * Revision 1.19  2011-09-28 05:35:47  keinstein
 * fix compiling on ubuntu
 *
 * Revision 1.18  2011-09-27 20:13:20  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.17  2011-09-06 08:09:20  keinstein
 * fix a compiler error showing a corruped error message
 *
 * Revision 1.16  2011-02-20 22:35:55  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.2  2010-11-21 13:15:51  keinstein
 * merged experimental_tobias
 *
 * Revision 1.1.2.1  2010-01-11 10:12:59  keinstein
 * added some .cvsignore files
 *
 *
 ********************************************************************
 * \addtogroup kernel
 * \{
 ********************************************************************/
// prevent double inclusion

#ifndef	MU32_DEFS_H
#define MU32_DEFS_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#define MUTWIN
//#define MUTMIDI
#endif

#ifdef WX
#include "mywx/mhDefs.h"
#include "wx/wxchar.h"
#include "wx/intl.h"
#endif


#if defined(MUTWIN) && (!defined(WX) || defined(__WXMSW__))
#include <windows.h>
#include "wx/msw/winundef.h"
#endif

#ifdef WX
#include "stdint.h"
#  include "wx/setup.h"
#  include "wx/wxchar.h"
#  if !defined(__WXMSW__)
#define UINT unsigned int
#define WORD uint16_t
#define DWORD uint32_t
#define BYTE uint8_t
#define BOOL bool
#define pascal
#define CALLBACK
#endif
#define _export
#else // not WX
#define REUSE(type) type
#endif

#if defined(WX)
#define STD_PRE std
#else
#define STD_PRE
#endif

#define mutT _T

#define mutUnused(expr) do { (void)(expr); } while (0)

#ifdef WX
#define mut_thread_mutex(name)
#define mut_thread_locker(name)
#define mut_thread_lock(name) do {} while (0)
#define mut_thread_release(name) do {} while (0)


#define mutChar   wxChar
#define mutString wxString
#define mutStringRef mutString &
#define mutEmptyString (wxString) wxEmptyString
#define mutDelString(string) (string = mutEmptyString)
#define mutFreeString(string) do {} while (0)
#define mutFopen  wxFopen
#define mutCopyString(left,right) (left = right)
#define mutCopyIntoString(left,right) (left = right)
#define mutStrdup wxStrdup
#define mutStrCmp(left, right) (left.Cmp (right))
#define mutStrEq(left, right) (left == right)
#define mutStrEq2(left, right) (left.IsSameAs(right))
#define mutStrLast(x) ((x).Last())
#define mutLen(x) ((x).Len())
#define C_STR(x) ((const wxChar *)(x))
#define mutC_STR(x) (C_STR(muT(x)))

#define mutStrLen wxStrlen
#define mutStrChr wxStrchr
#define mutIsspace wxIsspace
#define mutIsdigit wxIsdigit
#define mutFileName(name) (name.fn_str())

#define mutOFstream wxOutputStream
#define mutIFstream wxInputStream
#define mutTextStream wxTextFile

#define mutOpenOFstream(name,filename) \
	wxFFileOutputStream name (filename, _T("wb"))
#define mutOpenIFstream(name,filename) \
	wxFFileInputStream name (filename, _T("rb"))
#define mutOpenITextStream(name, filename) \
	wxTextFile name (filename)

#define mutWriteStream(stream,data,count) \
	(stream).Write(data,count)
#define mutReadStream(stream,data,count) \
	(stream).Read(data,count)
#define mutCloseStream(stream)

#define mutPutC(stream,data) (stream).PutC(data)
#define mutGetC(stream) (stream).GetC()

#define mutStreamBad(stream) (!(stream).IsOk())
#define mutStreamGood(stream) ((stream).IsOk())
#define mutStreamEOF(stream) ((stream).Eof())

#if wxCHECK_VERSION(2,9,0)
#define mutTranslationChar char
#define N_T(s) (s)
#define _C_STR(s) C_STR(s)
#else
#define mutTranslationChar mutChar
#define N_T(s) _T(s)
#define _C_STR(s) (s)
#endif

#else

#define mutChar char
#define mutString (char*)
#define mutStringRef mutString
#define mutEmptyString ((char *) NULL)
#define mutFreeString(string) if (string) free (string)
#define mutDelString(string) (mutFreeString(string), string = mutEmptyString)
#define mutFopen fopen
#define mutCopyString(left,right) left = strdup(right)
#define mutCopyIntoString(left,right) strcpy(left,right)
#define mutStrdup strdup
#define mutStrCmp(left,right) strcmp (left, right)
#define mutStrEq(left,right)  (!strcmp (left, right))
#define mutStrLast(x) (x[strlen(x)])
#define C_STR(x) (x)
#define mutC_STR(x) (x)


#define mutStrLen strlen
#define mutStrChr strchr
#define mutFileName

#define mutOFstream STD_PRE::ofstream
#define mutIFstream STD_PRE::ifstream
#define mutTextStrem STD_PRE::ifstream

#define mutOpenOFstream(name,filename) \
   STD_PRE::ofstream name(mutFileName(filename), STD_PRE::ios::out | STD_PRE::ios::binary/*0, filebuf::openprot*/)
#define mutOpenIFstream(name,filename) \
   STD_PRE::ifstream name(mutFileName(filename), STD_PRE::ios::in | STD_PRE::ios::binary/*0, filebuf::openprot*/)

#define mutWriteStream(stream,data,count) \
	stream.write(data,count)
#define mutReadStream(stream,data,count) \
	stream.read(data,count)
#define mutCloseStream(stream) stream.close()


#define mutPutC(stream,data) stream.putc(data)
#define mutGetC(stream) stream.getc()

#define mutStreamBad(stream) (stream.bad())
#define mutStreamGood(stream) (!stream.bad())
#define mutStreamEOF(stream) (stream.eof())

#endif

#ifdef DEBUG
#define mutAssertMsg(cond,msg) \
   if (!(cond)) \
	 std::cerr << (const char *)(wxString(msg).ToUTF8()) << std::endl; \
   assert(cond)
#define mutASSERT wxASSERT
#else
#define mutAssertMsg(cond,msg)
#define mutASSERT(cond)
#endif

inline wxString getContextLocal(const wxString & s)
{
	wxString ret = s.AfterFirst('|');

	if (ret == wxEmptyString) return s;
	else return ret;
}



class intrusive_ptr_refcount_type {
private:
	size_t value;

	template<class intrusive_ptr_T>
		friend void intrusive_ptr_add_ref(intrusive_ptr_T * obj);	
	template<class intrusive_ptr_T>
		friend void intrusive_ptr_release(intrusive_ptr_T * obj);
	template <class intrusive_ptr_T>
		friend size_t intrusive_ptr_get_refcount(intrusive_ptr_T * obj);
public:
	mut_thread_mutex(mutex)						
	intrusive_ptr_refcount_type():value(0) {}

	void lock () {
		mut_thread_lock(mutex);
	}

	void unlock () {
		mut_thread_release(mutex);
	}

	size_t operator ++() {
		lock();
		value++;
		unlock();
		return value;
	}

	size_t operator ++(int) {
		size_t retval = value;
		++(*this);
		return retval;
	}

	size_t operator --() {
		lock();
		value--;
		unlock();
		return value;
	}

	size_t operator --(int) {
		size_t retval = value;
		--(*this);
		return retval;
	}

	operator size_t () const {
		return value;
	}
};			

template <class intrusive_ptr_T>
inline size_t intrusive_ptr_get_refcount(intrusive_ptr_T * obj)
{
	if (!obj) return 0;
	return obj->intrusive_ptr_refcount;
}

template <class intrusive_ptr_T>
inline void intrusive_ptr_add_ref(intrusive_ptr_T * obj)
{
	if (!obj) return;
	++(obj->intrusive_ptr_refcount);
	DEBUGLOGTYPE(smartptr,*obj,_T("Incrementing %p to %d"),
		  obj,intrusive_ptr_get_refcount(obj));
}

template <class intrusive_ptr_T>
inline void intrusive_ptr_release(intrusive_ptr_T * obj)
{
	if (!obj) return;
	DEBUGLOGTYPE(smartptr,*obj,_T("Decrementing %p from %d"),
		  obj,intrusive_ptr_get_refcount(obj));
	if (!(--(obj->intrusive_ptr_refcount))) delete obj;
}

							      
#define REFPTR_INTERFACE						\
	public:								\
	intrusive_ptr_refcount_type intrusive_ptr_refcount;		


#define CHECK_REFPTR_NULL(class_data)				\
	mutASSERT(intrusive_ptr_get_refcount(class_data) <= 1);

// we are using std::max and std::min
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

#define MIDI_MIN_CHANNEL 0
#define MIDI_MAX_CHANNEL 15
#define MIDI_MIN_KEY 0
#define MIDI_MAX_KEY 0x7f
#endif /* MU32_DEFS_H */




///\}
