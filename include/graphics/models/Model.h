#pragma once

#include "ModelTypes.h"

class ModelJob : public ThreadJob
{
public:
  enum ModelJobType
  {
    LOAD,
    STRIP,
    NORMALIZE,
  };
  ModelJob(Model* model, ModelJobType t = LOAD, const String& filename = "");
  virtual void Execute() override;
  virtual void PostExecute() override;
  
private:
  String m_filename;
  ModelJobType m_type;
  Model* m_model;
};

class Shader;
class Model
{
  friend class ModelJob;
public:
  Model();
  ~Model();

  void Open(const String& filename);
  
  bool IsBorderEdge(HalfEdge* edge);
  HalfEdge* GetPreviousBorder(HalfEdge* edge);

  s32 GetVertexCount();
  Vertex* GetVertex(u32 index);

  s32   GetNumFaces() const;
  Face* GetFace(u32 index);

  VertexCont::const_iterator VertexBegin() const;
  VertexCont::const_iterator VertexEnd() const;

  void OneRingFace(Vertex* center, void (*function)(Face* f));
  void OneRingVertex(Vertex* center, void (*function)(Vertex* v));

  void OneRingVNormals(Vertex* center);

  void Draw(u32 shaderID);

  UpdateType<bool, Model*> isLoaded;
private:
  //utils
  void ThreadOpen(const String& filename);
  void CreateTriangle(u32 index1, u32 index2, u32 index3, Face* face);
  HalfEdge* MakeEdge(u32 head, u32 tail, Face* face);

  u32 CreateTriangleStrips(u32 startIndex = 0);
  void StartTriangleStrip(HalfEdge* startIndex, HalfEdge*& ePrime,
                          s32& indexBufferIndex);
  void ResetFaces(void);
  void SetVertexNormals(void);
  void SetBordersNext();

  void CreateBuffers();

  u32 m_vbo;
  u32 m_vao;
  std::vector<u32> m_vaos;
  std::vector<Math::LinearColor> m_colors;

  s32 m_numVerts;
  s32 m_numFaces;
  s32 m_numIndicies;

  Face* m_faces;
  //todo: dont use stl
  EdgeCont   m_edges;
  BorderCont m_borders;
  VertexCont m_vertices;
  std::vector<IndexCont>  m_indices;

  bool m_needsBuffers;

  Shader* m_shader;
};

