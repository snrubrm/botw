#include "Game/AI/AI/aiCookPotRoot.h"
#include "Game/gameSceneSubsys14.h"
#include "Game/DLC/aocHardModeManager.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/Attention/actAttention.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"

namespace uking::ai {

CookPotRoot::CookPotRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CookPotRoot::~CookPotRoot() {
    mCookIngredients.freeBuffer();
}

// NON_MATCHING: one instruction (the original branches on the masked value `and w8, w0, #1` that it stores
// to _241; we branch on w0 directly); everything else matches
bool CookPotRoot::init_(sead::Heap* heap) {
    auto* ingredients =
        new (heap, 8, std::nothrow) sead::FixedSafeString<64>[CookingMgr::NumIngredientsMax];
    mCookIngredients.setBuffer(CookingMgr::NumIngredientsMax, ingredients);
    if (!mCookIngredients.isBufferReady()) {
        return false;
    }
    if (*mInitBurnState_m)
        mActor->getRootAi()->setChemicalFlags3cMaybe(0x100000, true);

    auto* actor = mActor;
    _241 = actor->hasPlacementLinkForBasicSig();
    if (_241) {
        _240 = actor->checkBasicSig();
        if (_240) {
            if (auto* chemical = mActor->getChemicalStuff()) {
                if (chemical->_c0 != 2)
                    chemical->sub_7100D90858(false, 2, false, true, false);
            }
        }
    } else {
        _240 = false;
    }

    Unk_71023b0898_Payload::Data data;
    data._8.acquire(mActor, false);
    data._0 = 4;
    _248._18.x(data);
    return true;
}

void CookPotRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

// NON_MATCHING: the original computes `&_248` for the sender call after the payload lock is released
// (ours materialises it before the lock; scheduling only)
void CookPotRoot::leave_() {
    if (!isActorDeletedOrDeleting() && !isActorGoingBackToRootAi() && _242) {
        _242 = false;
        {
            sead::ScopedLock<sead::JobQueueLock> lock(&_248._18.mLock);
            _248._18._0 = false;
        }
        _248.sub_710070DBB0(*GameSceneSubsys14::instance()->_180, true);
    }
    if (!isActorGoingBackToRootAi()) {
        if (auto* holder = static_cast<void**>(mCurrentCookResultHolder_a)) {
            if (*holder == &_288)
                *holder = nullptr;
        }
    }
}

void CookPotRoot::loadParams_() {
    getMapUnitParam(&mInitBurnState_m, "InitBurnState");
    getAITreeVariable(&mCurrentCookResultHolder_a, "CurrentCookResultHolder");
}

// NON_MATCHING
bool CookPotRoot::handleMessage_(const ksys::Message& message) {
    if (message.getType() == (u32)ksys::act::AttActionCode::Cook) {
        // 着火: "ignition" or "on fire"
        // This is checking if the pot is lit.
        if (isCurrentChild("着火")) {
            // TODO: sub_7100EDC4B8
            // TODO: GameSceneSubsys12 class
            // GameSceneSubsys12 handles carried items.
            // This needs to check if the player is targeting the pot.
            if (true /* TODO */) {
                if (!_48 /* TODO */) {
                    _48 = true;

                    const int num_ingredients = 5;  // TODO
                    auto* cooking_mgr = CookingMgr::instance();

                    cooking_mgr->resetArgCookData(mCookArg, mCookIngredients, num_ingredients,
                                                  _288.mCookItem);

                    CookingMgr::BoostArg boost_arg{.always_boost = false,
                                                   .enable_random_boost = true};

                    if (ksys::world::Manager::instance()->getEnvMgr()->isInBloodMoonTimeRange()) {
                        boost_arg.always_boost = true;
                    }

                    if (cooking_mgr->cook(mCookArg, _288.mCookItem, boost_arg)) {
                        if (const auto* hard_mode_manager = aoc::HardModeManager::instance()) {
                            if (hard_mode_manager->checkFlag(
                                    aoc::HardModeManager::Flag::EnableHardMode)) {
                                if (hard_mode_manager->isHardModeChangeOn(
                                        aoc::HardModeManager::HardModeChange::NerfHpRestore)) {
                                    hard_mode_manager->nerfHpRestore(&_288.mCookItem.life_recover);
                                }
                            }
                        }
                        if (true /* TODO: callCookingDemo */) {
                            ui::PauseMenuDataMgr::instance()->removeGrabbedItems();
                            cooking_mgr->setCookItem(_288.mCookItem);
                            mHasFinishedCookItem = true;
                            return true;
                        }
                        _48 = false;
                        mHasFinishedCookItem = false;
                        // TODO
                    } else {
                        _48 = false;
                        mHasFinishedCookItem = false;
                        // TODO
                    }
                }
            }
        }
    }

    if (message.getType() != (u32)ksys::act::AttActionCode::KillTime) {
        return false;
    }

    // TODO: callDemo007_1
    return isCurrentChild("着火");
}

}  // namespace uking::ai
