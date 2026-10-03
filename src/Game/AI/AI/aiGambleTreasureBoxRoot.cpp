#include "Game/AI/AI/aiGambleTreasureBoxRoot.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

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
