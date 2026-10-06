#include "Game/AI/AI/aiDamageAttrSelect.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

DamageAttrSelect::DamageAttrSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DamageAttrSelect::~DamageAttrSelect() = default;

bool DamageAttrSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool DamageAttrSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool DamageAttrSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DamageAttrSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    bool match = false;
    if (auto* damage_mgr = mActor->getDamageMgr()) {
        const s32 value = damage_mgr->getField54();
        switch (*mOption_s) {
        case -1:
            match = value <= *mKeyAttribute_s;
            break;
        case 0:
            match = value == *mKeyAttribute_s;
            break;
        case 1:
            match = value >= *mKeyAttribute_s;
            break;
        }
    }
    if (match)
        changeChild("該当", params);
    else
        changeChild("非該当", params);
}

void DamageAttrSelect::calc_() {}

void DamageAttrSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DamageAttrSelect::loadParams_() {
    getStaticParam(&mKeyAttribute_s, "KeyAttribute");
    getStaticParam(&mOption_s, "Option");
}

}  // namespace uking::ai
