#include "Game/AI/Action/actionEventOpenGetDemo.h"
#include "Game/UI/uiUI.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

EventOpenGetDemo::EventOpenGetDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventOpenGetDemo::~EventOpenGetDemo() = default;

bool EventOpenGetDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: initializing the handle pointer is scheduled before the actor load.
void EventOpenGetDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    _28 = false;
    _29 = false;
    if (!*mIsInvalidOpenPouch_d) {
        u32* handle = nullptr;
        if (mActor->getRootAi()->getAITreeVariable(
                &handle, ksys::act::getStr_AtvKeyActorSaveDataIndex()) && handle) {
            ksys::gdt::Manager::instance()->setBool(true, ksys::gdt::FlagHandle(*handle));
            ui::uiManagerUpdateIsDungeon();
        }
    }
}

void EventOpenGetDemo::leave_() {
    if (auto* manager = ui::UI::instance()) {
        if (manager->sub_71010A5CAC())
            manager->sub_71010A6F04();
    }
}

void EventOpenGetDemo::loadParams_() {
    getDynamicParam(&mIsInvalidOpenPouch_d, "IsInvalidOpenPouch");
}

void EventOpenGetDemo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
