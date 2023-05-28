#include "systemc.h"
#include "../Conv.h"
#include "../Monitor.h"
#include "../ROM.h"
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


class Conv0Creator : public ScObjectCreatorBase
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
      if (creationVerboseMode() >= 6) { std::cout << "Conv/Conv: STUB for " << hierach_name << " created." << std::endl; }
      conf::stub *result = new conf::stub(n);
       conf::stub_port_registrator<>::register_stub_port(&Conv::rst, "rst" , string(static_cast<sc_object*>(result)->name()) + ".rst" );
       conf::stub_port_registrator<>::register_stub_port(&Conv::clk, "clk" , string(static_cast<sc_object*>(result)->name()) + ".clk" );
       conf::stub_port_registrator<>::register_stub_port(&Conv::rom_rd, "rom_rd" , string(static_cast<sc_object*>(result)->name()) + ".rom_rd" );
       conf::stub_port_registrator<>::register_stub_port(&Conv::rom_addr, "rom_addr" , string(static_cast<sc_object*>(result)->name()) + ".rom_addr" );
       conf::stub_port_registrator<>::register_stub_port(&Conv::data_in, "data_in" , string(static_cast<sc_object*>(result)->name()) + ".data_in" );
       conf::stub_port_registrator<>::register_stub_port(&Conv::data_out, "data_out" , string(static_cast<sc_object*>(result)->name()) + ".data_out" );
       conf::stub_port_registrator<>::register_stub_port(&Conv::data_out_signal, "data_out_signal" , string(static_cast<sc_object*>(result)->name()) + ".data_out_signal" );
      return result;
    } else {
      if (creationVerboseMode() >= 6) { std::cout << "Conv/Conv: " << hierach_name << " created." << std::endl; }
      Conv* result = new Conv(name.c_str());
       cwr_sc_object_registry::inst().addPort(&result->rst, string(static_cast<sc_object*>(result)->name()) + ".rst" );
       cwr_sc_object_registry::inst().addPort(&result->clk, string(static_cast<sc_object*>(result)->name()) + ".clk" );
       cwr_sc_object_registry::inst().addPort(&result->rom_rd, string(static_cast<sc_object*>(result)->name()) + ".rom_rd" );
       cwr_sc_object_registry::inst().addPort(&result->rom_addr, string(static_cast<sc_object*>(result)->name()) + ".rom_addr" );
       cwr_sc_object_registry::inst().addPort(&result->data_in, string(static_cast<sc_object*>(result)->name()) + ".data_in" );
       cwr_sc_object_registry::inst().addPort(&result->data_out, string(static_cast<sc_object*>(result)->name()) + ".data_out" );
       cwr_sc_object_registry::inst().addPort(&result->data_out_signal, string(static_cast<sc_object*>(result)->name()) + ".data_out_signal" );
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



class Monitor0Creator : public ScObjectCreatorBase
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
      if (creationVerboseMode() >= 6) { std::cout << "Monitor/Monitor: STUB for " << hierach_name << " created." << std::endl; }
      conf::stub *result = new conf::stub(n);
       conf::stub_port_registrator<>::register_stub_port(&Monitor::rst, "rst" , string(static_cast<sc_object*>(result)->name()) + ".rst" );
       conf::stub_port_registrator<>::register_stub_port(&Monitor::clk, "clk" , string(static_cast<sc_object*>(result)->name()) + ".clk" );
       conf::stub_port_registrator<>::register_stub_port(&Monitor::data_in, "data_in" , string(static_cast<sc_object*>(result)->name()) + ".data_in" );
       conf::stub_port_registrator<>::register_stub_port(&Monitor::data_in_signal, "data_in_signal" , string(static_cast<sc_object*>(result)->name()) + ".data_in_signal" );
      return result;
    } else {
      if (creationVerboseMode() >= 6) { std::cout << "Monitor/Monitor: " << hierach_name << " created." << std::endl; }
      Monitor* result = new Monitor(name.c_str());
       cwr_sc_object_registry::inst().addPort(&result->rst, string(static_cast<sc_object*>(result)->name()) + ".rst" );
       cwr_sc_object_registry::inst().addPort(&result->clk, string(static_cast<sc_object*>(result)->name()) + ".clk" );
       cwr_sc_object_registry::inst().addPort(&result->data_in, string(static_cast<sc_object*>(result)->name()) + ".data_in" );
       cwr_sc_object_registry::inst().addPort(&result->data_in_signal, string(static_cast<sc_object*>(result)->name()) + ".data_in_signal" );
      return result;
    }
  }
};


