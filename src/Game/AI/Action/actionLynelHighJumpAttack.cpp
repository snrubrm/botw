#include "Game/AI/Action/actionLynelHighJumpAttack.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

LynelHighJumpAttack::LynelHighJumpAttack(const InitArg& arg) : JumpAttack(arg) {}

LynelHighJumpAttack::~LynelHighJumpAttack() = default;

bool LynelHighJumpAttack::init_(sead::Heap* heap) {
    return JumpAttack::init_(heap);
}

void LynelHighJumpAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    JumpAttack::enter_(params);
}

// NON_MATCHING: the original ORs the old flag byte with the mask (`orr old, mask`); ours emits the
// operands the other way round
void LynelHighJumpAttack::leave_() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (auto* unit = enemy->_1148._48) {
            const f32 scale = _a8;
            const f32 current = unit->_10 ? unit->_2c : 0.0f;
            if (scale != current) {
                unit->_2c = scale;
                unit->_58.setBit(act::Unk_7102357908::Unk48::Flag(act::Unk_7102357908::Unk48::Flag::_4));
            }
        }
    }
    JumpAttack::leave_();
}

void LynelHighJumpAttack::loadParams_() {
    JumpAttack::loadParams_();
}

void LynelHighJumpAttack::calc_() {
    JumpAttack::calc_();
}

f32 LynelHighJumpAttack::m33() {
    return mActor->getVelocity().y < -0.1f ? 0.99f : 1.0f;
}

void LynelHighJumpAttack::m32(f32 a, f32 b) {
    f32 scale = 1.0f;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (auto* unit = enemy->_1148._48) {
            if (unit->_10)
                scale = unit->_2c + 1.0f;
        }
    }
    JumpAttack::m32(scale * a, scale * b);
}

}  // namespace uking::action
