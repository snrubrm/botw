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
#include "KingSystem/Utils/Thread/ManagedTask.h"
#include "KingSystem/Resource/resResourceFileUtil.h"

Unk_71024f9bb8::~Unk_71024f9bb8() = default;

namespace ksys::res {

Unk_71024f9b08::~Unk_71024f9b08() = default;

void sub_7100FE0D98(Unk_71024f9a08* resource, Unk_71024F9D48* handle) {
    resource->mCS.lock();
    resource->mHandles.erase(handle);
    resource->mCS.unlock();
}

bool sub_7100FE0F14(Unk_71024f9a08* resource) {
    if (resource->mStatus == 2 || resource->mStatus == 5)
        return true;
    return resource->mFlags.isOnBit(2);
}

// NON_MATCHING: the original lowers this switch to a seven-entry jump table over mStatus 2..8
// (cases 3, 5, 7 and the default all share the `mStatus == 5` block); clang 4 folds the
// 2/4/8 cluster into a 0x134 bit test instead. Both case orders were tried; both give the bit test.
bool sub_7100FE0F44(Unk_71024f9a08* resource) {
    switch (resource->mStatus) {
    case 2:
    case 4:
    case 8:
        return true;
    case 6:
        return resource->mFlags.isOnBit(1);
    default:
        return resource->mStatus == 5;
    }
}

nn::gfx::ResTexture* sub_7100FE0F8C(Unk_71024f9a08* resource) {
    return sub_7100FDDC24(&resource->_1f8);
}



// FE2890 allocates 0x140 bytes; FE85E8 constructs ManagedTask and the 0x80-byte data.
class Unk_71024f9da0 : public util::ManagedTask {
    SEAD_RTTI_OVERRIDE(Unk_71024f9da0, util::ManagedTask)
public:
    explicit Unk_71024f9da0(sead::Heap* heap);
    ~Unk_71024f9da0() override;

protected:
    void prepareImpl_(util::TaskRequest* request) override;

    ::Unk_71024f9e28 mData;
};
KSYS_CHECK_SIZE_NX150(Unk_71024f9da0, 0x140);

Unk_71024f9da0::Unk_71024f9da0(sead::Heap* heap) : util::ManagedTask(heap) {}

// NON_MATCHING: request flags are copied by field instead of the native whole block.
void Unk_71024f9da0::prepareImpl_(util::TaskRequest* request) {
    auto* req = sead::DynamicCast<::Unk_71024f9bb8>(request);
    if (!req)
        return;
    mData._20 = req->_68;
    mData._18 = req->_60;
    mData._10 = req->_58;
    mData._c = req->_54;
    mData._8 = req->_50;
    // C++14 evaluation order: the original evaluates the destination first.
    mData._28.operator=(req->_70);
    mData._38 = req->_80;
    // C++14 evaluation order: the original evaluates the destination first.
    mData._40.operator=(req->_88);
    mData._50 = req->_98;
    mData._58 = req->_a0;
    mData._68 = req->_b0;
    mData._60 = req->_a8;
    // C++14 evaluation order: the original evaluates the destination first.
    mData._70.operator=(req->_b8);
    if (!getUserData())
        setUserData(&mData);
}

Unk_71024f9da0::~Unk_71024f9da0() = default;

}  // namespace ksys::res

Unk_71024f9e28::~Unk_71024f9e28() = default;

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
