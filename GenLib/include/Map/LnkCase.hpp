#ifndef LNKCASE_HPP
#define LNKCASE_HPP

# include                   "ClassCase.hpp"

# define                    INV_DIR(X)      (LnkDir)(X & 1 ? X - 1 : X + 1)
enum                        LnkDir { UP, DOWN, LEFT, RIGHT, NONE, ALL};

typedef                     class ClassMap ClassMap;

class                       LnkCase
{
public:
    LnkCase(LnkDir border, ClassMap *map);
    virtual ~LnkCase();

    LnkCase                 *get_next(LnkDir dir, std::pair<int, int> &pos, bool create, bool cross);
    void                    set_dir(LnkDir dir, LnkCase *lnk);
    void                    set_pos(std::pair<int, int> pos);
    void                    set_case(ClassCase *newCase);
    bool                    check_remove(bool forced = false);
    void                    remove(bool forced = false);
    std::pair<int, int>     &get_pos();
    LnkCase                 *get_dir(LnkDir dir);
    ClassCase               *get_case();
    LnkDir                  get_border();
    ClassMap                *get_map();

private:
    LnkCase                 *m_dir[4];
    std::pair<int, int>     m_pos;
    ClassCase               *m_case;
    LnkDir                  m_border;
    ClassMap                *m_map;
};

#endif // LNKCASE_HPP
