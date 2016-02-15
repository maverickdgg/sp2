#include "MeshBuilder.h"
#include <GL\glew.h>


/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{


	vector<Vertex> vertex_buffer_data;
	vector<GLuint> index_buffer_data;
	Vertex v;

	v.pos.Set(-lengthX, 0, 0);	v.col.Set(1, 0, 0);	v.normal.Set(); vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, 0, 0);	v.col.Set(1, 0, 0);	v.normal.Set(); vertex_buffer_data.push_back(v);
	v.pos.Set(0, -lengthY, 0);	v.col.Set(0, 1, 0);	v.normal.Set(); vertex_buffer_data.push_back(v);
	v.pos.Set(0, lengthY, 0);	v.col.Set(0, 1, 0); v.normal.Set();	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, -lengthZ);	v.col.Set(0, 0, 1); v.normal.Set();	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, lengthZ);	v.col.Set(0, 0, 1); v.normal.Set();	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = 6;
	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName,Color color, float lengthX, float lengthY)
{
	vector<Vertex> vertex_buffer_data;
	vector<GLuint> index_buffer_data;
	Vertex v;
	 
	v.pos.Set(-1.0, 1.0, 0.0); v.col = color; v.normal.Set(0, 0, 1); v.texCoord.Set(0, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(1.0, 1.0, 0.0); v.col = color;v.normal.Set(0,0,1);v.texCoord.Set(0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(-1.0, -1.0, 0.0); v.col = color; v.normal.Set(0, 0, 1); v.texCoord.Set(1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(1.0, -1.0, 0.0); v.col = color; v.normal.Set(0, 0, 1); v.texCoord.Set(1, 1); vertex_buffer_data.push_back(v);


	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName,  Color color)
{

	vector<Vertex> vertex_buffer_data;
	vector<GLuint> index_buffer_data;
	Vertex v;
	//left
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.col = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);	v.col = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.col = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.col = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.col = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);	v.col = color;	v.normal.Set(-1, 0, 0);	vertex_buffer_data.push_back(v);
	//back
	v.pos.Set(0.5f, 0.5f, -0.5f);	v.col = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.col = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);	v.col = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);	v.col = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);	v.col = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.col = color;	v.normal.Set(0, 0, -1);	vertex_buffer_data.push_back(v);
	//bottom
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.col = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.col = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);	v.col = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.col = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);	v.col = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);	v.col = color;	v.normal.Set(0, -1, 0);	vertex_buffer_data.push_back(v);
	//front
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.col = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.col = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.col = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.col = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);	v.col = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.col = color;	v.normal.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	//right
	v.pos.Set(0.5f, -0.5f, -0.5f);	v.col = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.col = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);	v.col = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.col = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);	v.col = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);	v.col = color;	v.normal.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	//top
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.col = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);	v.col = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);	v.col = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);	v.col = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);	v.col = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);	v.col = color;	v.normal.Set(0, 1, 0);	vertex_buffer_data.push_back(v);

	for (unsigned i = 0; i < 36; ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

float CircleX(float theta)
{
	return cos(Math::DegreeToRadian(theta));
}

float CircleZ(float theta)
{
	return sin(Math::DegreeToRadian(theta));
}

Mesh* MeshBuilder::GenerateCircle(const string& meshName, Color color, unsigned numSlices)
{
	vector<Vertex> vertex_buffer_data;
	vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerSlice = 360.0f / numSlices;
	for (unsigned i = 0; i < numSlices+1; ++i)
	{
		float theta = i*anglePerSlice;
		v.pos.Set(CircleX(theta), 0, CircleZ(theta));
		v.col = color;
		v.normal.Set(0,1,0);
		vertex_buffer_data.push_back(v);
	}
	v.pos.Set(0, 0, 0);
	v.col = color;
	v.normal.Set(0,1,0);
	vertex_buffer_data.push_back(v);
	
	for (int i = 0; i < numSlices+1; ++i)
	{
		index_buffer_data.push_back(i);
		index_buffer_data.push_back(numSlices+1);
	}
	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateRing(const string& meshName, Color color, float innerRadius, unsigned numSlices)
{
	vector<Vertex> vertex_buffer_data;
	vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerSlice = 360.0f / numSlices;
	for (unsigned i = 0; i < numSlices + 1; ++i)
	{
		float theta = i*anglePerSlice;
		v.pos.Set(CircleX(theta), 0, CircleZ(theta));
		v.col = color;
		v.normal.Set(0,1,0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(CircleX(theta)*innerRadius, 0*innerRadius, CircleZ(theta)*innerRadius);
		v.col = color;
		v.normal.Set(0,1,0);
		vertex_buffer_data.push_back(v);
	}

	for (int i = 0; i < numSlices + 1; i++)
	{
		index_buffer_data.push_back(2*i);
		index_buffer_data.push_back(2*i+1);
	}
	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

float SphereX(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi))*cos(Math::DegreeToRadian(theta));
}

float SphereY(float phi, float theta)
{
	return sin(Math::DegreeToRadian(phi));
}

float SphereZ(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi))*sin(Math::DegreeToRadian(theta));
}

