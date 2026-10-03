#include "Game/AI/AI/aiKeeseDieSelect.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::ai {

KeeseDieSelect::KeeseDieSelect(const InitArg& arg) : DieSelectChemShockPlus(arg) {}

KeeseDieSelect::~KeeseDieSelect() = default;

bool KeeseDieSelect::init_(sead::Heap* heap) {
    return DieSelectChemShockPlus::init_(heap);
}

void KeeseDieSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    DieSelectChemShockPlus::enter_(params);
}

void KeeseDieSelect::calc_() {
    DieSelectChemShockPlus::calc_();
}

void KeeseDieSelect::leave_() {
    DieSelectChemShockPlus::leave_();
}

void KeeseDieSelect::loadParams_() {
    DieSelectChemShockPlus::loadParams_();
}

void KeeseDieSelect::m34(s32 a2, s32 a3, bool a4, bool a5) {
    if (a5) {
        *mActor->getLife() = 0;
        changeChild("被暗殺");
        return;
    }
    if (sub_7100361104(a2, a3)) {
        *mActor->getLife() = 0;
        changeChild("濡死");
        return;
    }

    bool skip_ground = false;
    switch (a3) {
    case -1:
    case 0:
    case 1:
    case 2:
    case 5:
        skip_ground = a2 >= 9 && a2 < 12;
        break;
    case 3:
    case 4:
    case 18:
        skip_ground = true;
        break;
    case 34:
        changeChild("消滅");
        return;
    }

    if (!skip_ground && isBgGroundHit(mActor, false)) {
        auto* entry = sub_71007A4948(mActor, 0);
        const sead::Vector3f gravity = getGravity(mActor);
        if (gravity.dot(entry->_c) > 0) {
            changeChild("ぶら下がり死亡");
            return;
        }
    }

    DieSelectChemShockPlus::m34(a2, a3, a4, false);
}

void KeeseDieSelect::m35() {
    sead::Vector3f pos = mActor->getMtx().getTranslation();
    pos.y += 0.15f;
    sub_7100734270(mActor, &pos, pos);
}

}  // namespace uking::ai
