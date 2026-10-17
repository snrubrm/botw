#include <nn/ui2d/Material.h>
#include <nn/ui2d/Pane.h>
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiUnkSingletons.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Thread/ManagedTaskHandle.h"
#include "KingSystem/Utils/Thread/ManagedTask.h"

namespace uking::ui {

// 0x71009cb0c8
Unk_71009cb0c8::Unk_71009cb0c8()
    : mTaskDelegate(this, &Unk_71009cb0c8::sub_71009CB188),
      mPostRunCallback(this, &Unk_71009cb0c8::sub_71009CB804),
      mRemoveCallback(this, &Unk_71009cb0c8::sub_71009CBC64) {}

// 0x71009cbc64
void Unk_71009cb0c8::sub_71009CBC64(const ksys::TaskRemoveCallbackContext&) {
    mCS.lock();
    auto* handle = mLoader.mTaskHandle;
    if (handle) {
        mLoader.mTaskHandle = nullptr;
        mCS.unlock();
        handle->finalize();
        return;
    }
    mCS.unlock();
}

// NON_MATCHING: queue search/allocation and packed request-flag stores schedule differently.
// 0x71009cbfc4
void Unk_71009cb0c8::sub_71009CBFC4(const ::Unk_710247e960& request) {
    if (!mTextureHandle)
        return;
    auto lock = sead::makeScopedLock(mCS);
    ::Unk_710247e990::Command* load = nullptr;
    ::Unk_710247e990::Command* cancel = nullptr;
    for (s32 i = 0; i < mLoader.mCommands.size(); ++i) {
        auto* command = mLoader.mCommands[i];
        if (command->type == 0)
            load = command;
        else if (command->type == 6)
            cancel = command;
    }
    if (!load && !mLoader.mCommands.isFull())
        load = mLoader.mCommands.emplaceBack();
    if (load) {
        load->type = 0;
        mLoader.mPendingRequest._8 = request._8;
        mLoader.mPendingRequest._60 = request._60;
        mLoader.mPendingRequest._b8 = request._b8;
        mLoader.mPendingRequest._c8 = request._c8;
        mLoader.mPendingRequest._cc = (request._cc & 0xff) | 0x100;
        mLoader.mPendingRequest._d0 = request._d0;
    }
    if (mLoader.mQueueState >= 0 && mLoader.mQueueState < 6 && !cancel) {
        if (!mLoader.mCommands.isFull())
            mLoader.mCommands.insert(0, {6});
        if (mMaterial)
            mMaterial->GetTexMapArray()[0].ReplaceTextureInfo(&mTexInfo);
        if (mAnimator)
            mAnimator->Stop(0.0f);
        mApplied = false;
    }
    if (!mLoader.mTaskHandle) {
        UiLowPrioThreadMgr::Request task{
            &mTaskDelegate, nullptr, &mRemoveCallback, &mPostRunCallback,
            mLoader.mTaskHandle, nullptr};
        mLoader.mTaskHandle = UiLowPrioThreadMgr::instance()->submitRequest(task);
    }
}

// NON_MATCHING: the state tests and packed flag stores differ in branch/store ordering.
// 0x71009cb804
void Unk_71009cb0c8::sub_71009CB804(ksys::TaskPostRunResult* result,
                                  const ksys::TaskPostRunContext& context) {
    const bool cancelled = context.mCancelled;
    bool finalize = false;
    ksys::ManagedTaskHandle* handle;
    {
        auto lock = sead::makeScopedLock(mCS);
        handle = mLoader.mTaskHandle;
        if (cancelled) {
            if (handle) {
                mLoader.mTaskHandle = nullptr;
                finalize = true;
            }
        } else {
            if (mLoader.mCommands.size() > 0) {
                auto* command = mLoader.mCommands.front();
                if (command) {
                    if (command->type == 6) {
                        if (mLoader.mQueueState > 11)
                            mLoader.mCommands.erase(0);
                        if (mLoader.mQueueState == 5 || mLoader.mQueueState == 2) {
                            mLoader.mQueueState = 6;
                            mLoader.mCommands.erase(0);
                        }
                    } else if (command->type == 0 && mLoader.mQueueState > 11) {
                        mLoader.mQueueState = 0;
                        mLoader.mCurrentRequest._8 = mLoader.mPendingRequest._8;
                        mLoader.mCurrentRequest._60 = mLoader.mPendingRequest._60;
                        mLoader.mCurrentRequest._b8 = mLoader.mPendingRequest._b8;
                        mLoader.mCurrentRequest._c8 = mLoader.mPendingRequest._c8;
                        mLoader.mCurrentRequest._d0 = mLoader.mPendingRequest._d0;
                        mLoader.mCurrentRequest._cc = (mLoader.mPendingRequest._cc & 0xff) | 0x100;
                        mLoader.mCommands.erase(0);
                        mLoader.mPendingRequest.reset();
                    }
                }
            }
            if (mLoader.mCommands.isEmpty() &&
                (mLoader.mQueueState == 5 || mLoader.mQueueState == 12 || mLoader.mQueueState == 13)) {
                if (mLoader.mTaskHandle) {
                    mLoader.mTaskHandle = nullptr;
                    finalize = true;
                }
            } else if (mLoader.mTaskHandle) {
                UiLowPrioThreadMgr::Request task{
                    &mTaskDelegate, nullptr, &mRemoveCallback, &mPostRunCallback,
                    mLoader.mTaskHandle, static_cast<ksys::ManagedTask*>(context.mTask)};
                mLoader.mTaskHandle = UiLowPrioThreadMgr::instance()->submitRequest(task);
                result->setResult(true);
            }
            if (mLoader.mQueueState == 12) {
                mLoader.mCurrentRequest.reset();
                mLoader.mQueueState = 13;
            }
        }
    }
    if (handle && finalize)
        handle->finalize();
}

// NON_MATCHING: queue lookup and insertion use different branch and allocation paths.
// 0x71009cc3a0
void Unk_71009cb0c8::sub_71009CC3A0() {
    if (!mTextureHandle)
        return;
    auto lock = sead::makeScopedLock(mCS);
    ::Unk_710247e990::Command* load = nullptr;
    ::Unk_710247e990::Command* cancel = nullptr;
    for (s32 i = 0; i < mLoader.mCommands.size(); ++i) {
        auto* command = mLoader.mCommands[i];
        if (command->type == 0)
            load = command;
        else if (command->type == 6)
            cancel = command;
    }
    if (load) {
        mLoader.mPendingRequest.reset();
        mLoader.mCommands.erase(mLoader.mCommands.indexOf(load));
    }
    if (mLoader.mQueueState < 6 || mLoader.mQueueState > 13) {
        if (!cancel) {
            if (!mLoader.mCommands.isFull())
                mLoader.mCommands.insert(0, {6});
            if (mMaterial)
                mMaterial->GetTexMapArray()[0].ReplaceTextureInfo(&mTexInfo);
            if (mAnimator)
                mAnimator->Stop(0.0f);
            mApplied = false;
        }
        if (!mLoader.mTaskHandle) {
            UiLowPrioThreadMgr::Request task{
                &mTaskDelegate, nullptr, &mRemoveCallback, &mPostRunCallback,
                mLoader.mTaskHandle, nullptr};
            mLoader.mTaskHandle = UiLowPrioThreadMgr::instance()->submitRequest(task);
        }
    }
}

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
    if (mLoader.mCommands.size() != 0)
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
    if (mLoader.mCommands.size() != 0)
        return false;
    return mLoader.mQueueState == 5;
}

// 0x71009cbfa4
bool Unk_71009cb0c8::sub_71009CBFA4() const {
    if (mLoader.mCommands.size() != 0)
        return false;
    return mLoader.mQueueState == 13;
}

}  // namespace uking::ui
