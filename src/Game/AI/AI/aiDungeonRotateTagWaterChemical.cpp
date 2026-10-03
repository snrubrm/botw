#include "Game/AI/AI/aiDungeonRotateTagWaterChemical.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

DungeonRotateTagWaterChemical::DungeonRotateTagWaterChemical(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

DungeonRotateTagWaterChemical::~DungeonRotateTagWaterChemical() = default;

bool DungeonRotateTagWaterChemical::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonRotateTagWaterChemical::enter_(ksys::act::ai::InlineParamPack* params) {
    _5c = 0;
    _58 = 0xff;
    changeChild("待機");
}

void DungeonRotateTagWaterChemical::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonRotateTagWaterChemical::loadParams_() {
    getStaticParam(&mSlowDownRotRadAccel_s, "SlowDownRotRadAccel");
    getStaticParam(&mSlowDownTimer_s, "SlowDownTimer");
    getStaticParam(&mRotRadAccel_s, "RotRadAccel");
    getStaticParam(&mReverseDotTh_s, "ReverseDotTh");
}

void DungeonRotateTagWaterChemical::sub_710037B08C(f32 ang_vel, f32 ang_accel) {
    _5c = 0;

    ksys::act::ai::InlineParamPack pack;
    pack.addFloat(ang_vel, "DynCurrentAngVel", -1);
    pack.addFloat(ang_accel, "DynAngAccel", -1);
    changeChild("減速", &pack);
}

void DungeonRotateTagWaterChemical::sub_710037AE80(f32 ang_vel, f32 ang_accel) {
    _5c = 0;
    _58 = 0;

    ksys::act::ai::InlineParamPack pack;
    pack.addFloat(ang_vel, "DynCurrentAngVel", -1);
    pack.addFloat(ang_accel, "DynAngAccel", -1);
    changeChild("時計回り", &pack);
}

void DungeonRotateTagWaterChemical::sub_710037AF84(f32 ang_vel, f32 ang_accel) {
    _5c = 0;
    _58 = 1;

    ksys::act::ai::InlineParamPack pack;
    pack.addFloat(ang_vel, "DynCurrentAngVel", -1);
    pack.addFloat(ang_accel, "DynAngAccel", -1);
    changeChild("反時計回り", &pack);
}

}  // namespace uking::ai
