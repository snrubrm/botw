#include "Game/AI/Action/actionAttackPartBind.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

AttackPartBind::AttackPartBind(const InitArg& arg) : Attack(arg) {}

AttackPartBind::~AttackPartBind() = default;

void AttackPartBind::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* helper = sead::DynamicCast<Unk_71023c8378>(m32()))
        helper->_8c = *mASSlot_s;
    Attack::enter_(params);
}

void AttackPartBind::leave_() {
    Attack::leave_();
}

void AttackPartBind::loadParams_() {
    Attack::loadParams_();
    getStaticParam(&mASSlot_s, "ASSlot");
}

void AttackPartBind::calc_() {
    Attack::calc_();
}

void AttackPartBind::m33() {
    if (auto* as_list = mActor->getASList()) {
        _168 = as_list->x_1(0, 0);
        playAS(mASName_s.cstr(), false, *mASSlot_s, 0, -1.0f);
    }
}

}  // namespace uking::action
