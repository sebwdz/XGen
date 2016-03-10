#ifndef SERIALIZE_HPP
#define SERIALIZE_HPP

#include        <vector>

class           Serialize
{
public:
    void                append(char *str, unsigned int size)
    {
        for (unsigned int it = 0; it < size; it++)
            data.push_back(str[it]);
    }

    std::vector<char>   data;
};

#endif // SERIALIZE_HPP
