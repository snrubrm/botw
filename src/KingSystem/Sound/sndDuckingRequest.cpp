#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Event/evtManager.h"
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/Utils/InitTimeInfo.h"
#include "Game/Actor/actEnvSeEmitPoint.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Terrain/teraSystem.h"
#include <prim/seadScopedLock.h>
#include <aal/aalSpeakerBalanceUnifier.h>
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::snd {

// The TU's static initialiser is 0x710103ae20 (`_GLOBAL__sub_I_sndDuckingRequest.cpp`).
static util::InitTimeInfoEx sInitTimeInfo;

void Unk_710103AB10::calc() {
    auto* message = SoundMgr::instance()->_48;
    const bool playing = message->_18.isActive() || message->_28.isActive();
    const bool active = SoundMgr::instance()->mDuckingMgr->getDucker(mType).isActive();
    if (playing) {
        if (!active)
            SoundMgr::instance()->mDuckingMgr->sub_7101042024(mType);
    } else if (active) {
        SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(mType, false);
    }
}

Unk_710103AB10::~Unk_710103AB10() {
    if (SoundMgr::instance()->mDuckingMgr->getDucker(mType).isActive())
        SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(mType, false);
}

void Unk_710103AC60::calc() {
    if (!mActive)
        return;
    const bool event = evt::Manager::instance()->hasActiveEvent();
    const bool active = SoundMgr::instance()->mDuckingMgr->getDucker(mType).isActive();
    if (event) {
        if (active)
            SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(mType, false);
    } else if (!active) {
        SoundMgr::instance()->mDuckingMgr->sub_7101042024(mType);
    }
}

void Unk_710103AC60::start(s32 kind) {
    if (mActive)
        return;
    mType = kind == 1 ? DuckingMgr::DuckerType::cFieldRemainsFire : DuckingMgr::DuckerType::cFieldRemainsOrGanon;
    mActive = true;
}

void Unk_710103AC60::stop() {
    if (!mActive)
        return;
    SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(mType, false);
    mActive = false;
}

void Unk_710103ACC8::calc() {
    if (mActive) {
        const bool event = evt::Manager::instance()->hasActiveEvent();
        const bool active = SoundMgr::instance()->mDuckingMgr->getDucker(mType).isActive();
        if (event) {
            if (active)
                SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(mType, false);
        } else if (!active) {
            SoundMgr::instance()->mDuckingMgr->sub_7101042024(mType);
        }
    } else if (mHoldFrames > 0 && --mHoldFrames == 0) {
        SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(mType, false);
    }
}

void Unk_710103ACC8::start() {
    if (!mActive)
        mActive = true;
    mHoldFrames = 0;
}

void Unk_710103ACC8::stop(bool hold) {
    if (!mActive)
        return;
    if (hold)
        mHoldFrames = 120;
    else
        SoundMgr::instance()->mDuckingMgr->sub_7101042D6C(mType, false);
    mActive = false;
}

}  // namespace ksys::snd
