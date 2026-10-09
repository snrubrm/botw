#include "Game/AI/Action/actionSoundReverbAreaTagAction.h"
#include "KingSystem/Utils/InitTimeInfo.h"
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/Sound/sndFxMgr.h"
#include <cstring>

namespace uking::action {

namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

SoundReverbAreaTagAction::SoundReverbAreaTagAction(const InitArg& arg) : AreaTagAction(arg) {}

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
    AreaTagAction::enter_(params);
    std::memset(_b0.getBufferPtr(), 0, _b0.getByteSize());
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
    AreaTagAction::calc_();
}

}  // namespace uking::action
