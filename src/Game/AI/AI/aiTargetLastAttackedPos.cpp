#include "Game/AI/AI/aiTargetLastAttackedPos.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

TargetLastAttackedPos::TargetLastAttackedPos(const InitArg& arg) : TargetPosAI(arg) {}

TargetLastAttackedPos::~TargetLastAttackedPos() = default;

bool TargetLastAttackedPos::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetLastAttackedPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetLastAttackedPos::calc_() {
    TargetPosAI::calc_();
}

void TargetLastAttackedPos::leave_() {
    TargetPosAI::leave_();
}

void TargetLastAttackedPos::loadParams_() {
    TargetPosAI::loadParams_();
}

// NON_MATCHING: block layout and the numbering of the callee-saved registers holding the actor position
// only (every arm is instruction-identical)
void TargetLastAttackedPos::m35(sead::Vector3f* pos) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (!enemy) {
        pos->set(0, 0, 0);
        return;
    }

    auto& target = enemy->_e08;
    if (!target._5d) {
        target._10.getTranslation(*pos);
        return;
    }

    sead::Vector3f trans;
    mActor->getMtx().getTranslation(trans);
    if (target._40.x == 0 && target._40.z == 0) {
        sead::Vector3f front;
        target._10.getBase(front, 2);
        front.normalize();
        if (front.x == 0 && front.z == 0)
            pos->setMul(mActor->getMtx(), sead::Vector3f(0, 0, 5));
        else
            *pos = trans - front * 5.0f;
    } else {
        pos->x = trans.x + target._40.x * -2.0f;
        pos->y = trans.y - target._40.y * 2.0f;
        pos->z = trans.z - target._40.z * 2.0f;
    }
}

}  // namespace uking::ai