class ROM0Creator : public ScObjectCreatorBase
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
      if (creationVerboseMode() >= 6) { std::cout << "ROM/ROM: STUB for " << hierach_name << " created." << std::endl; }
      conf::stub *result = new conf::stub(n);
       conf::stub_port_registrator<>::register_stub_port(&ROM::clk, "clk" , string(static_cast<sc_object*>(result)->name()) + ".clk" );
       conf::stub_port_registrator<>::register_stub_port(&ROM::rom_rd, "rom_rd" , string(static_cast<sc_object*>(result)->name()) + ".rom_rd" );
       conf::stub_port_registrator<>::register_stub_port(&ROM::rom_addr, "rom_addr" , string(static_cast<sc_object*>(result)->name()) + ".rom_addr" );
       conf::stub_port_registrator<>::register_stub_port(&ROM::data, "data" , string(static_cast<sc_object*>(result)->name()) + ".data" );
      return result;
    } else {
      if (creationVerboseMode() >= 6) { std::cout << "ROM/ROM: " << hierach_name << " created." << std::endl; }
      ROM* result = new ROM(name.c_str());
       cwr_sc_object_registry::inst().addPort(&result->clk, string(static_cast<sc_object*>(result)->name()) + ".clk" );
       cwr_sc_object_registry::inst().addPort(&result->rom_rd, string(static_cast<sc_object*>(result)->name()) + ".rom_rd" );
       cwr_sc_object_registry::inst().addPort(&result->rom_addr, string(static_cast<sc_object*>(result)->name()) + ".rom_addr" );
       cwr_sc_object_registry::inst().addPort(&result->data, string(static_cast<sc_object*>(result)->name()) + ".data" );
      return result;
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



extern void scv_tr_cwrdb_init();

int sc_main(int argc, char* argv[])
{
  scv_tr_cwrdb_init();
  ScObjectFactory::inst().addCreator ("Clock0", new Clock0Creator());
  ScObjectFactory::inst().addCreator ("Conv0", new Conv0Creator());
  ScObjectFactory::inst().addCreator ("Monitor0", new Monitor0Creator());
  ScObjectFactory::inst().addCreator ("ROM0", new ROM0Creator());
  ScObjectFactory::inst().addCreator ("Reset0", new Reset0Creator());
  ScObjectFactory::inst().addCreator ("sc_signal<bool>", new ScPrimChannelCreator<sc_signal<bool> >());
  ScObjectFactory::inst().addCreator ("sc_signal<float>", new ScPrimChannelCreator<sc_signal<float> >());
  ScObjectFactory::inst().addCreator ("sc_signal<sc_int<19> >", new ScPrimChannelCreator<sc_signal<sc_int<19> > >());
  ScObjectFactory::inst().addCreator ("sc_signal<sc_uint<7> >", new ScPrimChannelCreator<sc_signal<sc_uint<7> > >());
  ScPortFactory::inst().addCreator ("sc_in<bool>", new ScPortCreator<sc_in<bool> >());
  ScPortFactory::inst().addCreator ("sc_in<float>", new ScPortCreator<sc_in<float> >());
  ScPortFactory::inst().addCreator ("sc_in<sc_int<19> >", new ScPortCreator<sc_in<sc_int<19> > >());
  ScPortFactory::inst().addCreator ("sc_in<sc_uint<7> >", new ScPortCreator<sc_in<sc_uint<7> > >());
  ScPortFactory::inst().addCreator ("sc_inout<bool>", new ScPortCreator<sc_inout<bool> >());
  ScPortFactory::inst().addCreator ("sc_inout<float>", new ScPortCreator<sc_inout<float> >());
  ScPortFactory::inst().addCreator ("sc_inout<sc_int<19> >", new ScPortCreator<sc_inout<sc_int<19> > >());
  ScPortFactory::inst().addCreator ("sc_inout<sc_uint<7> >", new ScPortCreator<sc_inout<sc_uint<7> > >());
  ScPortFactory::inst().addCreator ("sc_out<bool>", new ScPortCreator<sc_out<bool> >());
  ScPortFactory::inst().addCreator ("sc_out<float>", new ScPortCreator<sc_out<float> >());
  ScPortFactory::inst().addCreator ("sc_out<sc_int<19> >", new ScPortCreator<sc_out<sc_int<19> > >());
  ScPortFactory::inst().addCreator ("sc_out<sc_uint<7> >", new ScPortCreator<sc_out<sc_uint<7> > >());
  if (::getenv("SNPS_SLS_DYNAMIC_LOADER_VERBOSE")) { std::cout << "Clock/Clock loaded." << std::endl; }
  if (::getenv("SNPS_SLS_DYNAMIC_LOADER_VERBOSE")) { std::cout << "Conv/Conv loaded." << std::endl; }
  if (::getenv("SNPS_SLS_DYNAMIC_LOADER_VERBOSE")) { std::cout << "Monitor/Monitor loaded." << std::endl; }
  if (::getenv("SNPS_SLS_DYNAMIC_LOADER_VERBOSE")) { std::cout << "ROM/ROM loaded." << std::endl; }
  if (::getenv("SNPS_SLS_DYNAMIC_LOADER_VERBOSE")) { std::cout << "Reset/Reset loaded." << std::endl; }

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
