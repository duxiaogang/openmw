
#include "collectionbase.hpp"

#include <stdexcept>
#include <cassert>

#include "columnbase.hpp"

CSMWorld::CollectionBase::CollectionBase() {}

CSMWorld::CollectionBase::~CollectionBase() {}

int CSMWorld::CollectionBase::searchColumnIndex (Columns::ColumnId id) const
{
    int columns = getColumns();

    for (int i=0; i<columns; ++i)
        if (getColumn (i).mColumnId==id)
            return i;

    return -1;
}

int CSMWorld::CollectionBase::findColumnIndex (Columns::ColumnId id) const
{
    int index = searchColumnIndex (id);

    if (index==-1)
        throw std::logic_error ("invalid column index");

    return index;
}

void CSMWorld::CollectionBase::setNestedData(int row, int column, const QVariant& data, int subRow, int subColumn)
{
    assert(false); //TODO remove and make pure abstract
}

int CSMWorld::CollectionBase::getNestedColumnsCount(int row, int column) const
{
    assert(false); //TODO remove and make pure abstract
    return 0;
}

int CSMWorld::CollectionBase::getNestedRowsCount(int row, int column) const
{
    assert(false); //TODO, make pure abstract
    return 0;
}

void CSMWorld::CollectionBase::removeNestedRows(int row, int column, int subRow)
{
    assert(false); //todo, make pure abstract
}
