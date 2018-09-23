#ifndef TRINITY_DBEDIT_SPELLDBCPAGE_H
#define TRINITY_DBEDIT_SPELLDBCPAGE_H

#include "TopLevelPage.h"

class QLineEdit;
class QListWidgetItem;
class SpellDataDisplay;
class SpellSearchResults;

class SpellDBCPage : public TopLevelPage
{
    Q_OBJECT
    
    public:
        SpellDBCPage(QWidget* parent = nullptr) : TopLevelPage(parent) {}
        void Setup() override;

    public Q_SLOTS:
        void SearchEnterPressed();
        void SearchItemSelected(QListWidgetItem* selected, QListWidgetItem*);

    private:
        QLineEdit* _searchBox;
        SpellSearchResults* _searchResults;
        SpellDataDisplay* _dataDisplay;
};

#endif
