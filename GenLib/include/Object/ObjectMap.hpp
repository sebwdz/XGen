#ifndef OBJECTMAP_HPP
#define OBJECTMAP_HPP

typedef class   ClassCase    ClassCase;

class           ObjectMap
{
public:
                ObjectMap();
                virtual ~ObjectMap();

                ClassCase                       *get_cases();
                std::pair<float, float>         &get_pos();
                virtual void                    set_pos(std::pair<float, float> &pos);
                void                            set_case(ClassCase* mycase);
protected:
                std::pair<float, float> m_pos;
                ClassCase                       *m_case;
};

#endif // OBJECTMAP_HPP
