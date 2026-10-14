#include "Game/Actor/AI/aiLOSFurthestHitPointFinder.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_7100742478.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

LOSFurthestHitPointFinder::LOSFurthestHitPointFinder(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LOSFurthestHitPointFinder::~LOSFurthestHitPointFinder() = default;

bool LOSFurthestHitPointFinder::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

inline void LOSFurthestHitPointFinder::changeToActionA() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_38, "TargetPos", -1);
    changeChild("行動A", &pack);
}

inline bool LOSFurthestHitPointFinder::isTargetAwayFromActor() const {
    if (_38.isNan())
        return false;
    const sead::Vector3f& pos = mActor->getMtx().getTranslation();
    return !(_38.x - pos.x <= 0.01f && _38.x - pos.x >= -0.01f && _38.z - pos.z >= -0.01f &&
             _38.z - pos.z <= 0.01f);
}

void LOSFurthestHitPointFinder::enter_(ksys::act::ai::InlineParamPack* params) {
    _68 = 0;
    const sead::Vector3f front = mActor->getMtx().getTranslation() + mActor->getMtx().getBase(2);
    _38 = front;
    sub_7100484D58(&_38);
    if (isTargetAwayFromActor()) {
        changeToActionA();
        _69 = true;
        return;
    }
    _38 = front;
    changeToActionA();
    _69 = false;
    ++_68;
}

// NON_MATCHING: the fallback target is stored as stp + str in the original (ours: three str).
void LOSFurthestHitPointFinder::calc_() {
    if (isFinished() || isFailed())
        return;
    auto* nav = mActor->m45();
    if (!nav || !nav->_18)
        return;

    if (!_69) {
        sub_7100484D58(&_38);
        if (isTargetAwayFromActor()) {
            changeToActionA();
            _69 = true;
        } else if (++_68 >= 5) {
            setFailed();
            return;
        }
    }

    auto* child = getCurrentChild();
    if (child) {
        if (!child->isFinished() && !child->isFailed())
            return;
        if (!child->isFailed()) {
            if (!isCurrentChild("行動A") || !*mUseActionB_s) {
                setFinished();
                return;
            }
            if (isTargetAwayFromActor()) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(_38, "TargetPos", -1);
                changeChild("行動B", &pack);
                return;
            }
            _38 = mActor->getMtx().getTranslation() + mActor->getMtx().getBase(2);
            changeToActionA();
        }
    }
    setFailed();
}

// NON_MATCHING: vector temporary storage and argument load scheduling differ.
void LOSFurthestHitPointFinder::sub_7100484D58(sead::Vector3f* out) {
    if (!out)
        return;
    auto* character = mActor->m45();
    if (!character)
        return;
    auto* actor = mActor;
    const sead::Vector3f position = actor->getMtx().getTranslation();
    if (!sub_7100742278(3.0f, nullptr, character, &position)) {
        const auto result = character->sub_7100F76078(out, position, 10.0f);
        if (!result.sub_7100F7EB40())
            setFailed();
    } else if (*mOnlyCheckBehind_s) {
        const sead::Vector3f first = actor->getMtx().getBase(0);
        const sead::Vector3f last = -first;
        sub_71007428EC(*mCheckDistance_s, 10.0f, out, character, &first, &last,
                       *mMaxNumCheck_s);
    } else {
        const sead::Vector3f axis = actor->getMtx().getBase(2);
        sub_71007428DC(*mCheckDistance_s, 10.0f, out, character, &axis, *mMaxNumCheck_s);
    }
}

void LOSFurthestHitPointFinder::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LOSFurthestHitPointFinder::loadParams_() {
    getStaticParam(&mMaxNumCheck_s, "MaxNumCheck");
    getStaticParam(&mCheckDistance_s, "CheckDistance");
    getStaticParam(&mOnlyCheckBehind_s, "OnlyCheckBehind");
    getStaticParam(&mUseActionB_s, "UseActionB");
}

}  // namespace uking::ai
