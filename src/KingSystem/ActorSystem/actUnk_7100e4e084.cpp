#include "KingSystem/ActorSystem/actUnk_7100e4e084.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLiftable.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace ksys::act {

bool Unk_7100e4e084::ContactCallback::invoke(phys::ContactPointInfo::ShouldDisableContact* disable,
                                             const phys::ContactPointInfo::Event& event) {
    if (!event.body)
        return true;

    if (_8 & 0x2) {
        if (event.body->getGroundHitType() == phys::GroundHit::MovingTrolley) {
            *disable = phys::ContactPointInfo::ShouldDisableContact::Yes;
            return false;
        }
    }
    if (!(_8 & 0x1))
        return true;
    if (event.body->getMotionType() != phys::MotionType::Dynamic)
        return true;
    *disable = phys::ContactPointInfo::ShouldDisableContact::Yes;
    return false;
}

void Unk_7100e4e084::sub_7100E504C0() {
    if (sead::BitFlagUtil::countOnBit(_1c8._8) < 1)
        return;

    phys::ContactPointInfo* info;
    if (auto* controller = mActor->getCharacterController()) {
        info = controller->sub_7100F635D8();
    } else {
        auto* body = mActor->getMainBody();
        info = body ? body->getContactPointInfo() : nullptr;
    }
    if (info) {
        info->setContactCallback(&_1c8);
        _1c8._10 |= 0x4;
    }
}

void Unk_7100e4e084::sub_7100E50450(Actor* carrier) {
    if (!carrier)
        return;
    auto* list = mActor->getParam()->getRes().mGParamList;
    if (!list)
        return;
    auto* liftable = list->getLiftable();
    if (!liftable || !liftable->mIsSetChemicalParent.ref())
        return;
    if (auto* chemicals = mActor->getChemicalContainer()) {
        chemicals->sub_7100E38C54(carrier, true);
        _1c8._10 |= 0x1;
    }
}

void Unk_7100e4e084::sub_7100E4E084() {
    _100 = -1;
    _bc = 0;
    _128 = false;
    _129 = false;
    _b0 = 0;
    _b8 = 0;
    if (_1c8._10 & 0x1) {
        if (auto* chemicals = mActor->getChemicalContainer())
            chemicals->sub_7100E38C54(nullptr, false);
        _1c8._10 &= ~0x1;
    }
    _1c8._8 = 0;
    _1c8._10 &= ~0x4;
}

void Unk_7100e4e084::sub_7100E5052C() {
    if (_1c8._10 & 0x4) {
        phys::ContactPointInfo* info;
        if (auto* controller = mActor->getCharacterController()) {
            info = controller->sub_7100F635D8();
        } else {
            auto* body = mActor->getMainBody();
            info = body ? body->getContactPointInfo() : nullptr;
        }
        if (info) {
            info->setContactCallback(nullptr);
            _1c8._10 &= ~0x4;
        }
    }
}

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

// NON_MATCHING: the original duplicates the accessor destructor and the unlock in both result paths (ours shares one tail)
// Placeholder name: registers the system group handlers 0 / 1 of the actor linked in `_170` with the physics of `actor`.
bool Unk_7100e4e084::sub_7100E50390(Actor* actor) {
    auto* physics = actor->getPhysics();
    if (!physics)
        return false;

    auto lock = sead::makeScopedLock(_130);
    ActorConstDataAccess accessor;
    acquireActor(&_170, &accessor);
    bool result = false;
    if (accessor.hasProc()) {
        physics->sub_7100FBDFA4(accessor.x(0));
        physics->sub_7100FBDFA4(accessor.x(1));
        result = true;
    }
    return result;
}

// NON_MATCHING: same operations, but the original loads the matrix rows in another order (scheduling)
// Placeholder name: the correction `scale * offset - mtx * (scale * offset)` of the Liftable LiftCenterOffset for a
// rotation `mtx` (zero without the parameter).
void Unk_7100e4e084::sub_7100E4FF1C(sead::Vector3f* out, const sead::Matrix34f& mtx) const {
    auto* list = mActor->getParam()->getRes().mGParamList;
    const res::GParamListObjectLiftable* liftable = list ? list->getLiftable() : nullptr;
    if (!liftable) {
        out->set(0, 0, 0);
        return;
    }

    const f32 scale = mActor->getScale().y;
    const sead::Vector3f& offset = liftable->mLiftCenterOffset.ref();
    const f32 nx = -(scale * offset.x);
    const f32 sy = scale * offset.y;
    const f32 sz = scale * offset.z;
    const f32 ny = -(scale * offset.y);
    const f32 nz = -(scale * offset.z);
    out->set(nx, ny, nz);
    out->x = mtx(0, 0) * nx - mtx(0, 1) * sy - mtx(0, 2) * sz;
    out->y = mtx(1, 0) * nx - mtx(1, 1) * sy - mtx(1, 2) * sz;
    out->z = mtx(2, 0) * nx - mtx(2, 1) * sy - mtx(2, 2) * sz;
    out->x += scale * offset.x;
    out->y += scale * offset.y;
    out->z += scale * offset.z;
}

}  // namespace ksys::act
