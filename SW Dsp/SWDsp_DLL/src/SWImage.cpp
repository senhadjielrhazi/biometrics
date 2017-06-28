/**_BEGIN_FILE_HEADER_********************************************************/
//																			 //
//	Copyright (C) SAGEM S.A., 2002-2003.									 //
//																			 //
//	File:		SWImage.cpp													 //
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




#include "stdafx.h"

/***********************************************************

 PROJET      : Morpho Smart Optique
 MODULE      : 

 FILE NAME   : $Workfile:   MORPHO_Image.cpp  $
 DESCRIPTION :

 REVISION    : $Revision:   1.10  $

 DATE        : $Date:   Mar 13 2003 13:35:36  $

************************************************************
  Copyright (c) 2002, SAGEM SA
************************************************************

 LOG         : $Log:   J:/Mobi 5/Dev/Base/archives/PC/Sdk/MORPHO_SDK/MORPHO_Image.cpp-arc  $
 * 
 *    Rev 1.10   Mar 13 2003 13:35:36   BAYON
 * Corrections diverses
 * 
 *    Rev 1.9   Jan 31 2003 12:45:12   BAYON
 * Pointeur à NULL après libération
 * 
 *    Rev 1.8   Jan 15 2003 13:53:52   BAYON
 * Memory leak
 * 
 *    Rev 1.7   Nov 08 2002 12:52:24   BAYON
 * Traitement d'images dégradées plus complet
 * 
 *    Rev 1.6   Nov 06 2002 15:34:12   BAYON
 * Amélioration interpolation linéaire
 * 
 *    Rev 1.5   Oct 30 2002 11:25:18   BAYON
 * Modif T_MORPHO_CALLBACK_IMAGE_STATUS
 * 
 *    Rev 1.4   Oct 30 2002 09:49:48   BAYON
 * Modidif interface ILV
 * 
 *    Rev 1.3   Oct 24 2002 15:39:40   BAYON
 * Interpolation lineaire
 * 
 *    Rev 1.2   Oct 24 2002 11:39:00   BAYON
 * Modif messages asynchrones
 * 
 *    Rev 1.1   Oct 23 2002 10:59:58   BAYON
 * Extrapolation linéaire
 * 
 *    Rev 1.0   Oct 18 2002 16:59:36   BAYON
 * Initial revision.
************************************************************/

#include "stdafx.h"
#include <math.h>
#include "MORPHO_Interface.h"
#include "MORPHO_Internal.h"
#include "MSO_types.h"

#define MAX_IMAGE_SIZE	(4*416*416)

C_MORPHO_Image::C_MORPHO_Image(UL	i_ul_ImageIndex)
{
	REGISTER_MAGIC

	m_pui_image8bits = (PUI)malloc(MAX_IMAGE_SIZE);
	m_pBitmap = (HBITMAP*)calloc(i_ul_ImageIndex, sizeof(HBITMAP));
	m_ul_ImageNbIndex = i_ul_ImageIndex;
}

C_MORPHO_Image::C_MORPHO_Image(const C_MORPHO_Image& i_px_Image)
{
	REGISTER_MAGIC

	m_ul_ImageNbIndex = i_px_Image.m_ul_ImageNbIndex;

	m_pui_image8bits = (PUI)malloc(MAX_IMAGE_SIZE);
	memcpy(m_pui_image8bits, i_px_Image.m_pui_image8bits, MAX_IMAGE_SIZE);

	m_pBitmap = (HBITMAP*)calloc(m_ul_ImageNbIndex, sizeof(HBITMAP));
}

C_MORPHO_Image::~C_MORPHO_Image()
{
	UL	l_ul_Cnt;

	if (m_pui_image8bits!=NULL)
	{
		free(m_pui_image8bits);
		m_pui_image8bits = NULL;
	}

	for (l_ul_Cnt=0; l_ul_Cnt<m_ul_ImageNbIndex; l_ul_Cnt++)
		if (m_pBitmap[l_ul_Cnt] != NULL)
			DeleteObject(m_pBitmap[l_ul_Cnt]);

	if (m_pBitmap != NULL)
	{
		free(m_pBitmap);
		m_pBitmap = NULL;
	}
}

#define CORRECT_LEVEL2(a)	if (a == 0x00)		\
								a = 0x02;		\
							else if (a == 0x40)	\
								a = 0x48;		\
							else if (a == 0x80)	\
								a = 0xB0;		\
							else if (a == 0xC0)	\
								a = 0xFE;		\

