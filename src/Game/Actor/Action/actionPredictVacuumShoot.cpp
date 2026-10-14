#include "Game/Actor/Action/actionPredictVacuumShoot.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

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

// NON_MATCHING: target selection, vector temporaries and the shared virtual call use different
// registers and stack slots.
void PredictVacuumShoot::calc_() {
    if (isFinishedAS(0, 0))
        setFinished();
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD5B0(mActor, 0x22, &query, 0, 0)) {
        _78.sub_710073F3FC(&_124, query._10);
        _121 = true;
    }
    if (_78.sub_710073FA54()) {
        sead::Vector3f predicted;
        const sead::Vector3f* target = &_124;
        if (!_121) {
            _78.sub_710073F3FC(&predicted, 0.0f);
            target = &predicted;
        }
        m33(target);
        _120 = true;
    }
    m32();
    if (!_120) {
        sead::Vector3f target;
        if (_121)
            target = _124;
        else
            _78.sub_710073F3FC(&target, 0.0f);
        sead::Vector3f direction = target - mActor->getMtx().getTranslation();
        direction.normalize();
        sub_710073FA94(&_50, mActor);
        sub_710074006C(&_50, direction, sead::Vector3f::ey, true, 0.16f, *mRotSpd_s,
                       *mRotSpd_s * 0.1f);
        sub_7100740F1C(_50, mActor);
    } else {
        sub_7100738AA8(mActor, *mAngReduceRatio_s);
    }
}

void PredictVacuumShoot::m32() {
    sead::Vector3f dir;
    sub_710072DC54(&dir, mActor);
    sub_7100738488(mActor, *mPosReduceRatio_s, dir);
}

}  // namespace uking::action
