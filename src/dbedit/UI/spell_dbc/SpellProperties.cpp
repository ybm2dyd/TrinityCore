#include "SpellProperties.h"
#include "DBCStructure.h"
#include "Log.h"
#include "QtHelpers.h"
#include "SearchableDropdown.h"
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
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
    FIND_Q_CHILD_DELAYED(_upkeepLabel);
    FIND_Q_CHILD_DELAYED(_upkeepWidget);
    FIND_Q_CHILD_DELAYED(_channelCost);
    FIND_Q_CHILD_DELAYED(_channelCostPerLevel);

    FIND_Q_CHILD_DELAYED(_castTime);
    FIND_Q_CHILD_DELAYED(_spellSchools);
    FIND_Q_CHILD_DELAYED(_recoveryTime);
    FIND_Q_CHILD_DELAYED(_spellCategory);
    FIND_Q_CHILD_DELAYED(_categoryCooldown);
    FIND_Q_CHILD_DELAYED(_gcdCategory);
    FIND_Q_CHILD_DELAYED(_gcdDuration);
}

void SpellProperties::PowerTypeChanged()
{
    switch (_powerType->GetCurrentValue())
    {
        case POWER_RUNE:
            _powerTypeSub->setCurrentIndex(PAGE_RUNE);
            _upkeepLabel->hide();
            _upkeepWidget->hide();
            break;
        case POWER_RUNIC_POWER:
            _manaCostPctPrefix->hide();
            _manaCostPercentage->hide();
            _manaCostPctSuffix->hide();
            _upkeepLabel->hide();
            _upkeepWidget->hide();
            _powerTypeSub->setCurrentIndex(PAGE_REGULAR);
            break;
        default:
            _manaCostPctPrefix->show();
            _manaCostPercentage->show();
            _manaCostPctSuffix->show();
            _upkeepLabel->show();
            _upkeepWidget->show();
            _powerTypeSub->setCurrentIndex(PAGE_REGULAR);
            break;
    }
}

void SpellProperties::SetEntry(SpellEntry const* entry)
{
    _powerType->SetCurrentValue(Powers(entry->powerType));
    _manaCost->setValue(entry->manaCost);
    _manaCostPercentage->setValue(entry->ManaCostPercentage);
    _runeCost->SetCurrentKey(entry->runeCostID);
    _manaCostPerLevel = entry->manaCostPerlevel;
    _channelCost->setValue(entry->manaPerSecond);
    _channelCostPerLevel->setValue(entry->manaPerSecondPerLevel);
    PowerTypeChanged();
    CONNECT(_powerType, ValueChanged, this, PowerTypeChanged);
    CONNECT(_powerType, ValueChanged, this, ValueChanged);
    connect(_manaCost, QOverload<int>::of(&QSpinBox::valueChanged), this, &SpellProperties::ValueChanged);
    connect(_manaCostPercentage, QOverload<int>::of(&QSpinBox::valueChanged), this, &SpellProperties::ValueChanged);
    CONNECT(_runeCost, ValueChanged, this, ValueChanged);

    _castTime->SetCurrentKey(entry->CastingTimeIndex);
    _recoveryTime->setValue(double(entry->RecoveryTime) / 1000);
    _spellCategory->setValue(entry->Category);
    _categoryCooldown->setValue(double(entry->CategoryRecoveryTime) / 1000);
    _gcdCategory->setValue(entry->StartRecoveryCategory);
    _gcdDuration->setValue(double(entry->StartRecoveryTime) / 1000);

    _spellSchools->SetMask(entry->SchoolMask);
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
    entry.manaPerSecond = _channelCost->value();
    entry.manaPerSecondPerLevel = _channelCostPerLevel->value();

    entry.CastingTimeIndex = _castTime->GetCurrentKey();
    entry.RecoveryTime = uint32(_recoveryTime->value() * 1000);

    entry.Category = _spellCategory->value();
    entry.CategoryRecoveryTime = uint32(_categoryCooldown->value() * 1000);
    entry.StartRecoveryCategory = _gcdCategory->value();
    entry.StartRecoveryTime = uint32(_gcdDuration->value() * 1000);

    entry.SchoolMask = _spellSchools->GetMask();
}
