#ifndef mhARRAY_H
#define mhARRAY_H

#include <wx/dynarray.h>

#define DEF_MHARRAY(T, name, baseType)								\
class name															\
{                                                                   \
public:                                                             \
    baseType data;													\
	name(int WXUNUSED(i), int WXUNUSED(j), int WXUNUSED(k)) {};                       \
	~name() {};                                                     \
	size_t GetItemsInContainer() const { return data.GetCount(); }  \
	void Flush() { data.Clear(); }                                 \
    void Add(T t) { data.Add(t); }									\
    T& operator[](size_t uiIndex) const { return data[uiIndex]; }	\
	void Destroy(size_t uiIndex) { data.RemoveAt(uiIndex); }		\
	void AddAt(T t, size_t uiIndex) { data.Insert(t, uiIndex); }		\
	void RemoveEntry(size_t uiIndex) { data.RemoveAt(uiIndex); }	\
};																	\

/*
*/
#define DEF_MHARRAYPTR(T, name, baseType)							\
class name															\
{                                                                   \
public:                                                             \
    baseType data;													\
    name(int WXUNUSED(i), int WXUNUSED(j), int WXUNUSED(k)) {};                       \
	~name() {};                                                     \
    size_t GetItemsInContainer() const { return data.GetCount(); }  \
    void Add(T t) { data.Add(new T(t)); }					\
	void Flush() { data.Clear(); }                                  \
	void RemoveEntry(size_t i) { data.RemoveAt(i); }					\
    T& operator[](size_t uiIndex) const { return *(data[uiIndex]); }\
	void Destroy(size_t uiIndex) { /*delete data[uiIndex];*/ data.RemoveAt(uiIndex); }		\
	void AddAt(T t, size_t uiIndex) { data.Insert(new T(t), uiIndex); }		\
};																	\

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

