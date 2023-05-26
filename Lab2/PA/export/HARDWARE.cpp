#include "systemc.h"
#include "../adder.h"
#include "../clockreset.h"
#include "cassert"
#include "cwr_dynamic_loader.h"
#include "cwr_sc_dynamic_stubs.h"
#include "cwr_sc_hierarch_module.h"
#include "cwr_sc_object_creator.h"
#include "scmlinc/scml_abstraction_level_switch.h"
#include "scmlinc/scml_property_registry.h"

using namespace conf;
using namespace std;


class Clock0Creator : public ScObjectCreatorBase
{
public:
  static unsigned int creationVerboseMode() {
    const char * const env_var_val = ::getenv("SNPS_SLS_DYNAMIC_CREATION_VERBOSE");
    return env_var_val ? (::atoi(env_var_val)) : 3;
  }
  sc_object* create ( const string& name ) {
    string hierach_name = getHierarchicalName(name);
    int division = scml_property_registry::inst().getIntProperty(
	      scml_property_registry::CONSTRUCTOR, hierach_name, "division");

    int cycle = scml_property_registry::inst().getIntProperty(
	      scml_property_registry::CONSTRUCTOR, hierach_name, "cycle");

    if (scml_property_registry::inst().hasProperty(scml_property_registry::MODULE, scml_property_registry::BOOL, hierach_name, "runtime_disabled") && 
        scml_property_registry::inst().getBoolProperty(scml_property_registry::MODULE, hierach_name, "runtime_disabled")) {
      sc_module_name n(name.c_str());
      if (creationVerboseMode() >= 6) { std::cout << "Clock/Clock: STUB for " << hierach_name << " created." << std::endl; }
      conf::stub *result = new conf::stub(n);
       conf::stub_port_registrator<>::register_stub_port(&Clock::clk, "clk" , string(static_cast<sc_object*>(result)->name()) + ".clk" );
      return result;
    } else {
      if (creationVerboseMode() >= 6) { std::cout << "Clock/Clock: " << hierach_name << " created." << std::endl; }
      Clock* result = new Clock(name.c_str(), division, cycle);
       cwr_sc_object_registry::inst().addPort(&result->clk, string(static_cast<sc_object*>(result)->name()) + ".clk" );
      return result;
    }
  }
};

template <class BC>
class BusCreator : public ScObjectCreatorBase
{
  sc_object* create (const string& name) {
    ScGeneratedBaseBlockCreatorHelper helper(getHierarchicalName(name));
    if (helper.is_runtime_disabled()) {
      return new conf::StubBusCreator(name.c_str(), helper);
    } else {
      return new BC(name.c_str(), helper);
    }
  }
};

template <class GBC>
class GeneratedBlockCreator : public ScObjectCreatorBase
{
  sc_object* create (const string& name) {
    ScGeneratedBaseBlockCreatorHelper helper(getHierarchicalName(name));
    if (helper.is_runtime_disabled()) {
      return new conf::StubBusCreator(name.c_str(), helper);
    } else {
      return new GBC(name.c_str(), helper);
    }
  }
};



class Reset0Creator : public ScObjectCreatorBase
{
public:
  static unsigned int creationVerboseMode() {
    const char * const env_var_val = ::getenv("SNPS_SLS_DYNAMIC_CREATION_VERBOSE");
    return env_var_val ? (::atoi(env_var_val)) : 3;
  }
  sc_object* create ( const string& name ) {
    string hierach_name = getHierarchicalName(name);
    int _ticks = scml_property_registry::inst().getIntProperty(
	      scml_property_registry::CONSTRUCTOR, hierach_name, "_ticks");

    if (scml_property_registry::inst().hasProperty(scml_property_registry::MODULE, scml_property_registry::BOOL, hierach_name, "runtime_disabled") && 
        scml_property_registry::inst().getBoolProperty(scml_property_registry::MODULE, hierach_name, "runtime_disabled")) {
      sc_module_name n(name.c_str());
      if (creationVerboseMode() >= 6) { std::cout << "Reset/Reset: STUB for " << hierach_name << " created." << std::endl; }
      conf::stub *result = new conf::stub(n);
       conf::stub_port_registrator<>::register_stub_port(&Reset::rst, "rst" , string(static_cast<sc_object*>(result)->name()) + ".rst" );
      return result;
    } else {
      if (creationVerboseMode() >= 6) { std::cout << "Reset/Reset: " << hierach_name << " created." << std::endl; }
      Reset* result = new Reset(name.c_str(), _ticks);
       cwr_sc_object_registry::inst().addPort(&result->rst, string(static_cast<sc_object*>(result)->name()) + ".rst" );
      return result;
    }
  }
};


