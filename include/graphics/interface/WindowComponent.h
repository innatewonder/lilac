/*
*  FILE          WindowComponent.h
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for global wrapper functions used to define a window context.
*/
#pragma once

namespace GUI
{
  enum WindowAlignment
  {
    CenterAlignment,

    LeftAlignment,
    RightAlignment,

    BottomAlignment,
    TopAlignment,
  };

  class WindowComponent : public Component
  {
    public:
      WindowComponent();

      void Begin(void);
      void Setup(void);
      void End(void);

      virtual void Display(void) = 0;
      virtual void Destroy(void) = 0;

      // -- Window Property Interface --
      INLINE std::string GetWindowTitle(void) const;
      INLINE Math::Vector2 GetInitialWindowSize(void) const;
      INLINE Math::Vector2 GetInitialWindowPosition(void) const;
      INLINE f32 GetWindowAlpha(void) const;

      INLINE void SetWindowTitle(const std::string& name);
      INLINE void SetWindowSize(const Math::Vector2& size);
      INLINE void SetWindowPosition(const Math::Vector2& position);
      INLINE void SetWindowAlpha(f32 a);
      INLINE void SetWindowCollapsed(bool collapsed);
      INLINE void SetWindowFocused(void);
     
      INLINE void Set(s32 argument, bool active = true);
      INLINE void Enable(s32 argument);
      INLINE void Disable(s32 argument);
      INLINE void Toggle(s32 argument);

      INLINE bool IsEnabled(s32 argument) const;
      INLINE bool IsDisabled(s32 argument) const;

      // -- Window Modified Property Interface --
      INLINE Math::Vector2 GetWindowSize(void) const;
      INLINE Math::Vector2 GetWindowPosition(void) const;
      INLINE bool IsCollapsed(void) const;
      INLINE bool IsFocused(void) const;

      // -- Window Alignment Interface --


    protected:
      // -- User Defined Properties --
      std::string   title;
      Math::Vector2 initial_size;
      Math::Vector2 initial_position;
      s32           flags;
      f32           alpha;

    private:
      // -- User Modified Properties --
      Math::Vector2 current_size;
      Math::Vector2 current_position;
      bool          is_collapsed;
      bool          is_focused;

      // -- Alignment Properties --
      Math::Vector2 anchor;
      WindowAlignment horizontal_alignment;
      WindowAlignment vertical_alignment;
      bool fixed;
  };
}
