/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior 
written consent of DigiPen Institute of Technology is prohibited.
Purpose: Declaration of ModelTypes Classes
Language: C++
Platform: Windows
Project: harrison.beachey_CS350_1
Author: Harrison Beachey 50007511
Creation date: 9.8.13
- End Header --------------------------------------------------------*/
#pragma once

namespace Graphics
{
  class Model;

  struct Vertex;
  class HalfEdge;
  struct Face;

  typedef std::vector<u32>      IndexCont;
  typedef std::vector<Vertex>   VertexCont;
  typedef std::vector<HalfEdge> EdgeCont;
  typedef std::list<HalfEdge*>  BorderCont;

  struct Vertex
  {
    Vertex();
    Math::Vector4 position;
    Math::Vector4 normal;
    Math::Vector2 UV;
    HalfEdge* edge;

    void AverageFaceNormal(Face* f);
  };

  class HalfEdge
  {
  public:
    HalfEdge(u32 head, Face* f, u32 tail);
    void SetNext(HalfEdge* next);

    //IsBorderEdge is part of the model class, as all borders are stored there

    //Needs the model its part of for the border case
    HalfEdge* Previous(Model* m);

    //the vertex pointed to
    u32 head;
    Face* face;

    HalfEdge* twin;
    HalfEdge* next;
  };

  struct Face
  {
    Face();

    HalfEdge* edges;
    bool visited;

    Math::Vector4 normal;
  };
}
