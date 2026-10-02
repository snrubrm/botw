#include "Game/AI/AI/aiEquipStand.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

EquipStand::EquipStand(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EquipStand::~EquipStand() {
    if (_b0.mLink.hasProc()) {
        ksys::act::ActorConstDataAccess acc;
        if (ksys::act::acquireActor(&_b0.mLink, &acc))
            acc.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

bool EquipStand::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EquipStand::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EquipStand::leave_() {
    *static_cast<void**>(mEquipDisplayChild_a) = nullptr;
}

void EquipStand::loadParams_() {
    getStaticParam(&mDisplayAttKey_s, "DisplayAttKey");
    getStaticParam(&mTakeOutAttKey_s, "TakeOutAttKey");
    getMapUnitParam(&mEquipStandSlot_m, "EquipStandSlot");
    getAITreeVariable(&mEquipDisplayChild_a, "EquipDisplayChild");
}

}  // namespace uking::ai
