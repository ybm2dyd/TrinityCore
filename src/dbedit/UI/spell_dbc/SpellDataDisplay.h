#ifndef TRINITY_DBEDIT_SPELLDATADISPLAY_H
#define TRINITY_DBEDIT_SPELLDATADISPLAY_H

#include <QWidget>

class SpellAttributes;
class SpellAuraProperties;
class SpellBaseProperties;
class SpellCasterProperties;
class SpellEffectProperties;
class SpellProperties;
class SpellSourceSelector;
class SpellTargetProperties;

class SpellDataDisplay : public QWidget
{
    Q_OBJECT

    public:
        SpellDataDisplay(QWidget* parent = nullptr) : QWidget(parent) {}
        void Setup();
        void SetSpell(unsigned int);

    Q_SIGNALS:
        void HavePendingChanges(bool);

    public Q_SLOTS:
        void ChildValueChanged() { Q_EMIT HavePendingChanges(true); }
        void SaveToDB();
        void Redraw();

    private:
        SpellSourceSelector*    _sourceSelector     = nullptr;
        SpellBaseProperties*    _baseProperties     = nullptr;
        SpellProperties*        _spellProperties    = nullptr;
        SpellAuraProperties*    _auraProperties     = nullptr;
        SpellCasterProperties*  _casterProperties   = nullptr;
        SpellTargetProperties*  _targetProperties   = nullptr;
        SpellAttributes*        _attributes         = nullptr;
        SpellEffectProperties*  _effect0            = nullptr;
        SpellEffectProperties*  _effect1            = nullptr;
        SpellEffectProperties*  _effect2            = nullptr;
};

#endif
