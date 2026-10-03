#include "Game/AI/AI/aiStoneBall_BRoot.h"
#include <math/seadVector.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

StoneBall_BRoot::StoneBall_BRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StoneBall_BRoot::~StoneBall_BRoot() = default;

bool StoneBall_BRoot::init_(sead::Heap* heap) {
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (!actor)
        return false;

    actor->_a70 = &_50;
    if (auto* chemical = mActor->sub_71011D8A44(0))
        chemical->_14c = 0.0f;
    _70 = 0.0f;
    return true;
}

void StoneBall_BRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

// NON_MATCHING: the original loads the player position before the actor position in the horizontal direction (same
// instructions otherwise)
void StoneBall_BRoot::scaleReceivedImpulseMaybe(ksys::act::Unk_71006dc134* arg) {
    auto* actor = mActor;
    if (!actor)
        return;

    auto* info = arg->_18;
    auto* chemical = actor->sub_71011D8A44(0);
    if (!info || !chemical)
        return;

    if (actor->getActorFlags2().isOn(ksys::act::Actor::ActorFlag2::_40)) {
        chemical->_14c = 1.0f;
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&info->_d8, &accessor) && accessor.isPlayerProfile()) {
            const sead::Vector3f& player_pos = getPlayerPosition();
            sead::Vector3f dir(actor->getMtx().m[0][3] - player_pos.x, 0.0f,
                               actor->getMtx().m[2][3] - player_pos.z);
            dir.normalize();
            arg->_0 = dir * arg->_0.length();
        }
        return;
    }

    chemical->_14c = 0.0f;
    if (info->sub_71007A1F68(1)) {
        arg->_0 *= *mWeaponImpulseAmplifyPower_s * 2;
    } else if (info->sub_71007A1F68(2)) {
        arg->_0 *= *mWeaponImpulseAmplifyPower_s;
    } else if (info->sub_71007A1F68(4)) {
        arg->_0 *= *mWeaponImpulseAmplifyPower_s * 1.5f;
    } else if (info->sub_71007A1F68(0x10)) {
        if (_70 > 0.0f) {
            arg->_0 *= *mDoubleBombImpulseAmplifyPower_s;
        } else {
            arg->_0 *= *mBombImpulseAmplifyPower_s;
            _70 = 10.0f;
        }
    }
}

void StoneBall_BRoot::calc_() {
    if (_70 > 0.0f)
        _70 -= 1.0f;
}

void StoneBall_BRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StoneBall_BRoot::loadParams_() {
    getStaticParam(&mWeaponImpulseAmplifyPower_s, "WeaponImpulseAmplifyPower");
    getStaticParam(&mBombImpulseAmplifyPower_s, "BombImpulseAmplifyPower");
    getStaticParam(&mDoubleBombImpulseAmplifyPower_s, "DoubleBombImpulseAmplifyPower");
}

}  // namespace uking::ai
