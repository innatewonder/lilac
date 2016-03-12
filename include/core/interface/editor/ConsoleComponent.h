/*
*  FILE          ConsoleComponent.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for console interface features.
*/
#pragma once
#include "WindowComponent.h"

namespace GUI
{
  class ConsoleComponent : public WindowComponent
  {
    public:
      ConsoleComponent();

      virtual void Initialize(void);
      virtual void Display(void);
      virtual void Destroy(void);
  };
}