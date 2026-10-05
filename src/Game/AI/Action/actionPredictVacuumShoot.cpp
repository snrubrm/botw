#include "Game/AI/Action/actionPredictVacuumShoot.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"

void sub_710072DC54(sead::Vector3f* out, ksys::act::Actor* actor);

namespace uking::action {

PredictVacuumShoot::PredictVacuumShoot(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PredictVacuumShoot::~PredictVacuumShoot() = default;

bool PredictVacuumShoot::init_(sead::Heap* heap) {
    return _78.sub_710073ECC0();
}

void PredictVacuumShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _78.sub_710073EF50(this);
    sub_710073FA90(&_50, mActor);
    _120 = false;
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    _121 = false;
    _78.mIsReuseBullet = *mIsReuseBullet_s;
}

void PredictVacuumShoot::leave_() {
    ksys::act::ai::Action::leave_();
}

void PredictVacuumShoot::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mIsReuseBullet_s, "IsReuseBullet");
    _78.sub_710073ED20(this);
    _78.sub_710073EEE4(this);
}

void PredictVacuumShoot::calc_() {
    ksys::act::ai::Action::calc_();
}

void PredictVacuumShoot::m32() {
    sead::Vector3f dir;
    sub_710072DC54(&dir, mActor);
    sub_7100738488(mActor, *mPosReduceRatio_s, dir);
}

}  // namespace uking::action
