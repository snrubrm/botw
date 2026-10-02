#include "Game/AI/AI/aiSandwormNormal.h"
#include "Game/AI/aiAwarenessFilters.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/Actor/actUnk_71002dccbc.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

SandwormNormal::SandwormNormal(const InitArg& arg) : SandwormNormalBase(arg) {}

SandwormNormal::~SandwormNormal() = default;

bool SandwormNormal::init_(sead::Heap* heap) {
    return SandwormNormalBase::init_(heap);
}

void SandwormNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    SandwormNormalBase::enter_(params);
}

void SandwormNormal::calc_() {
    SandwormNormalBase::calc_();
}

void SandwormNormal::leave_() {
    SandwormNormalBase::leave_();
}

void SandwormNormal::loadParams_() {
    SandwormNormalBase::loadParams_();
}

bool SandwormNormal::m72(Unk2* out, Unk1* info) {
    if (EnemyNormal::m72(out, info))
        return true;

    if (sub_71005D8F28(mActor)) {
        if (auto* link = sub_71005D9050(mActor)) {
            ksys::act::ActorConstDataAccess accessor;
            if (ksys::act::acquireActor(link, &accessor) && accessor.isPlayerProfile()) {
                out->sub_710039E308(link);
                out->_44 |= 1;
                return true;
            }
        }
    }
    return false;
}

// NON_MATCHING: regalloc (the original keeps the entry pointer in x21 instead of &filter)
bool SandwormNormal::m43() {
    if (auto* unk = sub_71005D9D68(mActor))
        unk->sub_71002DCBDC(4);

    if (!_50.hasProc())
        return false;

    const bool is_player = ksys::act::isPlayerProfile(&_50);
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return false;

    Unk_71024514e8 filter(mActor, nullptr);
    if (is_player) {
        auto* sensor = awareness->_260[1];
        auto* entry = sensor ? ksys::act::sub_7100D7EEE8(&sensor->_8, &filter) : nullptr;
        if (!entry)
            return false;
        entry->_58.getTranslation(_60);
        _50 = entry->_0.mLink;
        if (!ksys::act::isPlayerProfile(&entry->_0.mLink))
            getCurrentChild()->setDynamicParamImpl(_50, "TargetActor",
                                                   &ksys::act::ai::ParamPack::setActor);
        return true;
    }

    while (true) {
        auto* sensor = awareness->_260[1];
        auto* entry = sensor ? ksys::act::sub_7100D7EEE8(&sensor->_8, &filter) : nullptr;
        if (!entry)
            return false;
        if (_50 == entry->_0.mLink) {
            entry->_58.getTranslation(_60);
            _50 = entry->_0.mLink;
            return true;
        }
    }
}

bool SandwormNormal::m44(const sead::Vector3f& pos) {
    if (sub_710072E368(mActor)) {
        if (auto* nav = mActor->m45()) {
            sead::Vector3f nav_pos;
            if (nav->sub_7100F76078(&nav_pos, pos, 0.65f).sub_7100F7EB40())
                return true;
        }
    }
    return false;
}

bool SandwormNormal::handleMessage_(const ksys::Message& message) {
    if (message.getType() == ksys::MessageType(0x8000006))
        return true;
    return SandwormNormalBase::handleMessage_(message);
}

}  // namespace uking::ai
