#include "KingSystem/Sound/sndSound.h"
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

}  // namespace ksys::snd
