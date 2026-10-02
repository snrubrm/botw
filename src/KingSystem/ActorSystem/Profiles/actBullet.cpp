#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace ksys::act {

// NON_MATCHING: the non-virtual thunks (0x7100006964...) do not keep &_bd0._10 in a register
Bullet::~Bullet() = default;

Actor* Bullet::m163() {
    if (!_ba0.hasProc())
        return nullptr;
    return sead::DynamicCast<Actor>(_ba0.getProc(nullptr, nullptr));
}

void Bullet::sub_71000048BC(BaseProc* proc) {
    _b90.acquire(proc, false);
}

void Bullet::sub_71000048C8(const BaseProcLink& link) {
    _b90 = link;
}

void Bullet::sub_710000497C(BaseProc* proc) {
    _ba0.acquire(proc, false);
}

void Bullet::sub_7100004988(const BaseProcLink& link) {
    _ba0 = link;
}

namespace acc {

static BaseProc* getProcIfActor(BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<Actor>(proc))
        return proc;
    return nullptr;
}

const BaseProcLink& Bullet::sub_71000056E4() const {
    auto* actor = static_cast<Actor*>(getProcIfActor(mProc));
    if (sead::IsDerivedFrom<act::Bullet>(actor))
        return static_cast<act::Bullet*>(actor)->_ba0;
    return getDummyBaseProcLink();
}

}  // namespace acc

}  // namespace ksys::act
