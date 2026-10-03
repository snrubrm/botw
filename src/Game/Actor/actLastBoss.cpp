#include "Game/Actor/actLastBoss.h"

namespace uking::act {

namespace {
void forwardX17ToParts(ksys::act::Actor* actor, ksys::act::Unk117* arg) {
    if (!sead::IsDerivedFrom<Enemy>(actor))
        return;
    auto* enemy = static_cast<Enemy*>(actor);
    for (auto* part : enemy->_1128.mList) {
        if (auto* part_actor =
                sead::DynamicCast<ksys::act::Actor>(part->mLink.getProc(nullptr, nullptr)))
            part_actor->x_17(arg);
    }
}
}  // namespace

void LastBoss::m117(ksys::act::Unk117* arg) {
    forwardX17ToParts(this, arg);
}

// NON_MATCHING: member types incomplete
LastBoss::~LastBoss() = default;

void LastBoss::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    setter->set(0x20, 0x10);
    _14e8.reset(0x80);
    Enemy::m76(setter);
}

void LastBoss::m77(ksys::VFR::ScopedDeltaSetter* setter) {
    setter->set(0x20, 0x10);
}

bool LastBoss::isGuard() {
    return false;
}

bool LastBoss::isGuardJust() {
    return _14f8._30.isOn(1);
}

bool LastBoss::sub_71002C6210(f32 value) const {
    return _14f0 < value;
}

bool LastBoss::m140() {
    return _14e8.isOnBit(9);
}

}  // namespace uking::act
