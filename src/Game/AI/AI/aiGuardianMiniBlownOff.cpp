#include "Game/AI/AI/aiGuardianMiniBlownOff.h"
#include <prim/seadScopedLock.h>
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

GuardianMiniBlownOff::GuardianMiniBlownOff(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianMiniBlownOff::~GuardianMiniBlownOff() {
    if (_48) {
        delete _48;
        _48 = nullptr;
    }
}

bool GuardianMiniBlownOff::init_(sead::Heap* heap) {
    _48 = new (heap) Unk_71023f83e8(mActor, 0x8000021);
    return _48 != nullptr;
}

// NON_MATCHING: only the registers of the three components of `dir` differ (the original keeps x, y, z in
// d11, d9, d10; ours in d9, d10, d11)
void GuardianMiniBlownOff::sub_7100419D88(f32 value) {
    if (!mActor)
        return;

    sead::Vector3f dir = sead::Vector3f::ey;
    dir *= *mRotNeckAngle_s;
    if (auto* manager = sub_710072BA90(mActor)) {
        sead::Vector3f pos;
        sead::Matrix34f mtx;
        if (manager->getAttackPos(&pos) && manager->m35(&mtx)) {
            pos.y = 0.0f;
            pos.normalize();
            const sead::Vector3f v = pos;
            pos.x = v.x * mtx(0, 0) + v.y * mtx(1, 0) + v.z * mtx(2, 0);
            pos.y = v.x * mtx(0, 1) + v.y * mtx(1, 1) + v.z * mtx(2, 1);
            pos.z = v.x * mtx(0, 2) + v.y * mtx(1, 2) + v.z * mtx(2, 2);
            sead::Vector3f axis;
            f32 angle;
            ksys::util::sub_71011EEB08(&axis, &angle, pos, sead::Vector3f::ez,
                                       sead::Vector3f::ey);
            if (axis.y < 0.0f)
                dir = -dir;
        }
    }

    _48->_18.set(dir, *mRotNeckSpeed_s * value);
    _48->sub_710070DBB0(*mActor->getMessageTransceiver().getId(), true);
}

void GuardianMiniBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100419D88(1.0f);
    changeChild("ふっとび", params);
}

void GuardianMiniBlownOff::calc_() {}

void GuardianMiniBlownOff::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianMiniBlownOff::loadParams_() {
    getStaticParam(&mRotNeckAngle_s, "RotNeckAngle");
    getStaticParam(&mRotNeckSpeed_s, "RotNeckSpeed");
}

bool GuardianMiniBlownOff::handleMessage_(const ksys::Message* message) {
    if (_50.m2(*message) && _50._34._10) {
        setFinished();
        return true;
    }
    return false;
}

}  // namespace uking::ai
