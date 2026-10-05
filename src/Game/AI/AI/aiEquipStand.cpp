#include "Game/AI/AI/aiEquipStand.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

// The original helper's source namespace is unknown.
bool sub_7100700A78(s32 slot);

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

// NON_MATCHING: display attention-key address lifetime and register allocation differ.
void EquipStand::enter_(ksys::act::ai::InlineParamPack* params) {
    *static_cast<Unk_71025afb58**>(mEquipDisplayChild_a) = &_b0;
    ksys::act::disableAllAttClients(mActor);
    _a8 = false;
    const bool occupied = sub_7100700A78(*mEquipStandSlot_m);
    _a8 = false;
    _38.x();
    auto* actor = mActor;
    ksys::act::disableAttClient(actor, mTakeOutAttKey_s);
    if (occupied) {
        ksys::act::disableAttClient(actor, mDisplayAttKey_s);
        changeChild("飾り生成");
    } else {
        ksys::act::enableAttClient(actor, mDisplayAttKey_s);
        changeChild("待機");
    }
    _38._34 = 0x1800020;
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
