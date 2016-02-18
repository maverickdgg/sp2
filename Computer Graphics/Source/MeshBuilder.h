#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include <vector>
#include "Vertex.h"
#include <string>
#include <MyMath.h>
#include "LoadOBJ.h"
#include <fstream>

using std::vector;
using std::string;
/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName,Color color, float lengthX, float lengthY);
	static Mesh* GenerateCube(const std::string &meshName, Color color);
	static Mesh* GenerateCircle(const string& meshName, Color color, unsigned numSlices =36);
	static Mesh* GenerateRing(const string& meshName, Color color, float innerRadius, unsigned numSlices);
	static Mesh* GenerateSphere(const string& meshName, Color color, unsigned numSlices= 36 ,unsigned numStack = 36 );
	static Mesh* GenerateCylinder(const string& meshName, Color color, float topRadius,unsigned numSlice=36);
	static Mesh* GenerateTorus(const string& meshName, Color color, float innerRadius, float outerRadius, unsigned numStack=36, unsigned numSlice=36);
	static Mesh* GenerateHemiSphere(const string& meshName, Color color, unsigned numSlices = 36, unsigned numStack = 36);
	static Mesh* GenerateCircleLine(const string& meshName, Color color, unsigned numSlices = 36);
	static Mesh* GenerateHalfCircleLine(const string& meshName, Color color, unsigned numSlices = 36);
	static Mesh* GenerateOBJ(const std::string &meshName, const std::string &file_path);
	static Mesh* MeshBuilder::GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol);
};
#endif