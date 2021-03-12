#include <stddef.h>
#include "Variables/Variable.hpp"

#define _math_shortdefinition(x, y)        \
    template <typename V>                  \
    _result<V, V> _math_##x()              \
    {                                      \
        return [](V a, V b) { return y; }; \
    }

namespace fastscript::runtime::utility
{
    template <typename operator_type>
    using math_operator = operator_type (*)(operator_type, operator_type);

    template <typename operator_type, typename custom_return>
    using math_operatorz = custom_return (*)(operator_type, operator_type);

    template <typename resolved>
    using resolver = resolved (*)(Variable *);

    int intResolver(Variable *Variable);

    template <typename V1, typename T>
    T _math_operation(V1 *var1, Variable *var2, math_operator<T> oper)
    {
        return (*oper)(intResolver(var1), intResolver(var2));
    }

    template <typename V1, typename T>
    T _math_operation(V1 *var1, Variable *var2, math_operator<T> oper, resolver<T> res)
    {
        return (*oper)((*res)(var1), (*res)(var2));
    }

    template <typename V1, typename T, typename Z>
    Z _math_operationz(V1 *var1, Variable *var2, math_operatorz<T, Z> oper, resolver<T> res)
    {
        return (*oper)((*res)(var1), (*res)(var2));
    }

    template <typename T, typename Z>
    using _result = Z (*)(T, T);

    _math_shortdefinition(xor, a ^ b);
    _math_shortdefinition(and, a &b);
    _math_shortdefinition(or, a | b);
    _math_shortdefinition(lshft, a << b);
    _math_shortdefinition(rshft, a >> b);

    _math_shortdefinition(eq, (V)(a == b));
    _math_shortdefinition(gt, (V)(a > b));
    _math_shortdefinition(lt, (V)(a < b));

    _math_shortdefinition(add, a + b);
    _math_shortdefinition(subtract, a - b);
    _math_shortdefinition(divide, a / b);
    _math_shortdefinition(multiply, a *b);
    _math_shortdefinition(modulo, a % b);
}