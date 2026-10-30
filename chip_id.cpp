/*
 * chip_id.cpp
 *
 *	Reads STM32 unique 96 bit chip identifier
 *	Uses shift add to produce choice of 8 or 12 bit short ID.
 *	This should be sufficient to tie several items to CAN bus without ID clashes
 *
 *  Created on: 30 Oct 2026
 *      Author: Jon Freeman  B. Eng. Hons
 */
#include	"main.h"
//#include	<cstdio>

//#include	"Serial.hpp"
//extern	Serial	pc;


class	my_ID_class	{	//	Read unique STM32 die ident
	const	uint32_t	uid[3] = 	{*(uint32_t *)UID_BASE
									, *(uint32_t *)(UID_BASE + 4)
									, *(uint32_t *)(UID_BASE + 8)};

//	const	uint32_t	uidb[3] = {HAL_GetUIDw0(), HAL_GetUIDw1(), HAL_GetUIDw2()};	//	produces same as above

	const	uint16_t	ID8 =	//	8 bit
			(uid[0] + uid[1] + uid[2] +
			(uid[0] >> 8) + (uid[1] >> 8) + (uid[2] >> 8) +
			(uid[0] >> 16) + (uid[1] >> 16) + (uid[2] >> 16) +
			(uid[0] >> 24) + (uid[1] >> 24) + (uid[2] >> 24))
			& 0x0ff
			;

	const	uint16_t	ID12 =	//	12 bit
			(uid[0] + (uid[0] >> 12) + (uid[0] >> 24) + (uid[1] << 8) +
			(uid[1] >> 4) + (uid[1] >> 16) + (uid[1] >> 28) + (uid[2] << 4) +
			(uid[2] >> 8) + (uid[2] >> 20))
			& 0x0fff
			;

public:

	uint16_t	get_ID12	()	const	{		return		(ID12);	}

	uint16_t	get_ID8		()	const	{		return		(ID8);	}

//	void	show	()	{
//		char	t[84];
//		int len = sprintf	(t, "\r\nID 0x%08lx, 0x%08lx, 0x%08lx\r\n", uida[0], uida[1], uida[2]);
//		pc.write	(t, len);
//	}

//	bool	idcompare	()	{	//	Proved both are the same
//		return	((uida[0] == uidb[0]) && (uida[1] == uidb[1])&& (uida[2] == uidb[2]));
//	}


}	My_ID	;


//void	show_id	()	{
//	My_ID.show();
//}


uint16_t	get_ID8	()	{
//	if	(My_ID.idcompare())
//		pc.write	("ID methods same\r\n", 17);
//	else
//		pc.write	("ID methods NOT same\r\n", 21);
//	My_ID.show();
	return	(My_ID.get_ID8());
}




