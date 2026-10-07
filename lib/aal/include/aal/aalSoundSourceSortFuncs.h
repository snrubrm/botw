#pragma once

#include <basis/seadTypes.h>

namespace aal {

class SoundSource;

/// The comparison functions that the limiters sort sound sources with. All return a positive number if `lhs` has to
/// come after `rhs`, a negative number if it has to come before and 0 if they are equivalent (0 if one of the sound
/// sources is null). "Earlier" / "Later" refer to the time the sounds were started.
namespace SoundSourceSortFuncs {

/// The sounds with the higher priority come first. The priority is compared as an integer (priority * 255).
s32 comparePriority(const SoundSource* lhs, const SoundSource* rhs);
/// Same, with the priority of the sounds that are stopping or virtualized set to 0.
s32 comparePriorityIgnoreStopOrVirtual(const SoundSource* lhs, const SoundSource* rhs);
/// The sounds that were started earlier come first; the same time is compared by priority.
s32 compareEarlierPriority(const SoundSource* lhs, const SoundSource* rhs);
/// The sounds that were started later come first; the same time is compared by priority.
s32 compareLaterPriority(const SoundSource* lhs, const SoundSource* rhs);
/// Compared by priority first, then the sounds that were started earlier come first.
s32 comparePriorityEarlier(const SoundSource* lhs, const SoundSource* rhs);
/// Compared by priority first, then the sounds that were started later come first.
s32 comparePriorityLater(const SoundSource* lhs, const SoundSource* rhs);
/// compareEarlierPriority, with the priority of the sounds that are stopping or virtualized set to 0.
s32 compareEarlierPriorityIgnoreStopOrVirtual(const SoundSource* lhs, const SoundSource* rhs);

/// compareLaterPriority, with the priority of the sounds that are stopping or virtualized set to 0.
s32 compareLaterPriorityIgnoreStopOrVirtual(const SoundSource* lhs, const SoundSource* rhs);
/// comparePriorityEarlier, with the priority of the sounds that are stopping or virtualized set to 0.
s32 comparePriorityEarlierIgnoreStopOrVirtual(const SoundSource* lhs, const SoundSource* rhs);
/// comparePriorityLater, with the priority of the sounds that are stopping or virtualized set to 0.
s32 comparePriorityLaterIgnoreStopOrVirtual(const SoundSource* lhs, const SoundSource* rhs);

}  // namespace SoundSourceSortFuncs

}  // namespace aal
