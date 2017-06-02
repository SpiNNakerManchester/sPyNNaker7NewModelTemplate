#ifndef _MY_INPUT_TYPE_H_
#define _MY_INPUT_TYPE_H_

#include <neuron/input_types/input_type.h>

typedef struct input_type_t {

    REAL my_multiplicator;

    REAL my_input_parameter;

} input_type_t;

static inline input_t input_type_get_input_value(
        input_t value, input_type_pointer_t input_type) {
    use(input_type);
    return value;
}

static void input_type_set_inhibitory_multiplicator_value(
		input_t value, input_type_pointer_t input_type,
		input_t inh_input) {
	if (inh_input >= 0.01 && input_type->my_multiplicator==0 &&
			input_type->my_input_parameter == 0)
	{ input_type->my_multiplicator = value; }
	else if (inh_input < 0.01)
	{ input_type->my_multiplicator = 0; }

	input_type->my_input_parameter = inh_input;
}

static inline input_t input_type_convert_excitatory_input_to_current(
        input_t exc_input, input_type_pointer_t input_type,
        state_t membrane_voltage) {
    use(input_type);
    use(membrane_voltage);
    return exc_input;
}

static inline input_t input_type_convert_inhibitory_input_to_current(
        input_t inh_input, input_type_pointer_t input_type,
        state_t membrane_voltage) {
    use(membrane_voltage);

    // This changes inhibitory to excitatory input
    // (without the multiplication used in sEMD model, to test...)
    return (-inh_input * input_type->my_multiplicator);
}

#endif // _MY_INPUT_TYPE_H_
