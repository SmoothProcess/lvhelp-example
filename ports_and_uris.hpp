#ifndef PORTS_AND_URIS_HPP
#define PORTS_AND_URIS_HPP

#include <lvhelp/port.hpp>

struct Ports{
	lvhelp::InputAudioPort<0, "input", "Input"> input;
	lvhelp::OutputAudioPort<1, "output", "Output"> output;

	lvhelp::InputPort<
		lvhelp::port_type::Control, 2, "control", "Control",
		lvhelp::port::property::minimum<-90.0>,
		lvhelp::port::property::maximum<10.0>,
		lvhelp::port::property::default_value<0.0>
	> control;
};

struct Uris{}; // Not yet implemented

#endif