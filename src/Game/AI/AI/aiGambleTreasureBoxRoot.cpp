#include "Game/AI/AI/aiGambleTreasureBoxRoot.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtMetadata.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::act {
struct WeaponModifierInfo;
}

bool actorHasTagCanGetPouch(const sead::SafeString& actor_name);
void getDemoGetAnotherActor(ksys::act::Actor* actor, const sead::SafeString& actor_name,
                           bool can_get_pouch, bool option, uking::act::WeaponModifierInfo* modifier);

namespace uking::ai {

GambleTreasureBoxRoot::GambleTreasureBoxRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GambleTreasureBoxRoot::~GambleTreasureBoxRoot() = default;

bool GambleTreasureBoxRoot::init_(sead::Heap* heap) {
    *mIsOpenTreasureBox_a = false;
    return true;
}

void GambleTreasureBoxRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsOpenTreasureBox_a) {
        ksys::act::disableAttClient(mActor, "Open");
        changeChild("オープン待機");
    } else {
        ksys::act::enableAttClient(mActor, "Open");
        _48.x();
        changeChild("クローズ待機");
    }
}

void GambleTreasureBoxRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GambleTreasureBoxRoot::calc_() {
    auto* actor = mActor;
    if (isCurrentChild("クローズ待機")) {
        if (!_48._30)
            return;
        auto* data_mgr = ksys::gdt::Manager::instance();
        if (!data_mgr)
            return;
        bool activated = false;
        data_mgr->getParam().get().getBool(&activated, "MiniGame_GambleTreasureBox_Activated");
        if (activated) {
            const bool can_get_pouch = actorHasTagCanGetPouch(*mDropActorName_a);
            getDemoGetAnotherActor(actor, *mDropActorName_a, can_get_pouch, true, nullptr);
            if (can_get_pouch)
                ksys::act::disableAttClient(mActor, "Open");
        } else if (auto* event_mgr = ksys::evt::Manager::instance()) {
            _48.x();
            ksys::evt::Metadata metadata("MiniGame_GambleTreasureBox", "OpenWithoutPermission", "");
            event_mgr->callEvent(metadata, mActor, nullptr);
        }
    } else if (getCurrentChild()->isFinished()) {
        ksys::act::disableAttClient(mActor, "Open");
        changeChild("オープン待機");
    }
}

void GambleTreasureBoxRoot::loadParams_() {
    getAITreeVariable(&mIsOpenTreasureBox_a, "IsOpenTreasureBox");
    getAITreeVariable(&mDropActorName_a, "DropActorName");
}

bool GambleTreasureBoxRoot::handleMessage_(const ksys::Message* message) {
    if (isCurrentChild("クローズ待機") && _48.m2(*message))
        return true;
    return false;
}

}  // namespace uking::ai
