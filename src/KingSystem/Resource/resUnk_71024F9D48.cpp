#include "KingSystem/Resource/resUnk_71024F9D48.h"
#include "KingSystem/Resource/resBfRes.h"
#include "KingSystem/Resource/resTextureHandleMgr.h"
#include "KingSystem/Resource/resResourceFileUtil.h"
#include "KingSystem/Resource/resSystem.h"
#include <thread/seadAtomic.h>
#include <codec/seadHashCRC32.h>
#include <thread/seadThread.h>

namespace ksys::res {

Unk_71024f9cf0::Unk_71024f9cf0() = default;

// NON_MATCHING: native retains a base vtable store in the empty destructor.
Unk_71024f9cf0::~Unk_71024f9cf0() {}

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
        if (status == ManagedTaskHandle::Status::TaskRemoved) {
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
        if (status == ManagedTaskHandle::Status::TaskRemoved) {
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

void Unk_71024F9D48::sub_7100FE848C() {
    if (!_30)
        return;
    Unk_71024f9d68::CallbackArg arg;
    arg.mGeneration = TextureHandleMgr::instance()->getGeneration();
    arg.mHandle = this;
    _30->sub_7100FE85AC(&arg);
}

void Unk_71024F9D48::sub_7100FE84D4() {
    if (!_30)
        return;
    Unk_71024f9d68::CallbackArg arg;
    arg.mGeneration = TextureHandleMgr::instance()->getGeneration();
    arg.mHandle = this;
    _30->sub_7100FE85B8(&arg);
}

}  // namespace ksys::res
