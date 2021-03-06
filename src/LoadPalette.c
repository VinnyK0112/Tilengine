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

/*!
 * \file
 * \brief Adobe Color Table (.act) loader
 */

#include <stdio.h>
#include <string.h>
#include "Tilengine.h"
#include "LoadFile.h"

#define SWAP(w) ((w)&0xFF)<<8 | ((w)>>8)

#define ACT_ENTRIES		256
#define ACT_SIZE		(ACT_ENTRIES*3 + sizeof(trailing))

/* optional trailing bytes in an ACT file */
struct
{
	short entries;		/* number of entries 1-255 */
	short transparent;	/* index of transparent color */
}
trailing;

/*!
 * \brief
 * Loads a palette from a standard .act file
 * 
 * \param filename
 * ACT file containing the palette to load
 * 
 * \returns
 * A reference to the newly loaded palette, or NULL if error
 * 
 * \remarks
 * Palettes are also automatically created when loading tilesets and spritesets.
 * Use the functions TLN_GetTilesetPalette() and TLN_GetSpritesetPalette() to retrieve them.
 * 
 * \see
 * TLN_GetTilesetPalette(), TLN_GetSpritesetPalette()
 */
TLN_Palette TLN_LoadPalette (const char* filename)
{
	FILE *pf;
	TLN_Palette palette = NULL;
	int size;
	int c;

	/* open file */
	pf = FileOpen (filename);
	if (!pf)
	{
		TLN_SetLastError (TLN_ERR_FILE_NOT_FOUND);
		return NULL;
	}

	/* check size */
	fseek (pf, 0, SEEK_END);
	size = ftell (pf);

	/* load trailing and get number of entries */
	if (size == ACT_SIZE)
	{
		fseek (pf, - (int)sizeof(trailing), SEEK_END);
		fread (&trailing, sizeof(trailing), 1, pf);
		trailing.entries = SWAP(trailing.entries);
		trailing.transparent = SWAP(trailing.transparent);
	}
	else
		trailing.entries = size/3;

	/* create palette and load from file */
	palette = TLN_CreatePalette (trailing.entries);
	fseek (pf, 0, SEEK_SET);
	for (c=0; c<trailing.entries; c++)
	{
		uint8_t src[3];
		fread (src, sizeof(src), 1, pf);
		TLN_SetPaletteColor (palette, c, src[0], src[1], src[2]);
	}

	fclose (pf);
	TLN_SetLastError (TLN_ERR_OK);
	return palette;
}
