/**
 * \file basic/default/ailoss/ailoss_crossentropy_default.c
 * \version 2.0alpha
 * \date 14.01.2021
 * \copyright  Copyright (C) 2020-2021  Fraunhofer Institute for Microelectronic Circuits and Systems.
    All rights reserved.

    AIfES is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * \brief
 * \details
 */

#include "basic/default/ailoss/ailoss_crossentropy_default.h"


AISTRING_STORAGE_WRAPPER(aistring_error_loss_crossentropy_f32_1) = "[ailoss_crossentropy_f32_default] Input layer type not supported\n";

ailoss_t *ailoss_crossentropy_f32_default(ailoss_crossentropy_f32_t *loss, ailayer_t *input_layer)
{
	loss->dtype = aif32;

	loss->tensor_sub = aimath_f32_default_tensor_sub;

	// Automatically set the right crossentropy function for the output layer.
	if(input_layer->layer_type == ailayer_sigmoid_type){
        loss->crossentropy = aimath_f32_default_binary_crossentropy;
    } else if (input_layer->layer_type == ailayer_softmax_type){
        loss->crossentropy = aimath_f32_default_categorical_crossentropy;
    } else {
        // Error: Input layer type not supported
        #ifdef AIDEBUG_PRINT_ERROR_MESSAGES
            AILOG_E(aistring_error_loss_crossentropy_f32_1);
        #endif // AIDEBUG_PRINT_ERROR_MESSAGES
        return 0;
    }

	return ailoss_crossentropy(loss, input_layer);
}

AISTRING_STORAGE_WRAPPER(aistring_error_loss_crossentropy_sparse8_f32_1) = "[ailoss_crossentropy_f32_default] Input layer type not supported\n";

ailoss_t *ailoss_crossentropy_sparse8_f32_default(ailoss_crossentropy_f32_t *loss, ailayer_t *input_layer)
{
	loss->dtype = aif32;

	loss->tensor_sub = aimath_f32_default_tensor_sub_sparse8;

	// Automatically set the right crossentropy function for the output layer.
	if (input_layer->layer_type == ailayer_softmax_type){
        loss->crossentropy = aimath_f32_default_categorical_crossentropy_sparse8;
    } else {
        // Error: Input layer type not supported
        #ifdef AIDEBUG_PRINT_ERROR_MESSAGES
            AILOG_E(aistring_error_loss_crossentropy_sparse8_f32_1);
        #endif // AIDEBUG_PRINT_ERROR_MESSAGES
        return 0;
    }

	return ailoss_crossentropy(loss, input_layer);
}
