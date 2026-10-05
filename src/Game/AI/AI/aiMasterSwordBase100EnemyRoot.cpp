#include "Game/AI/AI/aiMasterSwordBase100EnemyRoot.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/System/VFR.h"

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

// NON_MATCHING: The listener member address uses a writeback load instead of a separate add.
void MasterSwordBase100EnemyRoot::calc_() {
    auto* child = getCurrentChild();
    if (!isCurrentChild("起動") && (child->isChangeable() || child->isFinished())) {
        if (isCurrentChild("アテンションなし待機")) {
            if (_80 >= *mKillAttentionWaitFrame_s) {
                ksys::act::enableAllAttClients(mActor);
                _40.x();
                ksys::gdt::setFlag_100enemy_KillMasterSwordBaseAttention(false);
                changeChild("待機", nullptr);
            } else {
                _80 += ksys::VFR::instance()->getDeltaTime() * 30.0f;
            }
        } else if (isCurrentChild("待機")) {
            if (ksys::gdt::getFlag_100enemy_KillMasterSwordBaseAttention()) {
                ksys::act::disableAllAttClients(mActor);
                _80 = 0;
                changeChild("アテンションなし待機", nullptr);
            } else if (_40._30) {
                ksys::act::disableAllAttClients(mActor);
                _40.x();
                changeChild("起動", nullptr);
            }
        }
    } else if (isCurrentChild("起動")) {
        if (ksys::gdt::getFlag_100enemy_KillMasterSwordBaseAttention()) {
            ksys::act::disableAllAttClients(mActor);
            _80 = 0;
            changeChild("アテンションなし待機", nullptr);
        } else {
            ksys::act::enableAllAttClients(mActor);
            _40.x();
            ksys::gdt::setFlag_100enemy_KillMasterSwordBaseAttention(false);
            changeChild("待機", nullptr);
        }
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
