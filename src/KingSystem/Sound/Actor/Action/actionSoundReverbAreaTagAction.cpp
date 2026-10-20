#include "KingSystem/Sound/Actor/Action/actionSoundReverbAreaTagAction.h"
#include "KingSystem/Utils/InitTimeInfo.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Sound/sndFxMgr.h"
#include <cstring>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/Profiles/actAreaActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace ksys::snd {

namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

SoundReverbAreaTagAction::SoundReverbAreaTagAction(const InitArg& arg) : AreaActionBase(arg) {}

// NON_MATCHING: the root destructor remains out of line to preserve its own D1 definition.
SoundReverbAreaTagAction::~SoundReverbAreaTagAction() {
    _a0.freeBuffer();
}

bool SoundReverbAreaTagAction::init_(sead::Heap* heap) {
    _a0.tryAllocBuffer(1, heap);
    if (!_a0.getBufferPtr())
        return false;
    _a0[0]._0 = ksys::phys::ContactLayer::SensorPlayer;
    return true;
}

void SoundReverbAreaTagAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaActionBase::enter_(params);
    std::memset(_b0, 0, sizeof(_b0));
    sub_7101059880(0);
    if (auto* sound = ksys::snd::SoundMgr::instance()) {
        if (auto* fx = sound->_50) {
            if (auto* reverb = fx->_50)
                reverb->sub_7101059B14(this);
        }
    }
}

void SoundReverbAreaTagAction::leave_() {
    if (auto* sound = ksys::snd::SoundMgr::instance()) {
        if (auto* fx = sound->_50) {
            if (auto* reverb = fx->_50)
                reverb->sub_7101059B8C(this);
        }
    }
}

void SoundReverbAreaTagAction::loadParams_() {
    getMapUnitParam(&mReverbSendAdd_m, "ReverbSendAdd");
    getMapUnitParam(&mReverbTimeAdd_m, "ReverbTimeAdd");
    getMapUnitParam(&mEarlyReflectionFeedbackAdd_m, "EarlyReflectionFeedbackAdd");
    getMapUnitParam(&mRoomHfAdd_m, "RoomHfAdd");
    getMapUnitParam(&mReverbAdd_m, "ReverbAdd");
    getMapUnitParam(&mMerginDistance_m, "MerginDistance");
    if (mReverbSendAdd_m)
        _134 = *mReverbSendAdd_m;
    if (mReverbTimeAdd_m)
        _138 = *mReverbTimeAdd_m;
    if (mEarlyReflectionFeedbackAdd_m)
        _13c = *mEarlyReflectionFeedbackAdd_m;
    if (mRoomHfAdd_m)
        _140 = *mRoomHfAdd_m;
    if (mReverbAdd_m)
        _144 = *mReverbAdd_m;
    if (mMerginDistance_m)
        _148 = *mMerginDistance_m;
}

void SoundReverbAreaTagAction::calc_() {
    AreaActionBase::calc_();
}

// NON_MATCHING: stack slot of the accessor and loop block layout differ (as in SoundShieldingAreaTagAction::m15).
bool SoundReverbAreaTagAction::m15(const ksys::act::ActorLinkConstDataAccess& accessor) {
    if (_130) {
        sub_7101059848(_134);
        sub_7101059850(_138);
        sub_7101059858(_13c);
        sub_7101059860(_140);
        sub_7101059868(_144);
        sub_7101059870(_148);
    } else {
        if (mReverbSendAdd_m)
            sub_7101059848(*mReverbSendAdd_m);
        if (mReverbTimeAdd_m)
            sub_7101059850(*mReverbTimeAdd_m);
        if (mEarlyReflectionFeedbackAdd_m)
            sub_7101059858(*mEarlyReflectionFeedbackAdd_m);
        if (mRoomHfAdd_m)
            sub_7101059860(*mRoomHfAdd_m);
        if (mReverbAdd_m)
            sub_7101059868(*mReverbAdd_m);
        if (mMerginDistance_m)
            sub_7101059870(*mMerginDistance_m);
    }

    ksys::act::acc::AreaActor area;
    f32 value = 0.0f;
    s32 index = getAreaCol(&area, -1);
    if (index >= 0 && index < 32) {
        f32 max_distance = 0.0f;
        do {
            if (area.hasProc()) {
                auto* collision = area.getField848();
                if (collision && collision->getCollidingBodies().size() != 0) {
                    if (auto* contacts = area.getField850()) {
                        if (contacts->getNumContactPoints() != 0 && !contacts->begin().isEnd()) {
                            f32 distance = 0.0f;
                            for (const auto* point : *contacts)
                                distance = sead::Mathf::max(
                                    sead::Mathf::abs(point->separating_distance), distance);
                            _b0[index] = distance;
                        }
                        max_distance = sead::Mathf::max(_b0[index], max_distance);
                    }
                } else {
                    _b0[index] = 0.0f;
                }
            }
            index = getAreaCol(&area, index);
        } while (index >= 0 && index < 32);
        if (max_distance > 0.0f)
            value = max_distance >= _1c ? 1.0f : max_distance / _1c;
    }
    sub_7101059878(value);
    sub_7101059880(1);
    return true;
}

}  // namespace ksys::snd
