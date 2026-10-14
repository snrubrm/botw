#include "Game/Actor/Action/actionHideShootArrow.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"

namespace uking::action {

HideShootArrow::HideShootArrow(const InitArg& arg) : ShootArrow(arg) {}

HideShootArrow::~HideShootArrow() = default;

void HideShootArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    ShootArrow::enter_(params);
    playAS(mShootStartASName_s.cstr(), false, 0, 0, -1.0f);
    _e8 = 0;
}

void HideShootArrow::leave_() {
    ShootArrow::leave_();
}

void HideShootArrow::loadParams_() {
    ShootArrow::loadParams_();
    getStaticParam(&mShootStartASName_s, "ShootStartASName");
    getStaticParam(&mShootASName_s, "ShootASName");
    getStaticParam(&mShootEndASName_s, "ShootEndASName");
    getStaticParam(&mLoopTime_s, "LoopTime");
}

void HideShootArrow::calc_() {
    switch (_e8) {
    case 0:
        sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(4));
        if (isFinishedAS(0, 0)) {
            playAS(mShootASName_s.cstr(), false, 0, 0, -1.0f);
            _ec.reset(*mLoopTime_s);
            _e8 = 1;
        }
        break;
    case 1:
        sub_71005D787C(mActor, *mWeaponIdx_s, act::Unk_71002eda38(4));
        _ec.update();
        if (_ec.value <= sead::Mathf::epsilon()) {
            playAS(mShootEndASName_s.cstr(), false, 0, 0, -1.0f);
            _e8 = 2;
        }
        break;
    case 2:
        if (sub_71005DD780(mActor, 71, nullptr, 0, 0)) {
            sead::Vector3f target;
            sead::Vector3f pos;
            if (sub_710024EB30(&target, &pos))
                m33(pos, &target);
            else
                m33(pos, nullptr);
        }
        if (isFinishedAS(0, 0))
            setFinished();
        break;
    }
    sub_710024E90C();
    sub_710024E994();
}

void HideShootArrow::m32() {}

}  // namespace uking::action
