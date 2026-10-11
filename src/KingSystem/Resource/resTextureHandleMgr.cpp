#include "KingSystem/Resource/resTextureHandleMgr.h"
#include <codec/seadHashCRC32.h>
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
#include "KingSystem/Utils/Thread/TaskQueueBase.h"
#include "KingSystem/Utils/Thread/TaskQueueLock.h"
#include "KingSystem/Utils/Thread/ManagedTask.h"
#include "KingSystem/Resource/resResourceFileUtil.h"
#include "KingSystem/Utils/HeapUtil.h"
#include <filedevice/seadFileDeviceMgr.h>
#include <thread/seadThread.h>
#include <resource/seadParallelSZSDecompressor.h>
#include <nn/g3d/ResFile.h>

Unk_71024f9bb8::~Unk_71024f9bb8() = default;

namespace ksys::res {

Unk_71024f9b08::~Unk_71024f9b08() = default;

void TextureHandleMgr::ValidateArg::setPath(const sead::SafeString& path) {
    mPath = path;
    const s32 length = path.calcLength();
    if (length >= 1)
        mHash = sead::HashCRC32::calcHash(path.cstr(), length);
}

void TextureHandleMgr::ValidateArg::setHash(u32 hash) {
    mHash = hash;
}

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
    mData._9 = req->_51;
    mData._a = req->_52;
    mData._b = req->_53;
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

// NON_MATCHING: native request initialization, context lifetimes and failure cleanup differ.
void Unk_71024f9a70::sub_7100FE1630(LoadStatus* status, const LoadParams& params) {
    TempResourceLoader loader;
    TempResourceLoader::InitArg init_arg{nullptr};
    ResourceMgrTask::instance()->initTempResourceLoader(&loader, init_arg);
    u32 resource_size = 0;
    if (ResourceMgrTask::instance()->returnTrue()) {
        resource_size = ResourceMgrTask::instance()->getResourceSize(params.mPath, nullptr);
    } else {
        sead::FixedStringBuilder<129> path;
        path.copy(params.mPath.cstr());
        ResourceMgrTask::instance()->addSExtensionPrefix(path);
        if (!ResourceMgrTask::instance()->getUncompressedSize(&resource_size, path.cstr(),
                                                             params.mFileDevice))
            stubbedLogFunction();
    }
    auto* thread = sead::ThreadMgr::instance()->getCurrentThread();
    const bool resource_thread =
        thread == ResourceMgrTask::instance()->getResourceMemoryThread() ||
        thread == ResourceMgrTask::instance()->getResourceLoadingThread();
    const u32 work_size = loader.getWorkHeapSize();
    if (resource_thread || work_size < resource_size) {
        stubbedLogFunction();
        if (!resource_thread)
            sead::FormatFixedSafeString<256>("↓↓↓\nテクスチャアーカイブサイズ : %u MB\n↑↑↑\n",
                                             resource_size >> 20);
        Unk_71024f9b08 context;
        context.mFileDevice = params.mFileDevice;
        context.mPath = params.mPath;
        ResourceMgrTask::DirectLoadArg arg;
        if (ResourceMgrTask::instance()->returnTrue())
            arg.heap = ResourceMgrTask::instance()->getArenaForResourceL()->getHeap();
        else
            arg.heap = util::getDebugHeap();
        arg.req._21 = false;
        arg.req._22 = true;
        arg.req._28 = false;
        arg.req.mPath = params.mPath;
        arg.req.mEntryFactory = &sUnk_710260E8A0;
        arg.req.mAocFileDevice = params.mFileDevice;
        arg.req._20 = false;
        arg.req.mLoadDataAlignment = 0x2000;
        arg.req.mRequester = params.mPath;
        arg.req._68 = &context;
        mResource = ResourceMgrTask::instance()->load(arg);
        if (!mResource) {
            status->success = false;
            return;
        }
    } else {
        Unk_71024f9b08 context;
        context.mFileDevice = params.mFileDevice;
        context.mPath = params.mPath;
        TempResourceLoader::LoadArg arg;
        arg.load_req._21 = false;
        arg.load_req._22 = true;
        arg.load_req._26 = params._0;
        arg.load_req.mLoadDataAlignment = 0x2000;
        arg.load_req._8 = true;
        arg.load_req.mLoadCompressed = true;
        arg.load_req._28 = false;
        arg.load_req.mEntryFactory = &sUnk_710260E8A0;
        arg.load_req.mAocFileDevice = params.mFileDevice;
        arg.load_req.mPath = params.mPath;
        arg.load_req.mRequester = params.mPath;
        arg.load_req._68 = &context;
        auto* loaded = sead::DynamicCast<sead::DirectResource>(loader.load(arg));
        if (!loaded) {
            stubbedLogFunction();
            status->success = false;
            status->_1 = loader.getHandleStatus() != Handle::Status::_1;
            return;
        }
        SimplePackedLoadRequest request;
        request._8 = true;
        request.mRequester = params.mPath;
        request.mLaneId = 2;
        request.mPack = loader.getHandle();
        if (!mHandle.load(params.mPath, &request)) {
            status->success = false;
            status->_1 = loader.getHandleStatus() != Handle::Status::_1;
            return;
        }
    }
    auto* resource = mResource ? mResource : mHandle.getResourceUnchecked();
    mResFile = static_cast<Unk_710251A740*>(resource)->_38;
    if (loader.getHandleFileDevice())
        mFileDevice = loader.getHandleFileDevice();
    else
        mFileDevice = sead::FileDeviceMgr::instance()->getDefaultFileDevice();
    status->success = true;
    status->_1 = true;
}

// NON_MATCHING: request construction and binary-search comparison branch layout.
bool Unk_71024f9a70::sub_7100FE1AFC(const TextureLoadArg& arg) {
    auto* texture = agl::g3d::ResFile::sub_7100B33BF0(mResFile, arg.mName.cstr());
    bool success;
    if (texture) {
        const u32 hash = sead::HashCRC32::calcStringHash(texture->GetName());
        const s32 index = mTextureFlags.binarySearch<u32>(hash, [](const TextureFlag& item,
                                                                  const u32& key) -> s32 {
            if (item.hash > key)
                return 1;
            if (item.hash < key)
                return -1;
            return 0;
        });
        u32 flags = 0;
        if (index != -1)
            flags = mTextureFlags[index].flag;
        Unk_71024f9a90 request;
        request._12 = arg._0;
        request._11 = arg._1;
        request.mRequester = mPath;
        request.mFileDevice = mFileDevice;
        request.mCallback = arg.mCallback;
        request.mTexture = texture;
        request.mTextureFlags = flags;
        success = arg.mHandle->sub_7100FE8074(&request);
    } else {
        Unk_71024f9ad8 request;
        request.mCallback = arg.mCallback;
        request.mPath = arg.mName;
        if (!arg.mHandle->sub_7100FE8074(&request)) {
            stubbedLogFunction();
            return false;
        }
        success = true;
    }
    if (arg.mHandle->sub_7100FE8330() == 4 || arg.mHandle->sub_7100FE8330() == 3)
        stubbedLogFunction();
    return success;
}

// Full native initializer FE2398 and loader FE1630 prove this separate factory.
// NON_MATCHING: namespace linkage uses GOT addressing instead of the native direct address.
EntryFactory<Unk_710251A740> sUnk_710260E8A0;

TextureHandleMgr* TextureHandleMgr::sInstance;
TextureHandleMgr* sUnk_710260E858;

void sub_7100FE11CC(TextureHandleMgr* manager) {
    sUnk_710260E858 = manager;
}

// Complete FE4CF4 supplies converted textures; 12A5304 consumes the fallback.
nn::gfx::ResTexture* sUnk_710260E868;
const nn::util::BinaryBlockHeader* sUnk_710260E870;
const nn::util::BinaryBlockHeader* sUnk_710260E878;
nn::gfx::ResTexture* sUnk_710260E860;

void sub_7100FE11F0(nn::gfx::ResTexture* texture, nn::gfx::ResTexture* fallback) {
    sUnk_710260E868 = texture;
    sUnk_710260E870 = sub_7100FDDBD8(texture);
    sUnk_710260E878 = sub_7100FDDBD8(texture);
    sUnk_710260E860 = fallback;
}

nn::gfx::ResTexture* sub_7100FE124C() {
    return sUnk_710260E860;
}

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

// NON_MATCHING: bool fields are copied separately instead of the native eight-byte block.
bool TextureHandleMgr::validateUser(const ValidateArg& arg) {
    Unk_71024f9bb8 request;
    request.mLaneId = 4;
    request.mThread = _50;
    request.mDelegate = &_178;
    request._50 = arg._0;
    request._51 = arg._1;
    request._52 = arg._2;
    request._53 = arg._3;
    request._54 = arg._4;
    request._58 = arg.mTexture;
    request._60 = arg.mHandle;
    request._68 = arg.mFileDevice;
    request._70 = arg.mRequester;
    request._80 = arg.mTextureFlags;
    request._88 = arg.mPath;
    request._98 = arg.mHash;
    request.mName = "Texture::ValidateUser";
    util::ManagedTaskHandle handle;
    util::TaskMgrRequest manager_request;
    manager_request.request = &request;
    manager_request.handle = &handle;
    _48->submitRequest(manager_request);
    if (handle.getStatus() == util::ManagedTaskHandle::Status::TaskRemoved) {
        stubbedLogFunction();
        arg.mHandle->sub_7100FE8328(4);
        return false;
    }
    return handle.didTaskCompleteSuccessfully();
}

// NON_MATCHING: status is retained in a 32-bit register rather than the native 64-bit copy.
bool TextureHandleMgr::invalidateUser(const InvalidateArg& arg) {
    auto* handle = arg._8;
    auto* resource = handle->_28;
    const u32 status = handle->sub_7100FE8330();
    handle->sub_7100FE8428();
    Unk_71024f9bb8 request;
    request.mHasHandle = arg._1;
    request.mSynchronous = arg._1;
    request.mLaneId = 5;
    request.mThread = _50;
    request.mDelegate = &_198;
    request._a0 = resource;
    request.mName = "Texture::InvalidateUser";
    util::TaskMgrRequest manager_request;
    manager_request.request = &request;
    if (arg._0) {
        _48->submitRequest(manager_request);
        return true;
    }
    if (_48->trySubmitRequest(manager_request))
        return true;
    handle->sub_7100FE8474(resource, status);
    return false;
}

// NON_MATCHING: native request setup and loader cleanup branch layout differ.
void TextureHandleMgr::repairExecute(util::TaskPostRunResult* result,
                                     const util::TaskPostRunContext& context) {
    auto* data = sead::DynamicCast<::Unk_71024f9e28>(
        static_cast<util::TaskData*>(context.mUserData));
    if (!data)
        return;
    auto* resource = static_cast<Unk_71024f9a08*>(data->_60);
    if (context.mCancelled) {
        if (mLoader.isLoading() || mLoader.isSuccess())
            mLoader.unload();
        resource->sub_7100FE0EC8();
        resource->sub_7100FE0850();
        return;
    }
    const auto path = resource->sub_7100FE0DF0();
    bool repair;
    if (path.findIndex(".Tex1.") != -1) {
        auto* queue = _50->getTaskQueue();
        repair = (!queue || queue->countTasksInLane(1) < 1) && mFlags.isOnAll(3);
    } else {
        repair = mFlags.isOnBit(0);
    }
    const bool can_submit = repair && resource->sub_7100FE0ED0();
    if (mLoader.isLoading() || mLoader.isSuccess()) {
        if (can_submit) {
            Unk_71024f9bb8 request;
            request.mName = resource->sub_7100FE0CF8() ? "toTex1Execute" : "RepairExecute";
            request.mSynchronous = false;
            request.mLaneId = 3;
            request.mThread = _50;
            request.mDelegate = &_298;
            request.mPostRunCallback = &_218;
            request.mRemoveCallback = &_258;
            request._a8 = resource;
            util::TaskMgrRequest manager_request;
            manager_request.task = static_cast<util::ManagedTask*>(context.mTask);
            manager_request.request = &request;
            manager_request.handle = &resource->mTaskHandle;
            const bool submitted = _48->trySubmitRequest(manager_request);
            if (!submitted) {
                resource->sub_7100FE0EC8();
                resource->sub_7100FE0850();
            }
            result->setResult(submitted);
            return;
        }
        mLoader.unload();
    }
    resource->sub_7100FE0EC8();
    resource->sub_7100FE0850();
}

// NON_MATCHING: native retains the address of the task data repair fields.
void TextureHandleMgr::invoked7(util::TaskPostRunResult* result,
                               const util::TaskPostRunContext& context) {
    auto* data = sead::DynamicCast<::Unk_71024f9e28>(
        static_cast<util::TaskData*>(context.mUserData));
    if (!data)
        return;
    if (!mLoader.isLoading() && !mLoader.isSuccess())
        return;
    Unk_71024f9bb8 request;
    request.mSynchronous = false;
    request.mLaneId = 3;
    request.mThread = _50;
    request.mDelegate = &_1d8;
    request.mPostRunCallback = &_238;
    request._a8 = data->_60;
    request._b0 = data->_68;
    request._b8 = data->_70;
    request.mName = "RepairHandles(HighPrio)";
    context.mTask->submitRequest(request);
    result->setResult(true);
}

void TextureHandleMgr::invoked8(const util::TaskRemoveCallbackContext& context) {
    auto* data = sead::DynamicCast<::Unk_71024f9e28>(
        static_cast<util::TaskData*>(context.mUserData));
    if (!data)
        return;
    auto* resource = static_cast<Unk_71024f9a08*>(data->_60);
    resource->sub_7100FE0EC8();
    resource->sub_7100FE0850();
}

void TextureHandleMgr::invoked9(const util::TaskRemoveCallbackContext& context) {
    auto* data = sead::DynamicCast<::Unk_71024f9e28>(
        static_cast<util::TaskData*>(context.mUserData));
    if (!data)
        return;
    auto* resource = static_cast<Unk_71024f9a08*>(data->_60);
    mLoader.unload();
    resource->sub_7100FE0EC8();
    resource->sub_7100FE0850();
}

// NON_MATCHING: typed hash-key lifetime and structured retry / eviction change code layout.
bool TextureHandleMgr::x_0(nn::g3d::ResFile* file, bool tex1, Unk_71024f9a08** resource) {
    const s32 texture_count = agl::g3d::ResFile::GetTextureCount(file);
    if (texture_count == 0) {
        stubbedLogFunction();
        return false;
    }
    mCS.lock();
    bool matched = false;
    for (s32 i = 0; i < texture_count; ++i) {
        const u32 hash = sead::HashCRC32::calcStringHash(agl::g3d::ResFile::GetTextureName(file, i));
        mCS.lock();
        Unk_71024f9a50 key;
        key.mHash = hash;
        auto* node = mResourceMap.find(key);
        auto* found = node ? node->key().mOwner : nullptr;
        mCS.unlock();
        matched |= found == *resource;
        if (!found || !found->sub_7100FE0ED0())
            continue;
        auto* counter = mHeapCounter;
        counter->incrementRef();
        Unk_71024f9a08::LoadArg arg;
        // Native FE6134 sets only byte 0; FE0C38 does not read bytes 1 / 2.
        arg._0 = tex1;
        arg.device = nullptr;
        arg.mipHeap = static_cast<CompactedHeap*>(counter->getData());
        arg.texture = agl::g3d::ResFile::GetTexture(file, i);
        arg.heap = mTextureHeap;
        bool changed = false;
        s32 removed = 0;
        while (found->sub_7100FE0ED0() && found->sub_7100FE0C38(arg)) {
            if (!found->sub_7100FE0ED0()) {
                changed = true;
                continue;
            }
            mCS.lock();
            auto* pending = mPendingRemoval.popFront();
            if (!pending) {
                mCS.unlock();
                break;
            }
            if (pending == *resource) {
                pending->sub_7100FE0EC8();
                pending->sub_7100FE0850();
                stubbedLogFunction();
            } else if (pending == found) {
                stubbedLogFunction();
            }
            x(pending);
            if (pending == *resource) {
                *resource = nullptr;
                mHeapCounter->decrementRef();
                mCS.unlock();
                mCS.unlock();
                return true;
            }
            mCS.unlock();
            if (pending == found)
                break;
            ++removed;
        }
        if (removed > 0)
            stubbedLogFunction();
        mHeapCounter->decrementRef();
        if (changed)
            found->sub_7100FE0ED0();
    }
    mCS.unlock();
    return matched;
}

// NON_MATCHING: resource reloads around the diagnostic string arguments differ.
bool TextureHandleMgr::invoked6(void* user_data) {
    auto* data = sead::DynamicCast<::Unk_71024f9e28>(static_cast<util::TaskData*>(user_data));
    if (!data)
        return false;
    auto* resource = static_cast<Unk_71024f9a08*>(data->_60);
    const s32 tex1_index = resource->sub_7100FE0DF0().findIndex(".Tex1.");
    if (tex1_index != -1) {
        auto* queue = _50->getTaskQueue();
        if (queue && queue->countTasksInLane(1) > 0)
            return false;
        if (!mFlags.isOnAll(3)) {
            mLoader.unload();
            return false;
        }
    } else if (!mFlags.isOnBit(0)) {
        mLoader.unload();
        return false;
    }
    if (!resource->sub_7100FE0ED0()) {
        mLoader.unload();
        return true;
    }
    const auto load_path = resource->sub_7100FE0DF0();
    Unk_71024f9b08 context;
    context.mFileDevice = resource->sub_7100FE0E08();
    context.mPath = load_path;
    if (!mLoader.getResourceForLoadRequest(&context)) {
        mLoader.checkLoadStatus();
        return false;
    }
    auto* loaded = static_cast<Unk_710251A740*>(mLoader.getResource());
    const bool success = x_0(loaded->_38, tex1_index != -1, &resource);
    mLoader.unload();
    if (!success && resource) {
        sead::FormatFixedSafeString<256> message(
            "↓↓↓\nベーステクスチャ名               : %s\n修復に用いる予定だったアーカイブ : %s\n↑↑↑\n",
            resource->sub_7100FE10A8().cstr(), resource->sub_7100FE0DF0().cstr());
    }
    return true;
}

// NON_MATCHING: the heap counter and argument fields reload separately.
// The existing TreeMapImpl erase / eraseMin instantiations at FE6970 / FE6CE8
// also retain an extra comparison and differ in the recursive result-store schedule.
void TextureHandleMgr::x(Unk_71024f9a08* resource) {
    mCS.lock();
    mResourceMap.erase(resource->mNode.key());
    mResources.erase(resource);
    mCS.unlock();
    mHeapCounter->incrementRef();
    const Unk_71024f9a08::UnloadArg arg{mTextureHeap, static_cast<CompactedHeap*>(mHeapCounter->getData())};
    resource->sub_7100FE0C40(arg);
    mHeapCounter->decrementRef();
    if (!mFreeResources.isFull())
        mFreeResources.emplaceBack(resource);
}

bool TextureHandleMgr::invoked2(void*) {
    mCS.lock();
    stubbedLogFunction();
    while (!mPendingRemoval.isEmpty()) {
        auto* resource = mPendingRemoval.popFront();
        if (!resource)
            break;
        x(resource);
    }
    stubbedLogFunction();
    mCS.unlock();
    return true;
}

// NON_MATCHING: typed key lifetimes and structured allocation / retry paths alter code layout.
bool TextureHandleMgr::invoked3(void* user_data) {
    auto* data = sead::DynamicCast<::Unk_71024f9e28>(static_cast<util::TaskData*>(user_data));
    if (!data)
        return false;
    auto* handle = static_cast<Unk_71024F9D48*>(data->_18);
    mCS.lock();
    const u32 hash = data->_c ? data->_50 : sead::HashCRC32::calcStringHash(
        static_cast<nn::gfx::ResTexture*>(data->_10)->GetName());
    mCS.lock();
    Unk_71024f9a50 key;
    key.mHash = hash;
    auto* node = mResourceMap.find(key);
    auto* resource = node ? node->key().mOwner : nullptr;
    mCS.unlock();
    if (!resource && data->_c) {
        mCS.unlock();
        return false;
    }
    bool reset = false;
    bool load = false;
    if (resource) {
        if (resource->sub_7100FE0DE8() == 0) {
            Unk_71024f9a08** pending = nullptr;
            for (auto* item = mPendingRemoval.front(); item; item = mPendingRemoval.next(item)) {
                if (*item == resource) {
                    pending = item;
                    break;
                }
            }
            mPendingRemoval.erase(pending);
        }
        load = data->_a;
    } else {
        resource = mFreeResources.popFront();
        if (!resource) {
            resource = mPendingRemoval.popFront();
            if (!resource) {
                stubbedLogFunction();
                mCS.unlock();
                return false;
            }
            mCS.lock();
            mResourceMap.erase(resource->mNode.key());
            mResources.erase(resource);
            mCS.unlock();
            reset = true;
        }
        sead::SafeString path = data->_c ? data->_40 :
            data->_10 ? sead::SafeString(static_cast<nn::gfx::ResTexture*>(data->_10)->GetName()) :
                        sead::SafeString::cEmptyString;
        auto* counter = mHeapCounter;
        counter->incrementRef();
        resource->sub_7100FE0348(path, reset, static_cast<CompactedHeap*>(counter->getData()),
                               mTextureHeap);
        mHeapCounter->decrementRef();
        mCS.lock();
        if (resource->mNode.key().mOwner) {
            mResources.pushBack(resource);
            mResourceMap.insert(&resource->mNode);
        }
        mCS.unlock();
        load = true;
    }
    sub_7100FE0D38(resource, handle);
    handle->sub_7100FE8414(resource);
    mCS.unlock();
    if (!load)
        return true;
    auto* counter = mHeapCounter;
    counter->incrementRef();
    auto* mip_heap = static_cast<CompactedHeap*>(counter->getData());
    Unk_71024f9a08::LoadArg arg;
    arg._0 = data->_9;
    arg._1 = data->_a;
    arg._2 = 0;
    arg.texture = static_cast<nn::gfx::ResTexture*>(data->_10);
    arg.heap = mTextureHeap;
    arg.mipHeap = mip_heap;
    if (data->_c) {
        arg.path = "_";
        arg.device = nullptr;
    } else {
        arg.path = data->_28;
        arg.device = static_cast<sead::FileDevice*>(data->_20);
        arg._2 = data->_38;
    }
    bool force = reset || data->_a;
    s32 removed = 0;
    while (true) {
        if (!force && resource->sub_7100FE0D0C())
            break;
        resource->sub_7100FE0584(arg);
        force = false;
        if (resource->sub_7100FE0D0C())
            continue;
        mCS.lock();
        auto* pending = mPendingRemoval.popFront();
        if (!pending) {
            stubbedLogFunction();
            mCS.unlock();
            break;
        }
        x(pending);
        ++removed;
        sead::SafeString path = data->_c ? data->_40 :
            data->_10 ? sead::SafeString(static_cast<nn::gfx::ResTexture*>(data->_10)->GetName()) :
                        sead::SafeString::cEmptyString;
        resource->sub_7100FE0348(path, true, mip_heap, mTextureHeap);
        mCS.unlock();
    }
    if (removed > 0)
        stubbedLogFunction();
    mHeapCounter->decrementRef();
    return true;
}

bool TextureHandleMgr::doCalc() {
    if (mTextureHeap->getState() == 3) {
        const s32 available = mTextureHeap->_5dbc;
        if (available >= 0 && available < 15 * 1024 * 1024) {
            u64 free_size = available;
            mCS.lock();
            while (!mPendingRemoval.isEmpty()) {
                auto* resource = mPendingRemoval.popFront();
                if (!resource)
                    break;
                free_size += resource->sub_7100FE10C0();
                x(resource);
                if (free_size >= 15 * 1024 * 1024)
                    break;
            }
            mCS.unlock();
        }
    }
    s32 count = 0;
    if (mFlags.isOffBit(0)) {
        mFlags2.resetBit(2);
    } else if (_98.diffToNow().toSeconds() >= 2) {
        _98.setNow();
        x_1(&count);
    }
    return true;
}

// NON_MATCHING: structured archive loading and diagnostic / request lifetimes differ.
bool TextureHandleMgr::bfres_file_stuff(void* user_data) {
    auto* data = sead::DynamicCast<::Unk_71024f9e28>(static_cast<util::TaskData*>(user_data));
    if (!data)
        return false;
    auto* resource = static_cast<Unk_71024f9a08*>(data->_60);
    const bool tex1 = resource->sub_7100FE0DF0().findIndex(".Tex1.") != -1;
    if (tex1) {
        auto* queue = _50->getTaskQueue();
        if (queue && queue->countTasksInLane(1) > 0)
            return false;
        if (mFlags.isOffBit(0) || mFlags.isOffBit(1))
            return false;
    } else if (mFlags.isOffBit(0)) {
        return false;
    }
    if (!resource->sub_7100FE0ED0())
        return true;
    auto* counter = mHeapCounter;
    counter->incrementRef();
    auto* heap = static_cast<CompactedHeap*>(counter->getData());
    u32 size = ResourceMgrTask::instance()->getResourceSize(resource->sub_7100FE0DF0(), nullptr);
    if (size == 0)
        ResourceMgrTask::instance()->getUncompressedSize(&size, resource->sub_7100FE0DF0(),
                                                        resource->sub_7100FE0E08());
    void* buffer = nullptr;
    nn::g3d::ResFile* file = nullptr;
    if (mArchiveWork->getHeapSize() < size) {
        sead::FixedStringBuilder<256> path;
        path.copy(resource->sub_7100FE0DF0().cstr());
        const s32 extension = path.rfindIndex(".bfres");
        if (extension != -1)
            path.copyAtWithTerminate(extension, ".sbfres");
        const bool compressed = path.findIndex(".sbfres") != -1;
        buffer = heap->x_17(size, -0x2000, 0, true);
        auto* device = resource->sub_7100FE0E08();
        if (!device)
            device = sead::FileDeviceMgr::instance()->getDefaultFileDevice();
        if (compressed) {
            auto* decompressor = ResourceMgrTask::instance()->getSzsDecompressor();
            sead::ResourceMgr::LoadArg arg;
            arg.path = path.cstr();
            arg.load_data_buffer = static_cast<u8*>(buffer);
            arg.load_data_buffer_size = size;
            arg.device = device;
            arg.assert_on_alloc_fail = false;
            decompressor->tryDecompFromDevice(arg, nullptr, nullptr, nullptr, nullptr);
            ResourceMgrTask::instance()->unlockSzsDecompressorCS();
        } else {
            sead::FileDevice::LoadArg arg;
            arg.path = path.cstr();
            arg.buffer = static_cast<u8*>(buffer);
            arg.buffer_size = size;
            arg.check_read_entire_file = false;
            device->tryLoad(arg);
        }
        if (!buffer) {
            resource->sub_7100FE0850();
            mHeapCounter->decrementRef();
            return false;
        }
        file = nn::g3d::ResFile::ResCast(buffer);
    } else {
        const auto path = resource->sub_7100FE0DF0();
        if (!mLoader.isLoading()) {
            TempResourceLoader::LoadArg arg;
            arg.load_req.mLoadDataAlignment = 0x2000;
            arg.load_req._21 = false;
            arg.load_req._22 = true;
            arg.load_req._26 = true;
            arg.load_req._8 = true;
            arg.load_req.mLoadCompressed = true;
            arg.load_req._28 = false;
            arg.load_req.mEntryFactory = &sUnk_710260EA08;
            arg.load_req.mAocFileDevice = nullptr;
            arg.load_req.mPath = path;
            mLoader.requestLoad(arg);
        }
        Unk_71024f9b08 context;
        context.mFileDevice = resource->sub_7100FE0E08();
        context.mPath = path;
        if (!mLoader.getResourceForLoadRequest(&context)) {
            mLoader.checkLoadStatus();
            mHeapCounter->decrementRef();
            return false;
        }
        file = static_cast<Unk_710251A740*>(mLoader.getResource())->_38;
    }
    const bool matched = x_0(file, tex1, &resource);
    mLoader.unload();
    if (resource && !matched) {
        const auto name = resource->sub_7100FE10A8();
        const auto path = resource->sub_7100FE0DF0();
        sead::FormatFixedSafeString<256>(
            "↓↓↓\nベーステクスチャ名               : %s\n修復に用いる予定だったアーカイブ : %s\n↑↑↑\n",
            name.cstr(), path.cstr());
    }
    if (buffer)
        heap->x_19(buffer, true);
    mHeapCounter->decrementRef();
    return true;
}

// NON_MATCHING: structured archive loading and request / context lifetimes differ.
bool TextureHandleMgr::bfres_file_stuff_2(void* user_data) {
    auto* data = sead::DynamicCast<::Unk_71024f9e28>(static_cast<util::TaskData*>(user_data));
    if (!data)
        return false;
    sead::SafeString path = data->_70;
    auto* device = static_cast<sead::FileDevice*>(data->_68);
    if (!device)
        device = sead::FileDeviceMgr::instance()->getDefaultFileDevice();
    auto* counter = mHeapCounter;
    counter->incrementRef();
    auto* heap = static_cast<CompactedHeap*>(counter->getData());
    u32 size = ResourceMgrTask::instance()->getResourceSize(path, nullptr);
    if (size == 0)
        ResourceMgrTask::instance()->getUncompressedSize(&size, path, device);
    void* buffer = nullptr;
    nn::g3d::ResFile* file = nullptr;
    if (mArchiveWork->getHeapSize() < size) {
        sead::FixedStringBuilder<256> archive_path;
        archive_path.copy(path.cstr());
        const s32 extension = archive_path.rfindIndex(".bfres");
        if (extension != -1)
            archive_path.copyAtWithTerminate(extension, ".sbfres");
        const bool compressed = archive_path.findIndex(".sbfres") != -1;
        buffer = heap->x_17(size, -0x2000, 0, true);
        if (compressed) {
            auto* decompressor = ResourceMgrTask::instance()->getSzsDecompressor();
            sead::ResourceMgr::LoadArg arg;
            arg.path = archive_path.cstr();
            arg.load_data_buffer = static_cast<u8*>(buffer);
            arg.load_data_buffer_size = size;
            arg.device = device;
            arg.assert_on_alloc_fail = false;
            decompressor->tryDecompFromDevice(arg, nullptr, nullptr, nullptr, nullptr);
            ResourceMgrTask::instance()->unlockSzsDecompressorCS();
        } else {
            sead::FileDevice::LoadArg arg;
            arg.path = archive_path.cstr();
            arg.buffer = static_cast<u8*>(buffer);
            arg.buffer_size = size;
            arg.check_read_entire_file = false;
            device->tryLoad(arg);
        }
        if (!buffer) {
            mHeapCounter->decrementRef();
            return false;
        }
        file = nn::g3d::ResFile::ResCast(buffer);
    } else {
        if (!mLoader.isLoading()) {
            TempResourceLoader::LoadArg arg;
            arg.load_req.mLoadDataAlignment = 0x2000;
            arg.load_req._21 = false;
            arg.load_req._22 = true;
            arg.load_req._26 = true;
            arg.load_req._8 = true;
            arg.load_req.mLoadCompressed = true;
            arg.load_req._28 = false;
            arg.load_req.mEntryFactory = &sUnk_710260EA08;
            arg.load_req.mAocFileDevice = nullptr;
            arg.load_req.mPath = path;
            mLoader.requestLoad(arg);
        }
        Unk_71024f9b08 context;
        context.mFileDevice = device;
        context.mPath = path;
        if (!mLoader.getResourceForLoadRequest(&context)) {
            mLoader.checkLoadStatus();
            mHeapCounter->decrementRef();
            return false;
        }
        file = static_cast<Unk_710251A740*>(mLoader.getResource())->_38;
    }
    Unk_71024f9a08* resource = nullptr;
    x_0(file, path.findIndex(".Tex1.") != -1, &resource);
    mLoader.unload();
    if (buffer)
        heap->x_19(buffer, true);
    mHeapCounter->decrementRef();
    return true;
}

// NON_MATCHING: status-query inlining and resource-list loop induction differ.
void TextureHandleMgr::x_1(s32* count) {
    mCS.lock();
    if (*count < 100) {
        util::TaskQueueLock queue_lock;
        _50->lock(&queue_lock);
        s32 repaired = 0;
        for (auto* resource = mResources.front(); resource; resource = mResources.next(resource)) {
            if (!resource->sub_7100FE0ED0() || !sub_7100FE0F14(resource))
                continue;
            ++*count;
            if (repaired == 0) {
                stubbedLogFunction();
                stubbedLogFunction();
                _50->getTaskQueue()->cancelTasks(0);
                stubbedLogFunction();
            }
            ++repaired;
            if (!resource->sub_7100FE0F38()) {
                resource->sub_7100FE0E10();
                resource->sub_7100FE0F38();
            }
            if (*count >= 100)
                break;
        }
        if (repaired == 0) {
            mFlags2.resetBit(2);
        } else {
            stubbedLogFunction();
            if (mFlags2.isOffBit(2)) {
                mTickTime.setNow();
                mFlags2.setBit(2);
            }
        }
    }
    mCS.unlock();
}

// NON_MATCHING: the status query is inlined and the u16 result is masked.
bool TextureHandleMgr::invoked4(void* data) {
    auto* task_data = sead::DynamicCast<::Unk_71024f9e28>(static_cast<util::TaskData*>(data));
    if (!task_data)
        return false;
    auto* resource = static_cast<Unk_71024f9a08*>(task_data->_58);
    if (!resource)
        return false;
    mCS.lock();
    resource->sub_7100FE10D8();
    const u16 count = resource->sub_7100FE0DE8();
    mCS.unlock();
    if (count == 0) {
        if (sub_7100FE0F14(resource)) {
            mCS.lock();
            x(resource);
            mCS.unlock();
        } else if (!mPendingRemoval.isFull()) {
            mPendingRemoval.emplaceBack(resource);
        }
    }
    return true;
}

bool TextureHandleMgr::invoked5(void*) {
    mCS.lock();
    if (mResources.begin() != mResources.end()) {
        s32 count = 0;
        for (auto& resource : mResources) {
            if (resource.sub_7100FE0ED0()) {
                resource.sub_7100FE0E64();
                ++count;
            }
        }
        if (count > 0)
            stubbedLogFunction();
    }
    mCS.unlock();
    return true;
}

// NON_MATCHING: request initialization and branch argument setup are scheduled differently.
bool TextureHandleMgr::repairTexture(Unk_71024f9a08* resource) {
    Unk_71024f9bb8 request;
    request.mLaneId = !resource->sub_7100FE0CF8();
    request.mName = request.mLaneId ? "RepairTexture" : "toTex1";
    request.mSynchronous = false;
    request.mThread = _50;
    request.mDelegate = &_1b8;
    request.mPostRunCallback = &_218;
    request.mRemoveCallback = &_278;
    request._a8 = resource;
    util::TaskMgrRequest manager_request;
    manager_request.request = &request;
    manager_request.handle = &resource->mTaskHandle;
    return _48->trySubmitRequest(manager_request);
}

// NON_MATCHING: request initialization stores are scheduled differently.
void TextureHandleMgr::repairHandleForSync(Unk_71024f9a08* resource) {
    Unk_71024f9bb8 request;
    request.mLaneId = 6;
    request.mThread = _50;
    request.mDelegate = &_1b8;
    request.mPostRunCallback = &_218;
    request.mRemoveCallback = &_278;
    request._a8 = resource;
    request.mName = "RepairHandle(ForSync)";
    util::TaskMgrRequest manager_request;
    manager_request.request = &request;
    manager_request.handle = &resource->mTaskHandle;
    _48->submitRequest(manager_request);
    stubbedLogFunction();
}

// NON_MATCHING: request initialization stores are scheduled differently.
void TextureHandleMgr::repairAllHandlesForSync() {
    Unk_71024f9bb8 request;
    request.mLaneId = 6;
    request.mThread = _50;
    request.mDelegate = &_1f8;
    request.mName = "RepairAllHandles(ForSync)";
    util::TaskMgrRequest manager_request;
    manager_request.request = &request;
    _48->submitRequest(manager_request);
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

// NON_MATCHING: makeTaskType_ inlines the texture ManagedTask constructor.
// Complete FE4C14 and FE6798, independently called by FE2890, instantiate the
// existing task manager factory for the 0x140-byte texture ManagedTask.
template void ksys::util::TaskMgr::initAndCheckType<ksys::res::Unk_71024f9da0>(
    s32 num_tasks, sead::Heap* heap);
