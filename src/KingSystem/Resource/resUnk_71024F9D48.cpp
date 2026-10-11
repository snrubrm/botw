#include "KingSystem/Resource/resUnk_71024F9D48.h"
#include "KingSystem/Resource/resBfRes.h"
#include "KingSystem/Resource/resTextureHandleMgr.h"
#include "KingSystem/Resource/resResourceFileUtil.h"
#include "KingSystem/Resource/resSystem.h"
#include <thread/seadAtomic.h>

namespace ksys::res {

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

bool Unk_71024f9a08::sub_7100FE0C38(const LoadArg& arg) {
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

u16 Unk_71024f9a08::sub_7100FE0DE8() const {
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

// FE852C receives the fallback ResTexture from TextureHandleMgr::xx; FE83EC consumes it.
nn::gfx::ResTexture* sUnk_710260EAD0;

void sub_7100FE852C(nn::gfx::ResTexture* texture) {
    sUnk_710260EAD0 = texture;
}

Unk_71024f9d68::Unk_71024f9d68() : _8(-1), _c(-1), _10(-1) {}

void Unk_71024f9d68::sub_7100FE85DC() {
    _8 = -1;
}

Unk_71024f9d68::~Unk_71024f9d68() = default;

static sead::Atomic<s32> sUnk_710260EAE0;

Unk_71024F9D48::Unk_71024F9D48() {
    sUnk_710260EAE0.increment();
}

Unk_71024F9D48::~Unk_71024F9D48() {
    sUnk_710260EAE0.decrement();
    if (_18.isOn(1))
        sub_7100FE7FBC(nullptr);
}

bool Unk_71024F9D48::sub_7100FE7FB0() const {
    return _18.isOn(1);
}

bool Unk_71024F9D48::sub_7100FE7FBC(void* arg) {
    if (_38.hasTask()) {
        _38.removeTaskFromQueue();
        const auto status = _38.getStatus();
        _38.finalize();
        if (status == util::ManagedTaskHandle::Status::TaskRemoved) {
            stubbedLogFunction();
            return true;
        }
    }
    if (_18.isOn(1)) {
        TextureHandleMgr::InvalidateArg request;
        request._8 = this;
        return TextureHandleMgr::instance()->invalidateUser(request);
    }
    return true;
}

// NON_MATCHING: the original constructs separate request records in each type branch.
bool Unk_71024F9D48::sub_7100FE8074(const Unk_710260e960* arg) {
    if (_28)
        return true;
    _1c = 1;
    const auto* texture_arg = sead::DynamicCast<const Unk_71024f9a90>(arg);
    TextureHandleMgr::ValidateArg request;
    request.mHandle = this;
    if (texture_arg) {
        _30 = texture_arg->mCallback;
        request._1 = texture_arg->_10;
        request._2 = texture_arg->_11;
        request._3 = texture_arg->_12;
        request._4 = false;
        request.mTexture = texture_arg->mTexture;
        request.mFileDevice = texture_arg->mFileDevice;
        request.mRequester = texture_arg->mRequester;
        request.mTextureFlags = texture_arg->mTextureFlags;
    } else {
        const auto* path_arg = sead::DynamicCast<const Unk_71024f9ad8>(arg);
        if (!path_arg)
            return false;
        if (!path_arg->mPath.cstr()) {
            _1c = 3;
            return false;
        }
        _30 = path_arg->mCallback;
        request.mRequester = sead::SafeString::cEmptyString;
        if (path_arg->mHash)
            request.setHash(path_arg->mHash);
        else
            request.setPath(path_arg->mPath);
    }
    const bool success = TextureHandleMgr::instance()->validateUser(request);
    if (texture_arg) {
        if (success) {
            _20 = 1;
            _1c = 2;
        } else if (_1c == 1) {
            _1c = 3;
        }
    } else {
        if (_18.isOn(1)) {
            _20 = 1;
            _1c = 2;
        } else {
            _20 = 0;
            if (_1c == 1)
                _1c = 3;
        }
    }
    return success;
}

void Unk_71024F9D48::sub_7100FE8328(u32 value) {
    _1c = value;
}

u32 Unk_71024F9D48::sub_7100FE8330() {
    return _1c;
}

bool Unk_71024F9D48::sub_7100FE8338() {
    if (_38.hasTask()) {
        _38.removeTaskFromQueue();
        const auto status = _38.getStatus();
        _38.finalize();
        if (status == util::ManagedTaskHandle::Status::TaskRemoved) {
            stubbedLogFunction();
            return true;
        }
    }
    if (_18.isOn(1)) {
        TextureHandleMgr::InvalidateArg request;
        request._0 = false;
        request._8 = this;
        return TextureHandleMgr::instance()->invalidateUser(request);
    }
    return true;
}

bool Unk_71024F9D48::sub_7100FE83CC() {
    if (_28)
        return sub_7100FE0F14(_28);
    return false;
}

bool Unk_71024F9D48::sub_7100FE83DC() {
    if (_28)
        return sub_7100FE0F44(_28);
    return false;
}

nn::gfx::ResTexture* Unk_71024F9D48::sub_7100FE83EC() {
    if (!_20)
        return sUnk_710260EAD0;
    if (_28)
        return sub_7100FE0F8C(_28);
    return nullptr;
}

void Unk_71024F9D48::sub_7100FE8414(Unk_71024f9a08* resource) {
    _28 = resource;
    _18.set(1);
}

void Unk_71024F9D48::sub_7100FE8428() {
    if (_10 || _8)
        sub_7100FE0D98(_28, this);
    _18.reset(1);
    _1c = 0;
    _28 = nullptr;
    _30 = nullptr;
}

void Unk_71024F9D48::sub_7100FE8474(Unk_71024f9a08* resource, u32 status) {
    _28 = resource;
    _1c = status;
    _18.set(1);
}

// NON_MATCHING: the compiler inlines the native out-of-line callback dispatch helper.
void Unk_71024F9D48::sub_7100FE848C() {
    if (!_30)
        return;
    Unk_71024f9d68::CallbackArg arg;
    arg.mGeneration = TextureHandleMgr::instance()->getGeneration();
    arg.mHandle = this;
    _30->sub_7100FE85AC(&arg);
}

// NON_MATCHING: the compiler inlines the native out-of-line generation check and callback helper.
void Unk_71024F9D48::sub_7100FE84D4() {
    if (!_30)
        return;
    Unk_71024f9d68::CallbackArg arg;
    arg.mGeneration = TextureHandleMgr::instance()->getGeneration();
    arg.mHandle = this;
    _30->sub_7100FE85B8(&arg);
}

void Unk_71024f9d68::sub_7100FE85AC(const CallbackArg* arg) {
    m3(arg);
}

void Unk_71024f9d68::sub_7100FE85B8(const CallbackArg* arg) {
    if (_10 == arg->mGeneration)
        return;
    _10 = arg->mGeneration;
    m4(arg);
}

}  // namespace ksys::res