Mesh* MeshBuilder::GenerateSphere(const string& meshName, Color color, unsigned numSlices, unsigned numStack)
{
	vector<Vertex> vertex_buffer_data;
	vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerStack = 180.0f / numStack; //180 because from -90 to 90
	float anglePerSlice = 360.0f / numSlices;
	for (unsigned stack = 0; stack < numStack+1; ++stack)
	{
		float phi = -90 + stack*anglePerStack; //each degree change per stack
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			float theta = slice*anglePerSlice;
			v.pos.Set(SphereX(phi, theta), SphereY(phi, theta), SphereZ(phi, theta));
			v.col = color;
			v.normal.Set(v.pos.x, v.pos.y, v.pos.z);//SphereX(phi, theta), SphereY(phi, theta), SphereZ(phi, theta) normal of the sphere is the same as the position
			vertex_buffer_data.push_back(v);
		}
	}



	for (unsigned stack = 0; stack < numStack + 1; ++stack)
	{
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			index_buffer_data.push_back(stack*(numSlices+1)+slice);
			index_buffer_data.push_back((stack+1)*(numSlices + 1) + slice);
		}
	}
	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateCylinder(const string& meshName, Color color, float topRadius,unsigned numSlice)
{
	vector<Vertex> vertex_buffer_data;
	vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerSlice = 360.0f / numSlice;
	for (unsigned i = 0; i < numSlice + 1; ++i)
	{
		float theta = i*anglePerSlice;
		v.pos.Set(CircleX(theta), -0.5, CircleZ(theta));
		v.col = color;
		v.normal.Set(CircleX(theta), 0, CircleZ(theta));
		vertex_buffer_data.push_back(v);

		v.pos.Set(CircleX(theta)*topRadius, 0.5, CircleZ(theta)*topRadius);
		v.col = color;
		v.normal.Set(CircleX(theta), 0, CircleZ(theta));
		vertex_buffer_data.push_back(v);
	}
	//btm lide
	v.pos.Set(0, -0.5, 0);
	v.col = color;
	v.normal.Set(0, -1.5, 0);
	vertex_buffer_data.push_back(v);
	//top lid
	v.pos.Set(0, 0.5, 0);
	v.col = color;
	v.normal.Set(0, 1.5, 0);
	vertex_buffer_data.push_back(v);

	//btm lid
	for (int slice = 0; slice < numSlice + 1; ++slice)
	{
		index_buffer_data.push_back(2 * (numSlice + 1));
		index_buffer_data.push_back(2 * slice);
	}
	//center
	for (int slice = 0; slice < numSlice+1; ++slice)
	{
		index_buffer_data.push_back(2 * slice);
		index_buffer_data.push_back(2 * (slice)+1);
	}
		// top lid
	for (int slice = 0; slice < numSlice + 1; ++slice)
	{
		index_buffer_data.push_back(2 * slice+1);
		index_buffer_data.push_back(2 * (numSlice + 1) + 1);
	}
	

	
	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateTorus(const string& meshName, Color color, float innerRadius, float outerRadius, unsigned numStack, unsigned numSlice)
{
	vector<Vertex> vertex_buffer_data;
	vector<GLuint> index_buffer_data;
	Vertex v;
	float degreePerStack = 360.0f / numStack;
	float degreePerSlice = 360.0f / numSlice;
	float x1, z1; //y1 will always be 0
	float x2, y2, z2;
	for (unsigned stack = 0; stack < numStack + 1; ++stack)
	{
		for (unsigned slice = 0; slice < numSlice + 1; ++slice)
		{
			z1 = outerRadius*cos(Math::DegreeToRadian(stack*degreePerStack));
			x1 = outerRadius*sin(Math::DegreeToRadian(stack*degreePerStack));
			z2 = (outerRadius + innerRadius*cos(Math::DegreeToRadian(slice*degreePerSlice)))*cos(Math::DegreeToRadian(stack*degreePerStack));
			y2 = innerRadius*sin(Math::DegreeToRadian(slice*degreePerSlice));
			x2 = (outerRadius + innerRadius*cos(Math::DegreeToRadian(slice*degreePerSlice)))*sin(Math::DegreeToRadian(stack*degreePerStack));
			v.pos.Set(x2, y2, z2);
			v.col = color;
			v.normal.Set(x2 - x1, y2, z2 - z1);
			vertex_buffer_data.push_back(v);
		}
	}
	for (unsigned stack = 0; stack < numStack; stack++) {
		for (unsigned slice = 0; slice < numSlice + 1; slice++) {
			index_buffer_data.push_back((numSlice + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
		}
	}
	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateHemiSphere(const string& meshName, Color color, unsigned numSlices, unsigned numStack )
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerStack = 180.f / numStack;
	float anglePerSlice = 360.f / numSlices;

	for (unsigned stack = 0; stack < numStack + 1; ++stack)
	{
		float phi = stack * anglePerStack;
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			float theta = slice * anglePerSlice;
			v.pos.Set(SphereX(phi, theta), SphereY(phi, theta), SphereZ(phi, theta));
			v.col = color;
			v.normal.Set(SphereX(phi, theta), SphereY(phi, theta), SphereZ(phi, theta));
			vertex_buffer_data.push_back(v);

		}
	}


	for (unsigned slice = 0; slice < numSlices + 1; ++slice)
	{
		float theta = 180 - anglePerSlice * slice;
		v.pos.Set(CircleX(theta), 0, CircleZ(theta));
		v.col = color;
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);
	}

	v.pos.Set(0, 0, 0);
	v.col = color;
	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);

	for (unsigned stack = 0; stack < numStack; ++stack)
	{
		for (unsigned slice = 0; slice < numSlices + 1; ++slice)
		{
			index_buffer_data.push_back(stack * (numSlices + 1) + slice);
			index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);
		}
	}


	for (unsigned slice = (numSlices + 1) * (numStack + 1); slice < (numSlices + 1) * (numStack + 1) + (numSlices + 1) * 2; ++slice)
	{
		index_buffer_data.push_back(slice);
		index_buffer_data.push_back((numSlices + 1) * (numStack + 1) + (numSlices + 1));
	}


	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateCircleLine(const string& meshName, Color color, unsigned numSlices)
{
	vector<Vertex> vertex_buffer_data;
	vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerSlice = 360.0f / numSlices;
	for (unsigned i = 0; i < numSlices + 1; ++i)
	{
		float theta = i*anglePerSlice;
		v.pos.Set(CircleX(theta), 0, CircleZ(theta));
		v.col = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
	}


	for (int i = 0; i < numSlices + 1; ++i)
	{
		if (i != numSlices)
		{
			index_buffer_data.push_back(i);
			index_buffer_data.push_back(i + 1);
		}
		else
		{
			index_buffer_data.push_back(i);
		}
	}
	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

Mesh* MeshBuilder::GenerateHalfCircleLine(const string& meshName, Color color, unsigned numSlices)
{
	vector<Vertex> vertex_buffer_data;
	vector<GLuint> index_buffer_data;
	Vertex v;

	float anglePerSlice = 180.0f / numSlices;
	for (unsigned i = 0; i < numSlices + 1; ++i)
	{
		float theta = i*anglePerSlice;
		v.pos.Set(CircleX(theta), 0, CircleZ(theta));
		v.col = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
	}


	for (int i = 0; i < numSlices + 1; ++i)
	{
		if (i != numSlices)
		{
			index_buffer_data.push_back(i);
			index_buffer_data.push_back(i + 1);
		}
		else
		{
			index_buffer_data.push_back(i);
		}
	}
	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

Mesh* MeshBuilder::GenerateOBJ(const std::string &meshName, const std::string &file_path)
{
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
	if (!success)
		return NULL;
	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;

}

Mesh* MeshBuilder::GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol)
{
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	Vertex v;

	float width = 1.f / numCol;
	float height = 1.f / numRow;
	int offset = 0;
	for (unsigned j = 0; j < numRow; ++j)
	{
		for (unsigned i = 0; i < numCol; ++i)
		{
			v.pos.Set(-0.5f, -0.5f, 0); v.texCoord.Set(i*width, 1.f - (j + 1)*height); v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v);
			v.pos.Set(0.5f, -0.5f, 0); v.texCoord.Set((i + 1)*width, 1.f - (j + 1)*height); v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v);
			v.pos.Set(0.5f, 0.5f, 0); v.texCoord.Set((i + 1)*width, 1.f - j *height); v.normal.Set(0, 0, 1);  vertex_buffer_data.push_back(v);
			v.pos.Set(-0.5f, 0.5f, 0); v.texCoord.Set(i*width, 1.f - j *height); v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v);

			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 1);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 3);
			offset += 4;
		}
	}


	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}