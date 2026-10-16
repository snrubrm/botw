#include "Game/Actor/AI/aiNPCTravelerRoot.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/ActorSystem/actActorX6A0.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "Game/Actor/aiUnk_71007130BC.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/Utils/Thread/Message.h"

// Source namespace and return spelling are inferred from the lifecycle callers.
void sub_71007136BC(ksys::act::Actor* actor);
void sub_7100713780(ksys::act::Actor* actor, bool value);

namespace uking::ai {

NPCTravelerRoot::NPCTravelerRoot(const InitArg& arg) : NPCRoot(arg) {}

NPCTravelerRoot::~NPCTravelerRoot() = default;

void NPCTravelerRoot::onPreDelete() {
    sub_71007136BC(mActor);
    sub_7100713780(mActor, false);
    NPCRoot::onPreDelete();
}

bool NPCTravelerRoot::init_(sead::Heap* heap) {
    if (!NPCRoot::init_(heap))
        return false;
    _248 = sead::DynamicCast<act::NPC>(mActor);
    return true;
}

// NON_MATCHING: the terror level test is `cmp 3; b.ge` in the original (ours `cmp 2; b.gt`).
void NPCTravelerRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if ((mActor->getRootAi()->getI() & ~1u) == 8) {
        sub_71004D9608();
        ksys::act::ai::InlineParamPack pack;
        pack.addBool(true, "IsWarpHorse", -1);
        changeChild("Rest", &pack);
        _240 = true;
        return;
    }

    if (auto* ride_info = mActor->getPlayerRideInfo(); ride_info && ride_info->_30 & 1) {
        sub_71004D9608();
        if (*mIsRiderChangableAction_s) {
            m34();
            return;
        }
        changeChild("Ride");
        return;
    }

    if (_240) {
        if (!_248 || _248->_1048 != 4 || _248->_c74 < 3) {
            sub_71004D9608();
            sead::Vector3f home_pos;
            mActor->getHomePos(&home_pos);
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(home_pos, "TargetPos", -1);
            changeChild("ReturnRestPos", &pack);
            return;
        }
    } else if (auto* schedule = mActor->getSchedule();
               schedule && !schedule->_b8.isEmpty() && _248) {
        if (auto* unk = _248->_840; unk && unk->sub_7100EEBB74())
            _248->_9d8.copy(unk->sub_7100EEEE88(mActor));
    }
    NPCRoot::enter_(params);
}

// NON_MATCHING: the original evaluates the timeline end condition without branches (cset / orr).
void NPCTravelerRoot::calc_() {
    if (isCurrentChild("Timeline")) {
        if (auto* schedule = mActor->getSchedule(); schedule && !schedule->_b8.isEmpty()) {
            _2a8.update();
            const f32 time = _2a8.value;
            const auto flags = mActor->_6a0->_a;
            const bool bad_weather = wm::callIsRainingOrSnowingOrThunderStorm(false);
            if ((time <= sead::Mathf::epsilon() && !bad_weather) ||
                (!schedule->_88.isEmpty() && flags.isOff(8) && bad_weather)) {
                schedule->_b8 = sead::SafeString::cEmptyString;
                if (_248)
                    _248->_f80 = nullptr;
            }
        }
    }

    if (auto* ride_info = mActor->getPlayerRideInfo(); ride_info && ride_info->_30 & 1)
        return;

    if (isCurrentChild("Terror")) {
        auto* child = getCurrentChild();
        if ((child->isFinished() || child->isFailed()) && _240) {
            sead::Vector3f home_pos;
            mActor->getHomePos(&home_pos);
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(home_pos, "TargetPos", -1);
            changeChild("ReturnRestPos", &pack);
            return;
        }
    }

    if (isCurrentChild("ReturnRestPos")) {
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            ksys::act::ai::InlineParamPack pack;
            pack.addBool(false, "IsWarpHorse", -1);
            changeChild("Rest", &pack);
            if (_248 && _248->_f70.hasProc()) {
                ksys::act::ActorLinkConstDataAccess accessor;
                ksys::act::acquireActor(&_248->_f70, &accessor);
                _250.mLock.lock();
                _250.mLink.acquire(mActor, false);
                _250._50 = 0.5f;
                sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3800008), &_250);
                _250.mLock.unlock();
                return;
            }
        }
    }
    NPCRoot::calc_();
}

void NPCTravelerRoot::m34() {
    if ((mActor->getRootAi()->getI() & ~1u) == 8) {
        sub_71004D9608();
        ksys::act::ai::InlineParamPack pack;
        pack.addBool(true, "IsWarpHorse", -1);
        changeChild("Rest", &pack);
        _240 = true;
        return;
    }

    if (auto* ride_info = mActor->getPlayerRideInfo(); ride_info && ride_info->_30 & 1) {
        sub_71004D9608();
        if (*mIsRiderChangableAction_s)
            changeChild("Timeline");
        else
            changeChild("Ride");
        return;
    }

    if (!_240) {
        NPCRoot::m34();
        return;
    }

    sub_71004D9608();
    sead::Vector3f home_pos;
    mActor->getHomePos(&home_pos);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(home_pos, "TargetPos", -1);
    changeChild("ReturnRestPos", &pack);
}

bool NPCTravelerRoot::handleMessage_(const ksys::Message* message) {
    if (NPCRoot::handleMessage_(message))
        return true;
    if (message && message->getType() == 0x8000077) {
        if (auto* value = static_cast<const f32*>(message->getUserData())) {
            _2a8 = ksys::Timer(*value, *value, -1.0f);
            return true;
        }
    }
    return false;
}

void NPCTravelerRoot::leave_() {
    NPCRoot::leave_();
}

void NPCTravelerRoot::loadParams_() {
    NPCRoot::loadParams_();
    getStaticParam(&mIsRiderChangableAction_s, "IsRiderChangableAction");
}

}  // namespace uking::ai
