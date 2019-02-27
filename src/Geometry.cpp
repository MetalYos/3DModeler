#include "Geometry.h"

Geometry::~Geometry()
{

}

void Geometry::AddVertex(VertexData* vertex)
{
    vertex->Half = nullptr;
    Vertices.push_back(vertex);
}

void Geometry::AddEdge(VertexData* from, VertexData* to)
{

}