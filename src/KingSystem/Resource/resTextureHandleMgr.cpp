#include "KingSystem/Resource/resTextureHandleMgr.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resCounter.h"
#include "KingSystem/Resource/resArchiveWork.h"
#include "KingSystem/Resource/resUnk_71024F9D48.h"
#include "KingSystem/Resource/resUnk_710251A740.h"
#include "KingSystem/Resource/resBfRes.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include <g3d/aglNW4FToNN.h>
#include "Game/gameUnkRttiClasses.h"
#include "KingSystem/Utils/Thread/TaskMgr.h"
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/Utils/Thread/Task.h"
#include "KingSystem/Utils/Thread/TaskThread.h"

Unk_71024f9bb8::~Unk_71024f9bb8() = default;

namespace ksys::res {

Unk_71024f9a70::Unk_71024f9a70() = default;

Unk_71024f9a70::~Unk_71024f9a70() {
    mResFile = nullptr;
    mFileDevice = nullptr;
    if (mResource)
        ResourceMgrTask::instance()->unloadSeadResource(mResource);
    mHandle.requestUnload();
    mPath.clear();
    mFlags.reset(3);
}

bool Unk_71024f9a70::sub_7100FE15D8() const {
    return mFlags.isOn(1);
}

bool Unk_71024f9a70::init(const InitArg& arg) {
    mLoadParams.mFileDevice = arg.mFileDevice;
    mLoadParams._0 = arg._0;
    mLoadParams.mPath = mPath;
    mPath = arg.mPath;
    mFlags.set(1);
    return true;
}

bool Unk_71024f9a70::load() {
    LoadStatus status;
    sub_7100FE1630(&status, mLoadParams);
    if (!status.success)
        return false;
    mFlags.set(2);
    return true;
}

bool Unk_71024f9a70::sub_7100FE1AF0() const {
    return mFlags.isOn(2);
}

s32 Unk_71024f9a70::getTextureCount() const {
    if (!mFlags.isOn(2))
        return 0;
    return agl::g3d::ResFile::GetTextureCount(mResFile);
}

sead::SafeString Unk_71024f9a70::getTextureName(s32 index) const {
    return agl::g3d::ResFile::GetTextureName(mResFile, index);
}

bool Unk_71024f9a70::hasTexture(const sead::SafeString& name) const {
    return agl::g3d::ResFile::sub_7100B33BF0(mResFile, name.cstr()) != nullptr;
}

// Full native initializer FE2398 and loader FE1630 prove this separate factory.
// NON_MATCHING: namespace linkage uses GOT addressing instead of the native direct address.
EntryFactory<Unk_710251A740> sUnk_710260E8A0;

TextureHandleMgr* TextureHandleMgr::sInstance;

void TextureHandleMgr::setInstance(TextureHandleMgr* mgr) {
    sInstance = mgr;
}

void TextureHandleMgr::calc() {
    if (!_30->canSubmitRequest())
        return;

    util::TaskRequest req;
    req.mHasHandle = false;
    req.mSynchronous = false;
    req.mLaneId = 8;
    req.mThread = _50;
    req.mName = "TextureHandleMgr::calc";
    _30->submitRequest(req);
}

void TextureHandleMgr::preCalc() {}


// NON_MATCHING: resource iterator and heap use exchanged registers.
void TextureHandleMgr::sub_7100FE5190() {
    delete mArchiveWork;
    mArchiveWork = nullptr;
    stubbedLogFunction();
    auto* counter = mHeapCounter;
    counter->incrementRef();
    if (mResources.begin() != mResources.end()) {
        auto* heap = static_cast<CompactedHeap*>(counter->getData());
        for (auto& resource : mResources)
            resource.sub_7100FE10EC(heap);
    }
    mHeapCounter->decrementRef();
    stubbedLogFunction();
}

// NON_MATCHING: resource iterator and heap use exchanged registers.
void TextureHandleMgr::sub_7100FE5334() {
    stubbedLogFunction();
    auto* counter = mHeapCounter;
    counter->incrementRef();
    if (mResources.begin() != mResources.end()) {
        auto* heap = static_cast<CompactedHeap*>(counter->getData());
        for (auto& resource : mResources)
            resource.sub_7100FE10EC(heap);
    }
    mHeapCounter->decrementRef();
    stubbedLogFunction();
}

// 0x7100fe53bc (unnamed in the CSV): cancel everything queued on the loading thread and mark the
// manager as stopped.
void TextureHandleMgr::sub_7100FE53BC() {
    _50->cancelTasks(0);
    _50->cancelTasks(1);
    mFlags2.reset(1);
    if (!mFlags.isOn(4)) {
        mFlags.set(4);
        stubbedLogFunction();
    }
}

void TextureHandleMgr::sub_7100FE60B0(bool on) {
    if (mFlags.isOn(2) != on) {
        mFlags.change(2, on);
        stubbedLogFunction();
    }
}

void TextureHandleMgr::sub_7100FE60DC(bool on) {
    if (mFlags.isOn(1) != on) {
        mFlags.change(1, on);
        mFlags.change(4, on);
        stubbedLogFunction();
    }
}

bool TextureHandleMgr::isTooSlow(s32 seconds) {
    if (!mFlags2.isOn(4))
        return false;

    if (mTickTime.diffToNow().toSeconds() < seconds)
        return false;

    mTickTime.setNow();
    mFlags2.reset(4);
    stubbedLogFunction();
    return true;
}

bool TextureHandleMgr::sub_7100FE6120() const {
    return mFlags2.isOn(2);
}

ArchiveWork* TextureHandleMgr::getArchiveWork() const {
    return mArchiveWork;
}

void TextureHandleMgr::clearAllCache() {
    Unk_71024f9bb8 request;
    request.mHasHandle = false;
    request.mSynchronous = false;
    request.mLaneId = 7;
    request.mThread = _50;
    request.mDelegate = &_158;
    request.mName = "Texture::ClearAllCache";
    util::TaskMgrRequest manager_request;
    manager_request.request = &request;
    _48->submitRequest(manager_request);
}

}  // namespace ksys::res
