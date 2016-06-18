/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior 
written consent of DigiPen Institute of Technology is prohibited.
Purpose: Implementation of Model Types
Language: C++
Platform: Windows
Project: harrison.beachey_CS350_1
Author: Harrison Beachey 50007511
Creation date: 9.8.13
- End Header --------------------------------------------------------*/
#include "CommonPrecompiled.h"
#include "ModelTypes.h"
#include "Model.h"

namespace Graphics
{
  Vertex::Vertex() : position(0.0f, 0.0f, 0.0f, 1.0f), normal(0.0f, 0.0f, 0.0f, 0.0f),
    UV(0.0f, 0.0f), edge(nullptr)
  {}

  void Vertex::AverageFaceNormal(Face* face)
  {
    if(face == nullptr)
      return;
    f32 len = normal.Length();
    normal += face->normal;
    if(len > 0.001)
    {
      normal /= 2.0f;
    }
  }

  //////
  //Half Edge
  /////
  HalfEdge::HalfEdge(u32 h, Face* f, u32 tail) :
    head(h), face(f), next(nullptr), twin(nullptr)
  {}

  void HalfEdge::SetNext(HalfEdge* n)
  {
    next = n;
  }

  HalfEdge* HalfEdge::Previous(Model* m)
  {
    if(m->IsBorderEdge(this))
    {
      return m->GetPreviousBorder(this);
    }
    return next->next;
  }

  //////
  //Faces
  //////
  Face::Face() : visited(false), normal(0.0f, 0.0f, 0.0f, 0.0f)
  {}
}
