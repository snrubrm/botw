#include "Game/AI/AI/aiMasterSwordBase100EnemyRoot.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ai {

MasterSwordBase100EnemyRoot::MasterSwordBase100EnemyRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

MasterSwordBase100EnemyRoot::~MasterSwordBase100EnemyRoot() = default;

bool MasterSwordBase100EnemyRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MasterSwordBase100EnemyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    if (ksys::gdt::getFlag_100enemy_KillMasterSwordBaseAttention()) {
        ksys::act::disableAllAttClients(mActor);
        _80 = 0;
        changeChild("アテンションなし待機");
    } else {
        ksys::act::enableAllAttClients(mActor);
        _40.x();
        ksys::gdt::setFlag_100enemy_KillMasterSwordBaseAttention(false);
        changeChild("待機");
    }
}

void MasterSwordBase100EnemyRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MasterSwordBase100EnemyRoot::loadParams_() {
    getStaticParam(&mKillAttentionWaitFrame_s, "KillAttentionWaitFrame");
}

bool MasterSwordBase100EnemyRoot::handleMessage_(const ksys::Message* message) {
    return _40.sub_710070A674(*message);
}

}  // namespace uking::ai
