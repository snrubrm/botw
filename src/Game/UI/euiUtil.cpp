#include <cstring>
#include <nn/ui2d/Material.h>
#include <nn/ui2d/Pane.h>
#include <nn/ui2d/ResExtUserData.h>
#include <nn/ui2d/TextureInfo.h>
#include "Game/UI/euiTypes.h"
#include "Game/UI/euiTextSearcher.h"
#include "Game/UI/euiLayoutEx.h"

namespace eui {

// 0x7100befa74
void SetTextureInfoFromTexMap(nn::ui2d::TextureInfo* out, const nn::ui2d::TexMap& map) {
    const auto* info = map.GetTextureInfo();
    out->InvalidateDescriptorSlot();
    out->SetDescriptorSlot(info->GetDescriptorSlot());
}

// NON_MATCHING: the compiler inlines the hierarchy append helper into this wrapper.
// 0x7100bef394
void CreateLayoutItemUniqueName(sead::StringBuilder* out, const char* name, const LayoutEx* layout) {
    out->clear();
    AppendLayoutItemUniqueName(out, name, layout);
}

// NON_MATCHING: hierarchy-loop guards and the final append are lowered differently.
// 0x7100bef3b0
void AppendLayoutItemUniqueName(sead::StringBuilder* out, const char* name, const LayoutEx* layout) {
    const LayoutEx* parents[5];
    s32 count = 0;
    while (layout && layout->_88 && count < 5) {
        parents[count++] = layout;
        layout = layout->_88;
    }
    while (count > 0) {
        --count;
        out->append(parents[count]->GetPane()->GetName(), -1);
        out->append("-", -1);
    }
    out->append(name, -1);
}

// 0x7100bed2bc
f32 GetRadAngleOfDirection(Direction direction) {
    switch (int(direction.value())) {
    case 0:
        return 1.5707964f;
    case 1:
        return 4.712389f;
    case 2:
        return 3.1415927f;
    default:
        return 0.0f;
    }
}

// 0x7100bed250
const nn::ui2d::ResExtUserData* FindExtUserDataFromList(const nn::ui2d::ResExtUserDataList* list, const char* name) {
    if (list) {
        const nn::ui2d::ResExtUserData* data = list->GetArray();
        for (u64 i = 0; i < list->GetCount(); i++, data++) {
            if (std::strcmp(name, data->GetName()) == 0)
                return data;
        }
    }
    return nullptr;
}

// 0x7100bed6bc
void ApplyTextureInfoToMaterial(nn::ui2d::Pane* pane, const nn::ui2d::TextureInfo& info, s32 index) {
    const u8 count = pane->GetMaterialCount();
    for (s32 i = 0; i < count; ++i) {
        nn::ui2d::Material* material = pane->GetMaterial(i);
        if (index < material->GetTexMapCount())
            material->GetTexMapArray()[index].ReplaceTextureInfo(&info);
    }
}

}  // namespace eui
