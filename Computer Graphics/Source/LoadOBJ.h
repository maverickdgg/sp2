/******************************************************************************/
/*!
\file	LoadOBJ.h
\author Lee Jian Lin
\par	Email: 150580X@mymail.nyp.edu.sg
\par	Admin Number: 150580X
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9755 2038
\brief
Loading of OBJ files
*/
/******************************************************************************/
#ifndef LOAD_OBJ_H
#define LOAD_OBJ_H

#include <vector>
#include "Vertex.h"
#include "Vector3.h"

bool LoadOBJ(
	const char *file_path,
	std::vector<Position> & out_vertices,
	std::vector<TexCoord> & out_uvs,
	std::vector<Vector3> & out_normals
	);

void IndexVBO(
	std::vector<Position> & in_vertices,
	std::vector<TexCoord> & in_uvs,
	std::vector<Vector3> & in_normals,

	std::vector<unsigned> & out_indices,
	std::vector<Vertex> & out_vertices
	);
#endif