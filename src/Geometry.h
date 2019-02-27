#pragma once

#include "pch.h"

struct VertexData;
struct EdgeData;
struct PolygonData;

struct HalfData
{
    HalfData* Next;
    HalfData* Previous;
    HalfData* Pair;

    VertexData* Origin;
    PolygonData* Left;
};

struct VertexData
{
    Vec4 Position;
    Vec4 Normal;
    Vec4 TexCoords;

    HalfData* Half;
};

struct PolygonData
{
    Vec4 Center;
    Vec4 Normal;

    HalfData* Half;
};

class Geometry
{
public:
    Geometry() {}
    ~Geometry();

    void AddVertex(VertexData* vertex);
    void AddEdge(VertexData* from, VertexData* to);

public:
    std::vector<HalfData*> HalfEdges;
    std::vector<VertexData*> Vertices;
    std::vector<PolygonData*> Polygons;
};