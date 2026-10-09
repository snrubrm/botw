#include "KingSystem/Resource/resUnk_71024F9D48.h"
#include "KingSystem/Resource/resBfRes.h"
#include "KingSystem/Resource/resTextureHandleMgr.h"
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

bool Unk_71024f9a08::sub_7100FE0F38() const {
    return mFlags.isOn(1);
}

void Unk_71024f9a08::sub_7100FE0850() {
    mFlags.reset(1);
}

bool Unk_71024f9a08::sub_7100FE0CF8() const {
    return mStatus >= 6 && mStatus <= 8;
}

bool Unk_71024f9a08::sub_7100FE0D0C() const {
    return _60 != nullptr;
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
    return sead::SafeString(_168);
}

sead::SafeString Unk_71024f9a08::sub_7100FE10A8() const {
    return sead::SafeString(_29a);
}

s64 Unk_71024f9a08::sub_7100FE10C0() const {
    return _60 ? _78 : 0;
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
