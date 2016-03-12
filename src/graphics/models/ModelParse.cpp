#include "CommonPrecompiled.h"

#include "Model.h"
#include "FileHandle.h"

ModelJob::ModelJob(Model* model, ModelJob::ModelJobType type, const String& filename)
  : m_model(model)
  , m_type(type)
  , m_filename(filename)
{
  m_name = filename;
  switch(type)
  {
  case LOAD:
    m_name += " load";
    break;
  case STRIP:
    m_name += " strip";
    break;
  case NORMALIZE:
    m_name += " normalize";
  }
}

void ModelJob::Execute()
{
  if(m_type == ModelJobType::LOAD)
    m_model->ThreadOpen(m_filename);
  else if(m_type == ModelJob::STRIP)
    m_model->CreateTriangleStrips();
  else if(m_type == ModelJobType::NORMALIZE)
    m_model->SetVertexNormals();
}

void ModelJob::PostExecute()
{
  if(m_type == ModelJobType::STRIP)
  {
    m_model->ResetFaces();
    m_model->isLoaded = true;
    m_model->isLoaded.Update();
  }
}

void ReadToColon(Filesystem::FileHandle& file)
{
  c08 input;
  file.Read(input);
  while(input != ':')
  {
    file.Read(input);
  }
}

void Model::ThreadOpen(const String& filename)
{
  Filesystem::FileHandle file(filename);

  assertion(file.Open());

  std::string line;
  char input;

  ReadToColon(file);

  //read vertex count
  file.ReadIntegral(m_numVerts);
  m_vertices.resize(m_numVerts);

  //get to face count
  ReadToColon(file);
  file.ReadIntegral(m_numFaces);
  m_numIndicies = m_numFaces * 3;

  m_faces = new Face[m_numFaces];
  m_edges.reserve(m_numFaces * 6);

  file.Read(input);
  while(input == '#' || input == '\n' || input == '\r')
  {
    file.Read(input);
  }

  LOG(filename << " Loading " << m_numVerts << " verts...");
  file.MovePosition(-1);
  for(s32 i = 0; i < m_numVerts; ++i)
  {
    file.EatWhitespace();
    file.Read(input);
    assert(input == 'v');

    Vertex& currentV = m_vertices[i];

    file.ReadFloat(currentV.position.x);
    file.ReadFloat(currentV.position.y);
    file.ReadFloat(currentV.position.z);

    /*file >> currentV.UV.x;
    file >> currentV.UV.y;

    file >> currentV.normal.x;
    file >> currentV.normal.y;
    file >> currentV.normal.z;*/
  }
  file.ReadLine(line);
  file.ReadLine(line);

  LOG(filename << " Loading " << m_numFaces << " faces...");
  for(s32 j = 0; j < m_numFaces; ++j)
  {
    Face* face = &(m_faces[j]);
    u32 i1, i2, i3;

    file.EatWhitespace();
    file.Read(input);
    assert(input == 'f');

    file.ReadIntegral(i1);
    file.ReadIntegral(i2);
    file.ReadIntegral(i3);
    i1--;
    i2--;
    i3--;

    CreateTriangle(i1, i2, i3, face);
  }
  file.Close();

  SetBordersNext();
  
  Core::gCore->Pool(new ModelJob(this, ModelJob::STRIP, filename));
  Core::gCore->Pool(new ModelJob(this, ModelJob::NORMALIZE, filename));
}

void Model::CreateTriangle(u32 index1, u32 index2, u32 index3, Face* face)
{
  HalfEdge* edge1 = MakeEdge(index2, index1, face);
  HalfEdge* edge2 = MakeEdge(index3, index2, face);
  HalfEdge* edge3 = MakeEdge(index1, index3, face);
  edge1->SetNext(edge2);
  edge2->SetNext(edge3);
  edge3->SetNext(edge1);

  Vertex* vert = GetVertex(index1);
  if(vert->edge == nullptr)
  {
    vert->edge = edge1;
  }

  Vertex* vert2 = GetVertex(index2);
  if(vert2->edge == nullptr)
  {
    vert2->edge = edge2;
  }

  Vertex* vert3 = GetVertex(index3);
  if(vert3->edge == nullptr)
  {
    vert3->edge = edge3;
  }

  Math::Vector4 right, left;
  right = vert2->position - vert->position;
  left = vert3->position - vert->position;
  face->normal = right.Cross(left);
  face->normal = face->normal.Normalize();

  face->edges = edge1;
}

HalfEdge* Model::MakeEdge(u32 head, u32 tail, Face* face)
{
  BorderCont::iterator it = m_borders.begin();
  for(; it != m_borders.end(); ++it)
  {
    if((*it)->head == head && (*it)->twin->head == tail)
    {
      //if there is an edge pointing where we want
      (*it)->face = face;
      HalfEdge* ret = *it;

      m_borders.erase(it);
      return ret;
    }
  }
  HalfEdge& ret = *m_edges.emplace(m_edges.end(), HalfEdge(head, face, tail));
  HalfEdge& twin = *m_edges.emplace(m_edges.end(), HalfEdge(tail, nullptr, head));

  m_borders.push_back(&twin);
  ret.twin = &twin;
  twin.twin = &ret;
  return &ret;
}

u32 Model::CreateTriangleStrips(u32 startIndex)
{
  u32 n = 1, faceIndexCheck = 0;
  HalfEdge* ePrime;
  u32 facesVisited = 0;

  s32 indexBufferIndex = -1;

  StartTriangleStrip(GetVertex(startIndex)->edge, ePrime, indexBufferIndex);
  ++facesVisited;
  ++n;

  while(facesVisited < (u32)m_numFaces)
  {
    ePrime = ePrime->twin;

    if(ePrime->face->visited == true) //if the current face has been visited
    {
      for(; faceIndexCheck < (u32)m_numFaces; ++faceIndexCheck) //go through all faces (once for function)
      {
        if(m_faces[faceIndexCheck].visited != true) //unvisited face is now our face
        {
          StartTriangleStrip(m_faces[faceIndexCheck].edges, ePrime, indexBufferIndex);
          ++facesVisited;
          n = 0;
          break;
        }
      }
      continue;
    }//update face if visited

    m_indices[indexBufferIndex].push_back(ePrime->next->head);
    if(n % 2 == 0)
    {//even
      ePrime = ePrime->Previous(this);
    }
    else
    {//odd
      ePrime = ePrime->next;
    }
    ePrime->face->visited = true;
    ++n;
    ++facesVisited;
  }
  m_numIndicies = m_indices.size();
  return n;
}

void Model::StartTriangleStrip(HalfEdge* startEdge, HalfEdge*& ePrime, s32& indexBufferIndex)
{
  HalfEdge* e = startEdge;
  ePrime = e->next;
  ++indexBufferIndex;
  IndexCont i;
  m_indices.push_back(i);
  m_indices[indexBufferIndex].push_back(ePrime->next->head);
  m_indices[indexBufferIndex].push_back(e->head);
  m_indices[indexBufferIndex].push_back(ePrime->head);

  ePrime->face->visited = true;

  f32 r = Math::Random(0.1f, 1.0f);
  f32 g = Math::Random(0.1f, 1.0f);
  f32 b = Math::Random(0.1f, 1.0f);
  auto color = Math::LinearColor(r, g, b, 1);
  m_colors.push_back(color);
}
