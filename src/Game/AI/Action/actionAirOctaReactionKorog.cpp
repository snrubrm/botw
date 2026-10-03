#include "Game/AI/Action/actionAirOctaReactionKorog.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AirOctaReactionKorog::AirOctaReactionKorog(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AirOctaReactionKorog::~AirOctaReactionKorog() = default;

bool AirOctaReactionKorog::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AirOctaReactionKorog::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710073FA90(&_4c, mActor);
    playAS(mAS_s.cstr(), false, 0, 0, -1.0f);
    if (auto* damage_mgr = sub_710072BA90(mActor))
        damage_mgr->m30(&_40);
    else
        _40.set(sead::Vector3f::ez);
    _40 = -_40;
}

void AirOctaReactionKorog::leave_() {
    ksys::act::ai::Action::leave_();
}

void AirOctaReactionKorog::loadParams_() {
    getStaticParam(&mEndState_s, "EndState");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mAS_s, "AS");
}

void AirOctaReactionKorog::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