#define CORRECT_LEVEL1(a)	if (a == 0x00)		\
								a = 0x00;		\
							else if (a == 0x80)	\
								a = 0xFF;		\

C_MORPHO_Image::SetImage(	UL								i_ul_ImageIndex,
							T_MORPHO_CALLBACK_IMAGE_STATUS	i_x_Image,
							UL								i_ul_imageFilter,
							CDC								*i_p_Cdc,
							CRect &							i_p_Rect)
{
	I		l_i_ImageSize, l_i_Cnt;
	I		l_i_Ret;
	PUC		l_puc_image8bits;
	PUC		l_puc_image = NULL;

	CHECK_MAGIC

	if (m_ul_ImageNbIndex <= i_ul_ImageIndex)
		return MORPHOERR_BADPARAMETER;

	if (m_pui_image8bits == NULL)
		return MORPHOERR_CORRUPTED_CLASS;

	if (i_ul_imageFilter & MORPHO_LINEAR_INTERPOLATION)
	{
		l_puc_image = (PUC)malloc(MAX_IMAGE_SIZE);
		if (l_puc_image == NULL)
			l_i_Ret = MORPHOERR_MEMORY_PC;
		l_puc_image8bits = l_puc_image;
	}
	else
		l_puc_image8bits = (PUC)m_pui_image8bits;

	l_i_ImageSize = i_x_Image.m_x_ImageHeader.m_us_NbCol * i_x_Image.m_x_ImageHeader.m_us_NbRow;

	switch(i_x_Image.m_x_ImageHeader.m_uc_NbBitsPerPixel)
	{
		case 8:
			memcpy(l_puc_image8bits, i_x_Image.m_puc_Image, l_i_ImageSize);
			break;
		case 4:
			for (l_i_Cnt = 0; l_i_Cnt < l_i_ImageSize/2; l_i_Cnt++)
			{
				l_puc_image8bits[2*l_i_Cnt]   = (i_x_Image.m_puc_Image[l_i_Cnt] & 0xF0) + 0x08;
				l_puc_image8bits[2*l_i_Cnt+1] = ((i_x_Image.m_puc_Image[l_i_Cnt] & 0x0F)<<4) + 0x08;
			}
			break;
		case 2:
			for (l_i_Cnt = 0; l_i_Cnt < l_i_ImageSize/4; l_i_Cnt++)
			{
				l_puc_image8bits[4*l_i_Cnt]   = (i_x_Image.m_puc_Image[l_i_Cnt] & 0xC0);
				l_puc_image8bits[4*l_i_Cnt+1] = ((i_x_Image.m_puc_Image[l_i_Cnt] & 0x30)<<2);
				l_puc_image8bits[4*l_i_Cnt+2] = ((i_x_Image.m_puc_Image[l_i_Cnt] & 0x0C)<<4);
				l_puc_image8bits[4*l_i_Cnt+3] = ((i_x_Image.m_puc_Image[l_i_Cnt] & 0x03)<<6);
				CORRECT_LEVEL2(l_puc_image8bits[4*l_i_Cnt])
				CORRECT_LEVEL2(l_puc_image8bits[4*l_i_Cnt+1])
				CORRECT_LEVEL2(l_puc_image8bits[4*l_i_Cnt+2])
				CORRECT_LEVEL2(l_puc_image8bits[4*l_i_Cnt+3])
			}
			break;
		case 1:
			for (l_i_Cnt = 0; l_i_Cnt < l_i_ImageSize/8; l_i_Cnt++)
			{
				l_puc_image8bits[8*l_i_Cnt]   = (UC)(i_x_Image.m_puc_Image[l_i_Cnt] & 0x80);
				l_puc_image8bits[8*l_i_Cnt+1] = (UC)((i_x_Image.m_puc_Image[l_i_Cnt] & 0x40)<<1);
				l_puc_image8bits[8*l_i_Cnt+2] = (UC)((i_x_Image.m_puc_Image[l_i_Cnt] & 0x20)<<2);
				l_puc_image8bits[8*l_i_Cnt+3] = (UC)((i_x_Image.m_puc_Image[l_i_Cnt] & 0x10)<<3);
				l_puc_image8bits[8*l_i_Cnt+4] = (UC)((i_x_Image.m_puc_Image[l_i_Cnt] & 0x08)<<4);
				l_puc_image8bits[8*l_i_Cnt+5] = (UC)((i_x_Image.m_puc_Image[l_i_Cnt] & 0x04)<<5);
				l_puc_image8bits[8*l_i_Cnt+6] = (UC)((i_x_Image.m_puc_Image[l_i_Cnt] & 0x02)<<6);
				l_puc_image8bits[8*l_i_Cnt+7] = (UC)((i_x_Image.m_puc_Image[l_i_Cnt] & 0x01)<<7);
				CORRECT_LEVEL1(l_puc_image8bits[8*l_i_Cnt])
				CORRECT_LEVEL1(l_puc_image8bits[8*l_i_Cnt+1])
				CORRECT_LEVEL1(l_puc_image8bits[8*l_i_Cnt+2])
				CORRECT_LEVEL1(l_puc_image8bits[8*l_i_Cnt+3])
				CORRECT_LEVEL1(l_puc_image8bits[8*l_i_Cnt+4])
				CORRECT_LEVEL1(l_puc_image8bits[8*l_i_Cnt+5])
				CORRECT_LEVEL1(l_puc_image8bits[8*l_i_Cnt+6])
				CORRECT_LEVEL1(l_puc_image8bits[8*l_i_Cnt+7])
			}
			break;
	}

	if (i_ul_imageFilter & MORPHO_LINEAR_INTERPOLATION)
	{
		ZoomImageBilineaire(l_puc_image8bits, (PUC)m_pui_image8bits, 0,  
							i_x_Image.m_x_ImageHeader.m_us_NbCol,   i_x_Image.m_x_ImageHeader.m_us_NbRow, 1, 
							i_x_Image.m_x_ImageHeader.m_us_NbCol*2, i_x_Image.m_x_ImageHeader.m_us_NbRow*2, 2);
		l_i_Ret = MonochromeArrayToDIB(i_ul_ImageIndex, i_x_Image.m_x_ImageHeader.m_us_NbRow*2-2, i_x_Image.m_x_ImageHeader.m_us_NbCol*2-2, (PUC)m_pui_image8bits, i_p_Cdc);
	}
	else
		l_i_Ret = MonochromeArrayToDIB(i_ul_ImageIndex, i_x_Image.m_x_ImageHeader.m_us_NbRow, i_x_Image.m_x_ImageHeader.m_us_NbCol, (PUC)m_pui_image8bits, i_p_Cdc);

	if (l_i_Ret == MORPHO_OK)
		l_i_Ret = RefreshViewer(i_ul_ImageIndex, i_p_Rect, i_p_Cdc);

	if (l_puc_image != NULL)
		free(l_puc_image);

	return l_i_Ret;
}

