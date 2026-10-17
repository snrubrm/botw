#include "Game/Actor/Action/actionHorseMoveToSafePos.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::action {

class HorseSafePosQuery : public ksys::phys::NavMeshFaceQuery {
    SEAD_RTTI_OVERRIDE(HorseSafePosQuery, ksys::phys::NavMeshFaceQuery)
public:
    explicit HorseSafePosQuery(ksys::phys::NavMeshCharacter* character) { mCharacter = character; }
    ~HorseSafePosQuery() override;
    bool m0(const ksys::phys::Unk_7100f7e9f0& face) override;
    void* m1() override { return nullptr; }

    ksys::phys::Unk_7100f7e9f0 mFace;
    f32 mAreaThreshold = 0;
};
KSYS_CHECK_SIZE_NX150(HorseSafePosQuery, 0x58);

HorseSafePosQuery::~HorseSafePosQuery() = default;

// NON_MATCHING: The navigation filter is loaded after the material query.
bool HorseSafePosQuery::m0(const ksys::phys::Unk_7100f7e9f0& face) {
    const s32 material = face.sub_7100F7EEE4();
    if (!mCharacter->isMaterialUsableMaybe(material))
        return false;
    mFace = face;
    return true;
}

HorseMoveToSafePos::HorseMoveToSafePos(const InitArg& arg) : AnimalMoveGuidedBase(arg) {}

HorseMoveToSafePos::~HorseMoveToSafePos() = default;

bool HorseMoveToSafePos::init_(sead::Heap* heap) {
    return AnimalMoveGuidedBase::init_(heap);
}

// NON_MATCHING: Query construction uses a different store order.
void HorseMoveToSafePos::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalMoveGuidedBase::enter_(params);
    auto* character = mActor->m45();
    if (character && (character->_2a4.load() & 0xffff) != 0x17) {
        if (*mSetEndIfCurrentFaceIsSafe_s) {
            const u32 material = character->_2a4.load() & 0xffff;
            if (material != 0x17 && character->isMaterialUsableMaybe(material)) {
                setFinished();
                return;
            }
        }
        if (!character->_2e0) {
            void* memory = ksys::phys::HavokAI::instance()->_40->mHeap->tryAlloc(
                sizeof(HorseSafePosQuery), 8);
            if (memory) {
                auto* query = new (memory) HorseSafePosQuery(character);
                character->_2e0 = query;
                query->mAreaThreshold = *mAreaThreshold_s;
                query->mRadius = *mSearchRadius_s;
                character->sub_7100F75AF0();
                _a8 = true;
                return;
            }
            character->_2e0 = nullptr;
        }
    }
    setFailed();
}

// NON_MATCHING: Query construction and submission use different register allocation.
bool HorseMoveToSafePos::sub_71001A25D4(ksys::phys::NavMeshCharacter* character) {
    auto* query = sead::DynamicCast<HorseSafePosQuery>(character->_2e0);
    if (query->_8 == 2) {
        if (!query->mFace.sub_7100F7EB40()) {
            character->sub_7100F75AB8();
            _a8 = false;
            return false;
        }
        sead::Vector3f pos;
        query->mFace.sub_7100F7EB60(&pos);
        if (*mResolvePenetrationRadiusScale_s <= 0.0f ||
            *mResolvePenetrationSearchRadius_s <= 0.0f) {
            character->sub_7100F75F8C(pos);
        } else {
            void* memory = ksys::phys::HavokAI::instance()->_40->mHeap->tryAlloc(
                sizeof(ksys::phys::Unk_710239b220), 8);
            if (!memory) {
                _a0 = nullptr;
                return false;
            }
            _a0 = new (memory) ksys::phys::Unk_710239b220;
            _a0->_18 = character->_1d8;
            _a0->_c = pos;
            _a0->_1c = character->_2a8 * character->_2ac * *mResolvePenetrationRadiusScale_s;
            _a0->_20 = *mResolvePenetrationSearchRadius_s;
            ksys::phys::HavokAI::instance()->submitQuery(_a0);
        }
        character->sub_7100F75AB8();
        _a8 = false;
    }
    return true;
}

void HorseMoveToSafePos::leave_() {
    AnimalMoveGuidedBase::leave_();
    if (_a8) {
        if (auto* nav = mActor->m45())
            nav->sub_7100F75AB8();
        _a8 = false;
    }
    if (_a0) {
        ksys::phys::HavokAI::instance()->destroyQuery(_a0);
        _a0 = nullptr;
    }
}

void HorseMoveToSafePos::loadParams_() {
    AnimalMoveGuidedBase::loadParams_();
    getStaticParam(&mSearchRadius_s, "SearchRadius");
    getStaticParam(&mAreaThreshold_s, "AreaThreshold");
    getStaticParam(&mResolvePenetrationRadiusScale_s, "ResolvePenetrationRadiusScale");
    getStaticParam(&mResolvePenetrationSearchRadius_s, "ResolvePenetrationSearchRadius");
    getStaticParam(&mSetEndIfCurrentFaceIsSafe_s, "SetEndIfCurrentFaceIsSafe");
}

void HorseMoveToSafePos::calc_() {
    auto* character = mActor->m45();
    if (isFinished() || isFailed() || !character || (character->_220 & 0x41000)) {
        AnimalMoveGuidedBase::calc_();
        return;
    }
    if (_a8) {
        if (!_a0 && !sub_71001A25D4(character))
            setFailed();
    } else {
        if (!_a0) {
            AnimalMoveGuidedBase::calc_();
            return;
        }
        if (_a0->_8 == 2) {
            character->sub_7100F75F8C(_a0->_c);
            ksys::phys::HavokAI::instance()->destroyQuery(_a0);
            _a0 = nullptr;
        }
    }
    mActor->getASList()->x_6(1, 0, 0.0f);
    mActor->getASList()->x_6(2, 0, 0.0f);
    mActor->getASList()->x_6(9, 0, 0.0f);
    auto* rideable = mActor->m132();
    auto* as_list = mActor->getASList();
    act::sub_7100E7F698(rideable, as_list, mActor->getCharacterController());
}

}  // namespace uking::action

namespace ksys::phys {

void Unk_710239b220::process(HavokAI* ai) {
    _24 = ai->sub_7100F891C8(&_c, _18, _1c, _20);
}

}  // namespace ksys::phys
