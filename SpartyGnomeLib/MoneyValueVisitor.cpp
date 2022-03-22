/**
 * @file MoneyValueVisitor.cpp
 * @author ashre
 */

#include "pch.h"
#include "MoneyValueVisitor.h"
#include "ItemMoney.h"

/**
 * Constructor for this visitor to increase all money items by a factor.
 * The value added will the product of valueFactor and the value of a given money item.
 *
 * @param valueFactor The percent increase to add to the value of money items
 */
MoneyValueVisitor::MoneyValueVisitor(double valueFactor)
{
    mValueFactor = valueFactor;
}

/**
 * Increase the value of the given money item by the percent increase given at the constructor
 * @param money The money to increase the value of
 */
void MoneyValueVisitor::VisitMoney(ItemMoney* money)
{
    int newMoney = money->GetValue() * (1 + mValueFactor);
    money->SetValue(newMoney);
}