C_MORPHO_Image::RefreshViewer(UL	i_ul_ImageIndex,
							  CRect &	i_p_Rect, 
							  CDC*	i_p_Cdc)
{
    HDC             l_phMemDC	=	NULL;
    BITMAP			l_Bitmap;

	CHECK_MAGIC

	if (m_ul_ImageNbIndex <= i_ul_ImageIndex)
		return MORPHOERR_BADPARAMETER;

	//Recuperation des informations sur le bitmap (BitmapInfoHeader) 
	//dans une variable BITMAP.	
     GetObject(m_pBitmap[i_ul_ImageIndex], sizeof(BITMAP), &l_Bitmap);
    
	//Creation d'un device context memoire compatible avec celui de la fenetre
    //indispensable pour travailler avec le bitmap
    l_phMemDC = CreateCompatibleDC(i_p_Cdc->m_hDC);
    
    //Maintenant on travaille sur le DC memoire
    //Remplacement du bitmap de la fenetre (Old )par celui lu dans le fichier
    SelectObject(l_phMemDC, m_pBitmap[i_ul_ImageIndex]);
    
    //Réalise la copie effective de l'image depuis le device context memoire
    //vers le device context ecran
	StretchBlt(i_p_Cdc->m_hDC, 0, 0, i_p_Rect.Width(), i_p_Rect.Height(), 
			   l_phMemDC, 0, 0, l_Bitmap.bmWidth, l_Bitmap.bmHeight, SRCCOPY);
    
    DeleteDC(l_phMemDC);

	return MORPHO_OK;
}

