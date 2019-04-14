/*
 * 
 *TOPIC SET THR <P_S_set> <val>
 *TOPIC GET THR <P_S_set>
 *TOPIC SET TIME <val>
 *TOPIC GET TIME
 *TOPIC SET START_SEQ
 *TOPIC STATUS
 *TOPIC SET CHECK <HH:MM>
 *
*/
static char msg_payload[128];

void send_status( void ){
  snprintf(msg_payload, sizeof(msg_payload), "ct(%d) lc(%d) nc(%d) thB(%d) rB(%d) thC(%d) rC(%d) thD(%d) rD(%d)",
                  time_ctx.minutes, time_ctx.last_check, time_ctx.check_time, SENSE_B_THR, state_ctx.sense_B_read, SENSE_C_THR, state_ctx.sense_C_read, SENSE_D_THR, state_ctx.sense_D_read);
  send_msg(msg_payload); 
}

void update_thr(char *parama, char *paramb){
  int val = atoi(paramb);
  if (val < 0 || val > 1400) {
    send_msg("BAD COMMAND");
    return;
  }

  switch (parama[0]) {
    case 'B':
      SENSE_B_THR = val;
      break;
    case 'C':
      SENSE_C_THR = val;
      break;
    case 'D':
      SENSE_D_THR = val;
      break;
  }
  send_msg("OK");
}

void update_time(char *parama, char *paramb){
  int hour = atoi(parama);
  int minu = atoi(paramb);
  if ((hour < 0 || hour > 24) || (minu < 0 || minu >= 60)) {
    send_msg("BAD_COMMAND");
    return ;
  }
  time_ctx.minutes = (hour * 60) + minu;
  send_msg("OK");
}

void update_check(char *parama, char *paramb){
  int hour = atoi(parama);
  int minu = atoi(paramb);
  if ((hour < 0 || hour > 24) || (minu < 0 || minu >= 60)) {
    send_msg("BAD_COMMAND");
    return ;
  }
  time_ctx.check_time = (hour * 60) + minu;
  send_msg("OK");
  
}
void update_start( void ){
  state = IR_START;
  send_msg("OK");
}

void send_time( void ){
  snprintf(msg_payload, sizeof(msg_payload), "ct(%d) lc(%d)", time_ctx.minutes, time_ctx.last_check);
  send_msg(msg_payload);
}

void send_thr(char *param){
  switch (param[0]) {
    case 'B':
      snprintf(msg_payload, sizeof(msg_payload), "thB(%d)",SENSE_B_THR);
      break;
    case 'C':
      snprintf(msg_payload, sizeof(msg_payload), "thC(%d)",SENSE_C_THR);
      break;
    case 'D':
      snprintf(msg_payload, sizeof(msg_payload), "thD(%d)",SENSE_D_THR);
      break;
  }
  
  send_msg(msg_payload);
}
