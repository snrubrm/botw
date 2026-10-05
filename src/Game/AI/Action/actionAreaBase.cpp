#include "Game/AI/Action/actionAreaBase.h"
#include "KingSystem/ActorSystem/Profiles/actAreaActor.h"

namespace uking::action {

AreaBase::AreaBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void AreaBase::loadParams_() {
    getMapUnitParam(&mEnableCharacterOn_m, "EnableCharacterOn");
}

void AreaBase::calc_() {
    if (auto* actor = sead::DynamicCast<ksys::act::AreaActor>(mActor)) {
        if (actor->sub_7100E26A80() != *mEnableCharacterOn_m)
            actor->sub_7100E26A28(*mEnableCharacterOn_m);
    }
}

}  // namespace uking::action
