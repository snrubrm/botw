#include "Game/AI/AI/aiEnemyRoamSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

bool sub_710072C9FC(ksys::act::Actor* actor, f32 distance);
bool sub_71006DE574(const ksys::act::ActorConstDataAccess& accessor);
bool sub_71006DE3D8(const ksys::act::ActorConstDataAccess& accessor);
bool sub_71006DE4A4(const ksys::act::ActorConstDataAccess& accessor);

namespace uking::ai {

EnemyRoamSelect::EnemyRoamSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyRoamSelect::~EnemyRoamSelect() = default;

bool EnemyRoamSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: stack layout of the last block only (the original puts `height` at sp+8 (shared with the Vector3f of
// the "小物連携" branch) and the actor position in the InlineParamPack slot at sp+0x28; ours has them the other way
// round and `height` above the pack); the instructions are the same
void EnemyRoamSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    _50.reset();
    _74 = -1;
    _78 = false;
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_3000000);
    _70 = 0;
    if (mActor->getMapObject()) {
        if (sub_71003B3720()) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mCentralPos_d, "CentralPos", -1);
            pack.addVec3(*mCentralPos_d, "TargetPos", -1);
            changeChild("未帰還", &pack);
            return;
        }
        if (sub_71005D9F04(mActor)) {
            changeChild("レール移動");
            return;
        }
        if (sub_71003B384C()) {
            ksys::act::ai::InlineParamPack pack;
            pack.addActor(_50, "TargetActor", -1);
            sead::Vector3f position;
            ksys::act::sub_7100EE67B0(&position, &_50);
            pack.addVec3(position, "TargetPos", -1);
            pack.addBool(false, "IsChanged", -1);
            changeChild("小物連携", &pack);
            return;
        }
    }

    f32 height = 0;
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    const u32 on_grass = sub_710072C278(&height, &position);
    const f32 hide_height = *mHideGrassHeight_s;
    if (hide_height >= 0 && (on_grass == 1 || height > hide_height)) {
        changeChild("待ち伏せ");
        return;
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mCentralPos_d, "CentralPos", -1);
    pack.addVec3(*mCentralPos_d, "TargetPos", -1);
    changeChild("単純徘徊", &pack);
}

bool EnemyRoamSelect::sub_71003B3720() {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (sub_71005D9F04(mActor)) {
        if (isRootAiParamINot5())
            return false;
        return !sub_710072C9FC(mActor, 2.0f);
    }
    if (enemy && enemy->_e84.isOnBit(23))
        return false;
    return (mActor->getMtx().getTranslation() - *mCentralPos_d).length() > *mNotReturnDist_s;
}

// NON_MATCHING: the loop guard is `cmp w21, #1 ; b.lt` (the original `cmp w21, #0 ; b.le`) and the original keeps the
// address of `found` in x20 / the result in x21
bool EnemyRoamSelect::sub_71003B384C() {
    _74 = -1;
    auto* object = mActor->getMapObject();
    if (!object)
        return false;
    auto* links = object->getLinkData();
    ksys::act::ActorConstDataAccess found;
    if (!links)
        return false;
    auto objects = links->mObjects;
    const s32 count = objects.size();
    for (s32 i = 0; i < count; ++i) {
        if (!objects[i])
            continue;
        ksys::act::ActorConstDataAccess accessor;
        objects[i]->getActorWithAccessor(accessor);
        if (accessor.isStateCalc() && accessor.hasTag(0xc6bb51c0u)) {
            if (sub_71006DE574(accessor)) {
                _74 = 3;
                found.acquireActor(accessor);
                break;
            }
            if (sub_71006DE3D8(accessor)) {
                if (_74 < 2) {
                    _74 = 2;
                    found.acquireActor(accessor);
                }
            } else if (sub_71006DE4A4(accessor)) {
                if (_74 < 1) {
                    _74 = 1;
                    found.acquireActor(accessor);
                }
            } else if (_74 < 0) {
                _74 = 0;
                found.acquireActor(accessor);
            }
        }
    }
    if (!found.getProc())
        return false;
    const bool changed = !found.hasProc(_50);
    found.linkAcquire(&_50);
    return changed;
}

bool EnemyRoamSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool EnemyRoamSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool EnemyRoamSelect::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

void EnemyRoamSelect::leave_() {
    _78 = false;
}

void EnemyRoamSelect::loadParams_() {
    getStaticParam(&mHideGrassHeight_s, "HideGrassHeight");
    getDynamicParam(&mCentralPos_d, "CentralPos");
    getStaticParam(&mNotReturnDist_s, "NotReturnDist");
}

}  // namespace uking::ai
