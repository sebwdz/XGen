#ifndef PLUGIN_HPP
#define PLUGIN_HPP

#include        <qplugin.h>

class       Plugin
{
public:
    Plugin() {}
    virtual ~Plugin() {}
};

Q_DECLARE_INTERFACE(Plugin, "plugin basic")

#endif // PLUGIN_HPP
