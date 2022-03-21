/**
 * @file MoneyValueVisitor.cpp
 * @author ashre
 */

#include "MoneyValueVisitor.h"
#include "ItemMoney.h"
MoneyValueVisitor::MoneyValueVisitor(double valueFactor)
{
    mValueFactor = valueFactor;
}

void MoneyValueVisitor::VisitMoney(ItemMoney* money)
{
    int newMoney = money->GetValue() * (1 + mValueFactor);
    money->SetValue(newMoney);
}

