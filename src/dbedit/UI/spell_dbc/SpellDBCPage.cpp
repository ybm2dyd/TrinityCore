#include "SpellDBCPage.h"
#include "SpellDataDisplay.h"
#include "SpellSearchResult.h"
#include "SpellSearchResults.h"
#include "QtHelpers.h"
#include <QLineEdit>

void SpellDBCPage::Setup()
{
    FIND_Q_CHILD_DELAYED(_searchBox);
    FIND_Q_CHILD_DELAYED(_searchResults);
    FIND_Q_CHILD_DELAYED(_dataDisplay);
    CONNECT(_searchBox, returnPressed, this, SearchEnterPressed);
    CONNECT(_searchResults, currentItemChanged, this, SearchItemSelected);
    _dataDisplay->Setup();
    _dataDisplay->hide();
}

void SpellDBCPage::SearchEnterPressed()
{
    QString str = _searchBox->text();
    if (str.size() > 3)
        _searchResults->DoSearch(str);
    else
    {
        _searchResults->clear();
        _searchResults->AddMessage("Type 3 or more characters to search...");
    }
}

void SpellDBCPage::SearchItemSelected(QListWidgetItem* widget, QListWidgetItem* /*old*/)
{
    if (widget)
    {
        uint32 const spellId = static_cast<SpellSearchResult*>(widget)->GetId();
        _dataDisplay->SetSpell(spellId);
        _dataDisplay->show();
    }
    else
        _dataDisplay->hide();
}
