#include "Game/Actor/AI/aiWarpTagRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/World/worldManager.h"
#include <algorithm>
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/System/GameConfig.h"
#include "KingSystem/World/worldEnvMgr.h"

namespace uking::ai {

// NON_MATCHING: store order only (the original writes _38 after the _68 / _78 stores)
WarpTagRoot::WarpTagRoot(const InitArg& arg) : ksys::act::ai::Ai(arg), _48() {
    _38.value = 0;
    _38.prev_value = 0;
}

WarpTagRoot::~WarpTagRoot() = default;

bool WarpTagRoot::init_(sead::Heap* heap) {
    _78 = false;
    return true;
}

void WarpTagRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _38.value = 0;
    _38.prev_value = 0;
    _78 = false;
    _79 = false;
    _68 = ksys::world::Manager::instance()->getPlayerPos();
    mActor->m107();
}

// 0x71005eb760
// NON_MATCHING: the original takes &_38 once at the start, evaluates checkBasicSig before `waiting` in the fog switch
// and branches differently around the mist intensity.
void WarpTagRoot::calc_() {
    mActor->m107();

    bool far = false;
    bool waiting = false;
    if (_78) {
        if ((_68 - ksys::world::Manager::instance()->getPlayerPos()).length() >= 10.0f) {
            mActor->emitBasicSigOff();
            far = true;
        } else {
            _38.chase(1.0f, 0.011f);
            mActor->emitBasicSigOn();
            _74 = 60.0f;
            ksys::world::Manager::instance()->getEnvMgrUnchecked()->set6b60e(true);
        }
    } else {
        mActor->emitBasicSigOff();
        if (!mActor->checkBasicSig()) {
            _38.chase(0.0f, 0.02f);
        } else if (_38.value < ksys::world::Manager::instance()->getEnvMgrUnchecked()->getWarpMistIntensity()) {
            waiting = true;
        } else {
            _38.chase(1.0f, 0.011f);
            auto* wm = ksys::world::Manager::instance();
            if (_38.value >= 1.0f && !wm->getEnvMgrUnchecked()->get6b60e()) {
                _78 = true;
                _68 = wm->getPlayerPos();
            }
            if (!wm->getEnvMgrUnchecked()->get6b60e())
                wm->getEnvMgrUnchecked()->set6b60f(true);
        }
    }
    _38.updateStats();

    if (!ksys::GameConfig::getInstance()->_3d8) {
        auto* player_link = ksys::act::ActorSystem::instance()->getPlayerLink();
        switch (_79) {
        case 0:
            if (mActor->checkBasicSig() && !waiting) {
                if (player_link) {
                    xlinkSearchAndEmit(player_link->getPlayer(), "MayoiReturnFog", 2, &_48);
                    if (ksys::snd::sub_7100FFDDF0())
                        ksys::snd::sub_7100FFDDF0()->sub_7101013F70(true);
                }
                ++_79;
            }
            break;
        case 1:
            if (!mActor->checkBasicSig()) {
                _79 = 0;
                _38.value = 0;
                _38.prev_value = 0;
                if (_78) {
                    sub_710124127C(player_link->getPlayer(), 2);
                    _78 = false;
                    if (_74 != 0.0f) {
                        ksys::world::Manager::instance()->getEnvMgrUnchecked()->set6b60e(false);
                        _74 = 0.0f;
                    }
                } else {
                    _48.fadeXLink();
                    if (ksys::snd::sub_7100FFDDF0())
                        ksys::snd::sub_7100FFDDF0()->sub_7101013F70(false);
                }
            }
            break;
        }
    }

    if (_74 != 0.0f || (!far && _79 != 0)) {
        const f32 intensity = std::min(_74 != 0.0f ? 1.0f : _38.value, 1.0f);
        ksys::world::Manager::instance()->getEnvMgr()->setWarpMistIntensity(intensity);
    }
    if (_74 != 0.0f)
        _74 -= 1.0f;
}

void WarpTagRoot::leave_() {
    _48.fadeXLink();
}

void WarpTagRoot::loadParams_() {}

}  // namespace uking::ai
