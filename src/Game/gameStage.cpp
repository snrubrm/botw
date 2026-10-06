#include "Game/gameStage.h"
#include "Game/gameSaveSystem.h"
#include "Game/gameScene.h"
#include "Game/gameStageInfo.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldEnvMgr.h"

namespace uking {

// (defined in a different file than GameScene::m1: its caller does not inline it in the original)
void GameScene::sub_71007B7D78() {
    sInstance2->sub_71007B4B50();
}

// Thunks to members of the GameScene instances (in this file because the originals do not inline the members).
bool gameSceneHasStageBinder() {
    return GameScene::sInstance2->hasStageBinder();
}

void gameSceneSetNeedStageGenFinalStepInPreCalc() {
    GameScene::sInstance2->setNeedStageGenFinalStepInPreCalc();
}

bool gameSceneIsNotNeedStageGenFinalStepInPreCalc() {
    return GameScene::sInstance2->isNotNeedStageGenFinalStepInPreCalc();
}

// NON_MATCHING: the original loads the instance first and widens the argument with `and x1, x0, #0xffffffff`
// (a u32 or an enum parameter gives the same code as s32 here).
void gameSceneSetFadeType(s32 type) {
    GameScene::sInstance2->setFadeType(type);
}

void sub_71007BEB20() {
    GameScene::sInstance3->sub_71007B4C28();
}

void sub_71007B7E4C() {
    GameScene::sInstance2->sub_71007B4BCC();
}

void sub_71007B7E5C() {
    GameScene::sInstance2->sub_71007B4BE4();
}

bool sub_71007B7E6C() {
    return GameScene::sInstance2->sub_71007B4C00();
}

void GameScene::sub_71007B8DB4() {
    sInstance3->_8c9 = true;
}

bool GameScene::hasLoadingScreenStarted() {
    if (sInstance3)
        return sInstance3->_6e6;
    return false;
}

void GameScene::sub_71007AEF94() {
    resetStage(SaveSystem::instance()->_30, true);
}

void GameScene::sub_71007B1C64() {
    auto* save_system = SaveSystem::instance();
    if (!save_system || ksys::StageInfo::sIsDebugOrDevMap)
        return;
    if (u32(save_system->_3c - 10) < 4)
        return;
    ksys::gdt::setFlag_PlayerSavePos(StageInfo::getPSavePosForStageGen(), false);
    ksys::gdt::setFlag_PlayerSavePosAngleYDegree(StageInfo::getPSavePosAngleForStageGen().y, false);
    ksys::gdt::setFlag_PlayerSavePosMapType(getCurrentMapType().cstr(), false);
    ksys::gdt::setFlag_PlayerSavePosMapName(getCurrentMapName().cstr(), false);
}

void recoverLifeAndStamina() {
    ksys::act::PlayerInfo::instance()->setLifeForPlayerActor(
        ksys::act::PlayerInfo::instance()->getMaxLifeFromPlayerActor());
    ksys::act::PlayerInfo::instance()->setStaminaCurrentMax(
        ksys::act::PlayerInfo::instance()->getMaxStaminaFromPlayerActor());
}

// 0x71025cc6a8 (.bss; the type is unknown: a string object that TitleStageArg::m8 hands out; its initialiser is
// not decompiled).
static sead::SafeString sUnk_71025cc6a8;

// 0x71025cc858 (.bss; the type is unknown): returned by the three string getters of ViewerStageArg.
static sead::SafeString sUnk_71025cc858;

const sead::SafeString& ViewerStageArg::sub_71007D4CAC() const {
    return sUnk_71025cc858;
}

const sead::SafeString& ViewerStageArg::sub_71007D4CB8() const {
    return sUnk_71025cc858;
}

const sead::SafeString& ViewerStageArg::sub_71007D4CC4() const {
    return sUnk_71025cc858;
}

const sead::SafeString& TitleStageArg::m8() {
    return sUnk_71025cc6a8;
}

s32 IndoorStageArg::m4() {
    return 1;
}

s32 MainFieldDungeonStageArg::m4() {
    return 2;
}

StartupSaveCheckStageArg::~StartupSaveCheckStageArg() {}

s32 StartupSaveCheckStageArg::sub_71007D17E0() {
    return 4;
}

void StartupSaveCheckStageArg::sub_71007D17F0(sead::Heap* heap) {
    mHeap = heap;
}

s32 StartupSaveCheckStageArg::sub_71007D17F8() {
    return _18;
}

const sead::SafeString& StartupSaveCheckStageArg::sub_71007D1800() {
    return sead::SafeString::cEmptyString;
}

const sead::SafeString& StartupSaveCheckStageArg::sub_71007D180C() {
    return sead::SafeString::cEmptyString;
}

const sead::SafeString& StartupSaveCheckStageArg::sub_71007D1818() {
    return sead::SafeString::cEmptyString;
}

s32 StartupSaveCheckStageArg::sub_71007D1824() {
    return -1;
}

bool StartupSaveCheckStageArg::sub_71007D182C() {
    return _1c;
}

// 0x71025cb0e9: set while the title stage exists (its init stores true, its destructor false). Next to the
// GameScene statics (0x71025cb0e0 / 0x71025cb0ea).
bool sIsTitleStageActive;

TitleStage::TitleStage() : mHeap(nullptr), _18(nullptr), _20(nullptr), _28(nullptr), _30(nullptr) {}

TitleStage::~TitleStage() {
    sIsTitleStageActive = false;
    mHeap->destroy();
}

StartupSaveCheckStage::StartupSaveCheckStage() : mHeap(nullptr), mState(nullptr) {}

StartupSaveCheckStage::~StartupSaveCheckStage() {
    mHeap->destroy();
}

void IndoorStage::initForStageGen() {
    ksys::world::sub_71010D6094(ksys::world::Manager::instance()->getEnvMgr());
}

IndoorStage::~IndoorStage() {
    mHeap->destroy();
}

bool IndoorStage::m2(sead::BufferedSafeString* out) {
    out->copy(mMapName);
    return true;
}

bool IndoorStage::getMapName(sead::BufferedSafeString* out, int x, int z) {
    if (x != 5 || z != 4)
        return false;
    out->copy(mMapName);
    return true;
}

void IndoorStage::m4(int* x, int* z, const sead::SafeString& name) {
    *x = 5;
    *z = 4;
}

void IndoorStage::getMapType(sead::BufferedSafeString* out) {
    out->copy(GameScene::getCurrentMapType());
}

int IndoorStage::m0() {
    return 1;
}

MainFieldDungeonStage::~MainFieldDungeonStage() {
    mHeap->destroy();
}

bool MainFieldDungeonStage::m2(sead::BufferedSafeString* out) {
    out->copy(mMapName);
    return true;
}

bool MainFieldDungeonStage::getMapName(sead::BufferedSafeString* out, int x, int z) {
    if (x != 5 || z != 4)
        return false;
    out->copy(mMapName);
    return true;
}

void MainFieldDungeonStage::m4(int* x, int* z, const sead::SafeString& name) {
    *x = 5;
    *z = 4;
}

void MainFieldDungeonStage::getMapType(sead::BufferedSafeString* out) {
    out->copy(GameScene::getCurrentMapType());
}

int MainFieldDungeonStage::m0() {
    return 2;
}

s32 ViewerStage::getType() {
    return 5;
}

void ViewerStage::initForStageGen() {
    ksys::world::sub_71010D6094(ksys::world::Manager::instance()->getEnvMgr());
}

}  // namespace uking

// 0x71007b7da4 (CSV name; global namespace: E3Mgr declares it that way)
bool isStageSelectState() {
    return uking::GameScene::sInstance2->sub_71007B0D3C();
}
