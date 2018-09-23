#ifndef TRINITY_DBEDIT_SPELLEFFECTPROPERTIES_H
#define TRINITY_DBEDIT_SPELLEFFECTPROPERTIES_H

#include "Define.h"
#include <QWidget>

struct SpellEntry;
enum SpellEffIndex : uint8;

class SpellEffectProperties : public QWidget
{
    Q_OBJECT

    public:
        SpellEffectProperties(QWidget* parent = nullptr) : QWidget(parent) {}
        void Setup();
        void SetEntry(SpellEntry const*, SpellEffIndex index);
        void BuildEntry(SpellEntry&, SpellEffIndex index) const;

    Q_SIGNALS:
        void ValueChanged();
};

#endif
