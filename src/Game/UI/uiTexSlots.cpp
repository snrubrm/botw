#include "Game/UI/uiTexSlots.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "KingSystem/Resource/resHandle.h"

namespace eui {
void SetTextureInfoFromTexMap(nn::ui2d::TextureInfo* out, const nn::ui2d::TexMap& map);
}

namespace uking::ui {

// 0x7100a81208
UiTexSlots::UiTexSlots() = default;

// NON_MATCHING: same code, the original keeps the entry pointer of the second lookup in x8 (the register of the size)
// where ours uses a fresh register (register allocation only; the destructor below shows the same difference)
// 0x7100a813e0
void UiTexSlots::unload(s32 index) {
    if (eui::Animator* animator = mEntries[index].animator)
        animator->StopAtMin();
    Entry& entry = mEntries[index];
    if (entry.handle && entry.material)
        entry.material->GetTexMapArray()[entry.texMapIndex].ReplaceTextureInfo(&mTexInfo);
    if (mEntries[index].handle->requestedLoad())
        mEntries[index].handle->requestUnload2();
}

// NON_MATCHING: inlines unload() above (same register allocation difference)
// 0x7100a812a8
UiTexSlots::~UiTexSlots() {
    s32 i = 0;
    for (Entry& entry : mEntries) {
        if (entry.handle) {
            unload(i);
            delete entry.handle;
            entry.handle = nullptr;
        }
        ++i;
    }
    mEntries.freeBuffer();
}

// 0x7100a819fc
void UiTexSlots::setMaterial(s32 index, nn::ui2d::Material* material, bool apply) {
    mEntries[index].material = material;
    if (apply && material)
        eui::SetTextureInfoFromTexMap(&mTexInfo, material->GetTexMapArray()[0]);
}

// 0x7100a81a30
void UiTexSlots::setMaterialAndTexMapIndex(s32 index, nn::ui2d::Material* material, s32 tex_map_index,
                                           bool apply) {
    mEntries[index].material = material;
    mEntries[index].texMapIndex = tex_map_index;
    if (apply && material)
        eui::SetTextureInfoFromTexMap(&mTexInfo, material->GetTexMapArray()[0]);
}

// 0x7100a81a7c
void UiTexSlots::applyMaterial(s32 index) {
    if (nn::ui2d::Material* material = mEntries[index].material)
        eui::SetTextureInfoFromTexMap(&mTexInfo, material->GetTexMapArray()[0]);
}

// 0x7100a81aac
void UiTexSlots::setAnimator(s32 index, eui::LayoutEx* layout, const sead::SafeString& name) {
    if (layout)
        mEntries[index].animator = layout->tryCreateAnimatorAuto(name.cstr(), false);
}

// 0x7100a81f14
bool UiTexSlots::isLoaded(s32 index) {
    return mEntries[index].loaded;
}

// 0x71009f2778 (D1) / 0x71009f278c (D0)
Unk_7102481e30::~Unk_7102481e30() = default;

}  // namespace uking::ui
