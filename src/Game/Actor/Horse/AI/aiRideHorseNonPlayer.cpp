#include "Game/Actor/Horse/AI/aiRideHorseNonPlayer.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/aiUnk_7100E81220.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"
#include "KingSystem/Mii/miiUMii.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/Map/mapObject.h"

namespace uking::ai {

RideHorseNonPlayer::RideHorseNonPlayer(const InitArg& arg) : ksys::act::ai::Ai(arg) {
    // the original stores the bind type again after the ModelBindInfo constructor (`str wzr, [this, #0xd0]`)
    _38._98 = 0;
}

RideHorseNonPlayer::~RideHorseNonPlayer() = default;

bool RideHorseNonPlayer::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: UMii gender branch and saved receiver/register scheduling.
void RideHorseNonPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    _d8 = 0;
    if (!mActor->getModelBindInfo() && m35()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        sub_7100E81220(mActor, &accessor);
        f32 height = 0.0f;
        if (auto* rideable = accessor.getHorseRideStuff())
            height = rideable->procLink13();
        if (auto* umii = mActor->getUMii()) {
            if (auto* global = ksys::act::GlobalParameter::instance()) {
                if (auto* params = global->getGlobalParam()) {
                    if (umii->isFemale())
                        height += params->mHorseBindOffsetYOfFemaleUMii.ref();
                    else
                        height += params->mHorseBindOffsetYOfMaleUMii.ref();
                }
            }
        }
        _38.x(*act::sub_7100E811F0(mActor));
        auto* rideable = accessor.getHorseRideStuff();
        const sead::SafeString& bone =
            rideable ? rideable->sub_7100E8B524() : sead::SafeString::cEmptyString;
        _38._28 = bone.cstr();
        _38._30.getKey().reset();
        _38._68.makeRT(sead::Vector3f::zero, {0.0f, height, 0.0f});
        mActor->sub_71011DA824(&_38);
    }
    m36();
}

void RideHorseNonPlayer::leave_() {
    auto* actor = mActor;
    auto* map_object = actor->getMapObject();
    if (actor->get1a0() ||
        (map_object && map_object->getFlags0().isOn(ksys::map::Object::Flag0::_20000)) ||
        testRootAiFlag(ksys::act::ai::RootAiFlag::_5)) {
        if (auto* ride_actor = act::getRideActor(actor)) {
            if (auto* rideable = ride_actor->getMotorcyclePriorityStuffMaybe())
                rideable->_10.setBitOn(Bit(Bit::_1));
        }
        return;
    }
    m34();
}

void RideHorseNonPlayer::m34() {
    auto* actor = mActor;
    if (auto* info = actor->getPlayerRideInfo())
        info->sub_7100E7C0EC();
    if (m35())
        actor->sub_71011DA834(&_38);
}

void RideHorseNonPlayer::calc_() {
    if (++_d8 < 2)
        return;
    auto* ride_actor = act::getRideActor(mActor);
    if (!ride_actor)
        return;
    if (int(act::Unk_7100e8b2b8::Unk8(ride_actor->getMotorcyclePriorityStuffMaybe()->_8 & 0xff)) ==
        act::Unk_7100e8b2b8::Unk8::_0) {
        setFailed();
        return;
    }
    auto* child = getCurrentChild();
    if (child->isFinished()) {
        setFinished();
        return;
    }
    if (child->isFailed())
        setFailed();
}

void RideHorseNonPlayer::loadParams_() {}

bool RideHorseNonPlayer::m35() {
    return true;
}

void RideHorseNonPlayer::m36() {
    changeChild("乗る");
}

}  // namespace uking::ai
