#include "CommonPrecompiled.h"
#include "GraphicsSystem.h"
#include "GLClass.h"
#include "Shader.h"

#include "RenderableComponent.h"

#include "Model.h"
#include "ModelComponent.h"

namespace Graphics
{
  GraphicsSystem::GraphicsSystem()
   : m_width(1024), m_height(768), m_fullscreen(false)
   , m_dt(0.f)
  {
    m_api = new GLClass();
  }

  GraphicsSystem::~GraphicsSystem()
  {}

  bool GraphicsSystem::Initialize(ArgParser& args)
  {
    m_front = 1.f;
    if(args.Has("-screenWidth"))
    {
      m_width = args.Get("-w")->val.iVal;
    }

    if(args.Has("-screenHeight"))
    {
      m_height = args.Get("-h")->val.iVal;
    }

    if(args.Has("-f"))
    {
      m_fullscreen = true;
    }

    if(!m_api->Initialize())
      return false;

    if(!m_api->MakeWindow(m_width, m_height, m_fullscreen))
    {
      m_api->Teardown();
      return false;
    }

    m_defaultShader = new Shader("assets/shaders/Default.vs",
                                 "assets/shaders/Default.fs");
    m_defaultShader->Link();

    m_desiredFR = 1.f / 60.f;
    return true;
  }

  void GraphicsSystem::Destroy()
  {
    delete m_defaultShader;
    m_api->Teardown();
    delete m_api;
  }

  void addObj(bool& loaded, Model*& m)
  {
    auto obj = Factory::MakeObject();
    obj->AddComponent(Comp::TransformComponent);
    auto comp = obj->AddComponent(Comp::ModelComponent);
    RECAST(ModelComponent*, comp)->SetModel(m);
  }

  void GraphicsSystem::Test()
  {
    //String filename("assets/models/Cube.obj");
    String filename("assets/models/horse_lowres_cleaned.obj");
    //String filename("assets/models/happy_lowres_cleaned.obj");
    //String filename("assets/models/dragon_lowres_cleaned.obj");
    Model* m = new Model();
    m->Open(filename);
    m->isLoaded.SetUpdateFunc(addObj, m);
  }

  void GraphicsSystem::RegisterComponent(Component* comp)
  {
    System::RegisterComponent(comp);
    RenderableComponent* render = RECAST(RenderableComponent*, comp);
    if(render)
    {
      m_renderables.push_back(render);
    }
  }
  
  void GraphicsSystem::UnregisterComponent(Component* comp)
  {
    System::UnregisterComponent(comp);
    RenderableComponent* render = RECAST(RenderableComponent*, comp);
    if(render)
    {
      m_renderables.remove(render);
    }
  }

  void GraphicsSystem::HandleMessage(Message *m)
  {
    s32 button;
    s32 action;
    double x;
    double y;

    m->Reset();

    switch(m->GetType())
    {
      case Message::MSG_KEY:
        button = *m->GetFormatedData<s32>();
        action = *m->GetFormatedData<s32>();

        TODO("Universalize");
        if(button == GLFW_KEY_ESCAPE)
        {
          Core::gCore->Quit();
        }
        break;

      case Message::MSG_MOUSE:
        x = *m->GetFormatedData<double>();
        y = *m->GetFormatedData<double>();
        break;

      case Message::MSG_MOUSE_BUTTON:
        button = *m->GetFormatedData<s32>();
        action = *m->GetFormatedData<s32>();
        break;

      case Message::MSG_SCROLL:
        x = *m->GetFormatedData<double>();
        y = *m->GetFormatedData<double>();
        break;

      case Message::MSG_WINDOW:
        m_width = *m->GetFormatedData<s32>();
        m_height= *m->GetFormatedData<s32>();
        break;
    }
    m_api->Handle(m);
  }
  
  void GraphicsSystem::Tick(f32 dt)
  {
    m_dt += dt;
    if(m_dt < m_desiredFR)
    {
      return;
    }
    m_dt = 0.f;

    float sy = 0.2f * m_front;
    float sx = sy * m_width / m_height;
    f32 fov = Math::PI / 4.f;
    f32 aspect = (f32)m_width / (f32)m_height;
    Math::Matrix proj = Math::PerspectiveMatrix::Build(fov, aspect, m_front, 10000.0f);

    Math::Matrix view = m_camera.MakeView();

    m_defaultShader->Bind(proj, view);
    m_api->StartFrame();

    for(auto r : m_renderables)
    {
      r->Draw(m_defaultShader->GetID());
    }
    
    m_api->EndFrame();
    m_defaultShader->UnBind();
  }
}
