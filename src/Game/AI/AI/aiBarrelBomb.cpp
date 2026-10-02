#include "Game/AI/AI/aiBarrelBomb.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

BarrelBomb::BarrelBomb(const InitArg& arg) : SimpleLiftable(arg) {}

bool BarrelBomb::init_(sead::Heap* heap) {
    return SimpleLiftable::init_(heap);
}

void BarrelBomb::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleLiftable::enter_(params);
    if (auto* body = mActor->getMainBody()) {
        if (*mIsFixedPlace_m && !_d0) {
            body->changeMotionType(ksys::phys::MotionType::Fixed);
            _d0 = true;
        }
    }
}

void BarrelBomb::leave_() {
    SimpleLiftable::leave_();
}

void BarrelBomb::loadParams_() {
    getMapUnitParam(&mIsFixedPlace_m, "IsFixedPlace");
}

void BarrelBomb::calc_() {
    if (isCurrentChild("爆発"))
        return;

    auto* chemical = mActor->getChemicalStuff();
    if (chemical && chemical->_c0 == 4) {
        _38.x();
        ksys::act::disableAllAttClients(mActor);
        changeChild("爆発");
        return;
    }

    auto* life = mActor->getLife();
    if (life && *life <= 0) {
        if (chemical)
            chemical->sub_7100D909A4();
        else
            mActor->deleteAndEmit(0);
    }
    SimpleLiftable::calc_();
}

}  // namespace uking::ai
