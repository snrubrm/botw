#include "Game/AI/AI/aiMoveAndFreeFallGondola.h"
#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

MoveAndFreeFallGondola::MoveAndFreeFallGondola(const InitArg& arg) : RailMove(arg) {}

MoveAndFreeFallGondola::~MoveAndFreeFallGondola() = default;

bool MoveAndFreeFallGondola::init_(sead::Heap* heap) {
    return RailMove::init_(heap);
}

void MoveAndFreeFallGondola::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!_f0) {
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        return;
    }
    RailMove::enter_(params);
}

// NON_MATCHING: the original calls `_40.m3()` through the vtable (not devirtualized) and ours calls
// Unk_71024f15c0::m3 directly (the call probably sits in an inline member of the rail follower)
void MoveAndFreeFallGondola::calc_() {
    RailMove::calc_();
    if (!isCurrentChild("停止") && _40.m3()) {
        auto* actor = sead::DynamicCast<ksys::act::Actor>(_b0.getProc(nullptr, nullptr));
        _c0.sub_710070DC38(actor, false);
        changeChild("停止");
    }
}

void MoveAndFreeFallGondola::m34() {}

ksys::map::Rail* MoveAndFreeFallGondola::m36() {
    if (sub_7100EEF034(mActor, 0))
        return RailMove::m36();
    return _f0;
}

f32 MoveAndFreeFallGondola::m35() {
    return *mRailMoveSpeed_m;
}

bool MoveAndFreeFallGondola::m40() {
    return false;
}

void MoveAndFreeFallGondola::leave_() {
    RailMove::leave_();
}

void MoveAndFreeFallGondola::loadParams_() {
    RailMove::loadParams_();
    getMapUnitParam(&mRailMoveSpeed_m, "RailMoveSpeed");
    getMapUnitParam(&mGondolaRailOffsetTime_m, "GondolaRailOffsetTime");
}

bool MoveAndFreeFallGondola::handleMessage_(const ksys::Message* message) {
    const ksys::MessageType type = message->getType();
    if (type == 0x3000003 || type == 0x3000004) {
        if (!isCurrentChild("停止"))
            sub_71004AF894(message);
    }
    return false;
}

}  // namespace uking::ai
