#ifndef OBJECTMAP_HPP
#define OBJECTMAP_HPP

# include       "Object.hpp"

typedef class   ClassCase    ClassCase;

class           ObjectMap : public Object
{
public:
                ObjectMap(Object *parent);
                virtual ~ObjectMap();

                ClassCase                       *get_cases();
                void                            set_case(ClassCase* mycase);
protected:

                ClassCase                       *m_case;
};

#endif // OBJECTMAP_HPP
