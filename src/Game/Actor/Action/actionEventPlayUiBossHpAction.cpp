#include "Game/Actor/Action/actionEventPlayUiBossHpAction.h"
#include <random/seadGlobalRandom.h>
#include "Game/UI/uiScreens.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/System/UIGlue.h"

namespace uking::action {

EventPlayUiBossHpAction::EventPlayUiBossHpAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventPlayUiBossHpAction::~EventPlayUiBossHpAction() = default;

bool EventPlayUiBossHpAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPlayUiBossHpAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::gdt::setFlag_DispBossGaugeRate_Demo(1.0f);

    _28 = sead::DynamicCast<ui::Screen>(eui::ScreenMgr::instance()->getScreen(ui::ScreenId::MainScreen));
    if (_28) {
        ksys::ui::sub_7100EDC530(ui::ScreenId::MainScreen, nullptr);
        _28 = sead::DynamicCast<ui::Screen>(
            eui::ScreenMgr::instance()->getScreen(ui::ScreenId::MainScreen));
    }
    if (!_28) {
        setFailed();
        return;
    }

    if (*mClipIndex_d < 0) {
        _28->open(1);
    } else {
        const f32 frame = ksys::evt::Manager::instance()->sub_7100DB1174(*mClipIndex_d);
        _28->m73(frame);
    }

    {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (auto* link = ksys::evt::Manager::instance()->getBaseProcLinkFromActiveEvent(
                "Enemy_Ganon", sead::SafeString::cEmptyString))
            ksys::act::acquireActor(link, &accessor);
        if (accessor.hasProc())
            _30 = accessor.getId();
        else
            _30 = sead::GlobalRandom::instance()->getU32();
    }
    _34 = -1;
}

void EventPlayUiBossHpAction::leave_() {
    _28->m76();
}

void EventPlayUiBossHpAction::loadParams_() {
    getDynamicParam(&mClipIndex_d, "ClipIndex");
}

void EventPlayUiBossHpAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
