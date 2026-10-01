#include "Game/AI/AI/aiNearCreateSelect.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/World/worldManager.h"

namespace uking::ai {

NearCreateSelect::NearCreateSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NearCreateSelect::~NearCreateSelect() = default;

bool NearCreateSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NearCreateSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!*mIsNearCreate_m ||
        (ksys::world::Manager::instance()->isAocField() &&
         (ksys::act::hasTag(mActor, ksys::act::tags::TeamChuchu) ||
          ksys::act::hasTag(mActor, ksys::act::tags::TeamStalfos)))) {
        changeChild("通常湧き", params);
    } else {
        changeChild("近接湧き", params);
    }
}

void NearCreateSelect::calc_() {}

void NearCreateSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NearCreateSelect::loadParams_() {
    getMapUnitParam(&mIsNearCreate_m, "IsNearCreate");
}

}  // namespace uking::ai
