#include "Game/AI/Action/actionForkASTrgRemainsHowl.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::action {

ForkASTrgRemainsHowl::ForkASTrgRemainsHowl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgRemainsHowl::~ForkASTrgRemainsHowl() = default;

bool ForkASTrgRemainsHowl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: accessor address caching and stack placement differ.
void ForkASTrgRemainsHowl::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100142EC4(true);
    ksys::act::acc::PlayerBase player;
    if (player.getPlayerFromPlayerInfo())
        sendMessage(*player.getMessageTransceiverId(), ksys::MessageType(0x080000B2), nullptr);
    mFlags.set(Flag::Changeable);
    sub_7100143068();
    sub_7100143180();
}

void ForkASTrgRemainsHowl::leave_() {
    sub_7100142EC4(false);
}

void ForkASTrgRemainsHowl::loadParams_() {
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getDynamicParam(&mIsTargetLost_d, "IsTargetLost");
}

void ForkASTrgRemainsHowl::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
