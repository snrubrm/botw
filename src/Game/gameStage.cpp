#include "Game/gameStage.h"
#include "Game/gameScene.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldEnvMgr.h"

namespace uking {

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
