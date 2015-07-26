#ifndef OBJECTMAP_HPP
#define OBJECTMAP_HPP

# include       "Object/Object.hpp"

class           ObjectMap : public Object
{
public:
                ObjectMap(Object *parent);
                ~ObjectMap();

                std::list<void*>    &get_cases();
private:

                std::list<void*>    m_cases;
};

#endif // OBJECTMAP_HPP
