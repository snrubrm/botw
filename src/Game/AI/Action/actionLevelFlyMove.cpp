#include "Game/AI/Action/actionLevelFlyMove.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

LevelFlyMove::LevelFlyMove(const InitArg& arg) : LevelFlyMoveBase(arg) {}

bool LevelFlyMove::init_(sead::Heap* heap) {
    return LevelFlyMoveBase::init_(heap);
}

void LevelFlyMove::enter_(ksys::act::ai::InlineParamPack* params) {
    LevelFlyMoveBase::enter_(params);
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
}

void LevelFlyMove::leave_() {
    LevelFlyMoveBase::leave_();
}

void LevelFlyMove::loadParams_() {
    LevelFlyMoveBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void LevelFlyMove::calc_() {
    LevelFlyMoveBase::calc_();
}

void LevelFlyMove::sub_71001DA0D0() {
    if (*mVibrateMemoryStep_s > 0.0f && *mVibrateCheckFrame_s > 0.0f) {
        if (auto* checker = sead::DynamicCast<Unk_71025b0578>(*_108._0))
            checker->sub_7100716408(mActor->getMtx().getTranslation());
    }
}

}  // namespace uking::action
