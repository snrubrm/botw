#include "Game/AI/Action/actionAttack.h"

namespace uking::action {

Attack::Attack(const InitArg& arg) : StoppingAttackBase(arg) {}

void Attack::enter_(ksys::act::ai::InlineParamPack* params) {
    StoppingAttackBase::enter_(params);
    m33();
    if (auto* helper = m32())
        helper->_58 = m35();
    mFlags.reset(Flag::Changeable);
}

void Attack::leave_() {
    StoppingAttackBase::leave_();
}

u32 Attack::m35() {
    return 1;
}

void Attack::loadParams_() {
    StoppingAttackBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void Attack::calc_() {
    StoppingAttackBase::calc_();
    if (m34())
        setFinished();
}

void Attack::m33() {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
}

}  // namespace uking::action
