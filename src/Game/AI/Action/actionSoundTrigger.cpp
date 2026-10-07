#include "Game/AI/Action/actionSoundTrigger.h"
#include <xlink2/xlink2Event.h>
#include <xlink2/xlink2Locator.h>
#include <xlink2/xlink2UserInstance.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "Game/UI/uiUtils.h"
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtEventFlow.h"
#include "KingSystem/Event/evtEventResource.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace uking::action {

SoundTrigger::SoundTrigger(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SoundTrigger::~SoundTrigger() = default;

bool SoundTrigger::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SoundTrigger::enter_(ksys::act::ai::InlineParamPack* params) {
    getDynamicParam_2(&mSoundDelay_d, "SoundDelay");
    getDynamicParam(&mSound_d, "Sound");
    getDynamicParam(&mSLinkInst_d, "SLinkInst");
    _48 = *mSoundDelay_d;
    if (_48 <= 0) {
        if (!sub_7100E16614())
            setFailed();
        _48 = -1;
    }
    _60 = false;
}

bool SoundTrigger::sub_7100E16614() {
    _50.reset();
    if (auto* event = ksys::evt::Manager::instance()->getActiveEvent()) {
        event->getFrameCount();
        if (auto* info = ksys::evt::Manager::instance()->sub_7100DB137C()) {
            if (auto* xlink = info->sub_7100DC9628()) {
                if (auto* user = xlink->_50) {
                    xlink2::Locator locator;
                    if (user->searchAsset(&locator, mSound_d.cstr())) {
                        user->emit(locator, &_50);
                        return true;
                    }
                }
            }
        }
    }
    if (mActor) {
        if (auto* xlink = mActor->getXLink()) {
            if (auto* user = xlink->_50) {
                xlink2::Locator locator;
                if (user->searchAsset(&locator, mSound_d.cstr())) {
                    user->emit(locator, &_50);
                    return true;
                }
            }
        }
    }
    if (auto* user = ksys::snd::Unk_710104e5b4::instance()->_28) {
        xlink2::Locator locator;
        if (user->searchAsset(&locator, mSound_d.cstr())) {
            user->emit(locator, &_50);
            return true;
        }
    }
    uking::ui::playSound("Dummy_SoundTrigger", nullptr);
    return false;
}

void SoundTrigger::leave_() {
    ksys::act::ai::Action::leave_();
}

void SoundTrigger::loadParams_() {}

void SoundTrigger::calc_() {
    if (mSound_d.isEmpty())
        return;
    if (_48 == 0) {
        if (!sub_7100E16614())
            setFailed();
    } else if (_48 < 0) {
        if (!isFinished() && !isFailed()) {
            if (_50.isActive()) {
                const bool had_asset = _60;
                const s32 num = _50.getEvent()->getAliveAssetNum();
                if (had_asset) {
                    if (num == 0)
                        setFinished();
                } else if (num != 0) {
                    _60 = true;
                }
            } else {
                setFinished();
            }
        }
    }
    --_48;
}

}  // namespace uking::action
