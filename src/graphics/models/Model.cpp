#include "CommonPrecompiled.h"
#include "Model.h"
#include "Shader.h"

Model::Model()
  : m_vbo(0)
  , m_needsBuffers(true)
{
  isLoaded.SetNoUpdate(false);
}

Model::~Model()
{}

void Model::Open(const String& filename)
{
  Core::gCore->Pool(new ModelJob(this, ModelJob::LOAD, filename));
}

void Model::Draw(u32 shader)
{
  assertion(isLoaded);
  if(m_needsBuffers)
    CreateBuffers();

  s32 loc = glGetUniformLocation(shader, "stripColor");

  glBindVertexArray(m_vao);
  for(u32 i = 0; i < m_vaos.size(); ++i)
  {
    glUniform4fv(loc, 1, m_colors[i].v);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vaos[i]);
    glDrawElements(GL_TRIANGLE_STRIP, m_indices[i].size(), GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  glBindVertexArray(0);
  CHECK_GL_ERR;
}

bool Model::IsBorderEdge(HalfEdge* edge)
{
  if(m_borders.size() == 0)
    return false;

  for(HalfEdge* e : m_borders)
  {
    if(e == edge)
    {
      return true;
    }
  }
  return false;
}

HalfEdge* Model::GetPreviousBorder(HalfEdge* edge)
{
  for(HalfEdge* e : m_borders)
  {
    if(e->next == edge)
    {
      return e;
    }
  }
  return nullptr;
}

s32 Model::GetVertexCount()
{
  return m_numVerts;
}

Vertex *Model::GetVertex(u32 index)
{
  if(index >= (u32)m_numVerts)
  {
    return nullptr;
  }

  return &(m_vertices[index]);
}

s32 Model::GetNumFaces() const
{
  return m_numFaces;
}

Face* Model::GetFace(u32 index)
{
  if(index >= m_numFaces)
    return nullptr;
  return &m_faces[index];
}

VertexCont::const_iterator Model::VertexBegin() const
{
  return m_vertices.cbegin();
}

VertexCont::const_iterator Model::VertexEnd() const
{
  return m_vertices.cend();
}

void Model::OneRingVertex(Vertex* center, void (*function)(Vertex* v))
{
  HalfEdge* stop = center->edge;
  HalfEdge* h = stop;
  do
  {
    function(GetVertex(h->head));
    h = h->Previous(this)->twin;
  } while(h != stop);
}

void Model::OneRingFace(Vertex* center, void (*function)(Face* v))
{
  HalfEdge* stop = center->edge;
  HalfEdge* h = stop;
  do
  {
    function(h->face);
    h = h->Previous(this)->twin;
  } while(h != stop);
}

void Model::OneRingVNormals(Vertex* center)
{
  HalfEdge* stop = center->edge;
  HalfEdge* h = stop;
  do
  {
    center->AverageFaceNormal(h->face);
    h = h->Previous(this)->twin;
  } while(h != stop);
}

/////////////
//PRIVATE
////////////
void Model::ResetFaces()
{
  for(s32 i = 0; i < m_numFaces; ++i)
  {
    m_faces[i].visited = false;
  }
}

void Model::SetVertexNormals()
{
  for(s32 i = 0; i < m_numVerts; ++i)
  {
    OneRingVNormals(GetVertex(i));
  }
}

void Model::SetBordersNext()
{
  if(m_borders.size() == 0)
    return;
  for(HalfEdge* edge : m_borders)
  {
    for(HalfEdge* next : m_borders)
    {
      if(next == edge)
        continue;
      else if(edge->head == next->twin->head)
      {
        edge->next = next;
        break;
      }
    }
  }
}

void Model::CreateBuffers()
{
  //create vertex buffer
  Math::Vector4* vertArray = new Math::Vector4[m_numVerts];
  for(s32 i = 0; i < m_numVerts; ++i)
  {
    vertArray[i] = m_vertices[i].position;
  }

  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);

  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Math::Vector4) * m_numVerts,
               vertArray, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  //create index buffers
  for(u32 i = 0; i < m_indices.size(); ++i)
  {
    u32 buf = 0;
    glGenBuffers(1, &buf);
    m_vaos.push_back(buf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vaos[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices[i].size() * sizeof(u32), 
      &m_indices[i][0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  glBindVertexArray(0);
  delete[] vertArray;
  m_needsBuffers = false;
}
