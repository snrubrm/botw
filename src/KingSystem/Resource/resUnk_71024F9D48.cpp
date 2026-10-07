#include "KingSystem/Resource/resUnk_71024F9D48.h"
#include "KingSystem/Resource/resTextureHandleMgr.h"
#include "KingSystem/Resource/resSystem.h"
#include <thread/seadAtomic.h>

namespace ksys::res {

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

void Unk_71024F9D48::sub_7100FE8414(void* resource) {
    _28 = resource;
    _18.set(1);
}

void Unk_71024F9D48::sub_7100FE8474(void* resource, u32 status) {
    _28 = resource;
    _1c = status;
    _18.set(1);
}

}  // namespace ksys::res
