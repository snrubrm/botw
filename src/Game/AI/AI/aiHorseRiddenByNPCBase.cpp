#include "Game/AI/AI/aiHorseRiddenByNPCBase.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

HorseRiddenByNPCBase::HorseRiddenByNPCBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool HorseRiddenByNPCBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRiddenByNPCBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* awareness = mActor->getAwareness();
    if (!awareness) {
        setFailed();
        return;
    }
    _40 = true;
    if (!awareness->sub_7100D7E964()) {
        if (!awareness->enable()) {
            setFailed();
            return;
        }
        _40 = false;
    }
    m34(0, sead::Vector3f::zero, nullptr);
}

// NON_MATCHING: our clang threads the null-sensor path past the `kind > 1` check
void HorseRiddenByNPCBase::calc_() {
    auto* awareness = mActor->getAwareness();
    if (!awareness) {
        setFailed();
        return;
    }

    sead::Vector3f pos = sead::Vector3f::zero;
    u32 kind = 0;
    ksys::act::BaseProcLink* link = nullptr;
    for (s32 i = 0; i < 4; ++i) {
        if (auto* sensor = awareness->_260[i]) {
            const s32 num = sensor->_8.size();
            for (s32 j = 0; j < num; ++j) {
                auto* current = awareness->_260[i];
                if (!current || current->_8.size() <= j)
                    break;
                auto* entry = ksys::act::sub_7100D78E30(&current->_8, j);
                if (!entry)
                    break;
                if (m35(entry, i))
                    continue;
                u32 entry_kind = entry->_a0;
                if (i == 2 && entry->_a4 >= 2.0f)
                    entry_kind = 2;
                if (entry_kind > kind) {
                    entry->_58.getTranslation(pos);
                    link = &entry->_0.mLink;
                    kind = entry_kind;
                }
                break;
            }
        }
        if (kind > 1)
            break;
    }
    m34(kind, pos, link);
}

void HorseRiddenByNPCBase::m34(u32 kind, const sead::Vector3f& pos,
                               ksys::act::BaseProcLink* link) {
    auto* child = getCurrentChild();
    if (!child || child->isFinished() || child->isFailed()) {
        if (kind >= 2) {
            ksys::act::ai::InlineParamPack params;
            params.addVec3(pos, "TargetPos", -1);
            changeChild("逃走", &params);
            return;
        }
        changeChild("徘徊");
        return;
    }

    if (!child->isChangeable())
        return;
    if (isCurrentChild("徘徊") && kind >= 2) {
        ksys::act::ai::InlineParamPack params;
        params.addVec3(pos, "TargetPos", -1);
        changeChild("逃走", &params);
    }
}

bool HorseRiddenByNPCBase::m35(ksys::act::Unk_7100d78e50* entry, s32 idx) {
    if (!*mIsEscapeFromSameActorType_s) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&entry->_0.mLink, &accessor) &&
            accessor.getProfile() == mActor->getProfile()) {
            return true;
        }
    }
    return false;
}

void HorseRiddenByNPCBase::leave_() {
    auto* awareness = mActor->getAwareness();
    if (!awareness || _40)
        return;
    awareness->disable();
}

void HorseRiddenByNPCBase::loadParams_() {
    getStaticParam(&mIsEscapeFromSameActorType_s, "IsEscapeFromSameActorType");
}

}  // namespace uking::ai
