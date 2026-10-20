#include "KingSystem/Resource/resUnk_71024F9D48.h"
#include "KingSystem/Resource/resTextureHandleMgr.h"
#include <codec/seadHashCRC32.h>
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resCounter.h"
#include "KingSystem/Resource/resArchiveWork.h"
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

namespace ksys::res {

// Complete FE126C produces the 0x20-byte native settings; FE04D0 reads only the span.
struct Unk_710260E880 {
    u8 _0[0x18];
    sead::TickSpan sleep;
};
KSYS_CHECK_SIZE_NX150(Unk_710260E880, 0x20);
extern Unk_710260E880 sUnk_710260E880;

Unk_71024f9a08::~Unk_71024f9a08() = default;

Unk_71024f9a50::~Unk_71024f9a50() = default;

// Empty-statement body as in upstream's GameDataFlagSelector destructor (96101229):
// the native FE02DC retains its vtable store, which a defaulted destructor drops.
Unk_71024f9a28::~Unk_71024f9a28() {
    ;
}

void Unk_71024f9a28::erase_() {
    mLeft = nullptr;
    mRight = nullptr;
}

void Unk_71024f9a08::sub_7100FE0E10() {
    if (mFlags.isOffBit(0)) {
        mFlags.setBit(0);
        if (sUnk_710260E858 && !sUnk_710260E858->repairTexture(this))
            mFlags.resetBit(0);
    }
}

void Unk_71024f9a08::sub_7100FE0E64() {
    mFlags.setBit(0);
    mTaskHandle.removeTaskFromQueue();
    mTaskHandle.finalize();
    if (sUnk_710260E858) {
        sUnk_710260E858->repairHandleForSync(this);
        mTaskHandle.finalize();
    }
}

// NON_MATCHING: clang lowers the native jump table to bit tests.
bool Unk_71024f9a08::sub_7100FE0ED0() const {
    switch (mStatus) {
    case 0:
    case 1:
        return false;
    case 3:
    case 6:
    case 7:
        if (!mFlags.isOnBit(1))
            return true;
        break;
    case 5:
        return true;
    }
    return mStatus == 2;
}

bool Unk_71024f9a08::sub_7100FE0F38() const {
    return mFlags.isOn(1);
}

sead::FileDevice* Unk_71024f9a08::sub_7100FE0E08() const {
    return mFileDevice;
}

void Unk_71024f9a08::sub_7100FE0850() {
    mFlags.reset(1);
}

bool Unk_71024f9a08::sub_7100FE0348(const sead::SafeString& path, bool reset,
                                      CompactedHeap* mipHeap, CompactedHeap* heap) {
    if (reset) {
        if (mTaskHandle.hasTask()) {
            mTaskHandle.removeTaskFromQueue();
            mTaskHandle.finalize();
        }
        if (mFlags.isOnBit(5)) {
            sub_7100FDDBD4(sub_7100FDDC24(&_1f8));
            mFlags.resetBit(5);
        }
        if (mMipAllocation.mData)
            mipHeap->x_21(&mMipAllocation);
        if (mAllocation.mData)
            heap->x_21(&mAllocation);
    }
    sub_7100FE04D0();
    mStatus = 1;
    sead::BufferedSafeString requester(_29a, sizeof(_29a));
    requester = path;
    mRequesterLength = requester.calcLength();
    mFlags.setDirect(0x80);
    mNode.key().mHash = sead::HashCRC32::calcHash(_29a, mRequesterLength);
    return true;
}

bool Unk_71024f9a08::sub_7100FE0C38(const LoadArg& arg) {
    return true;
}


// NON_MATCHING: structured event and allocation wait loops differ.
void Unk_71024f9a08::sub_7100FE04D0() {
    if (!mEvent.wait(sead::TickSpan::makeFromSeconds(10)))
        return;
    // Full FE04D0 tests allocation +10 bit 0; complete 12B8C10 sets that same bit.
    // The tagged heap address remains opaque and is never decoded here.
    if (mAllocation.mData && (mAllocation.mTaggedHeap & 1) == 0) {
        while (!mAllocation.sub_71012B8C10())
            sead::Thread::sleep(sUnk_710260E880.sleep);
    }
    if (mMipAllocation.mData) {
        while (!mMipAllocation.sub_71012B8C10())
            sead::Thread::sleep(sUnk_710260E880.sleep);
    }
}

// NON_MATCHING: structured dummy-texture handling and heap argument reloads change layout.
bool Unk_71024f9a08::sub_7100FE0584(const LoadArg& arg) {
    const bool dummy = arg._1 && sub_7100FDDC0C(arg.texture) == 1 &&
                       sub_7100FDDC14(arg.texture) == 1;
    if (dummy) {
        stubbedLogFunction();
        if (mStatus != 1)
            return true;
    } else {
        if (arg._1) {
            if (mAllocation.mData || mMipAllocation.mData) {
                stubbedLogFunction();
                mFlags.resetBit(0);
                if (mFlags.isOnBit(5)) {
                    sub_7100FDDBD4(sub_7100FDDC24(&_1f8));
                    mFlags.resetBit(5);
                }
                if (mMipAllocation.mData)
                    arg.mipHeap->x_21(&mMipAllocation);
                if (mAllocation.mData)
                    arg.heap->x_21(&mAllocation);
                sub_7100FE04D0();
            } else {
                if (mFlags.isOnBit(5)) {
                    sub_7100FDDBD4(sub_7100FDDC24(&_1f8));
                    mFlags.resetBit(5);
                    if (mMipAllocation.mData)
                        arg.mipHeap->x_21(&mMipAllocation);
                }
                if (mAllocation.mData)
                    arg.heap->x_21(&mAllocation);
                stubbedLogFunction();
            }
        }
        _158 = arg._2;
        _159 = 0;
        mPath.copy(arg.path.cstr());
        mFileDevice = arg.device;
        sub_7100FDDC04(arg.texture);
        mStatus = 1;
        if (arg.path.findIndex(".Tex2.") == -1) {
            mFlags.setBit(1);
            const TransferArg transfer{true, false, arg.texture, arg.heap};
            bool success = false;
            sub_7100FE09EC(&success, transfer);
            mStatus = success ? 4 : 2;
            _159 = success ? 0 : 3;
        } else {
            sub_7100FE0860(arg);
        }
        if (arg._1) {
            stubbedLogFunction();
            mCS.lock();
            for (auto& handle : mHandles)
                handle.sub_7100FE84D4();
            mCS.unlock();
        }
    }
    if (mMipAllocation.mData)
        mMipAllocation.sub_71012B8C7C();
    if (mAllocation.mData && mFlags.isOffBit(6))
        mAllocation.sub_71012B8C7C();
    mEvent.setSignal();
    return true;
}

// NON_MATCHING: reverse-search loop induction/branch layout and stack record allocation.
bool Unk_71024f9a08::sub_7100FE0860(const LoadArg& arg) {
    auto* texture = arg.texture;
    if (sub_7100FDDBFC(texture) == 0)
        mFlags.set(2);
    const TransferArg transfer{false, true, texture, arg.heap};
    bool success = false;
    sub_7100FE09EC(&success, transfer);
    if (!success) {
        mStatus = 5;
        _159 = 1;
        return true;
    }
    if (mStatus == 1) {
        mStatus = 6;
        _159 = 2;
        const s32 index = mPath.rfindIndex(".Tex2.");
        if (_158) {
            sead::FormatFixedSafeString<32> suffix(".Tex1.%u.bfres", _158);
            mPath.copyAt(index, suffix.cstr());
        } else {
            mPath.copyAt(index, ".Tex1");
        }
    }
    return true;
}

// NON_MATCHING: heap arguments reload at their uses and final byte stores reverse order.
void Unk_71024f9a08::sub_7100FE0C40(const UnloadArg& arg) {
    mFlags.setBit(3);
    if (mTaskHandle.hasTask()) {
        mTaskHandle.removeTaskFromQueue();
        mTaskHandle.finalize();
    }
    if (mFlags.isOnBit(5)) {
        sub_7100FDDBD4(sub_7100FDDC24(&_1f8));
        mFlags.resetBit(5);
    }
    if (mMipAllocation.mData)
        arg.mipHeap->x_21(&mMipAllocation);
    if (mAllocation.mData)
        arg.heap->x_21(&mAllocation);
    mFlags.reset(0x88);
    mStatus = 0;
}

// NON_MATCHING: final status byte stores and handle-list loop induction differ.
void Unk_71024f9a08::sub_7100FE10EC(CompactedHeap* heap) {
    stubbedLogFunction();
    mFlags.setBit(3);
    if (mMipAllocation.mData)
        heap->x_21(&mMipAllocation);
    mFlags.resetBit(3);
    if (mStatus == 4) {
        mStatus = 3;
        _159 = 3;
    } else if (mStatus == 8) {
        mStatus = 7;
        _159 = 2;
    }
    mCS.lock();
    for (auto* handle = mHandles.front(); handle; handle = mHandles.next(handle))
        handle->sub_7100FE84D4();
    mCS.unlock();
}

bool Unk_71024f9a08::sub_7100FE0CF8() const {
    return mStatus >= 6 && mStatus <= 8;
}

bool Unk_71024f9a08::sub_7100FE0D0C() const {
    return mAllocation.mData != nullptr;
}

bool Unk_71024f9a08::sub_7100FE0D1C() const {
    return mStatus == 4 || mStatus == 8;
}

void sub_7100FE0D38(Unk_71024f9a08* resource, Unk_71024F9D48* handle) {
    resource->mCS.lock();
    resource->mHandles.pushBack(handle);
    ++resource->_1a;
    resource->mCS.unlock();
}

u32 Unk_71024f9a08::sub_7100FE0DE8() const {
    return _1a;
}

void Unk_71024f9a08::sub_7100FE0EC8() {
    mTaskHandle.finalize();
}

sead::SafeString Unk_71024f9a08::sub_7100FE0DF0() const {
    return sead::SafeString(mPath.cstr());
}

sead::SafeString Unk_71024f9a08::sub_7100FE10A8() const {
    return sead::SafeString(_29a);
}

s64 Unk_71024f9a08::sub_7100FE10C0() const {
    return mAllocation.mData ? mAllocation.mSize : 0;
}

void Unk_71024f9a08::sub_7100FE10D8() {
    if (_1a)
        --_1a;
}

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

// Full native initializer FE2398 and loader FE1630 prove this separate factory.
static EntryFactory<Unk_710251A740> sUnk_710260E8A0;

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

}  // namespace ksys::res
