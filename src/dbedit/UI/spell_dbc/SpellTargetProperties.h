#ifndef TRINITY_DBEDIT_SPELLTARGETPROPERTIES_H
#define TRINITY_DBEDIT_SPELLTARGETPROPERTIES_H

#include <QGroupBox>

struct SpellEntry;

class SpellTargetProperties : public QGroupBox
{
    Q_OBJECT

    public:
        SpellTargetProperties(QWidget* parent = nullptr) : QGroupBox(parent) {}
        void Setup();
        void SetEntry(SpellEntry const* entry);
        void BuildEntry(SpellEntry&) const;

    Q_SIGNALS:
        void ValueChanged();
};

#endif
