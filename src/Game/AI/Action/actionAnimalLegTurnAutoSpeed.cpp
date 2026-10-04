#include "Game/AI/Action/actionAnimalLegTurnAutoSpeed.h"
#include <algorithm>
#include <cmath>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

AnimalLegTurnAutoSpeed::AnimalLegTurnAutoSpeed(const InitArg& arg) : ForkAnimalASPlay(arg) {}

AnimalLegTurnAutoSpeed::~AnimalLegTurnAutoSpeed() = default;

bool AnimalLegTurnAutoSpeed::init_(sead::Heap* heap) {
    return ForkAnimalASPlay::init_(heap);
}

void AnimalLegTurnAutoSpeed::enter_(ksys::act::ai::InlineParamPack* params) {
    _68 = 0.6f;
    _6c = 0.6f;
    _70 = 0.0f;
    _1b4 = false;
    _1c4 = 0.0f;
    sub_710008FAC0();
    ForkAnimalASPlay::enter_(params);
}

void AnimalLegTurnAutoSpeed::leave_() {
    ForkAnimalASPlay::leave_();
}

void AnimalLegTurnAutoSpeed::loadParams_() {
    ForkAnimalASPlay::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void AnimalLegTurnAutoSpeed::calc_() {
    ForkAnimalASPlay::calc_();

    ksys::as::ASList::Unk4 query;
    if (sub_71005DD5B0(mActor, 41, &query, 0, 0)) {
        f32 blend;
        if (query._10 < 4.0f) {
            blend = 0.0f;
            _68 = 1.0f;
            _6c = 1.0f;
        } else {
            blend = 1.0f;
        }

        sead::Vector3f pos;
        mActor->getMtx().getTranslation(pos);
        const sead::Vector3f up = getUpDir(mActor);

        sead::Vector3f dir = *mTargetPos_d - pos;
        ksys::util::sub_71011EFA00(&dir, dir, up);
        dir.normalize();

        sead::Vector3f forward;
        mActor->getMtx().getBase(forward, 2);
        ksys::util::sub_71011EFA00(&forward, forward, up);
        forward.normalize();

        sead::Vector3f axis;
        f32 angle;
        ksys::util::sub_71011EEB08(&axis, &angle, forward, dir, sead::Vector3f::ey);
        _70 = angle / std::max(query._10 - (blend + blend) * 0.5f, 1.0f);

        if (query.name.isEmpty()) {
            _1b4 = false;
            sub_710073FA90(&_190, mActor);
            _1c4 = mActor->getAngVelocity().y;
        } else {
            _1b4 = true;
            _78.sub_710070E4EC(query.name);
        }
        _1b8 = *mTargetPos_d;
    }

    if (sub_71005DD798(mActor, 41, nullptr, 0, 0)) {
        if (_1b4) {
            _78.sub_710070E714();
            _78.sub_710070E7A8(&_1b8, _6c, _70, _68);
        } else {
            sead::Vector3f pos;
            mActor->getMtx().getTranslation(pos);
            const sead::Vector3f up = getUpDir(mActor);

            sead::Vector3f dir = _1b8 - pos;
            ksys::util::sub_71011EFA00(&dir, dir, up);
            dir.normalize();

            _1c4 += (1.0f - std::pow(1.0f - _68, ksys::VFR::instance()->getDeltaFrame())) * (_70 - _1c4);
            sub_710074006C(&_190, dir, up, true, _6c, _1c4, 0.0f);
            sub_7100740F1C(_190, mActor);
            sub_7100738488(mActor, 0.14f, -sead::Vector3f::ey);
        }
    } else {
        sub_7100738488(mActor, 0.14f, -sead::Vector3f::ey);
        sub_7100738AA8(mActor, 0.45f);
    }
}

void AnimalLegTurnAutoSpeed::sub_710008FAC0() {
    sead::Vector3f dir;
    dir.set(*mTargetPos_d);
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    dir -= pos;
    dir.y = 0;
    dir.normalize();

    sead::Vector3f forward;
    sub_71000891C8(&forward, mActor);
    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, forward, dir, sead::Vector3f::ey);
    mActor->getASList()->x_6(9, 0, sead::Mathf::rad2deg(angle) * axis.y);
}

}  // namespace uking::action
