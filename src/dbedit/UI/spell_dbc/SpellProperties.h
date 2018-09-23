#ifndef TRINITY_DBEDIT_SPELLPROPERTIES_H
#define TRINITY_DBEDIT_SPELLPROPERTIES_H

#include "SearchableDropdownDecl.h"
#include <QGroupBox>
#include <unordered_map>

class QCheckBox;
class QDoubleSpinBox;
class QLabel;
class QSpinBox;
class QStackedWidget;
struct SpellEntry;
enum SpellSchools;

class SpellSchoolSelector : public QGroupBox
{
    Q_OBJECT

    public:
        SpellSchoolSelector(QWidget* parent = nullptr);
        void SetMask(uint32);
        uint32 GetMask() const;

    private:
        std::unordered_map<QCheckBox*, uint32> _checkboxes;
};

class SpellProperties : public QGroupBox
{
    Q_OBJECT

    public:
        SpellProperties(QWidget* parent = nullptr) : QGroupBox(parent) {}
        void Setup();
        void SetEntry(SpellEntry const*);
        void BuildEntry(SpellEntry&) const;

    Q_SIGNALS:
        void ValueChanged();

    private Q_SLOTS:
        void PowerTypeChanged();

    private:
        PowerTypeDropdown*      _powerType;
        QStackedWidget*         _powerTypeSub;
        enum PowerTypePages     { PAGE_REGULAR = 0, PAGE_RUNE = 1 };
        QSpinBox*               _manaCost;
        QLabel*                 _manaCostPctPrefix;
        QSpinBox*               _manaCostPercentage;
        QLabel*                 _manaCostPctSuffix;
        RuneCostDropdown*       _runeCost;

        SpellCastTimeDropdown*  _castTime;
        SpellSchoolSelector*    _spellSchools;
        QDoubleSpinBox*         _recoveryTime;

        uint32 _manaCostPerLevel;
};

#endif
