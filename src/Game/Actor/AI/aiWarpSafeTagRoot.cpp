#include <algorithm>
#include "Game/Actor/AI/aiWarpSafeTagRoot.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/System/GameConfig.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"

namespace uking::ai {

WarpSafeTagRoot::WarpSafeTagRoot(const InitArg& arg) : ksys::act::ai::Ai(arg), _48() {
    _38.value = 0;
    _38.prev_value = 0;
}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
WarpSafeTagRoot::~WarpSafeTagRoot() {
    ;
}

bool WarpSafeTagRoot::init_(sead::Heap* heap) {
    _68 = false;
    return true;
}

void WarpSafeTagRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _38.value = 0;
    _38.prev_value = 0;
    _68 = false;
    _69 = false;
    _6a = false;
    mActor->m107();
}

// 0x71005eb1a0
// NON_MATCHING: the two VFRValue stores after `_69 = 0` are paired into one (the original schedules the _68 load
// between them).
void WarpSafeTagRoot::calc_() {
    mActor->m107();

    bool player_lost = false;
    auto* player = act::PlayerInfo::instance()->getPlayer();
    if (player && player->m188() && player->sub_710084ACF0(-1.0f) == 2) {
        player_lost = true;
    } else if (_68) {
        _38.chase(1.0f, 0.011f);
        mActor->emitBasicSigOn();
        ksys::world::Manager::instance()->getEnvMgrUnchecked()->set6b60e(true);
    } else {
        mActor->emitBasicSigOff();
        if (mActor->checkBasicSig() && (!ksys::world::Manager::instance()->getEnvMgrUnchecked()->get6b610() || _6a)) {
            _6a = true;
            ksys::world::Manager::instance()->getEnvMgrUnchecked()->set6b610(true);
            const f32 intensity = ksys::world::Manager::instance()->getEnvMgrUnchecked()->getWarpMistIntensity();
            if (_38.value < intensity)
                _38.chase(intensity, 1.0f);
            _38.chase(1.0f, 0.011f);
            if (_38.value >= 1.0f && !ksys::world::Manager::instance()->getEnvMgrUnchecked()->get6b60e() &&
                !ksys::world::Manager::instance()->getEnvMgrUnchecked()->get6b60f()) {
                _68 = true;
            }
        } else {
            if (_38.value <= 0.0f && _6a) {
                ksys::world::Manager::instance()->getEnvMgrUnchecked()->set6b610(false);
                _6a = false;
            }
            _38.chase(0.0f, 0.02f);
        }
    }
    _38.updateStats();

    if (!ksys::GameConfig::getInstance()->_3d8) {
        auto* player_link = ksys::act::ActorSystem::instance()->getPlayerLink();
        switch (_69) {
        case 0:
            if (mActor->checkBasicSig() && !player_lost) {
                if (player_link) {
                    xlinkSearchAndEmit(player_link->getPlayer(), "MayoiReturnFog", 2, &_48);
                    if (ksys::snd::sub_7100FFDDF0())
                        ksys::snd::sub_7100FFDDF0()->sub_7101013F70(true);
                }
                ++_69;
            }
            break;
        case 1:
            if (!mActor->checkBasicSig() || player_lost) {
                _69 = 0;
                _38.value = 0;
                _38.prev_value = 0;
                if (_68) {
                    sub_710124127C(player_link->getPlayer(), 2);
                    _68 = false;
                } else {
                    _48.fadeXLink();
                    if (ksys::snd::sub_7100FFDDF0())
                        ksys::snd::sub_7100FFDDF0()->sub_7101013F70(false);
                }
            }
            break;
        }
    }

    auto* wm = ksys::world::Manager::instance();
    if (_69 && !wm->getEnvMgrUnchecked()->get6b60f() && _6a)
        wm->getEnvMgr()->setWarpMistIntensity(std::min(_38.value, 1.0f));
}

void WarpSafeTagRoot::leave_() {
    _48.fadeXLink();
}

void WarpSafeTagRoot::loadParams_() {}

}  // namespace uking::ai
