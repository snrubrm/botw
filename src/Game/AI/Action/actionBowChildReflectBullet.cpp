#include "Game/AI/Action/actionBowChildReflectBullet.h"
#include <random/seadGlobalRandom.h>

namespace uking::action {

BowChildReflectBullet::BowChildReflectBullet(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BowChildReflectBullet::~BowChildReflectBullet() = default;

bool BowChildReflectBullet::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original zeroes the 8 bytes at 0x10c with one `str xzr` (address materialised with an add) and
// schedules the `playAS` string adrp earlier.
void BowChildReflectBullet::enter_(ksys::act::ai::InlineParamPack* params) {
    _10c = sead::Vector2f(0.0f, 0.0f);
    _90 = 0;
    const f32 range = *mTargetMoveOffsetRandRange_s;
    _94 = sead::GlobalRandom::instance()->getF32Range(-range, range);
    _98 = 2.0f;
    _a0 = 0;
    _a8 = sead::Vector2f(0.0f, 70.0f);
    _b0 = -1.0f;
    playAS("Open", false, 0, 0, -1.0f);
    _9c = 0;
    _a4 = false;
}

void BowChildReflectBullet::leave_() {
    ksys::act::ai::Action::leave_();
}

void BowChildReflectBullet::loadParams_() {
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mOffsetLength_s, "OffsetLength");
    getStaticParam(&mTargetOffsetY_s, "TargetOffsetY");
    getStaticParam(&mTargetMoveOffset_s, "TargetMoveOffset");
    getStaticParam(&mTargetMoveOffsetRandRange_s, "TargetMoveOffsetRandRange");
    getStaticParam(&mMoveRotateRate_s, "MoveRotateRate");
    getStaticParam(&mMoveRotateMax_s, "MoveRotateMax");
    getStaticParam(&mMoveRotateMin_s, "MoveRotateMin");
    getDynamicParam(&mID_d, "ID");
    getDynamicParam(&mXRotateAngle_d, "XRotateAngle");
    getDynamicParam(&mIsReflectAmongChild_d, "IsReflectAmongChild");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mMoveTargetPos_d, "MoveTargetPos");
    getDynamicParam(&mParentActor_d, "ParentActor");
}

void BowChildReflectBullet::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
