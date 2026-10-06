#include "Game/AI/Action/actionRisingAirOneTime.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

RisingAirOneTime::RisingAirOneTime(const InitArg& arg) : AscendingCurrent(arg) {}

RisingAirOneTime::~RisingAirOneTime() = default;

bool RisingAirOneTime::init_(sead::Heap* heap) {
    return AscendingCurrent::init_(heap);
}

void RisingAirOneTime::enter_(ksys::act::ai::InlineParamPack* params) {
    AscendingCurrent::enter_(params);
    _88.mTimer = ksys::Timer(-1.0f, -1.0f, 0.0f);
    mActor->setFlag(ksys::act::Actor::ActorFlag::_2c, true);
}

void RisingAirOneTime::leave_() {
    AscendingCurrent::leave_();
}

void RisingAirOneTime::loadParams_() {
    AscendingCurrent::loadParams_();
    getStaticParam(&mLostCounter_s, "LostCounter");
}

void RisingAirOneTime::calc_() {
    AscendingCurrent::calc_();

    const f32 eps = sead::Mathf::epsilon();
    if (_88.mTimer.value <= eps) {
        bool rising;
        {
            ksys::act::acc::PlayerBase player;
            player.getPlayerFromPlayerInfo();
            rising = player.isRisingInAirMaybe();
        }
        if (rising) {
            bool m200;
            {
                ksys::act::acc::PlayerBase player;
                player.getPlayerFromPlayerInfo();
                m200 = player.m200();
            }
            if (m200) {
                const f32 lost = *mLostCounter_s;
                _88.mTimer = ksys::Timer(lost, lost, -1.0f);
            }
        }
    }

    bool rising;
    {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        rising = player.isRisingInAirMaybe();
    }
    if (!rising) {
        if (!(_88.mTimer.value <= eps))
            _88.sub_7100D3BCE4();
        if (_88.mTimer.value <= eps)
            setFinished();
    }
}

void RisingAirOneTime::m32() {
    _28._2c = true;
    _28.sub_71010F16FC();
}

}  // namespace uking::action
