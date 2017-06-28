/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWImage.h 													 //
//																			 //
//	Contents:																 //
//																			 //
//	Classes:																 //
//																			 //
//	Functions:																 //
//																			 //
//	History:	01-01-2003	 O. Senhadji El Rhazi   Created					 //
//				01-07-2003	 O. Senhadji El Rhazi   1 ere Release			     //
///////////////////////////////////////////////////////////////////////////////
//																			 //
//	Secure Workstation Suite Product										 //
//	SAGEM SA Data Service Provider Module									 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
/**********************************************************_FILE_HEADER_END_**/




#ifndef SWDSP_H
#define SWDSP_H

/***********************************************************
  Copyright (c) 2002, SAGEM SA
************************************************************

 PROJET      : MorphoSmart
 MODULE      : 

 FILE NAME   : $Workfile:   MORPHO_Image.h  $

 REVISION    : $Revision:   1.7  $

 DATE        : $Date:   May 06 2003 15:25:00  $

************************************************************/

#ifndef MORPHO_IMAGE_H
#define MORPHO_IMAGE_H

#ifdef MORPHO_SDK
#define MORPHO_API __declspec(dllexport)
#else
#define MORPHO_API __declspec(dllimport)
#endif

class MORPHO_API C_MORPHO_Image
{
private:
	UC	m_uc_magicFirst;
public:
	// Constants
	#define	MORPHO_LINEAR_INTERPOLATION		0x0001

	// Constructor and destructor
	C_MORPHO_Image(UL	i_ul_ImageNbIndex);
	C_MORPHO_Image(const C_MORPHO_Image& i_px_Image);
	~C_MORPHO_Image();

	// Methods
	SetImage(	UL								i_ul_ImageIndex,
				T_MORPHO_CALLBACK_IMAGE_STATUS	i_x_Image,
				UL								i_ul_imageFilter,
				CDC								*i_p_Cdc,
				CRect &							i_p_Rect);

	RefreshViewer(	UL		i_ul_ImageIndex,
					CRect &	i_p_Rect, 
					CDC*	i_p_Cdc);

private:
	HBITMAP	*m_pBitmap;
	UL		m_ul_ImageNbIndex;
	PUI		m_pui_image8bits;
	CStatic	*m_p_Static_Viewer;

	MonochromeArrayToDIB(	UL	i_ul_ImageIndex,
							UL	i_ul_ImageRow,
							UL	i_ul_ImageCol,
							PUC i_puc_Image,
							CDC	*i_p_Cdc);

	VOID ZoomImageBilineaire(	PUC entree, PUC sortie, UC background, 
								L larg_entree, L haut_entree, L reso_entree, 
								L larg_sortie, L haut_sortie, L reso_sortie);

private:
	UC	m_uc_magicEnd;
};

#endif


#endif//SWDSP_H