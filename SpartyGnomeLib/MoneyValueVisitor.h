/**
 * @file MoneyValueVisitor.h
 * @author ashrey
 *
 *
 */

#ifndef SPARTYGNOME_MONEYVALUEVISITOR_H
#define SPARTYGNOME_MONEYVALUEVISITOR_H

#include "ItemVisitor.h"
class MoneyValueVisitor: public ItemVisitor {
private:
    double mValueFactor;
public:
    MoneyValueVisitor(double valueFactor);

    void VisitMoney(ItemMoney* money) override;
};

#endif //SPARTYGNOME_MONEYVALUEVISITOR_H
