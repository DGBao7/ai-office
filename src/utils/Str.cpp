#include "utils/Str.h"

namespace utils
{
    bool _is_blank(std::string str)
    {
        for (auto i : str)
        {
            if (i != ' ')
            {
                return false;
            }
        }

        return true;
    }
}