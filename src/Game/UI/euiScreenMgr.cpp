#include "Game/UI/euiBoxCursor.h"
#include "Game/UI/euiConstantBuffer.h"
#include "Game/UI/euiFontMgr.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/euiNwAllocator.h"
#include <gfx/nin/seadGraphicsNvn.h>
#include <heap/seadHeapMgr.h>

namespace eui {

// NON_MATCHING: final byte flags and null-pointer initialization store order differs.
SEAD_CREATE_SINGLETON_INSTANCE(ScreenMgr)

ScreenMgr::ScreenMgr()
    : mTargetMgr(nullptr), mArcResourceMgr(nullptr), mBoxCursorMgr(nullptr), mAnimationStep(1.0f),
      mMessageMgr(nullptr), mFontMgr(nullptr), mTargetFlags{{1, 1}}, mConstantBuffer(nullptr) {}

ScreenMgr::~ScreenMgr() {
    if (auto* heap = sead::HeapMgr::instance()->findContainHeap(mScreens.getBufferPtr())) {
        NwAllocator::initialize(heap);
        mGraphicsResource.UnregisterCommonSamplerSlot(UnregisterSlotForSampler, nullptr);
        mGraphicsResource.Finalize(sead::GraphicsNvn::instance()->getNnDevice());
        NwAllocator::finalize();
    }
}


// 0x7100bec7cc
const void* ScreenMgr::getMultiFilterParameterData(const sead::SafeString& path) const {
    if (auto* archive = mMultiFilterArchive.getResource())
        return archive->getFile(path);
    return nullptr;
}

// 0x7100bec794
void ScreenMgr::resetScreenId(s32 id) {
    mScreenTargets[id] = -1;
    mScreens[id] = nullptr;
}

// 0x7100bec724
void ScreenMgr::unloadScreen(s32 id) {
    Screen* screen = mScreens[id];
    if (!screen)
        return;
    resetScreenId(id);
    if (screen->isOwnInitializeHeap())
        screen->getInitializeHeap()->destroy();
}

// 0x7100bec7e8
void ScreenMgr::inactivateScreen(s32 id) {
    mScreenTargets[id] = -1;
}

// 0x7100bec808
void ScreenMgr::activateScreen(s32 id) {
    mScreenTargets[id] = mScreens[id]->mDrawTarget;
}

// 0x7100bec4c0
void ScreenMgr::update() {
    mTargetFlags[0] = 1;
    mTargetFlags[1] = 1;
    if (auto* font = mFontMgr->getScalableFontMgr())
        font->sub_7100BE55A8();
    if (mBoxCursorMgr)
        mBoxCursorMgr->update();
    mConstantBuffer->map();
    updateScreenAll();
    mConstantBuffer->unmap();
    mConstantBuffer->swapIndex();
}

// 0x7100bec840
void ScreenMgr::eraseBoxCursorNodeFromRouteNodes(const BoxCursorNode* node) {
    for (auto it = mScreens.begin(), end = mScreens.end(); it != end; ++it) {
        if (*it)
            (*it)->eraseBoxCursorNodeFromRouteNodes(node);
    }
}

// 0x7100bec534
// NON_MATCHING: same code, but clang keeps the reverse index and the loop counter as separate values and peels the
// loop on `count > 1` differently (register allocation / induction variable choice)
void ScreenMgr::updateScreenAll() {
    Screen* deferred[2];
    u32 count = 0;
    for (auto it = mScreenTargets.rbegin(); it != mScreenTargets.rend(); ++it) {
        if (*it < 0)
            continue;
        Screen* screen = mScreens[it.getIndex()];
        if (screen->hasFlag4()) {
            if (count < 2)
                deferred[count++] = screen;
        } else {
            screen->update();
        }
    }
    for (u32 i = 0; i < count; ++i)
        deferred[i]->update();
}

// 0x7100bec690
void ScreenMgr::draw(s8 target, const DrawInfoEx::RenderBufferInfo* info) {
    s32 i = 0;
    for (const s8& t : mScreenTargets) {
        if (u8(t) == u8(target))
            mScreens[i]->draw(info);
        ++i;
    }
}

}  // namespace eui
