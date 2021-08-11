/*
Copyright (C) 2019, NVIDIA CORPORATION. All rights reserved.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef __MATERIAL_H_
#define __MATERIAL_H_

#include "shared/shared.h"
#include "refresh/refresh.h"

#define MAX_PBR_MATERIALS 4096

typedef struct image_s image_t;

//
// PBR material
//

typedef struct pbr_material_s {
	char name[MAX_QPATH];
	char filename_base[MAX_QPATH];
	char filename_normals[MAX_QPATH];
	char filename_emissive[MAX_QPATH];
	image_t * image_base;
	image_t * image_normals;
	image_t * image_emissive;
	float bump_scale;
	float rough_override;
	float metalness_factor;
	float emissive_factor;
	uint32_t flags;
	int registration_sequence;
	int num_frames;
	int next_frame;
	int enable_light_styles;
	imageflags_t image_flags;
	imagetype_t image_type;
} pbr_material_t;

extern pbr_material_t r_materials[MAX_PBR_MATERIALS];

// clears the material table
void MAT_Init(void);

// resets all previously loaded wall materials and loads a map-specific material file
void MAT_ChangeMap(const char* map_name);

// finds or loads a material by name, which must have no extension
// all available textures will be initialized in the returned material
pbr_material_t* MAT_Find(const char* name, imagetype_t type, imageflags_t flags);

// clone a material for use on a surface with LIGHT flag
pbr_material_t *MAT_CloneForRadiance(pbr_material_t *mat, int radiance);

// registration sequence: update registration sequence of images used by the material
void MAT_UpdateRegistration(pbr_material_t * mat);

// returns a material by index, if it's valid - NULL otherwise
pbr_material_t* MAT_ForIndex(int index);

// update material when a skin is applied
pbr_material_t* MAT_ForSkin(image_t * image_base);

// sets a material attribute by name
qerror_t MAT_SetAttribute(pbr_material_t * mat, char const * attribute, char const * value);

// reset materials textures (call before loading a level)
qerror_t MAT_FreeUnused(void);

// prints material properties on console
void MAT_Print(pbr_material_t const * mat);

// replaces the material kind field with the given value
uint32_t MAT_SetKind(uint32_t material, uint32_t kind);

// tests if the material is of a given kind
qboolean MAT_IsKind(uint32_t material, uint32_t kind);

#endif // __MATERIAL_H_
