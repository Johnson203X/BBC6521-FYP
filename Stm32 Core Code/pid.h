#ifndef __PID_H
#define __PID_H

void PID_init(void);
float PID_realize_err(float speed);
float PID_realize(float speed);
float PID_realize_filter(float speed);

#endif