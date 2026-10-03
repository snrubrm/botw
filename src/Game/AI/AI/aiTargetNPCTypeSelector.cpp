#include "Game/AI/AI/aiTargetNPCTypeSelector.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7100736460.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

TargetNPCTypeSelector::TargetNPCTypeSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetNPCTypeSelector::~TargetNPCTypeSelector() = default;

bool TargetNPCTypeSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetNPCTypeSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* link = sub_71005D9050(mActor);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    if (link && sub_7100736414(link))
        changeChild("戦士", &pack);
    else
        changeChild("一般", &pack);
}

void TargetNPCTypeSelector::calc_() {
    if (getCurrentChild()->isChangeable()) {
        const bool is_warrior = isCurrentChild("戦士");
        auto* link = sub_71005D9050(mActor);
        if (is_warrior) {
            if (!link || !sub_7100736414(link)) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
                changeChild("一般", &pack);
            }
        } else if (link && sub_7100736414(link)) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("戦士", &pack);
        }
    }
    getCurrentChild()->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
}

void TargetNPCTypeSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetNPCTypeSelector::loadParams_() {}

}  // namespace uking::ai
