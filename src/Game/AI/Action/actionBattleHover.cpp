#include "Game/AI/Action/actionBattleHover.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_710073fa90.h"

namespace uking::action {

BattleHover::BattleHover(const InitArg& arg) : Hover(arg) {}

BattleHover::~BattleHover() = default;

bool BattleHover::init_(sead::Heap* heap) {
    return Hover::init_(heap);
}

void BattleHover::enter_(ksys::act::ai::InlineParamPack* params) {
    Hover::enter_(params);
    sub_710073FA90(&_80, mActor);
}

void BattleHover::leave_() {
    Hover::leave_();
}

void BattleHover::loadParams_() {
    Hover::loadParams_();
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void BattleHover::calc_() {
    Hover::calc_();
    auto* actor = mActor;
    sead::Vector3f dir = *mTargetPos_d - actor->getMtx().getTranslation();
    dir.normalize();
    sub_710073FA94(&_80, actor);
    sub_71007407F0(&_80, dir, sead::Vector3f::ey, true, *mRotSpeed_s);
    sub_7100740F1C(_80, actor);
}

}  // namespace uking::action
