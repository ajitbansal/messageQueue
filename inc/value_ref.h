
#pragma once

#include <string>
#include <cstring>
#include <memory>

namespace messagequeue
{

template <typename T>
class data_ref
{
public:

    using value_type = T;

    using buff = std::basic_string<value_type>;

    using ptr_type = std::shared_ptr<const buff>;

    data_ref() = default;
    

private:

    ptr_type data_;

}
}