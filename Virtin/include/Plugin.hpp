#ifndef PLUGIN_HPP
#define PLUGIN_HPP

#include        <QWidget>
#include        <QPluginLoader>
#include        <qplugin.h>

class       Plugin
{
public:
  Plugin();
  virtual ~Plugin() {}

  virtual QWidget     *get_new_widget(std::string &path) = 0;
  void                close();

  static Plugin   *load(std::string &path);

  QPluginLoader   *m_load;
};

Q_DECLARE_INTERFACE(Plugin, "plugin basic")

class       MachineViewWidget : public QWidget, public MachineView
{
public:
  MachineViewWidget() { }
  virtual ~MachineViewWidget() = 0;
};

class       PluginMachine : public Plugin
{
public:
  PluginMachine();
  virtual ~PluginMachine() { }

  virtual VirtualMachine      *get_machine() = 0;
  virtual MachineViewWidget   *get_view() = 0;

  static PluginMachine    *load_machine(std::string &path);

};

Q_DECLARE_INTERFACE(PluginMachine, "plugin machine")


#endif // PLUGIN_HPP
