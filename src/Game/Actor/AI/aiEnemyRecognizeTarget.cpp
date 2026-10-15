#include "Game/Actor/AI/aiEnemyRecognizeTarget.h"
#include "Game/Actor/aiAwarenessFilters.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Utils/MathUtil.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include <random/seadGlobalRandom.h>
#include <cmath>

namespace uking::ai {

EnemyRecognizeTarget::EnemyRecognizeTarget(const InitArg& arg) : EnemyRecognizeTargetBase(arg) {}

EnemyRecognizeTarget::~EnemyRecognizeTarget() = default;

// NON_MATCHING: register allocation and stack slots for the grass query and awareness filter differ.
bool EnemyRecognizeTarget::m34() {
    if (*mSummonNum_s > 0) {
        auto* actor = mActor;
        if (actor->checkFlag(ksys::act::Actor::ActorFlag::_29)) {
            float height = 0.0f;
            const sead::Vector3f position = mActor->getMtx().getTranslation();
            if (sub_710072C1B8(&height, &position) != 1 && height < *mSummonGrassHeight_s)
                return false;
            if (auto* awareness = actor->getAwareness()) {
                Unk_7102451448 filter;
                return ksys::act::sub_7100D7EEE8(&awareness->_8, &filter) == nullptr;
            }
        }
    }
    return false;
}

// NON_MATCHING: normalization scheduling, vector copies and retry-loop branch layout differ.
bool EnemyRecognizeTarget::m35() {
    const s32 count = sead::Mathi::max(
        *mSummonNum_s + sead::GlobalRandom::instance()->getS32Range(-1, 1), 1);
    s32 skipped_index;
    if (count == 1)
        skipped_index = sead::GlobalRandom::instance()->getS32Range(0, 2);
    else if (count == 2)
        skipped_index = 1;
    else
        skipped_index = sead::GlobalRandom::instance()->getS32Range(1, count);

    auto* actor = mActor;
    const auto& target = sub_71005D9330(actor);
    auto direction = actor->getMtx().getTranslation() - target;
    const f32 distance = direction.normalize();
    f32 radius = sead::Mathf::max(2.0f, distance);
    f32 step = 3.0f / radius;
    if (f32(count) * step >= sead::numbers::pi_v<f32>) {
        radius += 1.0f;
        step = 3.0f / radius;
    }
    f32 angle = std::atan2(direction.x, direction.z) - f32(skipped_index) * step;
    s32 created = 0;
    s32 failed = 0;
    for (s32 i = 0; i < count; ++i) {
        if (i != skipped_index) {
            sead::Vector3f position = sead::Vector3f::zero;
            ksys::util::sub_71011EEE98(&position, angle,
                radius * sead::GlobalRandom::instance()->getF32Range(0.9f, 1.1f));
            auto front = -position;
            front.normalize();
            position += target;
            position.y += 3.0f;
            somePositionCalc(&position, position, -sead::Vector3f::ey, 10.0f);
            f32 height = 0.0f;
            const bool valid = sub_710072C278(&height, &position) == 2 &&
                               !(height < *mSummonGrassHeight_s);
            if (valid) {
                sub_71003AF848(position, front);
                ++created;
            } else {
                ++failed;
            }
        }
        angle = step + angle;
    }
    while (failed > 0) {
        sead::Vector3f position = sead::Vector3f::zero;
        ksys::util::sub_71011EEE98(&position, angle,
            radius * sead::GlobalRandom::instance()->getF32Range(0.9f, 1.1f));
        auto front = -position;
        front.normalize();
        position += target;
        position.y += 3.0f;
        somePositionCalc(&position, position, -sead::Vector3f::ey, 10.0f);
        f32 height = 0.0f;
        if (sub_710072C278(&height, &position) == 2 && !(height < *mSummonGrassHeight_s)) {
            sub_71003AF848(position, front);
            ++created;
        }
        angle = step + angle;
        --failed;
    }
    return created > 0;
}

// NON_MATCHING: the singular rotation branch uses a different paired-load register order.
void EnemyRecognizeTarget::sub_71003AF848(const sead::Vector3f& position,
                                         const sead::Vector3f& front) {
    sead::Matrix34f matrix;
    ksys::util::sub_71011F00EC(&matrix, front, sead::Vector3f::ey, position, false);
    sead::Vector3f rotation;
    matrix.getRotation(rotation);
    ksys::act::InstParamPack pack;
    pack.getBuffer().addPosition(position);
    pack.getBuffer().addRotation(rotation);
    pack.getBuffer().add(6, "@I");
    pack.getBuffer().add(mEquipItem1_m, "EquipItem1");
    pack.getBuffer().add(mEquipItem2_m, "EquipItem2");
    auto* creator = ksys::act::ActorCreator::instance();
    const char* name = mActor->getName().cstr();
    creator->requestCreateActor(name, ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
                                nullptr, &pack, nullptr, 1);
}

void EnemyRecognizeTarget::loadParams_() {
    EnemyRecognizeTargetBase::loadParams_();
    getStaticParam(&mSummonNum_s, "SummonNum");
    getStaticParam(&mSummonGrassHeight_s, "SummonGrassHeight");
    getStaticParam(&mSummonCheckDist_s, "SummonCheckDist");
    getMapUnitParam(&mEquipItem1_m, "EquipItem1");
    getMapUnitParam(&mEquipItem2_m, "EquipItem2");
}

}  // namespace uking::ai
