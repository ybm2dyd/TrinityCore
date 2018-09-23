#include "SpellProperties.h"
#include "DBCStructure.h"
#include "Log.h"
#include "QtHelpers.h"
#include "SearchableDropdown.h"
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QSpinBox>
#include <QStackedWidget>

SpellSchoolSelector::SpellSchoolSelector(QWidget* parent) : QGroupBox(parent)
{
    QGridLayout* layout = new QGridLayout(this);
    for (SpellSchools v : EnumUtils<SpellSchools>::Iterate())
    {
        QCheckBox* box = new QCheckBox(this);
        _checkboxes.emplace(box, (1 << v));
        box->setText(EnumUtils<SpellSchools>::ToTitle(v));
        layout->addWidget(box, (v + 1) / 2, (v ? 1 - (v % 2) : 0), 1, (v ? 1 : 2), Qt::AlignLeft);
    }
}

void SpellSchoolSelector::SetMask(uint32 mask)
{
    for (auto pair : _checkboxes)
        pair.first->setChecked(pair.second & mask);
}

uint32 SpellSchoolSelector::GetMask() const
{
    uint32 v = 0;
    for (auto pair : _checkboxes)
        if (pair.first->isChecked())
            v |= pair.second;
    return v;
}

void SpellProperties::Setup()
{
    FIND_Q_CHILD_DELAYED(_powerType);
    FIND_Q_CHILD_DELAYED(_powerTypeSub);
    FIND_Q_CHILD_DELAYED(_manaCost);
    FIND_Q_CHILD_DELAYED(_manaCostPctPrefix);
    FIND_Q_CHILD_DELAYED(_manaCostPercentage);
    FIND_Q_CHILD_DELAYED(_manaCostPctSuffix);
    FIND_Q_CHILD_DELAYED(_runeCost);

    _manaCost->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    _manaCostPercentage->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    FIND_Q_CHILD_DELAYED(_castTime);
    FIND_Q_CHILD_DELAYED(_spellSchools);
    FIND_Q_CHILD_DELAYED(_recoveryTime);
}

void SpellProperties::PowerTypeChanged()
{
    switch (_powerType->GetCurrentValue())
    {
        case POWER_RUNE:
            _powerTypeSub->setCurrentIndex(PAGE_RUNE);
            break;
        case POWER_RUNIC_POWER:
            _manaCostPctPrefix->hide();
            _manaCostPercentage->hide();
            _manaCostPctSuffix->hide();
            _powerTypeSub->setCurrentIndex(PAGE_REGULAR);
            break;
        default:
            _manaCostPctPrefix->show();
            _manaCostPercentage->show();
            _manaCostPctSuffix->show();
            _powerTypeSub->setCurrentIndex(PAGE_REGULAR);
    }
}

void SpellProperties::SetEntry(SpellEntry const* entry)
{
    _powerType->SetCurrentValue(Powers(entry->powerType));
    _manaCost->setValue(entry->manaCost);
    _manaCostPercentage->setValue(entry->ManaCostPercentage);
    _runeCost->SetCurrentKey(entry->runeCostID);
    _manaCostPerLevel = entry->manaCostPerlevel;
    PowerTypeChanged();
    CONNECT(_powerType, ValueChanged, this, PowerTypeChanged);
    CONNECT(_powerType, ValueChanged, this, ValueChanged);
    connect(_manaCost, QOverload<int>::of(&QSpinBox::valueChanged), this, &SpellProperties::ValueChanged);
    connect(_manaCostPercentage, QOverload<int>::of(&QSpinBox::valueChanged), this, &SpellProperties::ValueChanged);
    CONNECT(_runeCost, ValueChanged, this, ValueChanged);

    _castTime->SetCurrentKey(entry->CastingTimeIndex);
    _spellSchools->SetMask(entry->SchoolMask);
    _recoveryTime->setValue(double(entry->RecoveryTime) / 1000);
    printf("Category recovery time %u\n", entry->CategoryRecoveryTime);
    printf("Damage class %s\n", EnumUtils<SpellDmgClass>::ToTitle(SpellDmgClass(entry->DmgClass)));
    printf("InterruptFlags %u\n", entry->InterruptFlags);
}

void SpellProperties::BuildEntry(SpellEntry& entry) const
{
    entry.powerType = _powerType->GetCurrentValue();
    entry.manaCost = _manaCost->value();
    entry.ManaCostPercentage = _manaCostPercentage->value();
    entry.runeCostID = _runeCost->GetCurrentKey();
    entry.manaCostPerlevel = _manaCostPerLevel;
    entry.RecoveryTime = uint32(_recoveryTime->value() * 1000);

    entry.CastingTimeIndex = _castTime->GetCurrentKey();
    entry.SchoolMask = _spellSchools->GetMask();
}
