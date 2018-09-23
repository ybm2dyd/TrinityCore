#ifndef TRINITY_DBEDIT_SPELLCASTERPROPERTIES_H
#define TRINITY_DBEDIT_SPELLCASTERPROPERTIES_H

#include <QGroupBox>

struct SpellEntry;

class SpellCasterProperties : public QGroupBox
{
    Q_OBJECT

    public:
        SpellCasterProperties(QWidget* parent = nullptr) : QGroupBox(parent) {}
        void Setup();
        void SetEntry(SpellEntry const*);
        void BuildEntry(SpellEntry&) const;

    Q_SIGNALS:
        void ValueChanged();
};

#endif
