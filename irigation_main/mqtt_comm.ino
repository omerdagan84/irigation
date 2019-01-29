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
  snprintf(msg_payload, sizeof(msg_payload), "ct(%d) lc(%d) nc(%d) thA(%d) thB(%d) thC(%d) thD(%d)",
                  minutes, last_check, check_time, SENSE_A_THR, SENSE_B_THR, SENSE_C_THR, SENSE_D_THR);
  send_msg(msg_payload); 
}

void update_time(char *param){
  int val = atoi(param);
  if (val < 0 || val > ((24 * 60) - 1)) {
    send_msg("BAD COMMAND");
    return;
  }
  minutes = val;
  send_msg("OK");
}

void update_thr(char *parama, char *paramb){
  int val = atoi(paramb);
  if (val < 0 || val > 1400) {
    send_msg("BAD COMMAND");
    return;
  }

  switch (parama[0]) {
    case 'A':
      SENSE_A_THR = val;
      break;
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

void update_check(char *parama, char *paramb){
  int hour = atoi(parama);
  int minu = atoi(paramb);
  if ((hour < 0 || hour > 24) || (minu < 0 || minu >= 60)) {
    send_msg("BAD_COMMAND");
    return ;
  }
  minutes = (hour * 60) + minu;
  send_msg("OK");
  
}
void update_start( void ){
  state = IR_START;
  send_msg("OK");
}

void send_time( void ){
  snprintf(msg_payload, sizeof(msg_payload), "ct(%d) lc(%d) thA(%d) thB(%d) thC(%d) thD(%d)",
                  minutes, last_check, SENSE_A_THR, SENSE_B_THR, SENSE_C_THR, SENSE_D_THR);
  send_msg(msg_payload);
}

void send_thr(char *param){
  switch (param[0]) {
    case 'A':
      snprintf(msg_payload, sizeof(msg_payload), "thA(%d)",SENSE_A_THR);
      break;
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
