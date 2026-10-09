#include "KingSystem/Resource/resUnk_71024F9D48.h"
#include "KingSystem/Resource/resBfRes.h"
#include "KingSystem/Resource/resTextureHandleMgr.h"
#include "KingSystem/Resource/resSystem.h"
#include <thread/seadAtomic.h>

namespace ksys::res {

// FE852C receives the fallback ResTexture from TextureHandleMgr::xx; FE83EC consumes it.
nn::gfx::ResTexture* sUnk_710260EAD0;

void sub_7100FE852C(nn::gfx::ResTexture* texture) {
    sUnk_710260EAD0 = texture;
}

Unk_71024f9d68::Unk_71024f9d68() : _8(u64(-1)), _10(-1) {}

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

void Unk_71024F9D48::sub_7100FE8474(Unk_71024f9a08* resource, u32 status) {
    _28 = resource;
    _1c = status;
    _18.set(1);
}

}  // namespace ksys::res
