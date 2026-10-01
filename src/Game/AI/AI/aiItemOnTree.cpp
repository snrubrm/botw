#include "Game/AI/AI/aiItemOnTree.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

ItemOnTree::ItemOnTree(const InitArg& arg) : ItemRoot(arg) {}

ItemOnTree::~ItemOnTree() = default;

bool ItemOnTree::init_(sead::Heap* heap) {
    return ItemRoot::init_(heap);
}

void ItemOnTree::enter_(ksys::act::ai::InlineParamPack* params) {
    _a8 = 0;
    _ac = 0;
    _b0 = 0;
    _b4 = false;
    _b5 = false;
    ItemRoot::enter_(params);
}

void ItemOnTree::leave_() {
    ItemRoot::leave_();
}

void ItemOnTree::loadParams_() {
    ItemRoot::loadParams_();
    getStaticParam(&mFallPowerMin_s, "FallPowerMin");
    getStaticParam(&mFallPowerMax_s, "FallPowerMax");
    getStaticParam(&mFallOddsMin_s, "FallOddsMin");
    getStaticParam(&mFallOddsMax_s, "FallOddsMax");
    getStaticParam(&mFallIntervalRange_s, "FallIntervalRange");
    getStaticParam(&mFallCheckSpeedTh_s, "FallCheckSpeedTh");
    getStaticParam(&mAttOnTree_s, "AttOnTree");
    getStaticParam(&mAttOnGround_s, "AttOnGround");
}

bool ItemOnTree::handleMessage_(const ksys::Message& message) {
    if (isCurrentChild("通常") && message.getType().value == 0x800001c) {
        if (message.getUserData())
            _a8 = *static_cast<const int*>(message.getUserData());
        _b4 = true;
    }
    return false;
}

}  // namespace uking::ai
