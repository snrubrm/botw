#include <nn/ui2d/Material.h>
#include <nn/ui2d/Pane.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Thread/ManagedTaskHandle.h"

namespace uking::ui {

// 0x71009cbcc0
Unk_71009cb0c8::~Unk_71009cb0c8() {
    ksys::ManagedTaskHandle* task_handle;
    {
        auto lock = sead::makeScopedLock(mCS);
        task_handle = mLoader.mTaskHandle;
    }
    if (task_handle && task_handle->hasTask())
        task_handle->removeTaskFromQueue();
    if (mTextureHandle) {
        mTextureHandle->requestUnload();
        delete mTextureHandle;
        mTextureHandle = nullptr;
    }
}

// 0x71009cbe38
void Unk_71009cb0c8::sub_71009CBE38() {
    if (mApplied)
        return;
    if (mLoader.mQueueCount != 0)
        return;
    if (mLoader.mQueueState != 5)
        return;
    auto* texture_info = sub_71009CBECC();
    if (!texture_info)
        return;
    if (mMaterial)
        mMaterial->GetTexMapArray()[0].ReplaceTextureInfo(texture_info);
    if (mAnimator)
        mAnimator->PlayAuto(1.0f);
    mApplied = true;
}

// 0x71009cbd48
void Unk_71009cb0c8::sub_71009CBD48(sead::Heap* heap, eui::LayoutEx* layout,
                                    const sead::SafeString& name) {
    if (!layout)
        return;
    const char* pane_name = name.cstr();
    auto* pane = layout->mPane->FindPaneByName(pane_name, true);
    if (!pane)
        return;
    auto* material = pane->GetMaterial();
    mTextureHandle = new (heap, 8) ksys::res::Handle;
    mMaterial = material;
    if (mMaterial)
        eui::SetTextureInfoFromTexMap(&mTexInfo, mMaterial->GetTexMapArray()[0]);
}

// 0x71009cbde8
void Unk_71009cb0c8::sub_71009CBDE8(eui::LayoutEx* layout, const sead::SafeString& name) {
    mAnimator = layout->tryCreateAnimatorAuto(name.cstr(), false);
}

// 0x71009cbeac
bool Unk_71009cb0c8::sub_71009CBEAC() const {
    if (mLoader.mQueueCount != 0)
        return false;
    return mLoader.mQueueState == 5;
}

// 0x71009cbfa4
bool Unk_71009cb0c8::sub_71009CBFA4() const {
    if (mLoader.mQueueCount != 0)
        return false;
    return mLoader.mQueueState == 13;
}

}  // namespace uking::ui
