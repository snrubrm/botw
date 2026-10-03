#include "Game/AI/AI/aiPriestBossShadowCloneThrow.h"
#include <cmath>
#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

PriestBossShadowCloneThrow::PriestBossShadowCloneThrow(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (SafeString members); written
// like upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
PriestBossShadowCloneThrow::~PriestBossShadowCloneThrow() {
    ;
}

bool PriestBossShadowCloneThrow::init_(sead::Heap* heap) {
    for (auto& sender : _b8)
        sender._8 = &mActor->getMessageTransceiver();
    return true;
}

void PriestBossShadowCloneThrow::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("準備完了待ち", params);
    _80 = ksys::Timer(*mPrepareTimer_s, *mPrepareTimer_s);
    _8c = 0;
    _90 = 2;
    _3ea = false;
    _3e8 = true;
    _3e9 = false;
}

// NON_MATCHING: the original copies the identity matrix from a TU-local constant (three q loads from
// rodata) before patching the translation; ours copies the GOT'd sead::Matrix34f::ident with memcpy
void PriestBossShadowCloneThrow::m34() {
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (!unit)
        return;

    for (auto& value : _94)
        value = -1;

    ksys::act::ActorConstDataAccess accessor;
    s32 count = 0;
    if (unit->sub_71007194D4(25, &accessor)) {
        sead::Vector3f pos;
        m38(&pos, false);
        if (accessor.isStateSleep()) {
            sead::Matrix34f mtx = sead::Matrix34f::ident;
            mtx.setTranslation(pos);
            accessor.setProperties(mtx, nullptr, nullptr, nullptr, false, 0, -1);
            count = 1;
            _94[0] = 0;
        }
    }
    if (unit->sub_71007194D4(26, &accessor)) {
        sead::Vector3f pos;
        m38(&pos, true);
        if (accessor.isStateSleep()) {
            sead::Matrix34f mtx = sead::Matrix34f::ident;
            mtx.setTranslation(pos);
            accessor.setProperties(mtx, nullptr, nullptr, nullptr, false, 0, -1);
            _94[count] = 1;
        }
    }
}

bool PriestBossShadowCloneThrow::m36() {
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    if (!unit)
        return false;

    ksys::act::ActorConstDataAccess accessor;
    for (s32 i = 25; i < 33; ++i) {
        if (unit->sub_71007194D4(i, &accessor) && accessor.isStateCalc())
            return false;
    }
    return true;
}

// NON_MATCHING: the original copies the identity from a TU-local constant (three q loads from rodata; ours
// calls memcpy on the GOT'd sead::Matrix34f::ident) and selects the bone rows with the inverted condition
void PriestBossShadowCloneThrow::m38(sead::Vector3f* out, bool a2) {
    sead::Matrix34f left = sead::Matrix34f::ident;
    sead::Matrix34f right = sead::Matrix34f::ident;
    mActor->sub_71011D57F8(&left, mShadowCloneLefeBoneName_s);
    mActor->sub_71011D57F8(&right, mShadowCloneRightBoneName_s);

    const f32 offset_y = *mShadowCloneOffsetY_s;
    f32 angle_offset = *mShadowCloneAngleOffset_s;
    const sead::Matrix34f& bone = a2 ? left : right;
    const f32 base_x = mActor->getMtx().m[0][0];
    const f32 base_z = mActor->getMtx().m[2][0];
    out->x = bone(0, 3);
    out->y = bone(1, 3);
    if (a2)
        angle_offset = -angle_offset;
    out->z = bone(2, 3);
    const f32 angle = sead::Mathf::deg2rad(angle_offset + 90.0f);
    const f32 c = std::cos(angle) * *mShadowCloneRadius_s;
    const f32 s = std::sin(angle);
    const f32 radius = *mShadowCloneRadius_s;
    out->x += base_x * c;
    out->y += offset_y + (s * radius - radius);
    out->z += base_z * c;
}

bool PriestBossShadowCloneThrow::m37() {
    return mActor->getASList()->x(0x47, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC,
                                  true);
}

void PriestBossShadowCloneThrow::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossShadowCloneThrow::loadParams_() {
    getStaticParam(&mShadowCloneOffsetY_s, "ShadowCloneOffsetY");
    getStaticParam(&mShadowCloneRadius_s, "ShadowCloneRadius");
    getStaticParam(&mShadowCloneAngleOffset_s, "ShadowCloneAngleOffset");
    getStaticParam(&mPrepareTimer_s, "PrepareTimer");
    getStaticParam(&mShadowCloneLefeBoneName_s, "ShadowCloneLefeBoneName");
    getStaticParam(&mShadowCloneRightBoneName_s, "ShadowCloneRightBoneName");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
