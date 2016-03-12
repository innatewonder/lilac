/*
*  FILE          InterfaceGUIWrapper.hpp
*  AUTHOR        Brendon Clifford
*  DESCRIPTION
*    Declaration for global wrapper functions used to interface with GUI libraries.
*/

#if defined(INTERFACE_IMGUI)

#include <imgui.h>

namespace GUI
{
  template <typename T>
  void Display(Meta::VariantReference& ref, const Meta::MetaProperty* member)
  {
    s32 id = 0;
    const Meta::MetaData* meta = ref.Meta();
    /*
    if(ImGui::CollapsingHeader(meta->GetName(), nullptr, true, true))
    {
      const Meta::MetaData* meta_iter = meta;
      while(meta_iter)
      {
        ImGui::PushID(id++);
        DisplaySeparator(meta->Interface());
        const Meta::MetaProperty* member_iter = meta_iter->Members();
        while(member_iter)
        {
          member_iter->Meta()->Display(Meta::VariantReference(member_iter->Meta(), POINTER_OFFSET(ref.Data(), member_iter->GetOffset())), member_iter);
          member_iter = member_iter->Next();
        }
        ImGui::PopID();
        meta_iter = meta_iter->GetParent();
      }
    }
    */

    if(ImGui::CollapsingHeader(meta->GetName(), nullptr, true, true))
    {
      for(Meta::MetaData::CategoryMap::const_iterator it = meta->Categories().begin(); it != meta->Categories().end(); ++it)
      {
        const std::string& category = it->first;
        if(category[0] == '\0')
          continue;

        ImGui::SetNextTreeNodeOpened(true, ImGuiSetCond_Once);
        if(ImGui::TreeNode(category.c_str()))
        {
          const Meta::MetaData* category_iter = meta;
          while(category_iter)
          {
            ImGui::PushID(id++);
            if(category_iter->Categories().find(category) != category_iter->Categories().end())
            {
              const Meta::MetaData::PropertyList& property_list = (category_iter->Categories().find(category))->second;
              for(Meta::MetaData::PropertyList::const_iterator p = property_list.begin(); p != property_list.end(); ++p)
              {
                (*p)->Meta()->Display(Meta::VariantReference((*p)->Meta(), POINTER_OFFSET(ref.Data(), (*p)->GetOffset())), (*p));
              }
            }

            ImGui::PopID();
            category_iter = category_iter->GetParent();
          }
          ImGui::TreePop();
        }

        DisplaySeparator(meta->Interface());
      }


      const Meta::MetaData* meta_iter = meta;
      while(meta_iter)
      {
        ImGui::PushID(id++);

        if(meta_iter->Categories().find("") != meta_iter->Categories().end())
        {
          const Meta::MetaData::PropertyList& property_list = (meta_iter->Categories().find(""))->second;
          for(Meta::MetaData::PropertyList::const_iterator p = property_list.begin(); p != property_list.end(); ++p)
          {
            (*p)->Meta()->Display(Meta::VariantReference((*p)->Meta(), POINTER_OFFSET(ref.Data(), (*p)->GetOffset())), (*p));
          }
          DisplaySeparator(meta->Interface());
        }

        ImGui::PopID();
        meta_iter = meta_iter->GetParent();
      }
    }
  }
}

#else

namespace GUI
{

}

#endif