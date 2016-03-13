/*
*  FILE          InterfaceCommon.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for common interface includes.
*/
#pragma once

#define INTERFACE_IMGUI

#if defined(INTERFACE_IMGUI)

#include <imgui.h>

#endif

namespace GUI
{
  enum CommonInterfaceDefinition
  {
    InterfaceDisable = 0,
    InterfaceReadWrite,
    InterfaceReadOnly,

    InterfaceCommonTotal,
  };

  enum IntegralInterfaceDefinition
  {
    InputWidget = InterfaceCommonTotal,
    SliderWidget,
    DraggableWidget,
    VerticalSliderWidget,

    RangeWidget,
    AngleWidget,

    DisableRangeLimits,
    DisableColorAlpha,

    EnableFullNumericVectorInput,

    MaxIntegralAttributes = 32
  };

  enum TextureInterfaceDefinition
  {
    ConstTexture = InterfaceCommonTotal,

    NormalMap,
    AlphaMask,
    EnvironmentMap,

    ParticleSprite,

    MaxTextureAttributes = 32
  };

  enum EnumInterfaceDefinition
  {
    MaxEnumAttributes = 32
  };

  enum ClassInterfaceDefinition
  {
    MaxClassAttributes = 32
  };
}