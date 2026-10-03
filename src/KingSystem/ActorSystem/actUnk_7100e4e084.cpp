#include "KingSystem/ActorSystem/actUnk_7100e4e084.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include <prim/seadScopedLock.h>

namespace ksys::act {

void Unk_7100e4e084::sub_7100E50010(int state, const sead::Vector3f& pos, bool a3) {
    auto lock = sead::makeScopedLock(_c0);
    _104 = pos;
    _100 = state;
    _128 = a3;
    _129 = false;
}

void Unk_7100e4e084::sub_7100E5007C(int state, const sead::Vector3f& pos) {
    sead::Vector3f scaled{pos.x, pos.y, pos.z};
    scaled *= static_cast<f32>(sub_7100EDD218(mActor));
    auto lock = sead::makeScopedLock(_c0);
    _104 = scaled;
    _100 = state;
    _128 = false;
    _129 = false;
}

void Unk_7100e4e084::sub_7100E500F8(int state, const sead::Vector3f& pos, f32 a3, f32 a4) {
    auto lock = sead::makeScopedLock(_c0);
    _100 = state;
    _129 = true;
    _110.set(pos);
    _11c = a4;
    _120 = a3;
    _104 = sead::Vector3f::ey * static_cast<f32>(sub_7100EDD218(mActor));
}

bool Unk_7100e4e084::sub_7100E5019C(sead::Vector3f* pos, f32* a2, f32* a3) {
    bool result = false;
    {
        auto lock = sead::makeScopedLock(_c0);
        if (_129) {
            pos->set(_110);
            *a3 = _11c;
            *a2 = _120;
            result = true;
        }
    }
    return result;
}

void Unk_7100e4e084::sub_7100E50220() {
    auto lock = sead::makeScopedLock(_c0);
    _100 = 3;
}

void Unk_7100e4e084::sub_7100E50254() {
    auto lock = sead::makeScopedLock(_c0);
    _100 = 2;
}

void Unk_7100e4e084::sub_7100E50288() {
    auto lock = sead::makeScopedLock(_c0);
    _100 = 0;
}

bool Unk_7100e4e084::sub_7100E502B8() const {
    return mActor->getVelocity().squaredLength() > 1.0f;
}

void Unk_7100e4e084::sub_7100E502EC(BaseProc* proc) {
    auto lock = sead::makeScopedLock(_130);
    _170.acquire(proc, false);
}

bool Unk_7100e4e084::sub_7100E50334(ActorConstDataAccess* accessor) {
    if (!accessor)
        return false;
    auto lock = sead::makeScopedLock(_130);
    return acquireActor(&_170, accessor);
}

}  // namespace ksys::act
