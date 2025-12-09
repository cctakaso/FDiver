/*    PortTool v2.2     version.h          */

// If want to make shareware version then define next line!!!!!
#ifndef __VERSION_H_
#define __VERSION_H_

//takaso2010
//#define VERSION_NUM		170			//1.70 use in Document
//#define NOSUP_VERSION_NUM		150		//no support version 1.50
#define VERSION_NUM		200				//1.80 use in Document
#define NOSUP_VERSION_NUM		170		//no support version 1.50
//takaso2010
//#define CRJ_TIME_STR	"ID_3.16"	//use in Crejit 
#define CRJ_TIME_STR	"ID_4.40"	//use in Crejit 

#define PROJ_SHARE_ID	"-1060-" //9509-1060-A001
#define CRJ_NEW_USERID_LENGTH	12	//"XYIJ9805210B"
#define CRJ_USERID_LENGTH	9		//"XYIJ0777B"

#define DEF_DSPCOLUM	128
#ifdef WIN32
#define DEF_WIDTH	520	//482//440
#define DEF_HIGHT	400	//360
#define MIN_READBUFSIZE	1024
#define DEF_READBUFSIZE	102400
#define MAX_READBUFSIZE	512000
#define MIN_DSPLINES	50
#define DEF_DSPLINES	5000
#define MAX_DSPLINES	10000
#else
#define DEF_WIDTH	487	//482//440
#define DEF_HIGHT	360	//360
#define MIN_READBUFSIZE	1024
#define DEF_READBUFSIZE	20480
#define MAX_READBUFSIZE	30720
#define MIN_DSPLINES	50
#define DEF_DSPLINES	1000
#define MAX_DSPLINES	2500
#endif 

#endif //__VERSION_H_
