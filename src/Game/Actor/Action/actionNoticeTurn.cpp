#include "Game/Actor/Action/actionNoticeTurn.h"
#include "Game/Actor/actEnemy.h"

namespace uking::action {

NoticeTurn::NoticeTurn(const InitArg& arg) : ASPlayRotateTurnToTarget(arg) {}

NoticeTurn::~NoticeTurn() = default;

bool NoticeTurn::init_(sead::Heap* heap) {
    return ASPlayRotateTurnToTarget::init_(heap);
}

void NoticeTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ASPlayRotateTurnToTarget::enter_(params);
}

void NoticeTurn::leave_() {
    ASPlayRotateTurnToTarget::leave_();
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor))
        enemy->_e74 = *mNoDoubleNoticeTime_s;
}

void NoticeTurn::loadParams_() {
    ASPlayRotateTurnToTarget::loadParams_();
    getStaticParam(&mNoDoubleNoticeTime_s, "NoDoubleNoticeTime");
}

void NoticeTurn::calc_() {
    ASPlayRotateTurnToTarget::calc_();
}

}  // namespace uking::action