class adder0Creator : public ScObjectCreatorBase
{
public:
  static unsigned int creationVerboseMode() {
    const char * const env_var_val = ::getenv("SNPS_SLS_DYNAMIC_CREATION_VERBOSE");
    return env_var_val ? (::atoi(env_var_val)) : 3;
  }
  sc_object* create ( const string& name ) {
    string hierach_name = getHierarchicalName(name);
    if (scml_property_registry::inst().hasProperty(scml_property_registry::MODULE, scml_property_registry::BOOL, hierach_name, "runtime_disabled") && 
        scml_property_registry::inst().getBoolProperty(scml_property_registry::MODULE, hierach_name, "runtime_disabled")) {
      sc_module_name n(name.c_str());
      if (creationVerboseMode() >= 6) { std::cout << "adder/adder: STUB for " << hierach_name << " created." << std::endl; }
      conf::stub *result = new conf::stub(n);
       conf::stub_port_registrator<>::register_stub_port(&adder::clk, "clk" , string(static_cast<sc_object*>(result)->name()) + ".clk" );
       conf::stub_port_registrator<>::register_stub_port(&adder::rst, "rst" , string(static_cast<sc_object*>(result)->name()) + ".rst" );
       conf::stub_port_registrator<>::register_stub_port(&adder::a, "a" , string(static_cast<sc_object*>(result)->name()) + ".a" );
       conf::stub_port_registrator<>::register_stub_port(&adder::b, "b" , string(static_cast<sc_object*>(result)->name()) + ".b" );
       conf::stub_port_registrator<>::register_stub_port(&adder::c, "c" , string(static_cast<sc_object*>(result)->name()) + ".c" );
      return result;
    } else {
      if (creationVerboseMode() >= 6) { std::cout << "adder/adder: " << hierach_name << " created." << std::endl; }
      adder* result = new adder(name.c_str());
       cwr_sc_object_registry::inst().addPort(&result->clk, string(static_cast<sc_object*>(result)->name()) + ".clk" );
       cwr_sc_object_registry::inst().addPort(&result->rst, string(static_cast<sc_object*>(result)->name()) + ".rst" );
       cwr_sc_object_registry::inst().addPort(&result->a, string(static_cast<sc_object*>(result)->name()) + ".a" );
       cwr_sc_object_registry::inst().addPort(&result->b, string(static_cast<sc_object*>(result)->name()) + ".b" );
       cwr_sc_object_registry::inst().addPort(&result->c, string(static_cast<sc_object*>(result)->name()) + ".c" );
      return result;
    }
  }
};


class monitor0Creator : public ScObjectCreatorBase
{
public:
  static unsigned int creationVerboseMode() {
    const char * const env_var_val = ::getenv("SNPS_SLS_DYNAMIC_CREATION_VERBOSE");
    return env_var_val ? (::atoi(env_var_val)) : 3;
  }
  sc_object* create ( const string& name ) {
    string hierach_name = getHierarchicalName(name);
    if (scml_property_registry::inst().hasProperty(scml_property_registry::MODULE, scml_property_registry::BOOL, hierach_name, "runtime_disabled") && 
        scml_property_registry::inst().getBoolProperty(scml_property_registry::MODULE, hierach_name, "runtime_disabled")) {
      sc_module_name n(name.c_str());
      if (creationVerboseMode() >= 6) { std::cout << "monitor/monitor: STUB for " << hierach_name << " created." << std::endl; }
      conf::stub *result = new conf::stub(n);
       conf::stub_port_registrator<>::register_stub_port(&monitor::clk, "clk" , string(static_cast<sc_object*>(result)->name()) + ".clk" );
       conf::stub_port_registrator<>::register_stub_port(&monitor::rst, "rst" , string(static_cast<sc_object*>(result)->name()) + ".rst" );
       conf::stub_port_registrator<>::register_stub_port(&monitor::eyes, "eyes" , string(static_cast<sc_object*>(result)->name()) + ".eyes" );
      return result;
    } else {
      if (creationVerboseMode() >= 6) { std::cout << "monitor/monitor: " << hierach_name << " created." << std::endl; }
      monitor* result = new monitor(name.c_str());
       cwr_sc_object_registry::inst().addPort(&result->clk, string(static_cast<sc_object*>(result)->name()) + ".clk" );
       cwr_sc_object_registry::inst().addPort(&result->rst, string(static_cast<sc_object*>(result)->name()) + ".rst" );
       cwr_sc_object_registry::inst().addPort(&result->eyes, string(static_cast<sc_object*>(result)->name()) + ".eyes" );
      return result;
    }
  }
};