C_MORPHO_Image::MonochromeArrayToDIB(	UL	i_ul_ImageIndex,
										UL	i_ul_ImageRow,
										UL	i_ul_ImageCol,
										PUC i_puc_Image,
										CDC	*i_p_Cdc)
{
   	INT		i;	

	CHECK_MAGIC

	if (m_ul_ImageNbIndex <= i_ul_ImageIndex)
		return MORPHOERR_BADPARAMETER;

    DeleteObject(m_pBitmap[i_ul_ImageIndex]);

	//Info image (format bitmap)
    struct  
	{
         BITMAPINFOHEADER    bmiHeader;
         RGBQUAD             bmiColors[256];
	} l_InfoBitmap;

    //Init RGBQUAD Palette monochrome de 256 niveaux
    for(i = 0; i < 256; i++)
    {
		l_InfoBitmap.bmiColors[i].rgbBlue = i; 
        l_InfoBitmap.bmiColors[i].rgbGreen = i; 
        l_InfoBitmap.bmiColors[i].rgbRed = i; 
        l_InfoBitmap.bmiColors[i].rgbReserved = 0; 
    }

	//Init BITMAPINFOHEADER    
    l_InfoBitmap.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    l_InfoBitmap.bmiHeader.biWidth = i_ul_ImageCol;
    l_InfoBitmap.bmiHeader.biHeight = - (long)i_ul_ImageRow; /*the minus sign imply that */
												/*the bitmap is a top-down DIB and its origin is the upper left corner*/

    l_InfoBitmap.bmiHeader.biPlanes = 1;
    l_InfoBitmap.bmiHeader.biBitCount = 8;
    l_InfoBitmap.bmiHeader.biCompression = BI_RGB;
    l_InfoBitmap.bmiHeader.biSizeImage = 0;

    l_InfoBitmap.bmiHeader.biXPelsPerMeter = 0;
    l_InfoBitmap.bmiHeader.biYPelsPerMeter = 0;
    l_InfoBitmap.bmiHeader.biClrUsed = 0;
    l_InfoBitmap.bmiHeader.biClrImportant = 0;

	m_pBitmap[i_ul_ImageIndex] = CreateDIBSection(i_p_Cdc->m_hDC, (BITMAPINFO*)&l_InfoBitmap, DIB_RGB_COLORS, NULL, NULL, 0);
	SetDIBits(i_p_Cdc->m_hDC, m_pBitmap[i_ul_ImageIndex], 0, i_ul_ImageRow, i_puc_Image, (BITMAPINFO*)&l_InfoBitmap, DIB_RGB_COLORS); 

	return MORPHO_OK;
}

VOID
C_MORPHO_Image::ZoomImageBilineaire(PUC entree, PUC sortie, UC background, 
									L larg_entree, L haut_entree, L reso_entree, 
									L larg_sortie, L haut_sortie, L reso_sortie)
{
	long            i, j, k, l;
	double          u0, u1, v0, v1, r, r0, r1, x, y, dx, dy;
	double          zz = (double) reso_entree / (double) reso_sortie;
	double          x0 = (-(double) larg_sortie / (double) 2) * zz + (double) larg_entree / (double) 2;
	double          y0 = (-(double) haut_sortie / (double) 2) * zz + (double) haut_entree / (double) 2;
	unsigned char  *e = NULL;

	for (i = 0, y = y0; i < haut_sortie; i++, y += zz) {
		k = (long) floor(y);
		if (k < 0 || k > haut_entree - 2) {
			(void) memset(sortie, background, larg_sortie);
			sortie += larg_sortie;
		} else {
			dy = y - k;
			v0 = 1 - dy;
			v1 = dy;
			for (j = 0, x = x0; j < larg_sortie; j++, x += zz) {
				l = (long) floor(x);
				if (l < 0 || l > larg_entree - 2) {
					*sortie++ = background;
				} else {
					dx = x - l;
					u0 = 1 - dx;
					u1 = dx;
					e = entree + k * larg_entree + l;
					r0 = u0 * e[0] + u1 * e[1];
					e = e + larg_entree;
					r1 = u0 * e[0] + u1 * e[1];
					r = (long) (v0 * r0 + v1 * r1 + 0.5);
					r = (r < 0 ? 0 : r > 255 ? 255 : r);
					*sortie++ = (UC)r;
				}
			}
		}
	}
}


