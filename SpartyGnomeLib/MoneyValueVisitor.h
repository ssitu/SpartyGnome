/**
 * @file MoneyValueVisitor.h
 * @author ashrey
 *
 * The visitor to increase the value of money items
 */

#ifndef SPARTYGNOME_MONEYVALUEVISITOR_H
#define SPARTYGNOME_MONEYVALUEVISITOR_H

#include "ItemVisitor.h"

/**
 * The visitor that handles the increase to money values
 */
class MoneyValueVisitor: public ItemVisitor {
private:
    double mValueFactor;
public:
    MoneyValueVisitor(double valueFactor);

    void VisitMoney(ItemMoney* money) override;
};

#endif //SPARTYGNOME_MONEYVALUEVISITOR_H
