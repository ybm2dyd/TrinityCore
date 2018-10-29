/*
 * Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TRINITY_SPELLDEFINES_H
#define TRINITY_SPELLDEFINES_H

#include "Define.h"
#include "ObjectGuid.h"
#include <vector>

class Item;
class AuraEffect;

struct TC_GAME_API CastSpellExtraArgs
{
    CastSpellExtraArgs() {}
    CastSpellExtraArgs(bool triggered) : TriggerFlags(triggered ? TRIGGERED_FULL_MASK : TRIGGERED_NONE) {}
    CastSpellExtraArgs(TriggerCastFlags trigger) : TriggerFlags(trigger) {}
    CastSpellExtraArgs(Item* item) : TriggerFlags(TRIGGERED_FULL_MASK), CastItem(item) {}
    CastSpellExtraArgs(AuraEffect const* eff) : TriggerFlags(TRIGGERED_FULL_MASK), TriggeringAura(eff) {}
    CastSpellExtraArgs(ObjectGuid const& origCaster) : TriggerFlags(TRIGGERED_FULL_MASK), OriginalCaster(origCaster) {}
    CastSpellExtraArgs(AuraEffect const* eff, ObjectGuid const& origCaster) : TriggerFlags(TRIGGERED_FULL_MASK), TriggeringAura(eff), OriginalCaster(origCaster) {}
    CastSpellExtraArgs(SpellValueMod mod, int32 val) { SpellValueOverrides.AddMod(mod, val); }

    CastSpellExtraArgs& SetTriggerFlags(TriggerCastFlags flag) { TriggerFlags = flag; return *this; }
    CastSpellExtraArgs& SetCastItem(Item* item) { CastItem = item; return *this; }
    CastSpellExtraArgs& SetTriggeringAura(AuraEffect const* triggeringAura) { TriggeringAura = triggeringAura; return *this; }
    CastSpellExtraArgs& SetOriginalCaster(ObjectGuid const& guid) { OriginalCaster = guid; return *this; }
    CastSpellExtraArgs& AddSpellMod(SpellValueMod mod, int32 val) { SpellValueOverrides.AddMod(mod, val); return *this; }
    CastSpellExtraArgs& AddSpellBP0(int32 val) { return AddSpellMod(SPELLVALUE_BASE_POINT0, val); } // because i don't want to type SPELLVALUE_BASE_POINT0 300 times

    TriggerCastFlags TriggerFlags = TRIGGERED_NONE;
    Item* CastItem = nullptr;
    AuraEffect const* TriggeringAura = nullptr;
    ObjectGuid OriginalCaster = ObjectGuid::Empty;
    struct
    {
        friend struct CastSpellExtraArgs;
        friend class WorldObject;

        private:
            void AddMod(SpellValueMod mod, int32 val) { data.push_back({ mod, val }); }

            auto begin() const { return data.cbegin(); }
            auto end() const { return data.cend(); }

            std::vector<std::pair<SpellValueMod, int32>> data;
    } SpellValueOverrides;
};

#endif
