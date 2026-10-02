#include "Game/AI/AI/aiTargetExistSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actUnk_71002dccbc.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

TargetExistSelect::TargetExistSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetExistSelect::~TargetExistSelect() = default;

bool TargetExistSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetExistSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* link = sub_71005D9050(mActor);
    if (!link || !link->hasProc()) {
        auto* unk = sub_71005D9D68(mActor);
        if (!unk || unk->sub_71002DCCBC(0x10)) {
            changeChild("いない", params);
            return;
        }
    }
    changeChild("いる", params);
}

void TargetExistSelect::calc_() {}

void TargetExistSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetExistSelect::loadParams_() {}

}  // namespace uking::ai
