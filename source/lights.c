/**
 * @file
 * @brief
 */


#include "lights.h"

// N: Har et forslag til implementasjon av lights-funksjonene under. Disse er avhengig av at queue_clear eller queue_remove_executed_orders har
// blitt kalt først! Er det OK tror du eller blir dette feil? Hvis man kaller lights_clear_orders(int floor) og ikke har tatt bort
// ordene enda så vil ingen lys gå av --> det burde vel ikke skje? En løsning kan være å implementere lights_clear_orders inn i 
// queue-funksjonene? Eller hva tenker du? 

void lights_clear_all_order_lights() {
    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; ++i) {
        lights_clear_orders(i);
    }
}


void lights_clear_order_lights(int floor) {
    for (int i = 0; i < INSIDE_QUEUE_SIZE; ++i) {

        if (((m_inside_queue[i]).to_floor == floor) && !m_inside_queue[i].active) {
            hardware_command_order_light(floor,HARDWARE_ORDER_INSIDE, 0);
        }

    }
    for (int i = 0; i < OUTSIDE_QUEUE_SIZE; ++i) {

        if ((m_outside_queue[i].from_floor == floor) && !m_outside_queue[i].active) {
            hardware_command_order_light(floor, m_outside_queue[i].direction, 0);     
        }

    }
}


static void clear_all_order_lights(){
    HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
}
