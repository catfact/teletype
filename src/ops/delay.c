#include "ops/delay.h"

#include "helpers.h"
#include "teletype.h"
#include "teletype_io.h"

static void mod_DEL_func(scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs, tele_command_t *sub_command);

static void op_DEL_CLR_get(const void *data, scene_state_t *ss,
                           exec_state_t *es, command_state_t *cs);


const tele_mod_t mod_DEL = MAKE_MOD(DEL, mod_DEL_func, 1);
const tele_op_t op_DEL_CLR = MAKE_GET_OP(DEL.CLR, op_DEL_CLR_get, 0, false);

static void mod_DEL_func(scene_state_t *ss, exec_state_t *NOTUSED(es),
                         command_state_t *cs, tele_command_t *sub_command) {
    int16_t i = 0;
    int16_t a = cs_pop(cs);

    if (a < 1) a = 1;

    while (ss->delay.time[i] != 0 && i != DELAY_SIZE) i++;

    if (i < DELAY_SIZE) {
        ss->delay.count++;
        if (ss->delay.count == 1) tele_delay(1);
        ss->delay.time[i] = a;

        copy_command(&ss->delay.commands[i], sub_command);
    }
}

static void op_DEL_CLR_get(const void *NOTUSED(data),
                           scene_state_t *NOTUSED(ss),
                           exec_state_t *NOTUSED(es),
                           command_state_t *NOTUSED(cs)) {
    clear_delays();
}
