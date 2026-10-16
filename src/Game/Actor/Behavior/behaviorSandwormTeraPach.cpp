#include "Game/Actor/Behavior/behaviorSandwormTeraPach.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "Game/Actor/actSandworm.h"
#include "KingSystem/System/VFR.h"

namespace uking::behavior {

SandwormTeraPach::SandwormTeraPach(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

SandwormTeraPach::~SandwormTeraPach() = default;

bool SandwormTeraPach::init_(sead::Heap* heap) {
    return true;
}

void SandwormTeraPach::leave() {}

// NON_MATCHING: the original reads Sandworm::_1640 / _163c through stack slots (they are probably SEAD_ENUMs, read
// with operator int() const volatile); the rest matches
void SandwormTeraPach::calc() {
    auto* sandworm = sead::DynamicCast<act::Sandworm>(mActor);
    if (!sandworm)
        return;

    if (sandworm->_1640 == 1)
        ksys::VFR::lerp(&_70, 1.0f, 0.1f);
    else if (sandworm->_1640 == 2 || sandworm->_163c == 4)
        ksys::VFR::lerp(&_70, 0.0f, 0.1f);
    else
        ksys::VFR::lerp(&_70, 1.0f, 0.1f);

    const auto& actor_mtx = sandworm->getMtx();
    sead::Vector3f pos{actor_mtx(0, 3), actor_mtx(1, 3), actor_mtx(2, 3)};
    sead::Vector3f node_pos = pos;
    if (auto* model = sandworm->getModel()) {
        if (_38.isValid()) {
            sead::Matrix34f mtx;
            model->getUnits()
                .unsafeAt(_38.getKey().model_unit_index)
                ->mModelUnit->getBoneWorldMatrix(&mtx, _38.getKey().bone_index);
            mtx.getTranslation(node_pos);
        }
    }
    pos += (node_pos - pos) * _70;
    sandworm->sub_71002CD990(pos);
}

void SandwormTeraPach::enter() {
    _70 = 1.0f;
    const auto& actor_mtx = mActor->getMtx();
    sead::Vector3f pos{actor_mtx(0, 3), actor_mtx(1, 3), actor_mtx(2, 3)};
    if (auto* model = mActor->getModel()) {
        _38.search(model, mNode1_s);
        if (_38.isValid()) {
            sead::Matrix34f mtx;
            model->getUnits()
                .unsafeAt(_38.getKey().model_unit_index)
                ->mModelUnit->getBoneWorldMatrix(&mtx, _38.getKey().bone_index);
            mtx.getTranslation(pos);
        }
    } else {
        _38.getKey().reset();
    }
    if (auto* sandworm = sead::DynamicCast<act::Sandworm>(mActor))
        sandworm->sub_71002CD930(pos);
}

void SandwormTeraPach::loadParams() {
    getStaticParam(&mNode1_s, "Node1");
}

}  // namespace uking::behavior
