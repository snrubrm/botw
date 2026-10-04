#pragma once

#include <basis/seadTypes.h>
#include <nn/gfx/gfx_DescriptorSlot.h>
#include <nn/gfx/gfx_Types.h>
#include <prim/seadEnum.h>

namespace nn::ui2d {
class DrawInfo;
class Pane;
class TextureInfo;
struct Size;
struct ResExtUserData;
struct ResExtUserDataList;
}  // namespace nn::ui2d

namespace eui {

// The two screens of the original (guess: TV / gamepad); the enumerator names are not known.
SEAD_ENUM(DrawTarget, _0, _1)

// A direction of the box cursor routes (up / down / left / right in some order; names not known)
SEAD_ENUM(Direction, _0, _1, _2, _3)

// 0x7100bee638
void SetupDrawInfoOrtho(nn::ui2d::DrawInfo*, const nn::ui2d::Size&);

// 0x7100bed2bc: the angle (radians) of a box cursor route direction
f32 GetRadAngleOfDirection(Direction direction);

// 0x7100bed6bc: sets the texture info of texture map `index` in every material of the pane that has such a map
void ApplyTextureInfoToMaterial(nn::ui2d::Pane* pane, const nn::ui2d::TextureInfo& info, s32 index);

// 0x7100bed250: the entry named `name` of an ext user data list (null list or no such entry: null)
const nn::ui2d::ResExtUserData* FindExtUserDataFromList(const nn::ui2d::ResExtUserDataList* list, const char* name);

// Descriptor callbacks release the registered backend slot; other callback inputs are unused.
void UnregisterSlotForTexture(nn::gfx::DescriptorSlot*, const nn::gfx::TextureView&, void*);
void UnregisterSlotForSampler(nn::gfx::DescriptorSlot*, const nn::gfx::Sampler&, void*);

}  // namespace eui
