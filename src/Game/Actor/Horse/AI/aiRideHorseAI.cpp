#include "Game/Actor/Horse/AI/aiRideHorseAI.h"
#include "Game/Actor/aiUnk_7100E81220.h"
#include "Game/Actor/actRideable.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

RideHorseAI::RideHorseAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RideHorseAI::~RideHorseAI() = default;

bool RideHorseAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RideHorseAI::enter_(ksys::act::ai::InlineParamPack* params) {
    _40 = 0;
    ksys::act::ActorLinkConstDataAccess accessor;
    if (!sub_7100E81220(mActor, &accessor)) {
        setFailed();
        return;
    }

    uking::act::Unk_7100e8b2b8* rideable = accessor.getHorseOptions();
    if (rideable && rideable->_8 & 0x400) {
        ksys::act::ai::InlineParamPack pack;
        pack.addBool(*mHasToPlayRidingOnAS_d, "HasToPlayRidingOnAS", -1);
        changeChild("なだめる", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addBool(*mHasToPlayRidingOnAS_d, "HasToPlayRidingOnAS", -1);
        changeChild("乗る", &pack);
    }
}

// NON_MATCHING: stack slot of the Unk8 temporary (the original reuses the param pack area)
void RideHorseAI::calc_() {
    if (++_40 < 2)
        return;
    auto* ride = act::getRideActor(mActor);
    if (!ride)
        return;
    auto* priority = ride->getMotorcyclePriorityStuffMaybe();
    if (!priority) {
        setFailed();
        return;
    }
    auto* rideable = ride->getHorseOptionsMaybe();
    auto* child = getCurrentChild();
    const char* name = child->getName();

    if (child->isFinished()) {
        if (rideable && (rideable->Unk_7100e8b2b8::_8 & 0x400) && (rideable->RideableBase::_8 & 0x800)) {
            ksys::act::ai::InlineParamPack pack;
            pack.addBool(false, "HasToPlayRidingOnAS", -1);
            changeChild("なだめる", &pack);
        } else {
            ksys::act::ai::InlineParamPack pack;
            pack.addBool(false, "HasToPlayRidingOnAS", -1);
            changeChild("乗る", &pack);
        }
        return;
    }

    if (child->isFailed()) {
        setFailed();
        return;
    }
    if (!child->isChangeable())
        return;

    if (int(act::Unk_7100e8b2b8::Unk8(priority->_8 & 0xff)) == act::Unk_7100e8b2b8::Unk8::_0) {
        setFailed();
        return;
    }
    if (!rideable)
        return;

    if ((rideable->Unk_7100e8b2b8::_8 & 0x400) && sead::SafeString(name) == "乗る") {
        ksys::act::ai::InlineParamPack pack;
        pack.addBool(false, "HasToPlayRidingOnAS", -1);
        changeChild("なだめる", &pack);
        return;
    }
    if (!(rideable->Unk_7100e8b2b8::_8 & 0x400) && sead::SafeString(name) == "なだめる") {
        ksys::act::ai::InlineParamPack pack;
        pack.addBool(false, "HasToPlayRidingOnAS", -1);
        changeChild("乗る", &pack);
    }
}

void RideHorseAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RideHorseAI::loadParams_() {
    getDynamicParam_2(&mHasToPlayRidingOnAS_d, "HasToPlayRidingOnAS");
}

}  // namespace uking::ai
