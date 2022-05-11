#include "lvhelp/plugin.hpp"

#include "ports_and_uris.hpp"
#include "config.hpp"

#include <math.h>

class TestPlugin : public lvhelp::Plugin<lvtk::Plugin<TestPlugin>, Ports, Uris>{
public:
	TestPlugin(const lvtk::Args& args) : Plugin(args){}

	void run(uint32_t n_samples){
		float volume = powf(10.f, *_ports.control.port*.05f);
		for(uint32_t i=0;i<n_samples;i++){
			_ports.output.port[i] = _ports.input.port[i]*volume;
		}
	}
};

static const lvtk::Descriptor<TestPlugin> volume(PLUGIN_IRI);