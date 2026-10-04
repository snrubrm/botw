#include "Game/AI/Action/actionAnimalASPlayWithLegTurn.h"
#include "Game/Actor/actRideable.h"
#include <cmath>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

AnimalASPlayWithLegTurn::AnimalASPlayWithLegTurn(const InitArg& arg) : ForkAnimalASPlay(arg) {}

AnimalASPlayWithLegTurn::~AnimalASPlayWithLegTurn() = default;

bool AnimalASPlayWithLegTurn::init_(sead::Heap* heap) {
    return ForkAnimalASPlay::init_(heap);
}

void AnimalASPlayWithLegTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    _198 = false;
    sub_710008DC24();
    ForkAnimalASPlay::enter_(params);
}

void AnimalASPlayWithLegTurn::leave_() {
    _80.sub_710070E4C0();
    ForkAnimalASPlay::leave_();
}

void AnimalASPlayWithLegTurn::loadParams_() {
    ForkAnimalASPlay::loadParams_();
    getStaticParam(&mParams.mRotSpeed_s, "RotSpeed");
    getStaticParam(&mParams.mRotAccRatio_s, "RotAccRatio");
    getStaticParam(&mParams.mRotRatio_s, "RotRatio");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void AnimalASPlayWithLegTurn::calc_() {
    sub_710008DC24();
    ForkAnimalASPlay::calc_();
    if (sub_71005DD734(mActor, 41, nullptr, 0, 0)) {
        _80.sub_710070E4C0();
        _198 &= ~3;
    }
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD5B0(mActor, 41, &query, 0, 0)) {
        if (query.name.isEmpty()) {
            _198 |= 2;
            _1a0 = mActor->getAngVelocity().y;
        } else {
            _198 |= 1;
            _80.sub_710070E434(query.name);
            _80.sub_710070E4EC(query.name);
        }
    }
    if (_198 & 1) {
        _80.sub_710070E714();
        _80.sub_710070E7A8(mParams.mTargetPos_d, *mParams.mRotRatio_s, *mParams.mRotSpeed_s,
                           *mParams.mRotAccRatio_s);
    } else {
        auto* as_list = mActor->getASList();
        auto* controller = mActor->getCharacterController();
        auto* rideable = mActor->m132();
        if (as_list && controller && rideable) {
            if (_198 & 2) {
                uking::act::sub_7100E7F4FC(as_list, controller, 1.0f);
                sub_710008DF6C(controller);
            } else {
                uking::act::sub_7100E7F698(rideable, as_list, controller);
            }
        } else {
            setFailed();
        }
    }
}

void AnimalASPlayWithLegTurn::sub_710008DC24() {
    sead::Vector3f dir;
    dir.set(*mParams.mTargetPos_d);
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    dir -= pos;
    dir.normalize();

    sead::Vector3f side;
    mActor->getMtx().getBase(side, 2);
    ksys::util::sub_71011EFA00(&side, side, sead::Vector3f::ey);
    side.normalize();

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, side, dir, sead::Vector3f::ey);
    mActor->getASList()->x_6(9, 0, sead::Mathf::rad2deg(angle) * axis.y);
}

// NON_MATCHING: the original loads the mRotSpeed_s pointer before the powf call and the value after it
// (`const f32& speed = *mParams.mRotSpeed_s;` reproduces it).
void AnimalASPlayWithLegTurn::sub_710008DF6C(ksys::phys::CharacterController* controller) {
    sead::Vector3f dir;
    dir.set(*mParams.mTargetPos_d);
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    dir -= pos;
    dir.y = 0;
    dir.normalize();

    const f32 rate = 1.0f - std::pow(1.0f - *mParams.mRotAccRatio_s, ksys::VFR::instance()->getDeltaFrame());
    _1a0 += rate * (*mParams.mRotSpeed_s - _1a0);
    sub_710073FA94(&_1a4, mActor);
    sub_710074006C(&_1a4, dir, sead::Vector3f::ey, true, *mParams.mRotRatio_s, _1a0, 0.0f);
    sub_7100740E04(_1a4, controller);
}

}  // namespace uking::action
