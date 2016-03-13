/*
This is where all components should be defined

  define parameters:
    namespace, componentName, owningSystem, only one allowed per obj (placeholder for implementation)
*/
COMPONENT_DEF(Test, TestComponent, TestSystem, true)

COMPONENT_DEF(Physics, TransformComponent, PhysicsSystem, true)
COMPONENT_DEF(Physics, ColliderComponent, PhysicsSystem, true)

COMPONENT_DEF(GUI, ConsoleComponent, InterfaceSystem, true)

COMPONENT_DEF(Graphics, RenderableComponent, GraphicsSystem, false)
COMPONENT_DEF(Graphics, ModelComponent, GraphicsSystem, false)
COMPONENT_DEF(Graphics, UIComponent, GraphicsSystem, false)
