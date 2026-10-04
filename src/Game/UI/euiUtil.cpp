#include <nn/ui2d/Material.h>
#include <nn/ui2d/Pane.h>
#include "Game/UI/euiTypes.h"

namespace eui {

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
