/***********************************************************************************
-- Class Name: C D I R L i s t   c l a s s 
-- Description and Usage:
【機能概要】
	ディレクトリ・リストを作成管理するクラスです。
-- Notes:---------------------------------------------------------------------------

-- History:
		'95.2	- created		(M.Design)
**************************************************************************************/

#ifndef __DIRLIST_H__
#define __DIRLIST_H__

#undef this_class_id
#define this_class_id 0 //list box
#include "dbmpstr.h"

// BITMAP TYPE

// BmpStrList クラスからの派生
class CDirList : public THIS_CLASS{

	DECLARE_DYNAMIC ( CDirList ) 

public:

	CDirList():THIS_CLASS()
	{};

	~CDirList()
	{};
};

#endif //__DIRLIST_H__
