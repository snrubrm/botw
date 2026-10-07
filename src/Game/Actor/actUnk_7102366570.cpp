#include "Game/Actor/actUnk_7102366570.h"

// NON_MATCHING: the invalid-owner retry loop differs from the original terminal loop.
void Unk_71006cee58::clear() {
    while (mHead)
        erase(mHead);
}

// NON_MATCHING: pointer strength reduction and callback field stores differ.
void Unk_71006cee58::erase(Unk_7102366570* callback) {
    if (callback->mOwner != this || !mHead)
        return;
    if (mHead == callback) {
        mHead = callback->mNext;
        if (mHead)
            mHead->mPrev = nullptr;
    } else {
        for (auto* current = mHead; current; current = current->mNext) {
            if (current == callback) {
                if (callback->mPrev)
                    callback->mPrev->mNext = callback->mNext;
                if (callback->mNext)
                    callback->mNext->mPrev = callback->mPrev;
            }
        }
    }
    callback->mNext = nullptr;
    callback->mOwner = nullptr;
    callback->mPrev = nullptr;
}

void Unk_71006cee58::append(Unk_7102366570* callback) {
    if (callback->mOwner)
        return;
    if (mHead) {
        auto* current = mHead;
        while (current->mNext)
            current = current->mNext;
        current->mNext = callback;
        callback->mPrev = current;
    } else {
        mHead = callback;
    }
    callback->mOwner = this;
}

void Unk_71006cee58::dispatch() {
    auto* current = mHead;
    if (!current)
        return;
    auto* actor = mActor;
    do {
        current->call(actor);
        current = current->mNext;
    } while (current);
}
