#include "Game/AI/Action/actionNoticeTurn.h"
#include "Game/Actor/actEnemy.h"

namespace uking::action {

NoticeTurn::NoticeTurn(const InitArg& arg) : RotateTurnToTarget(arg) {}

NoticeTurn::~NoticeTurn() = default;

bool NoticeTurn::init_(sead::Heap* heap) {
    return RotateTurnToTarget::init_(heap);
}

void NoticeTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    RotateTurnToTarget::enter_(params);
}

void NoticeTurn::leave_() {
    RotateTurnToTarget::leave_();
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e74 = *mNoDoubleNoticeTime_s;
}

void NoticeTurn::loadParams_() {
    RotateTurnToTarget::loadParams_();
    getStaticParam(&mNoDoubleNoticeTime_s, "NoDoubleNoticeTime");
}

void NoticeTurn::calc_() {
    RotateTurnToTarget::calc_();
}

}  // namespace uking::action
