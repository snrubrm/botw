#include "Game/Actor/Action/actionSiteBossSpearChangeWaterLevel.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/System/VFR.h"
#include <cmath>
#include <limits>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

SiteBossSpearChangeWaterLevel::SiteBossSpearChangeWaterLevel(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossSpearChangeWaterLevel::~SiteBossSpearChangeWaterLevel() = default;

bool SiteBossSpearChangeWaterLevel::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossSpearChangeWaterLevel::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    mActor->getMtx().getTranslation(_3c);
    _48 = ksys::Timer(240.0f, 240.0f);
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5FB24(sead::Vector3f::zero);
    _38 = false;
}

void SiteBossSpearChangeWaterLevel::leave_() {
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5F6FC(sead::Vector3f::zero);
}

void SiteBossSpearChangeWaterLevel::loadParams_() {
    getStaticParam(&mIsSignalOn_s, "IsSignalOn");
    getStaticParam(&mASName_s, "ASName");
}

// NON_MATCHING: operand order of the velocity scale and load scheduling of the water-level target.
void SiteBossSpearChangeWaterLevel::calc_() {
    ksys::as::ASList::Unk4 query;
    if (sub_71005DD5B0(mActor, 0x2f, &query, 0, 0)) {
        sead::Vector3f home;
        mActor->getHomePos(&home);
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
            boss->sub_71002D2A5C(17, true);
        _3c = home;
        _3c.y += 3.0f;
        sead::Matrix34f home_mtx;
        mActor->getHomeMtx(&home_mtx);
        home_mtx.setTranslation(_3c);
        mActor->sub_71011C8B04(home_mtx);
    }

    if (sub_71005DD780(mActor, 0x39, &query, 0, 0)) {
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
            if (*mIsSignalOn_s) {
                mActor->emitBasicSigOn();
                boss->_1558.setBit(12);
            } else {
                mActor->emitBasicSigOff();
                boss->_1558.resetBit(12);
            }
        }
    }

    bool arrived = false;
    if (auto* controller = mActor->getCharacterController()) {
        const auto& mtx = mActor->getMtx();
        if (sead::Mathf::abs(mtx(1, 3) - _3c.y) < 0.01f) {
            controller->sub_7100F5F6FC(sead::Vector3f::zero);
            arrived = true;
        } else {
            sead::Vector3f velocity;
            sead::Vector3f dir = _3c;
            dir -= mtx.getTranslation();
            const f32 distance = dir.length();
            if (distance > 0.0f)
                dir *= 1.0f / distance;
            controller->sub_7100F5F598(&velocity);
            f32 speed = velocity.length();
            ksys::VFR::lerp(&speed, distance, 0.1f);
            speed = std::fmax(speed, 0.01f);
            dir = dir * speed;
            controller->sub_7100F5F6FC(dir);
        }
    }

    _48.update();
    const bool done = _48.value <= std::numeric_limits<f32>::epsilon() || arrived;
    if (isFinishedAS(0, 0)) {
        _38 = true;
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor))
            boss->sub_71002D2A5C(17, true);
        playAS("Wait", false, 0, 0, -1.0f);
    }
    if (done && _38)
        setFinished();
}

}  // namespace uking::action
