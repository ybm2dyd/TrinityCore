#ifndef TRINITY_DBEDIT_SPELLBASEPROPERTIES_H
#define TRINITY_DBEDIT_SPELLBASEPROPERTIES_H

#include <QGroupBox>
#include "SearchableDropdownDecl.h"

class QLabel;
struct SpellEntry;

class SpellBaseProperties : public QGroupBox
{
    Q_OBJECT

    public:
        SpellBaseProperties(QWidget* parent = nullptr) : QGroupBox(parent) {}
        void Setup();
        void SetEntry(SpellEntry const*);
        void BuildEntry(SpellEntry&) const;

    Q_SIGNALS:
        void ValueChanged();

    private:
        QLabel*                 _spellId;
        QLabel*                 _spellName;
        QLabel*                 _spellRank;
        SpellFamilyDropdown*    _spellFamily;

        uint32                  _currentSpellId;
};

#endif
