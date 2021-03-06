/*
* Tilengine - The 2D retro graphics engine with raster effects
* Copyright (C) 2015-2018 Marc Palacios Domenech <mailto:megamarc@hotmail.com>
* All rights reserved
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Library General Public License for more details.
*
* You should have received a copy of the GNU Library General Public
* License along with this library. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _LAYER_H
#define _LAYER_H

#include "Tilengine.h"
#include "Draw.h"
#include "Blitters.h"
#include "Math2D.h"

/* tipo de capa */
typedef enum
{
	LAYER_NORMAL,
	LAYER_AFFINE,
}
layer_t;

/* capa */
typedef struct Layer
{
	/* configuraci�n */
	layer_t		type;		/* tipo de capa */
	TLN_Tileset	tileset;	/* puntero al tileset */
	TLN_Tilemap	tilemap;	/* puntero al array de memoria con el mapa de tiles */
	TLN_Palette	palette;	/* puntero a la paleta */
	TLN_Bitmap  bitmap;		/* puntero al bitmap (modo bitmap) */
	int			width;		/* anchura total en p�xeles */
	int			height;		/* altura total en p�xeles */
	bool		ok;
	bool		affine;
	ScanDrawPtr draw;
	ScanBlitPtr blitters[2];
	Matrix3		transform;
	int*		column;		/* offset de columna (opcional) */
	fix_t		xfactor;
	fix_t		dx;
	fix_t		dy;
	uint8_t*	blend;		/* puntero a tabla de transparencia (NULL = no hay) */
	TLN_PixelMap* pixel_map;	/* puntero a tabla de pixel map (NULL = no hay) */
	draw_t		mode;
	
	/* */
	int			hstart;		/* offset de inicio horizontal */
	int			vstart;		/* offset de inicio vertical */

	/* clip */
	struct
	{
		int x1, y1, x2, y2;
	}
	clip;

	/* mosaico */
	struct
	{
		int w,h;			/* tama�o del pixel */
		uint8_t* buffer;	/* linea temporal */
	}
	mosaic;
}
Layer;

#endif