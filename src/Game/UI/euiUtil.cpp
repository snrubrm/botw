#include <cstring>
#include <driver/aglNVNMgr.h>
#include <gfx/seadCamera.h>
#include <gfx/seadProjection.h>
#include <math/seadBoundBox.h>
#include <message/seadMessageSet.h>
#include <prim/seadDelegate.h>
#include <nn/gfx/gfx_Sampler.h>
#include <nn/gfx/gfx_Texture.h>
#include <nn/ui2d/DrawInfo.h>
#include <nn/ui2d/Types.h>
#include <nn/ui2d/Material.h>
#include <nn/ui2d/Pane.h>
#include <nn/ui2d/ResExtUserData.h>
#include <nn/ui2d/TextureInfo.h>
#include "Game/UI/euiTypes.h"
#include "Game/UI/euiTextSearcher.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiMessageString.h"

namespace eui {

// NON_MATCHING: base-position branches fold into conditional selects; load scheduling differs.
// 0x7100bed030
void CalcPaneBoundBox(sead::BoundBox2f* box, const nn::ui2d::Pane& pane) {
    const auto& matrix = pane.GetMtx();
    f32 width = pane.GetSize().width * matrix.m[0][0];
    f32 height = pane.GetSize().height * matrix.m[1][1];
    width = width > 0.0f ? width : -width;
    height = height > 0.0f ? height : -height;
    width *= 0.5f;
    height *= 0.5f;
    f32 x = matrix.m[0][3];
    f32 y = matrix.m[1][3];
    switch (pane.GetBasePositionH()) {
    case nn::ui2d::HorizontalPosition_Left:
        x += width;
        break;
    case nn::ui2d::HorizontalPosition_Right:
        x -= width;
        break;
    default:
        break;
    }
    switch (pane.GetBasePositionV()) {
    case nn::ui2d::VerticalPosition_Top:
        y -= height;
        break;
    case nn::ui2d::VerticalPosition_Bottom:
        y += height;
        break;
    default:
        break;
    }
    box->setMin({x - width, y - height});
    box->setMax({x + width, y + height});
}

// NON_MATCHING: matrix copies remain memcpy calls and the derived destructors are out of line.
// 0x7100bee638
void SetupDrawInfoOrtho(nn::ui2d::DrawInfo* info, const nn::ui2d::Size& size) {
    sead::OrthoProjection projection(0.0f, 300.0f, size.height * 0.5f, size.height * -0.5f,
                                    size.width * -0.5f, size.width * 0.5f);
    sead::OrthoCamera camera(projection);
    camera.updateViewMatrix();
    nn::util::Matrix4x4fType matrix;
    std::memcpy(&matrix, &projection.getDeviceProjectionMatrix(), sizeof(matrix));
    info->SetProjMtx(matrix);
    std::memcpy(&info->mViewMtx, &camera.getMatrix(), sizeof(info->mViewMtx));
}

// NON_MATCHING: matrix copies remain memcpy calls and the frame is larger (as SetupDrawInfoOrtho)
// 0x7100bee700
void SetupDrawInfoPerspective(f32 fov, nn::ui2d::DrawInfo* info, const nn::ui2d::Size& size) {
    const f32 half_width = size.width * 0.5f;
    const f32 half_height = size.height * 0.5f;
    const f32 distance = half_height / std::tan(fov * 0.5f);
    sead::PerspectiveProjection projection(1.0f, 10000.0f, fov, half_width / half_height);
    const sead::Vector3f position(0.0f, 0.0f, distance);
    sead::LookAtCamera camera(position, sead::Vector3f::zero, sead::Vector3f::ey);
    camera.updateViewMatrix();
    nn::util::Matrix4x4fType matrix;
    std::memcpy(&matrix, &projection.getDeviceProjectionMatrix(), sizeof(matrix));
    info->SetProjMtx(matrix);
    std::memcpy(&info->mViewMtx, &camera.getMatrix(), sizeof(info->mViewMtx));
}

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

// NON_MATCHING: initial guards, marker tests and tag-loop blocks are lowered differently.
// 0x7100bef968
void ProcessMessageAppTag(
    const MessageString& message,
    sead::IDelegate1<const sead::MessageSet<char16>::TagInfo*>* callback) {
    const char16* text = message.getString();
    const s32 length = message.getLength();
    if (!text || length < 1)
        return;
    for (s32 i = 0; i < length;) {
        const char16* cursor = text + i;
        if (*cursor != 0xe && *cursor != 0xf) {
            ++i;
            continue;
        }
        const auto* tag = reinterpret_cast<const sead::MessageSet<char16>::TagInfo*>(cursor);
        const char16* next =
            *cursor == 0xe ? reinterpret_cast<const char16*>(tag->getParam() + tag->paramSize)
                          : cursor + 3;
        if (tag->group >= 2)
            callback->invoke(tag);
        i = next - text;
    }
}

// 0x7100befa8c
bool RegisterSlotForTexture(nn::gfx::DescriptorSlot* slot, const nn::gfx::TextureView& view,
                            void*) {
    slot->ToData()->value =
        static_cast<agl::driver::NVNMgr*>(agl::driver::GraphicsDriverMgr::instance())
            ->registerTexture(static_cast<const NVNtexture*>(view.ToData()->pNvnTexture.ptr),
                              static_cast<const NVNtextureView*>(view.ToData()->pNvnTextureView.ptr),
                              "ui2d");
    return true;
}

// 0x7100befad4
bool RegisterSlotForSampler(nn::gfx::DescriptorSlot* slot, const nn::gfx::Sampler& sampler,
                            void*) {
    slot->ToData()->value =
        static_cast<agl::driver::NVNMgr*>(agl::driver::GraphicsDriverMgr::instance())
            ->registerSampler(static_cast<const NVNsampler*>(sampler.ToData()->pNvnSampler.ptr),
                              "ui2d");
    return true;
}

// 0x7100befb18
void UnregisterSlotForTexture(nn::gfx::DescriptorSlot* slot, const nn::gfx::TextureView&, void*) {
    static_cast<agl::driver::NVNMgr*>(agl::driver::GraphicsDriverMgr::instance())
        ->releaseTexture(slot->ToData()->value);
}

// 0x7100befb30
void UnregisterSlotForSampler(nn::gfx::DescriptorSlot* slot, const nn::gfx::Sampler&, void*) {
    static_cast<agl::driver::NVNMgr*>(agl::driver::GraphicsDriverMgr::instance())
        ->releaseSampler(slot->ToData()->value);
}

}  // namespace eui