class pattern_gen0Creator : public ScObjectCreatorBase
{
public:
  static unsigned int creationVerboseMode() {
    const char * const env_var_val = ::getenv("SNPS_SLS_DYNAMIC_CREATION_VERBOSE");
    return env_var_val ? (::atoi(env_var_val)) : 3;
  }
  sc_object* create ( const string& name ) {
    string hierach_name = getHierarchicalName(name);
    if (scml_property_registry::inst().hasProperty(scml_property_registry::MODULE, scml_property_registry::BOOL, hierach_name, "runtime_disabled") && 
        scml_property_registry::inst().getBoolProperty(scml_property_registry::MODULE, hierach_name, "runtime_disabled")) {
      sc_module_name n(name.c_str());
      if (creationVerboseMode() >= 6) { std::cout << "pattern_gen/pattern_gen: STUB for " << hierach_name << " created." << std::endl; }
      conf::stub *result = new conf::stub(n);
       conf::stub_port_registrator<>::register_stub_port(&pattern_gen::clk, "clk" , string(static_cast<sc_object*>(result)->name()) + ".clk" );
       conf::stub_port_registrator<>::register_stub_port(&pattern_gen::rst, "rst" , string(static_cast<sc_object*>(result)->name()) + ".rst" );
       conf::stub_port_registrator<>::register_stub_port(&pattern_gen::in1, "in1" , string(static_cast<sc_object*>(result)->name()) + ".in1" );
       conf::stub_port_registrator<>::register_stub_port(&pattern_gen::in2, "in2" , string(static_cast<sc_object*>(result)->name()) + ".in2" );
      return result;
    } else {
      if (creationVerboseMode() >= 6) { std::cout << "pattern_gen/pattern_gen: " << hierach_name << " created." << std::endl; }
      pattern_gen* result = new pattern_gen(name.c_str());
       cwr_sc_object_registry::inst().addPort(&result->clk, string(static_cast<sc_object*>(result)->name()) + ".clk" );
       cwr_sc_object_registry::inst().addPort(&result->rst, string(static_cast<sc_object*>(result)->name()) + ".rst" );
       cwr_sc_object_registry::inst().addPort(&result->in1, string(static_cast<sc_object*>(result)->name()) + ".in1" );
       cwr_sc_object_registry::inst().addPort(&result->in2, string(static_cast<sc_object*>(result)->name()) + ".in2" );
      return result;
    }
  }
};



extern void scv_tr_cwrdb_init();

int sc_main(int argc, char* argv[])
{
  scv_tr_cwrdb_init();
  ScObjectFactory::inst().addCreator ("Clock0", new Clock0Creator());
  ScObjectFactory::inst().addCreator ("Reset0", new Reset0Creator());
  ScObjectFactory::inst().addCreator ("adder0", new adder0Creator());
  ScObjectFactory::inst().addCreator ("monitor0", new monitor0Creator());
  ScObjectFactory::inst().addCreator ("pattern_gen0", new pattern_gen0Creator());
  ScObjectFactory::inst().addCreator ("sc_signal<bool>", new ScPrimChannelCreator<sc_signal<bool> >());
  ScObjectFactory::inst().addCreator ("sc_signal<int>", new ScPrimChannelCreator<sc_signal<int> >());
  ScPortFactory::inst().addCreator ("sc_in<bool>", new ScPortCreator<sc_in<bool> >());
  ScPortFactory::inst().addCreator ("sc_in<int>", new ScPortCreator<sc_in<int> >());
  ScPortFactory::inst().addCreator ("sc_inout<bool>", new ScPortCreator<sc_inout<bool> >());
  ScPortFactory::inst().addCreator ("sc_inout<int>", new ScPortCreator<sc_inout<int> >());
  ScPortFactory::inst().addCreator ("sc_out<bool>", new ScPortCreator<sc_out<bool> >());
  ScPortFactory::inst().addCreator ("sc_out<int>", new ScPortCreator<sc_out<int> >());
  if (::getenv("SNPS_SLS_DYNAMIC_LOADER_VERBOSE")) { std::cout << "Clock/Clock loaded." << std::endl; }
  if (::getenv("SNPS_SLS_DYNAMIC_LOADER_VERBOSE")) { std::cout << "Reset/Reset loaded." << std::endl; }
  if (::getenv("SNPS_SLS_DYNAMIC_LOADER_VERBOSE")) { std::cout << "adder/adder loaded." << std::endl; }
  if (::getenv("SNPS_SLS_DYNAMIC_LOADER_VERBOSE")) { std::cout << "monitor/monitor loaded." << std::endl; }
  if (::getenv("SNPS_SLS_DYNAMIC_LOADER_VERBOSE")) { std::cout << "pattern_gen/pattern_gen loaded." << std::endl; }

  scml_property_registry::inst().setXMLFile("Properties.xml");

  nSnps::nDynamicLoading::DynamicLoader dynamicLoader
    (scml_property_registry::inst().getStringProperty(scml_property_registry::GLOBAL, "", "/pct/runtime/dynamic_load_info"));

  string xml_file_path = scml_property_registry::inst().getPropertyXmlFilePath();
  string hierarchy_xml_file = xml_file_path + "/" + 
    scml_property_registry::inst().getStringProperty(
      scml_property_registry::GLOBAL, "", "system_hierarchy_xml_file");

  cwr_sc_hierarch_module* HARDWARE = new cwr_sc_hierarch_module("HARDWARE", hierarchy_xml_file);

  // Enable/disable backdoor accesses
  scml_abstraction_level_switch::instance().set_simulation_mode(scml_property_registry::inst().getStringProperty(scml_property_registry::GLOBAL, "", "/pct/runtime/simulation_mode")=="MODE_FULL_SIMULATION" ? scml_abstraction_level_switch::MODE_FULL_SIMULATION : scml_abstraction_level_switch::MODE_SPEED_OPTIMIZED);

  sc_start();

  if (sc_is_running()) {
    sc_stop();
  }
  delete HARDWARE;

  return 0;
}
