#include "Game/AI/AI/aiDrawnWeaponSelector.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

DrawnWeaponSelector::DrawnWeaponSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DrawnWeaponSelector::~DrawnWeaponSelector() = default;

bool DrawnWeaponSelector::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool DrawnWeaponSelector::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool DrawnWeaponSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DrawnWeaponSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100373988(params);
}

void DrawnWeaponSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DrawnWeaponSelector::loadParams_() {}

void DrawnWeaponSelector::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        return;
    if (child->isChangeable())
        sub_7100373988(nullptr);
}

// NON_MATCHING: the operand order of the `and` that clears the shield bit (`and w9, w9, w8` instead of
// `and w9, w8, w9`) and the mask's stack slot (sp+0x1c instead of sp+0x18).
void DrawnWeaponSelector::sub_7100373988(ksys::act::ai::InlineParamPack* params) {
    u32 mask = 0;
    sub_7100373C14(&mask);
    const u32 types = mask;
    if (types & 8) {
        if (!isCurrentChild("弓装備"))
            changeChild("弓装備", params);
        return;
    }
    mask = mask & ~(mask & 0x10u);
    if (types & 1) {
        if (types & 0x10) {
            if (!isCurrentChild("剣盾装備"))
                changeChild("剣盾装備", params);
        } else {
            if (!isCurrentChild("剣装備"))
                changeChild("剣装備", params);
        }
    } else if (types & 2) {
        if (!isCurrentChild("大剣装備"))
            changeChild("大剣装備", params);
    } else if (types & 4) {
        if (!isCurrentChild("槍装備"))
            changeChild("槍装備", params);
    } else {
        if (!isCurrentChild("素手"))
            changeChild("素手", params);
    }
}

void DrawnWeaponSelector::sub_7100373C14(u32* mask) {
    if (auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor)) {
        actor->getWeapons();
        for (s32 i = 0; i < 6; ++i) {
            if (sub_71005DB904(mActor, i)) {
                const s32 type = sub_71005DBB60(mActor, i);
                if (type != -1)
                    *mask |= 1u << type;
            }
        }
    }
}

}  // namespace uking::ai
