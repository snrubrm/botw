#include "Game/AI/AI/aiPriestBossFormation.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

PriestBossFormation::PriestBossFormation(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossFormation::~PriestBossFormation() = default;

bool PriestBossFormation::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossFormation::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestBossFormation::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossFormation::loadParams_() {
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

// NON_MATCHING: regalloc (the original materialises &_48 before the payload lock)
void PriestBossFormation::m35(Unk_7102450fa8* unit) {
    if (!unit)
        return;

    // The result is unused, but the call is in the binary.
    unit->sub_7100719534(mActor);

    s32 type = -1;
    switch (_44) {
    case 1:
        type = 1;
        break;
    case 2:
        type = 2;
        break;
    case 4:
        type = 3;
        break;
    case 6:
        type = 4;
        break;
    default:
        break;
    }
    if (type < 0)
        return;

    _48._18.y(type, mActor);

    ksys::act::ActorConstDataAccess accessor;
    if (unit->sub_71007194CC(&accessor))
        _48.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
}

bool PriestBossFormation::m37() {
    return _44 != 1;
}

void PriestBossFormation::m38(sead::Vector3f* out) {
    out->set(getPlayerPosition());
    const f32 x = sead::GlobalRandom::instance()->getF32Range(-1.0f, 1.0f);
    const f32 z = sead::GlobalRandom::instance()->getF32Range(-1.0f, 1.0f);
    *out += {x, 0.0f, z};
}

void PriestBossFormation::m39() {
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f pos;
    m38(&pos);
    params.addVec3(pos, "TargetPos", -1);
    changeChild("攻撃", &params);
}

void PriestBossFormation::m40() {
    changeChild("陣形作成_消える");
}

void PriestBossFormation::m42() {}

void PriestBossFormation::m43() {
    changeChild("待機");
}

void PriestBossFormation::m44() {
    changeChild("分身消す");
}

void PriestBossFormation::sub_71005183C0(bool on) {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;
    if (on)
        controller->sub_7100F60604();
    else
        controller->enableContactLayer(ksys::phys::ContactLayer(4));
}

s32 PriestBossFormation::sub_7100518B50() {
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (!unit)
        return -1;
    return unit->sub_710071A048(unit->sub_7100719534(mActor));
}

}  // namespace uking::ai
