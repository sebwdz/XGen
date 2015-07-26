#ifndef OBJECTMAP_HPP
#define OBJECTMAP_HPP

# include       "Object.hpp"

typedef class   ClassCase    ClassCase;

class           ObjectMap : public Object
{
public:
                ObjectMap(Object *parent);
                virtual ~ObjectMap();

                std::list<SMART(ClassCase)>    &get_cases();
private:

                std::list<SMART(ClassCase)>    m_cases;
};

#endif // OBJECTMAP_HPP
