#include "Game/Actor/AI/aiGiantEscapeFromDamageWater.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

GiantEscapeFromDamageWater::GiantEscapeFromDamageWater(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GiantEscapeFromDamageWater::~GiantEscapeFromDamageWater() = default;

// NON_MATCHING: the copy of `dir` in the loop is scheduled differently and the original clamps the count with an
// unsigned 64-bit compare.
void GiantEscapeFromDamageWater::sub_71003F6CF0() {
    auto* holder = sub_71005E2BCC(mActor);
    auto* nav = mActor->m45();
    if (!holder || !nav)
        return;

    sead::SafeArray<sead::Vector3f, 8> points;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f dir;
    sub_71000891C8(&dir, mActor);

    constexpr f32 radius = 10.0f;
    s32 count = 0;
    if (sub_71005D8F28(mActor)) {
        sead::Vector3f point;
        if (nav->sub_7100F76078(&point, sub_71005D9330(mActor), radius).sub_7100F7EB40())
            points[count++] = point;
    }

    {
        sead::Vector3f point;
        if (nav->sub_7100F76078(&point, pos, radius).sub_7100F7EB40())
            points[count++] = point;
    }

    const s32 step = sead::Mathf::pi2() / (8 - count);
    for (s32 i = count; i < 8; ++i) {
        const s32 index = (i & 1) ? -(i / 2) - 1 : i / 2 + 1;
        sead::Vector3f rotated = dir;
        ksys::util::sub_71011EF010(&rotated, index * step);
        sead::Vector3f point;
        const sead::Vector3f target = pos + rotated * radius * 1.5f;
        if (nav->sub_7100F76078(&point, target, radius).sub_7100F7EB40())
            points[count++] = point;
    }

    if (auto* holder_nav = holder->_0) {
        holder_nav->sub_71003F76A0(points.begin(),
                                   {points.getBufferPtr(), sead::Mathi::min(count, 8)});
        holder->_8 = 0;
    }
}

void GiantEscapeFromDamageWater::sub_71003F73D8() {
    auto* holder = sub_71005E2BCC(mActor);
    auto* nav = mActor->m45();
    if (holder && nav && sub_71005D8F28(mActor)) {
        sead::Vector3f position;
        if (nav->sub_7100F76078(&position, sub_71005D9330(mActor), 10.0f).sub_7100F7EB40()) {
            if (auto* holder_nav = holder->_0) {
                holder_nav->sub_7100F75F8C(position);
                holder->_8 = 0;
            }
        }
    }
}

bool GiantEscapeFromDamageWater::init_(sead::Heap* heap) {
    sub_71005E2C58(mActor);
    return true;
}

void GiantEscapeFromDamageWater::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71003F6CF0();
    _38 = ksys::Timer(60, 60);
    changeChild("初回探索");
}

void GiantEscapeFromDamageWater::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GiantEscapeFromDamageWater::loadParams_() {}

bool GiantEscapeFromDamageWater::isChangeable() const {
    if (isCurrentChild("移動")) {
        if (auto* nav = mActor->m45())
            return ksys::act::ai::Ai::isChangeable() && (nav->_2a4 & 0xffff) != 0x17;
    }
    return ksys::act::ai::Ai::isChangeable();
}

}  // namespace uking::ai
