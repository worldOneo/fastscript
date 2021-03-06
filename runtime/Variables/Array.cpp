#include "Variable.hpp"
#include "../Utility.hpp"
#include <sstream>
#include <cstring>
#include <iostream>

namespace fastscript::runtime
{
    Array::Array()
    {
    }

    Array::~Array()
    {
        for (int i = 0; i < index; i++)
        {
            auto var = this->data[i];
            if (var->getOwner() == this || var->getOwner() == nullptr)
                delete var;
        }
        delete data;
    }

    Variable *Array::add(Variable *v)
    {
        this->data[this->index] = v;
        v->setOwner(v->getOwner() == nullptr ? this : v->getOwner());
        if (++this->index > this->size)
        {
            resize();
        }
        return this;
    }

    std::string Array::to_string()
    {
        std::ostringstream out;
        out << this->get_size() << " :[ ";
        for (int a = 0; a < this->get_size(); a++)
        {
            auto variable = this->data[a];
            StringAble *stringAble = dynamic_cast<StringAble *>(variable);
            if (!stringAble)
            {
                out << variable->name() << "@" << &variable << ", ";
                continue;
            }
            out << stringAble->to_string() << ", ";
        }
        out << "]";
        return out.str();
    }

    void Array::resize()
    {
        size_t newSize = size * 2;
        Variable *newArr[newSize];

        std::memcpy(newArr, this->data, size * sizeof(Variable *));

        this->size = newSize;
        delete[] this->data;
        this->data = newArr;
    }

    int Array::get_size()
    {
        return this->index;
    }

    Variable *Array::get(int i)
    {
        return this->data[i];
    }

    Variable *Array::set_index(int i, Variable *v)
    {
        return this->data[i] = v;
    }
}